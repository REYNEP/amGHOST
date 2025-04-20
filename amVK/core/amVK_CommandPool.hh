#pragma once
#include "amVK/common/amVK.hh"

/**
 * As per QueueFamily
 */
class amVK_CommandPool {
  public:
    VkCommandPoolCreateInfo CI = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0,
        .queueFamilyIndex = 0
    };

  public:
    // TODO: Bind CommandPool as per QCI into a Different TopLevel STRUCTURE/Class
    amVK_CommandPool(amVK_Device *D, uint32_t queueFamilyIndex) : D(D) {
        this->CI.queueFamilyIndex = queueFamilyIndex;
    }

  public:
    amVK_Device *D;
    VkCommandPool vk_CommandPool = nullptr;

  public:
    void CreateCommandPool(void) {
        VkResult return_code = vkCreateCommandPool(this->D->vk_Device, &this->CI, nullptr, &this->vk_CommandPool);
        amVK_return_code_log( "vkCreateCommandPool()" );    // above variable "return_code" can't be named smth else
    }
    void DestroyCommandPool(void) {
        vkDestroyCommandPool(this->D->vk_Device, vk_CommandPool, nullptr);
    }






  public:
    VkCommandBufferAllocateInfo AI = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,

        .commandPool = nullptr,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = 1
    };

  public:
    REY_Array<VkCommandBuffer>      vk_CommandBuffers;
    REY_Array<VkCommandBuffer> AllocateCommandBuffers(void) 
    {
        this->AI.commandPool = this->vk_CommandPool;
        this->vk_CommandBuffers.reserve(this->AI.commandBufferCount); 

            VkResult return_code = vkAllocateCommandBuffers(this->D->vk_Device, &this->AI, this->vk_CommandBuffers.data);
            amVK_return_code_log( "vkAllocateCommandBuffers()" );

        return vk_CommandBuffers;
    }

    void  FreeCommandBuffers(void) {
        vkFreeCommandBuffers(this->D->vk_Device, vk_CommandPool, vk_CommandBuffers.n, vk_CommandBuffers.data);
    }

  public:
    uint32_t                   active_CMDBUF_Index = 0;
    void                   set_active_CMDBUF_Index(uint32_t I) {active_CMDBUF_Index = I;}
    inline VkCommandBuffer get_active_CMDBUF(void) {return this->vk_CommandBuffers[this->active_CMDBUF_Index];}
};