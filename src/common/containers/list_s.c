//
// Created by potato_coder on 21.04.23.
//

#include "../../../include/common/list_s.h"


typedef struct list_s {
    object_s object;
    list_s *next;
} list_s;

object_s *list_object(list_s *list) {
    if (list != NULL) {
        return list->object;
    }
    return NULL;
}

void list_set_object(list_s *list, object_s object) {
    list->object = object;
}

list_s *list_next(list_s *list) {
    if (list != NULL) {
        return list->next;
    }
    return NULL;
}

void list_set_next(list_s *list, list_s *next) {
    list->next = next;
}

void list_foreach_free(list_s *list, void (*destroy)(void *data)) {
    list_s *buffer;
    while (list != NULL) {
        buffer = list;
        list = list->next;
        destroy(buffer->object);
    }
}

void list_destroy(list_s *list) {
    if (list != NULL) {
        list_s *buffer;
        while (list != NULL) {
            buffer = list;
            list = list->next;
            free(buffer);
        }
    }
}

list_s *new_list_node() {
    list_s *list = malloc(sizeof(list_s));
    if (list != NULL) {
        list->next = NULL;
        list->object = NULL;
    }
    return list;
}

list_s *new_list(object_s object) {
    list_s *list = malloc(sizeof(list_s));
    if (list != NULL) {
        list->object = object;
        list->next = NULL;
    }
    return list;
}

list_s *list_get_last_node(list_s *node) {
    if (node != NULL) {
        list_s *prev_node = node;
        while (node != NULL) {
            prev_node = node;
            node = node->next;
        }
        return prev_node;
    }
    return NULL;
}

bool list_push(list_s *node, object_s object) {
    if (node != NULL) {
        node = list_get_last_node(node);
        if (node == NULL) {
            return false;
        }
        list_s *add_node = new_list_node();
        add_node->object = object;
        node->next = add_node;
        return true;
    }
    return false;
}

object_s *list_pop(list_s *node) {
    if (node != NULL) {
        list_s *prev_node = node;
        list_s *last_node = node;
        while (node != NULL) {
            prev_node = last_node;
            last_node = node;
            node = node->next;
        }
        prev_node->next = NULL;
        void *value = last_node->object;
        free(last_node);
        return value;
    }
    return NULL;
}

bool list_add_last(list_s *node, object_s object) {
    if (node != NULL) {
        node = list_get_last_node(node);
        if (node == NULL) {
            return false;
        }
        list_s *add_node = new_list_node();
        add_node->object = object;
        node->next = add_node;
        return true;
    }
    return false;
}

bool list_add_first(list_s **node, object_s object) {
    if (node == NULL) {
        return false;
    }
    list_s *new_node = new_list_node();
    if (new_node == NULL) {
        return false;
    }
    new_node->object = object;
    new_node->next = NULL;
    list_s *buffer;
    if ((*node)->object != NULL) {
        buffer = new_node;
        new_node = *node;
        *node = buffer;
        (*node)->next = new_node;
    } else {
        *node = new_node;
    }
    return true;
}

size_t list_size(list_s *node) {
    size_t counter = 0;
    while (node != NULL) {
        counter += 1;
        node = node->next;
    }
    return counter;
}

object_s *list_get(list_s *node, size_t index) {
    if (node == NULL) {
        return NULL;
    }
    size_t size = list_size(node);
    if (index > size) {
        return NULL;
    }
    for (size_t i = 0; i < index; i++) {
        node = node->next;
    }
    return node->object;
}

bool list_delete(list_s **list, size_t index, void (*destroyer)(void *data)) {
    list_s *start = *list;
    if (list != NULL) {
        list_s *buf = start;
        for (size_t i = 0; i < index; i++) {
            buf = start;
            start = start->next;
        }
        destroyer(start->object);
        buf->next = start->next;
        free(start);
        return true;
    }
    return false;
}

bool list_insert(list_s **node, size_t index, object_s object) {
    if (node == NULL) {
        return false;
    }
    size_t size = list_size(*node);
    if (index > size) {
        return false;
    }
    list_s *new_node = new_list_node();
    if (new_node != NULL) {
        if (index == 0) {
            new_node->object = object;
            new_node->next = *node;
            *node = new_node;
            return true;
        }
        new_node->object = object;
        for (size_t i = 1; i < index; i++) {
            *node = (*node)->next;
        }
        new_node->next = (*node)->next;
        (*node)->next = new_node;
        return true;
    }
    return false;
}

void list_foreach(list_s *list, callback iter_func) {
    list_s *buf = list;
    while (list != NULL) {
        buf = list;
        iter_func(list);
        list = buf->next;
    }
}

void list_print(FILE *stream, list_s *list, int(printer)(FILE *, char *, void *)) {
    while (list != NULL) {
        printer(stream, "%s", list->object);
        list = list->next;
    }
}