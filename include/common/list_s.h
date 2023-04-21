//
// Created by potato_coder on 21.04.23.
//

#ifndef IMAQLIQTESTTASK_LIST_S_H
#define IMAQLIQTESTTASK_LIST_S_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cont-common.h"

typedef struct list_s list_s;

object_s *list_object(list_s *list);

void list_set_object(list_s *list, object_s object);

list_s *list_next(list_s *list);

void list_set_next(list_s *list, list_s *next);

void list_foreach_free(list_s *list, void (*destroy)(void *data));

void list_destroy(list_s *list);

list_s *new_list_node();

list_s *new_list(object_s object);

list_s *list_get_last_node(list_s *node);

bool list_push(list_s *node, object_s object);

object_s *list_pop(list_s *node);

bool list_add_last(list_s *node, object_s object);

bool list_add_first(list_s **node, object_s object);

size_t list_size(list_s *node);

object_s *list_get(list_s *node, size_t index);

bool list_delete(list_s **list, size_t index, void (*destroyer)(void *data));

bool list_insert(list_s **node, size_t index, object_s object);

void list_foreach(list_s *list, callback iter_func);

void list_print(FILE *stream, list_s *list, int (printer)(FILE *, char *, void *));

#endif //IMAQLIQTESTTASK_LIST_S_H
