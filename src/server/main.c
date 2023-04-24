#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/server/server_app.h"
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv) {
    exception_s *exception = new_exception();

    if (exception == NULL) {
        fprintf(stderr, "%s", strerror(errno));
    }
    if (argc < 2) {
        throw_exception(exception, ARGS_IS_UNDEFINED, "Port not found.\n");
        exception_destroy(exception);
        return EXIT_FAILURE;
    }
    char *end;
    int64_t port = 0;
    port = strtol(argv[1], &end, 10);
    if (port < 1024 || port > 50000) {
        throw_exception(exception, ARGS_IS_UNDEFINED, "Invalid port in args.\n");
        exception_destroy(exception);
        return EXIT_FAILURE;
    }
    umask(0);
    pid_t pid = fork();
    if (pid < 0) {
        throw_exception(exception, FORK_DENIED_EXCEPTION, "Cannot make new daemon process.");
        exception_destroy(exception);
        return EXIT_FAILURE;
    } else if (pid != 0) {
        printf("Server-daemon successfully started!\n");
        exception_destroy(exception);
        return EXIT_SUCCESS;
    }
    exception_destroy(exception);
    server_start(port);
    return EXIT_SUCCESS;
}