#include <avr/io.h>

#include "output.h"

void init_pwm()
{
  // Enable output on the LED PA7/PIN6
  DDRA |= (1 << 7);
  // Configure OC0A/PB2/Pin5 as output
  DDRB |= (1 << 2);

  // Enable Fast PWM via Wave Generation Mode bits
  TCCR0A |= (1 << WGM01) | (1 << WGM00); // 1

  // Timer/Clock Control Register
  // Enable PWM on both OC0A and OC0B pins
  // Set COM0B0 for Inverting Mode
  TCCR0A |= (1 << COM0B1) | (0 << COM0B0);
  TCCR0A |= (1 << COM0A1);

  out_duty(127);
}

void out_off()
{
  TCCR0A &= ~(1 << COM0A1);
}

void out_on()
{
  TCCR0A |=(1 << COM0A1);
}