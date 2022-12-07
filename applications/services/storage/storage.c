#include <sys/cdefs.h>
//
// Created by bakatrouble on 12/11/22.
//

#include "storage.h"
#include "record.h"
#include "services.h"
#include <malloc.h>

const char *STORAGE_SVC = "storage_svc";

enum {
    STORAGE_MOUNT,
    STORAGE_UNMOUNT,
    STORAGE_FORMAT,
};

osMessageQueueAttr_t storage_queue_attr = {
        .name = "storage_queue",
};

FRESULT storage_format_impl(void) {
    uint8_t *work_buf = malloc(FF_MAX_SS);
    MKFS_PARM parm = {
            .fmt = FM_ANY
    };
    FRESULT res = f_mkfs("", &parm, work_buf, FF_MAX_SS);
    free(work_buf);
    return res;
}

FRESULT storage_mount_impl(void) {
    Storage *storage = record_get(STORAGE_SVC);
    FRESULT res = f_mount(&storage->fs, "", 1);
    storage->mounted = res == FR_OK;
    return res;
}

void storage_unmount_impl(void) {
    Storage *storage = record_get(STORAGE_SVC);
    if (storage->mounted)
        f_unmount("");
}

_Noreturn void storage_svc(void *p) {
    UNUSED(p);

    Storage *storage = malloc(sizeof(Storage));
    storage->queue = osMessageQueueNew(8, sizeof(STORAGE_MOUNT), &storage_queue_attr);

    record_create(STORAGE_SVC, storage);

    storage_mount_impl();

    mark_service_started(SVC_STORAGE_RUNNING);

    uint32_t msg;
    while (true) {
        if (osMessageQueueGet(storage->queue, &msg, 0, osWaitForever) == osOK) {
            switch (msg) {
                case STORAGE_MOUNT:
                    storage_mount_impl();
                    break;
                case STORAGE_UNMOUNT:
                    storage_unmount_impl();
                    break;
                case STORAGE_FORMAT:
                    storage_format_impl();
                    break;
            }
        }
    }
}
