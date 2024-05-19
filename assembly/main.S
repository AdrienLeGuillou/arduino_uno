#include <avr/io.h>

.section .text
.org 0x00
                jmp         MAIN

; take table address and multiply by 2; WARNING hexadecimal
.org (0x24<<1); USART receive complete, see table and <<1
                jmp         USART_lb_int

MAIN:
                ; ; enable global interrupts
                ; set r16:r17 to 103 to set the baud rate to 9600
                ldi         r16, 103
                ldi         r17, 103 >> 8
                rcall       USART_Init
                sei

                ; set internal led as output
                sbi         _SFR_IO_ADDR (DDRB), 5 ; sbi x04, 5
                rjmp        BLINKLED

BLINKLED:
                ; sbi         _SFR_IO_ADDR (PINB), 5 ; toggle PORTB5 with the set PINB5 trick
                rcall       WAIT_1S
                rjmp        BLINKLED

LOOPHELLO:
                ldi r16, 'H'
                rcall USART_Transmit
                ldi r16, 'E'
                rcall USART_Transmit
                ldi r16, 'L'
                rcall USART_Transmit
                ldi r16, 'L'
                rcall USART_Transmit
                ldi r16, 'O'
                rcall USART_Transmit
                ldi r16, '\n'
                rcall USART_Transmit
                rjmp WAIT_1S
                rjmp LOOPHELLO

LOOPBACK:
                rcall USART_Receive
                rcall USART_Transmit
                rjmp LOOPBACK

USART_Init:
                ; Set baud rate - sts as not IO ports
                sts         UBRR0H, r17
                sts         UBRR0L, r16
                ; Enable receiver, transmitter & reveice complete interrupt
                ldi         r16, (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)
                sts         UCSR0B,r16
                ; Set frame format: 2stop bit, 8 data  bit
                ldi         r16, (1<<USBS0)|(3<<UCSZ00)
                sts         UCSR0C,r16
                rcall       USART_Flush
                ret

USART_Transmit:
                ; Wait for empty transmit buffer
                lds     r15, UCSR0A ; load value to a register
                sbrs    r15, UDRE0  ; check bit set in register (not IO)
                rjmp    USART_Transmit
                ; Put data (r16) into buffer, sends the data
                sts     UDR0,r16 ; sts as not an IO register
                ret

USART_Receive:
                ; Wait for data to be received
                lds     r15, UCSR0A ; load value to a register
                sbrs    r15, RXC0  ; check bit set in register (not IO)
                rjmp    USART_Receive
                ; Get and return received data from buffer
                lds     r16, UDR0
                ret

USART_lb_int:
                sbi         _SFR_IO_ADDR (PINB), 5 ; toggle PORTB5 with the set PINB5 trick
                lds         r16, UDR0
                sts         UDR0, r16 ; sts as not an IO register
                reti

USART_Flush:
                lds     r15, UCSR0A
                sbrs    r15, RXC0
                ret
                lds     r16, UDR0
                rjmp    USART_Flush

;; wait sort of 1sec
WAIT_1S:
                ldi     r16, 64
W_set17:        ldi     r17, 250
W_set18:        ldi     r18, 250
W_dec18:        dec     r18
                nop
                brne    W_dec18

                dec     r17
                brne    W_set18

                dec     r16
                brne    W_set17

                ret


.section .data

.section .bss

