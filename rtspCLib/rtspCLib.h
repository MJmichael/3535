#ifndef __RTSP_C_LIB_H__
#define __RTSP_C_LIB_H__

#include "global.h"
#include "streamLib.h"


#define FRAME_SOURCE_IPC        0//��֡�Ǵ�IPC��õ�
#define FRAME_SOURCE_PLAT       1//��֡�Ǵ�ƽ̨��õ�

typedef enum
{               
	EN_RTP_PT_ULAW             = 0,        /* mu-law */
	EN_RTP_PT_GSM              = 3,        /* GSM */
	EN_RTP_PT_G723             = 4,        /* G.723 */
	EN_RTP_PT_ALAW             = 8,        /* a-law */
	EN_RTP_PT_G722             = 9,        /* G.722 */
	EN_RTP_PT_S16BE_STEREO     = 10,       /* linear 16, 44.1khz, 2 channel */
	EN_RTP_PT_S16BE_MONO       = 11,       /* linear 16, 44.1khz, 1 channel */
	EN_RTP_PT_MPEGAUDIO        = 14,       /* mpeg audio */
	EN_RTP_PT_JPEG             = 26,       /* jpeg */
	EN_RTP_PT_MPEG_TS          = 33,        /* mpeg ts */
	EN_RTP_PT_H264             = 96,       /* hisilicon define as h.264 */
	EN_RTP_PT_G726             = 97,       /* hisilicon define as G.726 */
	EN_RTP_PT_ADPCM            = 98,       /* hisilicon define as ADPCM */
	EN_RTP_PT_MPEG4                = 99,       /*xsf define as Mpeg4*/
	EN_RTP_PT_INVALID          = 127
}EN_RTP_PT;


#define RTP_HEAD_LEN 12//rtpͷ�ĳ���



#define RTSP_DATA_BUFER_SIZE       (4*1024)
#define RTSP_DATA_MAIN_BUFER_SIZE  (8*1024)  /*for rtsp main recv buffer size*/
#define RTSP_DATA_SUB_BUFER_SIZE   (4*1024)  /*for rtsp sub recv buffer size*/
#define RTSP_MAX_SESSION_LEN       64
#define RTSP_MAX_TRACKID_LEN       256 //256
#define RTSP_MAX_URL_LEN           1024   //1024
#define RTSP_MAX_ATH_LEN           256   //1024
#define RTSP_MAX_REALM_LEN         128   //256
#define RTSP_TICK_BASE             1                  /* ��ʱ����Ϣ�Ļ�����λ��1��tick */
#define RTSP_TICK_VALUE            10                 /* ϵͳ��10msΪ������λ */
#define NULL_DWORD                 0xffffffff
#define NULL_WORD                  0xffff
#define NULL_BYTE                  0xff
#define RTSP_DEFAULT_PORT          554
#define RTP_VEDIO_PORT             1600
#define RTP_AUDIO_PORT             1800
#define RTSP_CLIENT_LOC_PORT       16000
#define USER_AGENT "RTSP 1.0"
#define G711_A                        0x01  /* 64kbps G.711 A, see RFC3551.txt  4.5.14 PCMA */
#define G711_U                        0x02  /* 64kbps G.711 U, see RFC3551.txt  4.5.14 PCMU */
#define ADPCM_DVI4                    0x03  /* 32kbps ADPCM(DVI4) for RTP; see DVI4 diiffers in three 
                                               respects from the IMA ADPCM at RFC3551.txt 4.5.1 DVI4 */
#define G726_16KBPS                   0x04  /* 16kbps G.726, see RFC3551.txt  4.5.4 G726-16 */
#define G726_24KBPS                   0x05  /* 24kbps G.726, see RFC3551.txt  4.5.4 G726-24 */
#define G726_32KBPS                   0x06  /* 32kbps G.726, see RFC3551.txt  4.5.4 G726-32 */
#define G726_40KBPS                   0x07  /* 40kbps G.726, see RFC3551.txt  4.5.4 G726-40 */
#define RTSP_VER                "RTSP/1.0"

#define         GS_SEND                 (1)
#define         GS_SET_SEND             (0)

#define RTP_NAL_FU_A               28
#define RTP_NAL_FU_B               29

/* RTP���*/
typedef struct
{
	unsigned int uiTimestamp;
	unsigned int uiNetTimestamp;
	unsigned char ucPayloadType;
	unsigned char unused[3];
	unsigned short usmarker;
	unsigned short seqNo;

}ST_RTP_HEAD;


/* RTSP���ƿ�״̬ */
typedef enum
{
	EN_RTSP_STATUS_CONNET,
	EN_RTSP_STATUS_OPTION,
	EN_RTSP_STATUS_DESCRIBE,
	EN_RTSP_STATUS_SETUPONE,
	EN_RTSP_STATUS_SETUPTWO,
	EN_RTSP_STATUS_PLAY,
	EN_RTSP_STATUS_AVILABLE,
	EN_RTSP_STATUS_TEARDOWN,

	EN_RTSP_STATUS_BUTT
}EN_RTSP_CB_STATUS;

/* HTTP��Ϣ����״̬���� */
typedef enum
{
	EN_RTSP_RECV_CONTINUE,
	EN_RTSP_RECV_FINISHED,
	EN_RTSP_RECV_ERROR,

	EN_RTSP_RECV_TYPE_NULL
}EN_RTSP_RECV_TYPE;

/* RTSP���� */
typedef struct
{
	char *accept;
	char *authorization;
	char *range;
	char *session;
	char *transport;
	int scale;
	int speed;
}ST_RTSP_COMMAND_T;

enum
{
	TRANSPORT_UDP = 0,
	TRANSPORT_TCP = 1,
};

enum
{
	PROTOCOL_RTSP = 0,
	PROTOCOL_PLAT = 1,
};


/* RTSP���ƿ� */
typedef struct
{
	unsigned char ucCBStatus;
	unsigned char unused[3];
	unsigned long ulCBTimer;                    /* ״̬��ʱ�� */
	int iRTSPTcpSock;                               /* RTSP client�׽��� */
	int iRTPUdpVedioSock;                        /* Vedio�׽��� */
	int iRTPUdpAudioSock;                        /* Audio�׽��� */
	unsigned short usRTPVideoPort;
	unsigned short usRTPAudioPort;
	unsigned short usRTSPPort;
	unsigned short ucRetryNum;                /* ���Դ��� */
	int iCSeq;                                              /* RTSP����-��Ӧ�Ե����к� */

	/* http �������ݽṹ */
	char acRtspData[RTSP_DATA_BUFER_SIZE];  /* HTTP���ݻ�����, ����httpͷ */
	unsigned int usRtspDataLen;          /* Rtsp���ݻ��������� */
	//char IPNC_acRtspData[RTSP_DATA_BUFER_SIZE];
}rtsp_control_block_t;

/* �豸���ݽṹ */
typedef struct
{
	int id; /* ��¼�ڼ����豸 */
	char user[32];
	char password[32];
	char hostAddress[32];
	unsigned short rtspPort;
	char fileName[64];
	unsigned char protocol;

	int nRtspSeq;

	unsigned char ucauthflag;
	unsigned char unused[3];

	char realm[RTSP_MAX_REALM_LEN];
	char nonce[RTSP_MAX_REALM_LEN];
	unsigned char trackID1;
	unsigned char trackID2;
	unsigned char audioCoder;
	unsigned char videoCoder;
	char actrackID1[RTSP_MAX_TRACKID_LEN];
	char actrackID2[RTSP_MAX_TRACKID_LEN];
	char sessionID[RTSP_MAX_SESSION_LEN];

	unsigned short serverVideoPort;
	unsigned short serverAudioPort;

	unsigned long  ulLocationIP;
	unsigned int usLocationPort;

	char acAuthorization[RTSP_MAX_ATH_LEN];        /* Authorization */
	char acLocationURL[RTSP_MAX_URL_LEN];          /* Location URL��ַ */
	char acContenBase[RTSP_MAX_ATH_LEN];
}rtsp_igd_desc_t;

/* RTSPȫ�ֱ��� */
typedef struct
{
	unsigned long ulTicks;
	int nVideoWidth;
	int nVideoHeight;
	int nFrameRate;
	int nBitRate;
	unsigned char ucAudioMode;
	unsigned char unused[3];
}rtsp_global_t;

/* RTP���*/
typedef struct
{
	unsigned char ucsendflag;
	unsigned char ucPayloadType;
	unsigned short seqNo;
	unsigned int uiTimestamp;
	unsigned int uiNetTimestamp;
	int iRecvDataLen;
    int channel;
}rtsp_rtp_parse_t;

typedef struct packet_info_t
{//����Ϣ
	unsigned short seq;//
	char channel;//
	char unused[1];//
	unsigned int pts;
	unsigned short offset;//
	unsigned short len;//
}packet_info_t;
#define MAX_PACKET_NUM		1000//������Ŀ
typedef struct rtsp_info_t
{//rtsp��Ϣ
	unsigned char runFlag;//���б��  0��ֹͣ  1����ʼ
	rtsp_control_block_t *pstRTSPCB;
	rtsp_igd_desc_t *pstRTSPDesc;
	rtsp_global_t *pstRTSPGlobal;
	rtsp_rtp_parse_t *pstRtpParse;
	unsigned int statusTimeout[EN_RTSP_STATUS_BUTT];//rtsp��������״̬�ĳ�ʱʱ��

#if 0
	char *pRecvBuf;//�������ݻ���
	int bufStartPos;//��ʼλ��
	int bufEndPos;//����λ��
	int curRecvPos;//��ǰ�������ݵĳ���
	int curParsePos;//��������������λ��
	int frameLen;//֡����

	packet_info_t packetInfo[MAX_PACKET_NUM];
	int startPacketNo;//����ʼλ��
	int endPacketNo;//������λ��
	int curPacketNo;//��ǰ�����
#endif
}rtsp_info_t;


typedef struct rtp_para
{
    char magicnum;
    char channel;
    unsigned short size;
}rtp_para;



/* rtsp��ʼ�� */
rtsp_info_t * rtspInit();
/* rtsp���� */
void rtspUninit(rtsp_info_t *pRtspInfo);
/* rtsp������Ƶ */
int rtspInviteStream(rtsp_info_t *pRtspInfo, int channelNo, int streamNo, char *pAddr, int port, char *pUserName, char *pPwd, int protocol, char *pFileName);
/****************************************************
 * ������Ƶ��
 *
 * pRtspInfo:		rtsp��������Ϣ
 * pPacketBuf:		��ǰ���յ����ݰ�buf
 * packetBufLen:	�����ܳ���
 *
 * pChannel:		��ǰ���ݰ������ݵ�ͨ��  0����Ƶ  2����Ƶ
 * pRecvLen:		��ǰ���ݵĳ���
 * pOffset:		rtpͷ��Ϣ�ĳ���
 * pVideoFrameLen:	֡����
 ****************************************************/
int rtspRecvStream(rtsp_info_t *pRtspInfo, stream_packet_queue_t * pPacketQueue, stream_packet_t *pPacket, int packetBufLen, stream_packet_head_t *pPacketHead, int *pVideoFrameLen);
/* rtsp ��֡ */
int rtspPacketToFrameQueue(rtsp_info_t *pRtspInfo, stream_packet_queue_t *pPacketQueue, stream_packet_t *pPacket, stream_frame_queue_t *pAudioFrameQueue, stream_frame_queue_t *pVideoFrameQueue,
		int forceRestartNum, int packetFlg, int *pVideoFrameLen, int *pVideoFrameNo, int *pAudioFrameNo);
/*  �ر��� */
void rtspCloseStream(rtsp_info_t *pRtspInfo);

int rtspParseDetailURL(const char * url, char* address,int* portNum,char * filename);



int RtspParseRtpPacketInfo(rtsp_info_t *pRtspInfo, stream_packet_queue_t * pPacketBuff,stream_packet_head_t *pPacketHead,stream_frame_queue_t *pAudioFrameQueue,stream_frame_queue_t *pVideoFrameQueue,
                           int *pVideoFrameNo, int *pAudioFrameNo,int forceRestartNum,int channelNo,int streamNo,int* countStreamFrameRate);


int rtspPacketBuffToFrameQueue(rtsp_info_t *pRtspInfo, unsigned char *pPacketBuff, stream_packet_head_t *pPacketHead, stream_frame_queue_t *pAudioFrameQueue, stream_frame_queue_t *pVideoFrameQueue,
                           int *pVideoFrameNo, int *pAudioFrameNo,int Type,int forceRestartNum,int FrameLen,int channelNo,int streamNo,int* countStreamFrameRate);

#endif//__RTSP_C_LIB_H__

