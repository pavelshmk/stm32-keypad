//
// Created by bakatrouble on 09/11/22.
//

#ifndef HAL_POWER_H
#define HAL_POWER_H

#include <device.h>

typedef struct Power Power;

struct Power {
    ChargeStatus charge_status;
    bool power_good;
};

#endif //HAL_POWER_H
