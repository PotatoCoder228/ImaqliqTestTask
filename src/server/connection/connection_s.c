//
// Created by potato_coder on 21.04.23.
//

#include <stdbool.h>
#include "../../../include/server/connection_s.h"
#include "../../../include/common/exception_s.h"


int init_connection(int port, exception_s *exception) {
    int server_descr = socket(AF_INET, SOCK_STREAM, 0);
    if (server_descr == -1) {
        throw_exception(exception, SOCKET_INIT_DENIED, "Не удалось создать сокет\n");
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
        throw_exception(exception, SOCKET_BIND_DENIED, "Не удалось привязать адрес к сокету.\n");
        return EXIT_FAILURE;
    }
    result = listen(server_descr, 10);
    if (result == -1) {
        close(server_descr);
        throw_exception(exception, SOCKET_BIND_DENIED, "Не удалось создать очередь для прослушивания сокета.\n");
        return EXIT_FAILURE;
    }
}