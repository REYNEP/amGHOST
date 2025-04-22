#include "amVK_Surface.hh"
#include "amVK/utils/amVK_log.hh"
/**
 * POSSIBLE-BUG:- I am not sure, but we might not be able to call this function as per any random PhysicalDevice. We Are Probably not supposed to
 *  TODO:- Ask people/ChatGPT about this
 * 
 *        OUT:- `amVK_2D_GPUs_ImageFMTs`
 * DEPENDENCY:- [AutoCall]:- `amVK_InstanceProps::EnumeratePhysicalDevices()` if hasn't been called 
 */
void amVK_Surface::GetPhysicalDeviceSurfaceInfo(void) {
    if (!amVK_InstanceProps::called_EnumeratePhysicalDevices) {
         amVK_InstancePropsEXT::    EnumeratePhysicalDevices();
    }

    amVK_2D_GPUs_ImageFMTs.reserve(amVK_InstanceProps::amVK_1D_GPUs.n);
    amVK_1D_GPUs_SurfCAP  .reserve(amVK_InstanceProps::amVK_1D_GPUs.n);
    
    REY_Array_LOOP(amVK_InstanceProps::amVK_1D_GPUs, k)
    {
        // ----------------------- amVK_2D_GPUs_ImageFMTs --------------------------
        REY_Array<VkSurfaceFormatKHR> *k_IMG_FMTs = &amVK_2D_GPUs_ImageFMTs[k];

        uint32_t imageFormatCount = 0;
            // [implicit valid usage]:- must be 0     [if 3rd-param = nullptr]
            VkResult return_code = vkGetPhysicalDeviceSurfaceFormatsKHR(amVK_InstanceProps::amVK_1D_GPUs[k].vk_PhysicalDevice, this->vk_SurfaceKHR, &imageFormatCount, nullptr);
            amVK_RC_silent_check( "vkGetPhysicalDeviceSurfaceFormatsKHR()" );

        k_IMG_FMTs->n = imageFormatCount;
        k_IMG_FMTs->data = new VkSurfaceFormatKHR[imageFormatCount];
                     return_code = vkGetPhysicalDeviceSurfaceFormatsKHR(amVK_InstanceProps::amVK_1D_GPUs[k].vk_PhysicalDevice, this->vk_SurfaceKHR, &k_IMG_FMTs->n, k_IMG_FMTs->data);
            amVK_return_code_log( "vkGetPhysicalDeviceSurfaceFormatsKHR()" );
    
        amVK_Surface::called_GetPhysicalDeviceSurfaceFormatsKHR = true;
        // ----------------------- amVK_2D_GPUs_ImageFMTs --------------------------

        // ------------------------ amVK_1D_GPUs_SurfCAP ---------------------------
        VkSurfaceCapabilitiesKHR *k_SURF_CAPs = &amVK_1D_GPUs_SurfCAP[k];

                     return_code = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(amVK_InstanceProps::amVK_1D_GPUs[k].vk_PhysicalDevice, this->vk_SurfaceKHR, k_SURF_CAPs);
            amVK_return_code_log( "vkGetPhysicalDeviceSurfaceCapabilitiesKHR()" );

        amVK_Surface::called_GetPhysicalDeviceSurfaceFormatsKHR = true;
        // ------------------------ amVK_1D_GPUs_SurfCAP ---------------------------
    }
}


#include "amVK_Surface.hh"
/**
 *        OUT:- `amVK_2D_GPUs_ImageFMTs`
 * DEPENDENCY:- [AutoCall]:- `amVK_InstanceProps::EnumeratePhysicalDevices()` if hasn't been called 
 */
void amVK_Surface::GetPhysicalDeviceSurfaceCapabilitiesKHR(void) {
    if (!amVK_InstanceProps::called_EnumeratePhysicalDevices) {
         amVK_InstancePropsEXT::    EnumeratePhysicalDevices();
    }

    amVK_1D_GPUs_SurfCAP  .reserve(amVK_InstanceProps::amVK_1D_GPUs.n);
    
    REY_Array_LOOP(amVK_InstanceProps::amVK_1D_GPUs, k)
    {
        // ------------------------ amVK_1D_GPUs_SurfCAP ---------------------------
        VkSurfaceCapabilitiesKHR *k_SURF_CAPs = &amVK_1D_GPUs_SurfCAP[k];

            VkResult return_code = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(amVK_InstanceProps::amVK_1D_GPUs[k].vk_PhysicalDevice, this->vk_SurfaceKHR, k_SURF_CAPs);
            amVK_return_code_log( "vkGetPhysicalDeviceSurfaceCapabilitiesKHR()" );

        amVK_Surface::called_GetPhysicalDeviceSurfaceCapabilitiesKHR = true;
        // ------------------------ amVK_1D_GPUs_SurfCAP ---------------------------
    }
}