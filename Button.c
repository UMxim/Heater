#include "Button.h"
#include "max.h"
#include "iostm8s003f3.h" 

//---var's----------------------------------------------------------------------
u8 pin[NUMBER_OF_BUTTON]; //реальное состояние на ножке
u16 time[NUMBER_OF_BUTTON];//время нажатия
u8 fshort[NUMBER_OF_BUTTON];//флаг короткого нажатия. очищается юзером
u8 flong[NUMBER_OF_BUTTON];//флаг длинного нажатия. очищается при отпускании кнопки. все равно успеешь обработать

//---functions------------------------------------------------------------------
void Init_button(void)
{
  INIT_BUTTON_1; // инит кнопки 1
  #if NUMBER_OF_BUTTON > 1 //если кнопок больше 1 то и вторую
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
  if (pin[N]) //если нажали
  {
    time[N] ++; //считаем длительность нажатия
    if (time[N] > BUTTON_MAX_TIME) flong[N] = 1; //если долго то фиксируем долгое нажатие
  };
  
  if (!pin[N] && time[N] ) // если отпустили
  {
    if (time[N] > BUTTON_MAX_TIME) flong[N] = 0; //если долго то чистим флаг
    fshort[N] = 1;// фиксируем короткое
    time[N] = 0; //обнуляем время нажатия    
  };  
};
//------------------------------------------------------------------------------
void Reset_button (u8 i)// обнуляем флаги и время кнопки
{
  time[i] = 0;
  fshort[i] = 0;
  flong[i] = 0;
};
//------------------------------------------------------------------------------
u8 Double_button(u8 A, u8 B) // детектор двойного нажатия 1-если есть 0-нет
{ u16 temp = BUTTON_MAX_TIME>>1;  // мах время деленое на 2
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
  pin[0] = BUTTON_1;//  в переменную значение соотв. ноги
  #if NUMBER_OF_BUTTON > 1 //если кнопок больше 1 то и вторую
  pin[1] = BUTTON_2;  
  #elif NUMBER_OF_BUTTON > 2
  pin[2] = BUTTON_3;
  #elif NUMBER_OF_BUTTON > 3
  pin[3] = BUTTON_4;
  #endif
  
  for(u8 i=0;i<NUMBER_OF_BUTTON;i++) Update_button(i);
};