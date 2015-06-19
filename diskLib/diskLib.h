#ifndef __DISK_LIB_H__
#define __DISK_LIB_H__


#include "recordLib.h"

#define  HDD_FILE   "/www/hdd.txt"
#define  HDDSIZE_FILE  "/www/diskSize.txt"


#ifdef __cplusplus
extern "C" {
#endif

#define MAX_SATA_DISK_NUM  16

typedef struct mount_info_t
{//������Ϣ
	unsigned char formatFlag;//��ʽ�����
	unsigned char mountFlag;//���ر��
	unsigned char unused[2];//
	unsigned char diskUuid[16];//Ӳ��uuid
	char devName[16];//�豸��
	char volumeName[16];//Ӳ�̾���
	char mountPath[16];//����·��
}mount_info_t;

typedef struct disk_info_t
{//Ӳ����Ϣ
	int diskNum;//Ӳ����Ŀ
	mount_info_t mountInfo[MAX_SUPPORT_DISK_NUM];
}disk_info_t;

	typedef struct sata_disk_info_t
	{
		int  sataPort;
		char devName[16];
		unsigned char diskUuid[16];
		long long totalSize;

	}sata_disk_info_t;

	typedef struct sata_info_t
	{
		int diskNum;
		sata_disk_info_t sataInfo[MAX_SATA_DISK_NUM];
		
	}sata_info_t;


/* diskLib.c */
/* ��ȡӲ����Ϣ */
disk_info_t * diskGetInfo();
/* Ӳ�̿��ʼ�� */
void diskLibInit();
/* Ӳ�̿����� */
void diskLibDestroy();




/* diskInfo.c */
/* ��ȡӲ����Ϣ  uuid���������ϴι���·�� */
int getDiskPartitionInfo(char *pDevicePath, unsigned char *pUuid, char *pVolumeName, char *pMountPath);
/* ����Ӳ�̾�� */
int setDiskVolumeName(char *pDevicePath, char *pName);
/* ���Ӳ�̷����Ƿ��Ѿ����� */
int checkDiskPartitionIsMount(char *pDevName, char *pMountPath);
/* ��ȡ�Ѿ�����Usb·�� */
int getUsbMountPath(char *pPath);
/*ɨ��Ӳ�� */
int findSataDisk(sata_info_t *pSataInfo );
/*����Ӳ��*/
int mountSataDisk(unsigned int diskId);
/*��ʽ��Ӳ��*/
int FormatDisk( unsigned int diskId );

int mountAllSataDisk();

int matchSataPort( const char *p );

//       /dev/sda
int GetDiskFreeSize( const char *pdevPath);


/* fallocate.c */
/* ��ȡ��Ԥ������ļ������Ŀ */
int getFileTotalNum(char *pDevicePath, unsigned int fileSize);
/* ���Ԥ�����ļ� */
int checkFallocateFile(char *pDiskPath, unsigned int fileSize);
/* ����Ԥ�����ļ� */
int createFallocateFile(char *pFileName, int fileSize);


/* checkUsb.c */
int startHotPlugThread();
int pox_system(const char *cmd_line);
int iCheckSystemReturnValue(int p_iStatus);
#ifdef __cplusplus
}
#endif

#endif//__DISK_LIB_H__


