#include "main.h"
#include "RccConfig.h"


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
		GPIOB->BSRR |= (1<<16);		// Reset
		delay_ms(1000);
	}
}

void TIM6Config (void) {
	/************** STEPS TO FOLLOW *****************
	1. Enable Timer clock
	2. Set the prescalar and the ARR
	3. Enable the Timer, and wait for the update Flag to set
	************************************************/
	// 1. Enable Timer clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

	// 2. Set the prescalar and the ARR
	// 72Mhz default value as now of the TIM6 we need to set a prescaler for 1Mhz
	TIM6->PSC = 72-1; 	// +1 is added by default
	TIM6->ARR = 0xFFFF;	// Max auto-reload value, so we can count higher

	// 3. Enable the Timer, and wait for the update Flag to set
	TIM6->CR1 |= TIM_CR1_CEN;	// Enable the timer
	while(!(TIM6->SR & TIM_SR_UIF));	// Wait for update flag
}

void delay_us (uint16_t us) {
	/************** STEPS TO FOLLOW *****************
	1. RESET the Counter
	2. Wait for the Counter to reach the entered value. As each count will take 1 us,
		 the total waiting time will be the required us delay
	************************************************/
	// 1. RESET the Counter
	TIM6->CNT = 0x0000; // Reset the counter

	// 2. Wait for the Counter to reach the entered value.
	while(TIM6->CNT < us);
}

void delay_ms (uint16_t ms) {
	for(uint16_t i=0; i<ms;i++ ) {
		delay_us(1000);
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

