#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "app/server_app.h"
#include "../../include/common/exception_s.h"
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#import <sys/types.h>
#import <sys/stat.h>

int main(int argc, char **argv) {
    exception_s *exception = new_exception();
    if (argc == 0) {
        throw_exception(exception, ARGS_IS_UNDEFINED, "Вы не предоставили порт в аргументах программы.\n");
        exception_destroy(exception);
        return EXIT_FAILURE;
    }
    char *end;
    int64_t port = 0;
    port = strtol(*argv, &end, 10);
    if (port < 1024 || port > 64000) {
        throw_exception(exception, ARGS_IS_UNDEFINED, "Вы не предоставили порт в аргументах программы.\n");
        exception_destroy(exception);
        return EXIT_FAILURE;
    }
    umask(0);
    pid_t pid = fork();
    if(pid < 0){
        throw_exception(exception, FORK_DENIED_EXCEPTION, "Не удалось создать дочерний процесс.");
        exception_destroy(exception);
        return EXIT_FAILURE;
    }
    else if(pid == 0){
        exception_destroy(exception);
        return EXIT_FAILURE;
    }
    server_start(port, exception);
    exception_destroy(exception);
    return EXIT_SUCCESS;
}
