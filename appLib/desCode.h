/*
*******************************************************************************
*
**  : 
*******************************************************************************
*/

#ifndef __DES_CODE_H
#define __DES_CODE_H

#ifdef __cplusplus
extern "C" {
#endif
void DesEncode(char *MesOut,char *MesIn,char MyKey[8]);  // ִ��DES����
void DesDecode(char *MesOut,char *MesIn,char YourKey[8]);       // ִ��DES����
#ifdef __cplusplus
}
#endif


#endif//__DES_CODE_H
