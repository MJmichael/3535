/*
*******************************************************************************
*
**  : 
*******************************************************************************
*/

#ifndef __DATABASE_LIB_H__
#define __DATABASE_LIB_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "sqlite3.h"

#define ENABLE_MODIFY_MAC     //0�Զ���ȡMAC��ַ 1�ֶ��޸�MAC��ַ

#define TBL_CFG_SIZE	(sizeof(DbMainMsgCfgArr)/sizeof(DbMainCfg))
#define TBL_INIT_SIZE	(sizeof(TblInitArr)/sizeof(DbTblInit))
#define ADD_FIELD_EMPTY   0
#define SELECT_PARA_TURE 		1
#define SELECT_PARA_FALSE 		0	

typedef void (*DbTblCreate)(sqlite3 *db,char *TblName);
typedef void (*DbTblValueInit)(sqlite3 *db,char *TblName);

typedef struct DbTblInit{
    char *TblName;  // ����
    char *AddField;  // �������ֶ���������Ϊ�ա����û�������ֶΣ���ӦΪ����ĳ���Ѵ����ֶ�
    DbTblCreate TblCreate;  // �������ݿ��
    DbTblValueInit  TblValueInit; // ��ʼ����
}DbTblInit;

typedef int (*DbUpdate)(void *data, int len, void *pRecvData, int recvDataLen,sqlite3 *db);
typedef int (*DbSelect)(void *data, int len, void *pRecvData, int recvDataLen,sqlite3 *db);
typedef int (*DbInsert)(void *data, int len, void *pRecvData, int recvDataLen,sqlite3 *db);
typedef int (*DbDelete)(void *data, int len, void *pRecvData, int recvDataLen,sqlite3 *db);
typedef int (*GetGlobalVal)(void *data, int len, void *pRecvData, int recvDataLen);
typedef struct DbMainCfg{
    int MainType; // ������
    DbUpdate DbMainCfgUpdate;  // ���ݿ����
    DbSelect DbMainCfgSelect;     // ���ݿ�ѡ��
    DbInsert DbMainCfgInsert;     // ���ݿ����
    DbDelete DbMainCfgDelete;	// ���ݿ�ɾ��	
    int SelectFlg;				// ���ݿ��ȡ��־
    GetGlobalVal DbGetGlobalPara;    // ��ȡȫ�ֱ���ֵ
}DbMainCfg;


/*  */
void databaseLibInit();

/*  */
//void databaseLibDestroy();

/*
 * 
 * type:	
 * data:	
 * len:		
 * pRecvData:	buf
 * recvDataLen:	
 * */
int databaseOperate(int type, int subType, void *data, int len, void *pRecvData, int recvDataLen);


#ifdef __cplusplus
}
#endif


#endif//__DATABASE_LIB_H__

