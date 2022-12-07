//
// Created by bakatrouble on 12/11/22.
//

#include "msd.h"
#include "ff.h"
#include <cmsis_os2.h>
#include <stdio.h>

uint8_t msd_buf[FF_MAX_SS];
void msd_app(void *p) {
    FRESULT res;
    FATFS fs;

    MKFS_PARM parm = {
            .fmt = FM_ANY
    };
    if ((res = f_mkfs("", &parm, msd_buf, FF_MAX_SS)) == FR_OK) {
        if ((res = f_mount(&fs, "", 1) != FR_OK)) {
            printf("mount after mkfs fail\r\n");
        } else {
            printf("formatted\r\n");
        }
    } else {
        printf("mkfs fail\r\n");
    }
    f_unmount("");

    osThreadExit();
}
