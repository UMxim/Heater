#include "Button.h"
#include "max.h"
#include "iostm8s003f3.h" 

//---var's----------------------------------------------------------------------
u8 pin[NUMBER_OF_BUTTON]; //�������� ��������� �� �����
u16 time[NUMBER_OF_BUTTON];//����� �������
u8 fshort[NUMBER_OF_BUTTON];//���� ��������� �������. ��������� ������
u8 flong[NUMBER_OF_BUTTON];//���� �������� �������. ��������� ��� ���������� ������. ��� ����� ������� ����������

//---functions------------------------------------------------------------------
void Init_button(void)
{
  INIT_BUTTON_1; // ���� ������ 1
  #if NUMBER_OF_BUTTON > 1 //���� ������ ������ 1 �� � ������
  INIT_BUTTON_2;
  #elif NUMBER_OF_BUTTON > 2 
  INIT_BUTTON_3;
  #elif NUMBER_OF_BUTTON > 3 
  INIT_BUTTON_4;
  #endif
};
//------------------------------------------------------------------------------

void Update_button(u8 N)
{
  if (pin[N]) //���� ������
  {
    time[N] ++; //������� ������������ �������
    if (time[N] > BUTTON_MAX_TIME) flong[N] = 1; //���� ����� �� ��������� ������ �������
  };
  
  if (!pin[N] && time[N] ) // ���� ���������
  {
    if (time[N] > BUTTON_MAX_TIME) flong[N] = 0; //���� ����� �� ������ ����
    fshort[N] = 1;// ��������� ��������
    time[N] = 0; //�������� ����� �������    
  };  
};
//------------------------------------------------------------------------------
void Reset_button (u8 i)// �������� ����� � ����� ������
{
  time[i] = 0;
  fshort[i] = 0;
  flong[i] = 0;
};
//------------------------------------------------------------------------------
u8 Double_button(u8 A, u8 B) // �������� �������� ������� 1-���� ���� 0-���
{ u16 temp = BUTTON_MAX_TIME>>1;  // ��� ����� ������� �� 2
  if ( (time[A]>temp) && (time[B]>temp) )
  {
    Reset_button ( A );
    Reset_button ( B );
    return 1;
  } 
  else return 0;
};
//------------------------------------------------------------------------------

void Update_buttons (void)
{
  pin[0] = BUTTON_1;//  � ���������� �������� �����. ����
  #if NUMBER_OF_BUTTON > 1 //���� ������ ������ 1 �� � ������
  pin[1] = BUTTON_2;  
  #elif NUMBER_OF_BUTTON > 2
  pin[2] = BUTTON_3;
  #elif NUMBER_OF_BUTTON > 3
  pin[3] = BUTTON_4;
  #endif
  
  for(u8 i=0;i<NUMBER_OF_BUTTON;i++) Update_button(i);
};