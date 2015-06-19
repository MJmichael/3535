#ifndef DISCOVERY_H
#define DISCOVERY_H

#ifdef __cplusplus
extern "C"
{
#endif

/*DSC �� discovery ����д*/
/*������Կ*/
#define DSC_ENCODE_KEY                      "13141314"
/*�㲥�˿�*/
#define DSC_BROADCAST_PORT                  6789
/*У����Ϣ*/
#define DSC_CHECKCODE                       "searching.."
#define DSC_CHECKCODE_LEN                   12
/*��Ϣ����*/
#define DSC_OMT_SEARCH_RESP                 1
#define DSC_OMT_SEARCH                      2
#define DSC_OMT_MODIFY                      3
#define DSC_OMT_MODIFY_RESP                 4

#define DSC_MT_SEARCH                       10
#define DSC_MT_SEARCH_RESP                  11
#define DSC_MT_MODIFY                       12
#define DSC_MT_MODIFY_RESP                  14
/*�豸����*/
#define DSC_DEVTYPE_DVR                     "DVR"
#define DSC_DEVTYPE_IPCAM                   "IPCAMERA"
#define DSC_DEVTYPE_DECODER                 "DECODER"
#define DSC_DEVTYPE_NVR                     "NVR"
/*����*/
#define DSC_MESTYPE_OFFSET                  DSC_CHECKCODE_LEN
#define DSC_MESSAGE_MAXLEN                  1024
#define DSC_DEVTYPE_MAXLEN                  16
#define DSC_DEVNAME_MAXLEN                  64
#define DSC_VERSION_MAXLEN                  64
#define DSC_IPV4ADDR_LEN                    16
#define DSC_MACADDR_LEN                     18
#define DSC_USERNAME_MAXLEN                 32
#define DSC_PASSWORD_MAXLEN                 32

#define DSC_SOFTWARE_VERSION_MAXLEN         64
#define DSC_FIREWARE_VERSION_MAXLEN         64

/*ƽ̨����*/
typedef enum DSC_PLATFORM_TYPE
{
    DSC_PLATFORM_TIIPC_222	            = 0,
    DSC_PLATFORM_TIIPC_238,

    DSC_PLATFORM_HISIPC_3516C_IMX222	=100,
    DSC_PLATFORM_HISIPC_3518C_IMX238,
    DSC_PLATFORM_HISIPC_3518C_OV9712S,
    DSC_PLATFORM_HISIPC_3518E_OV9712S,

    DSC_PLATFORM_HISNVR_3535	        =200,
    DSC_PLATFORM_HISNVR_3520D,
    DSC_PLATFORM_HISNVR_3521,
    DSC_PLATFORM_HISNVR_3531,

    DSC_PLATFORM_ABIPC_A5s66_1080P      = 300,
    DSC_PLATFORM_ABIPC_A5s55_960P,
    DSC_PLATFORM_ABIPC_A5s66_1080P_BOX,
    DSC_PLATFORM_ABIPC_A5s66_1080P_PTZ,
}DSC_PLATFORM_TYPE;

/*������*/
typedef enum DSC_ERRORCODE_TYPE{
    DSC_ERRORCODE_SUCCESS               =  0x00,           /*�ɹ�*/
    DSC_ERRORCODE_VERSION_ERROR,                           /*�汾����*/

    DSC_ERRORCODE_USERPASSWD_ERROR      =  0x10,           /*������û�������*/
    DSC_ERRORCODE_ID_ERROR,                                /*�û�δ��¼*/
    DSC_ERRORCODE_ID_LIMITED,                              /*�û�Ȩ�޲���*/

    DSC_ERRORCODE_CMD_NOSUPPORT         =  0x20,           /*���֧��*/
    DSC_ERRORCODE_ARGE_ERROR,                              /*��������*/
    DSC_ERRORCODE_ARGE_NOSUPPORT,                          /*������֧��*/
}DSC_ERRORCODE_TYPE;

/*Ŀ���ַ*/
typedef struct DSC_TERMINAL_INFO{
    unsigned char   ucIpAddr[DSC_IPV4ADDR_LEN];            /*ip��ַ*/
    unsigned char   ucMacAddr[DSC_MACADDR_LEN];           /*mac ��ַ: ���� A1B2C3D4E5F6 ǰ12λ��Ч.ʣ��4λ��0*/
}DSC_TERMINAL_INFO;

/*�������ó�Ա��Ч��ö��*/
typedef enum DSC_NETWORK_ISVALID{
    DSC_NETWORK_DHCP_VALID              = (1<<1),          /*dhcp*/
    DSC_NETWORK_IP_VALID                = (1<<2),          /*ip*/
    DSC_NETWORK_NETMASK_VALID           = (1<<3),          /*��������*/
    DSC_NETWORK_GATEWAY_VALID           = (1<<4),          /*����*/
    DSC_NETWORK_DNS1_VALID              = (1<<5),          /*DNS1*/
    DSC_NETWORK_DNS2_VALID              = (1<<6),          /*DNS2*/
    DSC_NETWORK_MAC_VALID               = (1<<7),          /*MAC*/
}DSC_NETWORK_ISVALID;


/*����������Ϣ*/
typedef struct DSC_NETWORK_INFO{
    unsigned long   ulMemberIsValid;                       /*��Ա��Ч��*/
    unsigned char   ucDhcpEnable;                          /*dhcp�Ƿ�����: 0�ر�, 1����*/
    unsigned char   ucRes1[3];                             /*����1*/
      unsigned char  ucIpAddr[DSC_IPV4ADDR_LEN];            /*ip��ַ*/
    unsigned char   ucNetmaskAddr[DSC_IPV4ADDR_LEN];       /*��������*/
    unsigned char   ucGatewayAddr[DSC_IPV4ADDR_LEN];       /*���ص�ַ*/
    unsigned char   ucDnsAddr1[DSC_IPV4ADDR_LEN];          /*dns1��ַ*/
    unsigned char   ucDnsAddr2[DSC_IPV4ADDR_LEN];          /*dns2��ַ*/
    unsigned char   ucMacAddr[DSC_MACADDR_LEN];            /*mac ��ַ: ���� A1B2C3D4E5F6 ǰ12λ��Ч.ʣ��4λ��0*/
    unsigned char   ucRes2[16];                            /*����2*/
}DSC_NETWORK_INFO;

/*�豸��Ϣ��Ա��Ч��ö��*/
typedef enum DSC_DEV_ISVALID{
    DSC_DEV_NAME_VALID                  = (1<<1),          /*�豸����*/
    DSC_DEV_HTTPPORT_VALID              = (1<<8),          /*http �˿�*/
    DSC_DEV_RTSPPORT_VALID              = (1<<9),          /*�豸����*/
    DSC_DEV_TCPPORT_VALID               = (1<<10),         /*�豸����*/
    DSC_DEV_PLAYBACKPORT_VALID          = (1<<11),         /*�豸����*/
    DSC_DEV_PRIVATEPORT_VALID           = (1<<12),         /*�豸����*/
}DSC_DEV_ISVALID;
/*�豸��Ϣ*/
typedef struct DSC_DEV_INFO{
    unsigned long   ulMemberIsValid;                       /*��Ա��Ч��*/
    unsigned char   ucDevName[DSC_DEVNAME_MAXLEN];         /*�豸����*/

    unsigned char   ucRes[32];                             /*����*/
    unsigned long   ulHttpPort;                            /*http �˿�*/
    unsigned long   ulRtspPort;                            /*rtsp �˿�*/
    unsigned long   ulTcpPort;                             /*tcp  �˿�*/
    unsigned long   ulPlaybackPort;                        /*�ط� �˿�*/
    unsigned long   ulPrivatePort;                         /*˽��Э��˿�*/
    unsigned char   ucRes1[32];                            /*����*/
}DSC_DEV_INFO;

/*ƽ̨��Ϣ��Ա��Ч��ö��*/
typedef enum DSC_PLATFORM_ISVALID{
    DSC_PLATFORM_CHANNEL_VALID           = (1<<1),          /*ͨ����Ϣ*/
    DSC_PLATFORM_TYPE_VALID              = (1<<2),          /*ƽ̨����*/
    DSC_PLATFORM_DEV_TYPE_VALID          = (1<<3),          /*�豸����*/
    DSC_PLATFORM_SOFTWARE_VERSION_VALID  = (1<<4),          /*����汾*/
    DSC_PLATFORM_FIRMWARE_VERSION_VALID  = (1<<5),          /*�̼��汾*/
}DSC_PLATFORM_ISVALID;

/*ƽ̨��Ϣ*/
typedef struct DSC_PLATFORM_INFO{
    unsigned long   ulMemberIsValid;                                               /*��Ա��Ч��*/
    unsigned char	ucChNum;													   /*ͨ����*/
    unsigned char   ucRes1[3];													   /*����*/
    unsigned long   ucPlatformType;                                                /*ƽ̨����: ��д DSC_PLATFORM_XXX*/
    unsigned char   ucDevType[DSC_DEVTYPE_MAXLEN];                                 /*�豸����: ��д DSC_DEVTYPE_XXX*/
    unsigned char   ucSoftwareVersion[DSC_SOFTWARE_VERSION_MAXLEN];                /*����汾*/
    unsigned char   ucFirmwareVersion[DSC_FIREWARE_VERSION_MAXLEN];                /*�̼��汾*/
    unsigned char   ucRes2[32];													   /*����*/
}DSC_PLATFORM_INFO;


/*�û���Ϣ*/
typedef struct DSC_USER_INFO{
    unsigned char   ucUsername[DSC_USERNAME_MAXLEN];       /*�û���*/
    unsigned char   ucPassword[DSC_PASSWORD_MAXLEN];       /*����*/
}DSC_USER_INFO;

/*�����ṹ��*/
typedef struct DSC_SEARCH_INFO{
    unsigned char            ucCheckCode[DSC_CHECKCODE_LEN];     /*У����: ��д DSC_CHECKCODE*/
    unsigned char            ucMesType;                          /*��Ϣ����: ��д DSC_MT_SEARCH*/
    unsigned char            ucRes1[3];                          /*����1*/
    DSC_TERMINAL_INFO        srcInfo;                            /*Դ��ַ*/
    unsigned char            ucRes2[64];                         /*����2*/
}DSC_SEARCH_INFO;

/*�����ṹ��ظ�*/
typedef struct DSC_SEARCH_RESPONSE_INFO{
    unsigned char            ucCheckCode[DSC_CHECKCODE_LEN];     /*У����: ��д DSC_CHECKCODE*/
    unsigned char            ucMesType;                          /*��Ϣ����: ��д DSC_MT_SEARCH*/
    DSC_NETWORK_INFO         networkInfo;                        /*����������Ϣ*/
    DSC_DEV_INFO             devInfo;                            /*�豸��Ϣ*/
    DSC_PLATFORM_INFO        playformInfo;                       /*ƽ̨��Ϣ*/
    DSC_USER_INFO            userInfo;                           /*�û���Ϣ*/
}DSC_SEARCH_RESPONSE_INFO;

/*�޸Ľṹ��*/
typedef struct DSC_MODIFY_INFO{
    unsigned char            ucCheckCode[DSC_CHECKCODE_LEN];     /*У����: ��д DSC_CHECKCODE*/
    unsigned char            ucMesType;                          /*��Ϣ����: ��д DSC_MT_SEARCH*/
    unsigned char            ucRes1[3];                          /*����1*/
    DSC_TERMINAL_INFO        srcInfo;                            /*�ն���Ϣ*/
    DSC_TERMINAL_INFO        dstInfo;                            /*�ն���Ϣ*/
    DSC_NETWORK_INFO         networkInfo;                        /*����������Ϣ*/
    DSC_DEV_INFO             devInfo;                            /*�豸��Ϣ*/
    DSC_USER_INFO            securityInfo;                       /*��ȫ��Ϣ*/
}DSC_MODIFY_INFO;

/*�޸�����ظ��ṹ��*/
typedef struct DSC_MODIFY_RESPONSE_INFO{
    unsigned char           ucCheckCode[DSC_CHECKCODE_LEN];      /*У����: ��д DSC_CHECKCODE*/
    unsigned char           ucMesType;                           /*��Ϣ����: ��д DSC_MESTYPE_MODIFY_RESPONSE*/
    unsigned char           ucErrorCode;                         /*��д������*/
    unsigned char           ucRes1[2];                           /*����1*/ 
    DSC_TERMINAL_INFO       dstInfo;                             /*�ն���Ϣ*/
    DSC_NETWORK_INFO        networkInfo;                         /*����������Ϣ*/
    DSC_DEV_INFO            devInfo;                             /*�豸��Ϣ*/
}DSC_MODIFY_RESPONSE_INFO;

/********************************************************************************************/
/*******************************          OLD        ***************************************/
/********************************************************************************************/
/*�����ظ��ṹ��*/
typedef struct DSC_SEARCH_RESPONSE_OINFO{
    unsigned char   ucCheckCode[DSC_CHECKCODE_LEN];        /*У����: ��д DSC_CHECKCODE*/
    unsigned char   ucMesType;                             /*��Ϣ����: ��д DSC_MESTYPE_SEARCH_RESPONSE*/

    unsigned char   ucDevType[DSC_DEVTYPE_MAXLEN];         /*�豸����: ��д DSC_DEVTYPE_XXX*/
    unsigned char   ucMacAddr[7];                          /*mac��ַ: ��д����,��0-5λ��Ч,��6λ��0*/
    unsigned char   ucIpAddr[DSC_IPV4ADDR_LEN];            /*ip��ַ*/
    unsigned char   ucNetmaskAddr[DSC_IPV4ADDR_LEN];       /*��������*/
    unsigned char   ucGatewayAddr[DSC_IPV4ADDR_LEN];       /*���ص�ַ*/
    unsigned char   ucDnsAddr[DSC_IPV4ADDR_LEN];           /*dns��ַ*/

    unsigned char   ucDevName[DSC_DEVNAME_MAXLEN];         /*�豸����*/
    unsigned char   ucVersion[DSC_VERSION_MAXLEN];         /*�汾��Ϣ*/
    unsigned long   ulDevModel;
    unsigned long   ulHttpPort;                            /*��ҳ�˿�*/
    unsigned long   ulRtspPort;                            /*rtsp �˿�*/
    unsigned long   ulMobilePort;
    unsigned long   ulTcpPort;                             /*tcp �˿�*/
    unsigned long   ulPlaybackPort;                        /*�ط� �˿�*/

    unsigned char   ucDhcpEnable;                          /*dhcp�Ƿ�ʹ��: 0�ر� 1ʹ��*/
    unsigned char   ucChNum;                               /*�û�ͨ����: DVRNVR �����ͨ������,IPC��д 1*/
    unsigned char   ucRes1[2];                             /*����*/
    DSC_USER_INFO   userInfo;                              /*�û���Ϣ*/
}DSC_SEARCH_RESPONSE_OINFO;

/*�޸�����ṹ��*/
typedef struct DSC_MODIFY_OINFO{
    unsigned char   ucCheckCode[DSC_CHECKCODE_LEN];        /*У����: ��д DSC_CHECKCODE*/
    unsigned char   ucMesType;                             /*��Ϣ����: ��д DSC_MESTYPE_MODIFY*/

    unsigned char   ucIpAddr[DSC_IPV4ADDR_LEN];            /*ip��ַ*/
    unsigned char   ucIpAddrNew[DSC_IPV4ADDR_LEN];         /*�µ�ip��ַ*/
    unsigned char   ucNetmaskAddr[DSC_IPV4ADDR_LEN];       /*��������*/
    unsigned char   ucGatewayAddr[DSC_IPV4ADDR_LEN];       /*���ص�ַ*/
    unsigned char   ucDnsAddr[DSC_IPV4ADDR_LEN];           /*dns��ַ*/
    unsigned char   ucMacAddr[7];                          /*mac��ַ: ��д����,��0-5λ��Ч,��6λ��0*/

    unsigned long   ulHttpPort;                             /*��ҳ�˿�*/
    unsigned long   ulRtspPort;                            /*rtsp �˿�*/
    unsigned long   ulMobilePort;
    unsigned char   ucDhcpEnable;                          /*dhcp�Ƿ�ʹ��: 0�ر� 1ʹ��*/
    unsigned char   ucRes1[2];                             /*����*/

    unsigned char   ucResetVieoConfig;                     /*������Ƶ����: 0������ 1����*/
    DSC_USER_INFO   userInfo;                              /*�û���Ϣ*/
}DSC_MODIFY_OINFO;


typedef struct 
{
      unsigned char  ucIpAddr[DSC_IPV4ADDR_LEN];    
      unsigned char ucErrorCode ;
	  int state ;
}NetConfigResponse;

#ifdef __cplusplus
}
#endif
#endif


/********************************************************************************************/
/*******************************       ��������        ***************************************/
/********************************************************************************************/
/* ͨ�Ź���:
 *    �������豸ʹ�� UDP �㲥������ͨ��.
 *
 *    UDP��ͷǰ 12(DSC_CHECKCODE_LEN)���ֽ�����У�鵱ǰUDP���Ƿ����ڱ���������
 *    ������д "searching.." (DSC_CHECKCODE)
 *    ��������:�� DSC_BROADCAST_PORT ����UDP�㲥socket. ���ڼ����������޸�����
 *
 * �����豸:
 *    �ͻ���: ����һ��UDP�㲥socket. �˿ڿ���Ϊ������� 1024 ����ֵ
 *    ���㲥��ַ(255.255.255.255)��(DSC_BROADCAST_PORT)�˿ڷ����豸������(DSC_SEARCH_INFO)
 *    DSC_SEARCH_INFO.ucMesType = DSC_MT_SEARCH;
 *    ��������: ���յ��豸������У�������.
 *    ���Զ�UDP�˿ڹ㲥һ���豸�����ظ��� (DSC_SEARCH_RESPONSE_INFO)
 *    DSC_SEARCH_RESPONSE_INFO.ucMesType = DSC_MESTYPE_SEARCH_RESPONSE;
 *    DSC_SEARCH_RESPONSE_INFO ��userInfo.ucPassword ��Ҫʹ�� des ����.������ԿĬ��Ϊ DSC_ENCODE_KEY
 *	  DSC_SEARCH_INFO.srcInfo ��д�ͻ��˵�ip��mac��ַ. ���ڹ��˱��豸�Լ�������������.
 *
 * �޸��豸����:
 *    �ͻ���: ����һ��UDP�㲥socket. �˿ڿ���Ϊ������� 1024 ����ֵ
 *    ���㲥��ַ(255.255.255.255)��(DSC_BROADCAST_PORT)�˿ڷ��Ͳ����޸İ�(DSC_MODIFY_INFO)
 *    DSC_MODIFY_INFO.ucMesType = DSC_MESTYPE_MODIFY;
 *
 *    DSC_MODIFY_INFO.srcInfo ��д������Ϣ
 *    DSC_MODIFY_INFO.dstInfo ��д�Զ���Ϣ
 *    DSC_MODIFY_INFO.securityInfo ��д�û���������
 *    DSC_MODIFY_INFO.networkInfo �� DSC_MODIFY_INFO.devInfo Ϊ�����޸ĵ�ѡ��
 *
 *    DSC_NETWORK_INFO.ulMemberIsValid ��ʾ��Ա�Ƿ���Ч.
 *    �����ֻ���޸�ip��ַ.���� DSC_NETWORK_INFO.ulMemberIsValid |= DSC_NETWORK_IP_VALID;
 *    �����ʾ�������ṹ����ֻ�� ip ��Ա����Ч��.
 *    ��� DSC_NETWORK_INFO.ulMemberIsValid = DSC_NETWORK_IP_VALID | DSC_NETWORK_DHCP_VALID;
 *    ��ʾ IP �� dhcp ͬʱ��Ч.
 *    DSC_DEV_INFO �� DSC_PLATFORM_INFO �����Ƶ��÷�.
 *
 *    ��������: �Ӳ����޸İ�, (�Ա�Ŀ��ip��ַ��mac��ַ�Ƿ�Ϊ����ip��mac��ַ.������Ǻ��������.)
 *    ���Զ�UDP�˿ڹ㲥һ���豸�����ظ��� (DSC_MODIFY_RESPONSE_INFO)
 *    DSC_MODIFY_RESPONSE_INFO.ucMesType = DSC_MESTYPE_MODIFY_RESPONSE;
 *    У�������:
 *       �ɹ�ʱ:             DSC_MODIFY_RESPONSE_INFO.ucErrorCode = DSC_ERRORCODE_SUCCESS.
 *                          ���ݰ������޸ı�������.
 *       ʧ��ʱ:             DSC_MODIFY_RESPONSE_INFO.ucErrorCode =  ���������.
 *
 *
 *
 *
 *
*/














