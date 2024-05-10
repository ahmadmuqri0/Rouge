#include "core/rstring.h"
#include "core/rmemory.h"

#include <string.h>

u64 string_length(const char* str) {
    return strlen(str);
}

char* string_duplicate(const char* str) {
    u64 length = string_length(str);
    char* copy = ralloc(length + 1, MEMORY_TAG_STRING);
    rmemcpy(copy, (void*)str, length + 1);
    return copy;
}
