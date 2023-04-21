#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/server/server_app.h"
#include "../../include/common/exception_s.h"
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <syslog.h>

int main(int argc, char **argv) {
    exception_s *exception = new_exception();

    if (exception == NULL) {
        fprintf(stderr, "%s", strerror(errno));
    }
    if (argc == 0) {
        throw_exception(exception, ARGS_IS_UNDEFINED, "Вы не предоставили порт в аргументах программы.\n");
        exception_destroy(exception);
        return EXIT_FAILURE;
    }
    char *end;
    int64_t port = 0;
    port = strtol(argv[1], &end, 10);
    if (port < 1024 || port > 64000) {
        throw_exception(exception, ARGS_IS_UNDEFINED, "Вы не предоставили порт в аргументах программы.\n");
        exception_destroy(exception);
        return EXIT_FAILURE;
    }
    umask(0);
    pid_t pid = fork();
    if (pid < 0) {
        throw_exception(exception, FORK_DENIED_EXCEPTION, "Не удалось создать дочерний процесс.");
        exception_destroy(exception);
        return EXIT_FAILURE;
    } else if (pid != 0) {
        exception_destroy(exception);
        return EXIT_SUCCESS;
    }
    exception_destroy(exception);
    openlog("server_logs", LOG_INFO, LOG_DAEMON);
    server_start(port);
    syslog(LOG_INFO, "Сервер успешно завершил работу.");
    return EXIT_SUCCESS;
}