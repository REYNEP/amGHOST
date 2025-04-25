#pragma once
#include "amVK_Device.hh"
#include "amVK/common/amVK_Synchronization.hh"

class amVK_CommandPool {
  public:
    amVK_CommandPool(amVK_Device *D, uint32_t QFamID) {this->D = D; CI.queueFamilyIndex = QFamID;}
   ~amVK_CommandPool() {}

    amVK_Device *D = nullptr;
    VkCommandPool vk_CommandPool = nullptr;

  public:
    VkCommandPoolCreateInfo CI = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .queueFamilyIndex = 0
    };

    void  CreateCommandPool(amVK_Sync::CommandPoolCreateFlags flags);
    void DestroyCommandPool(void);
};