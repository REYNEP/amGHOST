#pragma once
#include <vulkan/vulkan.h>
#include "REY_Utils.hh"
#include "intern/amVK_log.hh"
#include "amVK_Props.hh"

/**
 * SINGLETON Class Wrapper around VkInstance
 */
class amVK_Instance {
  public:
        // [1 Per VkInstance]:- All of these options should basically be set by the one who is gonna use amVK and create an APP/Software 🤷‍♀️
    static inline VkApplicationInfo AppInfo = {
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

    static inline VkInstanceCreateInfo CI = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            // [implicit valid usage]:- must     be <above_value>
        .pNext = nullptr,
            // [implicit valid usage]:- must     be NULL
        .flags = 0,
            // [implicit valid usage]:- must     be 0
        .pApplicationInfo = &AppInfo,
        .enabledLayerCount = 0,
        .ppEnabledLayerNames = nullptr,
        .enabledExtensionCount = 0,
        .ppEnabledExtensionNames = nullptr
    };

  public:
    static inline         VkInstance  s_vk   = nullptr;
    static inline      amVK_Instance *s_amVK = nullptr;
    #define amVK_HEART amVK_Instance::s_amVK
    #define amVK_PROPS amVK_Props
    static void       CreateInstance(void)
    {
        if (s_vk) {
            REY_LOG_EX("[amVK_Instance::CreateInstance]:- A amVK System Already Exists, Please Destroy it before you can create another System.");
            return;
        }

        VkResult return_code = vkCreateInstance(&CI, nullptr, &s_vk);
        amVK_return_code_log( "vkCreateInstance()" );  // above variable "return_code" can't be named smth else

            // If Everything is STATIC, won't need this
        amVK_HEART = (amVK_Instance *) new amVK_Instance();
        amVK_Props::Log_InstanceEXTs_Enabled(return_code);
    }

  public:
    /**
     * USES:- `REY_ArrayDYN<char *> amVK_Props::amVK_1D_InstanceEXTs_Enabled`
     */
    static void Add_InstanceEXT_ToEnable(const char* extName) {
        amVK_Props::Add_InstanceEXT_ToEnable(extName);
    }
};