/*-------------------------------------------------------
      Data Encryption Standard  56λ��Կ����64λ���� 
--------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include "desTables.h"
/*-------------------------------
 ��DatIn��ʼ�ĳ���λLenλ�Ķ�����
 ���Ƶ�DatOut��
--------------------------------*/
void BitsCopy(DesBool *DatOut,DesBool *DatIn,int Len)     // ���鸴�� OK 
{
	int i=0;
	for(i=0;i<Len;i++)
	{
		DatOut[i]=DatIn[i];
	}
}

/*-------------------------------
 �ֽ�ת����λ���� 
 ÿ8�λ�һ���ֽ� ÿ��������һλ
 ��1��ȡ���һλ ��64λ 
--------------------------------*/
void ByteToBit(DesBool *DatOut,char *DatIn,int Num)       // OK
{
	int i=0;
	for(i=0;i<Num;i++)
	{
		DatOut[i]=(DatIn[i/8]>>(i%8))&0x01;   
	}                                       
}

/*-------------------------------
 λת�����ֽں���
 �ֽ�����ÿ8����һλ
 λÿ�������� ����һ�λ�   
---------------------------------*/
void BitToByte(char *DatOut,DesBool *DatIn,int Num)        // OK
{
	int i=0;
	for(i=0;i<(Num/8);i++)
	{
		DatOut[i]=0;
	} 
	for(i=0;i<Num;i++)
	{
		DatOut[i/8]|=DatIn[i]<<(i%8);	
	}		
}


/*----------------------------------
 ����������ת��Ϊʮ������
 ��Ҫ16���ַ���ʾ
-----------------------------------*/
void BitToHex(char *DatOut,DesBool *DatIn,int Num)
{
	int i=0;
	for(i=0;i<Num/4;i++)
	{
		DatOut[i]=0;
	}
	for(i=0;i<Num/4;i++)
	{
		DatOut[i] = DatIn[i*4]+(DatIn[i*4+1]<<1)
					+(DatIn[i*4+2]<<2)+(DatIn[i*4+3]<<3);
		if((DatOut[i]%16)>9)
		{
			DatOut[i]=DatOut[i]%16+'7';       //  ��������9ʱ���� 10-15 to A-F
		}                                     //  ����ַ� 
		else
		{
			DatOut[i]=DatOut[i]%16+'0';       //  ����ַ�	   
		}
	}
	
}

/*---------------------------------------------
 ʮ�������ַ�ת������
----------------------------------------------*/
void HexToBit(DesBool *DatOut,char *DatIn,int Num)
{
	int i=0;                        // �ַ������� 
	for(i=0;i<Num;i++)
	{
		if((DatIn[i/4])>'9')         //  ����9 
		{
			DatOut[i]=((DatIn[i/4]-'7')>>(i%4))&0x01;   			
		}
		else
		{
			DatOut[i]=((DatIn[i/4]-'0')>>(i%4))&0x01; 	
		} 
	}	
}

// ���û�����  OK
void TablePermute(DesBool *DatOut,DesBool *DatIn,const char *Table,int Num)  
{
	int i=0;
	static DesBool Temp[256]={0};
	for(i=0;i<Num;i++)                // NumΪ�û��ĳ��� 
	{
		Temp[i]=DatIn[Table[i]-1];  // ԭ�������ݰ���Ӧ�ı��ϵ�λ������ 
	}
	BitsCopy(DatOut,Temp,Num);       // �ѻ���Temp��ֵ��� 
} 

// ����Կ����λ
void LoopMove(DesBool *DatIn,int Len,int Num) // ѭ������ Len���ݳ��� Num�ƶ�λ��
{
	static DesBool Temp[256]={0};    // ����   OK
	BitsCopy(Temp,DatIn,Num);       // ����������ߵ�Numλ(���Ƴ�ȥ��)����Temp 
	BitsCopy(DatIn,DatIn+Num,Len-Num); // ��������߿�ʼ�ĵ�Num����ԭ���Ŀռ�
	BitsCopy(DatIn+Len-Num,Temp,Num);  // ���������Ƴ�ȥ�����ݼӵ����ұ� 
} 

// ��λ���
void Xor(DesBool *DatA,DesBool *DatB,int Num)           // �����
{
	int i=0;
	for(i=0;i<Num;i++)
	{
		DatA[i]=DatA[i]^DatB[i];                  // ��� 
	}
} 

// ����48λ ���32λ ��Ri���
void S_Change(DesBool DatOut[32],DesBool DatIn[48])     // S�б任
{
	int i,X,Y;                                    // iΪ8��S�� 
	for(i=0,Y=0,X=0;i<8;i++,DatIn+=6,DatOut+=4)   // ÿִ��һ��,��������ƫ��6λ 
	{    										  // ÿִ��һ��,�������ƫ��4λ
		Y=(DatIn[0]<<1)+DatIn[5];                          // af����ڼ���
		X=(DatIn[1]<<3)+(DatIn[2]<<2)+(DatIn[3]<<1)+DatIn[4]; // bcde����ڼ���
		ByteToBit(DatOut,&S_Box[i][Y][X],4);      // ���ҵ��ĵ����ݻ�Ϊ������	
	}
}

// F����
void F_Change(DesBool DatIn[32],DesBool DatKi[48])       // F����
{
	static DesBool MiR[48]={0};             // ����32λͨ��Eѡλ��Ϊ48λ
	TablePermute(MiR,DatIn,E_Table,48); 
	Xor(MiR,DatKi,48);                   // ������Կ���
	S_Change(DatIn,MiR);                 // S�б任
	TablePermute(DatIn,DatIn,P_Table,32);   // P�û������
}



void SetKey(char *KeyIn)               // ������Կ ��ȡ����ԿKi 
{
	int i=0;
	static DesBool KeyBit[64]={0};                // ��Կ�����ƴ洢�ռ� 
	static DesBool *KiL=&KeyBit[0],*KiR=&KeyBit[28];  // ǰ28,��28��56
	ByteToBit(KeyBit,KeyIn,64);                    // ����ԿתΪ�����ƴ���KeyBit 
	TablePermute(KeyBit,KeyBit,PC1_Table,56);      // PC1���û� 56��
	for(i=0;i<16;i++)
	{
		LoopMove(KiL,28,Move_Table[i]);       // ǰ28λ���� 
		LoopMove(KiR,28,Move_Table[i]);	      // ��28λ���� 
	 	TablePermute(SubKey[i],KeyBit,PC2_Table,48); 
	 	// ��ά���� SubKey[i]Ϊÿһ����ʼ��ַ 
	 	// ÿ��һ��λ����PC2�û��� Ki 48λ 
	}		
}

void DesEncode(char *MesOut,char *MesIn,char *MyKey)  // ִ��DES����
{                                           // �ֽ����� Bin���� Hex��� 
	int i=0;
	static DesBool MesBit[64]={0};        // ���Ķ����ƴ洢�ռ� 64λ
	static DesBool Temp[32]={0};
	static DesBool *MiL=&MesBit[0],*MiR=&MesBit[32]; // ǰ32λ ��32λ 
	SetKey(MyKey);               // ������Կ �õ�����ԿKi
	ByteToBit(MesBit,MesIn,64);                 // �����Ļ��ɶ����ƴ���MesBit
	TablePermute(MesBit,MesBit,IP_Table,64);    // IP�û� 
	for(i=0;i<16;i++)                       // ����16�� 
	{
		BitsCopy(Temp,MiR,32);            // ��ʱ�洢
		F_Change(MiR,SubKey[i]);           // F�����任
		Xor(MiR,MiL,32);                  // �õ�Ri 
		BitsCopy(MiL,Temp,32);            // �õ�Li 
	}					
	TablePermute(MesBit,MesBit,IPR_Table,64);
	BitToHex(MesOut,MesBit,64);
}

void DesDecode(char *MesOut,char *MesIn,char *YourKey)       // ִ��DES����
{												// Hex���� Bin���� �ֽ���� 
	int i=0;
	static DesBool MesBit[64]={0};        // ���Ķ����ƴ洢�ռ� 64λ
	static DesBool Temp[32]={0};
	static DesBool *MiL=&MesBit[0],*MiR=&MesBit[32]; // ǰ32λ ��32λ
	SetKey(YourKey);                                       // ������Կ
	HexToBit(MesBit,MesIn,64);                 // �����Ļ��ɶ����ƴ���MesBit
	TablePermute(MesBit,MesBit,IP_Table,64);    // IP�û� 
	for(i=15;i>=0;i--)
	{
		BitsCopy(Temp,MiL,32);
		F_Change(MiL,SubKey[i]);
		Xor(MiL,MiR,32);
		BitsCopy(MiR,Temp,32);
	}	
	TablePermute(MesBit,MesBit,IPR_Table,64);
	BitToByte(MesOut,MesBit,64);		
} 