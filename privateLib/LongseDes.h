
#ifndef _LONGSE_DES_H_
#define _LONGSE_DES_H_

//���岿������
typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned char BOOLEAN;

#define TRUE	1
#define FALSE	0

//Ϊ����߳���Ч�ʣ���������λ�������ܶ����ںꡣ

//��ȡ��������ָ��λ.
#define PP_GET_BIT(p_array, bit_index)  \
            ((p_array[(bit_index) >> 3] >> (7 - ((bit_index) & 0x07))) & 0x01)

//���û�������ָ��λ.
#define PP_SET_BIT(p_array, bit_index, bit_val) \
            if (1 == (bit_val)) \
            {\
                p_array[(bit_index) >> 3] |= 0x01 << (7 - ((bit_index) & 0x07));\
            }\
            else\
            {\
                p_array[(bit_index) >> 3] &= ~(0x01 << (7 - ((bit_index) & 0x07)));\
            }

//�ӽ��ܱ�ʶ����������ʶ�漰���Ա�Ķ�ȡλ��,
//���뱣֤DES_ENCRYPT = 0 DES_DECRYPT = 1
typedef enum
{
    DES_ENCRYPT = 0,
    DES_DECRYPT = 1
}PP_DES_MODE;

///////////////////////////////////////////////////////////////
//	�� �� �� : des
//	�������� : DES�ӽ���
//	������� : ���ݱ�׼��DES�����㷨�������64λ��Կ��64λ���Ľ��м�/����
//				������/���ܽ���洢��p_output��
//	ʱ    �� : 2006��9��2��
//	�� �� ֵ :
//	����˵�� :	const char * p_data		����, ����ʱ��������, ����ʱ��������, 64λ(8�ֽ�)
//				const char * p_key		����, ��Կ, 64λ(8�ֽ�)
//				char * p_output			���, ����ʱ�������, ����ʱ��������, 64λ(8�ֽ�)
//				uint8 mode				0 ����  1 ����
///////////////////////////////////////////////////////////////
void PP_Des(const char * p_data, const char * p_key, const char * p_output, PP_DES_MODE mode);


void PP_DES_Encode(char *outData, char *inData, char *key, int len);
void PP_DES_Decode(char *outData, char *inData, char *key, int len);


#endif //#ifndef _DES_H_
