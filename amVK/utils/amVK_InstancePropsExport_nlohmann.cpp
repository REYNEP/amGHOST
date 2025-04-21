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

#include "amVK_nlohmann.hh"

nlohmann::ordered_json nlohmann_VkPhysicalDeviceFeatures(VkPhysicalDeviceFeatures* PD_Features) {
    nlohmann::ordered_json DICT_Features = nlohmann::ordered_json::object();
        DICT_Features["robustBufferAccess"]                      = PD_Features->robustBufferAccess;
        DICT_Features["fullDrawIndexUint32"]                     = PD_Features->fullDrawIndexUint32;
        DICT_Features["imageCubeArray"]                          = PD_Features->imageCubeArray;
        DICT_Features["independentBlend"]                        = PD_Features->independentBlend;
        DICT_Features["geometryShader"]                          = PD_Features->geometryShader;
        DICT_Features["tessellationShader"]                      = PD_Features->tessellationShader;
        DICT_Features["sampleRateShading"]                       = PD_Features->sampleRateShading;
        DICT_Features["dualSrcBlend"]                            = PD_Features->dualSrcBlend;
        DICT_Features["logicOp"]                                 = PD_Features->logicOp;
        DICT_Features["multiDrawIndirect"]                       = PD_Features->multiDrawIndirect;
        DICT_Features["drawIndirectFirstInstance"]               = PD_Features->drawIndirectFirstInstance;
        DICT_Features["depthClamp"]                              = PD_Features->depthClamp;
        DICT_Features["depthBiasClamp"]                          = PD_Features->depthBiasClamp;
        DICT_Features["fillModeNonSolid"]                        = PD_Features->fillModeNonSolid;
        DICT_Features["depthBounds"]                             = PD_Features->depthBounds;
        DICT_Features["wideLines"]                               = PD_Features->wideLines;
        DICT_Features["largePoints"]                             = PD_Features->largePoints;
        DICT_Features["alphaToOne"]                              = PD_Features->alphaToOne;
        DICT_Features["multiViewport"]                           = PD_Features->multiViewport;
        DICT_Features["samplerAnisotropy"]                       = PD_Features->samplerAnisotropy;
        DICT_Features["textureCompressionETC2"]                  = PD_Features->textureCompressionETC2;
        DICT_Features["textureCompressionASTC_LDR"]              = PD_Features->textureCompressionASTC_LDR;
        DICT_Features["textureCompressionBC"]                    = PD_Features->textureCompressionBC;
        DICT_Features["occlusionQueryPrecise"]                   = PD_Features->occlusionQueryPrecise;
        DICT_Features["pipelineStatisticsQuery"]                 = PD_Features->pipelineStatisticsQuery;
        DICT_Features["vertexPipelineStoresAndAtomics"]          = PD_Features->vertexPipelineStoresAndAtomics;
        DICT_Features["fragmentStoresAndAtomics"]                = PD_Features->fragmentStoresAndAtomics;
        DICT_Features["shaderTessellationAndGeometryPointSize"]  = PD_Features->shaderTessellationAndGeometryPointSize;
        DICT_Features["shaderImageGatherExtended"]               = PD_Features->shaderImageGatherExtended;
        DICT_Features["shaderStorageImageExtendedFormats"]       = PD_Features->shaderStorageImageExtendedFormats;
        DICT_Features["shaderStorageImageMultisample"]           = PD_Features->shaderStorageImageMultisample;
        DICT_Features["shaderStorageImageReadWithoutFormat"]     = PD_Features->shaderStorageImageReadWithoutFormat;
        DICT_Features["shaderStorageImageWriteWithoutFormat"]    = PD_Features->shaderStorageImageWriteWithoutFormat;
        DICT_Features["shaderUniformBufferArrayDynamicIndexing"] = PD_Features->shaderUniformBufferArrayDynamicIndexing;
        DICT_Features["shaderSampledImageArrayDynamicIndexing"]  = PD_Features->shaderSampledImageArrayDynamicIndexing;
        DICT_Features["shaderStorageBufferArrayDynamicIndexing"] = PD_Features->shaderStorageBufferArrayDynamicIndexing;
        DICT_Features["shaderStorageImageArrayDynamicIndexing"]  = PD_Features->shaderStorageImageArrayDynamicIndexing;
        DICT_Features["shaderClipDistance"]                      = PD_Features->shaderClipDistance;
        DICT_Features["shaderCullDistance"]                      = PD_Features->shaderCullDistance;
        DICT_Features["shaderFloat64"]                           = PD_Features->shaderFloat64;
        DICT_Features["shaderInt64"]                             = PD_Features->shaderInt64;
        DICT_Features["shaderInt16"]                             = PD_Features->shaderInt16;
        DICT_Features["shaderResourceResidency"]                 = PD_Features->shaderResourceResidency;
        DICT_Features["shaderResourceMinLod"]                    = PD_Features->shaderResourceMinLod;
        DICT_Features["sparseBinding"]                           = PD_Features->sparseBinding;
        DICT_Features["sparseResidencyBuffer"]                   = PD_Features->sparseResidencyBuffer;
        DICT_Features["sparseResidencyImage2D"]                  = PD_Features->sparseResidencyImage2D;
        DICT_Features["sparseResidencyImage3D"]                  = PD_Features->sparseResidencyImage3D;
        DICT_Features["sparseResidency2Samples"]                 = PD_Features->sparseResidency2Samples;
        DICT_Features["sparseResidency4Samples"]                 = PD_Features->sparseResidency4Samples;
        DICT_Features["sparseResidency8Samples"]                 = PD_Features->sparseResidency8Samples;
        DICT_Features["sparseResidency16Samples"]                = PD_Features->sparseResidency16Samples;
        DICT_Features["sparseResidencyAliased"]                  = PD_Features->sparseResidencyAliased;
        DICT_Features["variableMultisampleRate"]                 = PD_Features->variableMultisampleRate;
        DICT_Features["inheritedQueries"]                        = PD_Features->inheritedQueries;
    return DICT_Features;
}

nlohmann::ordered_json nlohmann_VkMemoryHeap(VkMemoryHeap* MEMHeap) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();
        dict["size"] = MEMHeap->size;
            std::vector<std::string> MHF = vulkan_memoryHeapFlags_Names(MEMHeap->flags);
        dict["flags ["                   +               std::to_string(MEMHeap->flags) + "]"] = MHF;

    return dict;
}
nlohmann::ordered_json nlohmann_Array_VkMemoryHeap(REY_Array<VkMemoryHeap> MEMHeaps) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();

    REY_Array_LOOP(MEMHeaps, i) {
        dict["[MemoryHeap " + std::to_string(i) + "]"] = nlohmann_VkMemoryHeap(&MEMHeaps[i]);
    }

    return dict;
}

nlohmann::ordered_json nlohmann_VkMemoryType(VkMemoryType* MEMType) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();
        dict["heapIndex"] = MEMType->heapIndex;
            std::vector<std::string> MHF = vulkan_memoryPropertyFlags_Names(MEMType->propertyFlags);
        dict["propertyFlags ["                +              std::to_string(MEMType->propertyFlags) + "]"] = MHF;

    return dict;
}
nlohmann::ordered_json nlohmann_Array_VkMemoryType(REY_Array<VkMemoryType> MEMTypes) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();

    REY_Array_LOOP(MEMTypes, i) {
        dict["[MemoryType " + std::to_string(i) + "]"] = nlohmann_VkMemoryType(&MEMTypes[i]);
    }

    return dict;
}

nlohmann::ordered_json nlohmann_VkPhysicalDeviceMemoryProperties(VkPhysicalDeviceMemoryProperties* MEMProps) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();
        dict["memoryTypeCount"] = MEMProps->memoryTypeCount;
        dict["memoryHeapCount"] = MEMProps->memoryHeapCount;
        dict["memoryHeaps"] = nlohmann_Array_VkMemoryHeap(REY_Array<VkMemoryHeap>(MEMProps->memoryHeaps, MEMProps->memoryHeapCount));
        dict["memoryTypes"] = nlohmann_Array_VkMemoryType(REY_Array<VkMemoryType>(MEMProps->memoryTypes, MEMProps->memoryTypeCount));
    return dict;
}
































nlohmann::ordered_json nlohmann_VkQueueFamilyProperties(VkQueueFamilyProperties *QFP) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();
        
        nlohmann::ordered_json qF = vulkan_queueFlags_Names(QFP->queueFlags);
        dict["queueFlags ["        +         std::to_string(QFP->queueFlags) + "]"] = qF;

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
        dict["supportedTransforms ["          +           std::to_string(SCAP->supportedTransforms) + "]"] = sT;

        std::vector<std::string> cT = vulkan_surfaceTransformFlags_Names(SCAP->currentTransform);
        dict["currentTransform ["             +           std::to_string(SCAP->currentTransform) + "]"] = cT;

        std::vector<std::string> cAF = vulkan_compositeAlphaFlags_Names(SCAP->supportedCompositeAlpha);
        dict["supportedCompositeAlpha ["      +          std::to_string(SCAP->supportedCompositeAlpha) + "]"] = cAF;

        std::vector<std::string> iUF = vulkan_imageUsageFlags_Names(SCAP->supportedUsageFlags);
        dict["supportedUsageFlags ["          +      std::to_string(SCAP->supportedUsageFlags) + "]"] = iUF;

    return dict;
}

nlohmann::ordered_json nlohmann_VkSurfaceFormatKHR(VkSurfaceFormatKHR SFMT) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();

        dict["format / imageFormat"] = vulkan_imageFormat_name(SFMT.format);
        dict["colorspace"] =            vulkan_colorSpace_name(SFMT.colorSpace);
    
    return dict;
}

nlohmann::ordered_json nlohmann_Array_VkQueueFamilyProperties(REY_Array<VkQueueFamilyProperties> QFPs) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();

    REY_Array_LOOP(QFPs, i) {
        dict["[QueueFamily " + std::to_string(i) + "]"] = nlohmann_VkQueueFamilyProperties(&QFPs[i]);
    }

    return dict;
}

nlohmann::ordered_json nlohmann_Array_VkExtensionProperties(REY_Array<VkExtensionProperties> EXTP) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();

    REY_Array_LOOP(EXTP, i) {
        std::string value = "specVersion" + std::to_string(EXTP[i].specVersion);
        dict[EXTP[i].extensionName] = value;
    }
    
    return dict;
}

nlohmann::ordered_json nlohmann_Array_VkSurfaceFormatKHR(REY_Array<VkSurfaceFormatKHR> SFMTs) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();

    REY_Array_LOOP(SFMTs, i) {
        dict["[SurfaceFormat " + std::to_string(i) + "]"] = nlohmann_VkSurfaceFormatKHR(SFMTs[i]);
    }

    return dict;
}













#include "amVK_InstanceProps.hh"
nlohmann::ordered_json nlohmann_amVK_GPUProps(amVK_GPUProps *GPUProps) {
    nlohmann::ordered_json GPU_k = nlohmann::ordered_json::object();

        GPU_k["Memory Address"] = toSTR(GPUProps->vk_PhysicalDevice);
        GPU_k["vkGetPhysicalDeviceQueueFamilyProperties()"] = nlohmann_Array_VkQueueFamilyProperties   ( GPUProps->amVK_1D_GPUs_QFAMs);
        GPU_k["vkGetPhysicalDeviceFeatures()"]              = nlohmann_VkPhysicalDeviceFeatures        (&GPUProps->Features);

        nlohmann::ordered_json    nloh_amVK_MemoryHeapIndex = nlohmann::ordered_json::object();
            nloh_amVK_MemoryHeapIndex["VRAM"]                 = GPUProps->MEMHeapID.VRAM;
            nloh_amVK_MemoryHeapIndex["VRAM_SharedWith_CPU"]  = GPUProps->MEMHeapID.VRAM_SharedWith_CPU;
            nloh_amVK_MemoryHeapIndex["RAM_SharedWith_GPU"]   = GPUProps->MEMHeapID.RAM_SharedWith_GPU;
            nloh_amVK_MemoryHeapIndex["CPU_GPU_Synced"]       = GPUProps->MEMHeapID.CPU_GPU_Synced;
        GPU_k["amVK_MemoryHeapIndex"]                       = nloh_amVK_MemoryHeapIndex;
        
        nlohmann::ordered_json    nloh_amVK_MemoryTypeIndex = nlohmann::ordered_json::object();
            nloh_amVK_MemoryTypeIndex["CPU_GPU_Synced"]       = GPUProps->MEMTypeID.CPU_GPU_Synced;
        GPU_k["amVK_MemoryTypeIndex"]                       = nloh_amVK_MemoryTypeIndex;

        GPU_k["vkGetPhysicalDeviceMemoryProperties()"]      = nlohmann_VkPhysicalDeviceMemoryProperties(&GPUProps->MEMProps);
        GPU_k["vkEnumerateDeviceExtensionProperties()"]     = nlohmann_Array_VkExtensionProperties     ( GPUProps->amVK_1D_GPUs_EXTs);

    return GPU_k;
}

nlohmann::ordered_json nlohmann_amVK_1D_GPUs(void) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();
    amVK_check_called_EnumeratePhysicalDevices();

    REY_Array_LOOP(amVK_InstanceProps::amVK_1D_GPUs, k) {
        dict["[GPU " + std::to_string(k) + "]"] = nlohmann_amVK_GPUProps(&amVK_InstanceProps::amVK_1D_GPUs[k]);
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

        nlohmann::ordered_json vkEnumerateInstanceExtensionProperties   = nlohmann::ordered_json::object();
        nlohmann::ordered_json vkCreate_xxx_SurfaceKHR                  = nlohmann::ordered_json::object();

        amVK_LOOP_IEXTs(i) {
            std::string value = "specVersion" + std::to_string(amVK_1D_InstanceEXTs[i].specVersion);
            vkEnumerateInstanceExtensionProperties[amVK_1D_InstanceEXTs[i].extensionName] = value;
        }
    
        /**
        amVK_LOOP_SURFs(m) {
            amVK_SurfaceLinks SurfLinks = amVK_1D_SurfaceLinks[m];
            vkCreate_xxx_SurfaceKHR["[Surface " + std::to_string(m) + "]"] = nlohmann_amVK_SurfaceLinks(SurfLinks);
        }
        */
   
    root["vkEnumerateInstanceExtensionProperties"] = vkEnumerateInstanceExtensionProperties; 
    root["vkCreate_xxx_SurfaceKHR"] = vkCreate_xxx_SurfaceKHR;
    root["vkEnumeratePhysicalDevices"] = nlohmann_amVK_1D_GPUs();
    
    // Write to file
    std::ofstream file("data.json");
    file << root.dump(4); // Indent with 4 spaces
}