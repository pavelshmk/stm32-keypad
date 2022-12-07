//
// Created by bakatrouble on 09/11/22.
//

#include "power.h"
#include "record.h"
#include "services.h"
#include "FreeRTOS.h"
#include <cmsis_os2.h>

const char *POWER_SVC = "power_svc";

void power_svc(void *p) {
    Power *power = pvPortMalloc(sizeof(Power));

    record_create(POWER_SVC, power);

    mark_service_started(SVC_POWER_RUNNING);

    while (true) {
        power->charge_status = power_status();
        power->power_good = power_pg();
//        switch (power->charge_status) {
//            case CHARGE_PRECHARGE:
//            case CHARGE_CHARGE:
//                leds_set(1, 1, 0);
//                break;
//            case CHARGE_DONE:
//                leds_set(0, 1, 0);
//                break;
//            case CHARGE_SUSPEND:
//                leds_set(1, 0, 0);
//                break;
//        }
        osDelay(100);
    }
}
