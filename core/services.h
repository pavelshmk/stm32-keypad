//
// Created by bakatrouble on 10/11/22.
//

#ifndef KEYPAD_CMSIS_FREERTOS_SERVICES_H
#define KEYPAD_CMSIS_FREERTOS_SERVICES_H

#include "cmsis_os2.h"
#include "applications_exports.h"

extern osEventFlagsId_t services_started;

void start_services(void);
void mark_service_started(uint32_t flag);
void wait_for_service_to_start(uint32_t flag);

#endif //KEYPAD_CMSIS_FREERTOS_SERVICES_H
