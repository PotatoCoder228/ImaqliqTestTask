//
// Created by potato_coder on 21.04.23.
//

#include <stdbool.h>
#include <syslog.h>
#include <netdb.h>
#include "../../../include/common/connection_s.h"
#include "../../../include/client/client_app.h"


int init_server_connection(int port) {
    int server_descr = socket(AF_INET, SOCK_STREAM, 0);
    if (server_descr == -1) {
        syslog(LOG_ERR, "Не удалось создать сокет\n");
        return EXIT_FAILURE;
    }
    //bind socket
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    int result = bind(server_descr,
                      (struct sockaddr *) &addr, sizeof(addr));
    if (!result) {
        close(server_descr);
        syslog(LOG_ERR, "Не удалось привязать адрес к сокету.\n");
        return EXIT_FAILURE;
    }
    result = listen(server_descr, 10);
    if (result == -1) {
        close(server_descr);
        syslog(LOG_ERR, "Не удалось создать очередь для прослушивания сокета.\n");
        return EXIT_FAILURE;
    }
    syslog(LOG_INFO, "Сокет успешно инициализирован");
    return server_descr;
}
int connect_retry(int domain, int type, int protocol, const struct sockaddr *addr, socklen_t adr_len) {
    int numsec, fd;
    for (int numsec = 1; numsec <= CONNECTION_TIMEOUT; numsec*=2) {
        if ((fd = socket(domain, type, protocol)) < 0)
            printf("%d", fd);
            return (-1);
        if (connect(fd, addr, adr_len) == 0) {
            printf("%d", fd);
            return (fd);
        }
        close(fd);
        if (numsec <= CONNECTION_TIMEOUT / 2)
            sleep(numsec);
    }
    return (-1);
}

int init_client_connection(int port, char *host, exception_s *exception) {

    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    int sockfd, err;
    memset(&hint, 0, sizeof(hint));
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;
    hint.ai_family = AF_INET;
    if ((err = getaddrinfo(host, NULL, &hint, &ailist)) != 0)
        printf("ошибка вызова функции getaddrinfo: %s", gai_strerror(err));
    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        if ((sockfd = connect_retry(aip->ai_family, SOCK_STREAM, 0,
                                    aip->ai_addr, aip->ai_addrlen)) < 0) {
            err = errno;
        }
        printf("%s", strerror(err));
        exit(0);
    }
    /*
    int socket_descr = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_descr == -1) {
        throw_exception(exception, NOT_RESOLVE_CONNECT, "Не удалось создать сокет\n");
        return -1;
    }
    struct hostent *host_entry;
    host_entry = gethostbyname(host);
    if (!host_entry) {
        throw_exception(exception, NOT_RESOLVE_HOST, "Не удалось получить хост\n");
        return -1;
    }
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr = *((struct in_addr *) host_entry->h_addr);;
    addr.sin_port = htons(port);

    int result = connect(socket_descr,
                         (struct sockaddr *) &addr, sizeof(addr));
    if (result == -1) {
        close(socket_descr);
        throw_exception(exception, NOT_RESOLVE_CONNECT, strerror(errno));
        return -1;
    }
    return socket_descr;
    */
    return sockfd;
}
