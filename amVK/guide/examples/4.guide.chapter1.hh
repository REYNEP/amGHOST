#pragma once
#include <vulkan/vulkan.h>
#include "amVK_log.hh"


/**
 * SINGLETON Class Wrapper around VkInstance
 */
class amVK_Instance {
  public:
        // [1 Per VkInstance]:- All of these options should basically be set by the one who is gonna use amVK and create an APP/Software 🤷‍♀️
    VkApplicationInfo amVK_AppInfo = {
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

    VkInstanceCreateInfo amVK_InstanceCI = {
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
    VkInstance m_instance = nullptr;
    void create(void) {
        VkResult return_code = vkCreateInstance(&amVK_InstanceCI, nullptr, &this->m_instance);
        amVK_return_code_log( "vkCreateInstance" );     // above variable "return_code" can't be named smth else
    }
};