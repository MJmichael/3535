/*
*******************************************************************************

*******************************************************************************
*/

#ifndef __DECODE_LIB_H__
#define __DECODE_LIB_H__

#ifdef __cplusplus
extern "C" {
#endif



/* ��ȡ�����߳����б�� */
int decodeGetRunFlag(int viewPos);
/* ���ý����߳����б�� */
void decodeSetRunFlag(int viewPos, int value);

void decodeEableAudio(int flag);

/* �������� */
int decodeStartDecode(int channelNo, int streamNo, int viewPos, int restartNetwork);
/* ֹͣ���� */
void decodeStopDecode(int viewPos);
/* ֹͣ���н��� */
void decodeStopAllDecode();

/* ��ȡ��ǰ���ڵ�״̬���Լ����ڲ�����ͨ���š����� */
int decodeGetCurViewChannelNoAndStreamNo(int viewPos, int *pChannelNo, int *pStreamNo);
void decodeSetViewChannelNoAndStreamNo(int viewPos, int channelNo, int streamNo);

/* ��ͣ���� */
void decodePauseDecode(int viewPos);
/* ��ͣ���н��� */
void decodePauseAllDecode();

/* �ָ����� */
void decodeRestartDecode(int viewPos);
/* �ָ����н��� */
void decodeRestartAllDecode();

/* �ȴ����������̵߳�����״̬ */
void decodeWaitRunFlag(int viewPos, int runFlag);
/* �ȴ����н����̵߳�����״̬ */
void decodeWaitAllRunFlag(int runFlag);



/* ȫ��ĳ������ */
int decodeLibFullScreen(int viewPos);
/* 4���� */
int decodeLibFourScreen(int viewPos);
/* 6���� */
int decodeLibSixScreen(int viewPos);
/* 8���� */
int decodeLibEightScreen(int viewPos);
/* 9���� */
int decodeLibNineScreen(int viewPos);
/* 16���� */
int decodeLibSixteenScreen(int viewPos);

int decodeLib24Screen(int viewPos);
/* 25 */
int decodeLib25Screen(int viewPos);
/* 36���� */
int decodeLib36Screen(int viewPos);


/* ��ȡ������ */
int decodeGetDisplayNum();

int decodeLibInit(int resolution, int displayNum);
int decodeLibReset(int resolution, int displayNum);
void decodeLibdestroy(int displayNum);

int AppStartVideo();
int SwitchScreenDisplay(int ViewPos, int DisplayNum);
int SwitchScreenPlayBackDisplay(int chn[4], int DisplayNum);




#ifdef __cplusplus
}
#endif


#endif//__DECODE_LIB_H__

