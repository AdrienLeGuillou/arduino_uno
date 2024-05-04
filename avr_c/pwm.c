#include <avr/io.h>

int main(void)
{
   DDRB |= (1 << DDB1);
   // PB1 as output
   OCR1A = 0x01FF;
   // set PWM for 50% duty cycle at 10bit
   TCCR1A |= (1 << COM1A1);
   // set non-inverting mode
   TCCR1A |= (1 << WGM11) | (1 << WGM10);
   // set 10bit phase corrected PWM Mode
   TCCR1B |= (1 << CS11);
   // set prescaler to 8 and starts PWM
   while (1)
   {
   }
}
