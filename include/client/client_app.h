//
// Created by potato_coder on 21.04.23.
//

#ifndef IMAQLIQTESTTASK_CLIENT_APP_H
#define IMAQLIQTESTTASK_CLIENT_APP_H

#include <stdint.h>
#include "../common/exception_s.h"

enum client_app_exceptions {
    HOST_ERROR = 0,
    SOCKET_ERROR,
    SENDING_ERROR,
    BREAK_PIPE_ERROR
};

int client_start(char *host);

void send_message(int socket, char *filename, exception_s *exception);

#endif //IMAQLIQTESTTASK_CLIENT_APP_H
