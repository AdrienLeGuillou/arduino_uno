#include <avr/io.h>

.section .data

.section .bss

.section .text
                .org 0x00
                ; set the input / output status of pins b5 and d7
                sbi         _SFR_IO_ADDR (DDRB), 5
                cbi         _SFR_IO_ADDR (DDRD), 7

                ; r16 is the last status of the button, 1 = pressed
resetbtn:       ldi         r16, 0

                ; while button pressed, jump back and forth to setbtn
loop:           sbic        _SFR_IO_ADDR (PIND), 7
                rjmp        setbtn
                cpi         r16, 1; will be TRUE only the first cycle after btn release
                brne        resetbtn; if it's FALSE: btn not pressed and was not prev cycle
                sbi         _SFR_IO_ADDR (PINB), 5 ; case when it was pressed last cycle: toggle PORTB5 with the set PINB5 trick
                rjmp        resetbtn; then resetbtn

                ; set r16 to 1 as btn is pressed and go back to loop
setbtn:         ldi         r16, 1
                rjmp        loop
