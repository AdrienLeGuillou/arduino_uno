#include <avr/io.h>

.section .data

.section .bss

.section .text
                .org 0x00
                ; set r16:r17 to 103 to set the baud rate to 9600
                ldi     r16, 103
                ldi     r17, 103 >> 8
                rcall USART_Init

LOOP:
                rcall USART_Receive
                rcall USART_Transmit

                ; ldi r16, 'H'
                ; rcall USART_Transmit
                ; ldi r16, 'E'
                ; rcall USART_Transmit
                ; ldi r16, 'L'
                ; rcall USART_Transmit
                ; ldi r16, 'L'
                ; rcall USART_Transmit
                ; ldi r16, 'O'
                ; rcall USART_Transmit
                ; ldi r16, '\n'
                ; rcall USART_Transmit
                ; rjmp WAIT_1S

                rjmp LOOP
USART_Init:
                ; Set baud rate - sts as not IO ports
                sts UBRR0H, r17
                sts UBRR0L, r16
                ; Enable receiver and transmitter
                ldi r16, (1<<RXEN0)|(1<<TXEN0)
                sts UCSR0B,r16
                ; Set frame format: 8data, 2stop bit
                ldi r16, (1<<USBS0)|(3<<UCSZ00)
                sts UCSR0C,r16
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

;; wait sort of 1sec
WAIT_1S:
                ldi     r17, 64 ; 64 for sec
W_set18:        ldi     r18, 250
W_set19:        ldi     r19, 250
W_dec19:        dec     r19
                nop
                brne    W_dec19

                dec     r18
                brne    W_set19

                dec     r17
                brne    W_set18

                ret
