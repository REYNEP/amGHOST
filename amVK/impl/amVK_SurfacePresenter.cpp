#include "amVK_SurfacePresenter.hh"

#include "amVK_SwapChain.hh"
amVK_SwapChain* amVK_SurfacePresenter::create_SwapChain_interface(void) {
            this->isBound_Device();
            this->isBound_Surface();
            this->SC = new amVK_SwapChain(this->S, this->D);
    return  this->SC;
}

#include "amVK_RenderPass.hh"
amVK_RenderPass* amVK_SurfacePresenter::create_RenderPass_interface(void) {
            this->isBound_Device();
            this->isBound_Surface();
            this->RP = new amVK_RenderPass(this->D);
    return  this->RP;
}

#include "amVK_CommandBuffer.hh"
amVK_CommandPool* amVK_SurfacePresenter::create_CommandPool_interface(void) {
            this->isBound_Device();
            this->isBound_Surface();
            this->CP = new amVK_CommandPool(this->D, this->D->amVK_1D_QCIs.ptr_Default()->queueFamilyIndex);
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

#include "amVK_RenderPassCMDs.hh"
amVK_RenderPassCMDs* amVK_SurfacePresenter::create_RenderPassCMDs_interface(void) {
            this->isBound_Device();
            this->isBound_Surface();
            this->RPC = new amVK_RenderPassCMDs(this->FBs, this->active_CMDBUF());
    return  this->RPC;
}

void amVK_SurfacePresenter::destroy_everything_serially(void) {
    this->FBs->DestroyFrameBuffers();
    this->IMGs->DestroySwapChainImageViews();
    this->SC->DestroySwapChain();
    this->CP->FreeCommandBuffers();
    this->RP->DestroyRenderPass();
    this->IMGs->AcquireNextImage_SemaPhore_Destroy();
    this->RenderingFinished_SemaPhore_Destroy();
    this->CP->DestroyCommandPool();
    this->D->DestroyDevice();
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
    // Ending the render pass will add an implicit barrier, transitioning the frame buffer color attachment to
    // `VK_IMAGE_LAYOUT_PRESENT_SRC_KHR` for presenting it to the windowing system
void  amVK_SurfacePresenter::EndCommandBuffer(void) {
    VkResult return_code = vkEndCommandBuffer(this->active_CMDBUF());
    amVK_return_code_log( "vkEndCommandBuffer()" );
}





static VkSemaphoreCreateInfo g_SP_CI = {
    .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
    .pNext = nullptr,
    .flags = 0
};
void  amVK_SurfacePresenter::RenderingFinished_SemaPhore_Create(void) {
    VkResult return_code = vkCreateSemaphore(this->SC->D->vk_Device, &g_SP_CI, nullptr, &this->RenderingFinished_SemaPhore);
    amVK_return_code_log( "vkCreateSemaphore()" );     // above variable "return_code" can't be named smth else
}
void amVK_SurfacePresenter::RenderingFinished_SemaPhore_Destroy(void) {
    vkDestroySemaphore(this->D->vk_Device, this->RenderingFinished_SemaPhore, nullptr);
}
static VkPipelineStageFlags g_WaitStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
static VkSubmitInfo g_SI = {
    .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
    .pNext = nullptr,
    .waitSemaphoreCount = 0,
    .pWaitSemaphores    = nullptr,

    .pWaitDstStageMask = &g_WaitStageMask,

    .commandBufferCount     = 0,
    .pCommandBuffers        = nullptr,
    .signalSemaphoreCount   = 0,
    .pSignalSemaphores      = nullptr
};
void amVK_SurfacePresenter::submit_CMDBUF(void) {
    if (RenderingFinished_SemaPhore == nullptr) {
        RenderingFinished_SemaPhore_Create();
    }

    VkSemaphore ImageAvailableSemaphore = this->IMGs->AcquireNextImage_SemaPhore;
    VkSemaphore RenderingFinishedSemaphore = this->RenderingFinished_SemaPhore;
    VkCommandBuffer ActiveCommandBuffer = this->active_CMDBUF();

        g_SI.waitSemaphoreCount     = 1;
        g_SI.pWaitSemaphores        = &ImageAvailableSemaphore;
        g_SI.signalSemaphoreCount   = 1;
        g_SI.pSignalSemaphores      = &RenderingFinishedSemaphore;
        g_SI.commandBufferCount     = 1;
        g_SI.pCommandBuffers        = &ActiveCommandBuffer;
            // I don't think VULKAN Objects are literal objects....
            // I think, VkSemaphore is rather just an ID or smth

    VkResult return_code = vkQueueSubmit(this->D->get_default_queue(), 1, &g_SI, VK_NULL_HANDLE);
    amVK_return_code_log( "vkQueueSubmit()" );
}




static VkPresentInfoKHR g_PI = {
    .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
    .pNext = nullptr,
    .waitSemaphoreCount = 0,
    .pWaitSemaphores = nullptr,
    .swapchainCount = 0,
    .pSwapchains = nullptr,
    .pImageIndices = nullptr,
    .pResults = nullptr
};
void amVK_SurfacePresenter::Present(void) {
    VkSemaphore RenderingFinishedSemaphore = this->RenderingFinished_SemaPhore;

        g_PI.waitSemaphoreCount = 1;
        g_PI.pWaitSemaphores = &RenderingFinishedSemaphore;
        g_PI.swapchainCount = 1;
        g_PI.pSwapchains = &this->SC->vk_SwapChainKHR;
        g_PI.pImageIndices = &this->IMGs->NextImageIndex_Acquired;

        VkResult return_code = vkQueuePresentKHR(
            this->D->get_default_queue(),
            &g_PI
        );
        
        if (return_code == VK_ERROR_OUT_OF_DATE_KHR) {
            REY_LOG_EX(" [ VK_ERROR_OUT_OF_DATE_KHR ] ----> WIP:- WindowResize()");
        }
        else if (return_code == VK_SUBOPTIMAL_KHR) {
            REY_LOG_EX(" [ VK_SUBOPTIMAL_KHR ] ----> WIP:- Figure out what to do");
        }
        else {
            amVK_return_code_log( "vkQueuePresentKHR()" ); // above variable "return_code" can't be named smth else
        }
}