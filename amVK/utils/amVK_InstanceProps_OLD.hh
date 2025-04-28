#pragma once

#include <vulkan/vulkan.h>
#include "REY_Array.hh"
#include "REY_Types.hh"
#ifndef amVK_GPU_HH
    typedef uint32_t amVK_GPU_Index;

    #define amVK_QueueFamily_NOT_FOUND    0xFFFFFFFF
    #define amVK_PhysicalDevice_NOT_FOUND 0xFFFFFFFF
    #define amVK_GPU_NOT_FOUND            0xFFFFFFFF
#endif

/**
 * i don't wanna scatter all the Properties All around my code. So, i'm gonna keep them here 😊
 *   --> Right inside `amVK_InstanceProps` class
 * 
 *   #1:- as of 2025, april 19, can't inclue amVK_Instance.hh, cz that file includes this 💁‍♀️
 *   #2:- 
 */
class amVK_InstanceProps {
  public:
    struct amVK_MemoryHeap {
        static inline VkMemoryHeap*  RAM_SharedWith_GPU = nullptr;
        static inline VkMemoryHeap* VRAM                = nullptr;
        static inline VkMemoryHeap* VRAM_SharedWith_CPU = nullptr;
    } MEMHeapPTR;

    struct amVK_MemoryHeapIndex {
        static inline uint32_t       RAM_SharedWith_GPU = 1;
        static inline uint32_t      VRAM                = 0;
        static inline uint32_t      VRAM_SharedWith_CPU = 2;
    } MEMHeapID;

    static void REY_CategorizeMemoryHeaps(void);
    
  public:
    static inline bool called_EnumeratePhysicalDevices                      = false;
    static inline bool       called_GetPhysicalDeviceQueueFamilyProperties  = false;
    static inline bool       called_GetPhysicalDeviceFeatures               = false;
    static inline bool       called_GetPhysicalDeviceMemoryProperties       = false;
    static inline bool called_EnumerateInstanceExtensions                   = false;
    static inline bool called_EnumerateDeviceExtensionProperties            = false;

    static void               EnumeratePhysicalDevices(VkInstance vk_Instance);  // amVK_1D_GPUs
    static void                     GetPhysicalDeviceQueueFamilyProperties(void);// amVK_2D_GPUs_QFAMs
    static void                     GetPhysicalDeviceFeatures(void);             // amVK_1D_GPUs_Features
    static void                     GetPhysicalDeviceMemoryProperties(void);     // amVK_1D_GPUs_MEMProps
    static void               EnumerateInstanceExtensions(void);                 // amVK_1D_InstanceEXTs
    static void               EnumerateDeviceExtensionProperties(void);          // amVK_2D_GPUs_EXTs

  public:
        // Array of `HardWare amVK_1D_GPUs` connected to motherboard
    static inline REY_Array<          VkPhysicalDevice>                             amVK_1D_GPUs;
    static inline REY_Array<          VkPhysicalDeviceFeatures>                     amVK_1D_GPUs_Features;
    static inline REY_Array<          VkPhysicalDeviceMemoryProperties>             amVK_1D_GPUs_MEMProps;
    static inline REY_Array<          VkExtensionProperties>                        amVK_1D_InstanceEXTs;
    static inline REY_Array<REY_Array<VkExtensionProperties>>                       amVK_2D_GPUs_EXTs;
    static inline REY_Array<REY_Array<VkQueueFamilyProperties>>                     amVK_2D_GPUs_QFAMs;
        // REY_Array  doesn't allocate any memory by default

    #define amVK_LOOP_GPUs(_var_)           for (uint32_t _var_ = 0,  lim = amVK_1D_GPUs.n;             _var_ < lim;  _var_++)
    #define amVK_LOOP_IEXTs(_var_)          for (uint32_t _var_ = 0,  lim = amVK_1D_InstanceEXTs.n;     _var_ < lim;  _var_++)
    #define amVK_LOOP_GPU_EXTs(_k_, _var_)  for (uint32_t _var_ = 0,  lim = amVK_2D_GPUs_EXTs[_k_].n;   _var_ < lim;  _var_++)
    #define amVK_LOOP_QFAMs(_k_, _var_)     for (uint32_t _var_ = 0,  lim = amVK_2D_GPUs_QFAMs[_k_].n;  _var_ < lim;  _var_++)
    #define amVK_LOOP_SURFs(_var_)          for (uint32_t _var_ = 0,  lim = amVK_1D_SurfaceLinks.n;     _var_ < lim;  _var_++)
    #define amVK_LOOP_SURF_FMTs(_SurfaceInfoPTR_, _GPU_k_, _var_) \
        for (uint32_t _var_ = 0, lim = _SurfaceInfoPTR_->amVK_2D_GPUs_ImageFMTs[_GPU_k_].n;             _var_ < lim;  _var_++)


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
    static          amVK_GPU_Index VkPhysicalDevice_2_amVK_GPU_Index(VkPhysicalDevice PDevice);
    static inline   amVK_GPU_Index GetARandom_GPU_amVK_Index(void) { return 0; }
        // Call: `EnumeratePhysicalDevices();` Before this function
    static inline VkPhysicalDevice GetARandom_GPU(void) { return amVK_1D_GPUs[0]; }


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
     * @param ID:- Use:- `amVK_InstanceProps::VkPhysicalDevice_2_amVK_GPU_Index()` if you wanna pass in `VkPhysicalDevice` 
     * @returns `VkDeviceQCI.queueFamilyIndex` to be used
     */
    static inline uint32_t ChooseAQueueFamily_for_GRAPHICS(amVK_GPU_Index  GPU_k = 0) {
        return amVK_InstanceProps::ChooseAQueueFamily(VK_QUEUE_GRAPHICS_BIT, GPU_k);
    }
    static        uint32_t ChooseAQueueFamily(VkQueueFlags p_flagBits, amVK_GPU_Index GPU_k = 0);


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
    static bool    is_1D_InstanceEXTs_Available(const char *extName);                       // amVK_1D_InstanceEXTs
    static bool        is_2D_GPU_EXTs_Available(amVK_GPU_Index GPU_k, const char *extName); // amVK_2D_GPUs_EXTs
        //           is_2D_DeviceEXTs_Available() --> Same as above
        //   is_2D_PhysicalDeviceEXTs_Available() --> Same as above


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