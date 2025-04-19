#pragma once
#include <vulkan/vulkan.h>

class amVK_FrameBuffer  {
  public:
    VkFramebufferCreateInfo CI = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0,

        .renderPass = nullptr,

        .attachmentCount = 0,
        .pAttachments = nullptr,
            // Actual ImageView Attachments

        .width = 0,
        .height = 0,
        .layers = 1,
    };

  public:
    amVK_FrameBuffer(void) {}
    amVK_FrameBuffer(VkRenderPass vk_RenderPass) {
        this->CI.renderPass = vk_RenderPass;
    }

  public:
    VkDevice used_vk_Device      = nullptr;
    VkFramebuffer vk_FrameBuffer = nullptr;

  public:
    void CreateFrameBuffer(VkDevice vk_Device) {
        this->used_vk_Device = vk_Device;
        VkResult return_code = vkCreateFramebuffer(vk_Device, &CI, nullptr, &this->vk_FrameBuffer);
        amVK_return_code_log( "vkCreateFramebuffer()" );     // above variable "return_code" can't be named smth else
    }
};