#pragma once

#include <vulkan/vulkan.h>
    // Every Function
#include <string>
    // Every Function
#include <vector>
    // vulkan_imageUsageFlags_Names()
    // etc

// Previously All of these were inside a class, because I didn't want a separate Forward Declaration & wanted the definitions to be inside the header, having to .cpp
//     -> https://github.com/REYNEP/amGHOST/blob/51b08c708ba73feb8e338f014da93efa0dd48d30/amVK/intern/amVK_Enum2String.hh

std::string toSTR(void* ptr);
std::string vulkan_colorSpace_name(VkColorSpaceKHR ColorSpace);
std::string vulkan_imageFormat_name(VkFormat imageFormat);

std::vector<std::string> vulkan_queueFlags_Names(VkQueueFlags queueFlags);
std::vector<std::string> vulkan_imageUsageFlags_Names(VkImageUsageFlags imageUsageFlags);
std::vector<std::string> vulkan_compositeAlphaFlags_Names(VkCompositeAlphaFlagsKHR compositeAlphaFlags);
std::vector<std::string> vulkan_surfaceTransformFlags_Names(VkSurfaceTransformFlagsKHR surfaceTransformFlags);