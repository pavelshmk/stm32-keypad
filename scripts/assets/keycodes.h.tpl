#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "keycodes_hash.h"

typedef enum {
% for name, keycode in keycodes:
    ${name} = ${keycode},
% endfor
} Keycodes;

#ifdef __cplusplus
}
#endif
