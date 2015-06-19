/*
*******************************************************************************
**  Copyright (c) 2012, All rights reserved.
**  
**  : epoll,epoll
*******************************************************************************
*/
#ifndef __COMMON_LIB_H__
#define __COMMON_LIB_H__


#include <unistd.h>
#include <sys/types.h>       /* basic system data types */
#include <sys/socket.h>      /* basic socket definitions */
#include <netinet/in.h>      /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>       /* inet(3) functions */
#include <sys/epoll.h> /* epoll function */
#include <fcntl.h>     /* nonblocking */
#include <sys/resource.h> /*setrlimit */

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>


#include <unistd.h>
#include <string.h>
//#include <epoll.h>
#include <sys/epoll.h>

#include "logLib.h"

#ifdef __cplusplus
extern "C" {
#endif


//#define Printf(format, arg...) myPrintf( __FILE__, __LINE__, format, ##arg)
#define Printf(format, arg...) dump_printf( __FILE__, __LINE__, format, ##arg)



/* commonLib.c */
/* ��ȡϵͳ�Ѿ����е�ʱ�� */
unsigned int getSystemBootTime();
/* ��ʱ���� , ��λ ms*/
inline void myMsleep(int sleepTime);
/* ��ӡ��Ϣ ���ļ��������� */
void myPrintf(const char *file, int line, const char *format, ... );
int readn(int fd, void *vptr, size_t n);
int writen(int fd, const void *vptr, size_t n);

int commonGetUpdataBoaParamFlag();
void commonSetUpdataBoaParamFlag(int value);


/* hash.c */
#define MAX_HASH_KEY_LEN 32//hash�ؼ��ֵĳ���

/* Ԫ��ֵ */
typedef struct elem_value_t
{
	char key[MAX_HASH_KEY_LEN];//hash�ؼ���
	int keyLen;//hash�ؼ��ֵĳ���
	void *pValue;//ֵ
	struct elem_value_t *pre;
	struct elem_value_t *next;
}elem_value_t;

/* Ԫ������ */
typedef struct elem_type_t
{
	int elemNum;//ÿ��hash�����е�Ԫ�ص���Ŀ
	struct elem_value_t *head;
	struct elem_value_t *last;
}elem_type_t;

/* hash�� */
typedef struct hash_table_t
{
	int hashNum;//hash����ĸ���
	int userHashNum;//�Ѿ��е�hash��Ŀ
	elem_type_t *pElem;
}hash_table_t;

/* ��ʼ��hash�� */
hash_table_t * initHash(int num);
/* ����hash���� */
int insertHash(hash_table_t *pHashTable, char *key, int keyLen, elem_value_t *pElemValue);
/* ��hash����ɾ�� */
int delHash(hash_table_t *pHashTable, char *key, int keyLen);
/* ��hash���в��� */
elem_value_t * searchHash(hash_table_t *pHashTable, char *key, int keyLen);
/* ��ʾhash�����ϸ��Ϣ */
void showHashInfo(hash_table_t *pHashTable);
/* ����hash�� */
int deinitHash(hash_table_t *pHashTable);



/* socketFunc.c */
/* ���÷�����socket */
int netSocketSetNonBlock(int sockfd);
/* ��ȡsocket���ջ����� */
int netSocketGetBufferRecvSize(int sockFd);
/* ��ȡsocket���ͻ����� */
int netSocketGetBufferSendSize(int sockFd);
/* ����socket���ջ����� */
int netSocketSetBufferRecvSize(int sockFd, int recvSize);
/* ����socket���ͻ����� */
int netSocketSetBufferSendSize(int sockFd, int sendSize);
/* select��ʱ�ȴ� */
int netSocketSelectWait(int sock, int maxMsec);
/* ��ȡsock�ϵ�IP�Ͷ˿� */
int netSocketGetSockName( int socket, char *pIp, int *pPort );


/* socketTcpFunc.c */
/* ��ʼ������TCP����������sock */
int netSocketCreateTcpListenServer(int port);
/* ����һ��TCP���� */
int netSocketTcpConnect(char *pIp, int port);
/* acceptһ��tcp���ӣ����������Ӻõ�socket */
int netSocketTcpAccept(int listenSocket);


/* socketUdpFunc.c */
/* ��ʼ������UDP����������sock */
int netSocketCreateUdpListenServer(int port);
/* ��ʼ������UDP�ͻ���sock */
int netSocketCreateUdpClient();


/* networkIntface.c */
/* ��������״̬  status == 1ΪUp�� status == 0ΪDown */
int netSetStatus(char *pInterface, int status);
/* ��ȡIp */
int netGetIp(char *pInterface, unsigned int *ip);
/* ����Ip */
int netSetIp(char *pInterface, unsigned int ip);
/* ��ȡ���� */
int netGetGw(char *gateway);
/* �������� */
int netSetGw(char *pInterface, unsigned int gw);
/* ������������ */
int netSetMask(char *pInterface, unsigned int mask);
/* ����mtu��Ԫ */
int netSetMtu(char *pInterface, unsigned int mtu);
/* ����·�� */
int netGetRoute(char *pInterface, unsigned int *route);
/* ����·�� */
int netSetRoute(char *pInterface, unsigned int route);
/* ɾ��·�� */
int netDelRoute(char *pInterface, int gw);
/* ����DNS */
int netSetDns(unsigned int dns1, unsigned int dns2);
/* ���������� */
int netSetHostName(char *pHostName);
/* ��ȡMAC��ַ */
int netGetMac(char *pInterface, unsigned char *pMac);
/*���� MAC��ַ*/
int netSetMac(char *pInterface,char* pMac);
/* ���ip�Ƿ�Ϸ�	����ֵ��>0:�Ϸ� */
int netCheckIpv4(char *pIp);
/* ������������Ƿ�Ϸ�	����ֵ��> 0:�Ϸ� */
int netCheckNetMask(char *pMask);
/*network status*/
int checkNetworkStatus(char* ethname);
/* DNS*/
int GetDNSAddr(char *Dns1, char *Dns2);
/*Mask*/
int GetNetMask(char *EthName,unsigned char *NetMask);

int netGetBro(char *pInterface, unsigned int *ip);
/* epollFunc.c */
int netEpollCreat( int size );
int netEpollClose( int epfd );
int netEpollCtl( int epfd, int op, int fd, struct epoll_event *event );
int netEpollWait( int epfd, struct epoll_event *events, int maxevents, int timeout );

int netEpollCtlAdd( int epfd, int sockfd, uint events );
int netEpollCtlDel( int epfd, int sockfd, uint events );
int netEpollCtlMod( int epfd, int sockfd, uint events );

int GetNetworkFlow(char * interface ,double * recv_rate , double * send_rate);


/* daemon.c */
/* �ػ����� */
void daemonInit();


/* semFunc.c */
/**************************************************************************
 * function: sem_init
 * description: create and initial semaphore
 * input:       int key
 * int sem_num
 * unsigned short int value_array
 * output:      null
 * return:      >0 SUCCEED  other: FAILED
 **************************************************************************/
int Sem_init(int key);

/****************************************************************
 * function:    sem_open
 * discription: open semaphore
 * input:       int key
 * output:      null
 * return:      0: SUCCEED  other: FAILED
 ****************************************************************/
int Sem_open(int key);

/****************************************************************
 * function:    sem_lock
 * description: semaphore lock
 * input:       int sem_id
 *              int sem_num
 * output:      null
 * return:      0:SUCCEED  other: FAILED
 ****************************************************************/
int Sem_lock(int sem_id);

/******************************************************************
 * function:    sem_unlock
 * description: semaphore unlock
 * input:       int sem_id
 * int sem_num
 * output:      null
 * return:      0:SUCCEED  other: FAILED
 ******************************************************************/
int Sem_unlock(int sem_id);

/****************************************************************
 * function:    sem_exit
 * description: semaphore exit
 * input:       int sem_id
 * output:      null
 * return:      0:SUCCEED  other: FAILED
 ***************************************************************/
int Sem_exit(int sem_id);



/* msg_util.c */
int Msg_Init( int msgKey );

int Msg_Send( int qid, void *pdata , int size );

int Msg_Rsv( int qid, int msg_type, void *pdata , int size );

int Msg_Send_Rsv( int qid, int msg_type, void *pdata , int size );

int Msg_Kill( int qid );


/* share_mem.c */
#define PROC_MEM_SIZE 4096*3
#define MAX_SHARE_PROC	12

int ShareMemInit(int key); ///< Initial shared memory.
int pShareMemInit(int key); ///< Initial shared memory for private use .
void ShareMemRead(int offset,void *buf, int length); ///< Read shared memory.
void ShareMemWrite(int offset,void *buf, int length); ///< Write shared memory.




#ifdef __cplusplus
}
#endif


#endif//__COMMON_LIB_H__

