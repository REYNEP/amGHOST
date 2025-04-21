#pragma once

// nlohmann - Handles String Stuffs automatically
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <vulkan/vulkan.h>
#define   amVK_Enum2String_IMPLEMENTATION
#include "amVK_Enum2String.hh"
#include "REY_Utils.hh"

nlohmann::ordered_json nlohmann_VkQueueFamilyProperties(VkQueueFamilyProperties *QFP);
nlohmann::ordered_json nlohmann_VkSurfaceCapabilitiesKHR(VkSurfaceCapabilitiesKHR *SCAP);
nlohmann::ordered_json nlohmann_VkSurfaceFormatKHR(VkSurfaceFormatKHR SFMT);

nlohmann::ordered_json nlohmann_Array_VkQueueFamilyProperties(REY_Array<VkQueueFamilyProperties> QFPs);
nlohmann::ordered_json nlohmann_Array_VkExtensionProperties(REY_Array<VkExtensionProperties> EXTP);
nlohmann::ordered_json nlohmann_Array_VkSurfaceFormatKHR(REY_Array<VkSurfaceFormatKHR> SFMTs);

nlohmann::ordered_json nlohmann_VkPhysicalDeviceMemoryProperties(VkPhysicalDeviceMemoryProperties* MEMProps);
nlohmann::ordered_json nlohmann_VkPhysicalDeviceFeatures(VkPhysicalDeviceFeatures* PD_Features);
nlohmann::ordered_json nlohmann_VkMemoryHeap(VkMemoryHeap* MEMHeap);
nlohmann::ordered_json nlohmann_VkMemoryType(VkMemoryType* MEMType);
nlohmann::ordered_json nlohmann_Array_VkMemoryHeap(REY_Array<VkMemoryHeap> MEMHeaps);
nlohmann::ordered_json nlohmann_Array_VkMemoryType(REY_Array<VkMemoryType> MEMTypes);

nlohmann::ordered_json nlohmann_amVK_GPUProps(void);
nlohmann::ordered_json nlohmann_amVK_1D_GPUs(void);