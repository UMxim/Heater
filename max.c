#include "iostm8s003f3.h"
#include "max.h"
#define ST PD_ODR_ODR2 
#define SH PD_ODR_ODR3
#define DS PD_ODR_ODR1

//------------------------------------------------------------------------------
void Delay(unsigned long i)
{
  for (unsigned long delay_count=0; delay_count<i; delay_count++); asm"nop";
};  
//------------------------------------------------------------------------------
/*void ByteTo595 (u8 byte)
{
  ST = 0;
  for (u8 i=8;i>0;i--)
  { 
    SH = 0;    
    DS = ((byte>>(i-1))&&1);
    SH = 1;  
  };
  ST = 1;
}*/
//------------------------------------------------------------------------------
struct divmod10_t
{
    u32 quot;
    u8 rem;
};

 divmod10_t divmodu10(u32 n)
{
    divmod10_t res;
// умножаем на 0.8
    res.quot = n >> 1;
    res.quot += res.quot >> 1;
    res.quot += res.quot >> 4;
    res.quot += res.quot >> 8;
    res.quot += res.quot >> 16;
    u32 qq = res.quot;
// делим на 8
    res.quot >>= 3;
// вычисляем остаток
    res.rem =  (n - ((res.quot << 1) + (qq & ~7ul)));
// корректируем остаток и частное
    if(res.rem > 9)
    {
        res.rem -= 10;
        res.quot++;
    }
    return res;
};

char * utoa_fast_div(u32 value, char *buffer)
{
    buffer += 11;
    *--buffer = 0;
    do
    {
        divmod10_t res = divmodu10(value);
        *--buffer = res.rem + '0';
        value = res.quot;
    }
    while (value != 0);
    return buffer;
};
//------------------------------------------------------------------------------