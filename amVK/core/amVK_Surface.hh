#pragma once
#include "amVK_InstanceProps.hh"

/**
 * VULKAN-EXT:- `VK_KHR_surface`
 */
class amVK_Surface {
  public:
    VkSurfaceKHR vk_SurfaceKHR = nullptr;
    
    amVK_Surface(VkSurfaceKHR pS) {
        this->vk_SurfaceKHR = pS;
        amVK_InstanceProps::push_back_amVK_Surface(this);
    }

    REY_Array<REY_Array<VkSurfaceFormatKHR>>    amVK_2D_GPUs_ImageFMTs;
    REY_Array<VkSurfaceCapabilitiesKHR>         amVK_1D_GPUs_SurfCAP;

    bool called_GetPhysicalDeviceSurfaceFormatsKHR = false;
    bool called_GetPhysicalDeviceSurfaceCapabilitiesKHR = false;
    void        GetPhysicalDeviceSurfaceInfo(void);
    void        GetPhysicalDeviceSurfaceCapabilitiesKHR(void);
};