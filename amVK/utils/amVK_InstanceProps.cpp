#include "amVK_InstanceProps.hh"
#include "amVK_log.hh"

// 1. NEXT:-
// 2. PREV:-
// 3. DEPENDENCY:- [AutoCall]
// 4. CALLS:- 

/**
 *  OUT:- `amVK_1D_GPUs`
 * PREV:- `amVK_Instance::CreateInstance()`
 */

#include <new>
void amVK_InstanceProps::EnumeratePhysicalDevices(VkInstance vk_Instance) 
{
    // ---------------------------- amVK_1D_GPUs -------------------------------
    uint32_t deviceCount = 0;     
        // [implicit valid usage]:- must be 0     [if 3rd-param = nullptr]

        vkEnumeratePhysicalDevices(vk_Instance, &deviceCount, nullptr);
            // This function is 'output-ing into' deviceCount

    REY_Array<VkPhysicalDevice> TMP;
    TMP.reserve(deviceCount);

        VkResult return_code = vkEnumeratePhysicalDevices(vk_Instance, &TMP.MAL, TMP.data);
        amVK_return_code_log( "vkEnumeratePhysicalDevices()" );
    // ---------------------------- amVK_1D_GPUs -------------------------------

    amVK_InstanceProps::called_EnumeratePhysicalDevices = true;

        amVK_1D_GPUs.malloc(TMP.MAL);

    REY_Array_LOOP(TMP, k) {
        new (&amVK_1D_GPUs.data[k]) amVK_GPUProps(TMP[k], k);
    }
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

    amVK_1D_InstanceEXTs.MAL  = extCount;
    amVK_1D_InstanceEXTs.data = new VkExtensionProperties[extCount];

                 return_code = vkEnumerateInstanceExtensionProperties(nullptr, &amVK_1D_InstanceEXTs.MAL, amVK_1D_InstanceEXTs.data);
        amVK_return_code_log( "vkEnumerateInstanceExtensionProperties()" );
    // ------------------------ amVK_1D_InstanceEXTs ---------------------------

    amVK_InstanceProps::called_EnumerateInstanceExtensions = true;
}

/**
 *  OUT:- amVK_1D_InstanceLayers
 * PREV:- No Dependency 😄
 */
void amVK_InstanceProps::EnumerateInstanceLayerProperties(void) 
{
    // ------------------------ amVK_1D_InstanceLayers ---------------------------
    uint32_t layerCount = 0;     

        VkResult return_code = vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        amVK_RC_silent_check( "vkEnumerateInstanceLayerProperties()" );

    amVK_1D_InstanceLayers.MAL    = layerCount;
    amVK_1D_InstanceLayers.data = new VkLayerProperties[layerCount];

                 return_code = vkEnumerateInstanceLayerProperties(&amVK_1D_InstanceLayers.MAL, amVK_1D_InstanceLayers.data);
        amVK_return_code_log( "vkEnumerateInstanceLayerProperties()" );
    // ------------------------ amVK_1D_InstanceLayers ---------------------------

    amVK_InstanceProps::called_EnumerateInstanceLayerProperties = true;
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
/** Call: `EnumeratePhysicalDevices();` Before this function */
amVK_GPUProps*           amVK_InstanceProps::GetARandom_GPU(void) {
    amVK_check_called_EnumeratePhysicalDevices();
    return &amVK_1D_GPUs[amVK_InstanceProps::GetARandom_GPU_amVK_Index()]; 
}
/** LinearSearch */
amVK_GPU_Index amVK_InstanceProps::VkPhysicalDevice_2_amVK_GPU_Index(VkPhysicalDevice PDevice) {
    amVK_check_called_EnumeratePhysicalDevices();

    amVK_LOOP_GPUs(k) {
        if (amVK_1D_GPUs[k].vk_PhysicalDevice == PDevice) {
            return k;
        }
    }

    REY_LOG_EX("amVK_PhysicalDevice_NOT_FOUND:- " << PDevice);
    if (called_EnumeratePhysicalDevices) {
        REY_LOG("But yes, amVK_InstanceProps::EnumeratePhysicalDevices() have been called 🤔");
    }
    return amVK_PhysicalDevice_NOT_FOUND;
}
amVK_GPUProps* amVK_InstanceProps::Get_GPUProps(VkPhysicalDevice PDevice) {
    return &amVK_1D_GPUs[VkPhysicalDevice_2_amVK_GPU_Index(PDevice)];
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
bool amVK_InstanceProps::isInstanceEXTAvailable(const char *extName) 
{
    amVK_LOOP_IEXTs(k) {
        if (strcmp(amVK_1D_InstanceEXTs[k].extensionName, extName) == 0) {
            return true;
        }
    }

    return false;
}

bool amVK_InstanceProps::isInstanceLayerAvailable(const char *layerName) {
    amVK_LOOP_ILayers(k) {
        if (strcmp(amVK_1D_InstanceLayers[k].layerName, layerName) == 0) {
            return true;
        }
    }

    return false;
}