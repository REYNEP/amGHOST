#pragma once
#include "amVK_SurfacePresenter.hh"
#include "amVK_Instance.hh"
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
            // Shortened to take screenshot, 
        .minImageCount = 2,
        .imageFormat = VK_FORMAT_R8G8B8A8_UNORM,
        .imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
            // More Elements are supposed to be here, I always try to list them all
        .oldSwapchain     = nullptr,               // (in SortedOrder of Declaration from VkSpecs)
    };

    /** Refreshes & Syncs `SurfaceCapabilites` */
    void                sync_SurfCaps(void);
    void              konf_Images(VkFormat IF, VkColorSpaceKHR CS, VkImageUsageFlagBits IU, bool autoFallBack = true);
    void              konf_Compositing(VkPresentModeKHR PM, amVK_CompositeClipping CC, VkCompositeAlphaFlagBitsKHR CA );
    void              konf_ImageSharingMode(VkSharingMode ISM)  {CI.imageSharingMode = ISM;}
    VkFormat        active_PixelFormat(void)                    {return CI.imageFormat;}
    VkColorSpaceKHR active_ColorSpace (void)                    {return CI.imageColorSpace;}

  public:
    /**
     * USE:- amVK_SurfacePresenter::create_SwapChain_interface()
     */
    amVK_SwapChain(amVK_SurfacePresenter *PR) {
        this->PR = PR;
        this->CI.surface = PR->S->vk_SurfaceKHR;
    }

  public:
    amVK_SurfacePresenter *PR = nullptr;
    VkSwapchainKHR vk_SwapChainKHR = nullptr;

  public:
    void CreateSwapChain(void);
};