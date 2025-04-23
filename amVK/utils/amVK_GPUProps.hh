#pragma once
#include <vulkan/vulkan.h>
#include "REY_Utils.hh"
#include "REY_Types.hh"

typedef uint32_t amVK_GPU_Index;

#define amVK_QueueFamily_NOT_FOUND    0xFFFFFFFF
#define amVK_PhysicalDevice_NOT_FOUND 0xFFFFFFFF
#define amVK_GPU_NOT_FOUND            0xFFFFFFFF

class amVK_GPUProps {
  public:
    amVK_GPUProps(VkPhysicalDevice PD, amVK_GPU_Index ID);
   ~amVK_GPUProps() {}

            amVK_GPU_Index                                   ID;
              VkPhysicalDevice                      vk_PhysicalDevice;
              VkPhysicalDeviceFeatures                 Features;
              VkPhysicalDeviceMemoryProperties         MEMProps;
    REY_Array<VkQueueFamilyProperties>                amVK_1D_GPUs_QFAMs;
    REY_Array<VkExtensionProperties>                  amVK_1D_GPUs_EXTs;
    uint32_t              get_QFamCount(void) {return amVK_1D_GPUs_QFAMs.n;}

  public:
    struct amVK_MemoryHeap {
        VkMemoryHeap*  CPU_GPU_Synced        = nullptr;
        VkMemoryHeap*  CPU_GPU_Synced_Cached = nullptr;
        VkMemoryHeap*  RAM_SharedWith_GPU    = nullptr;
        VkMemoryHeap* VRAM                   = nullptr;
        VkMemoryHeap* VRAM_SharedWith_CPU    = nullptr;
    } MEMHeapPTR;

    struct amVK_MemoryHeapIndex {
        uint32_t       CPU_GPU_Synced        = 1;  // HeapIndex of the Corresponding MemoryType below
        uint32_t       CPU_GPU_Synced_Cached = 1;  // HeapIndex of the Corresponding MemoryType below
        uint32_t       RAM_SharedWith_GPU    = 1;
        uint32_t      VRAM                   = 0;
        uint32_t      VRAM_SharedWith_CPU    = 2;  // if Multiple SharedVRAM available, will be set to Largest one 
    } MEMHeapID;

    struct amVK_MemoryTypeIndex {
        uint32_t       CPU_GPU_Synced        = 1;  // CPU_GPU_COHERENT [F1][if connected HEAP has a COHERENT+CACHED variant ---> AutoSelect That]
        uint32_t       CPU_GPU_Synced_Cached = 1;  // CPU_GPU_COHERENT + CPU_CACHED
    } MEMTypeID;

    bool called_REY_CategorizeMemoryHeaps = false;
    void        REY_CategorizeMemoryHeaps(void);
    bool called_REY_CategorizeQueueFamilies = false;
    void        REY_CategorizeQueueFamilies(void);

    struct amVK_QueueFamilyIndex {
        uint32_t       Graphics = UINT32_MAX;
        uint32_t    VideoEncode = UINT32_MAX;
        uint32_t    VideoDecode = UINT32_MAX;
        uint32_t        Compute = UINT32_MAX;
        uint32_t       Transfer = UINT32_MAX;
        uint32_t  SparseBinding = UINT32_MAX;
    } QFamID;

                //  Doesn't depened on the Categorized QueueFamilies
    uint32_t        ChooseAQueueFamily(VkQueueFlags p_flagBits);
    #define         ChooseAQueueFamily_GRAPHICS() ChooseAQueueFamily(VK_QUEUE_GRAPHICS_BIT)

    bool          isExtensionAvailable(const char*  extName);
    
  public:
    bool called_GetPhysicalDeviceQueueFamilyProperties  = false;
    bool called_GetPhysicalDeviceFeatures               = false;
    bool called_GetPhysicalDeviceMemoryProperties       = false;
    bool called_EnumerateDeviceExtensionProperties      = false;
    void        EnumerateDeviceExtensionProperties(void);
    void        GetPhysicalDeviceQueueFamilyProperties(void);
    void        GetPhysicalDeviceFeatures(void);
    void        GetPhysicalDeviceMemoryProperties(void);
};