#include <mega32.h>
#include <alcd.h>
#include <delay.h>
#include <stdio.h>

#define button PINB.2

int x = 0;
int y = 0;
char text[20];

interrupt [EXT_INT2] void ext_int2_isr(void)
{
    y++;
}

void main(void)
{
    DDRA = 0xFF;
    
    PORTB = 0xFF;    

    GICR|=(0<<INT1) | (0<<INT0) | (1<<INT2);
    MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
    MCUCSR=(0<<ISC2);
    GIFR=(0<<INTF1) | (0<<INTF0) | (1<<INTF2);

    lcd_init(16);

    #asm("sei")

    while (1)
    {
        sprintf(text,"Timer : %d  ",x++);   
        lcd_gotoxy(0,0);
        lcd_puts(text);
        sprintf(text,"Count : %d  ",y);   
        lcd_gotoxy(0,1);
        lcd_puts(text);
        
        delay_ms(500);
    }
}
