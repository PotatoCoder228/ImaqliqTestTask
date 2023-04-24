//
// Created by potato_coder on 21.04.23.
//

#include <stdbool.h>
#include <signal.h>
#include <syslog.h>
#include "../../../include/server/server_app.h"
#include "../../../include/common/connection_s.h"

sigset_t mask;

int server_descr;
FILE *file = NULL;

static void *signal_handler(void *arg) {
    int err, signum;
    while (true) {
        err = sigwait(&mask, &signum);
        if (err != 0) {
            syslog(LOG_ERR, "sigwait() call error");
            close(server_descr);
            closelog();
            if (file != NULL) fclose(file);
            return (0);
        }
        switch (signum) {
            case SIGHUP:
                syslog(LOG_INFO, "Server shutdown after the SIGHUP");
                close(server_descr);
                closelog();
                if (file != NULL) fclose(file);
                exit(0);
            case SIGTERM:
                syslog(LOG_INFO, "Server shutdown after the SIGTERM");
                close(server_descr);
                if (file != NULL) fclose(file);
                closelog();
                exit(0);
            default:
                syslog(LOG_WARNING, "Undefined signal");
                break;
        }
    }
}

bool receive_file(int socket) {
    char filename[255];
    time_t now = time(0);
    char *data_str = ctime(&now);
    if (data_str == NULL) {
        syslog(LOG_ERR, "ctime() return NULL");
        return false;
    }
    sprintf(filename, "Client_file_%s.txt", strtok(data_str, "\r\n"));
    char request[240] = {0};
    size_t read = recv(socket, request, sizeof(request), 0);
    while (read > 0) {
        if (file == NULL) {
            file = fopen(filename, "w");
            if (file == NULL) {
                syslog(LOG_ERR, "File creation error");
                return false;
            }
        }
        for (int i = 0; i < 240; i++) {
            if (request[i] != '\0') {
                fputc(request[i], file);
            }
        }
        fflush(file);
        for (int i = 0; i < 240; i++) {
            request[i] = 0;
        }
        read = recv(socket, request, sizeof(request), 0);
    }
    if (file != NULL) {
        fflush(file);
        int closed = fclose(file);
        if (!closed) {
            syslog(LOG_ERR, "File %s is not closed", filename);
            file = NULL;
            return false;
        }
        syslog(LOG_INFO, "File %s is received", filename);
        file = NULL;
    }
    return true;
}

void server_start(int64_t port) {
    openlog("file-server", LOG_PID, LOG_DAEMON);
    syslog(LOG_INFO, "Daemon server started");
    int err;
    pthread_t handler_thread;
    struct sigaction sa;
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0) {
        syslog(LOG_ERR, "SIGHUP reset error");
    }
    sigfillset(&mask);
    if ((pthread_sigmask(SIG_BLOCK, &mask, NULL) != 0)) {
        syslog(LOG_ERR, "SIG_BLOCK execution error");
    }
    err = pthread_create(&handler_thread, NULL, signal_handler, 0);
    if (err != 0) {
        syslog(LOG_ERR, "Cannot make new thread");
    }
    int is_working = true;
    while (is_working != false) {
        is_working = server_connection((int) port);
    }
}