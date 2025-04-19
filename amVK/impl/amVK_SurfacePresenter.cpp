#include "amVK_SurfacePresenter.hh"

#include "amVK_SwapChain.hh"
amVK_SwapChain* amVK_SurfacePresenter::create_SwapChain_interface(void) {
            this->isBound_Device();
            this->isBound_Surface();
            this->SC = new amVK_SwapChain(this->S->vk_SurfaceKHR);
    return  this->SC;
}

#include "amVK_RenderPass.hh"
amVK_RenderPass* amVK_SurfacePresenter::create_RenderPass_interface(void) {
            this->isBound_Device();
            this->isBound_Surface();
            this->RP = new amVK_RenderPass();
    return  this->RP;
}

#include "amVK_CommandBuffer.hh"
amVK_CommandPool* amVK_SurfacePresenter::create_CommandPool_interface(void) {
            this->isBound_Device();
            this->isBound_Surface();
            this->CP = new amVK_CommandPool(this->D->amVK_1D_QCIs.ptr_Default()->queueFamilyIndex);
    return  this->CP;
}

#include "amVK_SwapChainIMGs.hh"
amVK_SwapChainIMGs* amVK_SurfacePresenter::create_SwapChainImages_interface(void) {
            this->isBound_Device();
            this->isBound_Surface();
            this->IMGs = new amVK_SwapChainIMGs(this->SC);
    return  this->IMGs;
}

#include "amVK_RenderPassFBs.hh"
amVK_RenderPassFBs* amVK_SurfacePresenter::create_FrameBuffers_interface(void) {
            this->isBound_Device();
            this->isBound_Surface();
            this->FBs = new amVK_RenderPassFBs(this->IMGs, this->RP);
    return  this->FBs;
}






















static VkCommandBufferBeginInfo g_CMDBUF_BI = {
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
    .pNext = 0,
    .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
    .pInheritanceInfo = nullptr
};
void  amVK_SurfacePresenter::BeginCommandBuffer(void) {
    VkResult return_code = vkBeginCommandBuffer(this->active_CMDBUF(), &g_CMDBUF_BI);
    amVK_return_code_log( "vkBeginCommandBuffer()" );
}

static VkClearValue g_ClearValue = {
    .color = {0.0f, 0.2f, 0.4f, 1.0f}
};
static VkRenderPassBeginInfo g_BI = {
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
void amVK_SurfacePresenter::RPBI_ReadyUp(void) {
    g_BI.renderPass         = this->RP->vk_RenderPass;
    g_BI.framebuffer        = this->FBs->AcquireNextFrameBuffer();
    g_BI.renderArea.extent  = this->synced_ImageExtent();
}
void amVK_SurfacePresenter::BeginRenderPass(void) {
             vkCmdBeginRenderPass(this->active_CMDBUF(), &g_BI, VK_SUBPASS_CONTENTS_INLINE);
    REY_LOG("vkCmdBeginRenderPass()");
}