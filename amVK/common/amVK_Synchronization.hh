#pragma once
#include <vulkan/vulkan.h>

namespace amVK_Sync {
    namespace CommandPoolCreateFlagBits
    {
        inline constexpr VkCommandPoolCreateFlags RecordBuffer_Once         = 0;    // You can't BEGIN/RECORD same CMDBUF more than once. vkResetCommandBuffer() won't work
        inline constexpr VkCommandPoolCreateFlags RecordBuffer_MoreThanOnce = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;         // vkResetCommandBuffer() will  work
        inline constexpr VkCommandPoolCreateFlags TRANSIENT = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
        inline constexpr VkCommandPoolCreateFlags PROTECTED = VK_COMMAND_POOL_CREATE_PROTECTED_BIT;
    };
    typedef VkCommandPoolCreateFlags CommandPoolCreateFlags;
};