#include "main.h"

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	systemClockConfig();
	UartConfig();
	TIM6Config();
	GPIO_Config();
	//uint8_t myChar = 'C';
	uint8_t myArr[10] = "Hello\n\0";
	while (1)
	{
		GPIOB->BSRR |= (1<<0);		// Set
		delay_ms(500);
		GPIOB->BSRR |= (1<<16);		// Reset
		delay_ms(500);
		//UART3_SendChar(myChar);
		UART3_SendData(myArr);
		uint8_t rxData = UART3_GetChar();

	}
}

void UartConfig (void) {
	/******* STEPS FOLLOWED ********
	1. Enable the UART CLOCK and GPIO CLOCK
	2. Configure the UART PINs for Alternate Functions
	3. Program the M bit in USART_CR1 to define the word length.
	4. Select the desired baud rate using the USART_BRR register.
	5. Program the number of stop bits in USART_CR2.
	6. Enable the USART by writing the UE bit in USART_CR1 register to 1.
	7. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
	********************************/
	// 1. Enable the UART CLOCK and GPIO CLOCK
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;	// Enable USART3's clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;	// Enable GPIOD's clock (D port used by USART3's pins PD8,9)

	// 2. Configure the UART PINs for Alternate Functions
	GPIOD->MODER |= GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1; //PD8 and PD9 pins set as Alternate Function
	GPIOD->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR8 | GPIO_OSPEEDR_OSPEEDR9; //Pins setup as high speed.
	GPIOD->AFR[1] |= (7<<0) | (7<<4); // AF7 set for pin 8 and 9. Those pins' AFR is in the AFRH register therefore AFR[1].

	// 3. Program the M bit in USART_CR1 to define the word length.
	//USART3->CR1 &= ~(USART_CR1_M0 | USART_CR1_M1);
	USART3->CR1 &= ~USART_CR1_M; // We set the M0 and M1 as 0 for 8 bit message format.

	// 4. Select the desired baud rate using the USART_BRR register.
	USART3->CR1 &= ~USART_CR1_OVER8;	// Set the oversampling by 16 to be sure.
	USART3->BRR |= 0x139;	// For 115200 baud rate the BRR calculation via the RM0385 s.31.5.4 formula. 0x139 = 313d

	// 5. Program the number of stop bits in USART_CR2.
	USART3->CR2 &= ~USART_CR2_STOP; // For 1 stop bit (13:12) set as 0:0

	// 6. Enable the USART by writing the UE bit in USART_CR1 register to 1.
	USART3->CR1 |= USART_CR1_UE;	// Enable USART

	// 7. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
	USART3->CR1 |= USART_CR1_TE | USART_CR1_RE;	// Enable Transmit and Receive

}

void UART3_SendChar (uint8_t c) {
	/*********** STEPS FOLLOWED *************
	1. Write the data to send in the USART_TDR register (this clears the TXE bit). Repeat this
		 for each data to be transmitted in case of single buffer.
	2. After writing the last data into the USART_TDR register, wait until TC=1. This indicates
		 that the transmission of the last frame is complete. This is required for instance when
		 the USART is disabled or enters the Halt mode to avoid corrupting the last transmission.
	****************************************/
	if (USART3->ISR & USART_ISR_TXE) // First check if the Transmit Data Register is empty
	{
		USART3->TDR = c;	// Load the char to be transmitted into TDR
		while(!(USART3->ISR & USART_ISR_TC));	// Wait for Transmit Complete flag to be set in the ISR
	}
}

void UART3_SendData (uint8_t * data) {	// The input of the function is the address of the char array
	while (*data != '\0') {				// We will be looping until we find NULL char
		UART3_SendChar(*data);			// We send the value pointed by the current address
		(data)++;						// We increment the address by one for the next 8 bit
	}
}

uint8_t UART3_GetChar (void) {
	/*********** STEPS FOLLOWED *************
	1. Wait for the RXNE bit to set. It indicates that the data has been received and can be read.
	2. Read the data from USART_DR  Register. This also clears the RXNE bit
	****************************************/

	uint8_t data;
	while (!(USART3->ISR & USART_ISR_RXNE)); // Wait for the RX Not Empty Flag to set. Which indicates that data can be read.
	data = USART3->RDR;
	return data;
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

