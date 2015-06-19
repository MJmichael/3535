/*
*******************************************************************************
**  
**  : epoll,epoll
*******************************************************************************
*/
#ifndef __QUEUE_LIB_H__
#define __QUEUE_LIB_H__


#ifdef __cplusplus
extern "C" {
#endif


/* cycleQueue.c */
/* ����ѭ���������� */
typedef int queueCycleElemType;
typedef struct
{
	queueCycleElemType  *base;//Ԫ��
	int front;//��һ��
	int rear;//���һ��
	int maxQueueNum;//�����е���Ŀ
}CYCLE_QUEUE_T;

/* 1����ʼ��ѭ������ */
void queueCycleInit(CYCLE_QUEUE_T *Q, int maxQueueNum);
/* 2������ѭ������ */
void queueCycleDestroy(CYCLE_QUEUE_T *Q);
/* 3�����ѭ������ */
void queueCycleClear(CYCLE_QUEUE_T *Q);
/* 4���жϿն��� */
int queueCycleEmpty(CYCLE_QUEUE_T Q);
/* 5����ѭ�����г��� */
int queueCycleLength(CYCLE_QUEUE_T Q);
/* 6��ȡ��ͷԪ�� */
void queueCycleGetHead(CYCLE_QUEUE_T Q, queueCycleElemType *e);
/* 7������� */
int queueCycleIn(CYCLE_QUEUE_T *Q, queueCycleElemType e);
/* 8�������� */
int queueCycleOut(CYCLE_QUEUE_T *Q, queueCycleElemType *e);
/* 9������ѭ�����в����Ԫ�� */
void queueCycleTraverse(CYCLE_QUEUE_T Q);





/* linkQueue.c */
/* ������ʽ�������� */
typedef struct link_queue_data_t
{
	int type;//����
	char data[1024];
}link_queue_data_t;
typedef link_queue_data_t queueLinkElemType;
typedef struct QNode
{
	queueLinkElemType elemData;
	struct QNode *next;
}QNode, *QueuePtr;
typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LINK_QUEUE_T;

/* 1����ʼ����ʽ���� */
void queueLinkInit(LINK_QUEUE_T *Q);
/* 2��������ʽ���� */
void queueLinkDestroy(LINK_QUEUE_T *Q);
/* 3�������ʽ���� */
void queueLinkClear(LINK_QUEUE_T *Q);
/* 4���жϿն��� */
int queueLinkEmpty(LINK_QUEUE_T Q);
/* 5������ʽ���г��� */
int queueLinkLength(LINK_QUEUE_T Q);
/* 6��ȡ��ͷԪ�� */
queueLinkElemType *queueLinkGetHead(LINK_QUEUE_T Q);
/* 7������� */
void queueLinkIn(LINK_QUEUE_T *Q, queueLinkElemType e);
/* 8�������� */
int queueLinkOut(LINK_QUEUE_T *Q, queueLinkElemType *e);
/* 9��������ʽ���в����Ԫ�� */
void queueLinkTraverse(LINK_QUEUE_T Q);
/* Լɪ������ */
void queueLinkJoseffer(int n);



#ifdef __cplusplus
}
#endif


#endif//__QUEUE_LIB_H__

