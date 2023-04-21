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
#include "exception_s.h"
#include "../server/server_app.h"


enum conn_consts {
    CONNECTION_TIMEOUT = 128
};

static const char host[] = "localhost";

int init_server_connection(int port);

int init_client_connection(int port, char *host, exception_s *exception);

#endif //IMAQLIQTESTTASK_CONNECTION_H
