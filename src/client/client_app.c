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
    FILE *file = NULL;
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("%s\n", strerror(errno));
        return;
    }
    size_t b;
    ssize_t pipe_error;
    while (!feof(file)) {
        char buffer[240] = {0};
        b = fread(buffer, 1, sizeof(buffer), file);
        if (b > 0) {
            pipe_error = send(socket, buffer, b, MSG_NOSIGNAL);
            if(pipe_error == -1){
                throw_exception(exception, BREAK_PIPE_ERROR, strerror(errno));
                fclose(file);
                return;
            }
        }
        else {
            throw_exception(exception, SENDING_ERROR, strerror(errno));
            break;
        }
        fflush(file);
    }
    fclose(file);
    printf("The file was sent successfully\n");
}

int client_start(char *host) {
    int64_t port;
    exception_s *exception = new_exception();
    printf("Welcome to client application.\n");
    printf("exit - application shutdown.\n");
    while (true) {
        if (feof(stdin)) {
            clearerr(stdin);
        }
        char str_port[10];
        printf("Input port:");
        char *buf = fgets(str_port, 10, stdin);
        if (buf == NULL) {
            printf("You didn't enter port.\n");
            continue;
        } else if (strcmp(str_port, "exit\n") == 0) {
            printf("Application shutdown...\n");
            exception_destroy(exception);
            return EXIT_SUCCESS;
        }
        port = strtol(str_port, &buf, 10);
        if (port <= 1024 || port > 64000) {
            printf("Invalid port\n");
        } else {
            break;
        }
    }
    while (true) {
        if (feof(stdin)) {
            clearerr(stdin);
        }
        printf("Input file:");
        char path[255];
        char *buf = fgets(path, 255, stdin);
        if (buf == NULL) {
            printf("You didn't input filename or \"exit\". Retry.\n");
            continue;
        }
        buf = strtok(buf, "\n\r");
        (buf == NULL) ? buf = path : buf;
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