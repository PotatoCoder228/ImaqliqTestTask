//
// Created by potato_coder on 21.04.23.
//

#ifndef IMAQLIQTESTTASK_CONT_COMMON_H
#define IMAQLIQTESTTASK_CONT_COMMON_H

#include "stdint.h"

static const int8_t BLACK = 0;
static const int8_t RED = 1;

typedef void *object_s;

enum vector_consts {
    VECTOR_INIT_CAPACITY = 10
};

typedef void *(*callback)(void *data);

#endif //IMAQLIQTESTTASK_CONT_COMMON_H
