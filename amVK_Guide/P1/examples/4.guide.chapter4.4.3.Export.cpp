#include "amVK_Instance.hh"
#include "amVK_Enum2String.hh"

// nlohmann - Handles String Stuffs automatically
#include <nlohmann/json.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
std::string toSTR(void* ptr) {
    std::stringstream ss;
    ss << ptr;
    return ss.str();
}

/*
 * https://quickref.me/json.html
 * ordered_json -> kinda like std::unordered_map
 *              -> i.e. doesn't automatically sort alphabetically
 */
void amVK_InstanceProps::ExportJSON(void) {
    nlohmann::ordered_json root;
    nlohmann::ordered_json vkEnumeratePhysicalDevices               = nlohmann::ordered_json::object();
    nlohmann::ordered_json vkEnumerateInstanceExtensionProperties   = nlohmann::ordered_json::object();
    nlohmann::ordered_json vkCreate_xxx_SurfaceKHR                  = nlohmann::ordered_json::object();

    amVK_LOOP_IEXTs(i) {
        std::string value = "specVersion" + std::to_string(amVK_1D_InstanceEXTs[i].specVersion);
        vkEnumerateInstanceExtensionProperties[amVK_1D_InstanceEXTs[i].extensionName] = value;
    }
    root["vkEnumerateInstanceExtensionProperties"] = vkEnumerateInstanceExtensionProperties;


    amVK_LOOP_SURFs(m) {
        nlohmann::ordered_json SURF_m = nlohmann::ordered_json::object();

        {
            SURF_m["Memory Address"] = toSTR(amVK_1D_SurfaceInfos[m].S);
        }
        amVK_LOOP_GPUs(k) {
            nlohmann::ordered_json GPU_k = nlohmann::ordered_json::object();

                GPU_k["Memory Address"] = toSTR(amVK_1D_GPUs[k]);
                nlohmann::ordered_json vkGetPhysicalDeviceSurfaceFormatsKHR = nlohmann::ordered_json::object();

                    amVK_LOOP_SURF_FMTs(amVK_1D_SurfaceInfos[k], k, i) {
                        nlohmann::ordered_json SURF_FMT_i = nlohmann::ordered_json::object();

                            SURF_FMT_i["format / imageFormat"] = vulkan_imageFormat_name(amVK_1D_SurfaceInfos[k].amVK_2D_GPUs_ImageFMTs[k][i].format);
                            SURF_FMT_i["colorspace"] = vulkan_colorspace_name(amVK_1D_SurfaceInfos[k].amVK_2D_GPUs_ImageFMTs[k][i].colorSpace);

                        vkGetPhysicalDeviceSurfaceFormatsKHR["[SurfaceFormat " + std::to_string(i) + "]"] = SURF_FMT_i;
                    }

                GPU_k["vkGetPhysicalDeviceSurfaceFormatsKHR()"] = vkGetPhysicalDeviceSurfaceFormatsKHR;

            SURF_m["[GPU " + std::to_string(k) + "]"] = GPU_k;
        }

        vkCreate_xxx_SurfaceKHR["[Surface " + std::to_string(m) + "]"] = SURF_m;
    }
    root["vkCreate_xxx_SurfaceKHR"] = vkCreate_xxx_SurfaceKHR;
                    
    amVK_LOOP_GPUs(k) {
        nlohmann::ordered_json GPU_k = nlohmann::ordered_json::object();

            nlohmann::ordered_json QFAM_Array = nlohmann::ordered_json::object(); 

            for (uint32_t i = 0, lim = amVK_2D_GPUs_QFAMs[k].n; i < lim; i++) {
                nlohmann::ordered_json QFAM_i = nlohmann::ordered_json::object();

                nlohmann::ordered_json qF = nlohmann::ordered_json::array();
                    VkQueueFlags _qF = amVK_2D_GPUs_QFAMs[k][i].queueFlags;
                    if (_qF & VK_QUEUE_GRAPHICS_BIT)         { qF.push_back("VK_QUEUE_GRAPHICS_BIT"); }
                    if (_qF & VK_QUEUE_COMPUTE_BIT)          { qF.push_back("VK_QUEUE_COMPUTE_BIT"); }
                    if (_qF & VK_QUEUE_TRANSFER_BIT)         { qF.push_back("VK_QUEUE_TRANSFER_BIT"); }
                    if (_qF & VK_QUEUE_SPARSE_BINDING_BIT)   { qF.push_back("VK_QUEUE_SPARSE_BINDING_BIT"); }
                    if (_qF & VK_QUEUE_PROTECTED_BIT)        { qF.push_back("VK_QUEUE_PROTECTED_BIT"); }
                    if (_qF & VK_QUEUE_VIDEO_DECODE_BIT_KHR) { qF.push_back("VK_QUEUE_VIDEO_DECODE_BIT_KHR"); }
                    if (_qF & VK_QUEUE_VIDEO_ENCODE_BIT_KHR) { qF.push_back("VK_QUEUE_VIDEO_ENCODE_BIT_KHR"); }
                    if (_qF & VK_QUEUE_OPTICAL_FLOW_BIT_NV)  { qF.push_back("VK_QUEUE_OPTICAL_FLOW_BIT_NV"); }
                    qF.push_back(std::string("VkQueueFlagBits:- ") + std::to_string(_qF));
                
                QFAM_i["queueFlags"] = qF;
                QFAM_i["queueCount"] = amVK_2D_GPUs_QFAMs[k][i].queueCount;
                QFAM_i["timestampValidBits"] = amVK_2D_GPUs_QFAMs[k][i].timestampValidBits;

                nlohmann::ordered_json minImageTransferGranularity = nlohmann::json::object();
                    minImageTransferGranularity["width"] = amVK_2D_GPUs_QFAMs[k][i].minImageTransferGranularity.width;
                    minImageTransferGranularity["height"] = amVK_2D_GPUs_QFAMs[k][i].minImageTransferGranularity.height;
                    minImageTransferGranularity["depth"] = amVK_2D_GPUs_QFAMs[k][i].minImageTransferGranularity.depth;

                QFAM_i["minImageTransferGranularity"] = minImageTransferGranularity;

                std::string index_id  = "[QueueFamily " + std::to_string(i) + "]";
                 QFAM_Array[index_id] = QFAM_i;
            }

            GPU_k["Memory Address"] = toSTR(amVK_1D_GPUs[k]);
            GPU_k["vkGetPhysicalDeviceQueueFamilyProperties()"] = QFAM_Array;

        vkEnumeratePhysicalDevices["[GPU " + std::to_string(k) + "]"] = GPU_k;
    }
    root["vkEnumeratePhysicalDevices"] = vkEnumeratePhysicalDevices;
    
    // Write to file
    std::ofstream file("data.json");
    file << root.dump(4); // Indent with 4 spaces
}