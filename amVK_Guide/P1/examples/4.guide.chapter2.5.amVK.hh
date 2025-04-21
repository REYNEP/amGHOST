#pragma once
#include <vulkan/vulkan.h>
#include "REY_Utils.hh"
#include "amVK_log.hh"

/**
 * SINGLETON Class Wrapper around VkInstance
 */
class amVK_Instance {
  public:
        // [1 Per VkInstance]:- All of these options should basically be set by the one who is gonna use amVK and create an APP/Software 🤷‍♀️
    static inline VkApplicationInfo amVK_AppInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext = nullptr,
        .pApplicationName = "amVK_ApplicationInfo.pApplicationName not given",
            // [implicit valid usage]:- must not be NULL
        .applicationVersion = VK_MAKE_API_VERSION(0, 0, 0, 0),
        .pEngineName = "amVK_ApplicationInfo.pEngineName not given",
            // [implicit valid usage]:- must not be NULL
        .engineVersion = VK_MAKE_API_VERSION(0, 0, 0, 0),
        .apiVersion = VK_API_VERSION_1_0
            // version of the Vulkan API against which the application expects to run on
    };

    static inline VkInstanceCreateInfo amVK_InstanceCI = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            // [implicit valid usage]:- must     be <above_value>
        .pNext = nullptr,
            // [implicit valid usage]:- must     be NULL
        .flags = 0,
            // [implicit valid usage]:- must     be 0
        .pApplicationInfo = &amVK_AppInfo,
        .enabledLayerCount = 0,
        .ppEnabledLayerNames = nullptr,
        .enabledExtensionCount = 0,
        .ppEnabledExtensionNames = nullptr
    };

  public:
    static inline         VkInstance  s_vk   = nullptr;
    static inline      amVK_Instance *s_amVK = nullptr;
    #define amVK_HEART amVK_Instance::s_amVK
    static void       CreateInstance(void)
    {
        if (s_vk) {
            REY_LOG_EX("[amVK_Instance::CreateInstance]:- A amVK System Already Exists, Please Destroy it before you can create another System.");
            return;
        }
        amVK_HEART = (amVK_Instance *) new amVK_Instance();

        VkResult return_code = vkCreateInstance(&amVK_InstanceCI, nullptr, &s_vk);
        amVK_return_code_log("vkCreateInstance()");  // above variable "return_code" can't be named smth else
    }


/**
                                    _____  _               _           _ _____             _          
     /\                            |  __ \| |             (_)         | |  __ \           (_)         
    /  \   _ __ _ __ __ _ _   _    | |__) | |__  _   _ ___ _  ___ __ _| | |  | | _____   ___  ___ ___ 
   / /\ \ | '__| '__/ _` | | | |   |  ___/| '_ \| | | / __| |/ __/ _` | | |  | |/ _ \ \ / / |/ __/ _ \
  / ____ \| |  | | | (_| | |_| |   | |    | | | | |_| \__ \ | (_| (_| | | |__| |  __/\ V /| | (_|  __/
 /_/    \_\_|  |_|  \__,_|\__, |   |_|    |_| |_|\__, |___/_|\___\__,_|_|_____/ \___| \_/ |_|\___\___|
                           __/ |_____             __/ |                                               
                          |___/______|           |___/                                                
*/
  public:
    static inline REY_Array<VkPhysicalDevice>   s_HardwareGPU_List;
        // This doesn't allocate any memory
    #define amVK_GPU_List        amVK_Instance::s_HardwareGPU_List
    #define amVK_Enumerated_GPUs amVK_Instance::s_HardwareGPU_List

    static inline void EnumeratePhysicalDevices(void) 
    {
        uint32_t deviceCount = 0;     
            // [implicit valid usage]:- must be 0     [if 3rd-param = nullptr]

            vkEnumeratePhysicalDevices(amVK_Instance::s_vk, &deviceCount, nullptr);
                // This function is 'output-ing into' deviceCount

        amVK_GPU_List.n    = deviceCount;
        amVK_GPU_List.data = new VkPhysicalDevice[deviceCount];

            VkResult return_code = vkEnumeratePhysicalDevices(amVK_Instance::s_vk, &amVK_GPU_List.n, amVK_GPU_List.data);
            amVK_return_code_log("vkEnumeratePhysicalDevices()");
    }

    static inline VkPhysicalDevice GetARandom_PhysicalDevice(void) {
        return s_HardwareGPU_List[0];
    }
    static inline         PD_Index GetARandom_PhysicalDevice_amVK_Index(void) { 
        return 0; 
    }



/**
  ___  _____                                   ____  ______      __  __   _____                     
 |__ \|  __ \   /\                            / __ \|  ____/\   |  \/  | |  __ \                    
    ) | |  | | /  \   _ __ _ __ __ _ _   _   | |  | | |__ /  \  | \  / | | |__) | __ ___  _ __  ___ 
   / /| |  | |/ /\ \ | '__| '__/ _` | | | |  | |  | |  __/ /\ \ | |\/| | |  ___/ '__/ _ \| '_ \/ __|
  / /_| |__| / ____ \| |  | | | (_| | |_| |  | |__| | | / ____ \| |  | | | |   | | | (_) | |_) \__ \
 |____|_____/_/    \_\_|  |_|  \__,_|\__, |   \___\_\_|/_/    \_\_|  |_| |_|   |_|  \___/| .__/|___/
                                      __/ |_____                     ______              | |        
                                     |___/______|                   |______|             |_|        
*/
  public:
    static inline REY_Array<REY_Array<VkQueueFamilyProperties>>   s_HardwareGPU_QFamProps_List2D;
    #define amVK_2D_GPUs_QFAMs                     amVK_Instance::s_HardwareGPU_QFamProps_List2D

        /** 
         * Don't Call before you have called `amVK_Instance::EnumeratePhysicalDevices()`
         * TODO: 
         *   --> Make all the Memory Allocation within this function -> in one block of RAM
         */
    static inline void GetPhysicalDeviceQueueFamilyProperties(void) {
        amVK_2D_GPUs_QFAMs.reserve(amVK_GPU_List.n);
            
            // for each GPU
        for (uint32_t k = 0; k < amVK_GPU_List.n; k++) 
        {
            REY_Array<VkQueueFamilyProperties> *k_QFamProps = &amVK_2D_GPUs_QFAMs.data[k];

            uint32_t queueFamilyCount = 0;
                    // [implicit valid usage]:- must be 0     [if 3rd-param = nullptr]
                vkGetPhysicalDeviceQueueFamilyProperties(amVK_GPU_List[k], &queueFamilyCount, nullptr);
                    // This function is 'output-ing into' queueFamilyCount

            k_QFamProps->n = queueFamilyCount;
            k_QFamProps->data = new VkQueueFamilyProperties[queueFamilyCount];

                vkGetPhysicalDeviceQueueFamilyProperties(amVK_GPU_List[k], &k_QFamProps->n, k_QFamProps->data);
        }

        amVK_DONE("vkGetPhysicalDeviceQueueFamilyProperties()" << " 😄");
    }

  /**
   * i don't wanna scatter all the Properties All around my code. So, i'm gonna keep them here 😊
   */
    
  /*
   * Non-SingleTon Stuffs
   */
  public:
    void ExportYAML(void);
    void ExportJSON(void);
    void Export_yyJSON(void);
};