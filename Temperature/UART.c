#include <avr/io.h> 
#include <avr/interrupt.h> 
#include <stdio.h> 
#include "Uart.h" 

int put_uart_char(int c, FILE *fd) 
{
  while (!(UCSRA & _BV(UDRE)));  
  UDR = c;                      
  return 0; 
}

void uart_init(void)                               
{
  
  UCSRB  |=  _BV(TXEN)  |  _BV(RXEN)  |  _BV(RXCIE);  
    UCSRC |= _BV(UCSZ1) | _BV(UCSZ0);                  
  UBRRH = 0; 
  UBRRL = 103;                                        


  
  
  
  fdevopen(&put_uart_char, NULL); 
  

  SREG |= _BV(SREG_I); 
}
  
  
  
  
  
