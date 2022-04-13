#include "main.h"

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	systemClockConfig();
	TIM6Config();
	GPIO_Config();
	while (1)
	{
		GPIOB->BSRR |= (1<<0);		// Set
		delay_ms(1000);
		//delay_us(10000);
		GPIOB->BSRR |= (1<<16);		// Reset
		delay_ms(1000);
		//delay_us(10000);
	}
}


void GPIO_Config (void) {
	/************ STEPS FOLLOWED ***********
	1. Enable the GPIO CLOCK
	2. Set the Pin as OUTPUT
	3. Configure the OUTPUT MODE
	Note: LED connected to B0
	***************************************/
	// 1. Enable the GPIO CLOCK
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;	// Enable GPIO B Clock

	// 2. Set the Pin as OUTPUT
	GPIOB->MODER |= (1<<0);	// Set B0 as General purpose output mode. Bits 1:0 set as (01)

	// 3. Configure the OUTPUT MODE
	GPIOB->OTYPER |= (0<<0);	// Push-pull type for pin 0.
	GPIOB->OSPEEDR |= (2<<0);	// High speed setup for pin 0
	GPIOB->PUPDR &= ~((1<<1) | (1<<0)); // 1:0 set as (00) for pin 0 to be no pull up or down
}

