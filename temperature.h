//ћодуль дл€ датчика температуры 104 и резистора 51кќм 

#include "max.h"
# define TCHANEL 6 // канал дл€ ADC
void InitTemperature (void);
float TemperatureMeasuring(u8);// TemperatureMeasuring(N) делает 2^N измерений , усредн€ет и возвращает температуру  

