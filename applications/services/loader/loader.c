//
// Created by bakatrouble on 08/11/22.
//

#include "loader.h"
#include "record.h"
#include "services.h"
#include "FreeRTOS.h"
#include <cmsis_os2.h>

const char *LOADER_SVC = "loader_svc";

void loader_start(Loader *loader, const char *name, const char *args) {
    Application *app = *ApplicationDict_get(loader->applications, name);
    if (app != NULL) {
        osThreadAttr_t attr = {
                .name = app->name,
                .stack_size = app->stack / 4,
                .priority = osPriorityNormal,
        };
        osThreadNew(app->entrypoint, args, &attr);
//        tsk_t *tsk = wrk_create(0, app->entrypoint, app->stack, true, false);
//        tsk->arg = args;
//        tsk_start(tsk);
    }
}

int loader_svc(void *p) {
    Loader *loader = pvPortMalloc(sizeof(Loader));
    ApplicationDict_init(loader->applications);
    for (size_t i=0; i < APPS_COUNT; i++) {
        ApplicationDict_set_at(loader->applications, APPS[i].id, &APPS[i]);
    }
    record_create(LOADER_SVC, loader);

    mark_service_started(SVC_LOADER_RUNNING);

    osThreadExit();
//    return 0;
}
