
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f746xx.h"

/**
 * @brief Configures TIM6.
 *
 */
void TIM6Config (void);

/**
 * @brief Delay for uS.
 *
 * @param us Microsecond
 */
void delay_us (uint16_t us);

/**
 * @brief Delay for mS.
 *
 * @param ms Millisecond
 */
void delay_ms (uint16_t ms);

/**
 * @brief Configures the GPIO.
 *
 */
void GPIO_Config (void);






#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

