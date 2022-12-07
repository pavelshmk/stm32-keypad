//
// Created by bakatrouble on 08/11/22.
//

#ifndef HAL_LOADER_H
#define HAL_LOADER_H

#include <m-dict.h>
#include <applications.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Loader Loader;

DICT_DEF2(ApplicationDict, const char*, M_CSTR_OPLIST, Application*, M_PTR_OPLIST)

struct Loader {
    ApplicationDict_t applications;
};

void loader_start(Loader *loader, const char *name, const char *args);

#ifdef __cplusplus
}
#endif

#endif //HAL_LOADER_H
