#pragma once
#include "amVK_Instance.hh"
#include "amVK_Device.hh"
#include "amVK_Surface.hh"

class amVK_CommandPool {
  public:
    VkCommandPoolCreateInfo CI = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0,
        .queueFamilyIndex = 0
    };

  public:
    amVK_CommandPool(amVK_SurfacePresenter *paramPR) {
        this->PR = paramPR;
        this->CI.queueFamilyIndex = this->PR->D->QCI.Default.queueFamilyIndex;
    }

  public:
    amVK_SurfacePresenter *PR = nullptr;               // Basically, Parent Pointer
    VkCommandPool vk_CommandPool = nullptr;

  public:
    void CreateCommandPool(void) {
        VkResult return_code = vkCreateCommandPool(this->PR->D->vk_Device, &CI, nullptr, &this->vk_CommandPool);
        amVK_return_code_log( "vkCreateCommandPool()" );     // above variable "return_code" can't be named smth else
    }
};






class amVK_CommandBuffer {
  public:
    VkCommandBufferAllocateInfo CI = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,

        .commandPool = nullptr,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = 1
    };

  public:
    amVK_CommandBuffer(amVK_SurfacePresenter *paramPR) {
        this->PR = paramPR;
        this->CI.commandPool = this->PR->CP->vk_CommandPool;
    }

  public:
    amVK_SurfacePresenter *PR = nullptr;       // Basically, Parent Pointer
    VkCommandBuffer vk_CommandBuffer = nullptr;

  public:
    void AllocateCommandBuffer(void) {
        VkResult return_code = vkAllocateCommandBuffers(this->PR->D->vk_Device, &CI, &this->vk_CommandBuffer);
        amVK_return_code_log( "vkAllocateCommandBuffers()" );     // above variable "return_code" can't be named smth else
    }
};