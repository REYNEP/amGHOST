#pragma once
#include <vulkan/vulkan.h>
#include "REY_Utils.hh"

/**
 * Rule #1:- This file cannot have any reference to amVK_Instance. Because that class includes this before declaration
 * Rule #2:- Any Function Implementation that is Intuitive (from the perspective of a beginner) 
 *              ==> Does not have to be implemented in the header
 *              ==> it should rather be inside `amVK.cpp`
 * 
 * Ques #1:- Does this class need to be a SingleTon? -> Kinda, no. But we don't got any problems even if it iss.... yk
 */
class amVK_InstanceProps {
  public:
    static inline    VkInstance  s_vk   = nullptr;
  public:
    static inline bool called_EnumeratePhysicalDevices = false;
    static inline bool called_GetPhysicalDeviceQueueFamilyProperties = false;

    #define amVK_QueueFamily_NOT_FOUND    0xFFFFFFFF
    #define amVK_PhysicalDevice_NOT_FOUND 0xFFFFFFFF
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
  public:
    static inline REY_Array<VkPhysicalDevice>       s_HardwareGPU_List;
        // This doesn't allocate any memory
    #define amVK_GPU_List         amVK_InstanceProps::s_HardwareGPU_List
    #define amVK_Enumerated_GPUs  amVK_InstanceProps::s_HardwareGPU_List

    static                     void EnumeratePhysicalDevices(void);
    static inline VkPhysicalDevice GetARandomPhysicalDevice(void) {
        return s_HardwareGPU_List[0];
    }

    typedef uint32_t   PD_Index;
    static inline      PD_Index GetARandomPhysicalDevice_amVK_Index(void) {
        return 0;
    }
        // Linear Search
    static amVK_InstanceProps::PD_Index VkPhysicalDevice_2_amVK_Index(VkPhysicalDevice PDevice);



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
  public:
    static inline REY_Array<REY_Array<VkQueueFamilyProperties>>   s_HardwareGPU_QFamProps_List2D;
    #define amVK_2D_QFAM_PROPs                        amVK_InstanceProps::s_HardwareGPU_QFamProps_List2D

    static void GetPhysicalDeviceQueueFamilyProperties(void);

    /** 
     * @param ID:- Use:- `amVK_InstanceProps::VkPhysicalDevice_2_amVK_Index()` if you wanna pass in `VkPhysicalDevice` 
     * @returns `VkDeviceQCI.queueFamilyIndex` to be used
     */
    static inline uint32_t ChooseAQueueFamily_for_GRAPHICS(amVK_InstanceProps::PD_Index GPU_k = 0) {
        return amVK_InstanceProps::ChooseAQueueFamily(VK_QUEUE_GRAPHICS_BIT, ID);
    }
    static        uint32_t ChooseAQueueFamily(VkQueueFlags p_flagBits, amVK_InstanceProps::PD_Index GPU_k = 0);
    
  /*
   * Export/Visualization Stuffs
   */
  public:
    static void ExportYAML(void) {
        amVK_InstanceProps *P = new amVK_InstanceProps();
        P->_ExportYAML();
            // ryml causes bugs if it has like static shits
    }
    void _ExportYAML(void);
    static void ExportJSON(void);
    static void Export_yyJSON(void);
};