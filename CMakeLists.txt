cmake_minimum_required(VERSION 3.16)
project(ImaqliqTestTask C)

set(CMAKE_C_STANDARD 11)

add_executable(server
        src/server/main.c
        src/server/connection/connection_s.c
        include/server/connection_s.h
        src/common/containers/vector_s.c
        include/common/vector_s.h
        src/common/containers/rb_tree_s.c
        include/common/rb_tree_s.h src/common/containers/list_s.c
        include/common/list_s.h include/common/cont-common.h
        include/common/containers.h
        src/common/exception/exception_s.c
        include/common/exception_s.h)

add_executable(client
        src/client/main.c
        src/common/containers/vector_s.c
        include/common/vector_s.h
        src/common/containers/rb_tree_s.c
        include/common/rb_tree_s.h
        src/common/containers/list_s.c
        include/common/list_s.h include/common/cont-common.h
        include/common/containers.h
        src/common/exception/exception_s.c
        include/common/exception_s.h src/server/app/server_app.c
        src/server/app/server_app.h src/client/client_app.c src/client/client_app.h)
