#pragma once
#include "amVK/common/amVK.hh"
#include "amVK/common/amVK_log.hh"

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
    void sync_Attachments(void) {
        CI.attachmentCount = AttachmentInfos.neXt;
        CI.pAttachments = AttachmentInfos.data;
    }
    void sync_Subpasses(void) {
        CI.subpassCount = SubpassInfos.neXt;
        CI.pSubpasses = SubpassInfos.data;
    }
    void sync_Dependencies(void) {
        CI.dependencyCount = Dependencies.neXt;
        CI.pDependencies = Dependencies.data;
    }
    void sync_Attachments_Subpasses_Dependencies(void) {
         sync_Attachments();
         sync_Subpasses();
         sync_Dependencies();
    }
    void sync_Elements(void) {
         sync_Attachments_Subpasses_Dependencies();
    }

  public:
    amVK_RenderPass() {}
   ~amVK_RenderPass() {}

  public:
    VkDevice used_vk_Device     = nullptr;
    VkRenderPass  vk_RenderPass = nullptr;

  public:
    void CreateRenderPass(VkDevice vk_Device) {
        this->used_vk_Device = vk_Device;
        VkResult return_code = vkCreateRenderPass(vk_Device, &CI, nullptr, &this->vk_RenderPass);
        amVK_return_code_log( "vkCreateRenderPass()" );     // above variable "return_code" can't be named smth else
    }
};