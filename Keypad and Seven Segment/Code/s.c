#include <mega32.h>                     //io registers 
#include <delay.h>                      // for using delay function

#define column_0 PORTD.4                //defining columns of keypad
#define column_1 PORTD.5
#define column_2 PORTD.6
#define column_3 PORTD.7

#define row_0 PIND.3                    //defining rows of keypad
#define row_1 PIND.2
#define row_2 PIND.1
#define row_3 PIND.0

#define digit_1 PORTC.4                 //defining seven segment digit enable pins
#define digit_2 PORTC.5
#define digit_3 PORTC.6
#define digit_4 PORTC.7

#define seven_segment_port PORTB        //defining portb as seven_segment_port

unsigned char seven_segment_digit[10];          //for showing digits with seven segment

int row=0;                                      //global row and column variables
int column=0;

int keypad[4][4]={{0,0,0,0},{1,2,3,0},{4,5,6,0},{7,8,9,0}};    //keypad in array!

void show_number(int input)
{
    digit_1=1;
    seven_segment_port=~seven_segment_digit[0];
    delay_ms(10);
    digit_1=0;
    digit_2=1;
    seven_segment_port=~seven_segment_digit[0];
    delay_ms(10);
    digit_2=0;
    digit_3=1;
    seven_segment_port=~seven_segment_digit[0];
    delay_ms(10);
    digit_3=0;
    digit_4=1;
    seven_segment_port=~seven_segment_digit[input];
    delay_ms(10);
    digit_4=0;
    
}
void scan_keypad(void)
{
    DDRD=0xF0;                               //for scaning keypad
    PORTD=0x0F;
    
    if(!(row_0 == 1 && row_1 == 1 && row_2 == 1 && row_3 == 1))
    delay_ms(20);                                                  //debauncing switches
    if(!(row_0 == 1 && row_1 == 1 && row_2 == 1 && row_3 == 1))
    {
       if(row_0 == 0)
            row=0;
       else if(row_1 == 0 )
            row=1;
       else if(row_2 == 0 )
            row=2;
       else if(row_3 == 0 )
            row=3; 
            
       column_0=0;
       column_1=1;
       column_2=1;
       column_3=1;
       if(!(row_0 == 1 && row_1 == 1 && row_2 == 1 && row_3 == 1))
            column=0;
       else 
       {
            column_0=1;
            column_1=0;
            column_2=1;
            column_3=1;
            if(!(row_0 == 1 && row_1 == 1 && row_2 == 1 && row_3 == 1))
            column=1;
            else 
            {
                column_0=1;
                column_1=1;
                column_2=0;
                column_3=1;
                if(!(row_0 == 1 && row_1 == 1 && row_2 == 1 && row_3 == 1))
                column=2;
                else 
                {
                       column_0=1;
                       column_1=1;
                       column_2=1;
                       column_3=0;
                       if(!(row_0 == 1 && row_1 == 1 && row_2 == 1 && row_3 == 1))
                            column=3;
                }
            }
       }
    }
}

void main(void)
{                                            
    DDRB=0XFF;                         //for seven segment
    DDRC=0xF0;
    
    DDRD=0xF0;                         //for keypad
    PORTD=0x0F;
    
    seven_segment_digit[0]=0b00111111;              //showing digits in seven segment
    seven_segment_digit[1]=0b00000110;
    seven_segment_digit[2]=0b01011011;
    seven_segment_digit[3]=0b01001111;
    seven_segment_digit[4]=0b01100110;
    seven_segment_digit[5]=0b01101101;
    seven_segment_digit[6]=0b01111101;
    seven_segment_digit[7]=0b00000111;
    seven_segment_digit[8]=0b01111111;
    seven_segment_digit[9]=0b01101111;    

    while(1)
    { 
        scan_keypad();
        show_number(keypad[row][column]);
    }
}