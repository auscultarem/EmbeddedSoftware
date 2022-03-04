#include <stdint.h>
#include "mcal_reg.h"

//LED = PA5 Port A pin 5
//GPIOA = AHB1
//GPIOA = 0x4002 0000
//MODER REG OFFSET = 0x00
//ODR = 0x14 ADDRESS OFFSET
//AHBIENER = AHB1 + RCC + 0x30  -> 0x4002 0000 + 3800 + 30

#define RCC_AHB1ENR (*((volatile unsigned int *)	0x40023830))
#define GPIOA_MODER (*((volatile unsigned int *)	0x40020000))
#define GPIOA_ODR 	(*((volatile unsigned int *)	0x40020014))	

class Led
{
	public:
		typedef uint32_t port_type;
		typedef uint32_t bval_type;
	
	Led(const port_type p, bval_type b):port(p), bval(b)
	{
		/*Disable pin*/
		//*((volatile uint32_t *)GPIOB) = bval // C language
		*reinterpret_cast<volatile port_type *>(port) // port instead of -> GPIOB
			&= ~(1U<<bval); // switch position 1 to 1
		
		/*Set the pin mode to output*/
		const port_type gpio_mode_reg = port - 0x14;
			*reinterpret_cast<volatile port_type *>(gpio_mode_reg) |= ( 1U<<(bval * 2));		
	}
	
	void toggle()const
	{
		*reinterpret_cast<volatile port_type *>(port) ^=(1U<<bval);
	}
	
	void pseudo_delayMs()
	{
		for(int i=0; i<190000; i++)
		{
		}
	}
	
			
	private:
		const port_type port;
		const port_type bval;	
};



int main(){
	
	RCC_AHB1ENR |= (1U<<0); /*Enable clock to GPIOA*/
	Led led5(mcal::reg::gpioa, mcal::reg::gpio_pin5);
	
	while(1){
	led5.toggle();
	led5.pseudo_delayMs();
	}
}