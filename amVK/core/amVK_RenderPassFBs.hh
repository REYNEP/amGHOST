#pragma once
#include "amVK_SwapChainIMGs.hh"
#include "amVK_RenderPass.hh"

/**
 * amVK_RenderPass::FrameBuffers <-- SwapChain + RenderPass
 */
class amVK_RenderPassFBs {
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
    amVK_RenderPass*         RP = nullptr;
    amVK_SwapChainIMGs* SC_IMGs = nullptr;

    REY_Array<VkFramebuffer> amVK_1D_RP_FBs;

    amVK_RenderPassFBs(amVK_SwapChainIMGs *SC_IMGs, amVK_RenderPass* RP) {
        this->SC_IMGs = SC_IMGs; 
        this->RP = RP;
    }
   ~amVK_RenderPassFBs() {}

  public:
    void CreateFrameBuffers(void);
    void DestroyFrameBuffers(void);
    inline   VkFramebuffer        get(uint32_t index) { return amVK_1D_RP_FBs[index]; }
};