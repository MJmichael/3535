#ifndef __RECORD_FUNC_H__
#define __RECORD_FUNC_H__


#include "recordLib.h"


#define MAX_RECORD_FILE_PATH_LEN	64//¼���ļ�·����󳤶�

#define RECORD_TYPE_DATA		0//д��¼���ļ����������� I֡
#define RECORD_TYPE_I_FRAME		1//֡����

//#define RECORD_I_FRAME_INDEX_SIZE	8//¼���ļ�I֡��������󳤶�

#define RECORD_FILE_I_FRAME_SIZE	(10*(MAX_FILE_SIZE/1024))//�ļ���С

/* ¼���ļ����� */
#define RECORD_FILE_I_FRAME_START_ADDR	0//¼���ļ��� I֡��������ʼ��ַ
#define RECORD_FILE_DATA_START_ADDR	RECORD_FILE_I_FRAME_SIZE//¼���ļ��� ���ݵ���ʼ��ַ




typedef struct __record_info_mmap_t__
{//¼���ļ�ӳ����Ϣ
	char *pMmapAddr;//¼���ļ�ӳ���ַ
	unsigned int startAddr;//��Ӧ���ļ���ʼ��ַ
	unsigned int syncAddr;//����δͬ������ʼ��ַ
	unsigned int syncLen;//δͬ�������ݳ���
}record_info_mmap_t;
typedef struct __record_file_info_t__
{//¼���ļ���Ϣ
	char path[MAX_RECORD_FILE_PATH_LEN];//¼���ļ�·��
	int recordNo;//¼���ļ����
	int dataFd;//���� ������
	int iFrameFd;//i֡ ������

	record_info_mmap_t mmapIframe;//¼���ļ�I֡������ӳ���ַ
	record_info_mmap_t mmapData;//¼���ļ�������ӳ���ַ
}record_file_info_t;

typedef struct __record_i_frame_index_t__
{
//	int no;
	unsigned int time;//��֡��¼ʱ��
	unsigned int startAddr;//��֡��Ӧ����������ʼ��ַ
}record_i_frame_index_t;


/**************************************** recordFunc.c ****************************************/
/*
 * ��¼���ļ�
 * pPath��		¼���ļ�·��
 * type��		�򿪷�ʽ ֻ����ֻд����д
 * fileNo:		¼���ļ����
 * iFrameOffset:	¼��֡����ƫ�Ƶ�ַ
 * dataOffset:		¼��ƫ�Ƶ�ַ
 *
 * ����ֵ��	0���ɹ�  1:ʣ��ռ䲻��  ����:ʧ��
 * */
int recordOpen(RECORD_HANDLE *pHandle, char *pPath, int type, int fileNo, unsigned int iFrameOffset, unsigned int dataOffset);

/*
 * ӳ��¼���ļ�
 * handle��		¼���ļ�·��
 * dataOffset:		¼��ƫ�Ƶ�ַ
 * iFrameOffset:	¼��֡����ƫ�Ƶ�ַ
 *
 * ����ֵ��	-1��ʧ��  0:�ɹ�
 * */
int recordMmap(RECORD_HANDLE handle, unsigned int dataOffset, unsigned int iFrameOffset);

/*
 * ����ӳ��¼���ļ�  ��ӳ����ڴ����򲻹���ʱ����Ҫ������ӳ��
 * handle��		¼���ļ�·��
 * dataOffset:		¼��ƫ�Ƶ�ַ
 * iFrameOffset:	¼��֡����ƫ�Ƶ�ַ
 *
 * ����ֵ��	-1��ʧ��  0:�ɹ�
 * */
int recordReMmap(RECORD_HANDLE handle);

/*
 * д��¼������
 * handle��	¼���ļ����
 * type��	д�����������  0��¼������  1��I֡����
 * writeBuf��	д��buf
 * writeLen��	д�볤��
 *
 * ����ֵ��	0���ɹ�  ������ʧ��
 * */
int recordWrite(RECORD_HANDLE handle, int type, char *writeBuf, int writeLen);

/*
 * ��⵱ǰ�Ļ���buf�Ƿ��㹻д��
 * handle��	¼���ļ����
 * frameLen:	д���֡����
 *
 * ����ֵ��	0���ɹ�  1:��Ҫ����ӳ������  ������ʧ��
 * */
int recordCheckBufIsEnough(RECORD_HANDLE handle, int frameLen);

/*
 * ��⵱ǰд���¼���ļ��Ƿ����㹻�Ŀռ�
 * handle��	¼���ļ����
 *
 * ����ֵ��	0���ɹ�  1:��Ҫ����ӳ������  ������ʧ��
 * */
int recordCheckFileIsEnough(RECORD_HANDLE handle);

/*
 * ͬ��¼������
 * handle��	¼���ļ����
 *
 * ����ֵ��	0���ɹ�  ������ʧ��
 * */
int recordSync(RECORD_HANDLE handle);

/*
 * �ر�¼���ļ�
 * handle��	¼���ļ����
 *
 * ����ֵ��	0���ɹ�  ������ʧ��
 * */
int recordClose(RECORD_HANDLE handle);


void recordFuncInit();

void recordFuncDestroy();


#endif//__RECORD_FUNC_H__

