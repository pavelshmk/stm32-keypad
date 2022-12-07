#include "services.h"
#include "applications.h"

osEventFlagsId_t services_started;
osEventFlagsAttr_t services_started_attr = {
        .name = "services_started",
};

void start_service(const Application *service) {
    osThreadAttr_t attr = {
            .name = service->name,
            .priority = osPriorityAboveNormal,
            .stack_size = service->stack,
    };
    osThreadNew(service->entrypoint, NULL, &attr);
}

void start_services(void) {
    services_started = osEventFlagsNew(&services_started_attr);

    for (size_t i=0; i < SERVICES_COUNT; i++) {
        start_service(&SERVICES[i]);
    }
}

void mark_service_started(uint32_t flag) {
    osEventFlagsSet(services_started, flag);
}

void wait_for_service_to_start(uint32_t flag) {

    osEventFlagsWait(services_started, flag, osFlagsWaitAll | osFlagsNoClear, osWaitForever);
}


