//
// Created by potato_coder on 21.04.23.
//

#ifndef IMAQLIQTESTTASK_SERVER_APP_H
#define IMAQLIQTESTTASK_SERVER_APP_H

#include <stdint.h>
#include "stdbool.h"
#include "../common/exception_s.h"

enum server_app_exceptions {
    ARGS_IS_UNDEFINED = 0,
    FORK_DENIED_EXCEPTION
};


void server_start(int64_t port);

bool receive_file(int socket);

#endif //IMAQLIQTESTTASK_SERVER_APP_H
