#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include "commonLib.h"
#include "desCode.h"
#include "sdk_struct.h"
#include "main.h"
#include "databaseLib.h"
#include "myThreadLib.h"

#define BUFSIZE 16
#define SERVER_PORT 8765
#define DES_KEY "12345678"
#define QueryCmd "1" 

/*
��������: �����ݿ�����ӳ����û���Ϣ


*/
static int AddSuperUsrInfo(char *SuPwd, int PwdLen)
{
       int ret=0;
	char *SuUsrName = "root";
	sdk_user_right_t UserRightInfo;
	memset(&UserRightInfo,0,sizeof(UserRightInfo));
	memcpy(UserRightInfo.user.user_name, SuUsrName, strlen(SuUsrName));
	memcpy(UserRightInfo.user.user_pwd, SuPwd, strlen(SuPwd));
	UserRightInfo.local_right = 0x0000FFFF;
	//Printf("Usr:%s    Pwd:%s    localright:%x  \n",UserRightInfo.user.user_name, UserRightInfo.user.user_pwd, UserRightInfo.local_right);
	ret=databaseOperate(SDK_MAIN_MSG_USER, SDK_USER_DEL, &UserRightInfo, sizeof(UserRightInfo), NULL, 0);// ��ɾ����ԭ���ĳ����û����ٲ���
	if(ret<0)
	{
		Printf("Add super user info failed!\n");
	}
	
	ret=databaseOperate(SDK_MAIN_MSG_USER, SDK_USER_ADD, &UserRightInfo, sizeof(UserRightInfo), NULL, 0);
	if(ret<0)
	{
		Printf("Add super user info failed!\n");
	}
	return 0;
}

/*
	��������:�������һ��6λ���������ݣ�������Щ����ת�����ַ���


*/
static int RandInt6(char *chRand)
{
	int a = 0;
	srand(time(NULL));
	a = rand()%90000 + 100000 * (rand() % 9 + 1); 
	sprintf(chRand, "%d", a); 
	return 0;
}
/*
��������: TCP����������ɳ����û�����ӡ����ɼ������ݲ����͵��ͻ��˵Ĺ��ܡ�
                        ϵͳ�������һֱ����TCP�ͻ��˵�����

*/
static int TcpComKey()
{
  int s = 0;
  int fd = 0;
  int len = 0;
  char SuPwd[8] = {0};
  struct sockaddr_in my_addr;
  struct sockaddr_in remote_addr;
  socklen_t sin_size = 0;
  char RevBuf[BUFSIZE] = {0};
  char desEnReult[17] = {0};
  char SendBuf [64] = {0};
  sin_size = sizeof (struct sockaddr_in);
  bzero(&my_addr, sizeof (my_addr));
  my_addr.sin_family = AF_INET;
  my_addr.sin_addr.s_addr = INADDR_ANY;
  my_addr.sin_port = htons (SERVER_PORT);

  
  setPthreadPriority(PTHREAD_SCHEDULED_PRIORITY_LOW_EST);

    if ((s = socket (PF_INET, SOCK_STREAM, 0)) < 0)
    {
      perror ("socket");
      close (s);
      return -1;
    }
    if (bind (s, (struct sockaddr *) &my_addr, sizeof (struct sockaddr)) < 0)
    {
      perror ("bind");
      close (s);
      return -1;
    }
    while (1)
    {
    	usleep(50*1000);
        listen (s, 5);
        if ((fd = accept (s, (struct sockaddr *) &remote_addr, &sin_size)) < 0)
        {
            perror ("accept");
            close (fd);
            continue;
        }
        Printf ("accept client %s\n", inet_ntoa (remote_addr.sin_addr));
        memset(RevBuf,0,sizeof(RevBuf));
	 memset(desEnReult,0,sizeof(desEnReult));
	 memset(SendBuf,0,sizeof(SendBuf));
	 len = send (fd, "Connect Ok!\n", 21, 0);
        if(len < 0)
        {
            close (fd);
            continue;
        }
        len = recv (fd, RevBuf, BUFSIZE, 0);
        if((len > 0)&&(strcmp(RevBuf, QueryCmd) == 0))
        {
            RevBuf[len] = '\0';
	     //Printf ("Server recieve:%s\n", RevBuf);
	     RandInt6(SuPwd);
	     //Printf("ADMIN KEY:%s",SuPwd);
	     AddSuperUsrInfo(SuPwd, strlen(SuPwd));
	     DesEncode(desEnReult, SuPwd, DES_KEY);
	    // Printf("Your Message is Encrypted:%s\n",desEnReult);  // ��Ϣ�Ѽ���
	     //sprintf(SendBuf, "rand:%s    enc:%s", SuPwd, desEnReult);
	     memcpy(SendBuf,desEnReult,strlen(desEnReult));
	     //Printf("======desEnReult:%s\n",SendBuf);
            if (send (fd, SendBuf, sizeof(SendBuf), 0) < 0)
            {
                perror ("write");
                close (fd);
                continue;
            }
        }
        close(fd);
  }
  close (fd);
  close (s);
  return 0;
}
/*
��������: �̺߳���



*/
static void *pthKey()
{
    TcpComKey();
    return NULL;
}

/*
��������:���̵߳�������windows�������豸��һЩ���С���ߵ�ͨ�Žӿڣ������һЩ�����С����
                       �����ȡ�������롢�޸�MAC��ַ�ȡ�����δ����---hejunying2014.7.22
˵��:�������ֻ��ϵͳ������ʱ�����
*/
int TCPComTools()
{
    pthread_t pthid;
    if(pthread_create(&pthid,NULL,pthKey,NULL)!=0)
    {
        Printf("Create thread error!\n");
        return -1;
    }
    return 0;
}

