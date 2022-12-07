/******************************************************************************
 * @file    stm32f4_discovery_rand.h
 * @author  Rajmund Szymanski
 * @date    18.05.2021
 * @brief   This file contains definitions for STM32F4-Discovery Kit.
 ******************************************************************************/

#ifndef __STM32F4_DISCOVERY_RAND_H
#define __STM32F4_DISCOVERY_RAND_H

#include "stm32f4xx.h"

#ifdef  __cplusplus
extern "C" {
#endif//__cplusplus

/* -------------------------------------------------------------------------- */

// start random number generator

static inline
void rnd_init(void )
{
    __HAL_RCC_RNG_CLK_ENABLE();
	RNG->CR = RNG_CR_RNGEN;
}

/* -------------------------------------------------------------------------- */

// get next random number

static inline
unsigned rnd_get(void )
{
	while ((RNG->SR & RNG_SR_DRDY) == 0);

	return RNG->DR;
}

/* -------------------------------------------------------------------------- */

#ifdef  __cplusplus
}
#endif//__cplusplus

#endif//__STM32F4_DISCOVERY_RAND_H
