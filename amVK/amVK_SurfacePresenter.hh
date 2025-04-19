#pragma once
#include <vulkan/vulkan.h>

#include "amVK_Device.hh"
#include "amVK_Surface.hh"

#include "amVK_SwapChain.hh"
#include "amVK_SwapChainIMGs.hh"
#include "amVK_RenderPass.hh"
#include "amVK_RenderPassFBs.hh"
#include "amVK_CommandPool.hh"

/**
 * Should be created in amVK_Surface::CONSTRUCTOR 💁‍♀️
 */
class amVK_SurfacePresenter {
  public:
    amVK_Surface   *S  = nullptr;
    amVK_SwapChain  *SC = nullptr;
    amVK_RenderPass  *RP = nullptr;
    amVK_CommandPool  *CP = nullptr;
    amVK_Device         *D = nullptr;
    amVK_RenderPassFBs *FBs = nullptr;
    amVK_SwapChainIMGs *IMGs = nullptr;
    
  public:
    void bind_Device       (amVK_Device* D)   {this->D = D;}
    void bind_Surface      (amVK_Surface* S)  {this->S = S;}
    amVK_SurfacePresenter  (void)             {}
   ~amVK_SurfacePresenter  (void)             {}

    void               isBound_Device (void)  { if (D == nullptr) {REY_LOG_EX("use bind_Device();  first");} }
    void               isBound_Surface(void)  { if (S == nullptr) {REY_LOG_EX("use bind_Surface(); first");} }

  public:
    amVK_SwapChain*     create_SwapChain_interface(void);
    amVK_SwapChainIMGs* create_SwapChainImages_interface(void);
    amVK_RenderPass*    create_RenderPass_interface(void);
    amVK_RenderPassFBs* create_FrameBuffers_interface(void);
    amVK_CommandPool*   create_CommandPool_interface(void);
    
    void                      refresh_SurfCaps(void){          this->S->GetPhysicalDeviceSurfaceCapabilitiesKHR(); }
    VkSurfaceCapabilitiesKHR* fetched_SurfCaps(void){ return &(this->S->amVK_1D_GPUs_SurfCAP[this->D->GPU_ID]   ); }

    void                      sync_SC_SurfCaps(void){          this->refresh_SurfCaps();        SC->sync_SurfCaps(this->fetched_SurfCaps()); }
    VkExtent2D              synced_ImageExtent(void){          this->sync_SC_SurfCaps(); return SC->active_ImageExtent(); }

    void              CreateSwapChain(void)         { this->SC->CreateSwapChain  (this->D->vk_Device); }
    void              CreateRenderPass(void)        { this->RP->CreateRenderPass (this->D->vk_Device); }
    void              CreateCommandPool(void)       { this->CP->CreateCommandPool(this->D->vk_Device); }

  public:
    VkCommandBuffer active_CMDBUF(void)             { return   this->CP->get_active_CMDBUF(); }
    void            BeginCommandBuffer(void);
    void            RPBI_ReadyUp(void);
    void            BeginRenderPass(void);
};
