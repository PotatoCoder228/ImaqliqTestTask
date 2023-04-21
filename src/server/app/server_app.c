//
// Created by potato_coder on 21.04.23.
//

#include <stdbool.h>
#include "server_app.h"
#include "../../../include/server/connection_s.h"

int server_start(int64_t port, exception_s *exception) {
    int server_descrp = init_connection((int) port, exception);
    while(true){
        int accepted = accept(server_descrp, NULL, NULL);//ожидаем запрос от клиента
        if(accepted){

        }
    }
    close(server_descrp);
    return EXIT_SUCCESS;
}