//
// Created by potato_coder on 21.04.23.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include "../../include/client/client_app.h"
#include "../../include/common/exception_s.h"
#include "../../include/common/connection_s.h"

int client_start(char *host) {
    struct addrinfo *ailist;
    struct addrinfo hint;
    memset(&hint, 0, sizeof(hint));
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;
    printf("%d", getaddrinfo(host, "uploader", &hint, &ailist));
    int64_t port = EAI_SERVICE;
    exception_s *exception = new_exception();
    while (true) {
        char str_port[5];
        printf("Введите порт:");
        char *buf = fgets(str_port, 5, stdin);
        port = strtol(str_port, &buf, 10);
        if (port <= 1024 || port > 64000) {
            printf("Некорректный порт");
        } else {
            break;
        }
    }
    int socket = init_client_connection((int) port, host, exception);
    if (socket == -1) {
        exception_destroy(exception);
        return EXIT_FAILURE;
    }
    while (true) {
        char path[1000];
        char *buf = fgets(path, 1000, stdin);
        if (strcmp(buf, "exit") == 0) {
            close(socket);
            exception_destroy(exception);
            break;
        }

    }
    return EXIT_SUCCESS;
}