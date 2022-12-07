#include "device_power.h"
#include "stm32f4xx.h"
#include "device_gpio.h"

void power_init(void) {
    gpio_pin_init(GPIOB, GPIO_PIN_8 | GPIO_PIN_9, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, 0);
    gpio_pin_init(GPIOC, GPIO_PIN_12, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, 0);
}

ChargeStatus power_status(void) {
    bool stat1 = !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8);
    bool stat2 = !HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12);

    if (stat1 && stat2) {
        return CHARGE_PRECHARGE;
    } else if (stat1 && !stat2) {
        return CHARGE_CHARGE;
    } else if (!stat1 && stat2) {
        return CHARGE_DONE;
    } else {
        return CHARGE_SUSPEND;
    }
}

bool power_pg(void) {
    return !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9);
}
