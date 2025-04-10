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
        .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .queueFamilyIndexCount = 0,
        .pQueueFamilyIndices = nullptr,
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
    bool called_CreateSwapChainImageViews = false;

  public:
    void CreateSwapChain(void) {
        VkResult return_code = vkCreateSwapchainKHR(this->D->m_device, &CI, nullptr, &this->SC);
        amVK_return_code_log( "vkCreateSwapchainKHR()" );     // above variable "return_code" can't be named smth else
    }









  public:
    /**
     *  OUT:- `amVK_1D_GPUs`
     * PREV:- `amVK_Instance::CreateInstance()`
     */
    void GetSwapChainImagesKHR(void) 
    {
        // ---------------------------- amVK_1D_SC_IMGs -------------------------------
        uint32_t imagesCount = 0;     
            // [implicit valid usage]:- must be 0     [if 3rd-param = nullptr]

            vkGetSwapchainImagesKHR(this->D->m_device, this->SC, &imagesCount, nullptr);
                // This function is 'output-ing into' deviceCount

        amVK_1D_SC_IMGs.n    = imagesCount;
        amVK_1D_SC_IMGs.data = new VkImage[imagesCount];

            VkResult return_code = vkGetSwapchainImagesKHR(this->D->m_device, this->SC, &imagesCount, amVK_1D_SC_IMGs.data);
            amVK_return_code_log( "vkGetSwapchainImagesKHR()" );
        // ---------------------------- amVK_1D_SC_IMGs -------------------------------

        called_GetSwapChainImagesKHR = true;

        amVK_1D_SC_IMGs_amVK_WRAP.n    = imagesCount;
        amVK_1D_SC_IMGs_amVK_WRAP.data = new amVK_Image[imagesCount];
        REY_Array_LOOP(amVK_1D_SC_IMGs_amVK_WRAP, i) {
            amVK_1D_SC_IMGs_amVK_WRAP[i].D              = this->D;
            amVK_1D_SC_IMGs_amVK_WRAP[i].IMG            = this->amVK_1D_SC_IMGs[i];
            amVK_1D_SC_IMGs_amVK_WRAP[i].ViewCI.image   = this->amVK_1D_SC_IMGs[i];
            amVK_1D_SC_IMGs_amVK_WRAP[i].ViewCI.format  = this->CI.imageFormat;
        }
    }

    void CreateSwapChainImageViews(void) {
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
};