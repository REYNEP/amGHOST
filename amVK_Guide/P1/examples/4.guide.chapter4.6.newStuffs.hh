// --------------------------- main.cpp ---------------------------
            REY_LOG("")
        amVK_InstanceProps::push_back_VkSurfaceKHR(VK_S);
        amVK_SwapChain *SC = new amVK_SwapChain(VK_S, D);
            SC->CI.imageFormat = VK_FORMAT_B8G8R8A8_UNORM;
            SC->CI.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
            SC->CI.minImageCount    = amVK_InstanceProps::amVK_1D_SurfaceInfos[0].amVK_1D_GPUs_SurfCAP[0].minImageCount;
            SC->CI.imageExtent      = amVK_InstanceProps::amVK_1D_SurfaceInfos[0].amVK_1D_GPUs_SurfCAP[0].currentExtent;
            SC->CI.imageArrayLayers = amVK_InstanceProps::amVK_1D_SurfaceInfos[0].amVK_1D_GPUs_SurfCAP[0].maxImageArrayLayers;
            SC->CI.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            SC->CI.imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

            SC->CI.compositeAlpha   = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
            SC->CI.preTransform     = amVK_InstanceProps::amVK_1D_SurfaceInfos[0].amVK_1D_GPUs_SurfCAP[0].currentTransform;
            SC->CI.clipped          = VK_TRUE;
            SC->CI.presentMode      = VK_PRESENT_MODE_FIFO_KHR;
            SC->CI.oldSwapchain     = nullptr;
            SC->createSwapChain();
// --------------------------- main.cpp ---------------------------



class amVK_InstanceProps {
    ...
    static inline bool called_EnumerateDeviceExtensionProperties = false;
    static void               EnumerateDeviceExtensionProperties(void); // amVK_2D_GPUs_EXTs

    static inline REY_Array<REY_Array<VkExtensionProperties>>              amVK_2D_GPUs_EXTs;
    #define amVK_LOOP_GPU_EXTs(_k_, _var_)  for (uint32_t _var_ = 0,  lim = amVK_2D_GPUs_EXTs[_k_].n;   _var_ < lim;  _var_++)

    static bool      IS_GPU_EXT_Available(PD_Index GPU_k, const char *extName); // amVK_2D_GPUs_EXTs
    // kinda copy of IS_InstanceEXT_Available
    ...
};


/*
                                    ________   _________  
     /\                            |  ____\ \ / /__   __| 
    /  \   _ __ _ __ __ _ _   _    | |__   \ V /   | |___ 
   / /\ \ | '__| '__/ _` | | | |   |  __|   > <    | / __|
  / ____ \| |  | | | (_| | |_| |   | |____ / . \   | \__ \
 /_/    \_\_|  |_|  \__,_|\__, |   |______/_/ \_\  |_|___/
                           __/ |_____                     
                          |___/______|                    
*/
#include <cstring>
bool amVK_InstanceProps::IS_GPU_EXT_Available(amVK_InstanceProps::PD_Index GPU_k, const char *extName) 
{
     amVK_LOOP_GPU_EXTs(GPU_k, i) {
        if (strcmp(amVK_2D_GPUs_EXTs[GPU_k][i].extensionName, extName) == 0) {
            return true;
        }
    }

    return false;
}


void amVK_InstanceProps::EnumerateDeviceExtensionProperties(void) {
    if (!amVK_InstanceProps::called_EnumeratePhysicalDevices) {
         amVK_InstanceProps::       EnumeratePhysicalDevices();
    }

    amVK_2D_GPUs_EXTs     .reserve(amVK_1D_GPUs.n);

    amVK_LOOP_GPUs(k)
    {
        // ------------------------- amVK_2D_GPUs_EXTs -----------------------------
        REY_Array<VkExtensionProperties> *k_GPU_EXTs = &amVK_2D_GPUs_EXTs[k];

        uint32_t extPropertyCount = 0;
            // [implicit valid usage]:- must be 0     [if 3rd-param = nullptr]
            VkResult return_code = vkEnumerateDeviceExtensionProperties(amVK_1D_GPUs[k], nullptr, &extPropertyCount, nullptr);
            amVK_RC_silent_check( "vkEnumerateDeviceExtensionProperties()" );

        k_GPU_EXTs->n = extPropertyCount;
        k_GPU_EXTs->data = new VkExtensionProperties[extPropertyCount];
                     return_code = vkEnumerateDeviceExtensionProperties(amVK_1D_GPUs[k], nullptr, &k_GPU_EXTs->n, k_GPU_EXTs->data);
            amVK_return_code_log( "vkEnumerateDeviceExtensionProperties()" );
    
        amVK_InstanceProps::called_EnumerateDeviceExtensionProperties = true;
        // ------------------------- amVK_2D_GPUs_EXTs -----------------------------
    }
}
















class amVK_Device {
    ...
    REY_ArrayDYN<char*>   amVK_1D_DeviceEXTs_Enabled;
    void Log_GPU_EXTs_Enabled(VkResult ret);
    void Add_GPU_EXT_ToEnable(const char* extName);
        // Copy of `amVK_InstanceProps::Add_InstanceEXT_ToEnable()` -> but not static anymore.... 🤷‍♀️
};

#include <cstring>
void amVK_Device::Add_GPU_EXT_ToEnable(const char* extName) {
        // VK_KHR_swapchain
    if (!amVK_InstanceProps::called_EnumerateDeviceExtensionProperties) {
         amVK_InstanceProps::EnumerateDeviceExtensionProperties();
    }
    
    if (amVK_InstanceProps::IS_GPU_EXT_Available(this->m_PD_index, extName)) {
        char  *dont_lose = new char[strlen(extName)];
        strcpy(dont_lose, extName);

        REY_ArrayDYN_PUSH_BACK(this->amVK_1D_GPU_EXTs_Enabled) = dont_lose;

        this->CI.enabledExtensionCount = this->amVK_1D_GPU_EXTs_Enabled.neXt;
        this->CI.ppEnabledExtensionNames = this->amVK_1D_GPU_EXTs_Enabled.data;
    }
    else {
        REY_LOG_notfound("Vulkan (Physical) Device Extension:- " << extName);
    }
}

void amVK_Device::Log_GPU_EXTs_Enabled(VkResult ret) {
    if (ret != VK_SUCCESS) {
        REY_LOG_status("vkCreateInstance() failed 😶‍🌫️");
    }
    else {
        REY_LOG_status("         Enabled VULKAN Extensions' Name:- ");
        for (uint32_t k = 0,     lim = amVK_1D_GPU_EXTs_Enabled.n;     k < lim; k++) {
            REY_LOG_status("              | " << amVK_1D_GPU_EXTs_Enabled[k]);
        }
    }
}