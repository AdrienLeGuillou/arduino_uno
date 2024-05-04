#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000

ISR (TIMER1_OVF_vect) {
    PORTB ^= (1 << PORTB5);
    TCNT1 = 65535 - (F_CPU / 1024);
}

int main(void)
{
    DDRB |= (1 << DDB5);
    // max val == 65535
    TCNT1 = 65535 - (F_CPU / 1024);
    // sets the prescaler to 1024
    // 16MHz / 1024 = 15625
    TCCR1B = (1 << CS10) | (1 << CS12);
    TCCR1A = 0x00;
    TIMSK1 = (1 << TOIE1);

    sei();

    while(1)
    {
        ;;
    }
}
