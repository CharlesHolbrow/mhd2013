#include <avr/io.h>

#define F_CPU 2500000UL
#include <util/delay.h>

#include "output.h"

// Button  PA3 (pin 10)
#define BUTTON_UP (PINA & (1 << PINA3))
#define BUTTON_DOWN !BUTTON_UP

// Our second binary connected to a 0.1 inch header
#define OPEN (PINA & (1 << PINA2))
#define CLOSED !OPEN

int main()
{
  // Turn button pull up resistor on by setting PA2 and PA3
  PORTA |= (1 << 3) | (1 << 2);

  // Clock  divider - Data sheet Page 82
  TCCR0B = (0<<CS02) | (1<<CS01) | (1<<CS00); // does not effect _delay_ms()

  init_pwm();

  for(;;)
  {
    if (CLOSED || BUTTON_DOWN){
      led_level(255);
      out_on();
    }
    else
    {
      led_level(0);
      out_off();
    }
  }

}


