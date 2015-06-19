/*
 *  StreamServiceThread
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

#include "myMalloc.h"
#include "streamFrameQueue.h"
#include "streamLib.h"
#include "commonLib.h"


int streamInitFrameQueue(stream_frame_queue_t *pFrameQueue)
{
	memset(pFrameQueue, 0x00, sizeof(stream_frame_queue_t));

	if(pthread_mutex_init(&pFrameQueue->frameMutex, NULL) != 0)
	{
		perror("pthread_mutex_init");
		exit(0);
	}
	pthread_cond_init(&pFrameQueue->frameCond, NULL);

	return 0;
}

void streamUninitFrameQueue(stream_frame_queue_t *pFrameQueue)
{
	int i = 0;

	pthread_mutex_lock(&pFrameQueue->frameMutex);
	pthread_cond_broadcast(&pFrameQueue->frameCond);

	for(i = 0; i < MAX_FRAME_QUEUE_NUM; i++)
	{
		if(pFrameQueue->pFrameInfo[i] != NULL)
		{
#if 1
			ShareFree(pFrameQueue->pFrameInfo[i]);
#else
			free(pFrameQueue->pFrameInfo[i]);
#endif
			pFrameQueue->pFrameInfo[i] = NULL;
		}
	}

	pthread_mutex_unlock(&pFrameQueue->frameMutex);
	pthread_mutex_destroy(&pFrameQueue->frameMutex);	 	
	pthread_cond_destroy(&pFrameQueue->frameCond);
}


//////////////////////////////////////////////////////////////////////
/* Ϊ�˼���һ�ο����������������¼����������õ�ʱ��ע����*/
/* ��ס֡���� */
void streamFrameQueueLock(stream_frame_queue_t *pFrameQueue)
{
	pthread_mutex_lock(&pFrameQueue->frameMutex);
}
/* ����֡���� */
void steramFrameQueueUnlock(stream_frame_queue_t *pFrameQueue)
{
	pthread_cond_broadcast(&pFrameQueue->frameCond);
	pthread_mutex_unlock(&pFrameQueue->frameMutex);
}
/* ��ȡһ֡�Ļ��� */
stream_frame_t * streamGetFrameQueueBuffer(stream_frame_queue_t *pFrameQueue, int frameLen)
{
	stream_frame_t *pFrame = NULL;
	int len = sizeof(stream_frame_t) + frameLen;

	//len = ((len + 3)/4) * 4;//4
	len = ((len / 512) + 1) * 512;

#if 1
	pFrame = (stream_frame_t *)ShareMalloc(len);
#else
	pFrame = (stream_frame_t *)malloc(len);
#endif
	if(pFrame == NULL)
	{
		Printf("streamGetFrameQueueBuffer error, len = %d\r\n", len);
	}

	return pFrame;
}
/* ����һ֡��֡������   ��ָ�븳ֵ��*/
void streamInsertFrameToFrameQueue(stream_frame_queue_t *pFrameQueue, stream_frame_t *pFrame)
{
	int writePos = 0;

	writePos = pFrameQueue->writePos;

	if(pFrameQueue->pFrameInfo[writePos] != NULL)
	{
#if 1
		ShareFree(pFrameQueue->pFrameInfo[writePos]);
#else
		free(pFrameQueue->pFrameInfo[writePos]);
		pFrameQueue->pFrameInfo[writePos] = NULL;
#endif
	}
	pFrameQueue->pFrameInfo[writePos] = pFrame;

	writePos = (writePos + 1) % MAX_FRAME_QUEUE_NUM;
	pFrameQueue->writePos = writePos;
//	Printf("cur write %d\r\n", writePos);
}
//////////////////////////////////////////////////////////////////////


#if 0
/* ����һ֡���ݵ�֡������  �����ݿ�����*/
int streamSendFrameToNetPool(stream_frame_queue_t *pFrameQueue, char *pStreamBuf, int streamBufLen)
{			
	int writePos = 0;

	pthread_mutex_lock(&pFrameQueue->frameMutex);

	writePos = pFrameQueue->writePos;

	ShareFree(pFrameQueue->pFrameInfo[writePos]);
	pFrameQueue->pFrameInfo[writePos] = (stream_frame_t *)ShareMalloc( sizeof(stream_frame_t) + streamBufLen );

	pFrameQueue->pFrameInfo[writePos]->frameHead.len = streamBufLen;
	memcpy(pFrameQueue->pFrameInfo[writePos]->pFrameBuf, pStreamBuf, streamBufLen);

	writePos = (writePos + 1) % MAX_FRAME_QUEUE_NUM;
	pFrameQueue->writePos = writePos;

	pthread_mutex_unlock(&pFrameQueue->frameMutex);	

	return 0;
}
#endif

/* �ȴ�һ֡��Ƶ */
int streamWaitFrame(stream_frame_queue_t *pFrameQueue)
{
	int ret = 0;
	struct timeval curTime;
	struct timespec timeOut;

	pthread_mutex_lock(&pFrameQueue->frameMutex);

	/* ���ó�ʱ�ȴ� */
	gettimeofday(&curTime, NULL);
	timeOut.tv_sec = curTime.tv_sec + 1;
	timeOut.tv_nsec = curTime.tv_usec * 1000;
	ret = pthread_cond_timedwait(&pFrameQueue->frameCond, &pFrameQueue->frameMutex, &timeOut);
	if(ret == ETIMEDOUT)
	{
//		Printf("wait frame is time out\r\n");
		ret = -1;
	}

	pthread_mutex_unlock(&pFrameQueue->frameMutex);

	return 0;
}

/* ��ȡһ֡��Ƶ */
stream_frame_t* streamGetFrameFromNetPool(stream_frame_queue_t *pFrameQueue, int *pReadBegin, int *pReadEnd)
{
	int writePos = 0;
	stream_frame_t *pFrameInfo = NULL;

	if(pFrameQueue == NULL)
	{
		return NULL;
	}

	if((*pReadBegin == *pReadEnd) && (*pReadEnd == pFrameQueue->writePos))
	{
		return NULL;
	}
	//Printf("*pReadBegin =%d *pReadEnd =%d\n",*pReadBegin,*pReadEnd);

	pthread_mutex_lock(&pFrameQueue->frameMutex);	

	if((*pReadBegin == -1) && (*pReadEnd == -1))
	{//ƽ��
		*pReadBegin = (pFrameQueue->writePos + MAX_FRAME_QUEUE_NUM/2)%MAX_FRAME_QUEUE_NUM;
		*pReadEnd = (pFrameQueue->writePos + MAX_FRAME_QUEUE_NUM/2)%MAX_FRAME_QUEUE_NUM;
	}
	else if((*pReadBegin == -2) && (*pReadEnd == -2))
	{//ʵʱ
		//*pReadBegin = (pFrameQueue->writePos - 5)%MAX_FRAME_QUEUE_NUM;
		//*pReadEnd = (pFrameQueue->writePos - 5)%MAX_FRAME_QUEUE_NUM;
		*pReadBegin = (pFrameQueue->writePos)%MAX_FRAME_QUEUE_NUM;
		*pReadEnd = (pFrameQueue->writePos)%MAX_FRAME_QUEUE_NUM;
	}
	else if((*pReadBegin == -3) && (*pReadEnd == -3))
	{//�ӻ��������ʼ��ȡ��������Ԥ��
		*pReadBegin = (pFrameQueue->writePos + 1)%MAX_FRAME_QUEUE_NUM;
		*pReadEnd = pFrameQueue->writePos;
	}

	writePos = pFrameQueue->writePos;
//	Printf("cur read %d, end %d,  cur write %d\r\n", *pReadBegin, *pReadEnd, writePos);

	if((*pReadBegin <= *pReadEnd && *pReadEnd <= writePos) || (*pReadEnd <= writePos && writePos <= *pReadBegin) || (writePos <= *pReadBegin && *pReadBegin <= *pReadEnd))
	{
		*pReadEnd = writePos;
#if 1
		pFrameInfo = (stream_frame_t *)ShareCopy(pFrameQueue->pFrameInfo[*pReadBegin]);		
#else
		pFrameInfo = pFrameQueue->pFrameInfo[*pReadBegin];
		pFrameQueue->pFrameInfo[*pReadBegin] = NULL;
#endif
		*pReadBegin = (*pReadBegin + 1) % MAX_FRAME_QUEUE_NUM;
	}
	else
	{
//		Printf("failed : lost frame, rb(%d), re(%d), wp(%d)!\r\n", *pReadBegin, *pReadEnd, writePos);
		*pReadEnd = writePos;
		*pReadBegin = (*pReadBegin + 10) % MAX_FRAME_QUEUE_NUM;//writePos;
	}

	pthread_mutex_unlock(&pFrameQueue->frameMutex);

	return pFrameInfo;
}

/* �ͷ�һ֡��Ƶ */
void streamFreeFrameBuffer(stream_frame_queue_t *pFrameQueue, stream_frame_t *pFrameInfo)
{
#if 1
	ShareFree(pFrameInfo);
#else
	free(pFrameInfo);
	pFrameInfo = NULL;
#endif
}

/* �ͷ�����֡��Ƶbuf */
void streamFreeAllFrameBuffer(stream_frame_queue_t *pFrameQueue)
{
	int i = 0;

	pthread_mutex_lock(&pFrameQueue->frameMutex);
	for(i = 0; i < MAX_FRAME_QUEUE_NUM; i++)
	{
		if(pFrameQueue->pFrameInfo[i] != NULL)
		{
#if 1
			ShareFree(pFrameQueue->pFrameInfo[i]);
#else
			free(pFrameQueue->pFrameInfo[i]);
#endif
			pFrameQueue->pFrameInfo[i] = NULL;
		}
	}

	pFrameQueue->writePos = 0;

	pthread_mutex_unlock(&pFrameQueue->frameMutex);
}


