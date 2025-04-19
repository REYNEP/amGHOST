#pragma once
#include "amVK/common/amVK.hh"
#include "amVK/common/amVK_GPU.hh"

class amVK_Surface;

/**
 * i don't wanna scatter all the Properties All around my code. So, i'm gonna keep them here 😊
 *   --> Right inside `amVK_InstanceProps` class
 * 
 *   #1:- as of 2025, april 19, can't inclue amVK_Instance.hh, cz that file includes this 💁‍♀️
 *   #2:- 
 */
class amVK_InstanceProps {
  public:
    static inline bool called_EnumeratePhysicalDevices = false;
    static inline bool called_GetPhysicalDeviceQueueFamilyProperties = false;
    static inline bool called_EnumerateInstanceExtensions = false;
    static inline bool called_EnumerateDeviceExtensionProperties = false;

  public:
    static void EnumeratePhysicalDevices(void);                      // amVK_1D_GPUs
    static       void GetPhysicalDeviceQueueFamilyProperties(void);  // amVK_2D_GPUs_QFAMs
    static void EnumerateInstanceExtensions(void);                   // amVK_1D_InstanceEXTs
    static void EnumerateDeviceExtensionProperties(void);            // amVK_2D_GPUs_EXTs

  public:
        // Array of `HardWare amVK_1D_GPUs` connected to motherboard
    static inline REY_Array<VkPhysicalDevice>                           amVK_1D_GPUs;
    static inline REY_Array<REY_Array<VkQueueFamilyProperties>>         amVK_2D_GPUs_QFAMs;
    static inline REY_Array<VkExtensionProperties>                      amVK_1D_InstanceEXTs;
    static inline REY_ArrayDYN<char*>                                   amVK_1D_InstanceEXTs_Enabled;
    static inline REY_ArrayDYN<amVK_Surface *>                          amVK_1D_Surfaces;
    static inline REY_Array<REY_Array<VkExtensionProperties>>           amVK_2D_GPUs_EXTs;
        // REY_Array  doesn't allocate any memory by default

    #define amVK_LOOP_GPUs(_var_)           for (uint32_t _var_ = 0,  lim = amVK_1D_GPUs.n;             _var_ < lim;  _var_++)
    #define amVK_LOOP_IEXTs(_var_)          for (uint32_t _var_ = 0,  lim = amVK_1D_InstanceEXTs.n;     _var_ < lim;  _var_++)
    #define amVK_LOOP_GPU_EXTs(_k_, _var_)  for (uint32_t _var_ = 0,  lim = amVK_2D_GPUs_EXTs[_k_].n;   _var_ < lim;  _var_++)
    #define amVK_LOOP_QFAMs(_k_, _var_)     for (uint32_t _var_ = 0,  lim = amVK_2D_GPUs_QFAMs[_k_].n;  _var_ < lim;  _var_++)
    #define amVK_LOOP_SURFs(_var_)          for (uint32_t _var_ = 0,  lim = amVK_1D_Surfaces.n;         _var_ < lim;  _var_++)
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
    static void addTo_1D_InstanceEXTs_Enabled  (const char *extName);                       // amVK_1D_InstanceEXTs_Enabled
    static void   log_1D_InstanceEXTs_Enabled  (VkResult ret);                              // amVK_1D_InstanceEXTs_Enabled
    static bool        is_2D_GPU_EXTs_Available(amVK_GPU_Index GPU_k, const char *extName); // amVK_2D_GPUs_EXTs
        //           is_2D_DeviceEXTs_Available() --> Same as above
        //   is_2D_PhysicalDeviceEXTs_Available() --> Same as above
    

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
    static void push_back_amVK_Surface(amVK_Surface *S);                 // amVK_1D_Surfaces


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