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
bool is_working = true;

static void *signal_handler(void *arg) {
    int err, signum;
    while (true) {
        err = sigwait(&mask, &signum);
        if (err != 0) {
            syslog(LOG_ERR, "Ошибка вызова функции sigwait");
            close(server_descr);
            return (0);
        }
        switch (signum) {
            case SIGHUP:
                syslog(LOG_INFO, "Завершение работы сервера после SIGHUP");
                close(server_descr);
                exit(0);
            case SIGTERM:
                syslog(LOG_INFO, "Завершение работы сервера SIGTERM");
                close(server_descr);
                exit(0);
            default:
                syslog(LOG_INFO, "Получен непредвиденный сигнал");
                break;
        }
    }
}

int server_start(int64_t port) {
    int err;
    pthread_t handler_thread;
    //сбрасываем действия по умолчанию и блокируем все сигналы
    struct sigaction sa;
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0) {
        syslog(LOG_ERR, "Не удалось сбросить действие SIGHUP");
    }
    sigfillset(&mask);
    if ((pthread_sigmask(SIG_BLOCK, &mask, NULL) != 0)) {
        syslog(LOG_ERR, "Ошибка выполнения операции SIG_BLOCK");
    }
    err = pthread_create(&handler_thread, NULL, signal_handler, 0);
    if (err != 0) {
        syslog(LOG_ERR, "Невозможно создать поток.");
    }
    server_descr = init_server_connection((int) port);
    FILE* new_file = fopen("sended_file","wb");
    while (is_working) {
        int accepted = accept(server_descr, NULL, NULL);//ожидаем запрос от клиента
        if (accepted) {
            do
        }
    }
    return EXIT_SUCCESS;
}