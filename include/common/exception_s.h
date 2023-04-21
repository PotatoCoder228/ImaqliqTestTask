//
// Created by potato_coder on 21.04.23.
//

#ifndef IMAQLIQTESTTASK_EXCEPTION_S_H
#define IMAQLIQTESTTASK_EXCEPTION_S_H
typedef struct exception_s exception_s;

exception_s *new_exception();

char *exception_get_msg(exception_s *exception);

int exception_get_code(exception_s *exception);

int exception_set_code(exception_s *exception, int code);

void throw_exception(exception_s *exception, int code, char *message);

void exception_destroy(exception_s *exception);

#endif //IMAQLIQTESTTASK_EXCEPTION_S_H
