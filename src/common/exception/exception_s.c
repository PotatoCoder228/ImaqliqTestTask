//
// Created by potato_coder on 21.04.23.
//

#include "../../../include/common/exception_s.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct exception_s {
    char *msg;
    int code;
} exception_s;

exception_s *new_exception() {
    exception_s *exception = malloc(sizeof(exception_s));
    exception->msg = malloc(1);
    exception->msg[0] = '\0';
    exception->code = 0;
    return exception;
}

static void exception_set_msg(exception_s *exception, char *string) {
    if (exception != NULL && string != NULL) {
        char *is_alloc = realloc(exception->msg, strlen(string) + 1);
        if (is_alloc) {
            exception->msg = is_alloc;
            strcpy(exception->msg, string);
        }
    }
}

char *exception_get_msg(exception_s *exception) {
    if (exception != NULL) {
        return exception->msg;
    }
    return NULL;
}

int exception_get_code(exception_s *exception) {
    if (exception != NULL) {
        return exception->code;
    }
    return -1;
}

int exception_set_code(exception_s *exception, int code) {
    if (exception != NULL) {
        exception->code = code;
    }
    return -1;
}

void throw_exception(exception_s *exception, int code, char *message) {
    if (exception != NULL) {
        exception_set_msg(exception, message);
        exception_set_code(exception, code);
        fprintf(stderr, "%s", exception->msg);
    }
}

void exception_destroy(exception_s *exception) {
    free(exception->msg);
    free(exception);
}