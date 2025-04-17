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

void amVK_SwapChain::CreateSwapChain(void) {
    VkResult return_code = vkCreateSwapchainKHR(this->PR->D->vk_Device, &CI, nullptr, &this->vk_SwapChainKHR);
    amVK_return_code_log( "vkCreateSwapchainKHR()" );     // above variable "return_code" can't be named smth else
}