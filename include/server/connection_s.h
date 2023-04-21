//
// Created by potato_coder on 21.04.23.
//

#ifndef IMAQLIQTESTTASK_CONNECTION_H
#define IMAQLIQTE STTASK_CONNECTION_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include "../common/exception_s.h"
#include "../../src/server/app/server_app.h"


enum conn_consts {
    CONNECTION_TIMEOUT = 2000
};

enum conn_exceptions {
    SOCKET_BIND_DENIED = INVALID_PORT + 1,
    SOCKET_INIT_DENIED
};

static const char host[] = "localhost";

int init_connection(int port, exception_s *exception);

#endif //IMAQLIQTESTTASK_CONNECTION_H
