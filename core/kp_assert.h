//
// Created by bakatrouble on 08/11/22.
//

#ifndef HAL_ASSERT_H
#define HAL_ASSERT_H

#include <stdio.h>

extern char assert_buf[256];
void assert_failure(const char *expr, const char *msg, const char *file, int line);

#define ASSERT(expr, ...)                                      \
do {                                                           \
    if (!(expr)) {                                             \
        sprintf(assert_buf, __VA_ARGS__);                      \
        assert_failure(#expr, assert_buf, __FILE__, __LINE__); \
    }                                                          \
} while (0)

#endif //HAL_ASSERT_H
