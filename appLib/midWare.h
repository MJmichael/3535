#ifndef __MIDWARE_H__
#define __MIDWARE_H__
/******************************************************
Ŀǰ/appLib���潨��ddnsLib�� ptzLib�� smtpLib
����Ŀ¼Ҫ���������Ŀ¼�ܶ�������
��ζ���������ĵ��ã�����Ū��һ��
�м�����м������Щͷ�ļ��͸���.c
�ļ���ɡ�

******************************************************/

#include "sdk_struct.h"

/////DDNS�ӿڲ�
int StartDdnsThread();
int StopDdnsThread();
void  DdnsUpdate(int UpdateFlg);


/////SMTP�ӿڲ�
int  startSmtpThread(void);
int  stopSmtpThread(void);
int updateSmtpSetting(unsigned char flag);
int testSmtp(void);


/////NTP�ӿڲ�
int startNtpClientThread(void);
int stopNtpClientThread(void);
int updateNtpSetting(int flag);

/////FTP�ӿڲ�
int SentToFTP(char *strFileName);
int UpdateFtpDate(int value);


/////DHCP����
int dhcpNetFun();


/////onvif����̨���ƽӿ�
int GetAllPreset(int channel,sdk_preset_all_t * preset_set);

int SetPtzCruiseAllPreset(int channel,sdk_cruise_param_t  * cruise_param );

int SetPreset(int channel , sdk_preset_t * preset);

int RecallPreset(int channel ,sdk_preset_t *preset);

int GetPtzCruiseAllPreset(int channel, sdk_cruise_param_t * cruise_param);


int ptzStartCruise(int channel);
int ptzStopCruise(int channel);

int ptzCruiseInit();
int ptzCruiseDestroy();

void ptzSetStatus(int channel ,int flag);
int testSmtp(void);

#endif

