


#ifdef __cplusplus
extern "C" {
#endif


#ifndef _HEROSPEED_P2P_APP_MSG_DEF_H_
#define _HEROSPEED_P2P_APP_MSG_DEF_H_

#include "P2PSDK.h"



#define  MAX_SERVERIP_LENGTH   32
#define  MAX_ID_LENGTH   13    //id?????13
#define  MAX_USERNAME_LENGTH  64
#define  MAX_PASSWORD_LENGTH  64

typedef enum
{
    P2P_PLAY_REAL_STREAM = 0,
    P2P_STOP_REAL_STREAM = 1,
    P2P_PLAY_RELAY_STREAM = 2 ,
    P2P_STOP_RELAY_STREAM = 3,
    P2P_CLIENT_DISCONNECT = 4,
    P2P_RELAYCLIENT_DISCONNECT = 5,
    P2P_START_PTZ_CONTROL = 6,
    P2P_GET_DEVICE_STREAMINFO = 7,
    P2P_GET_DEVICE_STREAMINFO_RES = 8,
   // any else .... 
}P2pCmdType;
typedef enum
{
   Msg_Data,  // ��Ϣ���� 
   RealStream_Data, // ʵʱ������
   RecordStream_Data, // ¼��������
   // any else .... 
}StreamType;

typedef struct  m_mediainfo
{
    int    run;
    int    msessionid;	
    short streamType;  // 1:������ 2:������
    short channelNo;  // ͨ����(��1��ʼ)	
}P2pMediainfo,*MP2pMediainfo;


typedef struct
{
    unsigned char ucUsername[16];
    unsigned char ucPassWord[16];
    unsigned char ucSerialNum[16];
}USER_INFO;




int p2pTHRStart();



/*************************/
typedef int (*HandleCommandCallback)(P2pCmdType cmd,char* indata,int inlen,char* outdata,int outlen);  


int   P2p_RegisterCommandHandle(HandleCommandCallback handlecommand);

/*��P2P������ע��         serverIp:P2P��������ַ myId:�豸ID      username:�豸�û���  password:�豸����*/
int   P2P_InitService(char* serverIp, char* myId,const char*username,const char* password); 
/*��P2P������ע������*/
int P2P_StopService();

/************************
ԭ��:typedef void (*HandleStatusCallback)(int status)
˵��:�ϱ�P2Pע��״̬
����:status:1/�ɹ�   0/ʧ�� 
************************/
typedef void (*HandleStatusCallback)(int status);

/************************
ԭ��:int   P2p_RegisterStatusHandle(HandleStatusCallback   Pstatushandle)
˵��:ע��P2P״̬�ص�����
����:Pstatushandle:�ص�������ַ
���: 0/�ɹ�   -1/ʧ��
************************/
int   P2p_RegisterStatusHandle(HandleStatusCallback   Pstatushandle);



/*��ȡp2p����״̬*/
int GetP2PConnectStatus();

/*��ʼ����ý��������*/
int P2pStartSendData(int sessionid,char* data, int len,StreamType mstreamtype);
/*ֹͣý��������*/
int P2pStopService(int sessionid);

/*��ʼ����ý��������*/
int P2pStartSendRelayData(int sessionid,char* data, int len,StreamType mstreamtype);
/*ֹͣý��������*/
int P2pStopRelayService(int sessionid);


typedef void *(*sthread)(void*);

#ifdef __cplusplus
}
#endif

#endif










