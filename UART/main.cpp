#include "uart.h"
//#include <iostream>

int main(){

	uart_init();
	
	while(1){
		//uart_write('Y');
		
		//std::cout<<"Hello from embedded C++\r\n";
		printf("Hello from embedded C++\r\n");
		for(int i=0; i < 180000; i++){}
	}
}
