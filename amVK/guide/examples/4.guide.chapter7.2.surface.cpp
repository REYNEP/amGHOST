#include "amVK_Surface.hh"
amVK_Surface::amVK_Surface(VkSurfaceKHR pS) {
    this->S = pS;
    this->PR = new amVK_Presenter(this);
    amVK_Props::push_back_amVK_Surface(this);
}

#include "amVK_SwapChain.hh"
amVK_SwapChain* amVK_Presenter::create_SwapChain(void) {
    this->SC = new amVK_SwapChain(this->S, this->D);
    return this->SC;
}

#include "amVK_RenderPass.hh"
amVK_RenderPass* amVK_Presenter::create_RenderPass(void) {
    this->RP = new amVK_RenderPass(this);
    return this->RP;
}

#include "amVK_FrameBuffer.hh"
amVK_FrameBuffer* amVK_Presenter::create_FrameBuffer(void) {
    this->FB = new amVK_FrameBuffer(this);
    return this->FB;
}


















/**
 * @param D:- Why not Physical Device?
```
-> Because the way you would like to create the "VkDevice" is completely up to you
```
 */
void amVK_Presenter::bind_Device(amVK_Device *D) {
    this->D = D;
    this->GPU = D->vk_PhysicalDevice;
    this->GPU_Index = amVK_Props::VkPhysicalDevice_2_PD_Index(D->vk_PhysicalDevice);
}


















#include "amVK_Surface.hh"
/**
 * POSSIBLE-BUG:- I am not sure, but we might not be able to call this function as per any random PhysicalDevice. We Are Probably not supposed to
 *  TODO:- Ask people/ChatGPT about this
 * 
 *        OUT:- `amVK_2D_GPUs_ImageFMTs`
 * DEPENDENCY:- [AutoCall]:- `amVK_Props::EnumeratePhysicalDevices()` if hasn't been called 
 */
void amVK_Surface::GetPhysicalDeviceSurfaceInfo(void) {
    if (!amVK_Props::called_EnumeratePhysicalDevices) {
         amVK_Props::       EnumeratePhysicalDevices();
    }

    amVK_2D_GPUs_ImageFMTs.reserve(amVK_Props::amVK_1D_GPUs.n);
    amVK_1D_GPUs_SurfCAP  .reserve(amVK_Props::amVK_1D_GPUs.n);
    
    REY_Array_LOOP(amVK_Props::amVK_1D_GPUs, k)
    {
        // ----------------------- amVK_2D_GPUs_ImageFMTs --------------------------
        REY_Array<VkSurfaceFormatKHR> *k_IMG_FMTs = &amVK_2D_GPUs_ImageFMTs[k];

        uint32_t imageFormatCount = 0;
            // [implicit valid usage]:- must be 0     [if 3rd-param = nullptr]
            VkResult return_code = vkGetPhysicalDeviceSurfaceFormatsKHR(amVK_Props::amVK_1D_GPUs[k], this->S, &imageFormatCount, nullptr);
            amVK_RC_silent_check( "vkGetPhysicalDeviceSurfaceFormatsKHR()" );

        k_IMG_FMTs->n = imageFormatCount;
        k_IMG_FMTs->data = new VkSurfaceFormatKHR[imageFormatCount];
                     return_code = vkGetPhysicalDeviceSurfaceFormatsKHR(amVK_Props::amVK_1D_GPUs[k], this->S, &k_IMG_FMTs->n, k_IMG_FMTs->data);
            amVK_return_code_log( "vkGetPhysicalDeviceSurfaceFormatsKHR()" );
    
        amVK_Surface::called_GetPhysicalDeviceSurfaceFormatsKHR = true;
        // ----------------------- amVK_2D_GPUs_ImageFMTs --------------------------




        // ------------------------ amVK_1D_GPUs_SurfCAP ---------------------------
        VkSurfaceCapabilitiesKHR *k_SURF_CAPs = &amVK_1D_GPUs_SurfCAP[k];

                     return_code = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(amVK_Props::amVK_1D_GPUs[k], this->S, k_SURF_CAPs);
            amVK_return_code_log( "vkGetPhysicalDeviceSurfaceCapabilitiesKHR()" );

        amVK_Surface::called_GetPhysicalDeviceSurfaceFormatsKHR = true;
        // ------------------------ amVK_1D_GPUs_SurfCAP ---------------------------
    }
}


#include "amVK_Surface.hh"
/**
 *        OUT:- `amVK_2D_GPUs_ImageFMTs`
 * DEPENDENCY:- [AutoCall]:- `amVK_Props::EnumeratePhysicalDevices()` if hasn't been called 
 */
void amVK_Surface::GetPhysicalDeviceSurfaceCapabilitiesKHR(void) {
    if (!amVK_Props::called_EnumeratePhysicalDevices) {
         amVK_Props::       EnumeratePhysicalDevices();
    }

    amVK_1D_GPUs_SurfCAP  .reserve(amVK_Props::amVK_1D_GPUs.n);
    
    REY_Array_LOOP(amVK_Props::amVK_1D_GPUs, k)
    {
        // ------------------------ amVK_1D_GPUs_SurfCAP ---------------------------
        VkSurfaceCapabilitiesKHR *k_SURF_CAPs = &amVK_1D_GPUs_SurfCAP[k];

            VkResult return_code = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(amVK_Props::amVK_1D_GPUs[k], this->S, k_SURF_CAPs);
            amVK_return_code_log( "vkGetPhysicalDeviceSurfaceCapabilitiesKHR()" );

        amVK_Surface::called_GetPhysicalDeviceSurfaceCapabilitiesKHR = true;
        // ------------------------ amVK_1D_GPUs_SurfCAP ---------------------------
    }
}