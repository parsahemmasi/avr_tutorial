#include <mega32.h>
#include <delay.h>

void motor_speed(signed int speed)
{
    if(speed >= 0)
    {
        PORTD.0 = 0;
        OCR2 = (unsigned char)speed;
    }
    else
    {
        PORTD.0 = 1;
        OCR2 = (unsigned char)(255 + speed);
    } 
        
}

void main(void)
{
    DDRD = 0xFF;

    
    ASSR=0<<AS2;
    TCCR2=(1<<PWM2) | (1<<COM21) | (0<<COM20) | (1<<CTC2) | (0<<CS22) | (1<<CS21) | (0<<CS20);
    TCNT2=0x00;
    OCR2=200;

    TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

    while (1)
    {
        motor_speed(-200);
    }
}
