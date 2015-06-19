
#ifndef __NETWORK_LIB_H__
#define __NETWORK_LIB_H__

#include "global.h"
#include "streamLib.h"
#include "rtspCLib.h"
#include "queueLib.h"

#define MAX_ADDR_LEN		64//ip��ַ�ĳ���

typedef enum network_invite_type_e
{
	NETWORK_INVITE_TYPE_DECODE = 0X01,	//����
	NETWORK_INVITE_TYPE_RECORD = 0x02,	//�洢
	NETWORK_INVITE_TYPE_PROXY = 0x04,	//����ת��

	NETWORK_INVITE_TYPE_ALL = 0xFF,		//����
}network_invite_type_e;

typedef enum network_msg_queue_e
{//������Ϣ��������
	NETWORK_MSG_QUEUE_TYPE_PASUE = 0,
	NETWORK_MSG_QUEUE_TYPE_RUN = 1,
	NETWORK_MSG_QUEUE_TYPE_EXIT = 2,
	NETWORK_MSG_QUEUE_TYPE_RESTART = 3,
	NETWORK_MSG_QUEUE_TYPE_STOP = 4,
	NETWORK_MSG_QUEUE_TYPE_NEXT = 5,
	NETWORK_MSG_QUEUE_TYPE_WAIT = 6,
}network_msg_queue_e;

typedef enum
{
  NETWORK_ONVIF = 0x02,
  NETWORK_RTSP = 0x03, 
  NETWORK_PROTOCOL =0x04,
                       
}video_protocol;



typedef struct network_info_t
{
	unsigned char enable;

	unsigned char channelNo;
	unsigned char streamNo;

	int protocol;//ͨѶЭ��  0��onvif 
	char onvifAddr[32];
	int onvifPort;

	char addr[32];//��ַ  ��ip������      ���protocol = ƽ̨�� ��õ�ַΪmdu�ĵ�ַ 
	int port;//�˿�                                 ���protocol = ƽ̨�� ��ö˿�Ϊmdu�Ķ˿�
	char userName[32];//�û���
	char userPwd[32];//����
	unsigned char unused[3];//����Э��  0��rtsp 1:ƽ̨ 
	unsigned char transport;//����Э�� 0��tcp  1��udp
//	unsigned short channel;//ͨ��
	char fileName[64];//������ļ���

	/* ƽ̨���е���Ϣ */
	char guid[32];
	char mduId[32];
	char domainId[32];

	char rtspsuburl[128];                                // rtspЭ���url
       char rtspmainurl[128];  
}network_info_t;

typedef struct network_dev_channel_info_t
{////������Ϣ
	unsigned char runFlag;// �����߳����б��  0��δ����  1���߳��Ѿ�������
	unsigned char isConnect;// 0  1

	unsigned char channelNo;//�豸��
	unsigned char streamNo;//ͨ����

	LINK_QUEUE_T msgQueue;//��Ϣ����

	/* ���� */
	network_info_t *pNetworkInfo;//������Ϣ
	rtsp_info_t *pRtspInfo;
	char *pRecvBuf;//���ݽ��ջ�����
	int recvBufLen;//�Ѿ����յ����ݳ���

	/* ��Ƶ�� */
//	pthread_mutex_t streamMutex;
	unsigned char usedFlag;//�Ƿ����ʹ��
	unsigned char useNumDecode;//�����ʹ�ô���
	unsigned char useNumRecord;//¼���ʹ�ô���
	unsigned char useNumProxy;//ת��ʹ�ô���
	stream_packet_queue_t *pPacketQueue;
	stream_frame_queue_t *pVideoFrameQueue;
}network_dev_channel_info_t;

/*  */
int networkSetStreamConnect(int channelNo, int streamNo, int value);
int networkCheckStreamExist(int channelNo, int streamNo);

/* ��ȡʵʱ��ʹ�ô��� */
int networkGetStreamUsedNum(int channelNo, int streamNo);

/* ����ʵʱ��ʹ�ô��� */
int networkAddStreamUsedNum(int channelNo, int streamNo, int type);

/* ����ʵʱ��ʹ�ô��� */
int networkDelStreamUsedNum(int channelNo, int streamNo, int type);

/* ��ȡʵʱ��֡���� */
void *networkGetStreamFrameQueue(int channelNo, int streamNo);

/* ����ʵʱ��֡���� */
void networkSetStreamFrameQueue(int channelNo, int streamNo, void *pFrameQueue);

/* �����豸ͨ����������Ƶ�� */
int networkStartStream(int channelNo, int streamNo, int type);

/* �����豸ͨ��������������Ƶ�� */
void networkRestartStream(int channelNo, int streamNo);

/* �����豸ͨ����ֹͣ��Ƶ�� */
int networkStopStream(int channelNo, int streamNo, int type);

/* �ȴ��豸ͨ��ָ����״̬ */
int networkWaitStreamFlag(int channelNo, int streamNo, int value);


/* ��ȡ�����߳����б�� */
int networkGetRunFlag(int channelNo, int streamNo);

/* ���������߳����б�� */
void networkSetRunFlag(int channelNo, int streamNo, int value);

/* ��ȡ��ǰ������Ϣ */
void networkGetNetworkInfo(int channelNo, int streamNo, network_info_t *pNetworkInfo);

/* ����������� */
int networkSetNetworkInfo(network_info_t *pNetworkInfo);

int setNetworkChannelRecvBitrate(unsigned int channelNo,unsigned int streamNo,unsigned int bitrate);

int getNetworkChannelRecvBitrate(unsigned int channelNo,unsigned int streamNo,void *pRecvData, int* recvDataLen ,int* exten);



int   SetIPCTimeAndDateWhenNTP(int channel);

/* ������ʼ�� */
int networkLibInit();

/* ��������� */
int networkLibDestroy();


#endif//__NETWORK_LIB_H__

