/*
 * PLL.h
 *
 *  Created on: 26 abr. 2021
 *      Author: ASUS STRIX
 */

#ifndef PLL_PLL_H_
#define PLL_PLL_H_

extern void Configurar_PLL(void);
extern void SysTick_Init(void);
extern void SysTick_Wait(uint32_t delay);
extern void SysTick_Wait10ms(uint32_t delay);


#endif /* PLL_PLL_H_ */
