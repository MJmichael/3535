#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <pthread.h>

//#include "appLib.h"
//#include "codeLib.h"
//#include "commonLib.h"
//#include "myThreadLib.h"
//#include "queueLib.h"


#if defined (__cplusplus)
extern "C" {
#endif


#define CPU_3520A			0
#define CPU_3531			1
#define CPU_3521			2
#define CPU_3520D                  3
#define CPU_3535			4

#ifdef  HI3531
#define MAX_DISPLAY_NUM 		32//��������Ŀ
#define MAX_SUPPORT_ESATA_NUM		2//���֧�ֵ�esata��Ŀ
#define MAX_SUPPORT_SATA_NUM		8//���֧�ֵ�sata��Ŀ
#elif HI3521
#define MAX_DISPLAY_NUM 		16//
#define MAX_SUPPORT_ESATA_NUM		2//esata
#define MAX_SUPPORT_SATA_NUM		2//sata
#elif HI3520D
#define MAX_DISPLAY_NUM 		8//
#define MAX_SUPPORT_ESATA_NUM		2//esata
#define MAX_SUPPORT_SATA_NUM		1//sata
#elif HI3535
#define MAX_DISPLAY_NUM 		25//
#define MAX_SUPPORT_ESATA_NUM		2//esata
#define MAX_SUPPORT_SATA_NUM		8//sata
#endif

#define MAX_SUPPORT_DISK_NUM		(MAX_SUPPORT_SATA_NUM + MAX_SUPPORT_ESATA_NUM)//���֧�ֵ�Ӳ����Ŀ

/* 3531 ����λ��ioΪ 3��3��
 * 	����λ��ioΪ 16��4��
*/
#define MAX_ALARM_IN			4//��󱨾��������
#define MAX_ALARM_OUT			4//��󱨾��������


#define MAX_SUPPORT_DEV_NUM		(0xFF)//���֧�ֵ��豸��Ŀ
#define MAX_SUPPORT_DEV_CHANNEL_NUM	(0x3F)//һ���豸����ͨ����Ŀ


#define NVR_VERSION			"v5.1.22"

#define FLAG_PAUSE                      0//��ͣ
#define FLAG_RUN                        1//����
#define FLAG_EXIT                       2//�˳�
#define FLAG_RESTART                    3//����
#define FLAG_STOP                       4//ֹͣ
#define FLAG_PATROL_NEXT_CHANNEL        5//��ѯ����һ��ͨ��
#define FLAG_WAIT                       6//�ȴ�


/*************************************** ȫ��ͨ����Ϣ ***************************************/
typedef struct dev_channel_stream_info_t
{
	pthread_mutex_t mutex;
	unsigned int usedFlag:1;//�Ƿ����ʹ��
	unsigned int usedNum:31;//��ʹ�õĴ���
	void *pPacketQueue;//������
	void *pFrameQueue;//֡����
	void *pYuvQueue;//yuv����
}dev_channel_stream_info_t;

typedef struct dev_channel_network_info_t
{
	pthread_mutex_t mutex;
	int runFlag;//�����߳����б��  0��δ����  1���߳��Ѿ�������
	void *pNetworkInfo;//������Ϣָ��
}dev_channel_network_info_t;

#if 0
typedef struct dev_channel_decode_info_t
{
	pthread_mutex_t mutex;
	int runFlag;//�����߳����б��  0��δ����  1���߳��Ѿ�������
	void *pDecodeInfo;//������Ϣָ��
}dev_channel_decode_info_t;
#endif

typedef struct dev_channel_record_info_t
{
	pthread_mutex_t recordMutex;
	int recordFlag;//����״̬
}dev_channel_record_info_t;

typedef struct dev_channel_info_t
{//�豸ͨ����Ϣ
	pthread_mutex_t devChannelMutex;
//	spinlock_t  devChannelSpinlock;
	int flag;//��� 
//	int enable;
	unsigned char channelNo;//�豸��
	unsigned char streamNo;//ͨ����
	dev_channel_stream_info_t streamInfo;//����Ϣ
	dev_channel_network_info_t networkInfo;//������Ϣ
//	dev_channel_decode_info_t decodeInfo;//������Ϣ
}dev_channel_info_t;


typedef struct dev_channel_t
{//�豸ͨ����Ϣ
	unsigned char channelNo;//�豸��
	unsigned char streamNo;//ͨ����
	int pos;//��ʾ�ķ���λ��
}dev_channel_t;


#if defined (__cplusplus)
}
#endif

#endif//__GLOBAL_H__

