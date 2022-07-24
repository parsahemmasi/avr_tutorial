#include <mega32.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>

#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))

#define led PORTA.5

char text[20];

unsigned int read_adc(unsigned char adc_input)
{
    ADMUX=adc_input | ADC_VREF_TYPE;
    delay_us(10);
    ADCSRA|=(1<<ADSC);
    while ((ADCSRA & (1<<ADIF))==0);
    ADCSRA|=(1<<ADIF);
    return ADCW;
}

void main(void)
{
    DDRA = 0x20;    

    ADMUX=ADC_VREF_TYPE;
    ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
    SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

    lcd_init(16);

    while (1)
    {
        float value = read_adc(4);
        value = value * 5/1023;
        sprintf(text,"Value = %0.2f  ",value);
        lcd_gotoxy(0,0);
        lcd_puts(text);
        
        if ( value > 2.5 )
            led = 1;
        else
            led = 0; 
    }
}
