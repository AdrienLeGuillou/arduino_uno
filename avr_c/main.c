// Toggle switch led
#include <avr/io.h>

int main(void)
{
    // char used as int require >= 16 bits (2reg)
    char prevState = 0; // pressed or not

    DDRB |= (1 << DDB5); // PB5 as output (digital 13 / builtin)
    DDRD &= ~(1 << DDD6);// PD6 as input (digital 6)

    while(1)
    {
        char switchState = (PIND & (1 << PIND6)) >> PIND6; // read state PD6
                                                          //
        if (switchState == 0 && prevState == 1) {
            // writting to PINB5 in input mode toggles it (it's trick)
            PINB |= (1 << PINB5);
        }

        prevState = switchState;
    }
}
