#pragma once
#include "amVK_Instance.hh"

class amVK_RenderPass;
class amVK_SwapChain;
class amVK_Device;
class amVK_SurfacePresenter;

/**
 * VULKAN-EXT:- `VK_KHR_surface`
 *       IMPL:- `amVK_1D_SurfaceInfos`
 */
class amVK_Surface {
  public:
    VkSurfaceKHR S = nullptr;       // Set in CONSTRUCTOR
    amVK_SurfacePresenter *PR = nullptr;   // Set in CONSTRUCTOR
    
    amVK_Surface(void) {}
    amVK_Surface(VkSurfaceKHR pS);

                REY_Array<REY_Array<VkSurfaceFormatKHR>>              amVK_2D_GPUs_ImageFMTs;
                REY_Array<VkSurfaceCapabilitiesKHR>                   amVK_1D_GPUs_SurfCAP;

    bool called_GetPhysicalDeviceSurfaceFormatsKHR = false;
    bool called_GetPhysicalDeviceSurfaceCapabilitiesKHR = false;
    void        GetPhysicalDeviceSurfaceInfo(void);
    void        GetPhysicalDeviceSurfaceCapabilitiesKHR(void);
};


class amVK_SurfacePresenter {
  public:
    amVK_Surface  *S  = nullptr;
    amVK_SwapChain *SC = nullptr;
    amVK_RenderPass *RP = nullptr;
        //   SC.VkDevice = RP.VkDevice
    amVK_Device        *D = nullptr;
    VkPhysicalDevice   GPU = nullptr;
        // amVK_Device.m_PD = this->GPU;
    amVK_GPU_Index GPU_Index = 0;
    
  public:
    void bind_Device(amVK_Device *D);
    amVK_SurfacePresenter  (amVK_Surface* pS) {this->S = pS;}

  public:
    amVK_SwapChain*  create_SwapChain(void);
    amVK_RenderPass* create_RenderPass(void);
    // Defined currently inside amVK_SwapChain.cpp
    
    void                      refresh_SurfCaps(void) { this->S->GetPhysicalDeviceSurfaceCapabilitiesKHR(); }
    VkSurfaceCapabilitiesKHR* fetched_SurfCaps(void) {
        return &( this->S->amVK_1D_GPUs_SurfCAP[this->GPU_Index] );
    }
};
