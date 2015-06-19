#ifndef __RECORD_LIB_H__
#define __RECORD_LIB_H__


#include <pthread.h>
#include "mylist.h"
#include "queueLib.h"
#include "streamLib.h"
#include "param.h"
#include "global.h"

#define DISK_PATH "/disk"

#define MAX_FILE_SIZE			(1024*1024*1024)//ÿ��¼���ļ��Ĵ�С
#ifdef HI3535
#define MMAP_RECORD_DATA_SIZE		(2560*1024)//¼���ļ�ӳ��¼�������С
#else
#define MMAP_RECORD_DATA_SIZE		(1536*1024)//¼���ļ�ӳ��¼�������С
#endif
#define MMAP_RECORD_I_FRAME_SIZE	(16*1024)//¼���ļ�ӳ��I֡���������С


#define INDEX_MAIN_NO			0//�������ļ����
#define INDEX_BAK_NO			1//���������ļ����
#define RECORD_START_NO			2//¼���ļ���ʼ���

/* ¼���ļ����� */
#define RECORD_FILE_TYPE_NORMAL		0X01//��ͨ¼��
#define RECORD_FILE_TYPE_ALARM		0X02//�澯¼��
#define RECORD_FILE_TYPE_HAND		0X04//�ֶ�¼��

/*  */
#define RECORD_STATUS_NOT_INIT		1//δ��ʼ��
#define RECORD_STATUS_RECORD		2//����¼��
#define RECORD_STATUS_SWITCH		3//�л�
#define RECORD_STATUS_SWITCH_ITEM	4//�л�
#define RECORD_STATUS_SWITCH_RECORD_NO	5//�л�¼���ļ�
#define RECORD_STATUS_SWITCH_DISK_NO	6//�л�Ӳ��
#define RECORD_STATUS_RESTART		7//��������
#define RECORD_STATUS_STOP		8//ֹͣ¼��
#define RECORD_STATUS_WRITE_ERROR	9//¼��д�����
#define RECORD_STATUS_PAUSE                 10//¼����ͣ

/* Ӳ��״̬ */
#define DISK_STATUS_NOT_INIT		0//Ӳ��δ��ʼ��
#define DISK_STATUS_NORMAL		1//����
#define DISK_STATUS_USING		2//����ʹ��
#define DISK_STATUS_ERROR		3//Ӳ����
#define DISK_STATUS_STOP_USED		4//ֹͣʹ��

/* ¼����� */
typedef enum __record_update_flag_e__
{
	RECORD_UPDATE_FLAG_PARAM = 0,		//¼������仯
	RECORD_UPDATE_FLAG_DISK_STATUS,		//Ӳ�̷����仯
	MOTION_UPDATE_FLAG_PARAM,			//�ƶ������������仯
}record_update_flag_e;

/* ��Ϣ��������Ϣ���� */
typedef enum __msg_queue_type_e__
{
	RECORD_MSG_QUEUE_TYPE_NORMAL = 0,		//��������
	RECORD_MSG_QUEUE_TYPE_START_RECORD,		//��ʼ¼��
	RECORD_MSG_QUEUE_TYPE_STOP_RECORD,		//ֹͣ¼��
	RECORD_MSG_QUEUE_TYPE_STOP_ALL_RECORD,		//ֹͣ����¼��
	RECORD_MSG_QUEUE_TYPE_DEL,			//ɾ��¼���ļ�
	RECORD_MSG_QUEUE_TYPE_GET_STATUS,		//��ȡ״̬
	RECORD_MSG_QUEUE_TYPE_SWITCH_DISK_NO,		//�л�Ӳ��
	RECORD_MSG_QUEUE_TYPE_UPDATE_RECORD_NUM_ADD,	//����¼���ļ���Ŀ  ʹ�õ���Ŀ +1
	RECORD_MSG_QUEUE_TYPE_UPDATE_RECORD_NUM_DEL,	//����¼���ļ���Ŀ  ʹ�õ���Ŀ -1
	RECORD_MSG_QUEUE_TYPE_START_USED_DISKNO,	//��ʼʹ��ĳ��Ӳ��
	RECORD_MSG_QUEUE_TYPE_STOP_USED_DISKNO,		//ֹͣʹ��ĳ��Ӳ��
}msg_queue_type_e;

typedef unsigned int RECORD_HANDLE;//¼���ļ����
typedef unsigned int INDEX_HANDLE;//�����ļ����
typedef unsigned int INDEX_FILE_HANDLE;//�����ļ����



typedef enum __record_error_e__
{//¼���Ĵ����
	/* ¼���ļ� */
	RECORD_LIB_ERROR_RECORD = -200,				//¼�����

	/* �����ļ� */
	RECORD_LIB_ERROR_INDEX = -100,				//��������

	RECORD_LIB_ERROR_INDEX_HANDLE_NULL,			//�����ļ����Ϊ��
	RECORD_LIB_ERROR_INDEX_FD_ERROR,			//�����ļ�����������

	RECORD_LIB_ERROR_INDEX_FILE_MALLOC,			//
	RECORD_LIB_ERROR_INDEX_FILE_HANDLE_NULL,		//�����ļ����ļ�����������Ϊ��
	RECORD_LIB_ERROR_INDEX_FILE_MMAP_NULL,			//�����ļ����ļ���������ӳ��Ϊ��
	RECORD_LIB_ERROR_INDEX_FILE_ITEM_NO_IS_TOO_BIG,		//�����ļ����ļ�������Ŀ��ų�����Χ
	RECORD_LIB_ERROR_INDEX_FILE_ITEM_STATUS_NOT_MATCH,	//�����ļ����ļ�������Ŀ״̬��ƥ��

	RECORD_LIB_ERROR_ERROR = -1,
	RECORD_LIB_ERROR_SUCCESS = 0,
}record_error_e;


typedef struct __record_channel_info_t__
{
	int status;//״̬  0��δ��ʼ��  1����������  2��ֹͣ¼��  
	int diskNo;//Ӳ�̱�� ��0��ʼ
	INDEX_FILE_HANDLE indexFileHandle;
	unsigned short channelNo;
	unsigned short streamNo;
	int recordType;//¼������
	unsigned int recordTime;//¼��ʱ�� ��λ�� 
	int sendRecordAlarm;//����¼��״̬������  0��δ����  1���ѷ���

	int recordNo;//¼���ļ����
	int recordUsedNum;//¼���ļ�ʹ�ô���
	RECORD_HANDLE recordHandle;

	int indexNo;
	int itemNo;

	int startStream;//��ʼ���յ���Ƶ��
	unsigned int startTime;//��ʼ���յ���Ƶ��
	unsigned int endTime;//���һ�ν��յ���Ƶ��
	int waitIFrame;//�ȴ�I֡���  0:��Ҫ�ȴ�I֡  1���Ѿ��ȵ�I֡
	int frameNo;//֡���
	int iFrameCount;//I֡������
	stream_frame_queue_t *pFrameQueue;//֡����
	int readBegin;
	int readEnd;
	int preReadBegin;
	int preReadEnd;
	unsigned int iFrameWriteAddr;
	unsigned int dataWriteAddr;

	struct kernel_list_head list;
	//struct list_head list;
}record_channel_info_t;

typedef struct record_info_t
{//Ӳ����Ϣ
	pthread_t recordThreadId;//�߳�Id
	pthread_mutex_t recordMutex;//��

	int runFlag;//���б��

//	unsigned char diskUuid[16];//Ӳ��uuid
//	char mountPath[16];//����·��
	int mountFlag;//�Ƿ����
	int recordFlag;//�Ƿ�����¼��  0��������  1������
	int diskNo;//Ӳ�̱��
	int diskStatus;//Ӳ�̹���״̬  1��δ��ʼ��  2������ʹ��  3��Ӳ����
	int devChannelNum;//��Ӳ�̱����ٸ��豸ͨ����ʹ��
	unsigned int writeTotalByte;//д������ֽ���
	unsigned int writeTotalTime;//д����ܺ�ʱʱ�� ���룩
	unsigned int writeSpeed;//д������ ��ÿ����д�����������

	int usedRecordNoNum;//�Ѿ�ʹ�õ�¼���ļ���Ŀ
	int freeRecordNoNum;//���е�¼���ļ���Ŀ
	int usingRecordNoNum;//����ʹ�õ�¼���ļ���Ŀ
	int oldRecordNo;//���ϵ�¼���ļ�
	int oldRecordNoUsedNum;//ʹ�ô���

	/* һ��Ӳ�̶�Ӧһ�������ļ���һ�����������ļ������Ը���ͨ�����Թ��ã�ͳһ����Ӳ����Ϣ�ṹ���� */
	INDEX_HANDLE indexHandle;//�������
	INDEX_HANDLE indexHandleBak;//�����������
}record_info_t;

typedef struct __record_manage_channel_t__
{//¼������߳���Ϣ
	int diskNo;
	int channelNo;
	int streamNo;//
	int recordType;//¼������
	int recordStartTime;//¼���ļ���ʼʱ�� ��
	int recordTime;//¼��ʱ�� ��

	struct kernel_list_head list;
	//struct list_head list;
}record_manage_channel_t;

/*
 * ��ʼ��Ӳ��
 * ��ȡ��ǰÿ��ͨ������д���λ��
 * */
record_info_t * recordLibInit();

/*
 * ¼�������
 * */
void recordLibdestroy();

/*
 * ���ø���¼����ر��
 * type:	0��¼���߼� 1��Ӳ�̿���
 * no:		���
 * value:	ֵ
 */
void recordSetUpdateFlag(int type, int no, int value);

/*
 * ����һ���豸ͨ��¼��
 * channelNo:	�豸��
 * streamNo��	ͨ����
 * recordType:	¼������
 * recordTime:	¼��ʱ�� ��λ��
 * */
void recordStartDevChannel(unsigned char channelNo, unsigned char streamNo, unsigned char recordType, int recordTime);

/*
 * ֹͣһ���豸ͨ��¼��
 * channelNo:	�豸��
 * streamNo��	ͨ����
 * */
void recordStopDevChannel(unsigned char channelNo, unsigned char streamNo);

/* ֹͣ�����豸ͨ��¼�� */
void recordStopAllDevChannel();

/* ��ʼʹ��ĳ��Ӳ�� */
void recordStartUsedDiskNo(int diskNo);

/* ֹͣʹ��ĳ��Ӳ�� */
void recordStopUsedDiskNo(int diskNo);

/* ��ȡӲ�̵Ŀ������� */
int recordGetFreePercent(int diskNo);

/* ��ȡӲ��ʹ��״̬ */
int recordGetDiskUsedStatus(int diskNo);

/**/
int beepGetStatus(unsigned char channel);

/**/
int beepGetTime(unsigned char channel);


/*
 * �����豸ͨ��¼���ļ�
 * channelNo:		�豸��
 * streamNo��		ͨ����
 * recordType:		¼������
 * recordTime:		¼��ʱ�� ��λ��
 * pRecordSearchFile:	��ѯ�����ļ�
 * */
int recordFindDevChannelRecord(unsigned char channelNo, unsigned char streamNo, unsigned char recordType, unsigned int recordStartTime, unsigned int recordEndTime, record_search_file_t *pRecordSearchFile);




#endif//__RECORD_LIB_H__

