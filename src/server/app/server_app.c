//
// Created by potato_coder on 21.04.23.
//

#include "server_app.h"
#include "../../../include/server/connection_s.h"

int server_start(int64_t port, exception_s *exception) {
    int server_descrp = init_connection((int) port, exception);
    close(server_descrp);
}