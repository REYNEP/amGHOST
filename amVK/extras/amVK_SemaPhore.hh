#pragma once
#include <vulkan/vulkan.h>

class amVK_Semaphore {
  public:
    VkSemaphoreCreateInfo CI = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0,
    };

  public:
    amVK_Semaphore() {}
   ~amVK_Semaphore() {}

  public:
    VkDevice used_vk_Device    = nullptr;
    VkSemaphore   vk_Semaphore = nullptr;

  public:
    void CreateSemaphore(VkDevice vk_Device) {
        this->used_vk_Device = vk_Device;
        VkResult return_code = vkCreateSemaphore(vk_Device, &CI, nullptr, &this->vk_Semaphore);
        amVK_return_code_log( "vkCreateSemaphore()" );     // above variable "return_code" can't be named smth else
    }
};