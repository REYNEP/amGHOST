#include "amVK_GPUProps.hh"
#include "amVK_InstanceProps.hh"
#include "amVK_log.hh"

void amVK_GPUProps::GetPhysicalDeviceQueueFamilyProperties(void) {
    // ------------------------- amVK_1D_GPUs_QFAMs ----------------------------
        uint32_t queueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(vk_PhysicalDevice, &queueFamilyCount, nullptr);

        amVK_1D_GPUs_QFAMs.n    = queueFamilyCount;
        amVK_1D_GPUs_QFAMs.data = new VkQueueFamilyProperties[queueFamilyCount];
            vkGetPhysicalDeviceQueueFamilyProperties(vk_PhysicalDevice, &amVK_1D_GPUs_QFAMs.n, amVK_1D_GPUs_QFAMs.data);
    // ------------------------- amVK_1D_GPUs_QFAMs ----------------------------

    amVK_DONE("vkGetPhysicalDeviceQueueFamilyProperties()" << " 😄");
    this->called_GetPhysicalDeviceQueueFamilyProperties = true;
}

void amVK_GPUProps::EnumerateDeviceExtensionProperties(void) {
    // ------------------------- amVK_1D_GPUs_EXTs -----------------------------
        uint32_t extPropertyCount = 0;
            // [implicit valid usage]:- must be 0     [if 3rd-param = nullptr]
            VkResult return_code = vkEnumerateDeviceExtensionProperties(vk_PhysicalDevice, nullptr, &extPropertyCount, nullptr);
            amVK_RC_silent_check( "vkEnumerateDeviceExtensionProperties()" );

        amVK_1D_GPUs_EXTs.n = extPropertyCount;
        amVK_1D_GPUs_EXTs.data = new VkExtensionProperties[extPropertyCount];
                     return_code = vkEnumerateDeviceExtensionProperties(vk_PhysicalDevice, nullptr, &amVK_1D_GPUs_EXTs.n, amVK_1D_GPUs_EXTs.data);
            amVK_return_code_log( "vkEnumerateDeviceExtensionProperties()" );
    // ------------------------- amVK_1D_GPUs_EXTs -----------------------------

    amVK_DONE("vkEnumerateDeviceExtensionProperties()" << " 😄");
    this->called_EnumerateDeviceExtensionProperties = true;
}







void amVK_GPUProps::GetPhysicalDeviceFeatures(void) {
                  vkGetPhysicalDeviceFeatures(this->vk_PhysicalDevice, &this->Features);
             called_GetPhysicalDeviceFeatures = true;
}
void amVK_GPUProps::GetPhysicalDeviceMemoryProperties(void) {
                  vkGetPhysicalDeviceMemoryProperties(this->vk_PhysicalDevice, &this->MEMProps);
             called_GetPhysicalDeviceMemoryProperties = true;
}






/*

.___  ___.  _______ .___  ___.   ______   .______     ____    ____ 
|   \/   | |   ____||   \/   |  /  __  \  |   _  \    \   \  /   / 
|  \  /  | |  |__   |  \  /  | |  |  |  | |  |_)  |    \   \/   /  
|  |\/|  | |   __|  |  |\/|  | |  |  |  | |      /      \_    _/   
|  |  |  | |  |____ |  |  |  | |  `--'  | |  |\  \----.   |  |     
|__|  |__| |_______||__|  |__|  \______/  | _| `._____|   |__|     
                                                                   

 */
void amVK_GPUProps::REY_CategorizeMemoryHeaps(void) {
    if (!this->called_GetPhysicalDeviceMemoryProperties) {
                this->GetPhysicalDeviceMemoryProperties();
    }

    // ------------------------- VRAM ----------------------------
        REY_Array<bool>       isVRAM;
            REY_Array_RESERVE(isVRAM, this->MEMProps.memoryHeapCount, false);

        REY_Array_LOOP(isVRAM, k) {
            if (MEMProps.memoryHeaps[k].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) {
                isVRAM[k] = true;
            }
        }

        /** Double Checking. VkMemoryType also has a VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT flag */
        for(int k = 0; k < MEMProps.memoryTypeCount; k++) {
            if (MEMProps.memoryTypes[k].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) {
                if (isVRAM[MEMProps.memoryTypes[k].heapIndex] == false) {
                    isVRAM[MEMProps.memoryTypes[k].heapIndex] = true;

                    // VulkanSpecs does specify
                    // This property will be set if and only if the memory type belongs to a heap with the VK_MEMORY_HEAP_DEVICE_LOCAL_BIT set.
                    // https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkMemoryPropertyFlagBits.html

                    REY_LOG_EX("MEMProps.memoryHeaps[" << MEMProps.memoryTypes[k].heapIndex << "] did not have VK_MEMORY_HEAP_DEVICE_LOCAL_BIT flagged.\n"
                            << "MEMProps.memoryTypes[" << k                                 << "] had      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT flagged 😵‍💫");
                }
            }
        }

        #define MEMTYPE(x)         MEMProps.memoryTypes[x]
        #define MEMTYPE_FLAGs(x)   MEMProps.memoryTypes[x].propertyFlags
        #define MEMTYPE_SIZE(x)    MEMProps.memoryHeaps[MEMProps.memoryTypes[x].heapIndex].size
        #define MEMHEAP_SIZE(x)    MEMProps.memoryHeaps[x].size
        #define MEMTYPE_HEAP_ID(x) MEMProps.memoryTypes[x].heapIndex

        uint32_t biggestVRAM = 0;
        REY_Array_LOOP(isVRAM, k) {
            if (isVRAM[k]) {
                biggestVRAM = k;
                break;
            }
        }
        REY_Array_LOOP(isVRAM, k) {
            if (isVRAM[k]) {
                if (MEMHEAP_SIZE(k) > MEMHEAP_SIZE(biggestVRAM)) {
                    biggestVRAM = k;
                }
            }
        }
                 this->MEMHeapID.VRAM  = biggestVRAM;
                this->MEMHeapPTR.VRAM = &MEMProps.memoryHeaps[biggestVRAM];
    // ------------------------- VRAM ----------------------------


    // ------------------------- RAM_SharedWith_GPU ----------------------------
        REY_Array<bool>       isRAM;  // We are gonna use the short form. But VULKAN Wouldn't have reported it, if it wasn't RAM_SharedWith_GPU
            REY_Array_RESERVE(isRAM, this->MEMProps.memoryHeapCount, false);

        REY_Array_LOOP(isRAM, k) {
            if (!(MEMProps.memoryHeaps[k].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)) {
                isRAM[k] = true;
            }
        }

        uint32_t biggestRAM = 0;
        REY_Array_LOOP(isRAM, k) {
            if (isRAM[k]) {
                biggestRAM = k;
                break;
            }
        }
        REY_Array_LOOP(isRAM, k) {
            if (isRAM[k]) {
                if (MEMHEAP_SIZE(k) > MEMHEAP_SIZE(biggestRAM)) {
                    biggestRAM = k;
                }
            }
        }
                this->MEMHeapID. RAM_SharedWith_GPU = biggestRAM;
                this->MEMHeapPTR.RAM_SharedWith_GPU = &MEMProps.memoryHeaps[biggestRAM];
    // ------------------------- RAM_SharedWith_GPU ----------------------------


    // ------------------------- VRAM_SharedWith_CPU ----------------------------
        REY_Array<bool>       isCPUCoherent_but_NotCached;
            REY_Array_RESERVE(isCPUCoherent_but_NotCached, this->MEMProps.memoryHeapCount, false);

        for(int k = 0; k < MEMProps.memoryTypeCount; k++) {
            if     (  MEMTYPE_FLAGs(k) & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {
                if (!(MEMTYPE_FLAGs(k) & VK_MEMORY_PROPERTY_HOST_CACHED_BIT)) {
                    isCPUCoherent_but_NotCached[MEMProps.memoryTypes[k].heapIndex] = true;
                }
            }
        }

        uint32_t biggest_VRAM_SharedWith_CPU = 0;
        REY_Array_LOOP(isVRAM, k) {
            if (isVRAM[k] && isCPUCoherent_but_NotCached[k]) {
                biggest_VRAM_SharedWith_CPU = k;
                break;
            }
        }
        REY_Array_LOOP(isVRAM, k) {
            if (isVRAM[k] && isCPUCoherent_but_NotCached[k]) {
                if (MEMHEAP_SIZE(k) > MEMHEAP_SIZE(biggest_VRAM_SharedWith_CPU)) {
                    biggest_VRAM_SharedWith_CPU = k;
                }
            }
        }
                this->MEMHeapID. VRAM_SharedWith_CPU = biggest_VRAM_SharedWith_CPU;
                this->MEMHeapPTR.VRAM_SharedWith_CPU = &MEMProps.memoryHeaps[biggest_VRAM_SharedWith_CPU];
    // ------------------------- VRAM_SharedWith_CPU ----------------------------

    // ------------------------- CPU_GPU_Synced ----------------------------
        REY_Array<bool> isSynced;
            REY_Array_RESERVE(isSynced, this->MEMProps.memoryHeapCount, false);

        for(int k = 0; k < MEMProps.memoryTypeCount; k++) {
            if (MEMTYPE_FLAGs(k) & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {
                isSynced[MEMProps.memoryTypes[k].heapIndex] = true;
            }
        }
        uint32_t biggest_Synced = 0;
        REY_Array_LOOP(isVRAM, k) {
            if (isSynced[k]) {
                biggest_Synced = k;
                break;
            }
        }
        REY_Array_LOOP(isVRAM, k) {
            if (isSynced[k]) {
                if (MEMHEAP_SIZE(k) > MEMHEAP_SIZE(biggest_Synced)) {
                    biggest_Synced = k;
                }
            }
        }
        this->MEMHeapID. CPU_GPU_Synced = biggest_Synced;
        this->MEMHeapPTR.CPU_GPU_Synced = &MEMProps.memoryHeaps[biggest_Synced];

        uint32_t biggest_Synced_Type = 0;
        for (int k = 0; k < MEMProps.memoryTypeCount; k++) {
            if (MEMTYPE_FLAGs(k) & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {
                biggest_Synced_Type = k;
                break;
            }
        }
        for (int k = 0; k < MEMProps.memoryTypeCount; k++) {
            if (MEMTYPE_FLAGs(k) & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {
                if (MEMTYPE_SIZE(k) > MEMTYPE_SIZE(biggest_Synced_Type)) {
                    biggest_Synced_Type = k;
                }
                /** [F1][if connected HEAP has a COHERENT+CACHED variant ---> AutoSelect That] */
                else if (MEMTYPE_HEAP_ID(k) == MEMTYPE_HEAP_ID(biggest_Synced_Type)) {
                    if (MEMTYPE_FLAGs(k) & VK_MEMORY_PROPERTY_HOST_CACHED_BIT) {
                        biggest_Synced_Type = k;
                    }
                }
            }
        }
                 this->MEMTypeID.CPU_GPU_Synced = biggest_Synced_Type;
    // ------------------------- CPU_GPU_Synced ----------------------------

    // ------------------------- CPU_GPU_Synced_Cached ----------------------------
        uint32_t biggest_Synced_Cached_Type = 0;
        for (int k = 0; k < MEMProps.memoryTypeCount; k++) {
            if (MEMTYPE_FLAGs(k) & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {
                if (MEMTYPE_FLAGs(k) & VK_MEMORY_PROPERTY_HOST_CACHED_BIT) {
                    biggest_Synced_Cached_Type = k;
                    break;
                }
            }
        }
        for (int k = 0; k < MEMProps.memoryTypeCount; k++) {
            if (MEMTYPE_FLAGs(k) & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {
                if (MEMTYPE_FLAGs(k) & VK_MEMORY_PROPERTY_HOST_CACHED_BIT) {
                    if (MEMTYPE_SIZE(k) > MEMTYPE_SIZE(biggest_Synced_Cached_Type)) {
                        biggest_Synced_Cached_Type = k;
                    }
                }
            }
        }
                 this->MEMTypeID.CPU_GPU_Synced_Cached = biggest_Synced_Cached_Type;
    // ------------------------- CPU_GPU_Synced_Cached ----------------------------

    isVRAM.free();
    isRAM.free();
    isSynced.free();
    isCPUCoherent_but_NotCached.free();
    this->called_REY_CategorizeMemoryHeaps = true;
}

/*

  ______      _______    ___      .___  ___. 
 /  __  \    |   ____|  /   \     |   \/   | 
|  |  |  |   |  |__    /  ^  \    |  \  /  | 
|  |  |  |   |   __|  /  /_\  \   |  |\/|  | 
|  `--'  '--.|  |    /  _____  \  |  |  |  | 
 \_____\_____\__|   /__/     \__\ |__|  |__| 
                                             

*/
void amVK_GPUProps::REY_CategorizeQueueFamilies(void) {
    if (!this->called_GetPhysicalDeviceQueueFamilyProperties) {
                this->GetPhysicalDeviceQueueFamilyProperties();
    }

    REY_Array_LOOP(amVK_1D_GPUs_QFAMs, k) {
        if (amVK_1D_GPUs_QFAMs[k].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            this->QFamID.Graphics = k;
            break;
        }
    }
    REY_Array_LOOP(amVK_1D_GPUs_QFAMs, k) {
        if (amVK_1D_GPUs_QFAMs[k].queueFlags & VK_QUEUE_VIDEO_ENCODE_BIT_KHR) {
            this->QFamID.VideoEncode = k;
            break;
        }
    }
    REY_Array_LOOP(amVK_1D_GPUs_QFAMs, k) {
        if (amVK_1D_GPUs_QFAMs[k].queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR) {
            this->QFamID.VideoDecode = k;
            break;
        }
    }
    REY_Array_LOOP(amVK_1D_GPUs_QFAMs, k) {
        if (amVK_1D_GPUs_QFAMs[k].queueFlags & VK_QUEUE_COMPUTE_BIT) {
            this->QFamID.Compute = k;
            break;
        }
    }
    REY_Array_LOOP(amVK_1D_GPUs_QFAMs, k) {
        if (amVK_1D_GPUs_QFAMs[k].queueFlags & VK_QUEUE_TRANSFER_BIT) {
            this->QFamID.Transfer = k;
            break;
        }
    }
    REY_Array_LOOP(amVK_1D_GPUs_QFAMs, k) {
        if (amVK_1D_GPUs_QFAMs[k].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) {
            this->QFamID.SparseBinding = k;
            break;
        }
    }
}
uint32_t amVK_GPUProps::ChooseAQueueFamily(VkQueueFlags p_flagBits) {
    if (!this->called_GetPhysicalDeviceQueueFamilyProperties) {
                this->GetPhysicalDeviceQueueFamilyProperties();
    }
    REY_Array_LOOP(amVK_1D_GPUs_QFAMs, k) {
        if (amVK_1D_GPUs_QFAMs[k].queueFlags & p_flagBits) {
            return k;
        }
    }

    return amVK_QueueFamily_NOT_FOUND;
}

/*

 __________   ___ .___________.
|   ____\  \ /  / |           |
|  |__   \  V  /  `---|  |----`
|   __|   >   <       |  |     
|  |____ /  .  \      |  |     
|_______/__/ \__\     |__|     
                               

*/
#include <cstring>
bool amVK_GPUProps::isExtensionAvailable(const char* extName) {
    if (!this->called_EnumerateDeviceExtensionProperties) {
                this->EnumerateDeviceExtensionProperties();
    }
    REY_Array_LOOP(amVK_1D_GPUs_EXTs, k) {
            if (strcmp(amVK_1D_GPUs_EXTs[k].extensionName, extName) == 0) {
                return true;
            }
        }

    return false;
}

/*

  ______ .___________.  ______   .______      
 /      ||           | /  __  \  |   _  \     
|  ,----'`---|  |----`|  |  |  | |  |_)  |    
|  |         |  |     |  |  |  | |      /     
|  `----.    |  |     |  `--'  | |  |\  \----.
 \______|    |__|      \______/  | _| `._____|
                                              

 */
amVK_GPUProps::amVK_GPUProps(VkPhysicalDevice PD, amVK_GPU_Index ID) {
    amVK_check_called_EnumeratePhysicalDevices();
    this->vk_PhysicalDevice  = PD;
    this->ID = ID;
}