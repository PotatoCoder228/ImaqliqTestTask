//
// Created by potato_coder on 21.04.23.
//

#include <stdbool.h>
#include <syslog.h>
#include <netdb.h>
#include "../../../include/common/connection_s.h"
#include "../../../include/client/client_app.h"
#include <errno.h>
#include <sys/socket.h>


bool server_connection(int port) {
    struct sockaddr_in client;
    struct sockaddr_in server;
    int sock;
    int new_sock;
    int namelen;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        syslog(LOG_ERR, "Socket init error: %s", strerror(errno));
        return false;
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        syslog(LOG_ERR, "Socket binding error:%s", strerror(errno));
        return false;
    }

    if (listen(sock, 1) != 0) {
        syslog(LOG_ERR, "Socket listening error: %s", strerror(errno));
        return false;
    }
    namelen = sizeof(client);
    if ((new_sock = accept(sock, (struct sockaddr *) &client, (socklen_t *) (&namelen))) == -1) {
        syslog(LOG_ERR, "Socket accepting error: %s", strerror(errno));
        return false;
    }
    if (!receive_file(new_sock)) {
        syslog(LOG_ERR, "File is not received: %s", strerror(errno));
        close(new_sock);
        close(sock);
        return false;
    }
    close(new_sock);
    close(sock);
    return true;
}

bool client_connection(int port, char *host, char *buf, exception_s *exception) {
    struct hostent *host_name;
    struct sockaddr_in server;
    int sock;

    host_name = gethostbyname(host);
    if (host_name == (struct hostent *) 0) {
        throw_exception(exception, HOST_ERROR, "Error of getting host");
        return false;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = *((unsigned long *) host_name->h_addr);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        throw_exception(exception, SOCKET_ERROR, "Socket init error");
        return false;
    }

    int connected = connect(sock, (struct sockaddr *) &server, sizeof(server));
    int time = CONNECTION_TIMEOUT;
    while (connected < 0 && time > 0) {
        printf("Failed to connect, try again...\n");
        fflush(stdout);
        connected = connect(sock, (struct sockaddr *) &server, sizeof(server));
        sleep(1);
        time -= 10;
    }
    if (time < 1 && connected < 0) {
        printf("Failed to connect, try again...\n");
        return false;
    }

    send_message(sock, buf, exception);
    close(sock);
    return true;
}
