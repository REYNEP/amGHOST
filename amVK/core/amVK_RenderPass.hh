#pragma once
#include "amVK/common/amVK.hh"
#include "amVK/utils/amVK_log.hh"
#include "amVK_Device.hh"

class amVK_RenderPass  {
  public:
    VkRenderPassCreateInfo CI = {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
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
    amVK_RenderPass(amVK_Device *D) {this->D = D;}
   ~amVK_RenderPass() {}

    amVK_Device *D = nullptr;
    VkRenderPass vk_RenderPass = nullptr;

    void CreateRenderPass(void);
    void DestroyRenderPass(void);
};