#pragma once
#include "amVK.hh"

class amVK_RenderPass;
class amVK_SwapChain;
class amVK_Device;

/**
 * VULKAN-EXT:- `VK_KHR_surface`
 *       IMPL:- `amVK_1D_SurfaceInfos`
 */
class amVK_Surface {
  public:
    VkSurfaceKHR S = nullptr;
    amVK_SwapChain *SC = nullptr;
    amVK_RenderPass *RP = nullptr;
        // SC.VkDevice = RP.VkDevice
    
    amVK_Surface(void) {}
    amVK_Surface(VkSurfaceKHR pS) {
        this->S = pS;
        amVK_Props::push_back_amVK_Surface(this);
    }

                REY_Array<REY_Array<VkSurfaceFormatKHR>>              amVK_2D_GPUs_ImageFMTs;
                REY_Array<VkSurfaceCapabilitiesKHR>                   amVK_1D_GPUs_SurfCAP;

    bool called_GetPhysicalDeviceSurfaceFormatsKHR = false;
    bool called_GetPhysicalDeviceSurfaceCapabilitiesKHR = false;
    void        GetPhysicalDeviceSurfaceInfo(void);

  public:
    amVK_SwapChain* Create_amVK_SwapChain(amVK_Device *D);
        // Defined currently inside amVK_SwapChain.cpp
};
