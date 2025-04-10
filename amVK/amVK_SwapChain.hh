#pragma once
#include "amVK.hh"
#include "amVK_Device.hh"
#include "amVK_Image.hh"
#include "amVK_Surface.hh"
#include "amVK_ColorSpace.hh"

/**
 * konf = konfigurieren = configure 💁‍♀️
 */
class amVK_SwapChain  {
  public:
    VkSwapchainCreateInfoKHR CI = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0,
        .surface = nullptr,

        .minImageCount = 2,
        .imageFormat = VK_FORMAT_R8G8B8A8_UNORM,
        .imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
        
        .imageExtent = {},
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,

        .queueFamilyIndexCount = 0,
        .pQueueFamilyIndices = nullptr,

        .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = VK_PRESENT_MODE_FIFO_KHR,
        .clipped = VK_TRUE,

        .oldSwapchain     = nullptr,
    };

    void                sync_SurfCaps(void) {
        this->S->PR->refresh_SurfCaps();
        VkSurfaceCapabilitiesKHR *SurfCaps = this->S->PR->fetched_SurfCaps();

        this->CI.minImageCount    = SurfCaps->minImageCount;
        this->CI.imageExtent      = SurfCaps->currentExtent;
        this->CI.imageArrayLayers = SurfCaps->maxImageArrayLayers;
        this->CI.preTransform     = SurfCaps->currentTransform;
    }
    void              konf_Images(
        VkFormat IF, 
        VkColorSpaceKHR CS, 
        VkImageUsageFlagBits IU, 
        bool autoFallBack = true
    );
    void              konf_Compositing(
        VkPresentModeKHR PM,
        amVK_CompositeClipping CC,
        VkCompositeAlphaFlagBitsKHR CA
    );
    void              konf_ImageSharingMode(VkSharingMode ISM)  {CI.imageSharingMode = ISM;}
    VkFormat        active_PixelFormat(void)                    {return CI.imageFormat;}
    VkColorSpaceKHR active_ColorSpace (void)                    {return CI.imageColorSpace;}

  public:
    /**
     * USE:- amVK_Presenter::create_SwapChain()
     */
    amVK_SwapChain(amVK_Surface *pS, amVK_Device *pD) {
        this->S = pS;
        this->D = pD;
        this->CI.surface = pS->S;
    }

  public:
    amVK_Device *D = nullptr;
    amVK_Surface *S = nullptr;
    VkSwapchainKHR SC = nullptr;

    REY_Array<VkImage>    amVK_1D_SC_IMGs;
    REY_Array<amVK_Image> amVK_1D_SC_IMGs_amVK_WRAP;
        // Will we be able to keep sync of these two different thingies correctly?

    bool called_GetSwapChainImagesKHR = false;
    void        GetSwapChainImagesKHR(void);
    bool called_CreateSwapChainImageViews = false;
    void        CreateSwapChainImageViews(void);

  public:
    void CreateSwapChain(void) {
        VkResult return_code = vkCreateSwapchainKHR(this->D->vk_Device, &CI, nullptr, &this->SC);
        amVK_return_code_log( "vkCreateSwapchainKHR()" );     // above variable "return_code" can't be named smth else
    }
};