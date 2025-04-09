#include "amVK_Device.hh"

amVK_Device::amVK_Device(VkPhysicalDevice PD) 
{
    amVK_Props::PD_Index id = amVK_Props::VkPhysicalDevice_2_PD_Index(PD);
    if (id == amVK_PhysicalDevice_NOT_FOUND) {
        REY_LOG("Can't find VkPhysicalDevice:- " << PD)
    }
    else {
        m_PD_index = id;
        m_physicalDevice = amVK_Props::amVK_1D_GPUs[id];
    }
}

#include "REY_STDWrap.hh"
void amVK_Device::Add_GPU_EXT_ToEnable(const char* extName) {
        // VK_KHR_swapchain
    if (!amVK_Props::called_EnumerateDeviceExtensionProperties) {
         amVK_Props::EnumerateDeviceExtensionProperties();
    }
    
    if (amVK_Props::IS_GPU_EXT_Available(this->m_PD_index, extName)) {
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