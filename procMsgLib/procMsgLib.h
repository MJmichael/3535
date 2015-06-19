#ifndef __PROC_MSG_LIB_H__
#define __PROC_MSG_LIB_H__


#include "param.h"


#ifdef __cplusplus
extern "C" {
#endif

/* ���̼���Ϣͨ�ų�ʼ�� */
int procMsgInit(int *pMsgId, int *pSemId);

/* �����Ϣ���� */
void procMsgClean(int msgId, int msgType);

/* ���̼���Ϣͨ������ */
int procMsgDestroy(int semId);






/********************************** ���̼�ͨ�� �ͻ��˵��� **********************************/

/* ��ѯ���� */
int procGetParam(int paramType, char *pRecvBuf, int bufLen);
int procGetParamExt(int paramType, char *data, int dataLen, char *pRecvBuf, int bufLen);
/* ���ò��� */
int procSetParam(int paramType, char *pSendBuf, int bufLen);

/* ������� */
int procAddData(int paramType, char *pSendBuf, int bufLen);
/* ɾ������ */
int procDelData(int paramType, char *pSendBuf, int bufLen);



/* ��ѯ¼���ļ� */
int procSearchRecordFile(int channelNo, int streamNo, int startTime, int endTime, char *pRecvBuf, int len);
/* ���ûطŷ�����Ŀ */
int procSetPlaybackNum(int num);
/* �ط�¼�� */
int procPlayRecordFile(int displayChannel, int speed, record_search_file_t *pSearchFile, int fileNum, int startTime, int offset);
/* ֹͣһ���ط� */
int procStopPlayback(int displayChannel);
/* ֹͣ���лط� */
int procStopAllPlayback();
/* �ط�ͨ����ĳһλ�õ���Ƶ */
int procPlayRecordTime(int displayChannel, int startTime);
/* ��ȡ��ǰ�طŵ�¼���λ�� */
int procGetCurPlaybackPos(control_play_cur_pos_t *pPlayItem, int size);



/* ��ȡ���е��豸ͨ����Ϣ */
int procGetAllDevChannelInfo(char *pRecvBuf, int len);

/* ����Ԥ��������Ŀ */
int procSetDisplayNum(int num, int pos);

/* QT��������ͨѶ��ʼ�� */
void procMsgQtInit();

/* QT��������ͨѶ���� */
void procMsgQtDestroy();


#ifdef __cplusplus
}
#endif

#endif//__PROC_MSG_LIB_H__

