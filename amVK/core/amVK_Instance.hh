#pragma once
#include <vulkan/vulkan.h>
#include "amVK_InstanceProps.hh"

/**
 * SINGLETON Class Wrapper around VkInstance
 */
class amVK_Instance {
  public:
    static VkApplicationInfo AppInfo;
    static VkInstanceCreateInfo CI;
        // iMPLEMENTATIONS --> `amVK_Instance.cpp` 😊

  public:
    static inline   VkInstance vk_Instance = nullptr;
    static void CreateInstance(void);

  public:
    /**  USE:- `amVK_InstanceProps::EnumerateInstanceExtensions()` */
    static void                     EnumerateInstanceExtensions(void) {
                amVK_InstanceProps::EnumerateInstanceExtensions();
    }
    /**  USE:- `amVK_InstanceProps::addTo_1D_InstanceEXTs_Enabled()` */
    static void                     addTo_1D_InstanceEXTs_Enabled(const char* extName) {
                amVK_InstanceProps::addTo_1D_InstanceEXTs_Enabled(extName);
    }
};