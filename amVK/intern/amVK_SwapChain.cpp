#include "amVK_SwapChain.hh"

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













/**
 *  OUT:- `amVK_1D_GPUs`
 * PREV:- `amVK_Instance::CreateInstance()`
 */
void amVK_SwapChain::GetSwapChainImagesKHR(void) 
{
    // ---------------------------- amVK_1D_SC_IMGs -------------------------------
    uint32_t imagesCount = 0;     
        // [implicit valid usage]:- must be 0     [if 3rd-param = nullptr]

        vkGetSwapchainImagesKHR(this->D->vk_Device, this->SC, &imagesCount, nullptr);
            // This function is 'output-ing into' deviceCount

    amVK_1D_SC_IMGs.n    = imagesCount;
    amVK_1D_SC_IMGs.data = new VkImage[imagesCount];

        VkResult return_code = vkGetSwapchainImagesKHR(this->D->vk_Device, this->SC, &imagesCount, amVK_1D_SC_IMGs.data);
        amVK_return_code_log( "vkGetSwapchainImagesKHR()" );
    // ---------------------------- amVK_1D_SC_IMGs -------------------------------

    called_GetSwapChainImagesKHR = true;

    amVK_1D_SC_IMGs_amVK_WRAP.n    = imagesCount;
    amVK_1D_SC_IMGs_amVK_WRAP.data = new amVK_Image[imagesCount];
    REY_Array_LOOP(amVK_1D_SC_IMGs_amVK_WRAP, i) {
        amVK_1D_SC_IMGs_amVK_WRAP[i].D              = this->D;
        amVK_1D_SC_IMGs_amVK_WRAP[i].vk_Image       = this->amVK_1D_SC_IMGs[i];
        amVK_1D_SC_IMGs_amVK_WRAP[i].ViewCI.image   = this->amVK_1D_SC_IMGs[i];
        amVK_1D_SC_IMGs_amVK_WRAP[i].ViewCI.format  = this->CI.imageFormat;
    }
}

void amVK_SwapChain::CreateSwapChainImageViews(void) {
    if (!called_GetSwapChainImagesKHR) {
        GetSwapChainImagesKHR();
    }

    REY_Array_LOOP(amVK_1D_SC_IMGs_amVK_WRAP, i) {
        amVK_1D_SC_IMGs_amVK_WRAP[i].ViewCI.viewType = VK_IMAGE_VIEW_TYPE_2D;

        amVK_1D_SC_IMGs_amVK_WRAP[i].ViewCI.components = { // Equivalent to:
            VK_COMPONENT_SWIZZLE_R,        // VK_COMPONENT_SWIZZLE_IDENTITY
            VK_COMPONENT_SWIZZLE_G,        // VK_COMPONENT_SWIZZLE_IDENTITY
            VK_COMPONENT_SWIZZLE_B,        // VK_COMPONENT_SWIZZLE_IDENTITY
            VK_COMPONENT_SWIZZLE_A         // VK_COMPONENT_SWIZZLE_IDENTITY
        };

        amVK_1D_SC_IMGs_amVK_WRAP[i].ViewCI.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        amVK_1D_SC_IMGs_amVK_WRAP[i].ViewCI.subresourceRange.baseMipLevel = 0;
        amVK_1D_SC_IMGs_amVK_WRAP[i].ViewCI.subresourceRange.levelCount = 1;
        amVK_1D_SC_IMGs_amVK_WRAP[i].ViewCI.subresourceRange.baseArrayLayer = 0;
        amVK_1D_SC_IMGs_amVK_WRAP[i].ViewCI.subresourceRange.layerCount = 1;

        amVK_1D_SC_IMGs_amVK_WRAP[i].createImageView();
    }

    called_CreateSwapChainImageViews = true;
}