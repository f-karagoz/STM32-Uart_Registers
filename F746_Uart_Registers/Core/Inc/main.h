
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f746xx.h"
#include "RccConfig.h"
#include "Delay.h"
#include "UartConfig.h"


/**
 * @brief Configures the GPIO.
 *
 */
void GPIO_Config (void);

/**
 * @brief Configures the interrupt.
 *
 */
void Interrupt_Config (void);

/**
 * @brief Interrupt handler for EXTI 15:10
 *
 */
void EXTI15_10_IRQHandler(void);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

