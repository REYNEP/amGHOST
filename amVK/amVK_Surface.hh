#pragma once
#include <vulkan/vulkan.h>
#include "REY_Utils.hh"

class  amVK_SurfacePresenter;
    // amVK_SurfacePresenter is created from amVK_Surface. Ideally 1 per surface.
    // amVK_Surface.PR ---> Backlink to the amVK_SurfacePresenter responsible for this surface
        // it will be created inside the  amVK_Surface::CONSTRUCTOR()

/**
 * VULKAN-EXT:- `VK_KHR_surface`
 */
class amVK_Surface {
  public:
    VkSurfaceKHR vk_SurfaceKHR = nullptr;   //     Set in CONSTRUCTOR
    amVK_SurfacePresenter         *PR = nullptr;   // Created in CONSTRUCTOR
    
    amVK_Surface(VkSurfaceKHR pS);

    REY_Array<REY_Array<VkSurfaceFormatKHR>>    amVK_2D_GPUs_ImageFMTs;
    REY_Array<VkSurfaceCapabilitiesKHR>         amVK_1D_GPUs_SurfCAP;

    bool called_GetPhysicalDeviceSurfaceFormatsKHR = false;
    bool called_GetPhysicalDeviceSurfaceCapabilitiesKHR = false;
    void        GetPhysicalDeviceSurfaceInfo(void);
    void        GetPhysicalDeviceSurfaceCapabilitiesKHR(void);
};