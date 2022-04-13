
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
 * @brief Configures the GPIO.
 *
 */
void GPIO_Config (void);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

