#pragma once

#include "defines.h"

typedef enum memory_tag {
    // For temporary use. should be assigned one of the below or have a new tag created.
    MEMORY_TAG_UKNOWN,
    MEMORY_TAG_ARRAY,
    MEMORY_TAG_LIST,
    MEMORY_TAG_DICT,
    MEMORY_TAG_RING_QUEUE,
    MEMORY_TAG_BST,
    MEMORY_TAG_STRING,
    MEMORY_TAG_APPLICATION,
    MEMORY_TAG_JOB,
    MEMORY_TAG_TEXTURE,
    MEMORY_TAG_MATERIAL_INSTANCE,
    MEMORY_TAG_RENDERER,
    MEMORY_TAG_GAME,
    MEMORY_TAG_TRANSFORM,
    MEMORY_TAG_ENTITY,
    MEMORY_TAG_ENTITY_NODE,
    MEMORY_TAG_SCENE,

    MEMORY_TAG_MAX_TAGS,
} memory_tag;

RAPI void initialize_memory();
RAPI void shutdown_memory();

RAPI void* ralloc(u64 size, memory_tag tag);

RAPI void rfree(void* block, u64 size, memory_tag tag);

RAPI void* rmemzero(void* block, u64 size);

RAPI void* rmemcpy(void* dest, void* source, u64 size);

RAPI void* rmemset(void* dest, i32 value, u64 size);

RAPI char* get_memory_usage_str();
