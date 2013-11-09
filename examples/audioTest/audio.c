#include <avr/io.h>

#define F_CPU 2500000UL

#include <util/delay.h>
#include <avr/pgmspace.h>

#include "sin.h"

/*

Function To Initialize TIMER0 In Fast
PWWM Mode.

*/
void InitPWM()
{
   /*
   TCCR0 - Timer Counter Control Register (TIMER0)
   -----------------------------------------------

   BITS DESCRIPTION
   
   NO:   NAME   DESCRIPTION
   --------------------------
   BIT 7 : FOC0   Force Output Compare [Not used in this example]
   BIT 6 : WGM00  Wave form generartion mode [SET to 1]

   BIT 5 : COM01  Compare Output Mode        [SET to 1]
   BIT 4 : COM00  Compare Output Mode        [SET to 0]
   BIT 3 : WGM01  Wave form generartion mode [SET to 1]
   BIT 2 : CS02   Clock Select               [SET to 0]
   BIT 1 : CS01   Clock Select               [SET to 0]
   BIT 0 : CS00   Clock Select               [SET to 1]

   The above settings are for
   --------------------------
   Timer Clock = CPU Clock (No Prescalling)
   Mode        = Fast PWM
   PWM Output  = Non Inverted

   */


   TCCR0A|=(1<<WGM00)|(1<<WGM01)|(1<<COM0A1)|(1<<CS00);

   //Set OC0 PIN as output. It is  PB3 on ATmega16 ATmega32

   DDRB|=(1<<DDB2);
}

void main()
{
   uint8_t i;

   InitPWM();

   while(1)
   {

      uint8_t delay,n;

      for(delay=1;delay<=50;delay++)
      {
         for(n=0;n<(51-delay);n++)
         {
            for(i=0;i<=254;i++)
            {
               OCR0A=pgm_read_byte_near(sine+i);
               _delay_loop_2(delay);

            }
         }
      }
      for(delay=50;delay>=2;delay--)
      {
         for(n=0;n<(51-delay);n++)
         {
            for(i=0;i<=254;i++)
            {
               OCR0A=pgm_read_byte_near(sine+i);
               _delay_loop_2(delay);
            }
         }
      }

   }
}
