
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f746xx.h"
#include "RccConfig.h"
#include "Delay.h"

/**
 * @brief Configures UART.
 *
 */
void UartConfig (void);

/**
 * @brief Sends one char through USART3;
 *
 * @param c Actual char.
 */
void UART3_SendChar (uint8_t c);

/**
 * @brief Sends char array.
 *
 * @param data Pointer to char array.
 */
void UART3_SendData (uint8_t * data);

/**
 * @brief Gets the char from UART.
 *
 * @return Read char data.
 */
uint8_t UART3_GetChar (void);

/**
 * @brief Configures the GPIO.
 *
 */
void GPIO_Config (void);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

