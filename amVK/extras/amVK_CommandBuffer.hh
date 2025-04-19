#pragma once
#include "amVK_CommandPool.hh"

class amVK_CommandBuffer {
  public:
    VkCommandBufferBeginInfo BI = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .pNext = 0,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
        .pInheritanceInfo = nullptr
    };

  public:
    amVK_CommandBuffer(VkCommandBuffer vk_CommandBuffer) {
        this->vk_CommandBuffer = vk_CommandBuffer;
    }

  public:
    VkCommandBuffer vk_CommandBuffer = nullptr;
};