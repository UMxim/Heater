#include "init.h"
#include "iostm8s003f3.h"
#include "max.h"

//====INIT======================================================================
void Init(void)
{
//----GPIO----------------------------------------------------------------------  
 PA_DDR_DDR3 = 1; PA_CR1_C13 = 1; PA_CR2_C21 = 0; //
// PA_DDR_DDR2 = 1; PA_CR1_C11 = 1; PA_CR2_C22 = 0; //

 
//----CLOCK-------------------------------------------------------------def2Mh  
  CLK_CKDIVR_HSIDIV = 0;// 16Mhz
  
  //----INTERRUPTS----------------------------------------------------------------
  asm("rim"); //��������� ����������
//----TIM1----------------------------------------------------------------------  
/*  TIM1_CR1_ARPE = 1; //buffered ARR ���������� �� ��������� ��������
  TIM1_CR1_OPM = 0; //one puls mode off
  TIM1_CR1_URS = 0;//interrupt overflow ���������� ������ �� ������������ ���������
  TIM1_CR1_UDIS = 0;    // ��� ����������
  TIM1_CCMR3_OC3M = 0x6;//  pwm1
  TIM1_CCMR3_OC3PE = 0; //������������ �������� 
  TIM1_CCMR3_CC3S = 0; // ��������� ������ �� �����
  TIM1_CCER2_CC3P = 0; //OC1 active high
  TIM1_CCER2_CC3E = 1; //�������� �����
  TIM1_CCMR4_OC4M = 0x6;//  pwm1
  TIM1_CCMR4_OC4PE = 0; //������������ �������� 
  TIM1_CCMR4_CC4S = 0; // ��������� ������ �� �����
  TIM1_CCER2_CC4P = 0; //OC1 active high
  TIM1_CCER2_CC4E = 1; //�������� �����
  TIM1_BKR_MOE = 1;// �������� �����
 // TIM1_PSCRL = 0; TIM1_PSCRH = 0; // prescaller 1
 // TIM1_ARRH = 0; TIM1_ARRL = 0xFF;// ������� �� 256
 // TIM1_CCR3H = 0; TIM1_CCR3L = 255; //�������� 
  TIM1_EGR_UG = 1;
  TIM1_CR1_CEN = 1;  //start timer ��������� ����������    */  
//----TIM2----------------------------------------------------------------------  
  TIM2_CR1_ARPE = 1;//buffered ARR ���������� �� ��������� ��������
  TIM2_CR1_OPM = 0; //one puls mode off
  TIM2_CR1_URS = 0;//interrupt overflow ���������� ������ �� ������������ ���������
  TIM2_CR1_UDIS = 0;    // ��� ����������
  TIM2_IER_UIE = 1; // NO INTERRUPT
 // TIM2_CR1_URS = 1; //interrupt only overflow
 // TIM2_CR1_UDIS = 0; //update disable =0
 // TIM2_IER_UIE = 1;//update interrupt enable
  
  TIM2_CCMR3_OC3M = b110;//  pwm1
  TIM2_CCMR3_OC3PE = 1; //������������ �������� 
  TIM2_CCMR3_CC3S = 0; // ��������� ������ �� �����
  TIM2_CCER2_CC3P = 0; //OC1 active high
  TIM2_CCR3H = 0; TIM2_CCR3L = 0;// duty 0%
  TIM2_CCER2_CC3E = 1; //�������� �����
  
  TIM2_PSCR = 6; //prescaler ==64  2^6 250khz
  TIM2_ARRH = 0xF4;  TIM2_ARRL = 0x24; //62500 4Hz
  //
  
  TIM2_CR1_CEN = 1;

//----TIM4----------------------------------------------------------------------  
  TIM4_CR1_URS = 1; //interrupt only overflow
  TIM4_CR1_UDIS = 0; //update disable =0
  TIM4_IER_UIE = 1;//update interrupt enable
  TIM4_PSCR = 7; //prescaler ==128  2^7 
  TIM4_ARR = 0x7D; //1000Hz
  
  TIM4_CR1_CEN = 1;

  
//----UART----------------------------------------------------------------------

  
};  