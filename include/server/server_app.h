//
// Created by potato_coder on 21.04.23.
//

#ifndef IMAQLIQTESTTASK_SERVER_APP_H
#define IMAQLIQTESTTASK_SERVER_APP_H

#include <stdint.h>
#include "../common/exception_s.h"

enum server_app_exceptions {
    PORT_IS_OCCUPIED = 0,
    ARGS_IS_UNDEFINED,
    FORK_DENIED_EXCEPTION,
    INVALID_PORT
};


int server_start(int64_t port);

#endif //IMAQLIQTESTTASK_SERVER_APP_H
