#pragma once
#include "amVK_InstancePropsEXPORT.hh"

/**
 * VULKAN-EXT:- `VK_KHR_surface`
 */
class amVK_Surface {
  public:
    VkSurfaceKHR vk_SurfaceKHR = nullptr;
    
    amVK_Surface(VkSurfaceKHR pS) {
        this->vk_SurfaceKHR = pS;
    }

    REY_Array<REY_Array<VkSurfaceFormatKHR>>    amVK_2D_GPUs_ImageFMTs;
    REY_Array<VkSurfaceCapabilitiesKHR>         amVK_1D_GPUs_SurfCAP;

    bool called_GetPhysicalDeviceSurfaceFormatsKHR = false;
    bool called_GetPhysicalDeviceSurfaceCapabilitiesKHR = false;
    void        GetPhysicalDeviceSurfaceInfo(void);
    void        GetPhysicalDeviceSurfaceCapabilitiesKHR(void);

  public:
    inline void                      refresh_SurfCaps(void)                  {          this->GetPhysicalDeviceSurfaceCapabilitiesKHR();        }
    inline VkSurfaceCapabilitiesKHR* fetched_SurfCaps(amVK_GPU_Index GPU_ID) { return &(this->amVK_1D_GPUs_SurfCAP[GPU_ID]);                    }
    inline VkSurfaceCapabilitiesKHR* current_SurfCaps(amVK_GPU_Index GPU_ID) { this->refresh_SurfCaps(); return this->fetched_SurfCaps(GPU_ID); }
};