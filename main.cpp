#include "iostm8s003f3.h"   // подключение заголовочного файла с объявлениями регистров. масок и битов
#include "max.h"
#include "init.h"
#include "temperature.h"
#include "LSD.h"
#include "Button.h"


//__interrupt void TIM4_OVR_UIF_handler(void);

//----Var & Def ----------------------------------------------------------------
#pragma location=0x4000
__no_init u8 flash_var[3];

u16 freq10, freq4, freq25 ;
u8 Digit_to_LSD;
u8 dot_real = 0; //отображение точки плановых показаний // 0 реальная температура, 1- целевая
u8 dot_duty ;// отображаем 1- скважность 0-температура
u8 temp;
u8 state; // !!!!!!!!!!!!!!!!!!!!!!!!! from flash
u8 need_temperature; // !!!!!!!!!!!!!!!!! from flash
u8 need_duty = 0; //!!!!!!!!!!!!!!!!!!!!!!!!!!! from flash
u16 duty; //текущая скважность
u8 real_temperature = 0;
u16 hold_and_write = 0; //если 1 то показываем целевую температуру и записываем ее во флеш

//---- funct -------------------------------------------------------------------

void Write_to_flash()
{
  FLASH_DUKR = 0xAE;
  FLASH_DUKR = 0x56; 
  flash_var[0] = need_temperature;
  flash_var[1] = need_duty;
  flash_var[2] = state;
};

void Read_from_flash(void)
{
  need_temperature = flash_var[0]; 
  need_duty = flash_var[1];
  state = flash_var[2];
};



//==== MAIN ====================================================================
int main(void) // Основная программа
{//initTemperature();
Init();
InitLSD();
InitTemperature();
Init_button();
Read_from_flash();

if (state) 
{ 
  temp = need_duty;
  dot_duty = 1;
  TIM2_ARRH = 0x09;  TIM2_ARRL = 0xC4; //2500 100Hz !!!!!!!!!!!!!!!!!!!!!!!!!!!
}
else 
{ 
  temp = need_temperature;
  dot_duty = 0;
  TIM2_ARRH = 0xF4;  TIM2_ARRL = 0x24; //62500 4Hz
};

while(1) {};     // Бесконечный цикл
};

//==== INTERRUPTS ==============================================================

// Вектор прерывания по обновлению или переполнению Таймера2
#pragma vector = TIM4_OVR_UIF_vector 
__interrupt void TIM4_OVR_UIF_handler(void)
{ 
  TIM4_SR_UIF = 0;  // очистили флаг
  // 10Hz
  if (freq10 == 100)// создаем частота 10 Гц
    {
    freq10 = 0;
    
    DataLSD (Digit_to_LSD, 0,0, 0, dot_duty);
    
    if ( Double_button(B_UP, B_DOWN) ) 
      switch (state)
      {
      case 0:  //переключаемся с температуры на скважность
        state = 1;
        need_temperature = temp;// сохраняем текущую температуру
        temp = need_duty;// работаем со скважностью
        dot_duty = 1; //точка !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        hold_and_write = 1000; //кажем секунду и пишем во флеш
        break;
      case 1:
        state = 0;
        need_duty = temp;
        temp = need_temperature;// работаем с
        dot_duty = 0; //not точка**********************************************************
        hold_and_write = 1000; //кажем секунду и пишем во флеш
        break;
      };
    
    if (fshort[B_UP] == 1)     {fshort[B_UP]   = 0; temp++ ; hold_and_write = 1000;};
    if (fshort[B_DOWN] == 1)   {fshort[B_DOWN] = 0; temp-- ; hold_and_write = 1000;};
   
    if  ( flong[B_UP]   ) {temp++; hold_and_write = 1000;};
    if  ( flong[B_DOWN] ) {temp--; hold_and_write = 1000;};
    
    if (temp>99) temp=99;
    if (temp<1) temp=1;
    
    real_temperature = (u8) TemperatureMeasuring(4);
    
    
    if (state) 
    {
      need_duty = temp; 
      TIM2_ARRH = 0x09;  TIM2_ARRL = 0xC4; //2500 100Hz 
      duty = 25*need_duty;
      TIM2_CCR3H = (duty>>8); TIM2_CCR3L = (duty & b11111111);// duty 0%
    }
    else
    {
      need_temperature = temp;
      TIM2_ARRH = 0xF4;  TIM2_ARRL = 0x24; //62500 4Hz
    
    
      TIM2_CCR3H = (duty>>8); TIM2_CCR3L = (duty & b11111111);// duty 0%
    };
    
    
    }   else freq10 ++;// конец 10 гц
  // end 10Hz
  
  
  
  if (hold_and_write == 1000) Digit_to_LSD = temp;
  if (hold_and_write == 1) Write_to_flash();   
  if (hold_and_write) hold_and_write --; else Digit_to_LSD = real_temperature;

 
  
  
  
  UpdateLSD ();
  Update_buttons();
 
} ;

 // Вектор прерывания по обновлению или переполнению Таймера2
#pragma vector = TIM2_OVR_UIF_vector 
__interrupt void TIM2_OVR_UIF_handler(void)
{ 
  TIM2_SR1_UIF = 0;  // очистили флаг
    if ( duty>59999 ) duty = 60000;//62500-2500=60000
      if ( duty<2500) duty = 2500;
      if (real_temperature <=  need_temperature)  duty+=2500;  else duty-=2500;
      
};
 //TIM2_CCR3H = 0x7A; TIM2_CCR3L = 0x12;// duty 50%
//==== function ================================================================
