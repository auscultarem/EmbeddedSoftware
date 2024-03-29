#include "uart.h"

void uart_init(void){
	
	RCC->AHB1ENR |= 0x1; /*Enable GPIOA clock*/ //when we use | or operator we modified only the that bit
	RCC->APB1ENR |= 0x20000; /*Enable USART2 clock*/
	
	/*configure Pa2, Pa3 for USART2  TX, RX*/
	GPIOA->AFR[0] |= 0X7700; //to confiure PA2 and PA3  7=0111
	GPIOA->MODER |= 0x00A0; /*Enable alternate function for PA2, PA3*/
	
	USART2->BRR = 0x0683; /* 9600 baud @  16Mhz*/
	USART2->CR1 = 0x000C; /*Enable Tx, RX, 8-bit data*/
	USART2->CR2 = 0x000;  /*1 stop bit*/
	USART2->CR3 = 0x000; /*No flow control*/
	USART2->CR1 |= 0x2000; /*Enable USART2*/	
}

int uart_write(int ch){
	while(!(USART2->SR & 0x0080)){} // wait until TX empty
		USART2->DR=(ch & 0xFF);
		return 1;
}
int uart_read(void){
	
	while(!(USART2->SR & 0x0020)){}
		return USART2->DR;
}

namespace std{
struct __FILE
{ int handle;};	

FILE __stdout;
FILE __stdin;
FILE __stderr;

int fgetc(FILE *f){
	int c;
	c = uart_read();
	if( c == '\r'){
		uart_write(c);
		c = '\n';
	}
	uart_write(c);
	return c;
}
	
	int fputc(int c, FILE *stream){
		return uart_write(c);
	}
	
	int ferror(FILE *stream){
		return 1;
	}
		
	long int ftell(FILE *stream){
		return 1;
	}
	
	int fclose(FILE *f){
		return 1;
	}
	int fseek(FILE *f, long nPos, int nMode){
		return 0;
	}
	
	int fflush(FILE *f){
		return 1;
	}
		
}

