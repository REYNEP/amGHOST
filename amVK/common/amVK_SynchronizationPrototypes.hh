#pragma once
#include <vulkan/vulkan.h>














namespace amVK_Sync_prototype0 {
    namespace CommandPoolCreateFlagBits
    {
        inline constexpr VkCommandPoolCreateFlags RecordBuffer_Once         = 0;    // You can't BEGIN/RECORD same CMDBUF more than once. vkResetCommandBuffer() won't work
        inline constexpr VkCommandPoolCreateFlags RecordBuffer_MoreThanOnce = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;         // vkResetCommandBuffer() will  work
        inline constexpr VkCommandPoolCreateFlags TRANSIENT                 = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
        inline constexpr VkCommandPoolCreateFlags PROTECTED                 = VK_COMMAND_POOL_CREATE_PROTECTED_BIT;
    };
    typedef VkCommandPoolCreateFlags CommandPoolCreateFlags;
};














namespace amVK_Sync_prototype1
{
    enum class CommandBufferBeginFlags : VkCommandBufferUsageFlags
    {
        Submit_MoreThanOnce  = 0,
        Submit_Once          = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
        RENDER_PASS_CONTINUE = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT,
        SIMULTANEOUS_USE     = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT
    };

    // Free-standing implicit conversion operator
    inline VkCommandBufferUsageFlags operator+(CommandBufferBeginFlags flag) {
        return static_cast<VkCommandBufferUsageFlags>(flag);
    }
}















namespace amVK_Sync_prototype2 {
    namespace CommandPoolCreateFlags {
        enum BITS : VkCommandPoolCreateFlags {
                RecordBuffer_Once         = 0,
                RecordBuffer_MoreThanOnce = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
                TRANSIENT                 = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT,
                PROTECTED                 = VK_COMMAND_POOL_CREATE_PROTECTED_BIT,
        };
    };
    namespace CommandBufferBeginFlags {
        enum BITS : VkCommandPoolCreateFlags {
                Submit_MoreThanOnce  = 0,
                Submit_Once          = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
                RENDER_PASS_CONTINUE = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT,
                SIMULTANEOUS_USE     = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT,
        };
    }
    namespace CommandBufferUsageFlags = CommandBufferBeginFlags;
};