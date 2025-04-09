#include "amVK_SwapChain.hh"

/**
 * @param autoFallback:- if SurfaceCapabilities didn't list this imageFormat & colorSpace combination, 
 *      choose closest matching one & report log
 */
void amVK_SwapChain::set_SC_imageFormat_colorSpace(VkFormat imageFormat, VkColorSpaceKHR colorSpace, bool autoFallback) {
    CI.imageFormat = imageFormat;
    CI.imageColorSpace = colorSpace;
}

amVK_SwapChain* amVK_Surface::Create_amVK_SwapChain(amVK_Device *D) {
    this->SC = new amVK_SwapChain(this, D);
    return this->SC;
}