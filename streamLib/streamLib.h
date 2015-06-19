#ifndef __STREAM_LIB_H__
#define __STREAM_LIB_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sched.h>
#include <sys/resource.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "ncx_slab.h"
#include "buffer_ring.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define FRAME_TYPE_VIDEO 0//��Ƶ֡
#define FRAME_TYPE_AUDIO 1//��Ƶ֡

#define NAL_TYPE_SLICE      1
#define NAL_TYPE_IDR        5
#define NAL_TYPE_SEI        6
#define NAL_TYPE_SPS        7
#define NAL_TYPE_PPS        8
#define NAL_TYPE_SEQ_END    9
#define NAL_TYPE_STREAM_END 10



//#define MAX_DISPLAY_CHANNEL_NUM		1//  �����ʾ��������
//#define MAX_DECODE_CHANNEL_NUM		MAX_DISPLAY_CHANNEL_NUM//���⼸·����
//#define MAX_MCTP_NUM			MAX_DISPLAY_CHANNEL_NUM//������ҳ�߳���
//#define MAX_PLAT_NUM			1//����ƽ̨�߳���
//#define MAX_RECORD_NUM			1//����¼���߳���
//#define MAX_RETORE_ALARM_NUM		MAX_DISPLAY_CHANNEL_NUM//���ı�����һ����λ�߳�
//#define MAX_AUDIO_NUM			MAX_DISPLAY_CHANNEL_NUM//������Ƶ�߳�
//#define MAX_MAC_NUM			MAX_DISPLAY_CHANNEL_NUM//�����޸�MAC��ַ�߳�
//#define MAX_RECV_CHANNEL_NUM		MAX_DISPLAY_CHANNEL_NUM//�����ռ�·��Ƶ��
#define MAX_FRAME_QUEUE_NUM		(40)//֡������е���Ŀ
#define MAX_FRAME_BUFFER_LEN 		(1024 * 1024)//����һ֡�ĳ���
#define MAX_STREAM_PACKET_SIZE		(1500)//��������
#define MAX_ONE_FRAME_HAVE_PACKET_NUM	(MAX_FRAME_BUFFER_LEN/MAX_STREAM_PACKET_SIZE)//һ֡����ж��ٸ���
#define MAX_YUV_QUEUE_NUM		3//yuv���е���Ŀ
#define MAX_ADDR_LEN			64//ip��ַ�ĳ���
#ifdef HI3535
#define MAX_ALARM_QUEUE_NUM		(150)//
#else
#define MAX_ALARM_QUEUE_NUM		(50)//
#endif



typedef enum frame_video_e
{
	/* ��Ƶ֡���� */
	FRAME_VIDEO_TYPE_H264 = 0,
	FRAME_VIDEO_TYPE_MPEG4 = 1,
	FRAME_VIDEO_TYPE_JPEG = 2,

	/* ��Ƶ֡�ֱ��� */
	FRAME_VIDEO_RESOLUTION_352x288 = 0,
	FRAME_VIDEO_RESOLUTION_720x576 = 1,
	FRAME_VIDEO_RESOLUTION_1280x720 = 2,
	FRAME_VIDEO_RESOLUTION_1920X1080 = 3,
	FRAME_VIDEO_RESOLUTION_2048X1536 = 4,

}frame_video_e;

typedef enum frame_audio_e
{
	/* ��Ƶ֡���� */
	FRAME_AUDIO_TYPE_G711 = 0,//

	/* ��Ƶ������ */
	FRAME_AUDIO_SAMPLE_RATE_8K = 0,//8K
	FRAME_AUDIO_SAMPLE_RATE_32K = 1,//32K
	/* ��Ƶλ�� */
	FRAME_AUDIO_BIT_WIDE_8 = 0,//8λ
	FRAME_AUDIO_BIT_WIDE_16 = 1,//16λ

	/* ��Ƶͨ�� */
	FRAME_AUDIO_CHANNEL_1 = 0,//��ͨ��
	FRAME_AUDIO_CHANNEL_2 = 1,//˫ͨ��

}frame_audio_e;


typedef struct stream_packet_head_t
{
	unsigned short seq;//�ð���seq��
	char channel;//  �ð���ͨ��  0����Ƶ  2����Ƶ
	//char unused[1];//����
	char isKey;
	unsigned int pts;
	unsigned short offset;//��Ч���ݵ���ʼ��ַ
	unsigned int len;//��Ч���ݵĳ���
}stream_packet_head_t;

typedef struct stream_packet_t
{
	struct stream_packet_t *next;
	struct stream_packet_t *pre;
	stream_packet_head_t packetHead;
    char * pPacketBuf;  //[MAX_STREAM_PACKET_SIZE];//rtp
}stream_packet_t;

typedef struct stream_packet_queue_t
{//������
#if 0
	unsigned int packetTotalNum;//�������ܵĳ���
	stream_packet_t *pPacketBuf;//�������ܵ�buf

    unsigned int freeBufNum;//���еİ���Ŀ
	stream_packet_t freeHead;//���еİ�����ͷ
	stream_packet_t *pFreeLast;//���еİ�����β
     unsigned int copyBufNum;//
	unsigned int usedBufNum;//ʹ�õİ���Ŀ
    // int pPacketBufNum;
	stream_packet_t usedHead;//ʹ�õİ�����ͷ
	stream_packet_t *pUsedLast;//ʹ�õİ�����β

	/*  */
	char *pPoolBuf;//
	ncx_slab_pool_t *sp;
#endif



    Packet_buffer_t packetBuf;
    ring_buffer_t ringBuf;//buf
    unsigned char startFlag;//

}stream_packet_queue_t;

typedef struct stream_frame_head_t
{
	unsigned char type;//֡��ʽ  0����Ƶ  1����Ƶ
	unsigned char source;//0:ipc  1:ƽ̨  (��Ϊ֡�������ʽ��һ���� 0��sps��pps��I��P���ǵ�����һ֡   1��sps��pps��I��һ֡��P��һ֡)
	unsigned short frameNo;//֡��
	struct timeval tv;//
	unsigned int pts;
	unsigned char save[4];//
	//unsigned char save[8];//�����ֶ�
	union
	{
		struct
		{
			unsigned char format;//�����ʽ         0:H264     1:mpeg4    2:jpeg  
			unsigned char resolution;//�ֱ���       0:352*288  1:720*576  2:1280*720  3:1920*1080
			unsigned short bitRate;//����  bitRate*1024
			unsigned short width;//��
			unsigned short height;//��
			unsigned char frameRate;//֡��
			unsigned char forceRestartNum;//ǿ������������
			unsigned char unused[2];//����
		}video;
		struct
		{
			unsigned char format;//�����ʽ 0:G711 
			unsigned char sampleRate;//������  0��8K  1��32K
			unsigned char channel;//ͨ��  0����ͨ��  1��˫ͨ��
			unsigned char bitWide;//λ��  0:8λ  1��16λ
			unsigned char unused[8];//����
		}audio;
	}info;
	int len;//֡����
}stream_frame_head_t;
typedef struct stream_frame_t
{
	stream_frame_head_t frameHead;
	char pFrameBuf[0];//֡����
}stream_frame_t;

/* ֡���� */
typedef struct stream_frame_queue_t
{
	int writePos;
	pthread_mutex_t frameMutex;
	pthread_cond_t frameCond;
	stream_frame_t *pFrameInfo[MAX_FRAME_QUEUE_NUM];
}stream_frame_queue_t;

typedef struct stream_yuv_head_t
{//yuvͷ��Ϣ
	unsigned char resolution;//�ֱ���  0��352*288  1:720*576  2:1280*720  3:1920*1080
	unsigned char frameRate;//֡��
	unsigned short bitRate;//����  bitRate*1024
	unsigned short width;//��
	unsigned short height;//��
	int len;//֡����
}stream_yuv_head_t;
typedef struct stream_yuv_t
{//yuv��Ϣ
	int yuvNo;//no;//
	stream_yuv_head_t yuvHead;
//	BufferGfx_Dimensions srcDim;
//	BufferGfx_Dimensions dstDim;
	char *pYuvBuf;//һ��yuv���ݵ�buf��ָ��pYuvDataBuf�е�ĳ���ڴ�
	unsigned long pYuvBufPhyAddr;//yuvbuf�������ַ
	struct stream_yuv_t *next;
	struct stream_yuv_t *pre;
}stream_yuv_t;
typedef struct stream_yuv_queue_t
{//yuv����
	stream_yuv_t *pYuv;//yuv�ܶ��е�buf
	pthread_mutex_t yuvMutex;//yuv���л�����
	int packetTotalNum;//�������ܵĳ���

	char *pYuvDataBuf;//yuv���ݵ�buf
	int freeBufNum;//���еİ���Ŀ
	stream_yuv_t freeHead;//���еİ�����ͷ
	stream_yuv_t *pFreeLast;//���еİ�����β

	int usedBufNum;//ʹ�õİ���Ŀ
	stream_yuv_t usedHead;//ʹ�õİ�����ͷ
	stream_yuv_t *pUsedLast;//ʹ�õİ�����β
}stream_yuv_queue_t;


typedef struct stream_alarm_t
{//
	unsigned char type;//
	unsigned char channelNo;
	unsigned char streamNo;
	unsigned char status;//0    1  
}stream_alarm_t;
/*  */
typedef struct stream_alarm_queue_t
{
	int writePos;
	pthread_mutex_t alarmMutex;
	pthread_cond_t alarmCond;
	stream_alarm_t alarmInfo[MAX_ALARM_QUEUE_NUM];
}stream_alarm_queue_t;



/* streamLib.c */
/* ����ʼ�� */
int streamLibInit();
/* ������ */
int streamLibUninit();





/* streamFrameQueue.c */
/* ֡��ʼ�� */
int streamInitFrameQueue(stream_frame_queue_t *pFrameQueue);
/* ֡���� */
void streamUninitFrameQueue(stream_frame_queue_t *pFrameQueue);
//////////////////////////////////////////////////////////////////////
/* Ϊ�˼���һ�ο����������������¼����������õ�ʱ��ע����*/
/* ��ס֡���� */
void streamFrameQueueLock(stream_frame_queue_t *pFrameQueue);
/* ����֡���� */
void steramFrameQueueUnlock(stream_frame_queue_t *pFrameQueue);
/* ��ȡһ֡�Ļ��� */
stream_frame_t * streamGetFrameQueueBuffer(stream_frame_queue_t *pFrameQueue, int frameLen);
/* ����һ֡��֡������   ��ָ�븳ֵ��*/
void streamInsertFrameToFrameQueue(stream_frame_queue_t *pFrameQueue, stream_frame_t *pFrame);
//////////////////////////////////////////////////////////////////////
#if 0
/* �������ݵ�֡������ */
int streamSendFrameToNetPool(stream_frame_queue_t *pFrameQueue, char *pStreamBuf, int streamBufLen);
#endif
/* �ȴ�һ֡��Ƶ */
int streamWaitFrame(stream_frame_queue_t *pFrameQueue);
/* ��ȡһ֡��Ƶ */
stream_frame_t * streamGetFrameFromNetPool(stream_frame_queue_t *pFrameQueue, int *pReadBegin, int *pReadEnd);
/* �ͷ�һ֡��Ƶ */
void streamFreeFrameBuffer(stream_frame_queue_t *pFrameQueue, stream_frame_t *pFrameInfo);
/* �ͷ�����֡��Ƶbuf */
void streamFreeAllFrameBuffer(stream_frame_queue_t *pFrameQueue);





/* streamPacketQueue.c */
/************************************************************
 * ��ʼ��������
 * pStreamInfo ĳ����Ƶ���ڶ�Ӧ������Ϣ
 ************************************************************/
int streamInitPacketQueue(stream_packet_queue_t *pPacketQueue,int protocol);
/*  */
void streamUninitPacketQueue(stream_packet_queue_t *pPacketQueue,int protocol);
/*********************************************************
 *��ȡ���еİ�buffer
 *********************************************************/
stream_packet_t * streamGetPacketWriteBuffer(stream_packet_queue_t *pPacketQueue);
/* ����buffer���뵽ʹ�ö����� */
int streamInsertQueue(stream_packet_queue_t *pPacketQueue, stream_packet_t *pStreamBuf);
/* ��ȡʹ�ö��еĵ�һ����buffer */
stream_packet_t * streamGetPacketUsedBuffer(stream_packet_queue_t *pPacketQueue);
/* ��ʹ�ù��İ�buffer���뵽δʹ�õ������� */
void streamFreeUsedBuffer(stream_packet_queue_t *pPacketQueue, stream_packet_t *pStreamBuf);
/* ��ȡһ֡��Ƶ */
int streamGetFrameBuf(stream_packet_queue_t *pPacketQueue, char *pStreamBuf, int streamBufLen);
/* ��ȡ�����е�ǰ���ĸ��� */
int streamPacketBufferNum(stream_packet_queue_t *pPacketQueue);
/* ������������е�����ˢ��֡������ */
void streamPushPacketBufferToFrameBuffer(stream_packet_queue_t *pPacketQueue);


stream_packet_t * private_protocol_streamGetPacketWriteBuffer(stream_packet_queue_t *pPacketQueue);

void private_protocol_streamFreeUsedBuffer(stream_packet_queue_t *pPacketQueue, stream_packet_t *pStreamBuf);

/* streamYuvQueue.c */
/* ��ʼ��Yuv���� */
int streamInitYuvQueue(stream_yuv_queue_t *pYuvQueue);
/* ����Yuv���� */
void streamUninitYuvQueue(stream_yuv_queue_t *pYuvQueue);
/*********************************************************
 * ��ȡ���е�buffer
 *********************************************************/
stream_yuv_t * streamGetYuvWriteBuffer(stream_yuv_queue_t *pYuvQueue);
/* ����buffer���뵽ʹ�ö����� */
int streamInsertYuvQueue(stream_yuv_queue_t *pYuvQueue, stream_yuv_t *pYuv);
/* ��ȡһ֡ used yuv buffer */
stream_yuv_t * streamGetYuvUsedBuffer(stream_yuv_queue_t *pYuvQueue);
/* ��ʹ�ù��İ�buffer���뵽δʹ�õ������� */
void streamFreeYuvUsedBuffer(stream_yuv_queue_t *pYuvQueue, stream_yuv_t *pYuv);
/* �ͷ�Yuv���е��ڴ� */
void streamFreeYuvBuffer(stream_yuv_queue_t *pYuvQueue);



/* streamAlarmQueue.c */
int streamInitAlarmQueue(stream_alarm_queue_t *pAlarmQueue);
void streamUninitAlarmQueue(stream_alarm_queue_t *pAlarmQueue);
int streamWaitAlarm(stream_alarm_queue_t *pAlarmQueue);
void streamInsertAlarmToAlarmQueue(stream_alarm_queue_t *pAlarmQueue, stream_alarm_t *pAlarm);
int streamGetAlarmFromNetPool(stream_alarm_queue_t *pAlarmQueue, int *pReadBegin, int *pReadEnd, stream_alarm_t *pAlarm);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif//__STREAM_LIB_H__

