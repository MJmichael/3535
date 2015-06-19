
#ifndef __PLAYBACK_REMOTE_H__
#define __PLAYBACK_REMOTE_H__


#ifdef HI3520D
#define MAX_SUPPORT_REMOTE_PLAYBACK_NUM		8
#elif HI3521
#define MAX_SUPPORT_REMOTE_PLAYBACK_NUM		16
#elif HI3531
#define MAX_SUPPORT_REMOTE_PLAYBACK_NUM		16
#elif HI3535
#define MAX_SUPPORT_REMOTE_PLAYBACK_NUM		16
#endif

#define MAX_PATH				260


#define CMD_NVR_BASE				0x10000			//nvr�����׼ֵ

#define CMD_QUERYRECFILE_STATUS			(CMD_NVR_BASE + 0x62)	//�ͻ���֪ͨ¼���������ѯ¼���ļ�״̬
#define CMD_QUERYRECFILE			(CMD_NVR_BASE + 0x63)	//�ͻ���֪ͨ¼���������ѯ¼���ļ�
#define CMD_DOWNLOADRECFILE			(CMD_NVR_BASE + 0x64)	//�ͻ���֪ͨ¼�����������¼���ļ�
#define	CMD_QUERY_STOP				(CMD_NVR_BASE + 0x57)	//֪ͨ����ֹͣ��ѯ
#define CMD_REMOTEFILESTATUS				(CMD_NVR_BASE + 0x6B)	//¼�����������¼���ļ������ͻ���״̬
#define CMD_REMOTEFILEENDSTATUS			(CMD_NVR_BASE + 0x6C)	//¼�����������¼���ļ������ͻ��ˣ�֪ͨ����״̬
#define CMD_REMOTEFILE				(CMD_NVR_BASE + 0x66)	//¼�����������¼���ļ������ͻ���
#define CMD_REMOTEFILEEND			(CMD_NVR_BASE + 0x67)	//¼�����������¼���ļ������ͻ��ˣ�֪ͨ����
#define CMD_NVR_DOWNLOADRECFILE_COMPLETE	(CMD_NVR_BASE + 0x90) //���ؽ���
#define CMD_QUERY_DEVICE			(0x68)   //��ѯ�豸����Զ�̲�ѯ�豸��ʱ���Ȳ�ѯԶ���豸��Ȼ�����ѡ����豸�ڽ��в�ѯ�ļ���
#define CMD_DEVICE_DATA				(0x69)   //��ѯ�����豸����
#define CMD_QUERY_DEVICE_STOP			(0x6A)   //�豸��ѯ����
#define CMD_PLAYRECFILE_HEADER_REQ		(0x165)	//�����ļ�ͷ
#define CMD_PLAYRECFILE_SEEK_REQ		(0x265)	//�ط�¼��λ����ת
#define CMD_PLAYRECFILE_PLAY_REQ		(0x365)	//�طż�������
#define CMD_PLAYRECFILE_PAUSE_REQ		(0x465)	//�ط�¼����ͣ
#define CMD_PLAYRECFILE_STOP_REQ		(0x565)	//�ط�¼��ֹͣ
#define CMD_PLAYRECFILE_STEP_REQ		(0x665)      //֡���ظ�
#define CMD_PLAYRECFILE_HEADER_RES		(0x1165)	//�ظ��ļ�ͷ
#define CMD_PLAYRECFILE_SEEK_RES		(0x1265)	//�ط�¼��λ����ת
#define CMD_PLAYRECFILE_PLAY_RES		(0x1365)	//�طż�������
#define CMD_PLAYRECFILE_PAUSE_RES		(0x1465)	//�ط�¼����ͣ
#define CMD_PLAYRECFILE_STOP_RES		(0x1565)	//�ط�¼��ֹͣ
#define CMD_PLAYRECFILE_STEP_RES		(0x1665)      //֡���ظ�
#define CMD_PLAYRECFILE_DATA			(0x300)	//����Ƶ������
#define CMD_PLAYERCFILE_KEEPALIVE		(0xeeee)	//���� 



typedef struct playback_remote_msg_t
{//Զ�̻ط���Ϣ
	int len;
	int cmd;
	char  pData[0];
}playback_remote_msg_t;

typedef struct playback_remote_search_condition_t
{//¼����������
	unsigned int startTm;                // ��ʼʱ��
	unsigned int EndTm;                  // ����ʱ��
	unsigned int nChannelID;             // ͨ����
	unsigned int nFileType;              // �ļ�����  
	int     nReserver;                   // Ԥ��
}playback_remote_search_condition_t;

typedef struct playback_remote_file_head_t
{//�ļ���Ϣ
	long fileType;//�ļ�����
	long fileSize;//�ļ���С
	long videoCoder;//��Ƶ����
	long audioCoder;//��Ƶ����
	long frameRate;//֡��
	long bitRate;//������
	long width;//ͼ���
	long height;//ͼ���
	long totalFrames;//�ܹ�֡��
	long res[8];//����
}playback_remote_file_head_t;

typedef struct playback_remote_frame_head_t
{//֡ͷ��Ϣ
	long type;//�������� 0��ʾ��Ƶ  1��ʾ��Ƶ  2��ʾ�ļ�����
	long len;//���ݳ���
	long isKeyFrame;//�Ƿ�Ϊ�ؼ�֡	.��Ƶ������Ч
	long index;//��Ƶ֡����,��Ƶ������Ч
	long timestamp;//ʱ���
	long res1;
	long res2;
	long res3;
}playback_remote_frame_head_t;

typedef struct playback_remote_play_t
{//��������
	long lframe;//���󲥷ŵ�֡��
	long speed;//�ٶȿ���
	long res2;
	long res3;
}playback_remote_play_t;

typedef struct playback_remote_seek_t
{//¼��ط��϶�
	long lSecond;
	long res1;
	long res2;
	long res3;
}playback_remote_seek_t;



void playbackRemoteUpdateParam();

int playbackRemoteInit();

void playbackRemoteDestroy();

#endif//__PLAYBACK_REMOTE_H__


