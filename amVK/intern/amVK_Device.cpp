#include "amVK_Device.hh"

    /** 
     * Wait, I wanted to write some shits here.... [read the amVK_Guide] 
     * SEE: `amVK_GlobalProps::GetARandom_GPU()`
     */
amVK_Device::amVK_Device(VkPhysicalDevice PD) 
{
    amVK_GlobalProps::PD_Index id = amVK_GlobalProps::VkPhysicalDevice_2_PD_Index(PD);
    if (id == amVK_PhysicalDevice_NOT_FOUND) {
        REY_LOG("Can't find VkPhysicalDevice:- " << PD)
    }
    else {
        PD_ID = id;
        vk_PhysicalDevice = amVK_GlobalProps::amVK_1D_GPUs[id];
    }
}

#include "REY_STDWrap.hh"
void amVK_Device::Add_GPU_EXT_ToEnable(const char* extName) {
        // VK_KHR_swapchain
    if (!amVK_GlobalProps::called_EnumerateDeviceExtensionProperties) {
         amVK_GlobalProps::EnumerateDeviceExtensionProperties();
    }
    
    if (amVK_GlobalProps::IS_GPU_EXT_Available(this->PD_ID, extName)) {
        char  *dont_lose = REY_strcpy(extName);

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