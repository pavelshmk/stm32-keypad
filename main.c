#include <stdio.h>
#include "cmsis_os2.h"
#include "stm32f4xx_hal.h"
#include "record.h"
#include "device.h"
#include "services.h"
#include "FreeRTOS.h"
#include "ff.h"

void HAL_MspInit(void) {
    record_init();
    device_init();
}

void* malloc(size_t size)
{
    void* ptr = NULL;

    if(size > 0)
    {
        // We simply wrap the FreeRTOS call into a standard form
        ptr = pvPortMalloc(size);
    } // else NULL if there was an error

    return ptr;
}

void free(void* ptr)
{
    if(ptr)
    {
        // We simply wrap the FreeRTOS call into a standard form
        vPortFree(ptr);
    }
}

int main() {
    HAL_Init();

//    uint32_t q;
//    flash_read_buffer((uint8_t *) &q, 0, 4);
//    printf("read 0x%08X\r\n", q);
//    q = 0xdeadbeef;
//    flash_block_erase_64k(0);
//    flash_write_buffer((uint8_t *) &q, 0, 4);
//    flash_read_buffer((uint8_t *) &q, 0, 4);
//    printf("readback 0x%08X\r\n", q);

    FATFS fs;
    FRESULT res;

    if ((res = f_mount(&fs, "", 1) != FR_OK)) {
        printf("initial mount failed, formatting\r\n");
        uint8_t buf[FF_MAX_SS];
        MKFS_PARM parm = {
                .fmt = FM_ANY
        };
        if ((res = f_mkfs("", &parm, buf, FF_MAX_SS)) == FR_OK) {
            if ((res = f_mount(&fs, "", 1)) != FR_OK) {
                printf("mount after mkfs fail\r\n");
            } else {
                printf("done\r\n");
            }
        } else {
            printf("mkfs fail\r\n");
        }
    }
    f_unmount("");

    osKernelInitialize();
    start_services();
    osKernelStart();

    return 0;
}