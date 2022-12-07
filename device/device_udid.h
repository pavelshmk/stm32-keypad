/******************************************************************************
 * @file    stm32f4_discovery_udid.h
 * @author  Rajmund Szymanski
 * @date    18.05.2021
 * @brief   This file contains definitions for STM32F4-Discovery Kit.
 ******************************************************************************/

#ifndef __STM32F4_DISCOVERY_UDID_H
#define __STM32F4_DISCOVERY_UDID_H

#include "stm32f4xx.h"

#ifdef  __cplusplus
extern "C" {
#endif//__cplusplus

/* UDID --------------------------------------------------------------------- */

#ifndef UDID

#define UDID_BASE  UID_BASE

typedef struct {
	__I uint32_t ID[3];
} UDID_TypeDef;

#define UDID  ((UDID_TypeDef*)UDID_BASE)

#endif // UDID

/* -------------------------------------------------------------------------- */

// get udid crc

static inline
uint32_t udid_get(void )
{
    __HAL_RCC_CRC_CLK_ENABLE();

	CRC->CR = CRC_CR_RESET; __DSB();
	CRC->DR = UDID->ID[0];
	CRC->DR = UDID->ID[1];
	CRC->DR = UDID->ID[2];

	return ~CRC->DR;
}

/* -------------------------------------------------------------------------- */

#ifdef  __cplusplus
}
#endif//__cplusplus

#endif//__STM32F4_DISCOVERY_UDID_H
