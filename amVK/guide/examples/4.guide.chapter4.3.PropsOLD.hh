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
        // Array of `HardWare amVK_1D_GPUs` connected to motherboard
    static inline REY_Array<VkPhysicalDevice> amVK_1D_GPUs;
        // REY_Array  doesn't allocate any memory by default

    static                     void EnumeratePhysicalDevices(void);
        // Call: `EnumeratePhysicalDevices();` Before this function
    static inline VkPhysicalDevice GetARandom_PhysicalDevice(void) {
        return amVK_1D_GPUs[0];
    }

    typedef uint32_t   PD_Index;
    static inline      PD_Index GetARandom_PhysicalDevice_amVK_Index(void) { return 0; }
        // Linear Search
    static amVK_InstanceProps::PD_Index VkPhysicalDevice_2_PD_Index(VkPhysicalDevice PDevice);



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
    static inline REY_Array<REY_Array<VkQueueFamilyProperties>>   amVK_2D_GPUs_QFAMs;
    static void GetPhysicalDeviceQueueFamilyProperties(void);

    /** 
     * @param ID:- Use:- `amVK_InstanceProps::VkPhysicalDevice_2_PD_Index()` if you wanna pass in `VkPhysicalDevice` 
     * @returns `VkDeviceQCI.queueFamilyIndex` to be used
     */
    static inline uint32_t ChooseAQueueFamily_for_GRAPHICS(amVK_InstanceProps::PD_Index ID = 0) {
        return amVK_InstanceProps::ChooseAQueueFamily(VK_QUEUE_GRAPHICS_BIT, ID);
    }
    static        uint32_t ChooseAQueueFamily(VkQueueFlags p_flagBits, amVK_InstanceProps::PD_Index p_ID = 0);
    

/*
                                    _____           _                       ________   _________  
     /\                            |_   _|         | |                     |  ____\ \ / /__   __| 
    /  \   _ __ _ __ __ _ _   _      | |  _ __  ___| |_ __ _ _ __   ___ ___| |__   \ V /   | |___ 
   / /\ \ | '__| '__/ _` | | | |     | | | '_ \/ __| __/ _` | '_ \ / __/ _ \  __|   > <    | / __|
  / ____ \| |  | | | (_| | |_| |    _| |_| | | \__ \ || (_| | | | | (_|  __/ |____ / . \   | \__ \
 /_/    \_\_|  |_|  \__,_|\__, |   |_____|_| |_|___/\__\__,_|_| |_|\___\___|______/_/ \_\  |_|___/
                           __/ |_____                                                             
                          |___/______|                                                            
*/
  public:
    static inline REY_Array<VkExtensionProperties> s_InstanceEXT_Props;
    #define amVK_EXT_PROPs             amVK_InstanceProps::s_InstanceEXT_Props
    static void EnumerateInstanceExtensions(void);
    static bool IS_InstanceEXT_Available(const char *extName);


/*
  ____  _____                                   _____ __  __  _____   ______ __  __ _______  
 |___ \|  __ \   /\                            |_   _|  \/  |/ ____| |  ____|  \/  |__   __| 
   __) | |  | | /  \   _ __ _ __ __ _ _   _      | | | \  / | |  __  | |__  | \  / |  | |___ 
  |__ <| |  | |/ /\ \ | '__| '__/ _` | | | |     | | | |\/| | | |_ | |  __| | |\/| |  | / __|
  ___) | |__| / ____ \| |  | | | (_| | |_| |    _| |_| |  | | |__| | | |    | |  | |  | \__ \
 |____/|_____/_/    \_\_|  |_|  \__,_|\__, |   |_____|_|  |_|\_____| |_|    |_|  |_|  |_|___/
                                       __/ |_____                ______                      
                                      |___/______|              |______|                     
    for each (VkSurfaceKHR)
        for each (GPU)
            LIST IMG_FMTs
*/
    /**
     * VULKAN Extension:- VK_KHR_surface
     */
    class amVK_SurfaceProps {
      public:
        VkSurfaceKHR                 m_S = nullptr;
        amVK_SurfaceProps(void) {}
        amVK_SurfaceProps(VkSurfaceKHR S) {this-> m_S = S;}

        REY_Array<REY_Array<VkSurfaceFormatKHR>> m_GPU_IMG_FMTs;

        bool called_GetPhysicalDeviceSurfaceFormatsKHR = false;
        void        GetPhysicalDeviceSurfaceFormatsKHR(void);
    };

    static inline REY_ArrayDYN<amVK_SurfaceProps> s_SurfaceImageFormats;
    static void push_back_VkSurfaceKHR(VkSurfaceKHR S) {
        amVK_SurfaceProps S_Props(S);
        S_Props.GetPhysicalDeviceSurfaceInfo();

        s_SurfaceImageFormats.push_back(S_Props);
    }

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

