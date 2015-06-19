#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <unistd.h>
#include <pthread.h>
#include "sdk_struct.h"
#include "commonLib.h"
#include "main.h"
#include "myThreadLib.h"
#include <errno.h>
#include "ddnsCom.h"

static unsigned char g_DdnsThreadRun = 0;
static unsigned int g_DdnsUpdatFlg = 1;// DDNS��Ϣ�����ı�ı�־

void  DdnsUpdate(int UpdateFlg)
{
	g_DdnsUpdatFlg = UpdateFlg;
	Printf("===========g_DdnsUpdatFlg:%d\n",g_DdnsUpdatFlg);
}

// DDNS�̣߳�����NVR��DNS��������ͨ���Լ�DNS�������������ݵĴ���
//static void *DdnsClientThread()
static void * DdnsClientThread(char *arg, int argLen)
{
	int ret = 0;
	unsigned char  DdnsType = 0;
	sdk_ddns_cfg_t ddns[MAX_DDNS_TYPE];	
	ddns_cfg_t pddns;
	time_t tnow, tbef[MAX_DDNS_TYPE]={0,};
	setPthreadPriority(PTHREAD_SCHEDULED_PRIORITY_LOW_EST);
	
	while(1==g_DdnsThreadRun)
	{
		tnow = time(NULL);	
	
		if(g_DdnsUpdatFlg)// ��DDNS����Ϣ�仯ʱ����������ddns��������
		{
			for(DdnsType = 0; DdnsType < MAX_DDNS_TYPE; DdnsType++)
			{
				/////����ˢ��һ��DDNS
				tbef[DdnsType] = tnow - ddns[DdnsType].interval; 
				memset(&ddns[DdnsType],0,sizeof(sdk_ddns_cfg_t));	
				ret=databaseOperate(SDK_MAIN_MSG_DDNS_CFG, SDK_PARAM_GET, &DdnsType, 0, &ddns[DdnsType], sizeof(sdk_ddns_cfg_t));

				if(ret<0)
				{
					fprintf(stderr,"databaseOperate  SDK_MAIN_MSG_DDNS_CFG	read  fail %s:%d\n",__FILE__,__LINE__);
				}
			}

			g_DdnsUpdatFlg = 0;
		}
		else
		{
			for(DdnsType = 0; DdnsType < MAX_DDNS_TYPE; DdnsType++)
			{
				if(!ddns[DdnsType].enable || (tnow-tbef[DdnsType]) < ddns[DdnsType].interval)
				{
					continue;
				}

				if((strlen((char *)ddns[DdnsType].user) ==0)||(strlen((char *)ddns[DdnsType].pwd)==0)||(strlen((char *)ddns[DdnsType].domain)==0))
				{
					////�����κ�һ��������������������DDNS
					continue;
				}
		
				////memset(j_ddns, 0, sizeof(j_ddns));
				pddns.type = ddns[DdnsType].type;
				strcpy(pddns.user, ddns[DdnsType].user);
				strcpy(pddns.pwd, ddns[DdnsType].pwd);
				strcpy(pddns.domain, ddns[DdnsType].domain);
				
				StartDdns(&pddns);
				usleep(1000);
			}

			usleep(800*1000);

		}
		
	}
	return NULL;
}


// DDNS��ں���,��Ҫ���ڴ���DDNS�߳�
int StartDdnsThread()
{
	if(g_DdnsThreadRun == 1)
	{
		return 0;
	}
	
	g_DdnsThreadRun = 1; // ֻ����һ���߳�
	if(threadPoolAddWorker(NULL, DdnsClientThread, NULL, 0) != 0)
	{
		Printf("ddns thread create error !\n");
		return -1;
	}

	return 0;
}

int StopDdnsThread()
{
	if(g_DdnsThreadRun == 0)
	{
		return 0;
	}

	g_DdnsThreadRun = 0;
	//pthread_join(g_DdnsThreadRun, NULL);

	return 0;
}

