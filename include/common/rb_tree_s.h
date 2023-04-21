//
// Created by potato_coder on 21.04.23.
//

#ifndef IMAQLIQTESTTASK_RB_TREE_S_H
#define IMAQLIQTESTTASK_RB_TREE_S_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "cont-common.h"

typedef struct rb_tree_s rb_tree_s;

rb_tree_s *new_rb_tree(object_s key);

rb_tree_s *new_rb_node(object_s key);

void rb_destroy(void *node);

bool rb_is_empty(rb_tree_s *node);

void rb_set_color(rb_tree_s *node, int8_t color);

void rb_set_key(rb_tree_s *node, object_s key);

void rb_set_p(rb_tree_s *node, rb_tree_s *parent);

void rb_set_left(rb_tree_s *node, rb_tree_s *left);

void rb_set_right(rb_tree_s *node, rb_tree_s *right);

object_s rb_key(rb_tree_s *node);

int8_t rb_color(rb_tree_s *node);

rb_tree_s *rb_parent(rb_tree_s *node);

rb_tree_s *rb_left(rb_tree_s *node);

rb_tree_s *rb_right(rb_tree_s *node);

void rb_inorder_print(FILE *stream, rb_tree_s *node, int printer(FILE *, char *mode, void *));

void rb_print(FILE *stream, rb_tree_s *root, int printer(FILE *, char *mode, void *), int depth);

rb_tree_s *rb_search(rb_tree_s *node, object_s target, int comparator(void *, void *));

rb_tree_s *rb_max(rb_tree_s *node);

rb_tree_s *rb_min(rb_tree_s *node);

rb_tree_s *rb_successor(rb_tree_s *node);

rb_tree_s *rb_predecessor(rb_tree_s *node);

bool rb_insert(rb_tree_s **root, rb_tree_s *z, int comparator(void *, void *));

bool rb_delete(rb_tree_s **root, rb_tree_s *z);

void rb_foreach_free(rb_tree_s *node, void (func)(void *));

rb_tree_s *rb_start(rb_tree_s *root);

bool rb_has_next(rb_tree_s *node);

bool rb_has_prev(rb_tree_s *node);

rb_tree_s *rb_prev(rb_tree_s *node);

rb_tree_s *rb_next(rb_tree_s *node);

rb_tree_s *rb_end(rb_tree_s *root);

#endif //IMAQLIQTESTTASK_RB_TREE_S_H
