#include <lcd_mmr.h>


int main(void)
{
    lcd_ini();
    uint8_t count=250;
    while (1)
    {
	    _delay_ms(500);
	    count++;
	    lcd_num(count, 0,6);
    }
}

