#pragma once
#include <vulkan/vulkan.h>

#include "REY_Utils.hh"
#include "intern/amVK_log.hh"
#include "amVK_GlobalProps.hh"

/**
 * SINGLETON Class Wrapper around VkInstance
 */
class amVK_Instance {
  public:
        // [1 Per VkInstance]:- All of these options should basically be set by the one who is gonna use amVK and create an APP/Software 🤷‍♀️
    static VkApplicationInfo AppInfo;
    static VkInstanceCreateInfo CI;
        // iMPLEMENTATIONS of these CreateInfos (CI) is inside --> `amVK_CreateInfos.cpp` 😊

  public:
    static inline   VkInstance vk_Instance = nullptr;
    static void CreateInstance(void)
    {
        if (vk_Instance) {
            REY_LOG_EX("[amVK_Instance::CreateInstance]:- A amVK System Already Exists, Please Destroy it before you can create another System.");
            return;
        }

        VkResult return_code = vkCreateInstance(&CI, nullptr, &vk_Instance);
        amVK_return_code_log( "vkCreateInstance()" );  // above variable "return_code" can't be named smth else

        amVK_GlobalProps::Log_InstanceEXTs_Enabled(return_code);
    }

  public:
    /**
     * You should use `amVK_GlobalProps::EnumerateInstanceExtensions()`
     */
    static void EnumerateInstanceExtensions(void) {
        amVK_GlobalProps::EnumerateInstanceExtensions();
    }
    /**
     * USES:- `REY_ArrayDYN<char *> amVK_GlobalProps::amVK_1D_InstanceEXTs_Enabled`
     * SETS:- into `static amVK_Instance::CI`
     */
    static void Add_InstanceEXT_ToEnable(const char* extName) {
        amVK_GlobalProps::Add_InstanceEXT_ToEnable(extName);
    }
};