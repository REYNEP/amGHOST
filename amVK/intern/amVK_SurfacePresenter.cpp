#include "amVK_SurfacePresenter.hh"

#include "amVK_SwapChain.hh"
amVK_SwapChain* amVK_SurfacePresenter::create_SwapChain_interface(void) {
    this->SC = new amVK_SwapChain(this);
    return this->SC;
}

#include "amVK_RenderPass.hh"
amVK_RenderPass* amVK_SurfacePresenter::create_RenderPass_interface(void) {
    this->RP = new amVK_RenderPass(this);
    return this->RP;
}

#include "amVK_CommandBuffer.hh"
amVK_CommandPool* amVK_SurfacePresenter::create_CommandPool_interface(void) {
    this->CP = new amVK_CommandPool(this);
    return this->CP;
}























/**
 *  OUT:- `amVK_1D_GPUs`
 * PREV:- `amVK_Instance::CreateInstance()`
 */
void amVK_SurfacePresenter::GetSwapChainImagesKHR(void) 
{
    // ---------------------------- images1D -------------------------------
    uint32_t imagesCount = 0;     
        // [implicit valid usage]:- must be 0     [if 3rd-param = nullptr]

        vkGetSwapchainImagesKHR(this->D->vk_Device, this->SC->vk_SwapChainKHR, &imagesCount, nullptr);
            // This function is 'output-ing into' deviceCount

    REY_Array<VkImage> images1D;
    images1D.n    = imagesCount;
    images1D.data = new VkImage[imagesCount];

        VkResult return_code = vkGetSwapchainImagesKHR(this->D->vk_Device, this->SC->vk_SwapChainKHR, &imagesCount, images1D.data);
        amVK_return_code_log( "vkGetSwapchainImagesKHR()" );
    // ---------------------------- images1D -------------------------------

    called_GetSwapChainImagesKHR = true;

    this->amVK_1D_SC_IMGs.n    = imagesCount;
    this->amVK_1D_SC_IMGs.data = new amVK_Image[imagesCount];
    REY_Array_LOOP(this->amVK_1D_SC_IMGs, i) {
        this->amVK_1D_SC_IMGs[i].D              = this->D;
        this->amVK_1D_SC_IMGs[i].vk_Image       = images1D[i];
        this->amVK_1D_SC_IMGs[i].ViewCI.image   = images1D[i];
        this->amVK_1D_SC_IMGs[i].ViewCI.format  = this->SC->CI.imageFormat;
    }
}

void amVK_SurfacePresenter::CreateSwapChainImageViews(void) {
    if (!called_GetSwapChainImagesKHR) {
        GetSwapChainImagesKHR();
    }

    REY_Array_LOOP(this->amVK_1D_SC_IMGs, i) {
        this->amVK_1D_SC_IMGs[i].ViewCI.viewType = VK_IMAGE_VIEW_TYPE_2D;

        this->amVK_1D_SC_IMGs[i].ViewCI.components = { // Equivalent to:
            VK_COMPONENT_SWIZZLE_R,        // VK_COMPONENT_SWIZZLE_IDENTITY
            VK_COMPONENT_SWIZZLE_G,        // VK_COMPONENT_SWIZZLE_IDENTITY
            VK_COMPONENT_SWIZZLE_B,        // VK_COMPONENT_SWIZZLE_IDENTITY
            VK_COMPONENT_SWIZZLE_A         // VK_COMPONENT_SWIZZLE_IDENTITY
        };

        this->amVK_1D_SC_IMGs[i].ViewCI.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        this->amVK_1D_SC_IMGs[i].ViewCI.subresourceRange.baseMipLevel = 0;
        this->amVK_1D_SC_IMGs[i].ViewCI.subresourceRange.levelCount = 1;
        this->amVK_1D_SC_IMGs[i].ViewCI.subresourceRange.baseArrayLayer = 0;
        this->amVK_1D_SC_IMGs[i].ViewCI.subresourceRange.layerCount = 1;

        this->amVK_1D_SC_IMGs[i].CreateImageView();
    }

    called_CreateSwapChainImageViews = true;
}





















/*
  ______     ___      __    __  .___________. __    ______   .__   __. 
 /      |   /   \    |  |  |  | |           ||  |  /  __  \  |  \ |  | 
|  ,----'  /  ^  \   |  |  |  | `---|  |----`|  | |  |  |  | |   \|  | 
|  |      /  /_\  \  |  |  |  |     |  |     |  | |  |  |  | |  . `  | 
|  `----./  _____  \ |  `--'  |     |  |     |  | |  `--'  | |  |\   | 
 \______/__/     \__\ \______/      |__|     |__|  \______/  |__| \__| 

IMPL_CAUTION
*/
#include "amVK_FrameBuffer.hh"
void amVK_SurfacePresenter::create_FrameBuffers(void) {
    this->amVK_1D_SC_FBs.reserve(this->amVK_1D_SC_IMGs.n);

    REY_Array_LOOP(this->amVK_1D_SC_FBs, k) {
        amVK_FrameBuffer FB(this);

            FB.CI.attachmentCount = 1;
            FB.CI.pAttachments = &(this->amVK_1D_SC_IMGs[k].vk_ImageView);

            FB.CI.width = 0;
            FB.CI.height = 0;

            FB.CreateFrameBuffer();

        this->amVK_1D_SC_FBs[k] = FB;
    }
}
/*
IMPL_CAUTION
  ______     ___      __    __  .___________. __    ______   .__   __. 
 /      |   /   \    |  |  |  | |           ||  |  /  __  \  |  \ |  | 
|  ,----'  /  ^  \   |  |  |  | `---|  |----`|  | |  |  |  | |   \|  | 
|  |      /  /_\  \  |  |  |  |     |  |     |  | |  |  |  | |  . `  | 
|  `----./  _____  \ |  `--'  |     |  |     |  | |  `--'  | |  |\   | 
 \______/__/     \__\ \______/      |__|     |__|  \______/  |__| \__| 

*/




















void amVK_SurfacePresenter::CreateSemaPhore(void) {
    VkSemaphoreCreateInfo SP_CI = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0
    };

    VkResult return_code = vkCreateSemaphore(this->D->vk_Device, &SP_CI, nullptr, &this->vk_SemaPhore);
    amVK_return_code_log( "vkCreateSemaphore()" );     // above variable "return_code" can't be named smth else
}

uint32_t amVK_SurfacePresenter::AcquireNextImage(void) {
    uint64_t ns_per_second = 1'000'000'000;

    if (this->vk_SemaPhore == nullptr) {
        this->CreateSemaPhore();
    }

    VkResult return_code = vkAcquireNextImageKHR(this->D->vk_Device, this->SC->vk_SwapChainKHR, 1'000'000'000, vk_SemaPhore, nullptr, &this->NextImageIndex_Acquired);
    if (return_code == VK_ERROR_OUT_OF_DATE_KHR) {
        REY_LOG_EX(" [ VK_ERROR_OUT_OF_DATE_KHR ] ----> WIP:- WindowResize()");
    }
    else if (return_code == VK_SUBOPTIMAL_KHR) {
        REY_LOG_EX(" [ VK_SUBOPTIMAL_KHR ] ----> WIP:- Figure out what to do");
    }
    else {
        amVK_return_code_log( "vkAcquireNextImageKHR()" ); // above variable "return_code" can't be named smth else
    }

    return this->NextImageIndex_Acquired;
}