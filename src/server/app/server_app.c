//
// Created by potato_coder on 21.04.23.
//

#include <stdbool.h>
#include <signal.h>
#include <syslog.h>
#include "../../../include/server/server_app.h"
#include "../../../include/common/connection_s.h"

sigset_t mask;

pthread_mutex_t mutex;
FILE *file = NULL;

static void *signal_handler(void *arg) {
    int err, signum;
    while (true) {
        err = sigwait(&mask, &signum);
        if (err != 0) {
            pthread_mutex_lock(&mutex);
            syslog(LOG_ERR, "sigwait() call error");
            closelog();
            if (file != NULL) fclose(file);
            exit(EXIT_FAILURE);
        }
        switch (signum) {
            case SIGHUP:
                pthread_mutex_lock(&mutex);
                syslog(LOG_INFO, "Server shutdown after the SIGHUP");
                closelog();
                if (file != NULL) fclose(file);
                exit(EXIT_SUCCESS);
            case SIGTERM:
                pthread_mutex_lock(&mutex);
                syslog(LOG_INFO, "Server shutdown after the SIGTERM");
                if (file != NULL) fclose(file);
                closelog();
                exit(EXIT_SUCCESS);
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
            pthread_mutex_lock(&mutex);
            file = fopen(filename, "w");
            pthread_mutex_unlock(&mutex);
            if (file == NULL) {
                syslog(LOG_ERR, "File creation error");
                return false;
            }
        }
        for (int i = 0; i < 240; i++) {
            if (request[i] != '\0') {
                pthread_mutex_lock(&mutex);
                fputc(request[i], file);
                pthread_mutex_unlock(&mutex);
            } else {
                break;
            }
        }
        pthread_mutex_lock(&mutex);
        fflush(file);
        pthread_mutex_unlock(&mutex);
        for (int i = 0; i < 240; i++) {
            request[i] = 0;
        }
        read = recv(socket, request, sizeof(request), 0);
    }
    if (file != NULL) {
        pthread_mutex_lock(&mutex);
        fflush(file);
        int closed = fclose(file);
        pthread_mutex_unlock(&mutex);
        if (closed != 0) {
            syslog(LOG_ERR, "File %s is not closed", filename);
            return false;
        }
        syslog(LOG_INFO, "File %s is received", filename);
    }
    file = NULL;
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
    syslog(LOG_INFO, "Daemon server shutdown");
}