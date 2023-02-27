
#ifndef UART_H 
#define UART_H 
#include <avr/io.h> 
#include <avr/interrupt.h> 
#include <stdio.h> 

int put_uart_char(int c, FILE *fd);


void uart_init(void); 


#endif
