//
// Created by potato_coder on 21.04.23.
//

#ifndef IMAQLIQTESTTASK_CLIENT_APP_H
#define IMAQLIQTESTTASK_CLIENT_APP_H

#include <stdint.h>

enum client_app_exceptions {
    NOT_RESOLVE_HOST,
    NOT_RESOLVE_SOCKET,
    NOT_RESOLVE_CONNECT
};

int client_start(char *host);

#endif //IMAQLIQTESTTASK_CLIENT_APP_H
