//
// Created by bakatrouble on 06/11/22.
//

#include "record.h"
#include <m-dict.h>
#include "kp_assert.h"

typedef struct {
    void *data;
} RecordData;

DICT_DEF2(RecordDataDict, const char *, M_CSTR_OPLIST, RecordData, M_POD_OPLIST)
RecordDataDict_t records;

void record_init(void) {
    RecordDataDict_init(records);
}

void record_create(const char *name, void *data) {
    RecordData rd = {
            .data = data
    };
    RecordDataDict_set_at(records, name, rd);
}

void *record_get(const char *name) {
    RecordData *rd = RecordDataDict_get(records, name);
    ASSERT(rd != NULL, "Record %s not found", name);
    return rd->data;
}
