#pragma once
#include "amVK_SwapChain.hh"

class amVK_SwapChainIMGs {
  public:
    VkImageViewCreateInfo ViewCI = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .image = nullptr,
        .viewType = VK_IMAGE_VIEW_TYPE_2D,
        .format = VK_FORMAT_UNDEFINED,
            // CreateSwapChainImageViews() sets ---> this->SC->CI.imageFormat
        .components = {
            VK_COMPONENT_SWIZZLE_R,
            VK_COMPONENT_SWIZZLE_G,
            VK_COMPONENT_SWIZZLE_B,
            VK_COMPONENT_SWIZZLE_A 
        },
        .subresourceRange = {
            .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
            .baseMipLevel = 0,
            .levelCount = 1,
            .baseArrayLayer = 0,
            .layerCount = 1
        }
    };

    VkExtent2D active_ImageExtent(void) {return this->SC->active_ImageExtent();}

  public:
    amVK_SwapChain *SC = nullptr;

    REY_Array<VkImage>     amVK_1D_SC_IMGs;
    REY_Array<VkImageView> amVK_1D_SC_IMGViews;

    amVK_SwapChainIMGs(amVK_SwapChain *SC) {this->SC = SC;}
   ~amVK_SwapChainIMGs() {}

  public:
    void           GetSwapChainImagesKHR(void);              // used_vk_Device 
    bool    called_GetSwapChainImagesKHR         = false;
    bool called_CreateSwapChainImageViews        = false;
    void        CreateSwapChainImageViews(void);             // used_vk_Device

  public:
    uint32_t               NextImageIndex_Acquired = UINT32_MAX;
    uint32_t        AcquireNextImage(void);

    VkSemaphore vk_SemaPhore = nullptr;
    void     CreateSemaPhore(void);
};