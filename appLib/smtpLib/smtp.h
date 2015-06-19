#ifndef __EMAILLIB_H__
#define __EMAILLIB_H__

typedef struct Smtp_Email
{
	char *pHost;				// ���������� 
	char *pLoginName;			// ���� �˺� 
	char *pLoginPassword;		// ��½���� 
	char *pSendFrom;			// ���� �˺� 
	char *pSendTo;				// �����˺� 
	char *pSendCc;				//  ����,ÿ���ʼ���ַ֮�����Ҫ�Էֺ�;�����Ҳ��Ϊ��
	char *pDate;				//   ����ʱ�䣬ʱ��+800 ��ʾ����ʱ�� 
	char *pEmailSubject;		//  �ʼ���  
	char *pMessage;				//  �ʼ���ʾ������ 
	char *pFileName;			// �ʼ����� ������������Ϊ NULL 
	unsigned short port;		//��SMTPʹ��SSLʱ����˿ںű���Ϊ465����ʹ��ʱ��25.������ֻʹ��SSL������˿ں���Ϊ465
}st_smtp;


int SendEmail(st_smtp *s);


#endif

