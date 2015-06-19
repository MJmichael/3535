/*
 * =====================================================================================
 *
 *       Filename:  main.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20110523 005641
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =====================================================================================
 */
#ifndef __main_h__
#define __main_h__

#if defined (__cplusplus)
extern "C" {
#endif

/*
 * ȫ���������Ͷ���
 */
#include "sdk_global.h"

/*
 * ���������� ���ݽṹ����
 */
#include "sdk_struct.h"

/*
 * ����Э�鼰�ӿڶ���
 */
//#include "sdk_netlib.h"

/*----------- ������ϢID���� -----------*/

/*
 * ��ϢID��ѭ"ֻ����׷���޸ģ�������ı�ԭ����
 * ����ģ��ʹ����ϢID��Ϊ�����洢��ԪID���޸���ϢID��Ӱ����������ļ�.
 */
typedef enum _SDK_MAIN_MSG_ID{
      SDK_MAIN_MSG_VERSION = 0x001    //    	�汾��Ϣ    sdk_version_t
    , SDK_MAIN_MSG_STATUS             //		ϵͳ״̬    sdk_status_t
    , SDK_MAIN_MSG_PARAM_DEFAULT      //		Ĭ�ϲ���    sdk_default_param_t, SDK_PARAM_MASK_ID_E
    , SDK_MAIN_MSG_UPGRAD             //		����        SDK_UPGRAD_OP_E
    , SDK_MAIN_MSG_USER               //        �û�����    SDK_USER_OP_E
    , SDK_MAIN_MSG_LOG                //		��־����    SDK_LOG_OP_E
    , SDK_MAIN_MSG_SYS_CFG            //		ϵͳ����    sdk_sys_cfg_t
    , SDK_MAIN_MSG_NET_MNG_CFG        //		��������    sdk_net_mng_cfg_t
    , SDK_MAIN_MSG_PTZ_CFG            //     	��̨����    sdk_ptz_param_t
    , SDK_MAIN_MSG_PTZ_CONTROL        //     	��̨����    SDK_PTZ_MSG_ID_E
    , SDK_MAIN_MSG_CRUISE_CFG         //     	Ѳ������    sdk_cruise_param_t
    , SDK_MAIN_MSG_PREVIEW_CFG        //		����Ԥ������ sdk_preview_t
    , SDK_MAIN_MSG_VO_BINDING         //		��Ƶ�����(Ԥ��/�ط�) sdk_vo_binding_t
    , SDK_MAIN_MSG_PB_GROUP_CREATE    //		�������ػط��� sdk_pb_group_t 
    , SDK_MAIN_MSG_PB_GROUP_DESTORY   //		���ٱ��ػط��� 
    , SDK_MAIN_MSG_PB_GROUP_CONTROL   //		���Ʊ��ػط��� SDK_PB_GROUP_CONTROL_E
    , SDK_MAIN_MSG_CHANN_CFG          //		ͨ������       sdk_channel_t
    , SDK_MAIN_MSG_ENCODE_CFG         //		��������       sdk_encode_t 
    , SDK_MAIN_MSG_RECORD_CFG         //		¼������       sdk_record_cfg_t
    , SDK_MAIN_MSG_RECORD_QUERY       //		¼���ѯ       sdk_record_item_t, sdk_record_cond_t
    , SDK_MAIN_MSG_MOTION_CFG         //    	��Ƶ�ƶ�����   sdk_motion_cfg_v2_t
    , SDK_MAIN_MSG_ALARM_IN_CFG       //		�ⲿ������������sdk_alarm_in_cfg_t
    , SDK_MAIN_MSG_HIDE_CFG           //		��Ƶ�ڱα�������sdk_hide_cfg_t
    , SDK_MAIN_MSG_LOST_CFG           //		��Ƶ��ʧ����   sdk_lost_cfg_t
    , SDK_MAIN_MSG_OSD_CFG            //		OSD����       sdk_osd_cfg_t
    , SDK_MAIN_MSG_COMM_CFG			  //    	��������       sdk_comm_cfg_t
    , SDK_MAIN_MSG_OVERLAY_CFG		  //    	�ڵ���������   sdk_overlay_cfg_t
    , SDK_MAIN_MSG_DISK		  		  //		���̹���	pmsg->args:SDK_DISK_OP_E
    , SDK_MAIN_MSG_SYSTIME		  	  //		ϵͳʱ������	  sdk_time_t
    , SDK_MAIN_MSG_SERIAL_CFG		  //		���ڲ�������	  sdk_serial_func_cfg_t
    , SDK_MAIN_MSG_IMAGE_ATTR_CFG     //		ͼ����������   sdk_image_attr_t
    , SDK_MAIN_MSG_TV_CFG         	  //		TV����   sdk_vo_sideSize_t
	, SDK_MAIN_MSG_NOTIFY             //        ֪ͨ�¼�����/ֹͣ args:SDK_EVENT_TYPE_E, chann:ͨ��, extend:����/ֹͣ.
    , SDK_MAIN_MSG_DEVLIST            //        GUI ��ѯ�豸�б� sdk_device_t
    , SDK_MAIN_MSG_MANUAL_REC		  //		�ֶ���(�ر�)¼�� 	sdk_manual_record_t
    , SDK_MAIN_MSG_MANUAL_ALMIN		  //		�ֶ���(�ر�)�������� 	sdk_manual_alarmin_t
    , SDK_MAIN_MSG_MANUAL_ALMOUT	  //		�ֶ���(�ر�)�������  sdk_manual_alarmout_t
    , SDK_MAIN_MSG_RECORD_BACKUP	  //		¼�񱸷�  pmsg->args:SDK_BACKUP_OP_E
    , SDK_MAIN_MSG_CLOSE_SYSTEM		  // 		�ر�ϵͳ  pmsg->args:SDK_CLOSE_SYS_OP_E
    , SDK_MAIN_MSG_AUDIO_CONTROL	  // 		��Ƶ����  args:SDK_AUDIO_CONTROL_OP_E; extend:����/�ر�
    , SDK_MAIN_MSG_PLATFORM_CFG       //        ƽ̨��Ϣ����
    , SDK_MAIN_MSG_CHANGE_REMOTE_IP   //        �ı�Զ���豸��ip sdk_device_t
	, SDK_MAIN_MSG_DDNS_CFG			  //		DDNS���� sdk_ddns_cfg_t
	, SDK_MAIN_MSG_CAPABILITY		  //		�豸��������Ϣ sdk_device_capability_t
	, SDK_MAIN_MSG_NET_LINK_CFG		  //		������������ pmsg->chann = SDK_NET_IDX_E;
	, SDK_MAIN_MSG_UPNP_CFG           //        UPNP ����
	, SDK_MAIN_MSG_SCREEN_CFG         //        screen���� sdk_screen_t
	, SDK_MAIN_MSG_CRUISE_CTL         //        ����Ѳ��     �޶�Ӧ�ṹ�壬ֻ��ID
	, SDK_MAIN_MSG_PRESET_SET         //        Ԥ�õ㼯�� sdk_preset_param_t
	, SDK_MAIN_MSG_PREVIEW_TOUR       //        Ԥ��Ѳ������    sdk_tour_t
	, SDK_MAIN_MSG_28181				// ����28181
	, SDK_MAIN_MSG_NTP				//ntpʱ�����
	, SDK_MAIN_MSG_SMTP				//SMTP����
	, SDK_MAIN_MSG_ZOOM				//
	,SDK_MAIN_MSG_GET_CHANNEL_BITRATE
	,SDK_MAIN_MSG_P2P                           
	,SDK_MAIN_MSG_LOCAT_IMAGE_ATTR_CFG     //	����ͼ����������   sdk_image_attr_t
	,SDK_MAIN_MSG_ROTATE                             //����ͨ������ת    0:0  1:90  2:180  3:270
	, SDK_MAIN_MSG_AUTO_BIND	 
	,SDK_MAIN_MSG_PRESET
	,SDK_MAIN_MSG_ALLPRESETS


	,SDK_MAIN_MSG_CRUISECFG                                      //����ĳ��ͨ��ĳ��Ѳ��·�����е���Ϣ 
	, SDK_MAIN_MSG_PRI_SEARCH
	, SDK_MAIN_MSG_CHL_SWITCH
	 ,SDK_MAIN_MSG_IPC_NETWORK_CFG             //����IPC��IP��ַ
	 ,SDK_MAIN_MSG_IPC_DEVICE_INFO
	  ,SDK_MAIN_MSG_AUTO_MAINTAIN               //������
	  ,SDK_MAIN_MSG_RECORD_QUERY_STATUS  //¼���ѯ״̬       sdk_record_item_t, sdk_record_cond_t
	  ,SDK_MAIN_MSG_GET_P2P_STATUS		//��ȡp2p������״̬
	  ,SDK_MAIN_MSG_SMTP_TEST_STATUS		//��ȡemil������״̬
	  ,SDK_MAIN_MSG_POLL
	  ,SDK_MAIN_MSG_PB_WIN_SWITCH
	  ,SDK_MAIN_MSG_FTP
	  ,SDK_MAIN_MSG_BUTT
	
}SDK_MAIN_MSG_ID_E;

typedef int(*sdk_msg_dispatch_cb)(sdk_msg_t *pmsg);

int net_dispatch(sdk_msg_t *pmsg);
int msg_ptz_dispatch(sdk_msg_t *pmsg);
char *net_msg2main_msg_str(int msg_id);
int mcu_operate(int oper_type, int arg, void *p_arg);
int dm_msg_send(int fd, int id, int arg, int ch, void *data, int size, int timeout);
int main_free_system_resources();

#if defined (__cplusplus)
}
#endif

#endif //__main_h__




