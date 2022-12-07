/******************************************************************************
 * @file    stm32f4_discovery.h
 * @author  Rajmund Szymanski
 * @date    03.10.2018
 * @brief   This file contains definitions for STM32F4-Discovery Kit.
 ******************************************************************************/

#ifndef __STM32F4_DISCOVERY_H
#define __STM32F4_DISCOVERY_H

#include "device_leds.h"
#include "device_rand.h"
#include "device_udid.h"
#include "device_uart.h"
#include "device_display.h"
#include "device_spi.h"
#include "device_buzzer.h"
#include "device_power.h"
#include "device_usb.h"
#include "device_gpio.h"
#include "device_flash.h"

void device_init(void);

#endif//__STM32F4_DISCOVERY_H
