#include "amVK_Instance.hh"

// 1. NEXT:-
// 2. PREV:-
// 3. DEPENDENCY:- [AutoCall]
// 4. CALLS:- 

/**
 *  OUT:- `amVK_1D_GPUs`
 * PREV:- `amVK_Instance::CreateInstance()`
 */
void amVK_InstanceProps::EnumeratePhysicalDevices(void) 
{
    // ---------------------------- amVK_1D_GPUs -------------------------------
    uint32_t deviceCount = 0;     
        // [implicit valid usage]:- must be 0     [if 3rd-param = nullptr]

        vkEnumeratePhysicalDevices(amVK_Instance::s_vk, &deviceCount, nullptr);
            // This function is 'output-ing into' deviceCount

    amVK_1D_GPUs.n    = deviceCount;
    amVK_1D_GPUs.data = new VkPhysicalDevice[deviceCount];

        VkResult return_code = vkEnumeratePhysicalDevices(amVK_Instance::s_vk, &amVK_1D_GPUs.n, amVK_1D_GPUs.data);
        amVK_return_code_log( "vkEnumeratePhysicalDevices()" );
    // ---------------------------- amVK_1D_GPUs -------------------------------

    amVK_InstanceProps::called_EnumeratePhysicalDevices = true;
}

/**
 *  OUT:- amVK_1D_InstanceEXTs
 * PREV:- No Dependency 😄
 */
void amVK_InstanceProps::EnumerateInstanceExtensions(void) 
{
    // ------------------------ amVK_1D_InstanceEXTs ---------------------------
    uint32_t extCount = 0;     

        VkResult return_code = vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);
        amVK_RC_silent_check( "vkEnumerateInstanceExtensionProperties()" );

    amVK_1D_InstanceEXTs.n    = extCount;
    amVK_1D_InstanceEXTs.data = new VkExtensionProperties[extCount];

                 return_code = vkEnumerateInstanceExtensionProperties(nullptr, &amVK_1D_InstanceEXTs.n, amVK_1D_InstanceEXTs.data);
        amVK_return_code_log( "vkEnumerateInstanceExtensionProperties()" );
    // ------------------------ amVK_1D_InstanceEXTs ---------------------------

    amVK_InstanceProps::called_EnumeratePhysicalDevices = true;
}











/**
 *        OUT:- `amVK_2D_GPUs_QFAMs`
 * DEPENDENCY:- [AutoCall]:- `amVK_InstanceProps::EnumeratePhysicalDevices()` if hasn't been called 
 * 
 * TODO: 
 *   - Make all the Memory Allocation within this function -> in one block of RAM
 *   - HOGA
 */
void amVK_InstanceProps::GetPhysicalDeviceQueueFamilyProperties(void) {
    if (!amVK_InstanceProps::called_EnumeratePhysicalDevices) {
         amVK_InstanceProps::       EnumeratePhysicalDevices();
    }

    amVK_2D_GPUs_QFAMs.reserve(amVK_1D_GPUs.n);
        
    amVK_LOOP_GPUs(k)
    {
        // ------------------------- amVK_2D_GPUs_QFAMs ----------------------------
        REY_Array<VkQueueFamilyProperties> *k_QFamProps = &amVK_2D_GPUs_QFAMs.data[k];

        uint32_t queueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(amVK_1D_GPUs[k], &queueFamilyCount, nullptr);

        k_QFamProps->n = queueFamilyCount;
        k_QFamProps->data = new VkQueueFamilyProperties[queueFamilyCount];
            vkGetPhysicalDeviceQueueFamilyProperties(amVK_1D_GPUs[k], &k_QFamProps->n, k_QFamProps->data);
        // ------------------------- amVK_2D_GPUs_QFAMs ----------------------------
    }

    amVK_DONE("vkGetPhysicalDeviceQueueFamilyProperties()" << " 😄");
    amVK_InstanceProps::called_GetPhysicalDeviceQueueFamilyProperties = true;
}

/**
 *        OUT:- `amVK_2D_GPUs_ImageFMTs`
 * DEPENDENCY:- [AutoCall]:- `amVK_InstanceProps::EnumeratePhysicalDevices()` if hasn't been called 
 */
void amVK_InstanceProps::SurfaceInfo::GetPhysicalDeviceSurfaceInfo(void) {
    if (!amVK_InstanceProps::called_EnumeratePhysicalDevices) {
         amVK_InstanceProps::       EnumeratePhysicalDevices();
    }

    amVK_2D_GPUs_ImageFMTs.reserve(amVK_1D_GPUs.n);
    amVK_1D_GPUs_SurfCAP  .reserve(amVK_1D_GPUs.n);
    
    amVK_LOOP_GPUs(k)
    {
        // ----------------------- amVK_2D_GPUs_ImageFMTs --------------------------
        REY_Array<VkSurfaceFormatKHR> *k_IMG_FMTs = &amVK_2D_GPUs_ImageFMTs[k];

        uint32_t imageFormatCount = 0;
            // [implicit valid usage]:- must be 0     [if 3rd-param = nullptr]
            VkResult return_code = vkGetPhysicalDeviceSurfaceFormatsKHR(amVK_1D_GPUs[k], this->S, &imageFormatCount, nullptr);
            amVK_RC_silent_check( "vkGetPhysicalDeviceSurfaceFormatsKHR()" );

        k_IMG_FMTs->n = imageFormatCount;
        k_IMG_FMTs->data = new VkSurfaceFormatKHR[imageFormatCount];
                     return_code = vkGetPhysicalDeviceSurfaceFormatsKHR(amVK_1D_GPUs[k], this->S, &k_IMG_FMTs->n, k_IMG_FMTs->data);
            amVK_return_code_log( "vkGetPhysicalDeviceSurfaceFormatsKHR()" );
    
        amVK_InstanceProps::SurfaceInfo::called_GetPhysicalDeviceSurfaceFormatsKHR = true;
        // ----------------------- amVK_2D_GPUs_ImageFMTs --------------------------




        // ------------------------ amVK_1D_GPUs_SurfCAP ---------------------------
        VkSurfaceCapabilitiesKHR *k_SURF_CAPs = &amVK_1D_GPUs_SurfCAP[k];

                     return_code = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(amVK_1D_GPUs[k], this->S, k_SURF_CAPs);
            amVK_return_code_log( "vkGetPhysicalDeviceSurfaceCapabilitiesKHR()" );

        amVK_InstanceProps::SurfaceInfo::called_GetPhysicalDeviceSurfaceFormatsKHR = true;
        // ------------------------ amVK_1D_GPUs_SurfCAP ---------------------------
    }
}

void amVK_InstanceProps::EnumerateDeviceExtensionProperties(void) {
    if (!amVK_InstanceProps::called_EnumeratePhysicalDevices) {
         amVK_InstanceProps::       EnumeratePhysicalDevices();
    }

    amVK_2D_GPUs_EXTs     .reserve(amVK_1D_GPUs.n);

    amVK_LOOP_GPUs(k)
    {
        // ------------------------- amVK_2D_GPUs_EXTs -----------------------------
        REY_Array<VkExtensionProperties> *k_GPU_EXTs = &amVK_2D_GPUs_EXTs[k];

        uint32_t extPropertyCount = 0;
            // [implicit valid usage]:- must be 0     [if 3rd-param = nullptr]
            VkResult return_code = vkEnumerateDeviceExtensionProperties(amVK_1D_GPUs[k], nullptr, &extPropertyCount, nullptr);
            amVK_RC_silent_check( "vkEnumerateDeviceExtensionProperties()" );

        k_GPU_EXTs->n = extPropertyCount;
        k_GPU_EXTs->data = new VkExtensionProperties[extPropertyCount];
                     return_code = vkEnumerateDeviceExtensionProperties(amVK_1D_GPUs[k], nullptr, &k_GPU_EXTs->n, k_GPU_EXTs->data);
            amVK_return_code_log( "vkEnumerateDeviceExtensionProperties()" );
    
        amVK_InstanceProps::called_EnumerateDeviceExtensionProperties = true;
        // ------------------------- amVK_2D_GPUs_EXTs -----------------------------
    }
}












/**
                                    _____  _               _           _ _____             _          
     /\                            |  __ \| |             (_)         | |  __ \           (_)         
    /  \   _ __ _ __ __ _ _   _    | |__) | |__  _   _ ___ _  ___ __ _| | |  | | _____   ___  ___ ___ 
   / /\ \ | '__| '__/ _` | | | |   |  ___/| '_ \| | | / __| |/ __/ _` | | |  | |/ _ \ \ / / |/ __/ _ \
  / ____ \| |  | | | (_| | |_| |   | |    | | | | |_| \__ \ | (_| (_| | | |__| |  __/\ V /| | (_|  __/
 /_/    \_\_|  |_|  \__,_|\__, |   |_|    |_| |_|\__, |___/_|\___\__,_|_|_____/ \___| \_/ |_|\___\___|
                           __/ |_____             __/ |                                               
                          |___/______|           |___/                                                
*/

amVK_InstanceProps::PD_Index amVK_InstanceProps::VkPhysicalDevice_2_PD_Index(VkPhysicalDevice PDevice) {
    amVK_LOOP_GPUs(k) {
        if (amVK_1D_GPUs[k] == PDevice) {
            return k;
        }
    }

    return amVK_PhysicalDevice_NOT_FOUND;
}

/**
  ___  _____                                   ____  ______      __  __   _____                     
 |__ \|  __ \   /\                            / __ \|  ____/\   |  \/  | |  __ \                    
    ) | |  | | /  \   _ __ _ __ __ _ _   _   | |  | | |__ /  \  | \  / | | |__) | __ ___  _ __  ___ 
   / /| |  | |/ /\ \ | '__| '__/ _` | | | |  | |  | |  __/ /\ \ | |\/| | |  ___/ '__/ _ \| '_ \/ __|
  / /_| |__| / ____ \| |  | | | (_| | |_| |  | |__| | | / ____ \| |  | | | |   | | | (_) | |_) \__ \
 |____|_____/_/    \_\_|  |_|  \__,_|\__, |   \___\_\_|/_/    \_\_|  |_| |_|   |_|  \___/| .__/|___/
                                      __/ |_____                     ______              | |        
                                     |___/______|                   |______|             |_|        
*/

/** 
 * @param p_flagBits:- can be a mixture of multiple bits. use `|` operator a.k.a 'or' operator, which can join flags together
 * @param ID:- Use:- `amVK_InstanceProps::VkPhysicalDevice_2_PD_Index()` if you wanna pass in `VkPhysicalDevice` 
 * @returns `VkDeviceQCI.queueFamilyIndex` to be used
 */
uint32_t amVK_InstanceProps::ChooseAQueueFamily(VkQueueFlags p_flagBits, amVK_InstanceProps::PD_Index GPU_k) {
    REY_Array<VkQueueFamilyProperties> GPU_k_QFAM_Array = amVK_2D_GPUs_QFAMs[GPU_k];

    amVK_LOOP_QFAMs(GPU_k, i) {
        if (amVK_2D_GPUs_QFAMs[GPU_k][i].queueFlags & p_flagBits) {
            return i;
        }
    }

    return amVK_QueueFamily_NOT_FOUND;
}





/*
                                    ________   _________  
     /\                            |  ____\ \ / /__   __| 
    /  \   _ __ _ __ __ _ _   _    | |__   \ V /   | |___ 
   / /\ \ | '__| '__/ _` | | | |   |  __|   > <    | / __|
  / ____ \| |  | | | (_| | |_| |   | |____ / . \   | \__ \
 /_/    \_\_|  |_|  \__,_|\__, |   |______/_/ \_\  |_|___/
                           __/ |_____                     
                          |___/______|                    
*/
#include <cstring>
bool amVK_InstanceProps::IS_GPU_EXT_Available(amVK_InstanceProps::PD_Index GPU_k, const char *extName) 
{
     amVK_LOOP_GPU_EXTs(GPU_k, i) {
        if (strcmp(amVK_2D_GPUs_EXTs[GPU_k][i].extensionName, extName) == 0) {
            return true;
        }
    }

    return false;
}
bool amVK_InstanceProps::IS_InstanceEXT_Available(const char *extName) 
{
     amVK_LOOP_IEXTs(k) {
        if (strcmp(amVK_1D_InstanceEXTs[k].extensionName, extName) == 0) {
            return true;
        }
    }

    return false;
}

#include <string.h>
/**
 * @param extName:- must be null-terminated string
```
 - DEPENDENCY:- [AutoCall]  `amVK_InstanceProps::EnumerateInstanceExtensions()` 
 -       NEXT:-             `amVK_Instance::CreateInstance()`
```
 */
void amVK_InstanceProps::Add_InstanceEXT_ToEnable(const char* extName) {
    // VK_KHR_surface
    if (!amVK_InstanceProps::called_EnumerateInstanceExtensions) {
            amVK_InstanceProps::EnumerateInstanceExtensions();
    }
    
    if (amVK_InstanceProps::IS_InstanceEXT_Available(extName)) {
        char  *dont_lose = new char[strlen(extName)];
        strcpy(dont_lose, extName);

        REY_ArrayDYN_PUSH_BACK(amVK_1D_InstanceEXTs_Enabled) = dont_lose;

        amVK_Instance::CI.enabledExtensionCount = amVK_1D_InstanceEXTs_Enabled.neXt;
        amVK_Instance::CI.ppEnabledExtensionNames = amVK_1D_InstanceEXTs_Enabled.data;
    }
    else {
        REY_LOG_notfound("Vulkan Instance Extension:- " << extName);
    }
}
void amVK_InstanceProps::Log_InstanceEXTs_Enabled(VkResult ret) {
    if (ret != VK_SUCCESS) {
        REY_LOG_status("vkCreateInstance() failed 😶‍🌫️");
    }
    else {
        REY_LOG_status("         Enabled VULKAN Extensions' Name:- ");
        for (uint32_t k = 0,     lim = amVK_1D_InstanceEXTs_Enabled.n;     k < lim; k++) {
            REY_LOG_status("              | " << amVK_1D_InstanceEXTs_Enabled[k]);
        }
    }
}









/*
                                     _____             __               _____        __          
     /\                             / ____|           / _|             |_   _|      / _|         
    /  \   _ __ _ __ __ _ _   _    | (___  _   _ _ __| |_ __ _  ___ ___  | |  _ __ | |_ ___  ___ 
   / /\ \ | '__| '__/ _` | | | |    \___ \| | | | '__|  _/ _` |/ __/ _ \ | | | '_ \|  _/ _ \/ __|
  / ____ \| |  | | | (_| | |_| |    ____) | |_| | |  | || (_| | (_|  __/_| |_| | | | || (_) \__ \
 /_/    \_\_|  |_|  \__,_|\__, |   |_____/ \__,_|_|  |_| \__,_|\___\___|_____|_| |_|_| \___/|___/
                           __/ |_____                                                            
                          |___/______|                                                           
    
    for each (VkSurfaceKHR)
        for each (GPU)
            LIST IMG_FMTs
*/

/**
 * CALLS:- `GetPhysicalDeviceSurfaceInfo()`
 *  PREV:- `EnumeratePhysicalDevices()`
 */
void amVK_InstanceProps::push_back_VkSurfaceKHR(VkSurfaceKHR S) {
    amVK_InstanceProps::SurfaceInfo S_Props(S);
    S_Props.GetPhysicalDeviceSurfaceInfo();

    amVK_1D_SurfaceInfos.push_back(S_Props);
}