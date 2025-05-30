#pragma once
#include <vulkan/vulkan.h>

#include "amVK_Device.hh"
#include "amVK_DeviceQueues.hh"
#include "amVK_Surface.hh"

#include "amVK_SwapChain.hh"
#include "amVK_SwapChainIMGs.hh"
#include "amVK_RenderPass.hh"
#include "amVK_RenderPassFBs.hh"
#include "amVK_CommandPoolMAN.hh"

/**
 * For those who don't know, which after which
 */
class amVK_SurfacePresenter {
  public:
    amVK_Surface   *S  = nullptr;
    amVK_SwapChain  *SC = nullptr;
    amVK_RenderPass  *RP = nullptr;
    amVK_Device        *D = nullptr;
    VkCommandBuffer CMDBuf = nullptr;
    amVK_RenderPassFBs *FBs = nullptr;
    amVK_SwapChainIMGs *IMGs = nullptr;
    amVK_CommandPoolMAN  *CPM = nullptr;
    
  public:
    void bind_Device       (amVK_Device* D)     {this->D = D;}
    void bind_Surface      (amVK_Surface* S)    {this->S = S;}
    void bind_SwapChain    (amVK_SwapChain *SC) {this->SC = SC;}
    amVK_SurfacePresenter  (void)               {}
   ~amVK_SurfacePresenter  (void)               {}

    void               isBound_Device (void)  { if (D == nullptr) {REY_LOG_EX("use bind_Device();  first");} }
    void               isBound_Surface(void)  { if (S == nullptr) {REY_LOG_EX("use bind_Surface(); first");} }

  public:
    /** 
     * 1) Go Serially. 
     * 2) Call amVK_Class::FUNC that modify CreateInfos 3
     * 3) amVK_Class::CreateVkObject() 
     **/
    amVK_SwapChain*      create_SwapChain_interface(void);
    amVK_SwapChainIMGs*  create_SwapChainImages_interface(void);
    amVK_RenderPass*     create_RenderPass_interface(void);
    amVK_RenderPassFBs*  create_FrameBuffers_interface(void);
    amVK_CommandPoolMAN* create_CommandPoolMAN_interface(void);
    void                          set_CommandBuffer(VkCommandBuffer vk_CommandBuffer) {this->CMDBuf = vk_CommandBuffer;}
    void                destroy_everything_serially(void); 

  public:
    VkSemaphore RenderingFinished_SemaPhore = nullptr;
    void        RenderingFinished_SemaPhore_Create(void);
    void        RenderingFinished_SemaPhore_Destroy(void);
    void            submit_CMDBUF(VkQueue vk_Queue, VkSemaphore AcquireNextImageSema);
    void                  Present(VkQueue vk_Queue, VkSwapchainKHR vk_SwapChain, uint32_t nextImage_index);
};
