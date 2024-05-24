#pragma once

#include "defines.h"
#include "core/asserts.h"

#include <vulkan/vulkan.h>

// Checks the given expression's return value against VK_SUCCESS.
#define VK_CHECK(expr)               \
    {                                \
        RASSERT(expr == VK_SUCCESS); \
    }

typedef struct vulkan_device {
    VkPhysicalDevice physical_device;
    VkDevice logical_device;
} vulkan_device;

typedef struct vulkan_context {
    VkInstance instance;
    VkAllocationCallbacks* allocator;

#if defined(_DEBUG)
    VkDebugUtilsMessengerEXT debug_messenger;
#endif

    vulkan_device device;
} vulkan_context;
