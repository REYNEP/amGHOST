#include "amVK_SwapChain.hh"
#include "amVK/common/amVK_log.hh"

/**
 * TODO:- Implemenet autoFallBack support
 * 
 * @param imageFormat:- `VkFormat` / `amVK_ImageFormat::item` / see `amVK_ColorSpace.hh`
 * @param colorSpace:- `VkColorSpaceKHR` / `amVK_ColorSpace::item` / see `amVK_ColorSpace.hh`
 * @param autoFallBack:- if SurfaceCapabilities didn't list this imageFormat & colorSpace combination, 
 *      choose closest matching one & report log
```
 -       NEXT:-             `amVK_SwapChain::createSwapChain()`
```
 */
void amVK_SwapChain::konf_Images(
    VkFormat IF, 
    VkColorSpaceKHR CS, 
    VkImageUsageFlagBits IU, 
    bool autoFallBack
) {
    CI.imageFormat = IF;
    CI.imageColorSpace = CS;
    CI.imageUsage = IU;
}
void amVK_SwapChain::konf_Compositing(
    VkPresentModeKHR PM,
    amVK_CompositeClipping CC,
    VkCompositeAlphaFlagBitsKHR CA
) {
    CI.compositeAlpha = CA;
    CI.clipped = CC;
    CI.presentMode = PM;
}

void amVK_SwapChain::CreateSwapChain(VkDevice vk_Device) {
    this->used_vk_Device = vk_Device;
    
    VkResult return_code = vkCreateSwapchainKHR(vk_Device, &CI, nullptr, &this->vk_SwapChainKHR);
    amVK_return_code_log( "vkCreateSwapchainKHR()" );     // above variable "return_code" can't be named smth else
}


















/**
              __      ___  __          _____                     _____ _           _       _____                                 
              \ \    / / |/ /         / ____|                   / ____| |         (_)     |_   _|                                
   __ _ _ __ __\ \  / /| ' /         | (_____      ____ _ _ __ | |    | |__   __ _ _ _ __   | |  _ __ ___   __ _  __ _  ___  ___ 
  / _` | '_ ` _ \ \/ / |  <           \___ \ \ /\ / / _` | '_ \| |    | '_ \ / _` | | '_ \  | | | '_ ` _ \ / _` |/ _` |/ _ \/ __|
 | (_| | | | | | \  /  | . \          ____) \ V  V / (_| | |_) | |____| | | | (_| | | | | |_| |_| | | | | | (_| | (_| |  __/\__ \
  \__,_|_| |_| |_|\/   |_|\_\        |_____/ \_/\_/ \__,_| .__/ \_____|_| |_|\__,_|_|_| |_|_____|_| |_| |_|\__,_|\__, |\___||___/
                          ______ ______                  | |                                                      __/ |          
                         |______|______|                 |_|                                                     |___/           
 */

#include "amVK_SwapChainIMGs.hh"
/**
 *  OUT:- `amVK_1D_GPUs`
 * PREV:- `amVK_Instance::CreateInstance()`
 */
void amVK_SwapChainIMGs::GetSwapChainImagesKHR(void) 
{
    // ---------------------------- images1D -------------------------------
    uint32_t imagesCount = 0;     
        // [implicit valid usage]:- must be 0     [if 3rd-param = nullptr]

        vkGetSwapchainImagesKHR(this->SC->used_vk_Device, this->SC->vk_SwapChainKHR, &imagesCount, nullptr);
            // This function is 'output-ing into' deviceCount

    this->amVK_1D_SC_IMGs.n    = imagesCount;
    this->amVK_1D_SC_IMGs.data = new VkImage[imagesCount];

        VkResult return_code = vkGetSwapchainImagesKHR(this->SC->used_vk_Device, this->SC->vk_SwapChainKHR, &imagesCount, this->amVK_1D_SC_IMGs.data);
        amVK_return_code_log( "vkGetSwapchainImagesKHR()" );
    // ---------------------------- images1D -------------------------------

    called_GetSwapChainImagesKHR = true;
}

void amVK_SwapChainIMGs::CreateSwapChainImageViews(void) {
    if (called_GetSwapChainImagesKHR == false) {
         this->GetSwapChainImagesKHR();
    }

    this->ViewCI.format = this->SC->CI.imageFormat;

    this->amVK_1D_SC_IMGViews.n    = amVK_1D_SC_IMGs.n;
    this->amVK_1D_SC_IMGViews.data = new VkImageView[amVK_1D_SC_IMGs.n];

    REY_Array_LOOP(this->amVK_1D_SC_IMGs, i) {
        this->ViewCI.image = amVK_1D_SC_IMGs[i];

        VkResult return_code = vkCreateImageView(this->SC->used_vk_Device, &this->ViewCI, nullptr, &this->amVK_1D_SC_IMGViews[i]);
        amVK_return_code_log( "vkCreateImageView()" );
    }

    called_CreateSwapChainImageViews = true;
}







static VkSemaphoreCreateInfo g_SP_CI = {
    .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
    .pNext = nullptr,
    .flags = 0
};
void  amVK_SwapChainIMGs::CreateSemaPhore(void) {
    VkResult return_code = vkCreateSemaphore(this->SC->used_vk_Device, &g_SP_CI, nullptr, &this->vk_SemaPhore);
    amVK_return_code_log( "vkCreateSemaphore()" );     // above variable "return_code" can't be named smth else
}







uint32_t amVK_SwapChainIMGs::AcquireNextImage(void) {
    uint64_t ns_per_second = 1'000'000'000;

    if (this->vk_SemaPhore == nullptr) {
        this->CreateSemaPhore();
    }

        VkResult return_code = vkAcquireNextImageKHR(
            this->SC->used_vk_Device, 
            this->SC->vk_SwapChainKHR, 
            1'000'000'000, vk_SemaPhore, nullptr, 
            &this->NextImageIndex_Acquired
        );
        
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