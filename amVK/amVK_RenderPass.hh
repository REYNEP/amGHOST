#pragma once
#include "amVK_Instance.hh"
#include "amVK_Device.hh"
#include "amVK_Surface.hh"
#include "intern/amVK_log.hh"

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
    amVK_RenderPass(amVK_SurfacePresenter *PR) {
        this->PR = PR;
    }

  public:
    amVK_SurfacePresenter *PR = nullptr;       // Basically, Parent Pointer
    VkRenderPass vk_RenderPass = nullptr;

  public:
    void CreateRenderPass(void) {
        VkResult return_code = vkCreateRenderPass(this->PR->D->vk_Device, &CI, nullptr, &this->vk_RenderPass);
        amVK_return_code_log( "vkCreateRenderPass()" );     // above variable "return_code" can't be named smth else
    }

  public:
    VkRenderPassBeginInfo BI = {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        .pNext = nullptr,
        .renderPass = nullptr,
        .framebuffer = nullptr,
        .renderArea = {
            .offset = {0, 0},
            .extent = {100, 100}
        },
        .clearValueCount = 1,
        .pClearValues = &clearValue
    };

    VkClearValue clearValue = {
        .color = {0.0f, 0.2f, 0.4f, 1.0f}
    };

    /**
     * @param FB_Index --> USE: `amVK_SwapChain::AcquireNextImage()`
     */
    void BI_ReadyUp(uint32_t FB_Index) {
        this->BI.renderPass = this->vk_RenderPass;
        //this->BI.framebuffer = this->PR->acquire_FB(FB_Index);
    }
};