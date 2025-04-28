#pragma once
#include "amVK_DeviceQueues.hh"

/**
 * Not a "VkPhysicalDevice"
 * This is "VkDevice"
 */
class amVK_Device {
  public:
    amVK_Device(amVK_GPUProps *GPUProps) : GPUProps(GPUProps), Queues(GPUProps), vk_PhysicalDevice(GPUProps->vk_PhysicalDevice) {}
   ~amVK_Device() {}

  public:
    amVK_GPUProps*            GPUProps = nullptr;
    VkPhysicalDevice vk_PhysicalDevice = nullptr;
    VkDevice         vk_Device         = nullptr;

  public:
    amVK_DeviceQueues      Queues;      // see `QCI::amVK_QueueCount` & `amVK_GPUProps::QFamID`
              void sync_1D_QCIs(void) { 
        Queues.generate_1D_QCIs(); 
        Queues.    sync_1D_QCIs(&this->CI); 
    }
    
    REY_ArrayDYN<char*>     amVK_1D_GPU_EXTs_Enabled;
    void                   addTo_1D_GPU_EXTs_Enabled(const char* extName);  // If Available
    void                     log_1D_GPU_EXTs_Enabled(VkResult ret);         // CreateDevice() calls ---> this function

    VkDeviceCreateInfo CI = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,

        .queueCreateInfoCount = 0,
        .pQueueCreateInfos = nullptr,
            // CreateDevice() calls ---> sync_1D_QCIs()
            // CreateDevice() calls ---> REY_Calculate_QFam_MaxQueueCount_Queried()

        .enabledLayerCount = 0,
        .ppEnabledLayerNames = nullptr,
            // [deprecated by VULKAN]

        .enabledExtensionCount = 0,
        .ppEnabledExtensionNames = nullptr,
        .pEnabledFeatures = nullptr
    };

  public:
    void  CreateDevice(uint32_t GraphicsQueueCount);
    void     GetDeviceQueues(void) { Queues.GetDeviceQueues(vk_Device); }
    void DestroyDevice(void);
};