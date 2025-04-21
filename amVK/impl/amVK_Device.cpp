#include "amVK_Device.hh"
#include "amVK/utils/amVK_log.hh"
#include "amVK_InstancePropsEXT.hh"

/** 
 * Wait, I wanted to write some shits here.... [read the amVK_Guide] 
 * SEE: `amVK_InstanceProps::GetARandom_GPU()`
 */
amVK_Device::amVK_Device(VkPhysicalDevice PD) {
    amVK_GPU_Index GPU_ID = amVK_InstanceProps::VkPhysicalDevice_2_amVK_GPU_Index(PD);
    if (GPU_ID == amVK_PhysicalDevice_NOT_FOUND) { REY_LOG_EX("Can't find VkPhysicalDevice:- " << PD); }
    else                                         { _constructor_commons_(GPU_ID); }
}
void amVK_Device::_constructor_commons_(amVK_GPU_Index GPU_ID) {
    this->GPU_ID            = GPU_ID;
    this->GPU_Props         = &amVK_InstanceProps::amVK_1D_GPUs[GPU_ID];
    this->vk_PhysicalDevice = GPU_Props->vk_PhysicalDevice;
}













/* Must Call This:- after editing `amVK_Device::QCI.Array` */
void amVK_Device::sync_1D_QCIs(void) {
    this->CI.queueCreateInfoCount = amVK_1D_QCIs.TheArray.neXt;
    this->CI.pQueueCreateInfos    = amVK_1D_QCIs.TheArray.data;
}

/**
 * @param p1: [VkPhysicalDevice]:- see `amVK_InstanceProps::GetARandom_GPU()`
 */
void amVK_Device::CreateDevice(void) {
    this->sync_1D_QCIs();
    
        VkResult return_code = vkCreateDevice(vk_PhysicalDevice, &CI, nullptr, &this->vk_Device);
        amVK_return_code_log( "vkCreateDevice()" );     // above variable "return_code" can't be named smth else

    log_1D_GPU_EXTs_Enabled(return_code);
}
void amVK_Device::DestroyDevice(void) {
    vkDestroyDevice(this->vk_Device, nullptr);
}












namespace amVK_Array {
    void QCI::select_QFAM_Graphics(amVK_GPU_Index GPU_ID) {
        if (!amVK_InstanceProps::called_EnumeratePhysicalDevices) {
             amVK_InstancePropsEXT::EnumeratePhysicalDevices();
        }
        
        uint32_t  QFAM_Index = amVK_InstanceProps::amVK_1D_GPUs[GPU_ID].ChooseAQueueFamily(VK_QUEUE_GRAPHICS_BIT);
        this->set_QFAM_Index(QFAM_Index);
    }
}











#include "REY_STDWrap.hh"
void amVK_Device::addTo_1D_GPU_EXTs_Enabled(const char* extName) {
        // VK_KHR_swapchain
    if (amVK_InstanceProps::amVK_1D_GPUs[GPU_ID].isExtensionAvailable(extName)) {
        char  *dont_lose = REY_strcpy(extName);

        REY_ArrayDYN_PUSH_BACK(this->amVK_1D_GPU_EXTs_Enabled) = dont_lose;

        this->CI.enabledExtensionCount = this->amVK_1D_GPU_EXTs_Enabled.neXt;
        this->CI.ppEnabledExtensionNames = this->amVK_1D_GPU_EXTs_Enabled.data;
    }
    else {
        REY_LOG_notfound("Vulkan (Physical) Device Extension:- " << extName);
    }
}

void amVK_Device::log_1D_GPU_EXTs_Enabled(VkResult ret) {
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