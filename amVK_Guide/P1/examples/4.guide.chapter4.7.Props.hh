#pragma once
#include <vulkan/vulkan.h>
#include "REY_Utils.hh"

/**
 * i don't wanna scatter all the Properties All around my code. So, i'm gonna keep them here 😊
 *   --> Right inside `amVK_InstanceProps` class
 * 
 * Rule #1:- This file cannot have any reference to amVK_Instance. Because that class includes this before declaration
 * Rule #2:- Any Function Implementation that is Intuitive (from the perspective of a beginner) 
 *              ==> Does not have to be implemented in the header
 *              ==> it should rather be inside `amVK.cpp`
 * 
 * Ques #1:- Does this class need to be a SingleTon? -> Kinda, no. But we don't got any problems even if it iss.... yk
 */
class amVK_InstanceProps {
  public:
    static inline bool called_EnumeratePhysicalDevices = false;
    static inline bool called_GetPhysicalDeviceQueueFamilyProperties = false;
    static inline bool called_EnumerateInstanceExtensions = false;
    static inline bool called_EnumerateDeviceExtensionProperties = false;

    #define amVK_QueueFamily_NOT_FOUND    0xFFFFFFFF
    #define amVK_PhysicalDevice_NOT_FOUND 0xFFFFFFFF

    typedef uint32_t                   PD_Index; // VkPhysicalDevice Index -> into -> amVK_1D_GPUs
    #define amVK_GPU_Index amVK_InstanceProps::PD_Index

  public:
    static void EnumeratePhysicalDevices(void);                         // amVK_1D_GPUs
    static       void GetPhysicalDeviceQueueFamilyProperties(void);     // amVK_2D_GPUs_QFAMs
    static void EnumerateInstanceExtensions(void);                      // amVK_1D_InstanceEXTs
    static void EnumerateDeviceExtensionProperties(void);               // amVK_2D_GPUs_EXTs

  public:
    /**
     * VULKAN-EXT:- `VK_KHR_surface`
     *       IMPL:- `amVK_1D_SurfaceInfos`
     */
    class SurfaceInfo {
      public:
        VkSurfaceKHR S = nullptr;
        SurfaceInfo(void) {}
        SurfaceInfo(VkSurfaceKHR pS) {this-> S = pS;}

                  REY_Array<REY_Array<VkSurfaceFormatKHR>>              amVK_2D_GPUs_ImageFMTs;
                  REY_Array<VkSurfaceCapabilitiesKHR>                   amVK_1D_GPUs_SurfCAP;

        bool called_GetPhysicalDeviceSurfaceFormatsKHR = false;
        bool called_GetPhysicalDeviceSurfaceCapabilitiesKHR = false;
        void        GetPhysicalDeviceSurfaceInfo(void);
    };


  public:
        // Array of `HardWare amVK_1D_GPUs` connected to motherboard
    static inline REY_Array<VkPhysicalDevice>                           amVK_1D_GPUs;
    static inline REY_Array<REY_Array<VkQueueFamilyProperties>>         amVK_2D_GPUs_QFAMs;
    static inline REY_Array<VkExtensionProperties>                      amVK_1D_InstanceEXTs;
    static inline REY_ArrayDYN<char*>                                   amVK_1D_InstanceEXTs_Enabled;
    static inline REY_ArrayDYN<SurfaceInfo>                             amVK_1D_SurfaceInfos;
    static inline REY_Array<REY_Array<VkExtensionProperties>>           amVK_2D_GPUs_EXTs;
        // REY_Array  doesn't allocate any memory by default

    #define amVK_LOOP_GPUs(_var_)           for (uint32_t _var_ = 0,  lim = amVK_1D_GPUs.n;             _var_ < lim;  _var_++)
    #define amVK_LOOP_IEXTs(_var_)          for (uint32_t _var_ = 0,  lim = amVK_1D_InstanceEXTs.n;     _var_ < lim;  _var_++)
    #define amVK_LOOP_GPU_EXTs(_k_, _var_)  for (uint32_t _var_ = 0,  lim = amVK_2D_GPUs_EXTs[_k_].n;   _var_ < lim;  _var_++)
    #define amVK_LOOP_QFAMs(_k_, _var_)     for (uint32_t _var_ = 0,  lim = amVK_2D_GPUs_QFAMs[_k_].n;  _var_ < lim;  _var_++)
    #define amVK_LOOP_SURFs(_var_)          for (uint32_t _var_ = 0,  lim = amVK_1D_SurfaceInfos.n;     _var_ < lim;  _var_++)
    #define amVK_LOOP_SURF_FMTs(_SurfaceInfoPTR_, _GPU_k_, _var_) \
        for (uint32_t _var_ = 0, lim = _SurfaceInfoPTR_->amVK_2D_GPUs_ImageFMTs[_GPU_k_].n;         _var_ < lim;  _var_++)


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
        // Linear Search
    static                PD_Index VkPhysicalDevice_2_PD_Index(VkPhysicalDevice PDevice);
    static inline         PD_Index GetARandom_PhysicalDevice_amVK_Index(void) { return 0; }
        // Call: `EnumeratePhysicalDevices();` Before this function
    static inline VkPhysicalDevice GetARandom_PhysicalDevice(void) { return amVK_1D_GPUs[0]; }


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
    /** 
     * @param ID:- Use:- `amVK_InstanceProps::VkPhysicalDevice_2_PD_Index()` if you wanna pass in `VkPhysicalDevice` 
     * @returns `VkDeviceQCI.queueFamilyIndex` to be used
     */
    static inline uint32_t ChooseAQueueFamily_for_GRAPHICS(PD_Index  GPU_k = 0) {
        return amVK_InstanceProps::ChooseAQueueFamily(VK_QUEUE_GRAPHICS_BIT, GPU_k);
    }
    static        uint32_t ChooseAQueueFamily(VkQueueFlags p_flagBits, PD_Index GPU_k = 0);


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
  public:
    static bool  IS_InstanceEXT_Available(const char *extName);                 // amVK_1D_InstanceEXTs
    static void Add_InstanceEXT_ToEnable (const char *extName);                 // amVK_1D_InstanceEXTs_Enabled
    static void Log_InstanceEXTs_Enabled (VkResult ret);                        // amVK_1D_InstanceEXTs_Enabled
    static bool      IS_GPU_EXT_Available(PD_Index GPU_k, const char *extName); // amVK_2D_GPUs_EXTs
        //         IS_DeviceEXT_Available() --> Same as above
        // IS_PhysicalDeviceEXT_Available() --> Same as above
    

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
  public:
    static void push_back_VkSurfaceKHR(VkSurfaceKHR S);                 // amVK_1D_SurfaceInfos


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
    static void Export_nilohmannJSON(void);
    static void Export_yyJSON(void);
};