#include <mega32.h>
#include <alcd.h>
#include <stdio.h>

char text[20];
int x = 0;
int y = 0;

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
    x++;
    if ( x == 100)
    {
        y++;
        x = 0;
    }
}

void main(void)
{
    TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
    TCNT0=0x00;
    OCR0=0x00;

    TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);

    lcd_init(16);
    
    #asm("sei")

    while (1)
    {
        sprintf(text,"TCNT0= %d  ",TCNT0); 
        lcd_gotoxy(0,0);
        lcd_puts(text); 
        
        sprintf(text,"x= %d  ",x); 
        lcd_gotoxy(0,1);
        lcd_puts(text);
        
        sprintf(text,"y= %d  ",y); 
        lcd_gotoxy(6,1);
        lcd_puts(text);
    }
}
