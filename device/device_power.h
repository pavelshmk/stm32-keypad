//
// Created by bakatrouble on 15/10/22.
//

#ifndef HAL_DEVICE_BATTERY_H
#define HAL_DEVICE_BATTERY_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CHARGE_PRECHARGE,
    CHARGE_CHARGE,
    CHARGE_DONE,
    CHARGE_SUSPEND,
} ChargeStatus;

ChargeStatus power_status(void);
bool power_pg(void);

#ifdef __cplusplus
}
#endif

#endif //HAL_DEVICE_BATTERY_H
