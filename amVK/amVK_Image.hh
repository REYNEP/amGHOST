#pragma once
#include "amVK.hh"
#include "amVK_Device.hh"

class amVK_Image {
  public:
    VkImageViewCreateInfo ViewCI = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .image = this->vk_Image,
        .viewType = VK_IMAGE_VIEW_TYPE_2D,
        .format = VK_FORMAT_UNDEFINED,
        .components = {},
        .subresourceRange = {}
    };

  public:
    amVK_Image(void) {}
    amVK_Image(amVK_Device *paramD) {
        D = paramD;
    }

  public:
    amVK_Device *D = nullptr;
    VkImage vk_Image = nullptr;
    VkImageView vk_ImageView = nullptr;

  public:
    void createImageView(void) {
        VkResult return_code = vkCreateImageView(this->D->vk_Device, &ViewCI, nullptr, &this->vk_ImageView);
        amVK_return_code_log( "vkCreateImageView()" );     // above variable "return_code" can't be named smth else
    }
};