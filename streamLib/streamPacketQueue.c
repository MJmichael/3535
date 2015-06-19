
/*
* ��ģ���ʹ����ο� StreamServiceThread
*/

#include "streamLib.h"
#include "commonLib.h"
#include "streamPacketQueue.h"
#include "streamFrameQueue.h"

#include "ncx_slab.h"
#include "buffer_ring.h"
/* ��ʼ�������� */
int streamInitPacketQueue(stream_packet_queue_t *pPacketQueue,int protocol)
{
#if 0
	int i = 0;

	pPacketQueue->packetTotalNum = MAX_ONE_FRAME_HAVE_PACKET_NUM;//���������Ŀ

	/* ������������ڴ�ռ� */
	if(pPacketQueue->pPacketBuf != NULL)
	{
		free(pPacketQueue->pPacketBuf);
		pPacketQueue->pPacketBuf = NULL;
	}
	pPacketQueue->pPacketBuf = (stream_packet_t *)malloc(sizeof(stream_packet_t) * pPacketQueue->packetTotalNum);
	if(pPacketQueue->pPacketBuf == NULL)
	{
		return -1;
	}

	/* ��ʼ��free/used���� */
	memset(pPacketQueue->pPacketBuf, 0, sizeof(stream_packet_t) * pPacketQueue->packetTotalNum);
	pPacketQueue->freeHead.next = (stream_packet_t *)&pPacketQueue->pPacketBuf[0];

    if(protocol==0)
    {
        for(i = 0; i < pPacketQueue->packetTotalNum - 1; i++)
        {//��buffer��������
            pPacketQueue->pPacketBuf[i].next = (stream_packet_t *)&pPacketQueue->pPacketBuf[i+1];
#if 1
            pPacketQueue->pPacketBuf[i].pPacketBuf = (char *)malloc(MAX_STREAM_PACKET_SIZE);
            if( pPacketQueue->pPacketBuf[i].pPacketBuf ==NULL)
            {
                usleep(10*1000);
                pPacketQueue->pPacketBuf[i].pPacketBuf = (char *)malloc(MAX_STREAM_PACKET_SIZE);
                continue;
            }
#endif

		}
	}
	else if(protocol==1)
	{
		for(i = 0; i < pPacketQueue->packetTotalNum - 1; i++)
		{//buffer
			pPacketQueue->pPacketBuf[i].next = (stream_packet_t *)&pPacketQueue->pPacketBuf[i+1];
		}
	}
	pPacketQueue->pFreeLast = (stream_packet_t *)&pPacketQueue->pPacketBuf[i];
	pPacketQueue->freeBufNum = pPacketQueue->packetTotalNum;
	pPacketQueue->usedBufNum = 0;
	pPacketQueue->copyBufNum =0;



#if 0
	pPacketQueue->pPoolBuf = (char *)malloc(MAX_FRAME_BUFFER_LEN);
	memset(pPacketQueue->pPoolBuf, 0, MAX_FRAME_BUFFER_LEN);
	pPacketQueue->sp = (ncx_slab_pool_t*) pPacketQueue->pPoolBuf;
	pPacketQueue->sp->addr = pPacketQueue->pPoolBuf;
	pPacketQueue->sp->min_shift = 3;
	pPacketQueue->sp->end = pPacketQueue->pPoolBuf + MAX_FRAME_BUFFER_LEN;
	ncx_slab_init(pPacketQueue->sp);

	ncx_slab_stat_t stat;
	ncx_slab_stat(pPacketQueue->sp, &stat);
#endif

#endif

    int ret = 0;
    ret = ring_init(&pPacketQueue->ringBuf, MAX_FRAME_BUFFER_LEN);
    ret = PacketBuffer_init(&pPacketQueue->packetBuf,MAX_FRAME_BUFFER_LEN);

    return ret;
}


/* ������ */
void streamUninitPacketQueue(stream_packet_queue_t *pPacketQueue,int protocol)
{

#if 0
	int i ;
	if(1 == protocol)
	{
		for(i = 0; i < pPacketQueue->packetTotalNum - 1; i++)
		{//buffer
			if(pPacketQueue->pPacketBuf[i].pPacketBuf!= NULL)
			{
				free(pPacketQueue->pPacketBuf[i].pPacketBuf);
				pPacketQueue->pPacketBuf[i].pPacketBuf = NULL;
			}
		}
	}

	if(pPacketQueue->pPacketBuf != NULL)
	{

		free(pPacketQueue->pPacketBuf);
		pPacketQueue->pPacketBuf = NULL;
	}

	if(pPacketQueue->pPoolBuf != NULL)
	{
		free(pPacketQueue->pPoolBuf);
		pPacketQueue->pPoolBuf = NULL;
	}
 #endif
	ring_destroy(&pPacketQueue->ringBuf);
    PacketBuffer_destroy(&pPacketQueue->ringBuf);
}

stream_packet_t * private_protocol_streamGetPacketWriteBuffer(stream_packet_queue_t *pPacketQueue)
{
#if TEMP
	stream_packet_t *pTmpBuf = NULL;
	do
	{
		if(pPacketQueue->freeHead.next == NULL)
		{//
			//  Printf("can not find free buffer, used num %d, free num %d\r\n", pPacketQueue->usedBufNum, pPacketQueue->freeBufNum);
			streamPushPacketBufferToFrameBuffer(pPacketQueue);//bufferbuffer
			break;
		}

		/* buffer */
		pTmpBuf = pPacketQueue->freeHead.next;
		pPacketQueue->freeHead.next = pPacketQueue->freeHead.next->next;
#if 0
		pPacketQueue->freeBufNum--;
		if(pPacketQueue->freeBufNum == 0)
		{
			pPacketQueue->pFreeLast = NULL;
		}
#endif

		if(pTmpBuf->pPacketBuf != NULL)
		{
			// Printf("WWWWWWWWWWWWWWWWWWWWWWWWWWWW\r\n");
			free(pTmpBuf->pPacketBuf);
			//ncx_slab_free(pPacketQueue->sp, pTmpBuf->pPacketBuf);
			pTmpBuf->pPacketBuf = NULL;
		}

		memset(pTmpBuf, 0, sizeof(stream_packet_t));

	}while(0);

	return pTmpBuf;
#endif
}


/*********************************************************
 * ��ȡ���еİ�buffer
 * packetSeq:	�����
 *********************************************************/
stream_packet_t * streamGetPacketWriteBuffer(stream_packet_queue_t *pPacketQueue)
{
#if TEMP
    stream_packet_t *pTmpBuf = NULL;
    do
    {
        if(pPacketQueue->freeHead.next == NULL)
        {////�޿��õĻ���ռ�
            //  Printf("can not find free buffer, used num %d, free num %d\r\n", pPacketQueue->usedBufNum, pPacketQueue->freeBufNum);
            streamPushPacketBufferToFrameBuffer(pPacketQueue);//�����еİ�buffer������֡buffer
            break;
        }

        /* ȡ�õ�һ������buffer���������Ƴ��������� */
        pTmpBuf = pPacketQueue->freeHead.next;
        pPacketQueue->freeHead.next = pPacketQueue->freeHead.next->next;
#if 1
        pPacketQueue->freeBufNum--;
        if(pPacketQueue->freeBufNum == 0)
        {
            pPacketQueue->pFreeLast = NULL;
        }
#endif

#if 0
        if(pTmpBuf->pPacketBuf != NULL)
        {
           // Printf("WWWWWWWWWWWWWWWWWWWWWWWWWWWW\r\n");
            free(pTmpBuf->pPacketBuf);
            //ncx_slab_free(pPacketQueue->sp, pTmpBuf->pPacketBuf);
            pTmpBuf->pPacketBuf = NULL;
        }
 #endif

		//  memset(pTmpBuf, 0, sizeof(stream_packet_t));
		pTmpBuf->next = NULL;
		pTmpBuf->pre = NULL;



	}while(0);

	return pTmpBuf;
#endif
}

/* ����buffer���뵽ʹ�ö����� */
int streamInsertQueue(stream_packet_queue_t *pPacketQueue, stream_packet_t *pStreamBuf)
{
#if TEMP
	int ret = 0;
	stream_packet_t *pTmpBuf = NULL;

	pTmpBuf = pPacketQueue->pUsedLast;
	if(pTmpBuf == NULL)
	{
		//		Printf("the first packet, seq %d\r\n", pStreamBuf->packetHead.seq);
		pPacketQueue->usedHead.next = pStreamBuf;
		pPacketQueue->pUsedLast = pStreamBuf;
		pStreamBuf->next = NULL;
		pStreamBuf->pre = NULL;
	}
	else
	{
		pTmpBuf->next = pStreamBuf;
		pStreamBuf->next = NULL;
		pStreamBuf->pre = pTmpBuf;
		pPacketQueue->pUsedLast = pStreamBuf;
	}
	pPacketQueue->usedBufNum++;

	return ret;
#endif
}

/*********************************************************
 * ��ȡʹ�ö��еĵ�һ����buffer
 *********************************************************/
stream_packet_t * streamGetPacketUsedBuffer(stream_packet_queue_t *pPacketQueue)
{

#if TEMP
	stream_packet_t * pTmpBuf = NULL;

	do
	{
		if(pPacketQueue->usedHead.next == NULL)
		{//�޿��õĻ���ռ�
			pPacketQueue->copyBufNum= 0;
			//pPacketQueue->freeBufNum= 0;
			//Printf("can not find used buffer, used num %d, free num %d\r\n", pPacketQueue->usedBufNum, pPacketQueue->freeBufNum);
			break;
		}

		/* ȡ�õ�һ������buffer���������Ƴ��������� */
		pTmpBuf = pPacketQueue->usedHead.next;
		pPacketQueue->usedHead.next = pPacketQueue->usedHead.next->next;
		pPacketQueue->usedBufNum--;
		if(pPacketQueue->usedBufNum == 0)
		{
			pPacketQueue->pUsedLast = NULL;
		}
	}while(0);


	return pTmpBuf;
#endif
}


void private_protocol_streamFreeUsedBuffer(stream_packet_queue_t *pPacketQueue, stream_packet_t *pStreamBuf)
{
#if TEMP
	stream_packet_t *pTmpBuf = NULL;

#if 1
	if(pStreamBuf->pPacketBuf != NULL)
	{
		 free(pStreamBuf->pPacketBuf);
		//ncx_slab_free(pPacketQueue->sp, pStreamBuf->pPacketBuf);
		pStreamBuf->pPacketBuf = NULL;
	}
#endif


	memset(pStreamBuf, 0, sizeof(stream_packet_t));

	/* buffer */
	pTmpBuf = pPacketQueue->pFreeLast;
	if(pTmpBuf == NULL)
	{

		pPacketQueue->freeHead.next = pStreamBuf;
		pPacketQueue->pFreeLast = pStreamBuf;
	}
	else
	{

		pTmpBuf->next = pStreamBuf;
		pStreamBuf->pre = pTmpBuf;
		pPacketQueue->pFreeLast = pStreamBuf;
	}
	pPacketQueue->freeBufNum++;
	pPacketQueue->copyBufNum++;

	// fprintf(stderr,"!!!!!!!!!!!pPacketQueue->pPacketBufNum =%d ,pStreamBuf->packetHead.channel =%d\r\n",pPacketQueue->pPacketBufNum,pStreamBuf->packetHead.channel);
#endif
}


/* ��ʹ�ù��İ�buffer���뵽δʹ�õ������� */
void streamFreeUsedBuffer(stream_packet_queue_t *pPacketQueue, stream_packet_t *pStreamBuf)
{

#if TEMP
	stream_packet_t *pTmpBuf = NULL;

#if 0
	if(pStreamBuf->pPacketBuf != NULL)
	{
		Printf("WWWWWWWWWWWWWWWWWWWWWWWWWWWW\r\n");
		// free(pStreamBuf->pPacketBuf);
		//ncx_slab_free(pPacketQueue->sp, pStreamBuf->pPacketBuf);
		pStreamBuf->pPacketBuf = NULL;
	}
#endif


	//  memset(pStreamBuf, 0, sizeof(stream_packet_t));
	pStreamBuf->next = NULL;
	pStreamBuf->pre = NULL;

	/* ��buffer���뵽δʹ���������� */
	pTmpBuf = pPacketQueue->pFreeLast;
	if(pTmpBuf == NULL)
	{

		pPacketQueue->freeHead.next = pStreamBuf;
		pPacketQueue->pFreeLast = pStreamBuf;
	}
	else
	{

		pTmpBuf->next = pStreamBuf;
		pStreamBuf->pre = pTmpBuf;
		pPacketQueue->pFreeLast = pStreamBuf;
	}
	pPacketQueue->freeBufNum++;
	pPacketQueue->copyBufNum++;

	// fprintf(stderr,"!!!!!!!!!!!pPacketQueue->pPacketBufNum =%d ,pStreamBuf->packetHead.channel =%d\r\n",pPacketQueue->pPacketBufNum,pStreamBuf->packetHead.channel);

#endif
}

void AudiostreamFreeUsedBuffer(stream_packet_queue_t *pPacketQueue, stream_packet_t *pStreamBuf)
{
#if TEMP
    stream_packet_t *pTmpBuf = NULL;

#if 0
    if(pStreamBuf->pPacketBuf != NULL)
    {
      //  Printf("WWWWWWWWWWWWWWWWWWWWWWWWWWWW\r\n");
         free(pStreamBuf->pPacketBuf);
        //ncx_slab_free(pPacketQueue->sp, pStreamBuf->pPacketBuf);
        pStreamBuf->pPacketBuf = NULL;
    }
#endif


    //  memset(pStreamBuf, 0, sizeof(stream_packet_t));
    pStreamBuf->next = NULL;
    pStreamBuf->pre = NULL;

    /* buffer */
    pTmpBuf = pPacketQueue->pFreeLast;
    if(pTmpBuf == NULL)
    {
        pPacketQueue->freeHead.next = pStreamBuf;
        pPacketQueue->pFreeLast = pStreamBuf;
    }
    else
    {
        pTmpBuf->next = pStreamBuf;
        pStreamBuf->pre = pTmpBuf;
        pPacketQueue->pFreeLast = pStreamBuf;
    }
     pPacketQueue->freeBufNum++;
    // pPacketQueue->copyBufNum++;

    // fprintf(stderr,"!!!!!!!!!!!pPacketQueue->pPacketBufNum =%d ,pStreamBuf->packetHead.channel =%d\r\n",pPacketQueue->freeBufNum,pStreamBuf->packetHead.channel);
#endif
}

/* ��ȡһ֡��Ƶ */
int streamGetFrameBuf(stream_packet_queue_t *pPacketQueue, char *pStreamBuf, int streamBufLen)
{
#if TEMP
	int streamLen = 0;

	stream_packet_t *pTmpBuf = NULL;
	int status = 1;//1//1����ȡһ֡�Ŀ�ʼ 3����ȡ������֡  2����ȡһ֡����  0���ܹ���һ����  5������
	int offset = 0;//�Ѿ�������֡����
	unsigned short packetNo = 0;//�����

	static int count = 0;


	while(1)
	{
		if((status == 1) || (status == 3))
		{
			if(count%200 == 0)
			{
				Printf("used buffer num %d, free num %d, total num %d\r\n", pPacketQueue->usedBufNum, pPacketQueue->freeBufNum, pPacketQueue->packetTotalNum);
			}
			count++;
			pTmpBuf = pPacketQueue->usedHead.next;
			if(pTmpBuf == NULL)
			{
				//				Printf("used buffer queue is NULL\r\n");
				return -2;
			}

			/* ��buffer���Ѿ�ʹ�õ��������Ƴ� */
			pPacketQueue->usedHead.next = pTmpBuf->next;
			if(pPacketQueue->usedHead.next != NULL)
			{
				pPacketQueue->usedHead.next->pre = NULL;
			}
			pPacketQueue->usedBufNum--;
			if(pPacketQueue->usedBufNum == 0)
			{
				pPacketQueue->pUsedLast = NULL;
			}
			//			Printf("status %d, seqType %d, seq %d\r\n", status, pTmpBuf->packetHead.seqType, pTmpBuf->packetHead.seq);
		}

		switch(status)
		{
			case 1://��һ��
#if 0
				if((pTmpBuf->packetHead.seqType == 1) || (pTmpBuf->packetHead.seqType == 0))
				{//һ֡�Ŀ�ʼ
					if(pTmpBuf->packetHead.seqType == 0)
					{//�ǵ�һ��Ҳ�����һ��
						status = 0;
					}
					else
					{
						status = 3;
					}
					if((pTmpBuf->packetHead.len > 0) && (pTmpBuf->packetHead.len <= (streamBufLen - offset)))
					{
						memcpy(pStreamBuf, pTmpBuf->streamBuf, pTmpBuf->packetHead.len);
						offset += pTmpBuf->packetHead.len;
					}
					else
					{
						Printf("1 error, len = %d, total len = %d, offset = %d\r\n", pTmpBuf->packetHead.len, streamBufLen, offset);
						status = 5;
					}
				}
#endif
				packetNo = pTmpBuf->packetHead.seq;
				streamFreeUsedBuffer(pPacketQueue, pTmpBuf);
				break;
			case 2://����
				streamLen = offset;
				break;
			case 3://�����
				if(packetNo + 1 != pTmpBuf->packetHead.seq)
				{//�������������ȡ��֡����
					Printf("seq error, %d.%d\r\n", packetNo, pTmpBuf->packetHead.seq);
					status = 5;
				}
				else
				{
#if 0
					if((pTmpBuf->packetHead.len > 0) && (pTmpBuf->packetHead.len <= (streamBufLen - offset)))
					{
						memcpy(pStreamBuf + offset, pTmpBuf->streamBuf, pTmpBuf->packetHead.len);
						offset += pTmpBuf->packetHead.len;
						if(pTmpBuf->packetHead.seqType == 3)
						{//�м��
							status = 3;
						}
						else if(pTmpBuf->packetHead.seqType == 2)
						{//���һ��
							status = 2;
						}
					}
					else
					{
						Printf("2 error, len = %d, total len = %d, offset = %d\r\n", pTmpBuf->packetHead.len, streamBufLen, offset);
						status = 5;
					}
#endif
				}
				packetNo = pTmpBuf->packetHead.seq;
				streamFreeUsedBuffer(pPacketQueue, pTmpBuf);
				break;
			case 0:
				streamLen = offset;
				break;
			case 5://
				streamLen = -1;
				break;
			default:
				streamLen = -1;
				break;
		}

		if(streamLen == -1)
		{
			Printf("get stream buf error\r\n");
			break;
		}
		else if(streamLen > 0)
		{//��ȡ���ݳɹ�
			break;
		}
		else
		{//���ڻ�ȡ����
		}
	}


	return streamLen;
#endif
}

/* ��ȡ�����е�ǰ���ĸ��� */
int streamPacketBufferNum(stream_packet_queue_t *pPacketQueue)
{
#if TEMP
	int bufNum = 0;

	bufNum = pPacketQueue->usedBufNum;

	return bufNum;
#endif
}

/* ������������е�����ˢ��֡������ */
void streamPushPacketBufferToFrameBuffer(stream_packet_queue_t *pPacketQueue)
{
#if TEMP
	if(streamPacketBufferNum(pPacketQueue) <= 0)
	{
		return;
	}
#if 0
	int streamLen = 0;
	char streamBuf[MAX_STREAM_FRAME_SIZE] = {0};

	//	Printf("start push left packet buf to frame buf\r\n");
	while(1)
	{
		streamLen = streamGetFrameBuf(pPacketQueue, streamBuf, sizeof(streamBuf));
		if(streamLen == -2)
		{//�������Ѿ������
			break;
		}
		else if(streamLen == -1)
		{//��ȡһ֡ʧ��
		}
		else if(streamLen > 0)
		{//ȡ��������һ֡�������֡����
			//			streamFrameSendFrameToNetPool(pPacketQueue, streamBuf, streamLen);
		}
	}

	//	Printf("end push left packet buf to frame buf\r\n");
#else
	stream_packet_t * pUsedPacket = NULL;

	while(1)
	{//�����ʹ�õİ�����
		pUsedPacket = streamGetPacketUsedBuffer(pPacketQueue);
		if(pUsedPacket == NULL)
		{
			break;
		}
		streamFreeUsedBuffer(pPacketQueue, pUsedPacket);
	}
#endif

   #endif
}

