#pragma once
#include "amVK_GPUProps.hh"

/**
 * i don't wanna scatter all the Properties All around my code. So, i'm gonna keep them here 😊
 *   --> Right inside `amVK_InstanceProps` class
 */
class amVK_InstanceProps {
  public:
                        // REY_Array  doesn't allocate any memory by default
    static inline          REY_Array<amVK_GPUProps>                                 amVK_1D_GPUs;
    static inline          REY_Array<VkExtensionProperties>                         amVK_1D_InstanceEXTs;
    static inline          REY_Array<VkLayerProperties>                             amVK_1D_InstanceLayers;
    #define amVK_LOOP_GPUs(_var_)                   for (uint32_t _var_ = 0,  lim = amVK_1D_GPUs.n;             _var_ < lim;  _var_++)
    #define amVK_LOOP_IEXTs(_var_)                  for (uint32_t _var_ = 0,  lim = amVK_1D_InstanceEXTs.n;     _var_ < lim;  _var_++)
    #define amVK_LOOP_ILayers(_var_)                for (uint32_t _var_ = 0,  lim = amVK_1D_InstanceLayers.n;   _var_ < lim;  _var_++)

  public:
    static inline bool called_EnumeratePhysicalDevices                      = false;
    static inline bool called_EnumerateInstanceExtensions                   = false;
    static inline bool called_EnumerateInstanceLayerProperties              = false;
    static void               EnumeratePhysicalDevices(VkInstance vk_Instance);  // amVK_1D_GPUs
    static void               EnumerateInstanceExtensions(void);                 // amVK_1D_InstanceEXTs
    static void               EnumerateInstanceLayerProperties(void);            // amVK_1D_InstanceLayers

    /** 
     * ========================================== 🛠️ amVK_check_called_EnumeratePhysicalDevices ==========================================
     **/
    #define amVK_check_called_EnumeratePhysicalDevices()                        \
        if (amVK_InstanceProps::called_EnumeratePhysicalDevices == false) {     \
            REY_LOG_EX("You haven't called   amVK_InstanceProps::EnumeratePhysicalDevices()  yet 😭");  \
        }
    /** 
     * ========================================== 🛠️ UTILITY FUNCTIONS ==========================================
     **/
  public:
    static          amVK_GPU_Index VkPhysicalDevice_2_amVK_GPU_Index(VkPhysicalDevice PDevice);     // Linear Search
    static          amVK_GPUProps*                      Get_GPUProps(VkPhysicalDevice PDevice);     // Calls Above function
    static          amVK_GPUProps*              GetARandom_GPU(void);
    static inline   amVK_GPU_Index              GetARandom_GPU_amVK_Index(void)  { return 0; }
    static inline   amVK_GPU_Index               PD_2_ID(VkPhysicalDevice PD)    { VkPhysicalDevice_2_amVK_GPU_Index(PD); }
    static bool                   isInstanceEXTAvailable(const char *extName);                      // amVK_1D_InstanceEXTs
    static bool                   isInstanceLayerAvailable(const char *layerName);                  // amVK_1D_InstanceLayers
   /** 
    * ========================================== 👀 Export / Visualization / [See it] / JSON Printing ==========================================
    **/
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