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
    amVK_RenderPass*           RP = nullptr;
    amVK_SwapChainIMGs* SC_IMGs = nullptr;

    REY_Array<VkFramebuffer> amVK_1D_RP_FBs;

    amVK_RenderPassFBs(amVK_SwapChainIMGs *SC_IMGs, amVK_RenderPass* RP) {
        this->SC_IMGs = SC_IMGs; 
        this->RP = RP;
    }
   ~amVK_RenderPassFBs() {}

  public:
    void CreateFrameBuffers(void) {
        if (this->SC_IMGs->called_GetSwapChainImagesKHR == false) {
            this->SC_IMGs->GetSwapChainImagesKHR();
        }
        if (this->SC_IMGs->called_CreateSwapChainImageViews == false) {
            this->SC_IMGs->CreateSwapChainImageViews();
        }

        VkExtent2D imageExtent = this->SC_IMGs->active_ImageExtent();
            this->CI.width  = imageExtent.width;
            this->CI.height = imageExtent.height;

        this->amVK_1D_RP_FBs.reserve(this->SC_IMGs->amVK_1D_SC_IMGs.n);

        REY_Array_LOOP(this->amVK_1D_RP_FBs, k) {
            this->CI.attachmentCount = 1;
            this->CI.pAttachments = &(this->SC_IMGs->amVK_1D_SC_IMGViews[k]);

                VkResult return_code = vkCreateFramebuffer(this->RP->used_vk_Device, &CI, nullptr, &this->amVK_1D_RP_FBs[k]);
                amVK_return_code_log( "vkCreateFramebuffer()" );     // above variable "return_code" can't be named smth else
        }
    }

  public:
    VkFramebuffer      AcquireNextFrameBuffer(void) {
        this->SC_IMGs->AcquireNextImage();
        return this->amVK_1D_RP_FBs[this->SC_IMGs->NextImageIndex_Acquired];
    }
};