#pragma once
#include <vulkan/vulkan.h>

class amVK_CommandBufferPrimary {
  public:
    amVK_CommandBufferPrimary(VkCommandBuffer vk_CommandBuffer) {
        this->vk_CommandBuffer = vk_CommandBuffer;
    }

  public:
    VkCommandBuffer vk_CommandBuffer = nullptr;

  public:
    VkCommandBufferBeginInfo BI = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .pNext = nullptr,
        .flags = 0,
        .pInheritanceInfo = nullptr
    };

    VkCommandBuffer BeginCommandBuffer(amVK_Sync::CommandBufferBeginFlags flags);
    void              EndCommandBuffer(void);
};