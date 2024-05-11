#pragma once

#include "defines.h"

// Returns the length of the given string.
RAPI u64 string_length(const char* str);

RAPI char* string_duplicate(const char* str);

// Case-sensitive string comparison. True if the same, otherwise false.
RAPI b8 string_equals(const char* str0, const char* str1);
