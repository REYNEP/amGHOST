#include "amVK_RenderPass.hh"

void amVK_RenderPass::sync_Attachments(void) {
    CI.attachmentCount = AttachmentInfos.neXt;
    CI.pAttachments = AttachmentInfos.data;
}
void amVK_RenderPass::sync_Subpasses(void) {
    CI.subpassCount = SubpassInfos.neXt;
    CI.pSubpasses = SubpassInfos.data;
}
void amVK_RenderPass::sync_Dependencies(void) {
    CI.dependencyCount = Dependencies.neXt;
    CI.pDependencies = Dependencies.data;
}
void amVK_RenderPass::sync_Attachments_Subpasses_Dependencies(void) {
        sync_Attachments();
        sync_Subpasses();
        sync_Dependencies();
}












#include "amVK_RenderPassFBs.hh"

void amVK_RenderPassFBs::CreateFrameBuffers(void) {
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

            VkResult return_code = vkCreateFramebuffer(this->RP->D->vk_Device, &CI, nullptr, &this->amVK_1D_RP_FBs[k]);
            amVK_return_code_log( "vkCreateFramebuffer()" );     // above variable "return_code" can't be named smth else
    }
}
void amVK_RenderPassFBs::DestroyFrameBuffers(void) {
    REY_Array_LOOP(this->amVK_1D_RP_FBs, k) {
        vkDestroyFramebuffer(this->RP->D->vk_Device, this->amVK_1D_RP_FBs[k], nullptr);
    }
}













#include "amVK_RenderPassCMDs.hh"

static VkClearValue g_ClearValue = {
    .color = {0.0f, 0.2f, 0.4f, 1.0f}
};
static VkRenderPassBeginInfo g_RPBI = {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
    .pNext = nullptr,
    .renderPass = nullptr,
    .framebuffer = nullptr,
    .renderArea = {
        .offset = {0, 0},
        .extent = {100, 100}
    },
    .clearValueCount = 1,
    .pClearValues = &g_ClearValue
};
void amVK_RenderPassCMDs::RPBI_AcquireNextFrameBuffer(void) {
    uint32_t nextImageIndex = this->SC_IMGs->AcquireNextImage();
      g_RPBI.framebuffer    = this->RP_FBs->get(nextImageIndex);
}
/** WELL, If SurfCaps have changed, SwapChainImages/ImageViews/FrameBuffers, all would have to be ReCreated 💁‍♀️ */
void amVK_RenderPassCMDs::RPBI_SyncSurfCaps(void) {
    this->SC->sync_SurfCaps();
    g_RPBI.renderArea.extent = this->SC->active_ImageExtent();
}






void amVK_RenderPassCMDs::CMDBeginRenderPass(void) {
    g_RPBI.renderPass        = this->RP->vk_RenderPass;
    g_RPBI.renderArea.extent = this->SC->active_ImageExtent();
    
                        vkCmdBeginRenderPass(this->CMDBUF, &g_RPBI, VK_SUBPASS_CONTENTS_INLINE);
               REY_LOG("vkCmdBeginRenderPass()");
}
void amVK_RenderPassCMDs::CMDEndRenderPass(void) {
                        vkCmdEndRenderPass(this->CMDBUF);
               REY_LOG("vkCmdEndRenderPass()");
}






static VkViewport g_Viewport = {
    .x = (float)0,
    .y = (float)0,
    .width = (float)0,
    .height = (float)0,
    .minDepth = (float)0.0f,
    .maxDepth = (float)1.0f,
};
static VkRect2D g_Scissor = {
    .offset = {0, 0},
    .extent = {}
};
void amVK_RenderPassCMDs::CMDSetViewport_n_Scissor(void) {
    g_Scissor.extent  = g_RPBI.renderArea.extent;
    g_Viewport.width  = g_Scissor.extent.width;
    g_Viewport.height = g_Scissor.extent.height;

                vkCmdSetViewport(CMDBUF, 0, 1, &g_Viewport);
    REY_LOG("vkCmdSetViewport()");
                vkCmdSetScissor(CMDBUF, 0, 1, &g_Scissor);
    REY_LOG("vkCmdSetScissor()");
}