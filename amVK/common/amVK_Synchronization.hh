#pragma once
#include <vulkan/vulkan.h>

/*
              __      ___  __          _____                  
              \ \    / / |/ /         / ____|                 
   __ _ _ __ __\ \  / /| ' /         | (___  _   _ _ __   ___ 
  / _` | '_ ` _ \ \/ / |  <           \___ \| | | | '_ \ / __|
 | (_| | | | | | \  /  | . \          ____) | |_| | | | | (__ 
  \__,_|_| |_| |_|\/   |_|\_\        |_____/ \__, |_| |_|\___|
                          ______ ______       __/ |           
                         |______|______|     |___/            
Why is this the best option so far?
    1) intelliSense suggestions made better! 
        - amVK_Sync::
        - amVK_Sync::CommandPoolCreateFlags::
        - amVK_Sync::CommandPoolCreateFlags::<chose a bit from one of the options>
        -   Options would be @ amVK_Sync::<here> 💁‍♀️
    
    2) Works as a Type
        - CreateCommandPool(amVK_Sync::CommandPoolCreateFlags::BITS flags);

    3) The implicit Conversion     static_cast<>     is not implicit anymore 💁‍♀️ 
        - anybody who is gonna come here to check the list of possible Flags, is gonna see how it's getting cast

*/
namespace amVK_Sync
{
    struct  CommandPoolCreateFlags {
            CommandPoolCreateFlags (VkCommandPoolCreateFlags flags) : _value_(flags) {}
                inline operator     VkCommandPoolCreateFlags() const {return _value_;}        // static_cast<> Operator
                                    VkCommandPoolCreateFlags _value_;
                static inline       VkCommandPoolCreateFlags RecordBuffer_Once         = 0;
                static inline       VkCommandPoolCreateFlags RecordBuffer_MoreThanOnce = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
                static inline       VkCommandPoolCreateFlags TRANSIENT                 = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
                static inline       VkCommandPoolCreateFlags PROTECTED                 = VK_COMMAND_POOL_CREATE_PROTECTED_BIT;
    };

    struct  CommandBufferBeginFlags {
            CommandBufferBeginFlags(VkCommandBufferUsageFlags flags) : _value_(flags) {}
                    inline operator VkCommandBufferUsageFlags() const {return _value_;}       // static_cast<> Operator
                                    VkCommandBufferUsageFlags _value_;
                    static inline   VkCommandBufferUsageFlags Submit_MoreThanOnce  = 0;
                    static inline   VkCommandBufferUsageFlags Submit_Once          = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
                    static inline   VkCommandBufferUsageFlags RENDER_PASS_CONTINUE = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
                    static inline   VkCommandBufferUsageFlags SIMULTANEOUS_USE     = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
    };
    typedef CommandBufferBeginFlags CommandBufferUsageFlags;
};