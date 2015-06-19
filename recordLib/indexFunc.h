#ifndef __INDEX_FUNC_H__
#define __INDEX_FUNC_H__


#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "recordLib.h"


#define INDEX_BLOCK_SIZE			(64*1024)//�����ļ��еĿ��С

#define MMAP_INDEX_RECORD_SIZE			(2 * INDEX_BLOCK_SIZE)//�����ļ�ӳ��¼�������С
#define MMAP_INDEX_INDEX_SIZE			(2 * INDEX_BLOCK_SIZE)//�����ļ�ӳ�����������С
#define MMAP_INDEX_CHANNEL_SIZE			(2 * INDEX_BLOCK_SIZE)//�����ļ�ӳ��ͨ�������С
#define MMAP_INDEX_DATA_SIZE			(INDEX_BLOCK_SIZE)//�����ļ�ӳ�����������С

#define INDEX_RECORD_INFO_START_BLOCK		1//�����ļ���¼���ļ���������ռ����ʼ��	1~2
#define INDEX_INDEX_INFO_START_BLOCK		3//�����ļ���������Ϣ��ռ����ʼ��	3~4
#define INDEX_CHANNEL_INFO_START_BLOCK		5//�����ļ���ͨ����Ϣ��ռ����ʼ��	5~6
#define INDEX_UNUSED_START_BLOCK		7//�����ļ��б���������ռ����ʼ��	7~9
#define INDEX_INDEX_DATA_START_BLOCK		10//�����ļ�������������ռ����ʼ��	10~���


#define INDEX_USED_FLAG_NULL		0//��
#define INDEX_USED_FLAG_NOT_USE		1//δʹ��
#define INDEX_USED_FLAG_USING		2//����ʹ��
#define INDEX_USED_FLAG_USED		3//�Ѿ�ʹ��

#define INDEX_FILE_STATUS_NULL		0//��
#define INDEX_FILE_STATUS_DEL		1//��ɾ��
#define INDEX_FILE_STATUS_WRITE		2//����д��
#define INDEX_FILE_STATUS_OK		3//д�����




typedef struct __index_record_info_t__
{//�����ļ��е�¼����Ϣ
	unsigned short usedNum:13;//¼��鱻ʹ�õĴ���
	unsigned short usedFlag:3;//�Ƿ�ʹ��  1:δʹ�� 2������ʹ��  3:ʹ�����
	unsigned char channelNo;//ʹ�øø�¼���ļ����豸��
	unsigned char streamNo;//ʹ�øø�¼���ļ���ͨ����
}index_record_info_t;
#define ONE_RECORD_INFO_SIZE		(sizeof(index_record_info_t))4//һ��¼���ļ�������Ϣ�Ĵ�С

typedef struct __index_index_info_t__
{//�����ļ��е�������Ϣ
	unsigned short usedFlag:3;//�Ƿ�ʹ��  1:δʹ�� 2������ʹ�� 3:ʹ�����
	unsigned short unused:13;//����
	unsigned char channelNo;//ʹ�øø�����������豸��
	unsigned char streamNo;//ʹ�øø����������ͨ����
}index_index_info_t;
#define ONE_INDEX_INFO_SIZE		(sizeof(index_index_info_t))//4//һ����������������Ϣ�Ĵ�С

typedef struct __index_channel_info_t__
{//�����ļ��е�ͨ����Ϣ
	unsigned short usedFlag:3;//�Ƿ�ʹ��  1:δʹ�� 2������ʹ��  3:ʹ�����
	unsigned short unused:13;//����
#if 0
	unsigned char channelNo;//�豸��  �ݲ�ʹ��
	unsigned char streamNo;//ͨ����  �ݲ�ʹ��
#else
	unsigned char unused1[2];//����
#endif
	unsigned short curIndexNo;//��ǰ���ڲ�������������� (��������Ŵ�0��ʼ)
	unsigned short curItemNo;//��ǰ���ڲ��������������ƫ�Ƶ���Ŀ�� (������Ŀ��Ŵ�0��ʼ)
}index_channel_info_t;
#define ONE_CHANNEL_INFO_SIZE		(sizeof(index_channel_info_t))//8//һ��ͨ��������Ϣ�Ĵ�С

typedef struct __index_file_item_t__
{//�����ļ��е��ļ�������Ŀ
	unsigned short fileStatus:3;//�ļ�״̬  1��δʹ��  2������ʹ�� 3��ʹ�����  4��ɾ��
	unsigned short fileType:13;//�ļ�����  bit0����ʱ¼�� bit1���澯¼�� bit2���ֶ�¼��
	unsigned char unused[6];
	unsigned short recordUsedNum:13;//¼��鱻ʹ�õĴ���
	unsigned short unused1:3;
	unsigned short recordNo;// ¼���ļ���%04X����Ϊ¼���ļ�����
	unsigned int startTime;//¼����ʼʱ�䣨�룩
	unsigned int endTime;//¼�����ʱ�䣨�룩
	unsigned int startAddr;//���ļ���һ֡��Ӧ��¼���ļ���I֡�����ĵ�ַ
	unsigned int endAddr;//���ļ����һ֡��Ӧ��¼���ļ���I֡�����ĵ�ַ
	unsigned int dataStartAddr;//¼���ļ���ʼ��ַ
	unsigned int dataEndAddr;//¼�������ļ�������ַ
}index_file_item_t;
#define ONE_FILE_INFO_SIZE		(sizeof(index_file_item_t))//32//һ���ļ�����������Ϣ�Ĵ�С

#define MAX_SUPPORT_RECORD_NUM		(MMAP_INDEX_RECORD_SIZE/ONE_RECORD_INFO_SIZE)//���֧�ֶ��ٸ�¼���ļ���Ŀ
#define MAX_ITEM_NUM_FOR_ONE_INDEXNO	(MMAP_INDEX_DATA_SIZE/ONE_FILE_INFO_SIZE)//һ����������������ٸ�������Ŀ
#define MAX_INDEXNO_NUM			((MMAP_INDEX_CHANNEL_SIZE/ONE_INDEX_INFO_SIZE) < (MAX_FILE_SIZE/INDEX_BLOCK_SIZE) ? (MMAP_INDEX_CHANNEL_SIZE/ONE_INDEX_INFO_SIZE) : (MAX_FILE_SIZE/INDEX_BLOCK_SIZE))//��������������Ŀ

typedef struct __index_info_mmap_t__
{//�����ļ�ӳ����Ϣ
	char *pMmapAddr;//ӳ���ַ
	unsigned int startAddr;//��Ӧ���ļ���ʼ��ַ
	unsigned int syncAddr;//����δͬ������ʼ��ַ
	unsigned int syncLen;//δͬ�������ݳ���
}index_info_mmap_t;
typedef struct __index_info_t__
{//�����ļ���Ϣ
	char path[64];//�����ļ�·��
	int fd;//������
	int fileNo;//¼���ļ����
//	int recordNo;//¼���ļ����
//	unsigned char channelNo;//�豸��
//	unsigned char streamNo;//ͨ����
//	unsigned char unused[2];//����

	index_info_mmap_t mmapRecord;//�����ļ�¼��������ӳ���ַ
	index_info_mmap_t mmapIndexInfo;//�����ļ�������Ϣ��ӳ���ַ
	index_info_mmap_t mmapChannel;//�����ļ�ͨ����ӳ���ַ
//	index_info_mmap_t mmapIndexData;//�����ļ�����������ӳ���ַ
}index_info_t;


typedef struct __index_file_info_t__
{//�ļ�������Ϣ
	INDEX_HANDLE handle;
	unsigned short curIndexNo; //��ǰ���ڲ�������������� (��������Ŵ�0��ʼ)
	unsigned short curItemNo;//��ǰ���ڲ��������������ƫ�Ƶ���Ŀ�� (������Ŀ��Ŵ�0��ʼ)
//	unsigned char channelNo;//�豸��
//	unsigned char streamNo;//ͨ����
//	unsigned short recordNo;// ¼���ļ���%04X����Ϊ¼���ļ�����
	char *pMmapAddr;//ӳ���ַ
}index_file_info_t;



/***************************************** indexFunc.c *****************************************/
/*
 * �������ļ�
 * pPath��		¼���ļ�·��
 * fileNo:		�����ļ����
 *
 * ����ֵ��	0��ʧ��  >0:�ɹ�
 * */
INDEX_HANDLE indexOpen(char *pPath, int fileNo);

/*
 * ͬ������
 * startAddr��	ӳ���ļ�����ʼ��ַ
 * offset��	Ҫд���ƫ�Ƶ�ַ
 * dataLen��	Ҫд������ݳ���
 *
 * ����ֵ��	0���ɹ�  ���ࣺʧ��
 * */
int indexSync(char *pStartAddr, int offset, int dataLen);

/*
 * �ر������ļ�
 * handle��	�����ļ����
 *
 * ����ֵ��	0���ɹ�  ������ʧ��
 * */
int indexClose(INDEX_HANDLE handle);




/***************************************** indexRecordFunc.c *****************************************/
/*
 * ��ʼ������¼���ļ�ʹ��״̬
 * 
 * ����ֵ��	==0:�ɹ�  ���ࣺʧ��
 * */
int indexInitRecordNoFlag(INDEX_HANDLE handle, int totalNum);

/*
 * ��ȡһ��δʹ�õ�¼���ļ����
 * 
 * ����ֵ��	>=RECORD_START_NO:�ɹ� ��Ŵ�2��ʼ  ���ࣺʧ��
 * */
int indexGetUnusedRecordNo(INDEX_HANDLE handle);

/*
 * ��ȡ¼���ļ���Ϣ
 * recordNo:	¼���ļ����
 *
 * pDevNo:	�豸��
 * pChannelNo:	ͨ����
 * pUsedNum:	ʹ�ô���
 * 
 * ����ֵ��	���ظ�¼���ļ�ʹ��״̬  �� < 0��ʧ��  
 * */
int indexGetRecordNoInfo(INDEX_HANDLE handle, int recordNo, int *pDevNo, int *pChannelNo, int *pUsedNum);

/*
 * ��ȡ����¼���ļ�״̬
 *
 * pUsedNum:		�Ѿ�ʹ��¼���ļ���Ŀ
 * pFreeNum��		���е���Ŀ
 * pUsingNum��		����ʹ�õ���Ŀ
 * pOldRecordNo:	���ϵ�¼���ļ�
 * pOldRecordNoUsedNum:	���ϵ�¼���ļ�ʹ�ô���
 * 
 * ����ֵ��	0:�ɹ�  �� < 0��ʧ��  
 * */
int indexGetAllRecordNoInfo(INDEX_HANDLE handle, int *pUsedNum, int *pFreeNum, int *pUsingNum, int *pOldRecordNo, int *pOldRecordNoUsedNum);

/*
 * ���¼���ļ�
 * recordNo:		¼���ļ����
 * type:		¼���ļ���״̬
 * recordUsedNum:	¼���ļ�ʹ�õĴ���
 * channelNo:		�豸��
 * streamNo:		ͨ����
 * 
 * ����ֵ��	=0:����  �� < 0��ʧ��  
 * */
int indexCheckRecordNoInfo(INDEX_HANDLE handle, int recordNo, int type, int recordUsedNum, unsigned char channelNo, unsigned char streamNo);

/*
 * �������ϵ�¼���ļ�
 *
 * pRecordNo:		¼���ļ�
 * pRecordUsedNum:	��¼���ļ�ʹ�ô���
 *
 * ����ֵ��		0���ҵ����ʵ�¼���ļ�  1���п��е�¼���ļ�  ���ࣺʧ��
 * */
int indexFindOldRecordNo(INDEX_HANDLE handle, int *pRecordNo, int *pRecordUsedNum);

/*
 * �޸�¼���ļ�ʹ��״̬
 * recordNo:	¼���ļ����
 * type:	״̬
 * channelNo:	�豸��
 * streamNo:	ͨ����
 * 
 * ����ֵ��	>=0:�ɹ�  ���ࣺʧ��
 * */
int indexModifyRecordNoFlag(INDEX_HANDLE handle, int type, int recordNo, unsigned char channelNo, unsigned char streamNo);

/*
 * ����ĳ���豸��ĳ��ͨ����ռ�õ�����¼���ļ����
 *
 * channelNo:       	�豸��
 * streamNo:   	ͨ����
 * pRecordNo:           ¼���ļ����;
 * pRecordNoUsedNum:    ¼���ļ�ʹ�ô���
 * 
 * ����ֵ��     >=0:�ɹ�  ���ࣺʧ��
 * */
int indexFindDevChannelAllUsedRecordNo(INDEX_HANDLE handle, unsigned char channelNo, unsigned char streamNo, unsigned short *pRecordNo, int *pRecordNoUsedNum);

/*
 * ɾ��ĳ���豸��ĳ��ͨ����ռ�õ�¼���ļ�
 *
 * channelNo:	�豸��
 * streamNo:	ͨ����
 * 
 * ����ֵ��	>=0:�ɹ�  ���ࣺʧ��
 * */
int indexDelDevChannelRecordNo(INDEX_HANDLE handle, unsigned char channelNo, unsigned char streamNo);




/***************************************** indexIndexFunc.c *****************************************/
/*
 * ��ȡδʹ�õ��ļ������������
 * */
int indexGetUnusedIndexNo(INDEX_HANDLE handle);

/*
 * �޸���������ʹ��״̬
 * type:	״̬
 * channelNo:	�豸��
 * streamNo:	ͨ����
 * 
 * ����ֵ��	>=0:�ɹ�  ���ࣺʧ��
 * */
int indexModifyIndexNoFlag(INDEX_HANDLE handle, int type, int indexNo, unsigned char channelNo, unsigned char streamNo);

/*
 * ����ĳ���豸��ĳ��ͨ����ռ�õ�����������
 * channelNo:	�豸��
 * streamNo:	ͨ����
 * pIndexNo:    ����������Ϣ
 * 
 * ����ֵ��	>=0:�ɹ�  ���ࣺʧ��
 * */
int indexFindDevChannelUsedIndexNo(INDEX_HANDLE handle, unsigned char channelNo, unsigned char streamNo, unsigned short *pIndexNo);





/***************************************** indexChannelFunc.c *****************************************/
/*
 * ��ȡͨ������ʹ�õ��ļ������������
 *
 * channelNo:	�豸��
 * streamNo:	ͨ����
 *
 * pIndexNo:	����������
 * pItemNo:	������Ŀ���
 *
 * ����ֵ��	0���ɹ�  ���ࣺʧ��
 * */
int indexGetFileCurIndexNo(INDEX_HANDLE handle, unsigned char channelNo, unsigned char streamNo, int *pIndexNo, int *pItemNo);

/*
 * �޸�ͨ������ʹ��״̬
 * type:	״̬
 * indexNo:	��ǰʹ�õ��������
 * itemNo:	��ǰʹ�õ����������е���Ŀ���
 * channelNo:	�豸��
 * streamNo:	ͨ����
 * 
 * ����ֵ��	>=0:�ɹ�  ���ࣺʧ��
 * */
int indexModifyChannelIndexNoFlag(INDEX_HANDLE handle, int type, int indexNo, int itemNo, unsigned char channelNo, unsigned char streamNo);





/***************************************** indexFileFunc.c *****************************************/
/*
 * �������ļ����ļ���������
 * pPath��	¼���ļ�·��
 * indexNo:	����������
 * itemNo:	������Ŀ���
 *
 * ����ֵ��	0��ʧ��  >0:�ɹ�
 * */
INDEX_FILE_HANDLE indexOpenFileInfo(INDEX_HANDLE handle, int indexNo, int itemNo);

/*
 * ӳ�������ļ��е��ļ���������
 * handle��		�����ļ����
 * indexNo:		�ļ��������ڵı��
 *
 * ����ֵ��		����ӳ���ָ�룬NULL:ʧ��
 * */
char * indexMmapFileInfo(INDEX_HANDLE handle, int indexNo);

/*
 * �ر������ļ����ļ���������
 * fileHandle:	�ļ��������
 *
 * ����ֵ��	0��ʧ��  >0:�ɹ�
 * */
void indexCloseFileInfo(INDEX_FILE_HANDLE fileHandle);

/*
 * �����ļ�������Ŀ��Ϣ
 * handle��	�����ļ����
 * fileHandle��	�����ļ�������������
 *
 * fileStatus:	
 * fileType:	
 * recordNo:	
 * recordUsedNum:
 * startTime:	
 * endTime:	
 * startAddr:	
 * endAddr:	
 * dataEndAddr:	
 * �����ֶ��У�Ϊ0ʱ����ʾ���޸�ԭ������
 *
 * ����ֵ��	0���ɹ�  ������ʧ��
 * */
int indexUpdateFileInfo(INDEX_HANDLE handle, INDEX_FILE_HANDLE fileHandle, int fileStatus, int fileType, 
		int recordNo, int recordUsedNum, unsigned int startTime, unsigned int endTime, unsigned int startAddr, unsigned int endAddr, unsigned int dataStartAddr, unsigned int dataEndAddr);

/*
 * ��ȡ��ǰ���ڲ�����¼���ļ����
 *
 * handle:		�����ļ����
 * fileHandle��		�����ļ����ļ�����������
 *
 * pRecordNo:		����ʹ�õ�¼���ļ����
 * pRecordUsedNum:	��¼���ļ�ʹ�õĴ���
 * pIFrameStartAddr��	��һ��I֡д�����ʼ��ַ
 * pDataStartAddr��	��һ��¼������д�����ʼ��ַ
 *
 * ����ֵ��		0���ɹ�  ������ʧ��
 *  */
int indexGetCurUsedRecordNo(INDEX_HANDLE handle, INDEX_FILE_HANDLE fileHandle, int *pRecordNo, int *pRecordUsedNum, unsigned int *pIFrameStartAddr, unsigned int *pDataStartAddr);

/*
 * ���Һ��ʵ���Ŀ
 *
 * handle:              �����ļ����
 * fileHandle��         �����ļ����ļ�����������
 * startTime:           ��ʼʱ��
 * endTime��            ����ʱ��
 * pRecordNo:           ¼���ļ����
 * pRecordUsedNum:      ¼���ļ�ʹ�õĴ���
 * recordNoNum:         ¼���ļ���Ŀ
 *
 * ����ֵ��             �����ҵ����ļ���Ŀ   <0��ʧ��
 *  */
int indexFindItem(INDEX_HANDLE handle, INDEX_FILE_HANDLE fileHandle, int diskNo,int recordType, int startTime, int endTime, unsigned short *pRecordNo, int *pRecordUsedNum, int recordNoNum, record_search_file_t *pRecordSearchFile, int itemCount);



#endif//__INDEX_FUNC_H__

