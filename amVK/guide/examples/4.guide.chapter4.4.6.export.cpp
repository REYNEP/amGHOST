/**
 __     __          _____               _____ _        _                                _   
 \ \   / /         / ____|             / ____| |      (_)        /\                    | |  
  \ \_/ /__  _   _| |     __ _ _ __   | (___ | |_ _ __ _ _ __   /  \   _ __   __ _ _ __| |_ 
   \   / _ \| | | | |    / _` | '_ \   \___ \| __| '__| | '_ \ / /\ \ | '_ \ / _` | '__| __|
    | | (_) | |_| | |___| (_| | | | |  ____) | |_| |  | | |_) / ____ \| |_) | (_| | |  | |_ 
    |_|\___/ \__,_|\_____\__,_|_| |_| |_____/ \__|_|  |_| .__/_/    \_\ .__/ \__,_|_|   \__|
                                  ______                | |           | |                   
                                 |______|               |_|           |_|                   
 */

// nlohmann - Handles String Stuffs automatically
#include <nlohmann/json.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
std::string toSTR(void* ptr) {
    std::stringstream ss;
    ss << ptr;
    return ss.str();
}

#include <vulkan/vulkan.h>
#include "amVK_Enum2String.hh"

nlohmann::ordered_json nlohmann_VkQueueFamilyProperties(VkQueueFamilyProperties *QFP) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();
        
        nlohmann::ordered_json qF = vulkan_queueFlags_Names(QFP->queueFlags);
                qF.push_back(std::string("VkQueueFlagBits:- ") + std::to_string(QFP->queueFlags));
        dict["queueFlags"] = qF;

        dict["queueCount"] = QFP->queueCount;
        dict["timestampValidBits"] = QFP->timestampValidBits;

        nlohmann::ordered_json mITG = nlohmann::json::object();
            mITG["width"] = QFP->minImageTransferGranularity.width;
            mITG["height"] = QFP->minImageTransferGranularity.height;
            mITG["depth"] = QFP->minImageTransferGranularity.depth;

        dict["minImageTransferGranularity"] = mITG;

    return dict;
}

nlohmann::ordered_json nlohmann_VkSurfaceCapabilitiesKHR(VkSurfaceCapabilitiesKHR *SCAP) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();

        dict["minImageCount"] = SCAP->minImageCount;
        dict["maxImageCount"] = SCAP->maxImageCount;
        
        nlohmann::ordered_json cE = nlohmann::json::object();
            cE["width"] = SCAP->currentExtent.width;
            cE["height"] = SCAP->currentExtent.height;
        dict["currentExtent"] = cE;

        nlohmann::ordered_json minIE = nlohmann::json::object();
            minIE["width"] = SCAP->minImageExtent.width;
            minIE["height"] = SCAP->minImageExtent.height;
        dict["minImageExtent"] = minIE;

        nlohmann::ordered_json maxIE = nlohmann::json::object();
            maxIE["width"] = SCAP->maxImageExtent.width;
            maxIE["height"] = SCAP->maxImageExtent.height;
        dict["maxImageExtent"] = maxIE;

        dict["maxImageArrayLayers"] = SCAP->maxImageArrayLayers;

        std::vector<std::string> sT = vulkan_surfaceTransformFlags_Names(SCAP->supportedTransforms);
            sT.push_back(std::string("VkSurfaceTransformFlagsKHR:- ") + std::to_string(SCAP->supportedTransforms));
        dict["supportedTransforms"] = sT;

        std::vector<std::string> cT = vulkan_surfaceTransformFlags_Names(SCAP->currentTransform);
            cT.push_back(std::string("VkSurfaceTransformFlagBitsKHR:- ") + std::to_string(SCAP->currentTransform));
        dict["currentTransform"] = cT;

        std::vector<std::string> cAF = vulkan_compositeAlphaFlags_Names(SCAP->supportedCompositeAlpha);
            cAF.push_back(std::string("VkCompositeAlphaFlagBitsKHR:- ") + std::to_string(SCAP->supportedCompositeAlpha));
        dict["supportedCompositeAlpha"] = cAF;

        std::vector<std::string> iUF = vulkan_imageUsageFlags_Names(SCAP->supportedUsageFlags);
            iUF.push_back(std::string("VkImageUsageFlags:- ") + std::to_string(SCAP->supportedUsageFlags));
        dict["supportedUsageFlags"] = iUF;

    return dict;
}

nlohmann::ordered_json nlohmann_VkSurfaceFormatKHR(VkSurfaceFormatKHR SFMT) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();

        dict["format / imageFormat"] = vulkan_imageFormat_name(SFMT.format);
        dict["colorspace"] = vulkan_colorSpace_name(SFMT.colorSpace);
    
    return dict;
}







/**
 .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------. 
| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |
| |      __      | || | ____    ____ | || | ____   ____  | || |  ___  ____   | || |              | || |   ______     | || |  _______     | || |     ____     | || |   ______     | || |    _______   | |
| |     /  \     | || ||_   \  /   _|| || ||_  _| |_  _| | || | |_  ||_  _|  | || |              | || |  |_   __ \   | || | |_   __ \    | || |   .'    `.   | || |  |_   __ \   | || |   /  ___  |  | |
| |    / /\ \    | || |  |   \/   |  | || |  \ \   / /   | || |   | |_/ /    | || |              | || |    | |__) |  | || |   | |__) |   | || |  /  .--.  \  | || |    | |__) |  | || |  |  (__ \_|  | |
| |   / ____ \   | || |  | |\  /| |  | || |   \ \ / /    | || |   |  __'.    | || |              | || |    |  ___/   | || |   |  __ /    | || |  | |    | |  | || |    |  ___/   | || |   '.___`-.   | |
| | _/ /    \ \_ | || | _| |_\/_| |_ | || |    \ ' /     | || |  _| |  \ \_  | || |              | || |   _| |_      | || |  _| |  \ \_  | || |  \  `--'  /  | || |   _| |_      | || |  |`\____) |  | |
| ||____|  |____|| || ||_____||_____|| || |     \_/      | || | |____||____| | || |   _______    | || |  |_____|     | || | |____| |___| | || |   `.____.'   | || |  |_____|     | || |  |_______.'  | |
| |              | || |              | || |              | || |              | || |  |_______|   | || |              | || |              | || |              | || |              | || |              | |
| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |
 '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' 
 */
#include "amVK_InstanceProps.hh"

nlohmann::ordered_json nlohmann_Array_VkQueueFamilyProperties(REY_Array<VkQueueFamilyProperties> QFPs) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();

    REY_Array_LOOP(QFPs, i) {
        //for (uint32_t i = 0, lim = amVK_2D_GPUs_QFAMs[k].n; i < lim; i++) {
        dict["[QueueFamily " + std::to_string(i) + "]"] = nlohmann_VkQueueFamilyProperties(&QFPs[i]);
    }

    return dict;
}

nlohmann::ordered_json nlohmann_Array_VkSurfaceFormatKHR(REY_Array<VkSurfaceFormatKHR> SURF_FMTs) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();

    REY_Array_LOOP(SURF_FMTs, i) {
        dict["[SurfaceFormat " + std::to_string(i) + "]"] = nlohmann_VkSurfaceFormatKHR(SURF_FMTs[i]);
    }

    return dict;
}

nlohmann::ordered_json nlohmann_amVK_SurfaceInfo(amVK_InstanceProps::SurfaceInfo *SInfo) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();

        dict["Memory Address"] = toSTR(SInfo->S);
    REY_Array_LOOP(amVK_InstanceProps::amVK_1D_GPUs, k) {
        nlohmann::ordered_json GPU_k = nlohmann::ordered_json::object();

            GPU_k["Memory Address"] = toSTR(amVK_InstanceProps::amVK_1D_GPUs[k]);
            GPU_k["vkGetPhysicalDeviceSurfaceFormatsKHR()"] = nlohmann_Array_VkSurfaceFormatKHR(SInfo->amVK_2D_GPUs_ImageFMTs[k]);

            VkSurfaceCapabilitiesKHR *SCAP = &(SInfo->amVK_1D_GPUs_SurfCAP[k]);
            GPU_k["VkSurfaceCapabilitiesKHR"] = nlohmann_VkSurfaceCapabilitiesKHR(SCAP);

        dict["[GPU " + std::to_string(k) + "]"] = GPU_k;
    }

    return dict;
}

nlohmann::ordered_json nlohmann_amVK_GPUInfo(void) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();

    REY_Array_LOOP(amVK_InstanceProps::amVK_1D_GPUs, k) {
        nlohmann::ordered_json GPU_k = nlohmann::ordered_json::object();

            GPU_k["Memory Address"] = toSTR(amVK_InstanceProps::amVK_1D_GPUs[k]);
            GPU_k["vkGetPhysicalDeviceQueueFamilyProperties()"] = nlohmann_Array_VkQueueFamilyProperties(amVK_InstanceProps::amVK_2D_GPUs_QFAMs[k]);

        dict["[GPU " + std::to_string(k) + "]"] = GPU_k;
    }

    return dict;
}













/*

░▒▓████████▓▒░ ░▒▓█▓▒░ ░▒▓███████▓▒░   ░▒▓██████▓▒░  ░▒▓█▓▒░        
░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░        
░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░        
░▒▓██████▓▒░   ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓████████▓▒░ ░▒▓█▓▒░        
░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░        
░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░        
░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓████████▓▒░ 

 * https://quickref.me/json.html
 * ordered_json -> kinda like std::unordered_map
 *              -> i.e. doesn't automatically sort alphabetically
 */
void amVK_InstanceProps::Export_nilohmannJSON(void) {
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
        amVK_InstanceProps::SurfaceInfo *SInfo = &amVK_1D_SurfaceInfos[m];
        vkCreate_xxx_SurfaceKHR["[Surface " + std::to_string(m) + "]"] = nlohmann_amVK_SurfaceInfo(SInfo);
    }
    root["vkCreate_xxx_SurfaceKHR"] = vkCreate_xxx_SurfaceKHR;
    root["vkEnumeratePhysicalDevices"] = nlohmann_amVK_GPUInfo();
    
    // Write to file
    std::ofstream file("data.json");
    file << root.dump(4); // Indent with 4 spaces
}