//
// Created by bakatrouble on 08/11/22.
//

#ifndef HAL_APPLICATIONS_H
#define HAL_APPLICATIONS_H

#include <stm32f4xx.h>
#include "applications_exports.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*ApplicationCallback)(void *p);
typedef struct Application Application;

struct Application {
    const char *id;
    const char *name;
    ApplicationCallback entrypoint;
    uint32_t stack;
};

extern const Application SERVICES[];
extern const size_t SERVICES_COUNT;

extern const Application APPS[];
extern const size_t APPS_COUNT;

#ifdef __cplusplus
}
#endif

#endif //HAL_APPLICATIONS_H
