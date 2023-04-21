//
// Created by potato_coder on 21.04.23.
//

#include "../../../include/common/vector_s.h"

typedef struct vector_s {
    object_s *objects;
    size_t capacity;
    size_t size;
} vector_s;

vector_s *new_vector() {
    vector_s *new_vector = malloc(sizeof(vector_s));
    if (new_vector) {
        new_vector->objects = malloc(sizeof(object_s) * VECTOR_INIT_CAPACITY);
        if (new_vector->objects) {
            new_vector->capacity = VECTOR_INIT_CAPACITY;
        }
        new_vector->size = 0;
    }
    return new_vector;
}

bool vector_resize(vector_s *vector, size_t capacity) {
    object_s *objects = realloc(vector->objects, sizeof(object_s) * capacity);
    if (objects) {
        vector->objects = objects;
        vector->capacity = capacity;
        return true;
    }
    return false;
}

object_s *vector_objects(vector_s *vector) {
    if (vector != NULL) {
        return vector->objects;
    }
    return NULL;
}

size_t vector_size(vector_s *vector) {
    if (vector != NULL) {
        return vector->size;
    }
    return 0;
}

size_t vector_capacity(vector_s *vector) {
    if (vector != NULL) {
        return vector->capacity;
    }
    return 0;
}

bool vector_push(vector_s *vector, object_s object) {
    if (vector != NULL && object != NULL) {
        bool stat;
        if (vector->size == vector->capacity) {
            stat = vector_resize(vector, (vector->capacity) + 25);
            if (!stat) {
                return stat;
            }
        }
        vector->objects[vector->size] = object;
        (vector->size)++;
        return true;
    }
    return false;
}

object_s vector_pop(vector_s *vector) {
    if (vector != NULL && vector->size > 0) {
        if (vector->capacity == VECTOR_INIT_CAPACITY) {
            (vector->size)--;
            return vector->objects[vector->size];
        }
        (vector->size)--;
        object_s *object = vector->objects[vector->size];
        if ((vector->size - 1) < (vector->capacity - 25)) {
            vector_resize(vector, (vector->capacity - 25));
        }
        return object;
    }
    return NULL;
}

bool vector_set(vector_s *vector, object_s object, size_t index) {
    if (vector != NULL) {
        if (index < vector->size) {
            vector->objects[index] = object;
            return true;
        }
        return false;
    }
    return false;
}

object_s vector_get(vector_s *vector, size_t index) {
    if (vector != NULL) {
        if (index < vector->size) {
            return vector->objects[index];
        }
        return NULL;
    }
    return NULL;
}

bool vector_delete(vector_s *vector, size_t index, void (*destroy)(void *)) {
    if (vector != NULL) {
        if (index < vector->size) {
            object_s *trash = vector->objects[index];
            for (size_t i = index; i < vector->size; i++) {
                vector->objects[i] = vector->objects[i + 1];
            }
            (vector->size)--;
            if ((vector->size < vector->capacity) && (vector->size > VECTOR_INIT_CAPACITY)) {
                vector_resize(vector, vector->capacity - 25);
            }
            destroy(trash);
            return true;
        }
        return false;
    }
    return false;
}

void vector_foreach(vector_s *vector, callback f) {
    for (int i = 0; i < vector_size(vector); i++) f(vector_get(vector, i));
}

void vector_foreach_free(vector_s *vector, void (destroy)(void *)) {
    for (int i = 0; i < vector_size(vector); i++) destroy(vector_get(vector, i));
}

void vector_destroy(vector_s *vector) {
    free(vector->objects);
    free(vector);
}

void vector_print(FILE *stream, vector_s *vector, int (printer)(FILE *, char *mode, void *)) {
    for (size_t i = 0; i < vector->size; i++) {
        printer(stream, " ", vector->objects[i]);
    }
}