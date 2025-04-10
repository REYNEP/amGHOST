#pragma once

#pragma once
#include "amVK.hh"
#include "amVK_Device.hh"
#include "amVK_Surface.hh"

class amVK_FrameBuffer  {
  public:
    VkFramebufferCreateInfo CI = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0,

        .renderPass = nullptr,

        .attachmentCount = 0,
        .pAttachments = nullptr,

        .width = 0,
        .height = 0,
        .layers = 0,
    };

  public:
    amVK_FrameBuffer(amVK_Presenter *paramPR) {
        this->PR = paramPR;
    }

  public:
    amVK_Presenter *PR = nullptr;       // Basically, Parent Pointer
    VkFramebuffer vk_FrameBuffer = nullptr;

  public:
    void CreateFrameBuffer(void) {
        VkResult return_code = vkCreateFramebuffer(this->PR->D->vk_Device, &CI, nullptr, &this->vk_FrameBuffer);
        amVK_return_code_log( "vkCreateFramebuffer()" );     // above variable "return_code" can't be named smth else
    }
};



    // amVK_Surface.cpp
#include "amVK_FrameBuffer.hh"
amVK_FrameBuffer* amVK_Presenter::create_FrameBuffer(void) {
    this->FB = new amVK_FrameBuffer(this);
    return this->FB;
}