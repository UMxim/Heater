#include "max.h"

#define BUTTON_MAX_TIME 1000 // максимальное количество тиков для фиксации длительного нажатия. при 1КГц здесь 1 секунда
#define NUMBER_OF_BUTTON 2 // количество кнопок 1,2,3 или 4

#define INIT_BUTTON_1 PA_DDR_DDR1 = 0; PA_CR1_C11 = 1; PA_CR2_C21 = 0 // input pullup nointerrupt
#define INIT_BUTTON_2 PA_DDR_DDR2 = 0; PA_CR1_C12 = 1; PA_CR2_C22 = 0 // input pullup nointerrupt
#define INIT_BUTTON_3 PA_DDR_DDR2 = 0; PA_CR1_C12 = 1; PA_CR2_C22 = 0 // input pullup nointerrupt
#define INIT_BUTTON_4 PA_DDR_DDR2 = 0; PA_CR1_C12 = 1; PA_CR2_C22 = 0 // input pullup nointerrupt

#define BUTTON_1 !(PA_IDR_IDR1) // реверс. нажатие если 0
#define BUTTON_2 !(PA_IDR_IDR2)
#define BUTTON_3 !(PA_IDR_IDR2)
#define BUTTON_4 !(PA_IDR_IDR2)

#define B_UP 0 // тут просто для наглядности чтобы в массиве не цифрами, а названиями было
#define B_DOWN 1
#define B_LEFT 2
#define B_RIGHT 3

void Init_button(void); //функция инициализации ног кнопокю смотри INIT_BUTTON_X
void Update_buttons (void); // здесь считываем состояния, обновляем флаги и таймер
u8 Double_button(u8, u8); // детектор двойного нажатия. возвращает 0 или 1. на входе номера кнопок для сканирования 0..3

extern u8 fshort[NUMBER_OF_BUTTON];//флаг короткого нажатия. очищается юзером. пример fshort[B_DOWN]
extern u8 flong[NUMBER_OF_BUTTON];//флаг длинного нажатия. очищается при отпускании кнопки. все равно успеешь обработать. пример flong[B_RIGHT]