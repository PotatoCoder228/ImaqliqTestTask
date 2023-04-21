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
#include "../../include/common/connection_s.h"

void send_message(int socket, char *filename, exception_s *exception) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("%s", strerror(errno));
        return;
    }
    char buffer[50] = {0};
    uint64_t b;
    while (!feof(file)) {
        b = fread(buffer, 1, sizeof(buffer), file);
        if (b > 0) send(socket, buffer, b, 0);
        else throw_exception(exception, SENDING_ERROR, strerror(errno));
    }
    fclose(file);
    printf("The file was sent successfully\n");
}

int client_start(char *host) {
    int64_t port;
    exception_s *exception = new_exception();
    while (true) {
        char str_port[10];
        printf("Input port:");
        char *buf = fgets(str_port, 10, stdin);
        port = strtol(str_port, &buf, 10);
        if (port <= 1024 || port > 64000) {
            printf("Invalid port\n");
        } else {
            break;
        }
    }
    while (true) {
        printf("Input file:");
        char path[255];
        char *buf = fgets(path, 255, stdin);
        buf = strtok(buf, "\n\r");
        if (strcmp(buf, "exit") == 0) {
            exception_destroy(exception);
            break;
        }
        bool socket = client_connection((int) port, host, buf, exception);
        if (socket == false) {
            exception_destroy(exception);
            return EXIT_FAILURE;
        }
        fflush(stdout);
    }
    return EXIT_SUCCESS;
}