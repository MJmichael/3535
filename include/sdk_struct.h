/*
 * =====================================================================================
 *
 *       Filename:  sdk_struct.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20110526 023509
 *       Revision:  none
 *       Compiler:  gcc
 *
 *
 * =====================================================================================
 */
#ifndef __sdk_struct_h__
#define __sdk_struct_h__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


#define MAX_VER_STR_LEN         32      //�汾��Ϣ����
#define MAX_SERIAL_NO_LEN       32      //���кų���
#define MAX_DVR_NAME_LEN        32      //�豸���Ƴ���
#define MAX_CHANN_NAME_LEN      32      //ͨ�����Ƴ���
#ifdef  HI3531
#define MAX_CHANN_NUM           16      //���ͨ������
#elif   HI3521
#define MAX_CHANN_NUM           16      //���ͨ������
#elif   HI3520D
#define MAX_CHANN_NUM           8      //���ͨ������
#elif   HI3535
#define MAX_CHANN_NUM           25      //���ͨ������
#endif
#define MAX_STRING_LEN  128
#define MAX_USER_NAME_LEN       32      //�û�������
#define MAX_PASSWD_LEN          32      //���볤��
#define MAX_ALARM_IN_NAME_LEN   32      //�����������Ƴ���
#define MAX_WEEK_NUM            8       //��������
#define MAX_TIME_SEG_NUM        6       //ʱ��θ���
#define MAX_ALARM_OUT_NUM       16      //��󱨾��������
#define MAX_ALARM_IN_NUM        16      //��󱨾��������
#define MAX_IP_ADDR_LEN         20      //IP��ַ����
#define MAX_RTSP_MAINURL_LEN	128
#define MAX_RTSP_SUBURL_LEN		128
#define MAX_MAC_ADDR_LEN        20      //MAC��ַ����
#define MAX_ETHERNET_NUM        4       //��������
#define MAX_RECORD_ITEM_LEN     64      //¼���¼���Ƴ���
#define MAX_LOG_DESC_LEN        128     //��־��¼���ݳ���
#define MAX_USER_NUM            17      //����û�����
#define MAX_PRESET_NUM          128     //�����̨Ԥ��λ����
#define MAX_CRUISE_LINE_NUM     3     //�����̨Ѳ���߸���
#define MAX_CRUISE_PRESET_NUM   32      //ÿ��Ѳ�������֧�ֵ�Ԥ��λ����
#define MAX_CHANN_CONN_NUM      8       //ÿ��ͨ�����֧�ֵ�������
#define MAX_DISK_NUM            8       //�����̸���
#define MAX_ALARM_DESC_LEN      64      //������¼���ݳ���
#define MAX_SCREEN_NUM          4       //���������Ļ����
#define MAX_WINDOWS_NUM         32      //����Ԥ����Ƶ��󴰿ڸ���
#define MAX_PREVIEW_MODE        8       //���Ԥ�����ָ���
#define MAX_OVERLAY_NUM         4       //ÿ��ͨ����󸲸��������
#define MAX_MOTION_NUM          4       //ÿ��ͨ������ƶ�����������
#define MAX_OSD_STR_LEN         64      //OSD�ַ�������
#define MAX_NTP_SETVER_STR_LEN  32      //NTP��������ַ����
#define MAX_BACKUP_ITEM			16		//��󱸷ݶ���

#define MAX_RESOLUTION_NUM    32
#define MAX_VDA_SENSITIVE_LEVEL 9
#define MAX_STREAM_NUM    		2     	/* �������·��, 0:��������1:������ */
#define MAX_STOR_FRAGMENT_LEN	16		// sizeof(stor_fragment_t)+6��int�ı�����С

#define MAX_NAL_DESC_SIZE       ((4+9*(4+4)))  //��Ƶ֡����ǰ�β��ֳ���

#define MAX_DEV_ID_LEN          32      //����豸ID����
#define MAX_WIFI_AP_NUM			16		//���WIFI-AP����
#define MAX_IF_NAME_LEN         8       //����ӿ�������󳤶�

#define SN_FILE_FREEIP    "/data/FreeIpSn.txt"          // ����FreeIp���кŵ��ļ�
#define SN_FILE_DANALE   "/data/sn.txt"		     // ����DANALE���кŵ��ļ�
#define SN_LEN                 64						// ���кŵ���󳤶�						
#define MAX_BLOCK_ROW  64  // �ƶ�����ڱ�������������
#define MAX_DDNS_TYPE     8                  // ����DDNS����
#define MAX_P2P_TYPE     2			  // ����P2P����
#define MAX_REC_SEG     6			  // ����¼�����
#define MAX_LOG_ITEM   512                  // ������־����
#define DB_OPR_ERROR  -1                   // ���ݿ����ʧ��
#define DATABASE_FILE		"/data/system.db"  // ���ݿ��ļ�

	/*----------- ��Ϣ���� -----------*/

#define MAX_MSG_SIZE        (64*1024)
#define CHANN_TYPE_ALL      0xFA
#define PARAM_MASK_ALL		0xFFFFFFFF		// �ָ���������


typedef enum _WEEKDAY{
	SUNDAY = 0
	,MONDAY
	,TUESDAY
	,WEDNESDAY
	,THURSDAY
	,FRIDAY
	,SATURDAY
}WEEKDAY;

typedef enum _SDK_DEV_TYPE {
	SDK_DEV_TYPE_DVR_16_3520 = 0x00	//DVR 3520 16-D1
	, SDK_DEV_TYPE_DVR_16_3531 = 0x01   //DVR 3531 16-D1(960)
	, SDK_DEV_TYPE_DVR_4_3531  = 0x02   //DVR 3531 04-HD-SDI

	, SDK_DEV_TYPE_NVR_8_3520  = 0x03   //NVR 3520 08-720P
	, SDK_DEV_TYPE_NVR_9_3531  = 0x04	//DVR 3531 09-1080P
	, SDK_DEV_TYPE_NVR_16_3531 = 0x05	//NVR 3531 16-720P
	, SDK_DEV_TYPE_NVR_25_3531 = 0x06	//NVR 3531 25-720P

	, SDK_DEV_TYPE_DECC_12_3531 = 0x07	//DEC CARD 12in, 2out
	, SDK_DEV_TYPE_DECB_12_3531	= 0x08	//DEC BOX  12in, 2out
	, SDK_DEV_TYPE_DVR_8_3531   = 0x09  //DVR 3531 08-HD-SDI
	, SDK_DEV_TYPE_NVR_32_3531  = 0x0A  //NVR 3531 32-720P

	, SDK_DEV_TYPE_NVR_4_3521   = 0x0B  //NVR 3521 04-1080P
	, SDK_DEV_TYPE_NVR_9_3521   = 0x0C  //NVR 3521 09-720P
	, SDK_DEV_TYPE_NVR_16_3521  = 0x0D  //NVR 3521 16-720P

	, SDK_DEV_TYPE_BUTT
}SDK_DEV_TYPE_E;

typedef enum _SDK_MSG_DIR{
	SDK_MSG_RESP= 0x00
	, SDK_MSG_REQ = 0x01
}SDK_MSG_DIR_E;

typedef struct sdk_msg_s {
	uint16_t magic;         //��������չ(���豸����)
	uint16_t version;       //�汾��
#if 1
	union {
		struct {
			uint8_t src;    //Դģ��ID
			uint8_t dst;    //Ŀ��ģ��ID
		}__attribute__((packed)) id;
		uint16_t session_id;//�û��ỰID(�豸�˷���)
	}__attribute__((packed));
	uint16_t sequence_id;   //�������
#endif
#if 1
	uint16_t msg_id;        //����ID
	uint8_t  f_dir:1;       //��SDK_MSG_REQ, SDK_MSG_RESP)
	uint8_t  f_pkg:1;       //1:extend�ֶ������ְ�;
	uint8_t  f_res:6;       //����
	uint8_t  ack;           //������
#endif
	uint32_t args;          //�������(���á���ȡ����;����������������[�û��������������̹���])
	uint32_t extend;        //��չ�ֶ�(8:pkg_total,8:pkg_num, 8:, 8:)
	uint32_t chann;         //ͨ����(CHANN_TYPE_ALL)
	uint32_t size;          //��Ϣ����
	uint8_t  data[0];       //��Ϣ��
	//uint8_t *data;
}sdk_msg_t;

/*----------- ���ݿ���� -----------*/
/*
	  ���ݿ��update��select�����ֱ�ʹ��SDK_PARAM_SET��SDK_PARAM_GET��ʾ��

 */
typedef enum _SDK_PARAM_OPERATE{
	SDK_PARAM_SET	= 0x01	    //����update
	, SDK_PARAM_GET        	    //��ѯselect
	, SDK_PARAM_INSERT             // ����insert
	, SDK_PARAM_DELETE		    // ɾ��delete
}SDK_PARAM_OPERATE_E;



/*----------- �����붨�� -----------*/

typedef enum _SDK_ERR_CODE {
	SDK_ERR_SUCCESS = 0x00        //�ɹ�
	, SDK_ERR_FAILURE               //ʧ��
	, SDK_ERR_PASS                  //�������
	, SDK_ERR_USER_NOT_EXIST		//�û���������
	, SDK_ERR_ROOT_USER				//root�û�����ɾ��
	, SDK_ERR_TOO_MANY_USER			//�û�����(�������16���û���)
	, SDK_ERR_USER_ALREADY_EXIST	//�û����Ѵ���
	, SDK_ERR_NET_CFG				//�����������ʧ��
	, SDK_ERR_PERMIT                //Ȩ�޴���
	, SDK_ERR_CHANN                 // 10 ͨ���Ŵ���
	, SDK_ERR_CONN_MAX              //�������������
	, SDK_ERR_CONN                  //���Ӵ���
	, SDK_ERR_SEND                  //���ݷ��ʹ���
	, SDK_ERR_RECV                  //���ݽ��մ���
	, SDK_ERR_BUSY                  //�豸��æ
	, SDK_ERR_DATA                  //���ݸ�ʽ����
	, SDK_ERR_CMD                   //�����ִ���
	, SDK_ERR_VER                   //Э��汾����
	, SDK_ERR_NO_DISK               //�޴���
	, SDK_ERR_DISK_ERR              // 20 ���̴���
	, SDK_ERR_RESOURCE              //��Դ������
	, SDK_ERR_FLASH                 //FLASH��д����
	, SDK_ERR_SET_SYSTIME			//����ϵͳʱ�����
	, SDK_ERR_SET_ENCODE_PARAM		//���ñ����������
	, SDK_ERR_SET_MD_PARAM			//�����ƶ�����������
	, SDK_ERR_SET_OSD_PARAM			//����OSD��������
	, SDK_ERR_SET_OVERLAY_PARAM		//�����ڵ������������
	, SDK_ERR_SET_TV_PARAM			//���ñ߾��С����
	, SDK_ERR_SET_IMAGE_ATTR		//����ͼ�����Դ���
	, SDK_ERR_LOG_QUERY				//��ѯ��־ʧ��
	, SDK_ERR_LOG_EMPTY				//�����־ʧ��
	, SDK_ERR_LOG_BACKUP			//������־ʧ��
	, SDK_ERR_SERIAL_NO				//���ںŴ���
	, SDK_ERR_SERIAL_OPEN			//�򿪴���ʧ��
	, SDK_ERR_SERIAL_PARAM_SET		//���ô��ڲ���ʧ��
	, SDK_ERR_DISK_MOUNT			//���̹���ʧ��
	, SDK_ERR_UMOUNT				//����ж��ʧ��
	, SDK_ERR_BACKUP				//����ʧ��	
	, SDK_ERR_LOG_DEL				//ɾ����־ʧ��

	, SDK_ERR_GET_DISK_PART_INOF	//��ȡ���̷�����Ϣ����
	, SDK_ERR_UPGRADING				//����������
	, SDK_ERR_UPGRADE_CHECK_HEAD	//У��������ͷ����
	, SDK_ERR_UPGRADE_FILE_FIND		// ���Ҳ��������ļ�
	, SDK_ERR_UPGRADE				// ����ʧ��

	, SDK_ERR_NVR_NOT_LOGIN				// ǰ���豸��û��½�ɹ�

}SDK_ERR_CODE_E;

/*----------- �澯���Ͷ��� -----------*/

typedef enum _SDK_EVENT_TYPE{
	SDK_EVENT_MANUAL_REC = 0x000	//�ֶ�¼���¼�
	, SDK_EVENT_ALARM_IN    		//����澯�¼�
	, SDK_EVENT_MOTION              //�ƶ�����¼�
	, SDK_EVENT_LOST                //��Ƶ��ʧ�¼�
	, SDK_EVENT_HIDE                //��Ƶ�ڵ��¼�(Ŀǰ����)
	, SDK_EVENT_TIMER_REC           //��ʱ¼���¼�
	, SDK_EVENT_HD_ERR              //���̴����¼�
	, SDK_EVENT_HD_IS_EXIST			//¼�����Ƿ�����¼� (pmsg->extend: ������/����[0/1])

	/*8******* ר�����ϱ�������ģ�����Ϣ *************/
	, SDK_EVENT_REC_MSG				//¼���Ƿ����¼�
	, SDK_EVENT_ALARM_IN_MSG
	, SDK_EVENT_MOTION_MSG
	, SDK_EVENT_LOST_MSG
	, SDK_EVENT_HIDE_MSG
	, SDK_EVENT_SYS_RESET           //ϵͳ��λ�¼�, extend:����/�ػ�.
	/******** ***********************/

	/*13*********add 20120601 for  NVR***************/
	, SDK_DEV_LOGIN				//��¼
	, SDK_DEV_TIMEOUT           //��¼��ʱ
	, SDK_DEV_LOGOUT            //ע��
	, SDK_STREAM_OPEN	//���ڴ���
	, SDK_STREAM_CLOSE  		//���ӹر�

	/************add end******************/
	, SDK_EVENT_ALL
	,SDK_CHL_RESET              //Զ������ͨ��֪ͨ
	, SDK_DISKFORMAT		//Զ��Ӳ�̸�ʽ��֪ͨ
	, SDK_UPDATE			//��������֪ͨ
	, SDK_EVENT_BUTT
}SDK_EVENT_TYPE_E;


/*----------- ����Ƶ���Ͷ��� -----------*/
typedef enum _SDK_AUDIO_SAMPLE_RATE
{
	SDK_AUDIO_SAMPLE_R8K        = 0,   /* 8K Sample rate     */
	SDK_AUDIO_SAMPLE_R11_025K   = 1,   /* 11.025K Sample rate*/
	SDK_AUDIO_SAMPLE_R16K       = 2,   /* 16K Sample rate    */
	SDK_AUDIO_SAMPLE_R22050     = 3,   /* 22.050K Sample rate*/
	SDK_AUDIO_SAMPLE_R24K       = 4,   /* 24K Sample rate    */
	SDK_AUDIO_SAMPLE_R32K       = 5,   /* 32K Sample rate    */
	SDK_AUDIO_SAMPLE_R44_1K     = 6,   /* 44.1K Sample rate  */
	SDK_AUDIO_SAMPLE_R48K       = 7,   /* 48K Sample rate    */
	SDK_AUDIO_SAMPLE_BUTT,
}SDK_AUDIO_SAMPLE_RATE_E;

typedef enum _SDK_AUDIO_CODEC_FORMAT
{
	SDK_AUDIO_FORMAT_NULL	        = 0,   /*                    */
	SDK_AUDIO_FORMAT_G711A	        = 1,   /* G.711 A            */
	SDK_AUDIO_FORMAT_G711Mu	        = 2,   /* G.711 Mu           */
	SDK_AUDIO_FORMAT_ADPCM	        = 3,   /* ADPCM              */
	SDK_AUDIO_FORMAT_G726_16        = 4,   /* G.726              */
	SDK_AUDIO_FORMAT_G726_24        = 5,   /* G.726              */
	SDK_AUDIO_FORMAT_G726_32        = 6,   /* G.726              */
	SDK_AUDIO_FORMAT_G726_40        = 7,   /* G.726              */
	SDK_AUDIO_FORMAT_AMR	        = 8,   /* AMR encoder format */
	SDK_AUDIO_FORMAT_AMRDTX	        = 9,   /* AMR encoder formant and VAD1 enable */
	SDK_AUDIO_FORMAT_AAC	        = 10,  /* AAC encoder        */
	SDK_AUDIO_FORMAT_ADPCM_DVI4	    = 11,  /* ADPCM              */
	SDK_AUDIO_FORMAT_ADPCM_IMA	    = 12,  /* ADPCM              */
	SDK_AUDIO_FORMAT_MEDIA_G726_16  = 13,  /* G.726              */
	SDK_AUDIO_FORMAT_MEDIA_G726_24  = 14,  /* G.726              */
	SDK_AUDIO_FORMAT_MEDIA_G726_32  = 15,  /* G.726              */
	SDK_AUDIO_FORMAT_MEDIA_G726_40  = 16,  /* G.726              */
	SDK_AUDIO_FORMAT_BUTT,
}SDK_AUDIO_CODEC_FORMAT_E;

typedef enum _SDK_AUDIO_SAMPLE_WIDTH {
	SDK_AUDIO_SAMPLE_WIDTH_8  = 0,    /* 8bits */
	SDK_AUDIO_SAMPLE_WIDTH_16 = 2,    /* 16bits */
	SDK_AUDIO_SAMPLE_WIDTH_BUTT,
}SDK_AUDIO_SAMPLE_WIDTH_E;


/*
 * ��Ƶ֡��Ϣ(�ӽṹ��)
 */
typedef struct sdk_a_frame_info_s {
	uint8_t encode_type;        //�������� 1: G711A
	uint8_t samples;            //����Ƶ�� 0: 8000, 
	uint8_t bits;               //λ��     1: 16bit, 
	uint8_t channels;           //ͨ����
	uint8_t res[4];
}sdk_a_frame_info_t;


typedef enum _SDK_VIDEO_ENCODE_FORMAT {
	SDK_VIDEO_FORMAT_H264    = 0, //H.264
	SDK_VIDEO_FORMAT_MPEG4   = 1, //MPEG4
	SDK_VIDEO_FORMAT_MJPEG   = 2, //MJPEG
}SDK_VIDEO_ENCODE_FORMAT_E;


typedef enum _SDK_VIDEO_STANDARD {
	SDK_VIDEO_STANDARD_PAL  = 0, // PAL
	SDK_VIDEO_STANDARD_NTSC = 1, //NTSC
}SDK_VIDEO_STANDARD_E;


typedef enum _SDK_VIDEO_RESOLUTION
{
	SDK_VIDEO_RESOLUTION_QCIF    = 0 /* 176 * 144 */
	,SDK_VIDEO_RESOLUTION_CIF     = 1 /* 352 * 288 */
	,SDK_VIDEO_RESOLUTION_HD1     = 2 /* 704 * 288 */
	,SDK_VIDEO_RESOLUTION_D1      = 3 /* 704 * 576 */
	,SDK_VIDEO_RESOLUTION_960H    = 4 /* 960 * 576 */
	,SDK_VIDEO_RESOLUTION_QVGA    = 5 /* 320 * 240 */
	,SDK_VIDEO_RESOLUTION_VGA     = 6 /* 640 * 480 */
	,SDK_VIDEO_RESOLUTION_XGA     = 7 /* 1024 * 768 */
	,SDK_VIDEO_RESOLUTION_SXGA    = 8 /* 1400 * 1050 */
	,SDK_VIDEO_RESOLUTION_UXGA    = 9 /* 1600 * 1200 */
	,SDK_VIDEO_RESOLUTION_QXGA    = 10/* 2048 * 1536 */
	,SDK_VIDEO_RESOLUTION_WVGA    = 11/* 854  * 480  */
	,SDK_VIDEO_RESOLUTION_WSXGA   = 12/* 1680 * 1050 */
	,SDK_VIDEO_RESOLUTION_WUXGA   = 13/* 1920 * 1200 */
	,SDK_VIDEO_RESOLUTION_WQXGA   = 14/* 2560 * 1600 */
	,SDK_VIDEO_RESOLUTION_720p    = 15/* 1280 * 720  */
	,SDK_VIDEO_RESOLUTION_1024p   = 16/*1280 * 1024 */
	,SDK_VIDEO_RESOLUTION_1080p   = 17/* 1920 * 1080 */
	,SDK_VIDEO_RESOLUTION_960p    = 18/* 1280 * 960  */
	,SDK_VIDEO_RESOLUTION_SVGA    = 19/* 800  * 600  */
	,SDK_VIDEO_RESOLUTION_BUTT      // ----------

}SDK_VIDEO_RESOLUTION_E;


typedef enum _SDK_CODEC_AO_DEV_E
{
	SDK_CODEC_COMM_AO_DEV = 0
	, SDK_CODEC_HDMI_AO_DEV = 1
	, SDK_CODEC_AO_DEV_BUTT
}SDK_CODEC_AO_DEV_E;

typedef enum _SDK_CODEC_AO_MOD_E
{
	SDK_CODEC_PREVIEW_AO_MOD = 0
	, SDK_CODEC_PLAYBACK_AO_MOD = 1
	, SDK_CODEC_TALK_AO_MOD = 2
	, SDK_CODEC_MUTE_AO_MOD = 3
}SDK_CODEC_AO_MOD_E;



/*
 * ��Ƶ֡��Ϣ(�ӽṹ��) 
 */
typedef struct sdk_v_frame_info_s {
	uint8_t encode_type;        //�������� 0: H.264
	uint8_t standard;           //��ʽ     0: PAL, 1: NTSC
	uint8_t resolution;         //�ֱ���   SDK_VIDEO_RESOLUTION_E
	uint8_t frame_rate;         //֡��     1-25/30 
	uint16_t width;             //��
	uint16_t height;            //��
}sdk_v_frame_info_t;



typedef enum _SDK_FRAME_TYPE {
	SDK_VIDEO_FRAME_I = 0x01,   //I֡
	SDK_VIDEO_FRAME_P = 0x02,   //P֡
	SDK_VIDEO_FRAME_B = 0x03,   //B֡
	SDK_AUDIO_FRAME_A = 0x04,   //��Ƶ֡A
}SDK_FRAME_TYPE_E;

/*
 * ����Ƶ֡�ṹ�嶨��
 */
typedef struct sdk_frame_s {
	uint16_t  magic;            //��������չ 
	uint8_t   res[1];           //����
	uint8_t   frame_type;       //֡����, ��Ƶ��I, P, B��, ��Ƶ��A��
	uint32_t  frame_size;       //֡����
	uint32_t  frame_no;         //֡���
	uint32_t  sec;              //֡ʱ�䣨�룩
	uint32_t  usec;             //֡ʱ�䣨΢�룩
	uint64_t  pts;              //֡PTS
	union
	{
		sdk_v_frame_info_t video_info;//��Ƶ֡��Ϣ
		sdk_a_frame_info_t audio_info;//��Ƶ֡��Ϣ
	};
	uint8_t   data[0];          //֡����
}__attribute__ ((packed))sdk_frame_t;
/*
* nal�ṹ��
*/
typedef struct sdk_nal_desc_s {
	uint32_t nal_num;           /*NAL����*/
	struct nal_d_s {
		uint32_t nal_off;       /*NAL��ַ*/
		uint32_t nal_size;      /*NAL��С*/
	}nal[0];
}sdk_nal_desc_t;


/*----------- ���ò����ṹ���� -----------*/


/*
 * ʱ��ṹ�嶨��
 */
typedef struct sdk_time_s{
	uint32_t year;
	uint32_t mon;
	uint32_t day;
	uint32_t hour;
	uint32_t min;
	uint32_t sec;
}sdk_time_t;

/*
 * ��ϸʱ��ṹ�嶨��
 */
typedef struct sdk_date_s{
	sdk_time_t _time;
	uint8_t     wday;
	uint8_t     tzone;
	uint8_t     res[2];
}sdk_date_t;



/*
* ����ṹ�嶨��
 */
typedef struct sdk_rect_s{
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
}sdk_rect_t;

/*
 * ��ṹ�嶨��
 */
typedef struct sdk_point_s{
	uint16_t x;
	uint16_t y;
}sdk_point_t;

/*
 * ʱ��νṹ�嶨��
 */
typedef struct sdk_sched_time_s{
	uint8_t enable;	    //����, ����ʱ¼��ʱ��ʾ¼������;
	uint8_t record_type;  /* bit0: Record    bit1: Motion */
	uint8_t res[2];
	uint8_t start_hour; //��ʼʱ��
	uint8_t start_min;
	uint8_t stop_hour;  //����ʱ��
	uint8_t stop_min;
}sdk_sched_time_t;

/*
 * �����������̣� SDK_UPGRAD_REQUEST => recv upg_pkg => SDK_UPGRAD_DISK_FILE => SDK_UPGRAD_PROGRESS;
 * GUI�������� :  SDK_UPGRAD_FIND_FILE => SDK_UPGRAD_DISK_FILE => SDK_UPGRAD_PROGRESS;
*/
typedef enum _SDK_UPGRAD_OP {
	SDK_UPGRAD_REQUEST   = 0x001  //��������				upgrade_packet_t
	, SDK_UPGRAD_DISK_FILE          //�������ڴ����ļ�
	, SDK_UPGRAD_MEM_FILE           //���������ڴ�
	, SDK_UPGRAD_PROGRESS           //��������
	, SDK_UPGRAD_FIND_FILE          //GUI��ѯ�������ļ��б�	upgrad_pkg_file_t
}SDK_UPGRAD_OP_E;


#define MAX_UPGRADE_DEVNAME_LEN		16
#define MAX_UPGRADE_VERNAME_LEN		16
#define MAX_UPGRADE_DATENAME_LEN	16
#define MAX_UPGRADE_FILENAME_LEN	64
#define MAX_UPGRADE_FILEPATH_LEN	128

/*
* GUI��ѯ�������ļ��б�
*/
typedef struct upgrad_pkg_file_s {
	uint8_t   device_type[MAX_UPGRADE_DEVNAME_LEN];//�豸����
	uint8_t   ver[MAX_UPGRADE_VERNAME_LEN];        //�汾
	uint8_t   date[MAX_UPGRADE_DATENAME_LEN];       //����
	uint32_t  size;           //��С
	uint8_t   name[MAX_UPGRADE_FILENAME_LEN];       //���� aa.upg
	uint8_t   file_path[MAX_UPGRADE_FILEPATH_LEN];  //�����ļ�ȫ·�� /tmp/aa.upg
}upgrad_pkg_file_t;

#if 0
	//�ֱ��Ӧ���ݿ�Ĳ���SDK_PARAM_OPERATE_E�е�ö��ֵ
	typedef enum _SDK_USER_OP {
		SDK_USER_MODI=0x01         //update
			, SDK_USER_QUERY       //select
			, SDK_USER_ADD          //insert
			, SDK_USER_DEL          //delete
	}SDK_USER_OP_E;
#endif

typedef enum _SDK_USER_OP {
	SDK_USER_AAA = 0x001  //sdk_user_t
	, SDK_USER_ADD          //sdk_user_right_t
	, SDK_USER_DEL          //sdk_user_t
	, SDK_USER_MODI         //sdk_user_right_t
	, SDK_USER_QUERY        //sdk_user_t, sdk_user_right_t
}SDK_USER_OP_E;

typedef enum _SDK_DISK_OP {
	SDK_DISK_QUERY		= 0x001		//sdk_disk_t
	, SDK_DISK_FORMAT
	, SDK_DISK_PROGRESS
	, SDK_DISK_UMOUNT					//ж��U�� chann�ֶα�ʾ"�̺�"
}SDK_DISK_OP_E;


/*
* �û�����(�û���������)
 */
typedef struct sdk_user_s {
	uint8_t user_name[MAX_USER_NAME_LEN];
	uint8_t user_pwd[MAX_PASSWD_LEN];
}sdk_user_t;


/*
 * �û�Ȩ�޶���
*/
typedef struct sdk_user_right_s {

	sdk_user_t user;   
	uint32_t local_right;           //����GUIȨ��
	/*bit.0: ���ؿ�����̨*/
	/*bit.1: �����ֶ�¼��*/
	/*bit.2: ���ػط�*/
	/*bit.3: �������ò���*/
	/*bit.4: ���ز鿴״̬����־*/
	/*bit.5: ���ظ߼�����(��������ʽ�����������ػ�)*/
	/*bit.6: ���ز鿴���� */
	/*bit.7: ���ع���ģ���IP camera */
	/*bit.8: ���ر��� */
	/*bit.9: ���عػ�/���� */

	uint32_t remote_right;          //Զ��Ȩ��
	/*bit.0: Զ�̿�����̨*/
	/*bit.1: Զ���ֶ�¼��*/
	/*bit.2: Զ�̻ط� */
	/*bit.3: Զ�����ò���*/
	/*bit.4: Զ�̲鿴״̬����־*/
	/*bit.5: Զ�̸߼�����(��������ʽ�����������ػ�)*/
	/*bit.6: Զ�̷��������Խ�*/
	/*bit.7: Զ��Ԥ��*/
	/*bit.8: Զ�����󱨾��ϴ����������*/
	/*bit.9: Զ�̿��ƣ��������*/
	/*bit.10: Զ�̿��ƴ���*/	
	/*bit.11: Զ�̲鿴���� */
	/*bit.12: Զ�̹���ģ���IP camera */
	/*bit.13: Զ�̹ػ�/���� */

	uint8_t local_backup_right[MAX_CHANN_NUM];     //ͨ��Ȩ��
	uint8_t net_preview_right[MAX_CHANN_NUM];

}sdk_user_right_t;


/*
 * ����������������
 */
typedef enum _SDK_NET_IDX {
	SDK_NET_IDX_ETH0      = 0x00 //eth0   sdk_eth_cfg_t
		, SDK_NET_IDX_ETH1		= 0x01 //eth1   sdk_eth_cfg_t
		, SDK_NET_IDX_PPPOE0    = 0x02 //pppoe  sdk_pppoe_t
		, SDK_NET_IDX_WIFI0  	= 0x03 //wifi   sdk_wifi_cfg_t
		, SDK_NET_IDX_3G0		= 0x04 //3g     sdk_3g_cfg_t
		, SDK_NET_IDX_PPPOE1    = 0x05
		, SDK_NET_IDX_WIFI1     = 0x06
		, SDK_NET_IDX_3G1       = 0x07
		, SDK_NET_IDX_BUTT      = 0x08
}SDK_NET_IDX_E;

/*
 * �������ã��ӽṹ�壩
 */
typedef struct sdk_ip_info_s {
	uint8_t if_name[MAX_IF_NAME_LEN];//�ӿ�����(����)
	uint8_t ip_addr[MAX_IP_ADDR_LEN];//IP ADDR
	uint8_t mask[MAX_IP_ADDR_LEN];   //IP MASK
	uint8_t gateway[MAX_IP_ADDR_LEN];//����
	uint8_t mac[MAX_MAC_ADDR_LEN];   //MAC STRING
	uint8_t dns1[MAX_IP_ADDR_LEN];   //DNS1
	uint8_t dns2[MAX_IP_ADDR_LEN];   //DNS2
	uint8_t enable_dhcp;             //�Ƿ���DHCP
	uint8_t dns_auto_en;             //�Զ���ȡDNS(������DHCPʱ���Զ���ȡDNS)
	uint8_t enable_p2p;
	uint8_t res[1];
}sdk_ip_info_t;

/*
 * ������������
 */
typedef struct sdk_eth_cfg_s {

	sdk_ip_info_t ip_info; //IP��Ϣ����

	uint8_t if_mode;       //����ģʽ
	uint8_t res[3];
}sdk_eth_cfg_t;


/*
 * pppoe����
 */
typedef struct sdk_pppoe_s {

	sdk_ip_info_t ip_info;              //PPPOE ��ȡ����IP��ַ

	uint8_t user[MAX_USER_NAME_LEN];    //PPPOE �û���
	uint8_t pass[MAX_PASSWD_LEN];       //PPPOE ����
	uint8_t enable;                    	//�Ƿ���PPPOE
	uint8_t if_no;                      //����ӿ�
	uint8_t res[2];                     //����

}sdk_pppoe_t;


/*
 * wifi ����
 */
typedef struct sdk_wifi_cfg_s {

	sdk_ip_info_t ip_info;

	uint8_t essid[MAX_DEV_ID_LEN];		//���������
	uint8_t pwd[MAX_PASSWD_LEN];		//����
	uint32_t enable;				    //0����ֹ��1��wifi client 2: wifi ap
	uint32_t encrypt_type;				//��������0:NONE  1:WPA  2:WPA2 3:WEP
	uint32_t auth_mode;					//��֤��ʽ0:NONE  1:EAP 2:PSK 3:OPEN 4:SHARED 
	uint32_t secret_key_type;			//��Կ����ʽ 0:NONE  1:AES 2:TKIP ֻ��Ӧ�ڼ�������ΪWPA/WPA2�����

	uint32_t stat;					    //������������״̬ 0 ������ 1 ��������2 �ɹ�
}sdk_wifi_cfg_t;

/*
 * 3g ����
 */
typedef struct sdk_3g_cfg_s {

	sdk_ip_info_t   ip_info;            //3g PPP ��ȡ����IP��ַ

	uint32_t enable;
	uint32_t mod_id;
	uint32_t stat;
	uint8_t  res[64];
}sdk_3g_cfg_t;


/*
 * ��������
 */
typedef struct sdk_net_mng_cfg_s {

	uint8_t        def_if_no;                     //Ĭ������ӿ�(���豸�ж����������ʱ����ʹ��ָ��������)
	uint8_t        res[3];

	uint8_t        multicast[MAX_IP_ADDR_LEN];    //�鲥��ַ
	uint8_t        net_manager[MAX_IP_ADDR_LEN];  //���������IP

	uint16_t       net_manager_port;              //���������PORT
	uint16_t       http_port;                     //DVR HTTP PORT
	uint16_t       dvr_cmd_port;                  //DVR SERVICE PROT
	uint16_t       dvr_data_port;                 //����

}sdk_net_mng_cfg_t;

/*
 * upnp ����
 */
typedef struct sdk_upnp_s{
	uint8_t enable;			//�Ƿ���UPnP
	uint8_t net_type;		//����: SDK_NET_IF_E
	uint8_t en_auto;		//ʹ��ģʽ,0:�̶�ģʽ,1:�Զ�ģʽ
	uint8_t res;            //����

	uint32_t time;			//����ʱ��
	uint8_t server_ip[MAX_IP_ADDR_LEN];//������ip

	uint16_t cmd_port;		//����˿�:jxj����3321
	uint16_t data_port;	    //���ݶ˿�:jxj����7554
	uint16_t web_port;		//web�˿�:jxj����80
	uint16_t res_port;      //����
	uint16_t cmd_stat;		//����˿�ӳ���״̬,�ɹ�:ӳ�����ⲿ�˿ں�, ʧ��:0
	uint16_t data_stat;	    //���ݶ˿�ӳ���״̬,�ɹ�:ӳ�����ⲿ�˿ں�, ʧ��:0
	uint16_t web_stat;		//web�˿�ӳ���״̬,�ɹ�:ӳ�����ⲿ�˿ں�,  ʧ��:0
	uint16_t res_stat;      //����

}sdk_upnp_t;

/*
 * DVR�������ò���
 */

typedef struct sdk_comm_cfg_s
{
	uint8_t 	dvr_name[MAX_DVR_NAME_LEN]; //DVR ����
	uint32_t 	dvr_id;                    	//DVR ID,(ң����)
	uint32_t 	recycle_record;            	//�Ƿ�ѭ��¼��,0:����; 1:��
	uint8_t 	language;					//����0: ����  1 :Ӣ��
	uint8_t  	video_mode;					//��Ƶ��ʽ0:PAL  1 NTSC
	uint8_t  	out_device;					//����豸  0: CVBS; 1: VGA; 2: HDMI
	uint8_t  	resolution; 				//(����)�ֱ���0 :1024 * 768    1 : 1280 * 720   2: 1280*1024  3: 1920*1080
	uint8_t 	standby_time; 				//�˵�����ʱ�� 1~60����  0: ��ʾ������
	uint8_t  	boot_guide;					//������ 0 : ��������  1 : ������
	uint8_t  	resolution2; 				//(����)�ֱ���0 :1024 * 768    1 : 1280 * 720   2: 1280*1024  3: 1920*1080
	uint8_t  	wizardEnable;         // ������
	uint8_t  	transparent;           //͸����
} sdk_comm_cfg_t;


/* 
 *
 * DVRϵͳ���ò���
 */

typedef struct sdk_sys_cfg_s {

	/*---------- ������Ϣ���ɸ��� ----------*/
	uint8_t serial_no[MAX_SERIAL_NO_LEN];       //���к�
	uint8_t device_type[MAX_VER_STR_LEN];       //�豸�ͺ�
	uint8_t software_ver[MAX_VER_STR_LEN];      //����汾��
	uint8_t software_date[MAX_VER_STR_LEN];     //�����������
	uint8_t panel_ver[MAX_VER_STR_LEN];         //ǰ���汾
	uint8_t hardware_ver[MAX_VER_STR_LEN];      //Ӳ���汾

	uint32_t dev_type;                          //�豸����SDK_DEV_TYPE_E    J_DevType_E from j_sdk.h

	uint8_t ana_chan_num;                       //ģ��ͨ������
	uint8_t ip_chan_num;                        //����ͨ����
	uint8_t dec_chan_num;                       //����·��
	uint8_t stream_num;                         //����

	uint8_t audio_in_num;                       //��������ڵĸ���
	uint8_t audio_out_num;                      //��������ڵĸ���
	uint8_t alarm_in_num;                       //�����������
	uint8_t alarm_out_num;                      //�����������

	uint8_t net_port_num;                       //����ڸ���
	uint8_t rs232_num;                          //232���ڸ���
	uint8_t rs485_num;                          //485���ڸ���
	uint8_t usb_num;                            //USB�ڵĸ���

	uint8_t hdmi_num;                           //HDMI�ڵĸ���
	uint8_t vga_num;                            //VGA�ڵĸ���
	uint8_t cvbs_num;                           //cvbs�ڵĸ���
	uint8_t aux_out_num;                        //���ڵĸ���

	uint8_t disk_ctrl_num;                      //Ӳ�̿���������
	uint8_t disk_num;                           //Ӳ�̸���
	uint8_t res2[2];                            //����

	uint32_t max_encode_res;                    //������ֱ���
	uint32_t max_display_res;                   //�����ʾ�ֱ���

	uint32_t dvr_bit;                           //DVR����
	uint8_t  dvr_byte[4];                       //DVR����
}sdk_sys_cfg_t;

/*
 * ƽ̨��Ϣ �ӽṹ��
 *
 */

typedef struct sdk_screen_slot_s {
	uint32_t magic;				/* 0x55aa55aa */
	uint32_t index[MAX_SCREEN_NUM];
}sdk_screen_slot_t;

/*
 * ƽ̨��Ϣ
 *
 */

typedef struct sdk_platform_s {
	uint8_t pu_id[MAX_USER_NAME_LEN];           
	uint8_t cms_ip[MAX_IP_ADDR_LEN];            //ƽ̨mds ip
	uint8_t mds_ip[MAX_IP_ADDR_LEN];            //ƽ̨mds ip
	uint32_t cms_port;                          //ƽ̨cms�˿ں�
	uint32_t mds_port;                          //ƽ̨mds�˿ں�
	uint32_t protocol;                          //0:tcp   1:udp
	uint32_t plat_enable;                       //ƽ̨����

	sdk_screen_slot_t slot;						//����������
}sdk_platform_t;

/*
 * 
 * ϵͳ�汾��Ϣ
 */

typedef struct sdk_version_s {
	uint8_t serial_no[MAX_SERIAL_NO_LEN];       /* ��Ʒ���к� */
	uint8_t device_type[MAX_VER_STR_LEN];       /* ��Ʒ�ͺ� */
	uint8_t software_ver[MAX_VER_STR_LEN];	    /* �汾�� */
	uint8_t software_date[MAX_VER_STR_LEN];	    /* �汾���� */
	uint8_t panel_ver[MAX_VER_STR_LEN];         //ǰ���汾
	uint8_t hardware_ver[MAX_VER_STR_LEN];      //Ӳ���汾
}sdk_version_t;


/*
 * �ָ�Ĭ�ϲ���
 */

typedef enum _SDK_PARAM_MASK_ID {
	SDK_PARAM_MASK_ENCODE = 0x00    	//bit.0: �������
		, SDK_PARAM_MASK_PTZ             	//bit.1: PTZ��̨����
		, SDK_PARAM_MASK_RECORD      		//bit.2: ¼�����
		, SDK_PARAM_MASK_NET             	//bit.3: �������
		, SDK_PARAM_MASK_CHANNEL    		//bit.4: ͨ������
		, SDK_PARAM_MASK_IMAGE_ATTR			//bit.5: ��Ƶ����
		, SDK_PARAM_MASK_SERIAL				//bit.6: ���ڲ���
		, SDK_PARAM_MASK_OVERLAY			//bit.7: �ڵ��������
		, SDK_PARAM_MASK_MOTION				//bit.8: �ƶ����
		, SDK_PARAM_MASK_COMM				//bit.9: �������
		, SDK_PARAM_MASK_OSD				//bit.10: osd����
		, SDK_PARAM_MASK_USER				//bit.11: �û�����
		, SDK_PARAM_MASK_ALARM_IN			//bit.12: �ⲿ�����������
		, SDK_PARAM_MASK_HIDE				//bit.13: ��Ƶ�ڵ�������
		, SDK_PARAM_MASK_VIDEO_LOST			//bit.14: ��Ƶ��ʧ����
		, SDK_PARAM_MASK_TV					//bit.15: �߾���ڲ���
		, SDK_PARAM_MASK_PREVIEW			//bit.16: Ѳ�ز���
		, SDK_PARAM_MASK_TOUR               //bit.17: Ѳ�ز���
		, SDK_PARAM_MASK_EMAIL			  	//bit.18
		, SDK_PARAM_MASK_DDNS			  	//bit.19
		,SDK_PARAM_MASK_DISPLAY                     //bit 20
		, SDK_PARAM_MASK_BUIT
}SDK_PARAM_MASK_ID_E;


typedef struct sdk_default_param {

	uint32_t param_mask;    //������������ SDK_PARAM_MASK_ID_E
	uint32_t res[1];
}sdk_default_param_t;


/*
 * ϵͳ����״̬��Ϣ
 */
typedef enum _SDK_STATUS_OP {
	SDK_STATUS_DEVICE = 0x01  //�豸����״̬
		, SDK_STATUS_DISK           //����״̬
		, SDK_STATUS_CHANN          //ͨ��״̬
		, SDK_STATUS_ALARM_IN       //���뱨��״̬
		, SDK_STATUS_ALARM_OUT      //�������״̬
}SDK_STATUS_OP_E;

typedef struct sdk_chan_status_s {

	uint8_t chan_type;          //ͨ������ 0�����أ�1��IP
	uint8_t record_state;       //¼��״̬,0-��¼��,1-¼��
	uint8_t signal_state;       //�ź�״̬, 0:������1���źŶ�ʧ
	uint8_t encode_state;       //����״̬, 0:�����룬1������

	uint32_t bit_rate;          //ʵ������
	uint32_t conn_num;          //ͨ��������
	uint8_t  conn_ip[MAX_CHANN_CONN_NUM][MAX_IP_ADDR_LEN];//����IP
}sdk_chan_status_t;


typedef struct sdk_disk_status_s {
	uint32_t volume;        //Ӳ�̵�����
	uint32_t free_space;    //Ӳ�̵�ʣ��ռ�
	uint32_t disk_state;   //Ӳ�̵�״̬,0-�,1-����,2-������
}sdk_disk_status_t;

/*
 * ϵͳ״̬(������ֳ� SDK_STATUS_OP_E)
 */

typedef struct sdk_status_s { 

	uint32_t            device_status;                      //�豸״̬��0-����,1-CPUռ����̫��,����85%,2-Ӳ������
	sdk_disk_status_t   disk_status[MAX_DISK_NUM];          //Ӳ��״̬
	sdk_chan_status_t   chan_status[MAX_CHANN_NUM];         //ͨ��״̬
	uint8_t             alarm_in_status[MAX_ALARM_IN_NUM];  //�����˿ڵ�״̬,0-û�б���,1-�б���
	uint8_t             alarm_out_status[MAX_ALARM_OUT_NUM];//��������˿ڵ�״̬,0-û�����,1-�б������

	uint8_t             local_display;                      //������ʾ״̬, 0:������1��������
	uint8_t             audio_chan_status;                  //����ͨ����״̬ 0-δʹ�ã�1-ʹ����, 0xff��Ч
	uint8_t             res[2];

}sdk_status_t;




/*
 * ��־
 */
// ��־����ѡ��,�ֱ��Ӧ���ݿ�Ĳ���SDK_PARAM_OPERATE_E�е�ö��ֵ
typedef enum _SDK_LOG_OP {
	SDK_LOG_QUERY=0x02,       // select
	SDK_LOG_INSERT, 		 //insert
	SDK_LOG_CLEAR,                //delete
}SDK_LOG_OP_E;


// ��־��ѯ����
typedef enum _SDK_LOG_QUERY {
	SDK_LOG_QUERY_NUM = 0x00, // ��ѯĳ����־��������־������
	SDK_LOG_QUERY_CONTENT     // ��ѯ��־������
}SDK_LOG_QUERY_E;


// ��־�����ͺ�������ö��
// ��־�����ͣ�logId�ĸ�8λ
typedef enum _SDK_LOG_MAIN_TYPE
{
	LOG_QUERY_ALL=0,      // ȫ����־
	LOG_SYS_MANAGE = 0x01, // ϵͳ����
	LOG_USER_MANAGE,          // �û�����
	LOG_PARAMS_SETUP,        // ��������
	LOG_FILE_OPERATE,          // �ļ�����
	LOG_STATUS_WARNING,    // ״̬��ʾ
	LOG_ALARM_EVENT            // �澯�¼�
}SDK_LOG_MAIN_TYPE_E;

//��������־�����͵�ö�٣�logId�ĵ�8λ
//  ������ö��:  "�û�����"
typedef enum _SDK_LOG_USER_MANAGER_TYPE
{
	LOG_USER_LOGIN = 0x01,    //�û���¼
	LOG_USER_LOGOUT,            // �û��˳�
	LOG_USER_ADD,                  // ����û�
	LOG_USER_DEL,                  // ɾ���û�
	LOG_USER_MODIFY,           // �޸��û�
	LOG_USER_ADD_GROUP,  //�����û���
	LOG_USER_DEL_GROUP,   // ɾ���û���
	LOG_USER_MODIFY_GROUP  // �޸��û���
}SDK_LOG_USER_MANAGER_TYPE_E;


//  ������ö��:  "ϵͳ����"
typedef enum _SDK_LOG_SYS_OPT_TYPE
{
	LOG_SYS_START = 0x01,  // ����
	LOG_SYS_SHUTDOWN,     // �ػ�
	LOG_SYS_REBOOT,          // ����
	LOG_SYS_UPGRADE,       // ����
	LOG_SYS_DEFAULT       // �ָ���������
}SDK_LOG_SYS_OPT_TYPE_E;

/* ������ö��:  �������� */
typedef enum _SDK_LOG_PARAM_SETUP_TYPE
{
	LOG_COMMON_SETUP = 0x01, 	//������ͨ���ò��� 
	LOG_COMMON_DEFAULT,	//��������ָ�ΪĬ��ֵ
	LOG_ENCODE_SETUP,		//���ñ������
	LOG_ENCODE_DEFAULT,	//��������ָ�ΪĬ��ֵ
	LOG_RECODE_SETUP,		//����¼�����
	LOG_RECODE_DEFAULT,	//¼������ָ�ΪĬ��ֵ
	LOG_NETWORK_SETUP,	//�����������
	LOG_NETWORK_DEFAULT,//��������ָ�ΪĬ��ֵ
	LOG_ALARM_SETUP,		//���ñ�������
	LOG_ALARM_DEFAULT,	//���������ָ�ΪĬ��ֵ
	LOG_MOTION_SETUP,		//�����ƶ�������
	LOG_MOTION_DEFAULT,	//�ƶ��������ָ�ΪĬ��ֵ
	LOG_PTZ_SETUP,			//����Ѳ������
	LOG_PTZ_DEFAULT,		//Ѳ�������ָ�ΪĬ��ֵ
	LOG_OUTMODE_SETUP,	//�������ģʽ����

	LOG_OUTMODE_DEFAULT,//���ģʽ�����ָ�ΪĬ��ֵ
	LOG_CHN_SETUP,		//ͨ������
	LOG_CHN_DEFAULT,	       //ͨ�����ûָ�ΪĬ��ֵ
	LOG_IMAGE_COLOR_SETUP,		//����ͼ����ɫ����
	LOG_IMAGE_COLOR_DEFAULT,		//ͼ����ɫ�ָ�ΪĬ��ֵ
	LOG_PREVIEW_SETUP,			//����Ԥ������
	LOG_PREVIEW_DEFAULT,			//Ԥ�������ָ�ΪĬ��ֵ
	LOG_USER_PARAM_DEFAULT,		//�û������ָ�ΪĬ��ֵ
	LOG_SENSOR_SETUP,				//���ô���������
	LOG_SENSOR_DEFAULT,			//�����������ָ�ΪĬ��ֵ
	LOG_DDNS_SETUP,				//����DDNS����
	LOG_SMTP_SETUP,				//����SMTP����
	LOG_CLOUD_SETUP,				//�����ƶ˲���
	LOG_UPNP_SETUP,				//����UPNP����
	LOG_SERIAL_DEFAULT,                   // ���ڲ����ָ�ΪĬ��ֵ
	LOG_OVERLAY_DEFAULT,                 // �����ڱβ����ָ�ΪĬ��ֵ
}SDK_LOG_PARAM_SETUP_TYPE_E;

/* ������ö��: �ļ����� */
typedef enum _SDK_LOG_FILE_OPT_TYPE
{
	LOG_FILE_UPLOAD = 0x01,	//�ϴ������ļ����ƶ�
	LOG_FILE_DOWNLOAD,		//�����ƶ��ļ�������
	LOG_FORMAT_DISK,			//��ʽ��Ӳ��<N>
	LOG_READ_WRITE_DISK,		//�޸�Ӳ��<N>Ϊ��дӲ��
	LOG_READ_ONLY_DISK,		//�޸�Ӳ��<N>Ϊֻ��Ӳ��
	LOG_RECODE_BACKUP,		//¼�񱸷�
}SDK_LOG_FILE_OPT_TYPE_E;


/* ������ö��: ״̬��ʾ */
typedef enum _SDK_LOG_STATUS_WARNING_TYPE
{
	LOG_STATUS_SYNC_NTP = 0x01,			//ͬ������ʱ���������NTP��
	LOG_STATUS_AUTO_MAINTAIN_ON,		//����ϵͳ�Զ�ά��
	LOG_STATUS_AUTO_MAINTAIN_OFF,	//�ر�ϵͳ�Զ�ά��	
	LOG_STATUS_AUTO_RECODE_ON,		//����¼��<�Զ�>
	LOG_STATUS_AUTO_RECODE_OFF,		//�ر�¼��<�Զ�>
	LOG_STATUS_MANUAL_RECODE_ON,		//����¼��<�ֶ�>
	LOG_STATUS_MANUAL_RECODE_OFF,	//�ر�¼��<�ֶ�>
	LOG_STATUS_RECODE_ALLDAY_ON,		//����ȫ��¼��
	LOG_STATUS_RECODE_ALLDAY_OFF,		//�ر�ȫ��¼��
	LOG_STATUS_DHCP_ON,				//����DHCP���Զ���ȡ�������
	LOG_STATUS_NETWORK_MANUAL_SETUP,	//�ֶ������������	
	LOG_STATUS_MOTION_DETECT_ON,		//�����ƶ����
	LOG_STATUS_MOTION_DETECT_OFF,		//�ر��ƶ����
	LOG_STATUS_LINK_BUZZER_ON,		//����������
	LOG_STATUS_LINK_BUZZER_OFF,		//ȡ������������

	LOG_STATUS_LINK_RECODE_CH_ON,		//����¼��ͨ��	
	LOG_STATUS_LINK_RECODE_CH_OFF,	//ȡ������¼��ͨ��
	LOG_STATUS_SENSOR_WARNING_ON,	//�����������澯
	LOG_STATUS_SENSOR_WARNING_OFF,	//�رմ������澯
	LOG_STATUS_PTZ_CHN_ON,				//����ͨ��Ѳ��
	LOG_STATUS_PTZ_CHN_OFF,			//�ر�ͨ��Ѳ��
	LOG_STATUS_ADD_PRESET,				//���Ѳ����
	LOG_STATUS_DEL_PRESET,				//ɾ��Ѳ����
	LOG_STATUS_AUTO_SCAN_ON,			//�����Զ�ɨ��
	LOG_STATUS_AUTO_SCAN_OFF,			//�ر��Զ�ɨ��
	LOG_STATUS_DDNS_ON,				//����DDNS
	LOG_STATUS_UPNP_ON,				//����UPNP
	LOG_STATUS_UPNP_OFF,				//����UPNP	

	LOG_STATUS_P2P_ON,					//����P2P
	LOG_STATUS_P2P_OFF,					//�ر�P2P
	LOG_STATUS_SMTP_ON,				//����SMTP	
	LOG_STATUS_SMTP_OFF,				//�ر�SMTP	
	LOG_STATUS_AUDIO_ON,					//��������	
	LOG_STATUS_MUTE     						//����
}SDK_LOG_STATUS_WARNING_TYPE_E;

/* ������ö��: �澯�¼� */
typedef enum _SDK_LOG_WARNING_EVENT_TYPE
{
	LOG_WARNING_NO_DISK = 0x01,     			//��Ӳ��
	LOG_WARNING_DISK_FORMAT_FAIL,			//Ӳ��<N>��ʽ��ʧ��
	LOG_WARNING_DISK_FORMAT_SUCC,			//Ӳ��<N>��ʽ���ɹ�
	LOG_WARNING_DISK_ABNORMAL,				//Ӳ���쳣
	LOG_WARNING_DISK_NO_SPACE,				//Ӳ�̿ռ䲻��
	LOG_WARNING_ENCODE_PARAM_GET_FAIL,	//���������ȡʧ��
	LOG_WARNING_ENCODE_PARAM_SET_FAIL,	//�����������ʧ��	
	LOG_WARNING_ENCODE_PARAM_ABNORMAL,	//��������쳣
	LOG_WARNING_CLEAR_LOG,					//�����־
	LOG_WARNING_RECODE_ABNORMAL,			//¼���ļ��쳣	
	LOG_WARNING_NETWORK_ABNORMAL,			//�������ӶϿ�
	LOG_WARNING_NETWORK_OK,					//������������
	LOG_WARNING_IP_CONFLICT,					//IP��ַ��ͻ
	LOG_WARNING_MAC_CONFLICT,				//MAC��ַ��ͻ
	LOG_WARNING_DDNS_CONNECT_FAIL,			//DDNS����ʧ��

	LOG_WARNING_DDNS_CONNECT_SUCC,			//DDNS���ӳɹ�
	LOG_WARNING_NTP_SYNC_FAIL,				//NTP����ʱ�����ʧ��
	LOG_WARNING_NTP_SYNC_SUCC,				//NTP����ʱ����³ɹ�
	LOG_WARNING_UPNP_FAIL,					//UPNP�˿�ӳ��ʧ��
	LOG_WARNING_UPNP_SUCC,					//UPNP�˿�ӳ��ɹ�
	LOG_WARNING_EMAIL_SEND_FAIL,			//�ʼ�����ʧ��
	LOG_WARNING_EMAIL_SEND_SUCC,			//�ʼ����ͳɹ�
	LOG_WARNING_P2P_LINK_ABNORMAL,			//P2P�����쳣
	LOG_WARNING_P2P_LINK_OK,					//P2P��������
	LOG_WARNING_UPLOAD_FAIL,				//�����ļ��ϴ����ƶ�ʧ��
	LOG_WARNING_UPLOAD_SUCC,				//�����ļ��ϴ����ƶ˳ɹ�
	LOG_WARNING_DOWNLOAD_FAIL,				//�ƶ��ļ����ص�����ʧ��
	LOG_WARNING_DOWNLOAD_SUCC,				//�ƶ��ļ����ص����سɹ�
	LOG_WARNING_SENSOR,						//�������澯
	LOG_WARNING_VEDIO_LOSS,					//��Ƶ��ʧ�澯

	LOG_WARNING_BACKUP_FAIL,					//�ļ�����ʧ��
	LOG_WARNING_NO_REMOTE_DEVICE,			//δ����Զ���豸
	LOG_WARNING_NO_PTZ_DEVICE				//����̨�豸
}SDK_LOG_WARNING_EVENT_TYPE_E;
/*��־ö�ٽ���*/

/*
 * ϵͳ��־������
 */
typedef enum _L_SYSTEM_MINOR_TYPE {
	L_SYSTEM_MINOR_STARTUP = 0x0001   //����
		, L_SYSTEM_MINOR_SHUTDOWN           //�ػ�
		, L_SYSTEM_MINOR_REBOOT				//����

		, L_SYSTEM_MINOR_ALL     = 0xffff   //����ϵͳ��־
}L_SYSTEM_MINOR_TYPE_E;

/*
 * �澯��־������
 */
typedef enum _L_ALARM_MINOR_TYPE {
	L_ALARM_MINOR_DI_START = 0x0001   //����澯����
		, L_ALARM_MINOR_DI_STOP             //����澯ֹͣ
		, L_ALARM_MINOR_MD_START            //�ƶ����澯����
		, L_ALARM_MINOR_MD_STOP             //�ƶ����澯ֹͣ
		, L_ALARM_MINOR_VL_START			//��Ƶ��ʧ�澯����
		, L_ALARM_MINOR_VL_STOP				//��Ƶ��ʧ�澯ֹͣ

		, L_ALARM_MINOR_ALL		= 0xffff	//���и澯��־
}L_ALARM_MINOR_TYPE_E;

/*
 * ������־������
 */
typedef enum _L_OPERATE_MINOR_TYPE {
	L_OPERATE_MINOR_LOGIN = 0x0001	// ��½	
		, L_OPERATE_MINOR_LOGOUT 			// ע��
		, L_OPERATE_MINOR_USER_ADD			// �û�����-����
		, L_OPERATE_MINOR_USER_DEL			// �û�����-ɾ��
		, L_OPERATE_MINOR_USER_MODI			// �û�����-�޸�
		, L_OPERATE_MINOR_SETTIME 			// ����ϵͳʱ��
		, L_OPERATE_MINOR_FORMAT_DISK 		// ��ʽ��Ӳ��
		, L_OPERATE_MINOR_DEFAULT 			// �ָ�Ĭ��
		, L_OPERATE_MINOR_UPGRADE 			// ����
		, L_OPERATE_MINOR_PLAYBACK 			// �ط�
		, L_OPERATE_MINOR_PTZ 				// ��̨����
		, L_OPERATE_MINOR_BACKUP 			// ����
		, L_OPERATE_MINOR_RECORD_START 		// ����¼��
		, L_OPERATE_MINOR_RECORD_STOP 		// ֹͣ¼��
		, L_OPERATE_MINOR_CLR_ALARM 		// �������
		, L_OPERATE_MINOR_TALKBACK_START 	// �Խ���ʼ
		, L_OPERATE_MINOR_TALKBACK_STOP 	// �Խ�����
		, L_OPERATE_MINOR_LOG_DEL			// ɾ����־
		, L_OPERATE_MINOR_LOG_EMPTY			// �����־
		, L_OPERATE_MINOR_LOG_BACKUP		// ������־
		, L_OPERATE_MINOR_MANUAL_RECORD_START 		// �ֶ�����¼��
		, L_OPERATE_MINOR_MANUAL_RECORD_STOP 		// �ֶ�ֹͣ¼��	
		, L_OPERATE_MINOR_FORMAT_DISK_U 	// ��ʽ��U��

		, L_OPERATE_MINOR_ALL	= 0xffff	// ���в�����־
}L_OPERATE_TYPE_E;

/*
 * ������־������
 */
typedef enum _L_PARAM_MINOR_TYPE {
	L_PARAM_MINOR_PARAM_NETWORK = 0x0001 	// �����������
		, L_PARAM_MINOR_PARAM_UART 				// ���ڲ�������
		, L_PARAM_MINOR_PARAM_PTZ 				// ��̨��������
		, L_PARAM_MINOR_PARAM_CHAN 				// ͨ����������
		, L_PARAM_MINOR_PARAM_VENC 				// �����������
		, L_PARAM_MINOR_PARAM_TV 				// TV��������
		, L_PARAM_MINOR_PARAM_PIC_ATTR			// ͼ����������
		, L_PARAM_MINOR_PARAM_RECORD			// ¼���������
		, L_PARAM_MINOR_PARAM_MOTION			// �ƶ��������
		, L_PARAM_MINOR_PARAM_VIDEOLOST			// ��Ƶ��ʧ����
		, L_PARAM_MINOR_PARAM_ALARMIN			// ����澯����
		, L_PARAM_MINOR_PARAM_POLL				// ��Ѳ����
		, L_PARAM_MINOR_PARAM_PREVIEW			// Ԥ������
		, L_PARAM_MINOR_PARAM_OVERLAY			// �ڵ���������
		, L_PARAM_MINOR_PARAM_OSD				// OSD����
		, L_PARAM_MINOR_PARAM_COMM				// ��������

		, L_PRARM_MINOR_ALL	= 0xffff			// ���в�����־
}L_PARAM_MINOR_TYPE_E;

/*
 * �쳣��־������
 */
typedef enum _L_EXCEPTION_MINOR_TYPE {
	L_EXCEPTION_HD_FULL 		= 0x0001   	//Ӳ����
		, L_EXCEPTION_HD_ERROR           		//Ӳ�̴���
		, L_EXCEPTION_NET_DISCONNECT			//����Ͽ�
		, L_EXCEPTION_IP_CONFLICT				//IP��ͻ

		, L_EXCEPTION_MINOR_ALL     = 0xffff   	//�����쳣��־
}L_EXCEPTION_MINOR_TYPE_E;

/*
 * 
 */

#if 0
typedef struct sdk_log_item_s {
	sdk_time_t  time;                       //ʱ��
	uint32_t    major_type;                 //����LOG_MAJOR_TYPE_E 
	uint32_t    minor_type;                 //0x0000:ֱ����ʾdesc���ݣ�����ͨ��L_XXX_MINOR_TYPE_E��������.
	uint32_t    args;                       /*�����Ͳ���(args=0ʱ���ý���,�������minor_type�������ݡ�
						  ���minor_type��ͨ������أ�args��ʾͨ����;���minor_type�͸澯��أ�args��ʾ�澯�����)*/
	uint8_t     user[MAX_USER_NAME_LEN];    //�����û�
	uint8_t     ip_addr[MAX_IP_ADDR_LEN];   //�û�IP
	uint8_t     desc[MAX_LOG_DESC_LEN];     //��־����(minor_type=0ʱ��Ч)
}sdk_log_item_t;
*/
#endif

typedef struct sdk_log_item_s {
	sdk_time_t  time;                       // ��־������ʱ��
	uint8_t     user[MAX_USER_NAME_LEN];    // �û���
	uint16_t    logId;   // ��־ID��ǰ16λ����־���ͣ���16λ�Ǹ����͵���־��Ϣ�е���־���
}sdk_log_item_t;

/*
 * ��־��ѯ����
 */
typedef struct sdk_log_cond_s {
	sdk_time_t  begin_time;                 //��ʼʱ��
	sdk_time_t  end_time;                   //����ʱ��
	uint8_t    type;                       //����
	//uint8_t     user[MAX_USER_NAME_LEN];    //�����û�
	//uint8_t     ip_addr[MAX_IP_ADDR_LEN];   //�û�IP
}sdk_log_cond_t;



/*
 * ������Ϣ����
 */
typedef struct sdk_alarm_info_s {
	sdk_time_t  time;                   //����ʱ��
	uint32_t    type;                   //��������
	uint32_t    args;                   //��������
	uint8_t     desc[MAX_ALARM_DESC_LEN];//��������
}sdk_alarm_info_t;


/*
 * ���ڲ�������
 */
typedef struct sdk_serial_param_s {
	uint32_t baud_rate;             //���ڲ����� 115200, 57600, ...
	uint8_t  data_bit;              //����λ 5, 6, 7, 8 
	uint8_t  stop_bit;              //ֹͣλ 1, 2
	uint8_t  parity;                //У�� 0:�ޣ�1:��У�� 2:żУ�� 
	uint8_t  flow_ctl;              //����
}sdk_serial_param_t;

/*
 * ������;����
 */
typedef struct sdk_serial_func_cfg_s {
	uint8_t type;	// 0: normal, 1: ptz, 2...
	uint8_t res[3];
	sdk_serial_param_t serial_param;
}sdk_serial_func_cfg_t;


/*
 * ��̨���ò���
 */
/*
 *  _0: debug, _1: ptz/normal, _2: rs232, _3 mcu
 *  -------------------------, _2: mcu;
 *  0: 1
 *   
 */
typedef struct sdk_ptz_param_s {

	sdk_serial_param_t comm;                //���ڲ�����gui�̶�ֻ���ô���1
	uint8_t          address;               //��̨��ַ
	uint8_t          protocol;              //��̨Э��SDK_PTZ_PROTOCOL_E
	uint8_t          res[2];
}sdk_ptz_param_t;


//Ԥ�õ�
typedef struct  sdk_preset_s
{
	uint8_t  num;                       //Ԥ�õ���
	uint8_t enable;                    //Ԥ�õ�ʹ��״̬
	uint8_t res[2];     

}sdk_preset_t;


typedef struct sdk_preset_all_s
{
	int num;                            //Ԥ�õ����  ������128ʱ������128����
	sdk_preset_t  preset[MAX_PRESET_NUM];

}sdk_preset_all_t;
//ÿ���ؼ���
typedef struct sdk_preset_param_s 
{
	uint8_t enable;                                //  ʹ�ܱ�־
	uint8_t res[2];                                 // ����λ  
	uint8_t num;                                   //�ؼ�����                 
	uint8_t speed;     //                            //
	uint8_t dwell_time;//
	sdk_preset_t  preset;                      //��Ӧ��Ԥ�õ�

}sdk_preset_param_t;
//Ѳ��·��
typedef struct sdk_cruise_param_s 
{
	uint8_t         line;                        //Ѳ��·�߱��
	uint8_t         enable;                    //Ѳ��·���Ƿ�ʹ��
	uint8_t         res[3];                    //����λ
	sdk_preset_param_t  cruise_preset[MAX_CRUISE_PRESET_NUM];   //��·�����е�Ԥ�õ�

}sdk_cruise_param_t;


typedef struct sdk_cruise_line_s 
{ 
	//��ͨ�����е�Ѳ����·���еĹؼ�����Ϣ
	sdk_cruise_param_t  cruise_line[MAX_CRUISE_LINE_NUM];  
	//��ͨ�����е�Ԥ�õ�
	sdk_preset_all_t  preset_all;

}sdk_cruise_line_t;

//��̨����ѡ��Ŵ���С(˽�� ����ר��)


/*
 * 
 * Ԥ������(��������޸�)
 */


typedef enum _SDK_SCREE_SPLIT {
	SDK_SCREE_ONE  = 0x00
		, SDK_SCREE_FOUR
		, SDK_SCREE_NINE
		, SDK_SCREE_SIXTEEN
		, SDK_SCREE_THIRTY_TWO
		, SDK_SCREE_BUTT
}SDK_SCREE_SPLIT_E;


/*
 * ��Ļ����
 * sdk_msg_t.chann ��ʾ����
 */
typedef struct sdk_preview_s {
	uint8_t windows[MAX_PREVIEW_MODE][MAX_WINDOWS_NUM];
	uint8_t enable;     //����/��ֹ��Ļ������������ܽ�ֹ��
	uint8_t init_mode;      //����ʱ��ʼ������ģʽ,0-1����,1-4����,2-6����,3-8����,4-9����,5-16����,6-25����,7-36����,0xff:�����
	uint8_t res[2];         //����
}sdk_preview_t;

/*
 * GUIԤ��Ѳ������
 * sdk_msg_t.chann ��ʾ����
 */
typedef struct sdk_tour_s {
	uint8_t windows[MAX_PREVIEW_MODE][MAX_WINDOWS_NUM];//�л�˳��,step[i]Ϊ 0xff��ʾ����
	uint8_t enable;         //����/��ֹѲ�ع���
	uint8_t enable_audio;   //�Ƿ�����Ԥ��,0-��Ԥ��,1-Ԥ��
	uint8_t switch_time;    //�л�ʱ��(��)
	uint8_t res[1];         //����
}sdk_tour_t;


/*
 * VO�󶨶���
 * sdk_msg_t.chann ��ʾ����
 */
typedef struct sdk_vo_binding_s {

	uint8_t mode;        //����ģʽ,0-1����,1-4����,2-6����,3-8����,4-9����,5-16����,6-25����,7-36����,0xff:�����
	uint8_t win_num;     //���ڸ���
	uint8_t res[2];      //����
	uint8_t windows[MAX_WINDOWS_NUM];//��������;

}sdk_vo_binding_t;

/*
 * ���ڽ�������Ļ����
 */
typedef struct sdk_win_s {
	uint8_t valid;          //valid: 0��ʾ����ƵԴ
	uint8_t action;
	uint8_t res[1];         //����
	uint8_t win_no;
	uint8_t enc_name[48];
	uint8_t enc_chn;		//������ͨ���� �������õ�
	uint8_t level;			//�������� �������õ�
	uint8_t url[192];       //��ƵԴURL
}sdk_win_t;

typedef struct sdk_screen_s {
	uint8_t valid;                 //valid: 0��ʾ��ʾ������ֹ
	uint8_t mode;                  //����ģʽ,0:1����,1:4����,2:6����,3:8����,4:9����,5:16����,0xff:�����
	uint8_t res[1];                //����
	uint8_t count;
	sdk_win_t win[MAX_WINDOWS_NUM];//sdk_win_t
}sdk_screen_t;
/*
 *��Ƶ����
 */
typedef struct sdk_audio_cfg_s {

	uint8_t encode_type;        //�������� 1: G711A
	uint8_t samples;            //����Ƶ�� 0: 8000, 
	uint8_t bits;               //λ��     1: 16bit, 
	uint8_t channels;           //ͨ����

	uint8_t bufsize;            //�����С,��֡Ϊ��λ
	uint8_t resample;           //0 �޲��� 2 2->1 4 4->1 6 6->1
	uint16_t sample_per_frm;     //ÿһ֡���������
}sdk_audio_cfg_t;


/*
 * GUI��ѯ�豸�б�ʱʹ��
 */
typedef enum _MANUFACT_TYPE{
	MANUFACT_JXJ     = 0x00    /* JXJ�豸 */
		,MANUFACT_RTSP_CH = 0x01    /* ��ͨ��������ָ��2��RTSP URL ֱ�Ӵ���Ƶ */
		,MANUFACT_ONVIF   = 0x02    /* ONVIF NVT */
		,MANUFACT_RTSP    = 0x03    /* ��׼RTSP URL, ��ʹ��ͨ�����ò��� (�����������豸) */
		,MANUFACT_PRIVATE = 0x04
		,MANUFACT_ONVIF_PRIVATE = 0x05 
		,MANUFACT_ONVIF_MULTISUBNET = 0x06  //����������
}MANUFACT_TYPE_E;



typedef struct sdk_device_s {
	uint8_t   ip_addr[MAX_IP_ADDR_LEN];     //IP
	uint16_t  port;                         //port
	uint8_t  macaddr[MAX_IP_ADDR_LEN];
	uint8_t   dns_en;                       // 1:0:
	uint8_t   device_type;                  //  0:IPC 1: DVR 2:NVR
	uint8_t   chann_num;                    //
	uint8_t   chann_stream_num;             // 1:  2:  3:
	uint8_t   manufacturer;                 // MANUFACT_TYPE_E
	uint8_t   devmantype;                   //
	uint8_t   dns_path[64];                 //
	uint8_t   dst_id[32];                   // 
	uint8_t   index;                        // ������������
	sdk_user_t user;                        //+ 
}sdk_device_t;


typedef struct sdk_private_device_s
{
   uint8_t  ip_addr[MAX_IP_ADDR_LEN] ; //[MAX_IP_ADDR_LEN];     //IP
  uint16_t  port;     
  uint8_t  macaddr[MAX_IP_ADDR_LEN];
  uint8_t  dev_type;                          //  0 ipc   1 nvr  
  uint8_t  protocol;                           // 0   onvif  1  
  //port
  sdk_user_t user;    
} sdk_private_device_t;

/*
 *
 * ͨ�����ã�֧��IP���룩
 */
#if 0
typedef struct sdk_channel_s {
	uint8_t   enable;                        //�Ƿ�����
	uint8_t   is_local;                      //�Ƿ�Ϊ������ƵԴ		1:����; 0:Զ��
	//local vi info
	uint8_t   video_in;                      //������ƵԴ���
	uint8_t   video_format;                  //������ƵԴ�źŸ�ʽ    0��PAL�� 1��NTSC    
	//channel name
	uint8_t   name[MAX_CHANN_NAME_LEN];      //ͨ������
	//net channel info
	sdk_user_t user;                        //Զ���豸�û���+���� 
	uint8_t  chann_no;                      //����Զ���豸ͨ����
	uint8_t  chann_protocol;                //����ͨ������Э�� 0: TCP , 1: UDP
	uint8_t  chann_audio_en:1;              //����ͨ���Ƿ�֧����Ƶ 1: ֧��   0: ��֧��
	uint8_t  chann_win_mode:2;              //Ԥ������ģʽ 0: �Զ�, 1: ������, 2: ������
	uint8_t  chann_bit_res:5;               //����
	uint8_t  chann_byte_res;                //����

	//net device info
	sdk_device_t device;                    //Զ���豸��Ϣ

	//device.manufacturer extern info
	//uint8_t  url0[128];                    //URL0
	//uint8_t  url1[128];                    //URL1
}sdk_channel_t;
#endif

typedef struct sdk_channel_s {
	uint8_t   enable;                        //�Ƿ�����
	uint8_t   name[MAX_CHANN_NAME_LEN];      //ͨ������
	sdk_user_t user;                        //Զ���豸�û���+���� 
	uint8_t  chann_no;                      //����Զ���豸ͨ����
	uint8_t  chann_protocol;                //����ͨ������Э�� 0: TCP , 1: UDP
	uint8_t  chann_win_mode;              //Ԥ������ģʽ 0: �Զ�, 1: ������, 2: ������

	uint8_t   ip_addr[MAX_IP_ADDR_LEN];     //IP
	uint16_t  port;                         //port
	uint8_t   manufacturer;                 // MANUFACT_TYPE_E
	uint8_t  chann_byte_res[5];				//����
	uint8_t  rtsp_main_url[MAX_RTSP_MAINURL_LEN];
	uint8_t  rtsp_sub_url[MAX_RTSP_SUBURL_LEN];
}sdk_channel_t;


typedef struct sdk_resolution_s
{
	uint16_t height;
	uint16_t width;

}sdk_resolution_t;

/*
 * ͨ���������(�ӽṹ��)
 */
typedef struct sdk_av_enc_s {
	uint8_t res_num;                   //�ֱ��ʸ���
	uint8_t resolution_current;   //��ǰ�ֱ�������
	uint8_t resolution;	

	sdk_resolution_t  resolution_all[MAX_RESOLUTION_NUM];


	uint8_t bitrate_type;   //�������� 0--������;   1--������ SDK_CODEC_BR_TYPE_E
	uint8_t pic_quilty;     //��������0-��ã�1-�κã�2-�Ϻã�3-һ�㣬4-�ϲ5-��  
	uint8_t frame_rate;     //����֡��1-25(PAL)/30
	uint8_t gop;            //I ֡���1-200
	uint8_t video_enc;      //��Ƶ�����ʽ0--h264 1--MJPEG 2--JPEG  SDK_CODEC_ENC_TYPE_E
	uint8_t audio_enc;      //���ӱ����ʽ0:G711A
	uint8_t mix_type;       //����Ƶ��: 0, ��Ƶ��: 1.
	uint16_t bitrate;       //�������� 32kbps-16000kbps
	uint8_t level;          //����ȼ���h264: 0--baseline, 1--main, 2--high;
	uint8_t h264_ref_mod; 
}sdk_av_enc_t;

/*
 * �����������(pmsg->extend����)
 */
typedef enum _SDK_ENC_IDX {
	SDK_ENC_IDX_MAIN  = 0
		,SDK_ENC_IDX_SECOND= 1
		,SDK_ENC_IDX_ALL   = 0xFF
}SDK_ENC_IDX_T;
/*
 * ͨ���������
 */

typedef struct sdk_encode_s {
	sdk_av_enc_t main;          //������
	sdk_av_enc_t second;        //������
	sdk_av_enc_t res;           //����
}sdk_encode_t;

/*
	venc 
*/
typedef struct sdk_venc_s
{
	unsigned char channelNo;
	unsigned char encodeType;//0  h264
	unsigned char mainResolution;
	unsigned char mainEncodeMode; //0:  video  1:audio  2:video and audio
	unsigned char mainFrameRate;
	unsigned char mainBiteRate;
	unsigned char subResolution;
	unsigned char subEncodeMode;//0:  video  1:audio  2:video and audio
	unsigned char subBitRate;
	unsigned char subFrameRate;
}sdk_venc_t;

/*
 *
 *��Ƶ������������
 */

typedef struct sdk_overlay_cfg_s {
	uint8_t   enable;                  //�Ƿ���
	uint8_t   max_num;
	uint8_t   res[2];
	uint32_t   mask;                    //bit.0: area[0], bit.1: area[1]
	sdk_rect_t area[MAX_OVERLAY_NUM];   //��������
}sdk_overlay_cfg_t;


typedef struct _sdk_codec_area_zoom_ch_info_s
{
	int is_enable;
	sdk_rect_t area;
}sdk_codec_ch_area_zoom_info_t;


/*
 *
 *TV����
 */
typedef struct sdk_vo_sideSize_s
{
	int top_offset;
	int bottom_offset;
	int left_offset;
	int right_offset;
}sdk_vo_sideSize_t;

/*
 *
 *��ƵOSD����(�ӽṹ��)
 */

typedef struct sdk_osd_info_s {

	sdk_point_t pos;            //λ��
	uint8_t     valid;          // ��ǰ�����Ƿ���Ч
	uint8_t     font;           // ��������
	// [7 6 5 4 - 3 2 1 0]
	// bit[4-7]: display type, 0: time, 1: string, 2 .....
	// bit[0-3]: display format 
	//           sample time format:
	//           bit[2-3], 0: YYYYMMDD, 1: MMDDYYYY, 2: DDMMYYYY
	//           bit[1],   0: '-'       1: '/'
	//           bit[0],   0: 24hour    1: ampm
	uint8_t     format;         // ��ʾ��ʽ
	uint8_t     str_len;        // �ַ�������
	uint8_t     str[MAX_OSD_STR_LEN];//ascii+gb2312�ַ���
}sdk_osd_info_t;


/*
 *
 *��ƵOSD����
 */
typedef struct sdk_osd_cfg_s {
	sdk_osd_info_t  time;        //OSDʱ��
	sdk_osd_info_t  chann_name;  //OSDͨ������
	//  sdk_osd_info_t  vloss;       //����
	uint16_t max_width;
	uint16_t max_height;
	uint8_t  st_info_en;
	uint8_t  res1[3];
	uint8_t  res2[64];

}sdk_osd_cfg_t;



/*
 *
 *ͼ����������
 */
typedef struct sdk_image_attr_s {
	uint8_t brightness;         //����
	uint8_t contrast;           //�Աȶ�
	uint8_t saturation;         //���Ͷ�
	uint8_t hue;                //ɫ��
	uint8_t sharpness;          //���
	uint8_t res[3];
}sdk_image_attr_t;

/*
 *
 *�Զ�ά������
 */
typedef struct sdk_autoMaintain_attr_s {
	uint32_t interval;         //���� 0:never  1:every 2:mon  3:tue 4:wed 5 :thu 6 :fri 7:sat 8:sun
	uint32_t hour;           //ʱ��0-23
	uint8_t res[3];
}sdk_autoMaintain_attr_t;

/*
 *�Զ�ά��
 */
typedef enum _Maintain_Auto
{
	SDK_MAIN_AUTO_NEVER,
	SDK_MAIN_AUTO_EVERY_DAY,
	SDK_MAIN_AUTO_MONDAY,
	SDK_MAIN_AUTO_TUESDAY,
	SDK_MAIN_AUTO_WEDNESDAY,
	SDK_MAIN_AUTO_THURSDAY,
	SDK_MAIN_AUTO_FRIDAY,
	SDK_MAIN_AUTO_STAURDAY,
	SDK_MAIN_AUTO_SUNDAY
}Maintain_Auto;


/*
 * ץ�Ľṹ�嶨��
 */
typedef struct sdk_snap_pic_s {
	uint16_t width;             //���
	uint16_t height;            //�߶�
	uint8_t  encode;            //�����ʽ,JPEG
	uint8_t  quilty;            //ͼ������
	uint8_t  res[2];            //����
}sdk_snap_pic_t;

typedef enum _SDK_DISK_STATUS {
	SDK_DISK_STATUS_DISK_UNMOUNT = 0x00	// δ����
		, SDK_DISK_STATUS_DISK_NOMAL			// ����
		, SDK_DISK_STATUS_DISK_USING			// ����ʹ��
		, SDK_DISK_STATUS_DISK_BUTT
}SDK_DISK_STATUS_E;

/*
 * ������Ϣ�ṹ��
 */
typedef struct sdk_disk_s {
	uint32_t disk_no;       //���̺�
	uint32_t disk_type;     //�������ͣ�0:SATA��1:USB��2:ISCSI; 3:NFS��
	uint32_t status;        //����״̬ SDK_DISK_STATUS_E
	uint32_t total_size;    //��������(MB)
	uint32_t free_size;     //��������(MB)
	uint32_t is_backup;     //�Ƿ񱸷ݴ��� 0:¼����; 1:������
	uint32_t is_raid;       //�Ƿ�raid //�����ĸ�����
}sdk_disk_t;

//����������Ϣ����

//����Ӳ�̽ṹ����


/*
 * ¼��������ӽṹ�壩
 */
typedef struct sdk_record_sched_s {
	uint8_t is_allday;                              //�Ƿ�ȫ��¼��
	uint8_t record_time_num;                // ¼���ʱ�������
	uint8_t res[2];                                 //����
	sdk_sched_time_t sched_time[MAX_TIME_SEG_NUM];  //����ʱ���
}sdk_record_sched_t;

/*
 * ¼�����
 */
typedef struct sdk_record_cfg_s {
	uint8_t enable;                                //������ʱ¼��
	uint8_t res[3];                                 //����
	sdk_record_sched_t record_sched[MAX_WEEK_NUM];  //����ʱ���(0:������; 1:����һ,2:���ڶ�,... ,6:������)
	uint32_t pre_record_time;                       //Ԥ¼ʱ��
	uint32_t record_duration_time;                  //¼����ʱ��
	uint8_t  enable_redundancy;                     //�Ƿ����౸��
	uint8_t  enable_audio;                          //�Ƿ�¼����Ƶ
	uint8_t  res2[2];                                //����

}sdk_record_cfg_t;



/*
 * ¼���¼����
 */
typedef struct sdk_record_item_s {
	uint8_t item_name[MAX_RECORD_ITEM_LEN]; //��¼����
	uint32_t item_handle[MAX_STOR_FRAGMENT_LEN];   //sizeof(stor_fragment_t)+6��res
	sdk_time_t start_time;                  //��ʼʱ��
	sdk_time_t stop_time;                   //����ʱ��
	uint32_t item_size;                     //���ݴ�С
	uint8_t is_locked;                      //�Ƿ�����
	uint8_t record_type;                    //¼������
	uint8_t res[2];                         //����
	// card no;
}sdk_record_item_t;

/*
 * ¼���ѯ����
 */
typedef struct sdk_record_cond_s {
	uint8_t is_locked;              //����״̬
	uint8_t record_type;            //¼������
	uint8_t res[2];                 //����
	sdk_time_t start_time;          //��ʼʱ��
	sdk_time_t stop_time;           //����ʱ��
	// card no;    
}sdk_record_cond_t;

/*************LSL20130327*********************/

typedef struct record_search_file_t
{
	//¼���ļ���Ϣ 
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
/**********************************/

/*
 *
 * �طſ���������
 */


typedef enum _SDK_PB_GROUP_CONTROL {
	SDK_PB_CONTROL_ONNE  = 0x00 	//
		, SDK_PB_CONTROL_PAUSE  		// ��ͣ
		, SDK_PB_CONTROL_SETP          	// ��֡��
		, SDK_PB_CONTROL_NORMAL        	// ����
		, SDK_PB_CONTROL_DRAG          	// ��ק
		, SDK_PB_CONTROL_FORWARD       	// ǰ��
		, SDK_PB_CONTROL_BACKWARD      	// ����
		, SDK_PB_CONTROL_QUERY_TIME		// ��ѯ��ǰ������֡��ʱ�䣬��λ��
		, SDK_PB_CONTROL_FULLSCREEN
		, SDK_PB_CONTROL_BUTT
}SDK_PB_GROUP_CONTROL_E;

/*
 *
 * ǰ�������ٶ�ö�� [--------- | ---- -> -> ----]
 */
typedef enum _SDK_PB_GROUP_CONTROL_FORWARD {
	SDK_PB_CONTROL_FW_NORMAL = 0x00  				// ����
		, SDK_PB_CONTROL_FF_1X     						// 1����� (FF-fast forward-��ǰ���)
		, SDK_PB_CONTROL_FF_2X    						// 2�����
		, SDK_PB_CONTROL_FF_4X         					// 4�����
		, SDK_PB_CONTROL_FF_8X							// 8�����
		, SDK_PB_CONTROL_FF_16X							// 16�����
		, SDK_PB_CONTROL_SF_1_2X						// 1������ (SF-slow forward-��ǰ����)
		, SDK_PB_CONTROL_SF_1_4X						// 2������
		, SDK_PB_CONTROL_SF_1_8X						// 4������
		, SDK_PB_CONTROL_SF_1_16X						// 8������

}SDK_PB_GROUP_CONTROL_FORWARD_E;

/*
 *
 * ���˲����ٶ�ö�� [--- <- <- ---- | ----------]
 */
typedef enum _SDK_PB_GROUP_CONTROL_BACKWARD {
	SDK_PB_CONTROL_BW_NORMAL = 0x00  				// ����
		, SDK_PB_CONTROL_FB_1X     						// 1������ (FB-fast backward-�����)
		, SDK_PB_CONTROL_FB_2X    						// 2������
		, SDK_PB_CONTROL_FB_4X         					// 4������
		, SDK_PB_CONTROL_FB_8X							// 8������
		, SDK_PB_CONTROL_FB_16X							// 16������
		, SDK_PB_CONTROL_SB_1_2X						// 1������ (SB-slow backward-�������)
		, SDK_PB_CONTROL_SB_1_4X						// 2������
		, SDK_PB_CONTROL_SB_1_8X						// 4������
		, SDK_PB_CONTROL_SB_1_16X						// 8������

}SDK_PB_GROUP_CONTROL_BACKWARD_E;


/*
 * �ط�ͨ���鶨��
 */
#if 0
typedef struct sdk_pb_group_s {
	sdk_time_t start_time;             //��ʼʱ��
	sdk_time_t stop_time;              //����ʱ��
	uint32_t main_chann;               //��ͨ����
	uint8_t chann_mask[MAX_CHANN_NUM];//ͨ�����루��·�ط�ʱ��
}sdk_pb_group_t;
#else
typedef struct sdk_pb_group_s {
	record_search_file_t record_file_info;
	uint32_t main_chann;               //��ͨ����
	uint8_t chann_mask[MAX_CHANN_NUM];//ͨ�����루��·�ط�ʱ��
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
}sdk_pb_group_t;


#endif


/* ---------------------------------------*/
// ntp
// ddns
// wifi

typedef struct sdk_wifi_ap_s
{
	uint8_t essid[MAX_DEV_ID_LEN];		//���������
	uint32_t encrypt_type;				//��������0:NONE  1:WPA  2:WPA2 3:WEP
	uint32_t auth_mode;					//��֤��ʽ0:NONE  1:EAP 2:PSK 3:OPEN 4:SHARED 
	uint32_t secret_key_type;			//��Կ����ʽ 0:NONE  1:AES 2:TKIP ֻ��Ӧ�ڼ�������ΪWPA/WPA2�����
	uint32_t quality;					//�ź����� 0-100
	uint32_t bit_rate;					//��������
}sdk_wifi_ap_t;

typedef struct sdk_wifi_ap_set_s
{
	uint32_t count;							//��������wifi ����
	sdk_wifi_ap_t wifi_ap[MAX_WIFI_AP_NUM]; //
}sdk_wifi_ap_set_t;



// email
// ftp
/* ---------------------------------------*/


/*
 *
 *�豸��Ϣ���豸����ʱ�ã��磺�������ߣ�
 */

typedef struct sdk_device_info_s {
	/*------ �豸������Ϣ ------*/
	sdk_net_mng_cfg_t   net_mng;        //��������
	sdk_eth_cfg_t   eth_cfg;        //eth0
	sdk_sys_cfg_t   sys_cfg;        //ϵͳ����
	/*---- ϵͳ����ʱ��Ϣ  ----*/
	//��Ҫ��������
}sdk_device_info_t;

/*----------------- �������ýṹ�嶨�� -----------------*/

/*
 * ID
 */
typedef enum _SDK_PTZ_MSG_ID {
	SDK_PTZ_MSG_UP_START = 0x001
		, SDK_PTZ_MSG_UP_STOP
		, SDK_PTZ_MSG_DOWN_START
		, SDK_PTZ_MSG_DOWN_STOP
		, SDK_PTZ_MSG_LEFT_START
		, SDK_PTZ_MSG_LEFT_STOP
		, SDK_PTZ_MSG_RIGHT_START    
		, SDK_PTZ_MSG_RIGHT_STOP
		, SDK_PTZ_MSG_LEFT_UP_START
		, SDK_PTZ_MSG_LEFT_UP_STOP
		, SDK_PTZ_MSG_RIGHT_UP_START
		, SDK_PTZ_MSG_RIGHT_UP_STOP
		, SDK_PTZ_MSG_LEFT_DOWN_START
		, SDK_PTZ_MSG_LEFT_DOWN_STOP
		, SDK_PTZ_MSG_RIGHT_DOWN_START
		, SDK_PTZ_MSG_RITHT_DOWN_STOP
		, SDK_PTZ_MSG_PRESET_SET
		, SDK_PTZ_MSG_PRESET_CALL
		, SDK_PTZ_MSG_PRESET_DEL
		, SDK_PTZ_MSG_ZOOM_ADD_START
		, SDK_PTZ_MSG_ZOOM_ADD_STOP
		, SDK_PTZ_MSG_ZOOM_SUB_START
		, SDK_PTZ_MSG_ZOOM_SUB_STOP
		, SDK_PTZ_MSG_FOCUS_ADD_START
		, SDK_PTZ_MSG_FOCUS_ADD_STOP
		, SDK_PTZ_MSG_FOCUS_SUB_START
		, SDK_PTZ_MSG_FOCUS_SUB_STOP
		, SDK_PTZ_MSG_IRIS_ADD_START
		, SDK_PTZ_MSG_IRIS_ADD_STOP
		, SDK_PTZ_MSG_IRIS_SUB_START
		, SDK_PTZ_MSG_IRIS_SUB_STOP
		, SDK_PTZ_MSG_GOTO_ZERO_PAN
		, SDK_PTZ_MSG_FLIP_180
		, SDK_PTZ_MSG_SET_PATTERN_START
		, SDK_PTZ_MSG_SET_PATTERN_STOP
		, SDK_PTZ_MSG_RUN_PATTERN
		, SDK_PTZ_MSG_SET_AUXILIARY
		, SDK_PTZ_MSG_CLEAR_AUXILIARY
		, SDK_PTZ_MSG_AUTO_SCAN_START
		, SDK_PTZ_MSG_AUTO_SCAN_STOP
		, SDK_PTZ_MSG_RANDOM_SCAN_START
		, SDK_PTZ_MSG_RANDOM_SCAN_STOP
		, SDK_PTZ_MSG_LEFT_OFFSET
		, SDK_PTZ_MSG_RIGHT_OFFSET
		, SDK_PTZ_MSG_DOWN_OFFSET
		, SDK_PTZ_MSG_UP_OFFSET
		, SDK_PTZ_MSG_ZOOM_MULTIPLE
		, SDK_PTZ_MSG_POINT_CENTER
		, SDK_PTZ_MSG_VIEW_CENTER
		, SDK_PTZ_MSG_BUTT
}SDK_PTZ_MSG_ID_E;
/*
 * 
 */
typedef enum _SDK_PTZ_PROTOCOL {
	SDK_PTZ_PELCO_D = 0x01
		, SDK_PTZ_PELCO_P
		, SDK_PTZ_BUTT    = 0x20
}SDK_PTZ_PROTOCOL_E;


typedef enum _SDK_PTZ_OP_TYPE {
	SDK_PTZ_TYPE_NONE = 0x00
		, SDK_PTZ_TYPE_PRESET		// Ԥ��λ
		, SDK_PTZ_TYPE_CRUISE		// Ѳ��
		, SDK_PTZ_TYPE_BUTT
}SDK_PTZ_OP_TYPE_E;

/*
 *  ������������
 */
typedef struct sdk_alarm_handle_s {

	uint8_t record_mask[MAX_CHANN_NUM];   //¼��ͨ������
	uint8_t snap_mask[MAX_CHANN_NUM];     //ץ��ͨ������
	uint8_t alarm_out_mask[MAX_CHANN_NUM];//�����������      
	uint8_t ptz_type[MAX_CHANN_NUM];      //������̨��������(Ԥ��λ/Ѳ��)	SDK_PTZ_OP_TYPE_E
	uint8_t ptz_param[MAX_CHANN_NUM];     //������̨����(Ԥ��λ�ţ�Ѳ����)
	uint8_t res_mask[MAX_CHANN_NUM];

	uint8_t  record_enable;
	uint8_t  record_time;                 //¼����ʱʱ��
	uint8_t  snap_enable;
	uint8_t  snap_interval;               //ץ��ʱ����(��Ч)

	uint8_t  snap_num;                    //����ץ������
	uint8_t  beep_enable;                 //�Ƿ������
	uint8_t  beep_time;                   //����ʱ��
	uint8_t  ptz_enable;

	uint8_t  alarm_out_enable;
	uint8_t  alarm_out_time;              //�������ʱ��
	uint8_t  res[2+4];                    //email, ftp, 3g;
}sdk_alarm_handle_t;

/*
 * �������루IO����������
 */
typedef struct sdk_alarm_in_cfg_s {
	uint8_t name[MAX_ALARM_IN_NAME_LEN];                        //������������
	uint8_t type;                                               //�����������ͣ�1������(Ĭ��)��0������
	uint8_t enable;                                             //��������
	uint8_t res[2];                                             //����
	sdk_sched_time_t sched_time[MAX_WEEK_NUM][MAX_TIME_SEG_NUM];//����ʱ���
	sdk_alarm_handle_t alarm_handle;                            //��������
}sdk_alarm_in_cfg_t;


/*
 * ��Ƶ�ƶ��������
 */
typedef enum _SDK_VDA_MOD_E {
	SDK_VDA_MD_MOD = 0
		, SDK_VDA_OD_MOD = 1
}SDK_VDA_MOD_E;

typedef struct sdk_vda_codec_cfg_s
{
	uint8_t enable;                                             //��������
	uint8_t sensitive;                                          //������(0[���������]----6[���])
	uint8_t mode;                                             	/* 0:MD �ƶ� 1:OD �ڵ� */
	uint8_t res;
	uint32_t mask;												//��λ
	sdk_rect_t area[MAX_MOTION_NUM];                            //����
}sdk_vda_codec_cfg_t;

#if 0
typedef struct sdk_motion_cfg_v2_s {
	sdk_vda_codec_cfg_t codec_vda_cfg;						    			
	sdk_sched_time_t sched_time[MAX_WEEK_NUM][MAX_TIME_SEG_NUM];//?????
	sdk_alarm_handle_t alarm_handle;                            //????
}sdk_motion_cfg_v2_t;
#endif
typedef struct sdk_motion_cfg_v2_s {
	uint8_t enable;
	uint8_t beep_enable;
	uint8_t beep_time;
	uint8_t record_enable;
	uint8_t record_time;
	uint8_t smtp_enable;
	uint8_t ftp_enable;
	uint8_t sensitivity;
	uint32_t blockstatus[MAX_BLOCK_ROW];
}sdk_motion_cfg_v2_t;

typedef struct sdk_motion_cfg_s {
	//uint8_t scope[18][22];                                    //��Ҫȷ��
	uint8_t enable;                                             //��������
	uint8_t sensitive;                                          //������(0[���������]----6[���])
	uint8_t res[2];                                             //����
	uint32_t mask;							// ��λ
	sdk_rect_t area[MAX_MOTION_NUM];                            //����
	sdk_sched_time_t sched_time[MAX_WEEK_NUM][MAX_TIME_SEG_NUM];//����ʱ���
	sdk_alarm_handle_t alarm_handle;                            //��������
}sdk_motion_cfg_t;

/*
 * ��Ƶ�ڵ��������
 */
typedef struct sdk_hide_cfg_s {
	uint8_t enable;                                         //��������
	uint8_t sensitive;                                          //������(0[���������]----6[���])
	uint8_t res[2];                                             //����
	uint32_t mask;												 // ��λ
	sdk_rect_t area[MAX_MOTION_NUM];                            //����
	sdk_sched_time_t sched_time[MAX_WEEK_NUM][MAX_TIME_SEG_NUM];//����ʱ���
	sdk_alarm_handle_t alarm_handle;                            //��������
}sdk_hide_cfg_t;

/*
 * ��Ƶ��ʧ�������
 */
typedef struct sdk_lost_cfg_s {
	uint8_t enable;                                             //��������
	uint8_t res[3];                                             //����
	sdk_sched_time_t sched_time[MAX_WEEK_NUM][MAX_TIME_SEG_NUM];//����ʱ���
	sdk_alarm_handle_t alarm_handle;                            //��������
}sdk_lost_cfg_t;


/*
 * ¼�����
 */
typedef struct sdk_manual_record_s {
	uint8_t manual_record[MAX_CHANN_NUM];	// �ֶ�¼��
	uint8_t stop_record[MAX_CHANN_NUM];		// ��ֹ¼��
	uint8_t res[MAX_CHANN_NUM];				// ����λ
}sdk_manual_record_t;

/*
 * �ֶ�����(ֹͣ)����������
 */
typedef struct sdk_manual_alarmin_s {
	uint8_t enable_alarmin[MAX_ALARM_IN_NUM];	// 0:ֹͣ; 1:����(Ĭ��ȫ����)
	uint8_t res[MAX_ALARM_IN_NUM];				// ����λ
}sdk_manual_alarmin_t;

/*
 * �ֶ�����(ֹͣ)�������
 */
typedef struct sdk_manual_alarmout_s {
	uint8_t enable_alarmout[MAX_ALARM_OUT_NUM];	// 0:ֹͣ(Ĭ��ȫֹͣ); 1:����
	uint8_t res[MAX_ALARM_OUT_NUM];				// ����λ
}sdk_manual_alarmout_t;


/*
 * ¼�񱸷�
 */
typedef enum _SDK_BACKUP_OP {
	SDK_BACKUP_START		= 0x001		//sdk_record_backup_t
		, SDK_BACKUP_PROGRESS				//pmsg->chan:���ݽ���
		, SDK_BACKUP_BUTT
}SDK_BACKUP_OP_E;

/*
 * ��������ļ���ʽ
 */
typedef enum _SDK_BACKUP_FMT {
	SDK_BACKUP_FMT_JAV  = 0     /* jav */
		,SDK_BACKUP_FMT_AVI  = 1     /* avi */
}SDK_BACKUP_FMT_E;

typedef struct sdk_record_handle_s {
	uint32_t  	item_handle[MAX_STOR_FRAGMENT_LEN];
	uint32_t 	item_size;				//�δ�С
	sdk_time_t 	start_time;          	//��ʼʱ��
	sdk_time_t 	end_time;           	//����ʱ��
	uint8_t  	res[4];					//����
}sdk_record_handle_t;

typedef struct sdk_record_backup_s {
	//sdk_record_handle_t item_arr[MAX_BACKUP_ITEM];
	record_search_file_t record_file_info;
	uint8_t item_num;				//ʵ�ʱ��ݶ���
	uint8_t record_type;            //¼������
	uint8_t out_fmt;                //��������ļ���ʽ  SDK_BACKUP_FMT_E
	uint8_t res[1];					//����
}sdk_record_backup_t;


/*
 * �ر�ϵͳ
 */
typedef enum _SDK_CLOSE_SYS_OP {
	SDK_CLOSE_SYS_SHUTDOWN	= 0x001		//�ػ�
		, SDK_CLOSE_SYS_REBOOT					//����
		, SDK_COLSE_SYS_LOGOUT
		, SDK_CLOSE_SYS_BUTT
}SDK_CLOSE_SYS_OP_E;

/*
 * ��Ƶ����
 */
typedef enum _SDK_AUDIO_CONTROL_OP {
	SDK_AUDIO_CONTROL_OPEN	= 0x001		//����
		, SDK_AUDIO_CONTROL_MUTE				//����
		, SDK_AUDIO_CONTROL_TALK				//�Խ�
		, SDK_AUDIO_CONTROL_SPECIAL_CMD			//��������(GUI֪ͨ���ؽ���طŽ��棬pmsg->extend:1����; 0:�˳�)

		, SDK_AUDIO_CONTROL_BUTT
}SDK_AUDIO_CONTROL_OP_E;



/*
 * ��������
 */

#define 	MAX_DDNS_USER_LEN   	64				// DDNS�û�����󳤶�
#define 	MAX_DDNS_PWD_LEN    	32				// DDNS������󳤶�
#define 	MAX_DDNS_NAME_LEN   	128				// DDNS������󳤶�

typedef enum _SDK_DDNS_TYPE {
	SDK_DDNS_TYPE_DYNDNS	= 0x00		// Dyndns
		, SDK_DDNS_TYPE_3322				// 3322
		, SDK_DDNS_TYPE_ORAY				// Oray

		, SDK_DDNS_TYPE_BUTT
}SDK_DDNS_TYPE_E;

typedef enum _SDK_DDNS_ORAY_USERTYPE {
	SDK_ORAY_USERTYPE_COMMON	= 0x01	// ��ͨ�û�
		, SDK_ORAY_USERTYPE_EXPERT			// רҵ�û�

		, SDK_ORAY_USERTYPE_BUTT
}SDK_DDNS_ORAY_USERTYPE;

typedef struct sdk_ddns_cfg_s {
	uint8_t enable;						// DDNS 0-1-
	uint8_t type;						// DDNSSDK_DDNS_TYPE_E
	uint8_t user_type;					// SDK_DDNS_ORAY_USERTYPE ()

	uint32_t interval;					// (:)
	uint32_t port;						// DDNS
	uint8_t server[MAX_DDNS_NAME_LEN];	// DDNS(IP)
	uint8_t user[MAX_DDNS_USER_LEN];	// 
	uint8_t pwd[MAX_DDNS_PWD_LEN];		// 
	uint8_t domain[MAX_DDNS_NAME_LEN];	// (dyndns,domain',')
	uint8_t client_ip[MAX_IP_ADDR_LEN];	// IP
}sdk_ddns_cfg_t;


/*
 * ?????
 */

typedef enum SDK_VIDEO_CAP_RESOLUTION {
	SDK_VIDEO_CAP_RESOLUTION_QCIF      	= 0x1				//176*144  n176*120
		, SDK_VIDEO_CAP_RESOLUTION_CIF			= 0x2				//352*288  n352*240
		, SDK_VIDEO_CAP_RESOLUTION_HD1			= 0x4				//704*288  n704*240
		, SDK_VIDEO_CAP_RESOLUTION_D1			= 0x8				//704*576  n704*480
		, SDK_VIDEO_CAP_RESOLUTION_960H    		= 0x10				//960x576
		, SDK_VIDEO_CAP_RESOLUTION_QQVGA		= 0x20				//160*112
		, SDK_VIDEO_CAP_RESOLUTION_QVGA			= 0x40				//320*240
		, SDK_VIDEO_CAP_RESOLUTION_VGA			= 0x80				//640*480
		, SDK_VIDEO_CAP_RESOLUTION_SVGA			= 0x100				//800*600
		, SDK_VIDEO_CAP_RESOLUTION_UXGA			= 0x200				//1600*1200
		, SDK_VIDEO_CAP_RESOLUTION_720P			= 0x400				//1280*720
		, SDK_VIDEO_CAP_RESOLUTION_960			= 0x800				//1280*960
		, SDK_VIDEO_CAP_RESOLUTION_1080P		= 0x1000			//1920*1080
}SDK_VIDEO_CAP_RESOLUTION_E;

typedef struct device_chan_capability_s {
	uint32_t   res_cap[MAX_STREAM_NUM];			// SDK_VIDEO_CAP_RESOLUTION_E
	uint32_t   max_frame_rate[MAX_STREAM_NUM]; 	// �������֧��֡��
}device_chan_capability_t;

typedef struct sdk_device_capability_s {
	uint8_t    screen_num;                     			// ��Ļ������3531������3521һ����
	uint8_t    eth_num;                        			// ���ڸ������豸����Ϊxx_e2ʱ����������һ����
	uint8_t    res[2];                         			// ����
	device_chan_capability_t ch_cap[MAX_CHANN_NUM];
}sdk_device_capability_t;


/* 
 * ��ȡ�Զ��豸��ý��URL (MAIN -> PUA)
 */
typedef struct sdk_media_url_s {
	uint8_t    type;        /* 0:real av */
	uint8_t    st_ch;       /* 0:main, 1:second */
	uint8_t    trans;       /* 0: udp, 1: tcp, 3: rtsp 4: http*/
	uint8_t    proto;       /* 0: Unicast, 1: multicast */
	uint8_t    ip[40];      /* requestor ip */
	int8_t     b_time[16];  /* record fmt:YYYYMMDDhhmmss */
	int8_t     e_time[16];  /* record fmt:YYYYMMDDhhmmss */
	int8_t     url[256];    /* url */
}sdk_media_url_t;


/*
 * ��̨�������� (MAIN -> PUA)
 */
typedef struct sdk_ptz_ctl_s {
	uint8_t    cmd;     /* SDK_PTZ_MSG_ID_E */
	uint8_t    speed;   /* 1 - 100 */
	uint8_t    res;     /* res */
	uint8_t    val;     /* preset, track ...  */
	uint8_t    name[32];/* preset, track name */
}sdk_ptz_ctl_t;


typedef struct sdk_28181_conf_t
{
	int enable;
	char server_ip[32];
	int server_port;
	char server_id[64];
	char device_id[64];
	char channel_nvr_id[36][64];
	char pwd[32];
	char alarm_id[32];
}sdk_28181_conf_t;

typedef struct _sdk_ntp_conf_t
{
	signed char time_zone;
	char ntp_server[128];
	signed char enable;
	char interval;		/* ʱ����*/
	char date_format;	/* ���ڸ�ʽ:	������*/
	char date_separator;	/* ���ڷָ���"-" */
	char time_format;	/* ʱ���ʽ: 24 Сʱ, 12 Сʱ*/
	int port;			/* NTP�˿ں� */
}sdk_ntp_conf_t;


typedef struct _sdk_email_conf_t
{	
	char smtp_server[128];
	char user[32];
	char passwd[32];
	char receiver[32];
	char sender[32];
	char theme[32];
	uint8_t anonymity;
	uint8_t file_enable;	
	uint8_t encryption_type;
	uint16_t interval;
	uint8_t health_enable;
	uint16_t health_interval;
	uint16_t port;
	uint8_t email_enable;
}sdk_email_conf_t;

typedef enum _P2P_TYPE
{	
	P2P_FREE_IP = 0x00,
	P2P_DANALE
}P2P_TYPE;

typedef struct _sdk_p2p_conf_t
{	
	uint8_t P2pEn;    // P2Pʹ��
	char SerialNum[64]; // ���к�
	char AndroidAppUrl[128];// ��׿APP�����ص�ַ
	char IosAppUrl[128];       //ƻ��APP�����ص�ַ
}sdk_p2p_conf_t;

typedef struct _sdk_zoom_t
{
	int x;
	int y;
	int w;
	int h;
	int ch;
	int full_screen;
}sdk_zoom_t;


typedef struct _sdk_winswitch_t
{
	int win_num;
	int ch[4];
	int fullscreen;
}sdk_winswitch_t;

typedef struct sdk_playback_t
{
	int s32X;
	int s32Y;
	int u32Width;
	int u32Height;
	int  bMulti;
}sdk_playback_t;

typedef enum _ZOOM_OP
{
	SDK_MAIN_OP_ZOOMSTART,
	SDK_MAIN_OP_ZOOMSTOP,
	SDK_MAIN_OP_ZOOMMOVE,
}ZOOM_OP;
/* ---------------------------------*/



typedef struct _sdk_ipc_devinfo_t
{
	char Manufacturer[MAX_STRING_LEN];
	char Model[MAX_STRING_LEN];
	char FirmwareVersion[MAX_STRING_LEN];
	char SerialNumber[MAX_STRING_LEN];
	char HardwareId[MAX_STRING_LEN];
}sdk_ipc_devinfo_t;

typedef struct _sdk_modify_ip_t
{	
	uint16_t port;
	uint8_t old_ip_addr[MAX_IP_ADDR_LEN];//old  IP ADDR
	uint8_t new_ip_addr[MAX_IP_ADDR_LEN];//new IP ADDR
	uint8_t  macaddr[MAX_IP_ADDR_LEN];
	uint8_t mask[MAX_IP_ADDR_LEN];   //IP MASK
	uint8_t gateway[MAX_IP_ADDR_LEN];//����
	uint8_t user_name[MAX_USER_NAME_LEN];
	uint8_t user_pwd[MAX_PASSWD_LEN];
	uint8_t index ;	
}sdk_modify_ip;

typedef struct sdk_network_s
{
  char ip_addr[MAX_IP_ADDR_LEN];
  char netmask[MAX_IP_ADDR_LEN];
  char gateway[MAX_IP_ADDR_LEN];
  char macaddr[MAX_IP_ADDR_LEN];

}sdk_network_t;

typedef struct sdk_channel_define_s
{
	unsigned char IpChannelEnable[MAX_CHANN_NUM];
	unsigned char AhdChannelEnable[MAX_CHANN_NUM];
}sdk_channel_define_t;

typedef struct _sdk_poll_t
{
	uint8_t enable;
	uint8_t time;
	uint8_t mode;
}sdk_poll_t;

 typedef enum _Ad_Hoc_Network_status_
{
 STATUS_INIT = 0,
 STATUS_RUNNING,
 STATUS_END
}Ad_Hoc_Network_status;
typedef struct
{
	char bFtpEnable;					///ʹ�ܿ���
	char servier_ip[40+1]; ///��������ַ
	char username[32]; 			///�û���
	char password[32]; 		///����
	char foldername[128];		///�ļ��е�ַ
	int port; 							///��������ַ
} sdk_ftp_config;


typedef struct  sdk_stream_info_s
{
	unsigned int MainRecvBitRate;
	unsigned int SubRecvBitRate;
	unsigned int Height;
	unsigned int Width;
	unsigned int FrameRate;
}sdk_stream_info_t ;

/*�ƶ����������*/
typedef struct sdk_MotionDetectionAnalytics_s{
    int    Sensitivity;
    int    Row;
    int    Column;
}sdk_MotionDetectionAnalytics_t;


typedef struct sdk_MotionDetectionRule_s{
	int  ararmOnDelay;
	int  ararmOffDelay;
	int  activeCell[32];
}sdk_MotionDetectionRule_t;











#ifdef __cplusplus
}
#endif

#endif //__sdk_struct_h__

