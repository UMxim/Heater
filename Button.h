#include "max.h"

#define BUTTON_MAX_TIME 1000 // ������������ ���������� ����� ��� �������� ����������� �������. ��� 1��� ����� 1 �������
#define NUMBER_OF_BUTTON 2 // ���������� ������ 1,2,3 ��� 4

#define INIT_BUTTON_1 PA_DDR_DDR1 = 0; PA_CR1_C11 = 1; PA_CR2_C21 = 0 // input pullup nointerrupt
#define INIT_BUTTON_2 PA_DDR_DDR2 = 0; PA_CR1_C12 = 1; PA_CR2_C22 = 0 // input pullup nointerrupt
#define INIT_BUTTON_3 PA_DDR_DDR2 = 0; PA_CR1_C12 = 1; PA_CR2_C22 = 0 // input pullup nointerrupt
#define INIT_BUTTON_4 PA_DDR_DDR2 = 0; PA_CR1_C12 = 1; PA_CR2_C22 = 0 // input pullup nointerrupt

#define BUTTON_1 !(PA_IDR_IDR1) // ������. ������� ���� 0
#define BUTTON_2 !(PA_IDR_IDR2)
#define BUTTON_3 !(PA_IDR_IDR2)
#define BUTTON_4 !(PA_IDR_IDR2)

#define B_UP 0 // ��� ������ ��� ����������� ����� � ������� �� �������, � ���������� ����
#define B_DOWN 1
#define B_LEFT 2
#define B_RIGHT 3

void Init_button(void); //������� ������������� ��� ������� ������ INIT_BUTTON_X
void Update_buttons (void); // ����� ��������� ���������, ��������� ����� � ������
u8 Double_button(u8, u8); // �������� �������� �������. ���������� 0 ��� 1. �� ����� ������ ������ ��� ������������ 0..3

extern u8 fshort[NUMBER_OF_BUTTON];//���� ��������� �������. ��������� ������. ������ fshort[B_DOWN]
extern u8 flong[NUMBER_OF_BUTTON];//���� �������� �������. ��������� ��� ���������� ������. ��� ����� ������� ����������. ������ flong[B_RIGHT]