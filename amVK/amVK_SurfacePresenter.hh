#pragma once
#include <vulkan/vulkan.h>

#include "amVK_Surface.hh"
#include "amVK_Device.hh"

class amVK_Image;
class amVK_SwapChain;
class amVK_RenderPass;
class amVK_FrameBuffer;
class amVK_CommandPool;
class amVK_CommandBuffer;

/**
 * Should be created in amVK_Surface::CONSTRUCTOR 💁‍♀️
 */
class amVK_SurfacePresenter {
  public:
    amVK_Surface   *S  = nullptr;
    amVK_SwapChain  *SC = nullptr;
    amVK_RenderPass  *RP = nullptr;
    amVK_CommandPool  *CP = nullptr;
    amVK_CommandBuffer *CB = nullptr;
    amVK_Device          *D = nullptr;
    
  public:
    void bind_Device(amVK_Device* D)   {this->D = D;}
    amVK_SurfacePresenter  (amVK_Surface* pS) {this->S = pS;}

  public:
    amVK_SwapChain*   create_SwapChain_interface(void);
    amVK_RenderPass*  create_RenderPass_interface(void);
    amVK_CommandPool* create_CommandPool_interface(void);
    
    void                      refresh_SurfCaps(void) {              this->S->GetPhysicalDeviceSurfaceCapabilitiesKHR(); }
    VkSurfaceCapabilitiesKHR* fetched_SurfCaps(void) { return &(    this->S->amVK_1D_GPUs_SurfCAP[this->D->GPU_ID]   ); }

  public:
    REY_Array<amVK_Image>       amVK_1D_SC_IMGs;
    REY_Array<amVK_FrameBuffer> amVK_1D_SC_FBs;
    
    void        GetSwapChainImagesKHR(void);
    bool called_GetSwapChainImagesKHR       = false;
    bool called_CreateSwapChainImageViews   = false;
    void        CreateSwapChainImageViews(void);

  public:
    void  create_FrameBuffers(void);

    uint32_t        NextImageIndex_Acquired = UINT32_MAX;
    uint32_t AcquireNextImage(void);

  public:
    VkSemaphore vk_SemaPhore = nullptr;
    void     CreateSemaPhore(void);
};
