#include "FreeRTOS.h"
#include "task.h"
#include "kp_assert.h"

void configureTimerForRunTimeStats(void) {

}

unsigned long getRunTimeCounterValue(void) {
    return 0;
}

void vApplicationStackOverflowHook (TaskHandle_t xTask, char *pcTaskName) {
    UNUSED(xTask);
    ASSERT(0, "Stack Overflow in %s", pcTaskName);
}
