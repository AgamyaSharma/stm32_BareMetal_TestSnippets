

#include <stdint.h>
#include "stm32f302r8.h"

void delay_sec(){
	SYSTICK->CTRL |=(1<<2);// Enabling the bus at AHB frequency 8MHz standard (upto 72 MHz)
	SYSTICK->CTRL &= ~(1);// Clearing the enable bit
	SYSTICK->LOAD |= 7999999;// Timer load set according to LOAD = ((CLOCK FREQUENCY*TIME)-1)
	SYSTICK ->VAL = 0;
	SYSTICK->CTRL |= (1); // Enabling the systick
	while(!(SYSTICK->CTRL & (1<<16))); // polling for the count flag
	SYSTICK->CTRL &= ~(1);
}
int main(void)
{
	RCC->AHBENR |= (1<<18); // Enabling the Clock of GPIOB hanging off AHB bus
	GPIOB->MODER &= ~(3<<26); // Clearing the bits(26-27) of the mode register
	GPIOB->MODER |=(1<<26); //Setting 01 for PB13 connected to the internal Led
	GPIOB->ODR &= ~(1<<13); // Clearing the bit(13) of output data register
	while(1){

    GPIOB->ODR ^= (1<<13); // Toggling the bits
   delay_sec();
	}
	for(;;);
}

