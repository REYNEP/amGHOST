#include "amVK_Instance.hh"

/**
 * Not a "VkPhysicalDevice"
 * This is "VkDevice"
 */
class amVK_Device {
  public:
    VkDeviceCreateInfo CI = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = nullptr,
            // This one can be pointer to heck ton of things [see docs]
        .flags = 0,
            // [implicit valid usage]:- must     be 0
        .queueCreateInfoCount = 0,
        .pQueueCreateInfos = nullptr,
        .enabledLayerCount = 0,
            // [deprecated]             should not be used
        .ppEnabledLayerNames = nullptr,
            // [deprecated]             should not be used
        .enabledExtensionCount = 0,
        .ppEnabledExtensionNames = nullptr,
        .pEnabledFeatures = nullptr
    };
  public:
    amVK_Device() {}
   ~amVK_Device() {}

  public:
    VkPhysicalDevice m_physicalDevice = nullptr;
    VkDevice m_device = nullptr;
    /**
     * @param p1: [VkPhysicalDevice]:- see `amVK_Instance::GetARandom_PhysicalDevice()`
     */
    void CreateDevice(VkPhysicalDevice p1) {
        m_physicalDevice = p1;
        VkResult return_code = vkCreateDevice(m_physicalDevice, &CI, nullptr, &this->m_device);
        amVK_return_code_log( "vkCreateDevice" );     // above variable "return_code" can't be named smth else
    }
    void DestroyDevice(void) {
        vkDestroyDevice(this->m_device, nullptr);
    }
};