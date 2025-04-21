#pragma once
#include "amVK_Instance.hh"
#include "amVK_Device.hh"

class amVK_Image {
  public:
    VkImageViewCreateInfo ViewCI = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0
    };

  public:
    amVK_Image(void) {}
    amVK_Image(amVK_Device *paramD) {
        D = paramD;
    }

  public:
    amVK_Device *D = nullptr;
    VkImage IMG = nullptr;
    VkImageView IMGV = nullptr;

  public:
    void createImageView(void) {
        VkResult return_code = vkCreateImageView(this->D->m_device, &ViewCI, nullptr, &this->IMGV);
        amVK_return_code_log( "vkCreateImageView()" );     // above variable "return_code" can't be named smth else
    }
};