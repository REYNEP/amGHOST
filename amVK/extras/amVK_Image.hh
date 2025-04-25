#pragma once
#include <vulkan/vulkan.h>
#include "amVK/utils/amVK_log.hh"

class amVK_Image {
  public:
    VkImageViewCreateInfo ViewCI = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .image = nullptr,
        .viewType = VK_IMAGE_VIEW_TYPE_2D,
        .format = VK_FORMAT_UNDEFINED,
        .components = {},
        .subresourceRange = {}
    };

  public:
    amVK_Image(void) {}
    amVK_Image(  VkDevice vk_Device) {
        this->vk_Device = vk_Device;
    }
   ~amVK_Image(void) {}

  public:
    VkDevice      vk_Device    = nullptr;
    VkImage       vk_Image     = nullptr;
    VkImageView   vk_ImageView = nullptr;

  public:
    void CreateImageView(VkDevice vk_Device) {
        VkResult return_code = vkCreateImageView(vk_Device, &ViewCI, nullptr, &this->vk_ImageView);
        amVK_return_code_log( "vkCreateImageView()" );     // above variable "return_code" can't be named smth else
    }
};