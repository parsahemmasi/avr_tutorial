#include <mega32.h>
#include <delay.h>

#define seven_segment PORTA
#define button PINB.5

unsigned char digit[10];

int count = 0;

void main(void)
{
    DDRA = 0xFF;
    
    DDRB = 0x00;
    PORTB = 0x20;
    
    digit[0] = 0b11111100;
    digit[1] = 0b01100000;
    digit[2] = 0b11011010;
    digit[3] = 0b11110010;
    digit[4] = 0b01100110;
    digit[5] = 0b10110110;
    digit[6] = 0b10111110;
    digit[7] = 0b11100000;
    digit[8] = 0b11111110;
    digit[9] = 0b11110110;
    
    
    while (1)
    {   
        seven_segment = digit[count];

        if(!button)
        {
            delay_ms(20);
            
            while(!button);
            
            count++;
            if(count == 10)
                count = 0;
        }
    }
}
