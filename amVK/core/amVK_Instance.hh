#pragma once
#include <vulkan/vulkan.h>
#include "amVK_InstancePropsEXPORT.hh"

/**
 * SINGLETON Class Wrapper around VkInstance
 */
class amVK_Instance {
  public:
        // Modify just the way you'd like to 😊💁‍♀️
    static VkApplicationInfo AppInfo;
    static VkInstanceCreateInfo CI;
        // iMPLEMENTATIONS --> `amVK_Instance.cpp` 😊

  public:
    static inline    VkInstance vk_Instance = nullptr;
    static void  CreateInstance(void);
    static void DestroyInstance(void) {vkDestroyInstance(vk_Instance, nullptr);}

  public:
    static inline REY_ArrayDYN<char*> amVK_1D_Instance_EXTs_Enabled;
    static void                      addTo_1D_Instance_EXTs_Enabled(const char* extName);     // If Available
    static void                        log_1D_Instance_EXTs_Enabled(VkResult ret);            // CreateDevice() calls this

    static inline REY_ArrayDYN<char*> amVK_1D_Instance_Layers_Enabled;
    static void                      addTo_1D_Instance_Layers_Enabled(const char* layerName); // If Available
    static void                        log_1D_Instance_Layers_Enabled(VkResult ret);          // CreateDevice() calls this

    /**  USE:- `amVK_InstanceProps::EnumerateInstanceExtensions()` */
    static void                     EnumerateInstanceExtensions(void) {
                amVK_InstanceProps::EnumerateInstanceExtensions();
    }

    /**  USE:- `amVK_InstanceProps::EnumeratePhysicalDevices()` */
    static void                     EnumeratePhysicalDevices(void) {
                amVK_InstanceProps::EnumeratePhysicalDevices(amVK_Instance::vk_Instance);
    }

    /**  USE:- `amVK_InstanceProps::EnumerateInstanceLayerProperties()` */
    static void                     EnumerateInstanceLayerProperties(void) {
                amVK_InstanceProps::EnumerateInstanceLayerProperties();
    }
};