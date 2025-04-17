#include "amVK_Instance.hh"

struct amVK_Device_QueueCreateInfo {
    const float Default_QP = 1.0f;
        // Range = (0.0 -> 1.0) [inclusive]
        // Within the same device, queues with higher priority may be allotted more processing time than queues with lower priority.

    VkDeviceQueueCreateInfo Default = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .queueFamilyIndex = 0,
            // vkGetPhysicalDeviceQueueFamilyProperties() --> look for a QueueFamily that supports `VK_QUEUE_GRAPHICS_BIT`
        .queueCount = 1,
        .pQueuePriorities = &Default_QP
    };

    REY_ArrayDYN<VkDeviceQueueCreateInfo> Array = REY_ArrayDYN<VkDeviceQueueCreateInfo>(nullptr, 0, 0);
        // No Memory Allocation by default 😊
        //      1. REY_ArrayDYN.initialize(10)
        //      2. REY_ARRAY_PUSH_BACK(Array) = your_QueueCI;        [not a function. but rather a preprocessor macro]

    /* Initializes with Space for 2 elements --> PushBacks `this->Default`*/
    void init_with_default(void) {
        Array.initialize(2);
        REY_ARRAY_PUSH_BACK(Array) = this->Default;
    }
};

/**
 * Not a "VkPhysicalDevice"
 * This is "VkDevice"
 */
class amVK_Device {
  public:
    amVK_Device_QueueCreateInfo QCI;
    VkDeviceCreateInfo CI = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = nullptr,
            // This one can be pointer to heck ton of things [see docs]
        .flags = 0,
            // [implicit valid usage]:- must     be 0
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &QCI.Default,
            // if you wanna add --> edit `amVK_Device::QCI.Array` --> call `Set_QCI_Array_into_DeviceCI()`
        .enabledLayerCount = 0,
        .ppEnabledLayerNames = nullptr,
            // [deprecated]             should not be used
        .enabledExtensionCount = 0,
        .ppEnabledExtensionNames = nullptr,
        .pEnabledFeatures = nullptr
    };
    /* `amVK_Device::QCI.Array` shouldn't be edited after calling this */
    void Set_QCI_Array_into_DeviceCI(void) {
        this->CI.queueCreateInfoCount = QCI.Array.neXt;
        this->CI.pQueueCreateInfos    = QCI.Array.data;
    }
    void set_QFAM_Index(uint32_t qFAM_Index) {
        this->QCI.Default.queueFamilyIndex = qFAM_Index;
    }
    void select_QFAM_Graphics(void) {
        if (!amVK_InstanceProps::called_GetPhysicalDeviceQueueFamilyProperties) {
             amVK_InstanceProps::EnumeratePhysicalDevices();
        }

        if (!amVK_InstanceProps::called_GetPhysicalDeviceQueueFamilyProperties) {
             amVK_InstanceProps::GetPhysicalDeviceQueueFamilyProperties();
        }

        amVK_InstanceProps::PD_Index GPU_k = this->PD_ID;
        uint32_t        qFAM_Index = amVK_InstanceProps::ChooseAQueueFamily(VK_QUEUE_GRAPHICS_BIT, GPU_k);

        this->set_QFAM_Index(qFAM_Index);
    }

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