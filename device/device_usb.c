//
// Created by bakatrouble on 16/10/22.
//

#include "device/usbd.h"
#include "stm32f4xx.h"
#include "device_gpio.h"
#include <cmsis_os2.h>

//PCD_HandleTypeDef hpcd_USB_OTG_FS;

void usb_init(void) {
    gpio_pin_init(GPIOA, GPIO_PIN_11 | GPIO_PIN_12, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF10_OTG_FS);

    __HAL_RCC_USB_OTG_FS_CLK_ENABLE();
    HAL_NVIC_SetPriority(OTG_FS_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(OTG_FS_IRQn);

//    USB_OTG_FS->GCCFG |= USB_OTG_GCCFG_VBDEN;

//    hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
//    hpcd_USB_OTG_FS.Init.dev_endpoints = 6;
//    hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
//    hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
//    hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
//    hpcd_USB_OTG_FS.Init.Sof_enable = DISABLE;
//    hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
//    hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
//    hpcd_USB_OTG_FS.Init.battery_charging_enable = DISABLE;
//    hpcd_USB_OTG_FS.Init.vbus_sensing_enable = DISABLE;
//    hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
//    if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK) {
////        Error_Handler();
//    }
}

void OTG_FS_IRQHandler(void) {
    tud_int_handler(0);
}
