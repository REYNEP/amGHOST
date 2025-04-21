// --------------------------- amVK_InstanceProps.hh ---------------------------
class amVK_InstanceProps {
    ...
  public:
    /**
     * VULKAN-EXT:- `VK_KHR_surface`
     *       IMPL:- `amVK_1D_SurfaceInfos`
     */
    class SurfaceInfo {
      public:
        VkSurfaceKHR S = nullptr;
        SurfaceInfo(void) {}
        SurfaceInfo(VkSurfaceKHR pS) {this-> S = pS;}

                  REY_Array<REY_Array<VkSurfaceFormatKHR>>              amVK_2D_GPUs_ImageFMTs;
                  REY_Array<VkSurfaceCapabilitiesKHR>                   amVK_1D_GPUs_SurfCAP;

        bool called_GetPhysicalDeviceSurfaceFormatsKHR = false;
        bool called_GetPhysicalDeviceSurfaceCapabilitiesKHR = false;
        void        GetPhysicalDeviceSurfaceInfo(void);
    };
    ...
}


// --------------------------- amVK_InstanceProps.cpp ---------------------------

/**
 *        OUT:- `amVK_2D_GPUs_ImageFMTs`
 * DEPENDENCY:- [AutoCall]:- `amVK_InstanceProps::EnumeratePhysicalDevices()` if hasn't been called 
 */
void amVK_InstanceProps::SurfaceInfo::GetPhysicalDeviceSurfaceInfo(void) {
    if (!amVK_InstanceProps::called_EnumeratePhysicalDevices) {
         amVK_InstanceProps::       EnumeratePhysicalDevices();
    }

    amVK_2D_GPUs_ImageFMTs.reserve(amVK_1D_GPUs.n);
    amVK_1D_GPUs_SurfCAP  .reserve(amVK_1D_GPUs.n);
    
    amVK_LOOP_GPUs(k)
    {
        // ----------------------- amVK_2D_GPUs_ImageFMTs --------------------------
        REY_Array<VkSurfaceFormatKHR> *k_IMG_FMTs = &amVK_2D_GPUs_ImageFMTs.data[k];

        uint32_t imageFormatCount = 0;
            // [implicit valid usage]:- must be 0     [if 3rd-param = nullptr]
            VkResult return_code = vkGetPhysicalDeviceSurfaceFormatsKHR(amVK_1D_GPUs[k], this->S, &imageFormatCount, nullptr);
            amVK_RC_silent_check( "vkGetPhysicalDeviceSurfaceFormatsKHR()" );

        k_IMG_FMTs->n = imageFormatCount;
        k_IMG_FMTs->data = new VkSurfaceFormatKHR[imageFormatCount];
                     return_code = vkGetPhysicalDeviceSurfaceFormatsKHR(amVK_1D_GPUs[k], this->S, &k_IMG_FMTs->n, k_IMG_FMTs->data);
            amVK_return_code_log( "vkGetPhysicalDeviceSurfaceFormatsKHR()" );
    
        amVK_InstanceProps::SurfaceInfo::called_GetPhysicalDeviceSurfaceFormatsKHR = true;
        // ----------------------- amVK_2D_GPUs_ImageFMTs --------------------------




        // ------------------------ amVK_1D_GPUs_SurfCAP ---------------------------
        VkSurfaceCapabilitiesKHR *k_SURF_CAPs = &amVK_1D_GPUs_SurfCAP.data[k];

                     return_code = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(amVK_1D_GPUs[k], this->S, k_SURF_CAPs);
            amVK_return_code_log( "vkGetPhysicalDeviceSurfaceCapabilitiesKHR()" );

        amVK_InstanceProps::SurfaceInfo::called_GetPhysicalDeviceSurfaceFormatsKHR = true;
        // ------------------------ amVK_1D_GPUs_SurfCAP ---------------------------
    }
}