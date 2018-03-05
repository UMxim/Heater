#include "LSD.h"
#include "max.h"
#include "iostm8s003f3.h" 


//------------------------------------------------------------------------------
u8 pos = 3 ;// ������� �������. ����� ������ ������ � ������ ������. 3, ����� ���� ���� �� 2 ����� 1 � 0     0123
u8 update_part = 0; //������� ������� ���������� ��� ������������� ����������
u8 posSeg=0; //������� ������� �����
u8 Digit[13]= {b11101101,b00101000,b10110101,b10111001,b01111000,b11011001,b11011101,b10101000,b11111101,b11111001,b00010000,b00000010,0};//0 1 2 3 4 5 6 7 8 9 - .�����   �������������� �������!!!!!!!!!
u8 LSD[4]; //�����  �����.����������
//------------------------------------------------------------------------------
void InitLSD (void)
{ 
#if defined(HC595) // ���� ����� ������� �� ������ 3 ������
  // ��� ���-�� ����
#else // ������ �����. ��� 8 ��� 
 INIT_A; INIT_B; INIT_C; INIT_D; INIT_E; INIT_F; INIT_G; INIT_H; //������������� ���
#endif  
 
INIT_G3; //������������� ����� 4-��� ����������. �� ���� ������. ��������� ������
#if N_INDICATORS == 2 // ���� ����������� 2, �� ������������� � 3-�� ����������. ��������� �������
  INIT_G2;
#endif
#if N_INDICATORS == 3  
  INIT_G1;
  INIT_G2;
#endif
#if N_INDICATORS == 4    
  INIT_G0;
  INIT_G1;
  INIT_G2;
#endif

 };

//------------------------------------------------------------------------------

void DataLSD ( s16 number, u8 dot0, u8 dot1, u8 dot2, u8 dot3)                  //      -----A-----
{                                                                               //    |             |
  u8 D0,D1,D2,D3,temp,flag_minus=12;                                            //    |             |
  if (number<0)                                                                 //    B             C
  {                                                                             //    |             |
    number=(0-number);                                                          //    |             |
    flag_minus=10;                                                              //      -----D-----
  };                                                                            //    |             |
  D0 = (number / 1000); // ����� ������� �� 1000. �� 9547/1000=9                //    |             |
  temp = (number % 1000); // ������� �� ������� 9547%1000=547                   //    F             E  
  D1 = (temp / 100); // ����� ������� �� 100 547/100=5                          //    |             |
  temp = (temp % 100); // ������� �� ������� 547%100=47                         //    |             |
  D2 = (temp / 10); //����� ������� �� 10 47/10=4                               //      -----H-----   *G
  D3 = (temp % 10);// ������� �� ������� 47%10=7                                //
  LSD[0] = Digit[D0];
  LSD[1] = Digit[D1];
  LSD[2] = Digit[D2];
  LSD[3] = Digit[D3];
  
  if (D0==0) LSD[0]=Digit[flag_minus];// ���� ����� ���� ���� ������
  if (D0==1) LSD[0]=(Digit[flag_minus] | Digit[1]);
  if ((D0==0)&&(D1==0)) LSD[1]=Digit[flag_minus] ;// ���� ��� ������, ���� ����� � �����.
  if ((D1==0)&&(D2==0)) LSD[2]=Digit[flag_minus] ;// ���� ��� ������, ���� ����� � �����.

  if (dot0) LSD[0]+=Digit[11]; //��������� �����
  if (dot1) LSD[1]+=Digit[11];
  if (dot2) LSD[2]+=Digit[11];
  if (dot3) LSD[3]+=Digit[11];
};

//------------------------------------------------------------------------------

void UpdateLSD (void)
{  
  switch (pos) //��������� ��������������� ���������
  {    
    case 0: {G0=1;break;};
    case 1: {G1=1;break;};
    case 2: {G2=1;break;};
    case 3: {G3=1;break;};
  };
#if defined(HC595) // ���� ����� ������� �� ������ 3 ������
  //ByteTo595LSD(LSD[pos]);
#else // ������ �����. ��� 8 ���  
  
  #if defined(SEGMENT_UPDATE)  // ��������� �����������
  LA=0;LB=0;LC=0;LD=0;LE=0;LF=0;LG=0;LH=0;
  
  if (update_part==7)
  {
    update_part=0;
    if ( pos > (4 - N_INDICATORS)) pos--; else pos= 3; // �� ����� 3..2..1..0..3 ��� 4 �����������
  } else update_part++;
  
  
  switch (update_part)
  {
  case 0: {LA= 1 & (LSD[pos]>>7); break; };
  case 1: {LB= 1 & (LSD[pos]>>6); break; };
  case 2: {LC= 1 & (LSD[pos]>>5); break; };
  case 3: {LD= 1 & (LSD[pos]>>4); break; };
  case 4: {LE= 1 & (LSD[pos]>>3); break; };
  case 5: {LF= 1 & (LSD[pos]>>2); break; };
  case 6: {LG= 1 & (LSD[pos]>>1); break; };
  case 7: {LH= 1 & (LSD[pos]); break; };
  };
  
  
  #else
  if ( pos > (4 - N_INDICATORS)) pos--; else pos= 3; // �� ����� 3..2..1..0..3 ��� 4 �����������  
  
  LA= 1 & (LSD[pos]>>7);
  LB= 1 & (LSD[pos]>>6);
  LC= 1 & (LSD[pos]>>5);
  LD= 1 & (LSD[pos]>>4);
  LE= 1 & (LSD[pos]>>3);
  LF= 1 & (LSD[pos]>>2);
  LG= 1 & (LSD[pos]>>1);
  LH= 1 & (LSD[pos]);

  #endif
#endif
  
  switch (pos) //�������� ��������������� ���������
  {    
    case 0: {G0=0;break;};
    case 1: {G1=0;break;};
    case 2: {G2=0;break;};
    case 3: {G3=0;break;};
  };
};
