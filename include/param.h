
#ifndef __PARAM_H__
#define __PARAM_H__

#include "sdk_struct.h"

#define MAX_SUPPORT_CHANNEL_NUM         64


#define PROC_MSG_KEY		0x2013
#define PROC_MSG_MAIN_KEY	0x2014
#define PROC_MSG_QT_KEY		0x2015
#define PROC_MEM_KEY		0x2016
#define PROC_SEM_KEY		0x2017


#define MAX_SEARCH_FILE_NUM	1000//��ѯ¼���ļ�������


typedef struct proc_msg_t
{
	long Des;///< Where this message go. See /ref Sys_Msg_Def.h
	int type;//��Ϣ����  /< command to control system server.
	int subType;//��Ϣ������
	int src;///< Where this message from. See /ref Sys_Msg_Def.h
	int result;//����ֵ  0���ɹ�  ����ʧ��
	int shmid;///< Share memory which was used to communicate with system server.
	int length;///< Data length.
	int offset;///< Offset to begin of share memory.
}proc_msg_t;


/* ��Ϣ���� */
typedef enum proc_msg_type_e
{
	PROC_MSG_TYPE_PARAM_GET = 0,		//��ȡ����
	PROC_MSG_TYPE_PARAM_SET,		//���ò���
	PROC_MSG_TYPE_PARAM_INSERT,		//����
	PROC_MSG_TYPE_PARAM_MODIFY,		//�޸Ĳ���
	PROC_MSG_TYPE_PARAM_DEL,		//ɾ��
	PROC_MSG_TYPE_CONTROL,			//����
}proc_msg_type_e;
/* ��Ϣ������ */
typedef enum proc_msg_sub_type_param_e
{
	PROC_MSG_SUB_TYPE_PARAM_DEV_CHANNEL_INFO = 0,		//�豸ͨ����Ϣ
	PROC_MSG_SUB_TYPE_PARAM_VIEW_POS_INFO,			//��Ƶ����λ����Ϣ
	PROC_MSG_SUB_TYPE_PARAM_NETWORK_INFO,			//�������
	PROC_MSG_SUB_TYPE_PARAM_RECORD_INFO,			//¼�����
	PROC_MSG_SUB_TYPE_PARAM_CHANNEL_INFO,			//¼��ͨ����Ϣ
	PROC_MSG_SUB_TYPE_PARAM_TIME_INFO,			//ʱ����Ϣ
	PROC_MSG_SUB_TYPE_PARAM_VERSION_INFO,			//�汾��Ϣ
	PROC_MSG_SUB_TYPE_PARAM_MANAGE_INFO,			//������Ϣ
	PROC_MSG_SUB_TYPE_PARAM_USER_INFO,			//�û���Ϣ

	PROC_MSG_SUB_TYPE_PARAM_DISPLAY_NUM,			//��ȡ������
	
	PROC_MSG_SUB_TYPE_PARAM_LOG,                 // ��־
	PROC_MSG_SUB_TYPE_PARAM_DISK,                // Ӳ��
	PROC_MSG_SUB_TYPE_PARAM_IPC_VIDEO_INFO,     //��ȡ��Ƶ,����...
	PROC_MSG_SUB_TYPE_PARAM_IPC_ENCODE_INFO,    // ��ȡ���������֡��...
	PROC_MSG_SUB_TYPE_PARAM_DEV_ONE_CHANNEL_INFO,	
	PROC_MSG_SUB_TYPE_PARAM_GENERAL_INFO,
}proc_msg_sub_type_param_e;
typedef enum proc_msg_sub_type_control_e
{
	PROC_MSG_SUB_TYPE_CONTROL_SEARCH_RECORD = 0,		//��ѯ�豸¼��
	PROC_MSG_SUB_TYPE_CONTROL_PLAY_RECORD_DISPLAY_NUM,	//�ط��ܷ�����
	PROC_MSG_SUB_TYPE_CONTROL_SET_PLAY_RECORD,		//���ûطŵ�¼����Ŀ
	PROC_MSG_SUB_TYPE_CONTROL_PLAY_RECORD_TIME,		//���õ�ǰ�ط���ʼʱ��
	PROC_MSG_SUB_TYPE_CONTROL_PLAY_RECORD_SPEED,		//���ûط��ٶ�
	PROC_MSG_SUB_TYPE_CONTROL_PLAY_RECORD_STATUS,		//���ûط�״̬
	PROC_MSG_SUB_TYPE_CONTROL_PLAY_RECORD_CUR_POS,		//��ȡ��ǰ�طŵ�λ��
	PROC_MSG_SUB_TYPE_CONTROL_VIEW_DISPLAY_NUM,		//Ԥ��������
	
	PROC_MSG_SUB_TYPE_CONTROL_DISK,                // Ӳ��
	PROC_MSG_SUB_TYPE_CONTROL_IPC_VIDEO_INFO,      //��Ƶ����
	PROC_MSG_SUB_TYPE_CONTROL_IPC_ENCODE_INFO,     //�������
}proc_msg_sub_type_control_e;



/**********************************  ����  **********************************/
/* ���ݿ��е����ݶ�Ӧ�Ľṹ�� */
typedef struct param_dev_channel_info_t
{//�豸ͨ����Ϣ
//	char name[32];//�豸����
	int enable;//�Ƿ�ʹ��
	int viewPos;//��ʾλ��
	int channelNo;//�豸��
	int streamNo;//ͨ����
	char addr[64];//��ַ
	int port;//�˿�
	char userName[32];//�û���
	char userPwd[32];//�û�����
	int protocol;//Э������
}param_dev_channel_info_t;

typedef struct param_view_pos_info_t
{//��Ƶ������ʾλ����Ϣ
	int pos;//��ʾλ��
	int channelNo;//�豸��
	int streamNo;//ͨ����
}param_view_pos_info_t;

typedef struct param_disk_info_t
{//Ӳ����Ϣ
	unsigned char recordFlag;//�Ƿ�����¼��
	unsigned char mountFlag;//�Ƿ��Ѿ�����
	unsigned char formatFlag;//�Ƿ��Ѿ���ʽ��
	unsigned char unused;

	unsigned char uuid[16];
	char devName[16];//�豸��
	char volumeName[16];//Ӳ�̾���
	char mountPath[16];//����·��
}param_disk_info_t;

typedef struct param_network_info_t
{//�������
	int dhcpEnable;
	char ip[16];//
	char netmask[16];
	char gw[16];
	char mac[32];
	char dns[16];
	char dns2[16];
}param_network_info_t;

typedef struct param_record_channel_t
{
	int channelNo;//ͨ����
	int streamType;//������  0��������  1��������
	int time[4];//ʱ��Σ� ÿ��bit��ʾһ��ʱ�Σ�û���СʱΪһ��ʱ��Ρ�
}param_record_channel_t;
typedef struct param_record_info_t
{//¼�����
	int enable;
	int recordMode;
	param_record_channel_t recordChannel[MAX_SUPPORT_CHANNEL_NUM];//ÿ��ͨ����������
}param_record_info_t;

typedef struct time_info_t
{
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
}time_info_t;
typedef struct sntp_info_t
{
	int enable;
	char serverAddr[64];
	int timeZone;
}sntp_info_t;
typedef struct param_time_info_t
{//ʱ�����
	time_info_t curTime;//��ǰʱ��
	sntp_info_t sntp;
}param_time_info_t;

typedef struct param_version_info_t
{//�汾��Ϣ
	char version[64];
	char date[32];
}param_version_info_t;

typedef struct param_system_manage_t
{//ϵͳ����
	int timerRebootEnable;//ʹ�ܶ�ʱ����
	int week;//����
	int hour;
	int min;
	int sec;
//	int time;//ʱ��  ʱ���֣���
}param_system_manage_t;

typedef struct param_display_num_t
{//������
	int num;
}param_display_num_t;

typedef struct param_user_manage_t
{//�û�����
	char userName[32];
	char userPwd[32];
	unsigned int power;//�û�Ȩ��  ÿ��bit��ʾһ��Ȩ��  bit0:��Ƶ���  bit1:��������  bit2:�ط�
}param_user_manage_t;

typedef struct
{
	// Ӳ�̺Ŷ�Ӧ��ۺţ�1 ... N
	unsigned int id;             // Ӳ�̺� 1~99�ڲ�, 100 ~ �ⲿ
	unsigned int status;         // ����/�쳣
	unsigned int type;           // ��ʹ��/��д
	unsigned int capacity;       // ����
}param_hdd_info_t;

//���ڸ�ʽ������
typedef struct {
	unsigned int id;             // Ӳ�̺� 1 - 1000
}control_hdd_format_t;

//������������(Read/Write)
typedef struct{
	unsigned int id;            // Ӳ�̺�  1 - 1000  
	unsigned int type;          
}param_hdd_type_t;

typedef struct para_video_info_t
{//ipc��Ƶ��Ϣ
	int channelNo;  //�豸ͨ����
	int Brightness; //����
	int Contrast;   //�Աȶ�
	int Statuation; //���Ͷ�
	int Sharpness;  //���
}para_video_info_t;

typedef struct param_encodSet_info_t
{
	int channelNo;  //�豸ͨ����
	int stream;     //����  0:������  1��������
	int resolution; //�ֱ���
	int frame;      //֡��
	int bit_rate;   //������
	int ratecontrol;//���ʿ���  0 ��������  1��������

}param_encodSet_info_t;

typedef struct param_general_info_t
{//ͨ����Ϣ
	int nvrNo;  //nvr���
	int displayResolution;  //��ʾ�ֱ���
	int autoQuitTime;   //�Զ��Ƴ�ʱ��
}param_general_info_t;



/**********************************  ��ѯ  **********************************/
typedef struct control_search_record_t
{//��ѯ�豸¼��
	int channelNo;//�豸��
	int streamNo;//ͨ����
	int recordType;//¼������  0xFF������
	int startTime;//��ʼʱ��
	int endTime;//����ʱ��
}control_search_record_t;

#if 0
typedef struct record_search_file_t
{//¼���ļ���Ϣ
	unsigned short diskNo;//Ӳ�̺�
	unsigned short recordNo;// ¼���ļ���%04X����Ϊ¼���ļ�����
	unsigned short fileType;//�ļ�����  bit0����ʱ¼�� bit1���澯¼�� bit2���ֶ�¼��
	unsigned char unused[2];//
	unsigned int startTime;//¼����ʼʱ�䣨�룩
	unsigned int endTime;//¼�����ʱ�䣨�룩
	unsigned int startAddr;//���ļ���һ֡��Ӧ��¼���ļ���I֡�����ĵ�ַ
	unsigned int endAddr;//���ļ����һ֡��Ӧ��¼���ļ���I֡�����ĵ�ַ
	unsigned int dataStartAddr;//¼���ļ���ʼ��ַ
	unsigned int dataEndAddr;//¼�������ļ�������ַ
}record_search_file_t;
#endif

typedef struct control_search_log_t
{//��ѯ��־
	time_info_t logstartTime;
	time_info_t logendTime;
	int logType;//��־����  0��������־  1��ϵͳ��־  2��������־  3��������־  4��������־
}control_search_log_t;
typedef struct log_search_into_t
{//��־��Ϣ
	int logType;
	time_info_t logTime;
	char logContent[64];//��־����
	int  user;        //�û�����
}log_search_into_t;



/**********************************  ����  **********************************/
typedef struct control_play_record_t
{//�ط���Ϣ
	int status;//״̬  0������  1��ֹͣ���� 2��ֹͣ����
	int displayChannel;//ͨ�����ں�
	int speed;//�����ٶ�
	int fileNum;//���ŵ��ļ�����
	record_search_file_t searchFile[MAX_SEARCH_FILE_NUM];
	int startTime;//����ʱ��
	int startFileNum;//�����ĸ��ļ�
	int offset;//���Ÿ��ļ���ƫ��λ��
}control_play_record_t;

typedef struct control_play_time_t
{//�طž���¼��
	int displayChannel;
	int startTime;
	int startFileNum;//�����ĸ��ļ�
	int offset;//���Ÿ��ļ���ƫ��λ��
}control_play_time_t;

typedef struct control_play_speed_t
{//�ط��ٶ�
	int speed;
}control_play_speed_t;

typedef struct control_play_status_t
{//�ط�״̬
	int displayChannel;
	int status;//0������  1��ֹͣ  2����ͣ
}control_play_status_t;

typedef struct control_play_cur_pos_t
{//��ǰ�ط�λ��
	unsigned int time;//�����ƫ��ʱ��
}control_play_cur_pos_t;

typedef struct control_play_record_num_t
{//�ط�ͨ����Ŀ
	int num;
}control_play_record_num_t;

typedef struct control_view_display_num_t
{//Ԥ��ͨ����Ŀ
	int num;//������
	int viewPos;//��ʼ�����ı�� 0~36
}control_view_display_num_t;



#endif//__PARAM_H__

