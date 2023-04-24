#include <stdio.h>
#include "../../include/client/client_app.h"

//
// Created by potato_coder on 21.04.23.
//
int main(int argc, char **argv) {
    if (argc > 1) {
        client_start(argv[1]);
    } else {
        printf("You didn't input host in program args\n");
    }
    return 0;
}
