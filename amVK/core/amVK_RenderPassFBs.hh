#pragma once
#include "amVK_SwapChainIMGs.hh"
#include "amVK_RenderPass.hh"

/**
 * amVK_RenderPass::FrameBuffers <-- SwapChain + RenderPass
 */
class amVK_RenderPassFBs {
  public:
    VkFramebufferCreateInfo CI = {
        .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
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
        this->CI.renderPass = RP->vk_RenderPass;
        this->RPBI.renderPass = RP->vk_RenderPass;
    }
   ~amVK_RenderPassFBs() {}

  public:
    void CreateFrameBuffers(void);
    void DestroyFrameBuffers(void);

  public:
    void RPBI_AcquireNextFrameBuffer(void);
    void CMDBeginRenderPass(VkCommandBuffer CMDBUF);
    void CMDEndRenderPass(VkCommandBuffer CMDBUF);
    void CMDSetViewport_n_Scissor(VkCommandBuffer CMDBUF);

  public:
    VkClearValue clearValue = {
        .color = {0.0f, 0.2f, 0.4f, 1.0f}
    };
    VkRenderPassBeginInfo RPBI = {
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
    VkViewport Viewport = {
        .x = (float)0,
        .y = (float)0,
        .width = (float)0,
        .height = (float)0,
        .minDepth = (float)0.0f,
        .maxDepth = (float)1.0f,
    };
    VkRect2D Scissor = {
        .offset = {0, 0},
        .extent = {}
    };
};