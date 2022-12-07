//
// Created by bakatrouble on 06/11/22.
//

#ifndef HAL_RECORD_H
#define HAL_RECORD_H

#ifdef __cplusplus
extern "C" {
#endif

void record_init(void);
void record_create(const char *name, void *data);
void *record_get(const char *name);

#ifdef __cplusplus
}
#endif

#endif //HAL_RECORD_H
