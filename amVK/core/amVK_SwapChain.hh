#pragma once
#include "amVK/common/amVK.hh"
#include "amVK/common/amVK_ColorSpace.hh"
#include "amVK_InstancePropsEXT.hh"
#include "amVK_Surface.hh"
#include "amVK_Device.hh"

/**
 * konf = konfigurieren = configure 💁‍♀️
 */
class amVK_SwapChain {
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
            // CreateSwapChain() calls ---> sync_SurfCaps()

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

    void              sync_SurfCaps(void) {
        VkSurfaceCapabilitiesKHR   *SurfCaps = this->S->current_SurfCaps(this->D->GPUProps->ID);
        this->CI.minImageCount    = SurfCaps->minImageCount;
        this->CI.imageExtent      = SurfCaps->currentExtent;
        this->CI.imageArrayLayers = SurfCaps->maxImageArrayLayers;
        this->CI.preTransform     = SurfCaps->currentTransform;
    }
    void              konf_Images(VkFormat IF, VkColorSpaceKHR CS, VkImageUsageFlagBits IU, bool autoFallBack = true);
    void              konf_Compositing(VkPresentModeKHR PM, amVK_CompositeClipping CC, VkCompositeAlphaFlagBitsKHR CA);
    void              konf_ImageSharingMode(VkSharingMode ISM)  {       CI.imageSharingMode = ISM;}
    VkFormat        active_PixelFormat(void)                    {return CI.imageFormat;}
    VkColorSpaceKHR active_ColorSpace (void)                    {return CI.imageColorSpace;}
    VkExtent2D      active_ImageExtent(void)                    {return CI.imageExtent;}

  public:
    amVK_SwapChain(amVK_Surface *S, amVK_Device *D) : S(S), D(D){this->CI.surface = S->vk_SurfaceKHR;}
    amVK_Surface *S;
    amVK_Device  *D;
    VkSwapchainKHR vk_SwapChainKHR = nullptr;

    void CreateSwapChain(void);
    void DestroySwapChain(void);
};