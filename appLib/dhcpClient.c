
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <time.h>
#include "sdk_struct.h"
#include "LongseDes.h"
#include "global.h"
#include "commonLib.h"
#include "databaseLib.h"
#include "main.h"



void *SetDhcpAdressThread(void *param)
{
	int p_num=0, p_dhcp_time=0;
	sdk_eth_cfg_t p_eth_cfg;
	int GetIpResult = 0;

	int ret=0, result = 0;
	int nRow = 0, nColumn = 0;
	char sql_cmd[512] = {0};
	char **dbResult;
	char *err_msg = NULL;	
	unsigned int IpAddr[2] = {0};
	unsigned char mac[16] = { 0 };
	char GateWay[256] = {0};
	char Dns1[40] = {0}, Dns2[40] = {0};
	unsigned char NetMask[40] = {0}; 
	int dhcpSet=1;
	struct in_addr addr;

	memset(&p_eth_cfg, 0, sizeof(sdk_eth_cfg_t));
	databaseOperate(SDK_MAIN_MSG_NET_LINK_CFG, SDK_PARAM_GET, NULL, 0, &p_eth_cfg, sizeof(sdk_eth_cfg_t));

LOOP:
	Printf("\n\n=======dhcp (%d)========\n\n", p_dhcp_time);
	p_dhcp_time ++;
	system("/usr/share/udhcpc/udhcpc -i eth0 -s /usr/share/udhcpc/default.script &");
	usleep(400*1000);
			
	GetIpResult = -1;	
	while(GetIpResult != 0)
	{
		GetIpResult = netGetIp("eth0", IpAddr);
		if(p_num++ >= 30)    ////3S
		{
			p_num = 0;
			break;
		}
		usleep(100*1000);	///1.2S
	}
	p_num = 0;	
	system("killall -9 udhcpc");

	p_eth_cfg.ip_info.enable_dhcp = 1;
	
	if(GetIpResult == 0)//DHCP�Զ���ȡ�ɹ������ϵͳ�����ļ��ж�ȡ����������Ϣ�����浽���ݿ��У�ͬʱˢ�¼�������������ݡ�
	{
		Printf("\n\n=======dhcp sucess!!!!========\n\n");
		///memset(&p_eth_cfg,0,sizeof(sdk_eth_cfg_t));						  
		// ��ȡ����IP��ַ
		GetIpResult = netGetIp("eth0", IpAddr); 					  
		memcpy(&addr, &IpAddr, 4); 
		sprintf((char *)p_eth_cfg.ip_info.ip_addr,"%s",inet_ntoa((struct in_addr)addr));
		// ��ȡ����IP��ַ
		netGetGw(GateWay);
		if(strlen(GateWay) == 0)
		{
			sprintf((char *)p_eth_cfg.ip_info.gateway,"%s", "0.0.0.0");
		}
		else
		{
			sprintf((char *)p_eth_cfg.ip_info.gateway,"%s", GateWay);
		}
		// ��ȡ����
		GetNetMask("eth0", NetMask);
		sprintf((char *)p_eth_cfg.ip_info.mask,"%s", NetMask);
		// ��ȡDNS
		GetDNSAddr(Dns1, Dns2);
		if(strlen(Dns1) == 0)
		{
			sprintf((char *)p_eth_cfg.ip_info.dns1,"%s", "0.0.0.0");
		}
		else
		{
			sprintf((char *)p_eth_cfg.ip_info.dns1,"%s", Dns1);
		}
		if(strlen(Dns2) == 0)
		{
			sprintf((char *)p_eth_cfg.ip_info.dns2,"%s", "0.0.0.0");
		}
		else
		{
			sprintf((char *)p_eth_cfg.ip_info.dns2,"%s", Dns2);
		}

		ret=databaseOperate(SDK_MAIN_MSG_NET_LINK_CFG,SDK_PARAM_SET,&dhcpSet,sizeof(int),&p_eth_cfg,sizeof(p_eth_cfg));

	}
	else // DHCP��ȡʧ�ܣ�������ݿ��ж�ȡ��������������浽������
	{
		if(p_dhcp_time < 5)
		{
			goto LOOP;
		}
		
		Printf("\n\n=======dhcp error!!!!========\n\n");
		
		// ���������ݱ��浽ϵͳ��������
		netSetIp("eth0", inet_addr((char *)p_eth_cfg.ip_info.ip_addr));
		netSetMask("eth0", inet_addr((char *)p_eth_cfg.ip_info.mask));
		netSetGw("eth0", inet_addr((char *)p_eth_cfg.ip_info.gateway));
		netSetRoute("eth0", inet_addr((char *)p_eth_cfg.ip_info.gateway));
	#ifdef ENABLE_MODIFY_MAC
			//netSetMac("eth0", &p_eth_cfg.ip_info.mac);
	#endif
		netSetDns(inet_addr((char *)p_eth_cfg.ip_info.dns1), inet_addr((char *)p_eth_cfg.ip_info.dns2));
	}

	return NULL;
}



int dhcpNetFun()
{
	return CreatThread(SetDhcpAdressThread,NULL);
}




