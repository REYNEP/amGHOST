#pragma once
#include "amVK_Instance.hh"

class amVK_SwapChain;
class amVK_RenderPass;
class amVK_FrameBuffer;
class amVK_CommandPool;
class amVK_CommandBuffer;

class amVK_Device;
class amVK_Presenter;

/**
 * VULKAN-EXT:- `VK_KHR_surface`
 *       IMPL:- `amVK_1D_SurfaceInfos`
 */
class amVK_Surface {
  public:
    VkSurfaceKHR vk_SurfaceKHR = nullptr;       //     Set in CONSTRUCTOR
    amVK_Presenter         *PR = nullptr;   // Created in CONSTRUCTOR
    
    amVK_Surface(void) {}
    amVK_Surface(VkSurfaceKHR pS);

                REY_Array<REY_Array<VkSurfaceFormatKHR>>              amVK_2D_GPUs_ImageFMTs;
                REY_Array<VkSurfaceCapabilitiesKHR>                   amVK_1D_GPUs_SurfCAP;

    bool called_GetPhysicalDeviceSurfaceFormatsKHR = false;
    bool called_GetPhysicalDeviceSurfaceCapabilitiesKHR = false;
    void        GetPhysicalDeviceSurfaceInfo(void);
    void        GetPhysicalDeviceSurfaceCapabilitiesKHR(void);
};


class amVK_Presenter {
  public:
    amVK_Surface  *S  = nullptr;
    amVK_SwapChain *SC = nullptr;
    amVK_RenderPass *RP = nullptr;
    amVK_CommandPool *CP = nullptr;
    amVK_CommandBuffer *CB = nullptr;
        //      SC.VkDevice = RP.VkDevice
    amVK_Device           *D = nullptr;
    VkPhysicalDevice      GPU = nullptr;
        //    amVK_Device.m_PD = this->GPU;
    amVK_GPU_Index    GPU_Index = 0;

    REY_Array<amVK_FrameBuffer *> FBs;
    
  public:
    void bind_Device(amVK_Device *D);
    amVK_Presenter  (amVK_Surface* pS) {this->S = pS;}

  public:
    amVK_SwapChain*   create_SwapChain_interface(void);
    amVK_RenderPass*  create_RenderPass_interface(void);
    void              create_FrameBuffers(void);
    amVK_CommandPool* create_CommandPool_interface(void);
    // Defined currently inside amVK_SwapChain.cpp
    
    void                      refresh_SurfCaps(void) { this->S->GetPhysicalDeviceSurfaceCapabilitiesKHR(); }
    VkSurfaceCapabilitiesKHR* fetched_SurfCaps(void) {
        return &( this->S->amVK_1D_GPUs_SurfCAP[this->GPU_Index] );
    }
};
