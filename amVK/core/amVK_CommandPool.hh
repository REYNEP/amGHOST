#pragma once
#include "amVK/common/amVK.hh"
#include "amVK/utils/amVK_log.hh"
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

    void  CreateCommandPool( amVK_Sync::CommandPoolCreateFlags flags);
    void DestroyCommandPool(void);



  public:
    VkCommandBufferAllocateInfo AI = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .pNext = nullptr,

        .commandPool = nullptr,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = 1
    };

    REY_Array<VkCommandBuffer>      vk_CommandBuffers;
    REY_Array<VkCommandBuffer> AllocateCommandBuffers(void);
    void                           FreeCommandBuffers(void);



  public:
    uint32_t                   active_CMDBUF_Index = 0;
    void                   set_active_CMDBUF_Index(uint32_t I) {active_CMDBUF_Index = I;}
    inline VkCommandBuffer get_active_CMDBUF(void) {return this->vk_CommandBuffers[this->active_CMDBUF_Index];}

    static inline VkCommandBufferBeginInfo g_CMDBUF_BI = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .pNext = 0,
        .flags = 0,
        .pInheritanceInfo = nullptr
    };
    VkCommandBuffer BeginCommandBuffer(void);
    void              EndCommandBuffer(void);
};