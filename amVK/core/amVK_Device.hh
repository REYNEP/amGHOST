#pragma once
#include "amVK_DeviceQCI.hh"

/**
 * Not a "VkPhysicalDevice"
 * This is "VkDevice"
 */
class amVK_Device {
  public:
    amVK_Array::QCI         amVK_1D_QCIs;
    void                    sync_1D_QCIs(void);
    void                    Default_QCI__select_QFAM_Graphics(void) {amVK_1D_QCIs.select_QFAM_Graphics(this->GPU_ID);}
    
    REY_ArrayDYN<char*>     amVK_1D_GPU_EXTs_Enabled;
    void                   addTo_1D_GPU_EXTs_Enabled(const char* extName);  // If Available
    void                     log_1D_GPU_EXTs_Enabled(VkResult ret);         // CreateDevice() calls this

    VkDeviceCreateInfo CI = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,

        .queueCreateInfoCount = 0,
        .pQueueCreateInfos = nullptr,
            // CreateDevice() calls ---> sync_1D_QCIs()

        .enabledLayerCount = 0,
        .ppEnabledLayerNames = nullptr,
            // [deprecated by VULKAN]

        .enabledExtensionCount = 0,
        .ppEnabledExtensionNames = nullptr,
        .pEnabledFeatures = nullptr
    };

  public:
        /** SEE: `amVK_InstanceProps::GetARandom_GPU()` */
    amVK_Device(amVK_GPU_Index GPU_ID) {_constructor_commons_(GPU_ID);}
    amVK_Device(VkPhysicalDevice PD);
   ~amVK_Device() {}
    void _constructor_commons_(amVK_GPU_Index GPU_ID);

  public:
    amVK_GPU_Index GPU_ID = amVK_PhysicalDevice_NOT_FOUND;
    VkPhysicalDevice          vk_PhysicalDevice = nullptr;
    VkDevice                  vk_Device         = nullptr;

  public:
    void  CreateDevice(void);
    void DestroyDevice(void);
    VkQueue get_default_queue() {
        VkQueue vk_Queue = nullptr;
        vkGetDeviceQueue(this->vk_Device, this->amVK_1D_QCIs.get_QFAM_Index(), 0, &vk_Queue);
        return  vk_Queue;
    }
};