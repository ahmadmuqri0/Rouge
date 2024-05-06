#include "list.h"
#include "core/rmemory.h"
#include "core/logger.h"

void* _list_create(u64 length, u64 stride) {
    u64 header_size = LIST_FIELD_LENGTH * sizeof(u64);
    u64 array_size = length * stride;
    u64* new_array = ralloc(header_size * array_size, MEMORY_TAG_LIST);
    rmemset(new_array, 0, header_size * array_size);
    new_array[LIST_CAPACITY] = length;
    new_array[LIST_LENGTH] = 0;
    new_array[LIST_STRIDE] = stride;
    return (void*)(new_array + LIST_FIELD_LENGTH);
}

void _list_destroy(void* array) {
    u64* header = (u64*)array - LIST_FIELD_LENGTH;
    u64 header_size = LIST_FIELD_LENGTH * sizeof(u64);
    u64 total_size = header_size + header[LIST_CAPACITY] * header[LIST_STRIDE];
    rfree(header, total_size, MEMORY_TAG_LIST);
}

u64 _list_field_get(void* array, u64 field) {
    u64* header = (u64*)array - LIST_FIELD_LENGTH;
    return header[field];
}

void _list_field_set(void* array, u64 field, u64 value) {
    u64* header = (u64*)array - LIST_FIELD_LENGTH;
    header[field] = value;
}

void* _list_resize(void* array) {
    u64 length = list_length(array);
    u64 stride = list_stride(array);
    void* temp = _list_create((LIST_RESIZE_FACTOR * list_capacity(array)), stride);
    rmemcpy(temp, array, length * stride);

    _list_field_set(temp, LIST_LENGTH, length);
    _list_destroy(array);
    return temp;
}

void* _list_push(void* array, const void* value_ptr) {
    u64 length = list_length(array);
    u64 stride = list_stride(array);
    if (length >= list_capacity(array)) {
        array = _list_resize(array);
    }

    u64 addr = (u64)array;
    addr += (length * stride);
    rmemcpy((void*)addr, (void*)value_ptr, stride);
    _list_field_set(array, LIST_LENGTH, length + 1);
    return array;
}

void _list_pop(void* array, void* dest) {
    u64 length = list_length(array);
    u64 stride = list_stride(array);
    u64 addr = (u64)array;
    addr += ((length - 1) * stride);
    rmemcpy(dest, (void*)addr, stride);
    _list_field_set(array, LIST_LENGTH, length - 1);
}

void* _list_pop_at(void* array, u64 index, void* dest) {
    u64 length = list_length(array);
    u64 stride = list_stride(array);
    if (index >= length) {
        RERROR("Index outside the bounds of this array! Length: %i, index: %i", length, index);
        return array;
    }

    u64 addr = (u64)array;
    rmemcpy(dest, (void*)(addr + (index * stride)), stride);

    // If not on the last element, snip out the entry and copy the rest inward.
    if (index != length - 1) {
        rmemcpy(
            (void*)(addr + (index * stride)),
            (void*)(addr + ((index + 1) * stride)),
            stride * (length - index));
    }

    _list_field_set(array, LIST_LENGTH, length - 1);
    return array;
}
