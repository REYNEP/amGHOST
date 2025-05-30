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

#include "amVK_CommandPoolMAN.hh"
amVK_CommandPoolMAN* amVK_SurfacePresenter::create_CommandPoolMAN_interface(void) {
            this->isBound_Device();
            this->isBound_Surface();
            this->CPM = new amVK_CommandPoolMAN(this->D);
    return  this->CPM;
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

void amVK_SurfacePresenter::destroy_everything_serially(void) {
    this->FBs->DestroyFrameBuffers();
    this->IMGs->DestroySwapChainImageViews();
    this->SC->DestroySwapChain();
    //this->CP_G->FreeCommandBuffers();
    this->RP->DestroyRenderPass();
    this->IMGs->AcquireNextImage_SemaPhore_Destroy();
    this->RenderingFinished_SemaPhore_Destroy();
    //this->CP_G->DestroyCommandPool();
    this->D->DestroyDevice();
}




























static VkSemaphoreCreateInfo g_SP_CI = {
    .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
    .pNext = nullptr,
    .flags = 0
};
void  amVK_SurfacePresenter::RenderingFinished_SemaPhore_Create(void) {
    VkResult return_code = vkCreateSemaphore(this->D->vk_Device, &g_SP_CI, nullptr, &this->RenderingFinished_SemaPhore);
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
void amVK_SurfacePresenter::submit_CMDBUF(VkQueue vk_Queue, VkSemaphore AcquireNextImageSema) {
    if (RenderingFinished_SemaPhore == nullptr) {
        RenderingFinished_SemaPhore_Create();
    }

    VkSemaphore ImageAvailableSemaphore = AcquireNextImageSema;
    VkSemaphore RenderingFinishedSemaphore = this->RenderingFinished_SemaPhore;
    VkCommandBuffer ActiveCommandBuffer = this->CMDBuf;

        g_SI.waitSemaphoreCount     = 1;
        g_SI.pWaitSemaphores        = &ImageAvailableSemaphore;
        g_SI.signalSemaphoreCount   = 1;
        g_SI.pSignalSemaphores      = &RenderingFinishedSemaphore;
        g_SI.commandBufferCount     = 1;
        g_SI.pCommandBuffers        = &ActiveCommandBuffer;
            // I don't think VULKAN Objects are literal objects....
            // I think, VkSemaphore is rather just an ID or smth

    VkResult return_code = vkQueueSubmit(vk_Queue, 1, &g_SI, VK_NULL_HANDLE);
    amVK_return_code_log2("vkQueueSubmit()" );
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
void amVK_SurfacePresenter::Present(VkQueue vk_Queue, VkSwapchainKHR vk_SwapChain, uint32_t nextImage_index) {
    VkSemaphore RenderingFinishedSemaphore = this->RenderingFinished_SemaPhore;

        g_PI.waitSemaphoreCount = 1;
        g_PI.pWaitSemaphores = &RenderingFinishedSemaphore;
        g_PI.swapchainCount = 1;
        g_PI.pSwapchains = &vk_SwapChain;
        g_PI.pImageIndices = &nextImage_index;

        VkResult return_code = vkQueuePresentKHR(vk_Queue, &g_PI);
        
        if (return_code == VK_ERROR_OUT_OF_DATE_KHR) {
            REY_LOG_EX(" [ VK_ERROR_OUT_OF_DATE_KHR ] ----> WIP:- WindowResize()");
        }
        else if (return_code == VK_SUBOPTIMAL_KHR) {
            REY_LOG_EX(" [ VK_SUBOPTIMAL_KHR ] ----> WIP:- Figure out what to do");
        }
        else {
            amVK_return_code_log2( "vkQueuePresentKHR()" ); // above variable "return_code" can't be named smth else
        }
}