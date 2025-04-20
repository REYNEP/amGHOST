#pragma once
#include "amVK/common/amVK.hh"
#include "amVK/common/amVK_log.hh"
#include "amVK_Device.hh"

class amVK_RenderPass  {
  public:
    VkRenderPassCreateInfo CI = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0,
        .attachmentCount = 0,
        .pAttachments = nullptr,
            // AttachMent Descriptors, not actual, ImageView Attachments [that'd be in FrameBufferCI]
        .subpassCount = 0,
        .pSubpasses = nullptr,
        .dependencyCount = 0,
        .pDependencies = nullptr
    };

    REY_ArrayDYN<VkAttachmentDescription> AttachmentInfos;
    REY_ArrayDYN<VkSubpassDescription> SubpassInfos;
    REY_ArrayDYN<VkSubpassDependency> Dependencies;
    void sync_Attachments(void);
    void sync_Subpasses(void);
    void sync_Dependencies(void);
    void sync_Attachments_Subpasses_Dependencies(void);
    void sync_Elements(void) { sync_Attachments_Subpasses_Dependencies(); }

  public:
    amVK_RenderPass(amVK_Device *D) : D(D) {}
   ~amVK_RenderPass() {}

    amVK_Device *D;
    VkRenderPass vk_RenderPass = nullptr;

    void CreateRenderPass(void) {
        VkResult return_code = vkCreateRenderPass(this->D->vk_Device, &CI, nullptr, &this->vk_RenderPass);
        amVK_return_code_log( "vkCreateRenderPass()" );     // above variable "return_code" can't be named smth else
    }
};