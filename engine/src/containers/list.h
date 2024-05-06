#pragma once

#include "defines.h"

/* 
Memory layout
u64 capacity = number elements that can be held
u64 length = number of elements currently contained
u64 stride = size of each element in bytes
void* elements
*/

enum {
    LIST_CAPACITY,
    LIST_LENGTH,
    LIST_STRIDE,
    LIST_FIELD_LENGTH
};

RAPI void* _list_create(u64 length, u64 stride);
RAPI void _list_destroy(void* array);

RAPI u64 _list_field_get(void* array, u64 field);
RAPI void _list_field_set(void* array, u64 field, u64 value);

RAPI void* _list_resize(void* array);

RAPI void* _list_push(void* array, const void* value_ptr);
RAPI void _list_pop(void* array, void* dest);

RAPI void* _list_pop_at(void* array, u64 index, void* dest);
RAPI void* _list_insert_at(void* array, u64 index, void* value_ptr);

#define LIST_DEFAULT_CAPACITY 1
#define LIST_RESIZE_FACTOR 2

#define list_create(type) \
    _list_create(LIST_DEFAULT_CAPACITY, sizeof(type))

#define list_reserve(type, capacity) \
    _list_create(capacity, sizeof(type))

#define list_destroy(array) _list_destroy(array);

#define list_push(array, value)           \
    {                                       \
        typeof(value) temp = value;         \
        array = _list_push(array, &temp); \
    }
// NOTE: could use __auto_type for temp above, but intellisense
// for VSCode flags it as an unknown type. typeof() seems to
// work just fine, though. Both are GNU extensions.

#define list_pop(array, value_ptr) \
    _list_pop(array, value_ptr)

#define list_insert_at(array, index, value)           \
    {                                                   \
        typeof(value) temp = value;                     \
        array = _list_insert_at(array, index, &temp); \
    }

#define list_pop_at(array, index, value_ptr) \
    _list_pop_at(array, index, value_ptr)

#define list_clear(array) \
    _list_field_set(array, LIST_LENGTH, 0)

#define list_capacity(array) \
    _list_field_get(array, LIST_CAPACITY)

#define list_length(array) \
    _list_field_get(array, LIST_LENGTH)

#define list_stride(array) \
    _list_field_get(array, LIST_STRIDE)

#define list_length_set(array, value) \
    _list_field_set(array, LIST_LENGTH, value)
