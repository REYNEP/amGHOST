#include "amVK_Instance.hh"

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
void amVK_Instance::ExportJSON(void) {
    nlohmann::ordered_json root;
    nlohmann::ordered_json vkEnumeratePhysicalDevices  = nlohmann::ordered_json::object();
                    
    for (int k = 0, lim = amVK_GPU_List.n; k < lim; k++) {
        nlohmann::ordered_json GPU_k = nlohmann::ordered_json::object();

            nlohmann::ordered_json QFAM_Array = nlohmann::ordered_json::object(); 

            for (int i = 0, lim = amVK_2D_GPUs_QFAMs[k].n; i < lim; i++) {
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

                std::string index_id  = "QueueFamily" + std::to_string(i) + "_Properties";
                QFAM_Array[index_id] = QFAM_i;
            }

            GPU_k["Memory Address"] = toSTR(amVK_GPU_List[k]);
            GPU_k["vkGetPhysicalDeviceQueueFamilyProperties()"] = QFAM_Array;

        vkEnumeratePhysicalDevices["[GPU " + std::to_string(k) + "]"] = GPU_k;
    }

    root["vkEnumeratePhysicalDevices"] = vkEnumeratePhysicalDevices;
    
    // Write to file
    std::ofstream file("data.json");
    file << root.dump(4); // Indent with 4 spaces
}