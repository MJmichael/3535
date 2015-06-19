#ifndef __PLAYBACK_FUNC_H__
#define __PLAYBACK_FUNC_H__


#include "streamLib.h"

typedef struct playback_file_info_t
{
	int iFrameFd;
	int iFrameStartAddr;
	int iFrameEndAddr;
	int iFrameCurAddr;

	int dataFd;
	int dataStartAddr;
	int dataEndAddr;
	int dataCurAddr;

	int startTime;//¼�����ʼʱ��
	int endTime;//����ʱ��
}playback_file_info_t;



/* �򿪻ط�¼���ļ� */
int playbackRecordOpen(playback_file_info_t *pPlaybackFileInfo, char *pFilePath, int iFrameStartAddr, int iFrameEndAddr, int offset);

/*
 * ��ȡ�ط�¼���ļ�
 * pPlaybackFileInfo:	�ط��ļ���Ϣ
 * speed:		�ط��ٶ�
 * pFrame:		һ֡��Ƶ
 * */
int playbackRecordRead(playback_file_info_t *pPlaybackFileInfo, int speed, stream_frame_t *pFrame);

/* �رջط�¼���ļ� */
void playbackRecordClose(playback_file_info_t *pPlaybackFileInfo);


#endif//__PLAYBACK_FUNC_H__

