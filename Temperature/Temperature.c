#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>


#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)
//Declaration of our functions
void USART_init(void);
unsigned int USART_receive(void);
void USART_send(unsigned char data);
void USART_putstring(char* StringPtr);
void ADC_init();
int ADC_Read(int channel);
char String[]="Welcome to HCI Lab\n\n";
static volatile unsigned char temp = 0;
static volatile int i = 0;

#define SOUND_VELOCITY 340UL 
    
int main(void){
  USART_init();
  ADC_init();
   
   unsigned char voltage;                     // Call the USART initialization code
       //거리 변수
  //ultrasonic_init(); 
  DDRA = 0xFF;
   
  while(1){
      
	 


   
    voltage = (ADC_Read(0)*(5/1024));

	temp = (voltage+5)/0.01;
	//unsigned int distance = ultra_triger();	                      // Infinite loop
    USART_send(temp); // Pass the string to the USART_putstring function and sends it over the serial
    _delay_ms(1000);         // Delay for 5 seconds so it will re-send the string every 5 seconds
  }


  
  return 0;
}
/* Initialize USART */
void USART_init(void){
  UBRRH = (uint8_t)(BAUD_PRESCALLER>>8);
  UBRRL = (uint8_t)(BAUD_PRESCALLER);
  UCSRB = (1<<RXEN)|(1<<TXEN);
  UCSRC = (1<<UCSZ0)|(1<<UCSZ1)|(1<<URSEL);
}
/* Function to receive byte/char */
unsigned int USART_receive(void){
  while(!(UCSRA & (1<<RXC)));
  return UDR;
}
/* Function to send byte/char */
void USART_send( unsigned char data){
  while(!(UCSRA & (1<<UDRE)));
  UDR = data;
}
/* Send string */
void USART_putstring(char* StringPtr){
  while(*StringPtr != 0x00){
    USART_send(*StringPtr);
  StringPtr++;}
  
}


void ADC_init(){                              
   DDRA = 0x00;           
   ADCSRA = 0x87;          
   ADMUX = 0x40;           
}

int ADC_Read(int channel)                     
{
   ADMUX = 0x40 | (channel & 0x07);   
   ADCSRA |= (1<<ADSC);               
   while (!(ADCSRA & (1<<ADIF)));     
   ADCSRA |= (1<<ADIF);               
   _delay_ms(1);                      
   return ADCW;                       
}
