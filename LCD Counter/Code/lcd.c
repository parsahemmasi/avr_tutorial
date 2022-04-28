#include <mega32.h>
#include <alcd.h>
#include <delay.h>
#include <stdio.h>

int x = 0;
char text[20];

void main(void)
{
    DDRA=0xFF;    

    lcd_init(16);
    
    while (1)
    {
        delay_ms(1000);
        x++;
        sprintf(text,"Count= %d  ",x);
        lcd_gotoxy(0,0);
        lcd_puts(text);
    }
}
