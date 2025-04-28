#pragma once
#include "amVK_GPUProps.hh"

class amVK_DeviceQueues {
  public:
    amVK_DeviceQueues(amVK_GPUProps *GPUProps);
   ~amVK_DeviceQueues(void) {}

  public:
    amVK_GPUProps *GPUProps = nullptr;

  public:
    struct amVK_QueueCount {                    /**                  "That's gonna be Queried to vkCreateDevice()"                 */
        uint32_t       Graphics = 0;
        uint32_t    VideoEncode = 0;
        uint32_t    VideoDecode = 0;
        uint32_t        Compute = 0;
        uint32_t       Transfer = 0;
        uint32_t  SparseBinding = 0;
    } QCount;                                   /**    Also, for QueueFamilies \see amVK_GPUProps::QFamID [amVK_QueueFamilyIndex]  */

    struct amVK_QueueFamilyIndex {              /**                 CONSTRUCTOR  --->   D->GPU_Props->QFamID.Graphics              */
        uint32_t       Graphics = UINT32_MAX;
        uint32_t    VideoEncode = UINT32_MAX;
        uint32_t    VideoDecode = UINT32_MAX;
        uint32_t        Compute = UINT32_MAX;
        uint32_t       Transfer = UINT32_MAX;
        uint32_t  SparseBinding = UINT32_MAX;
    } Used_QFamID;                              /** So that you can set it to smth other than amVK_GPUProps::QFramID::Transfer 💁‍♀️ */

    void generate_1D_QFAMs_QCount(void) {       /**             generate_1D_QCI() calls ---> generate_1D_QFAMs_QCount()            */
                                                /**                     Array has been reserved in CONSTRUCTOR                     */
        amVK_1D_QFAMs_QCount_Internal[this->Used_QFamID.Graphics]      += this->QCount.Graphics;
        amVK_1D_QFAMs_QCount_Internal[this->Used_QFamID.VideoEncode]   += this->QCount.VideoEncode;
        amVK_1D_QFAMs_QCount_Internal[this->Used_QFamID.VideoDecode]   += this->QCount.VideoDecode;
        amVK_1D_QFAMs_QCount_Internal[this->Used_QFamID.Compute]       += this->QCount.Compute;
        amVK_1D_QFAMs_QCount_Internal[this->Used_QFamID.Transfer]      += this->QCount.Transfer;
        amVK_1D_QFAMs_QCount_Internal[this->Used_QFamID.SparseBinding] += this->QCount.SparseBinding;
    }

    static inline float                   s_QueuePrority = 1.0f;        // see: `generate_1D_QCIs()`
    static inline VkDeviceQueueCreateInfo s_CI_Template  = {            // see: `generate_1D_QCIs()`
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .queueFamilyIndex = 0,
        .queueCount = 0,
        .pQueuePriorities = &s_QueuePrority
    };

        // VULKAN:- The queueFamilyIndex member of each element of pQueueCreateInfos must be unique within pQueueCreateInfos
        //       So, Don't modify           amVK_1D_QCIs     yourself 💁‍♀️
    REY_ArrayDYN<VkDeviceQueueCreateInfo>   amVK_1D_QCIs;                               // != GPUProps::amVK_1D_GPUs_QFAMs.n    [usually]
              REY_Array<uint32_t>           amVK_1D_QFAMs_QCount_Internal;              // == GPUProps::amVK_1D_GPUs_QFAMs.n    [UseAfter:- generate_1D_QCI()]
              REY_Array<uint32_t>           amVK_1D_QFAMs_QCount_TOTAL;                 // == GPUProps::amVK_1D_GPUs_QFAMs.n    [UseAfter:- generate_1D_QCI()]
              REY_Array<uint32_t>           amVK_1D_QFAMs_QCount_USER;                  // == GPUProps::amVK_1D_GPUs_QFAMs.n    [UseAfter:- CONSTRUCTOR]
    void                                generate_1D_QCIs(void);                         // generate_1D_QCI() calls ---> generate_1D_QFAMs_QCount()
    bool                         called_generate_1D_QCIs = false;
    void                                    sync_1D_QCIs(VkDeviceCreateInfo* DeviceCI); // Use this, instead of manually using amVK_1D_QCI

  public:
    bool                            called_GetDeviceQueues = false;
    void                                   GetDeviceQueues(VkDevice D);                 // uses:- amVK_1D_QFam_QCount_EXT_incUserPushed

    struct amVK_Queues {
        REY_Array<VkQueue>       Graphics;
        REY_Array<VkQueue>    VideoEncode;
        REY_Array<VkQueue>    VideoDecode;
        REY_Array<VkQueue>        Compute;
        REY_Array<VkQueue>       Transfer;
        REY_Array<VkQueue>  SparseBinding;
        REY_Array<REY_Array<VkQueue>> amVK_2D_QFAMs_Queues; // [USER Ones] Doesn't include the ones above
    } TheArrays;

    void                          _CHK1_(void)      {  if (called_GetDeviceQueues == false) {REY_LOG_EX("called_GetDeviceQueues == false");} }
    REY_Array<VkQueue>*       GraphicsQs(void)      { _CHK1_(); return &TheArrays.Graphics; }
    REY_Array<VkQueue>*    VideoEncodeQs(void)      { _CHK1_(); return &TheArrays.VideoEncode; }
    REY_Array<VkQueue>*    VideoDecodeQs(void)      { _CHK1_(); return &TheArrays.VideoDecode; }
    REY_Array<VkQueue>*        ComputeQs(void)      { _CHK1_(); return &TheArrays.Compute; }
    REY_Array<VkQueue>*       TransferQs(void)      { _CHK1_(); return &TheArrays.Transfer; }
    REY_Array<VkQueue>*  SparseBindingQs(void)      { _CHK1_(); return &TheArrays.SparseBinding; }
    REY_Array<REY_Array<VkQueue>>* amVK_2D_UserQs() { _CHK1_(); return &TheArrays.amVK_2D_QFAMs_Queues; }

    void                 Graphics_CHK2_(uint32_t k) { _CHK1_(); if (k >= TheArrays.Graphics.MAL)       {REY_LOG_EX("k >= TheArrays.Graphics.MAL");}       }
    void              VideoEncode_CHK2_(uint32_t k) { _CHK1_(); if (k >= TheArrays.VideoEncode.MAL)    {REY_LOG_EX("k >= TheArrays.VideoEncode.MAL");}    }
    void              VideoDecode_CHK2_(uint32_t k) { _CHK1_(); if (k >= TheArrays.VideoDecode.MAL)    {REY_LOG_EX("k >= TheArrays.VideoDecode.MAL");}    }
    void                  Compute_CHK2_(uint32_t k) { _CHK1_(); if (k >= TheArrays.Compute.MAL)        {REY_LOG_EX("k >= TheArrays.Compute.MAL");}        }
    void                 Transfer_CHK2_(uint32_t k) { _CHK1_(); if (k >= TheArrays.Transfer.MAL)       {REY_LOG_EX("k >= TheArrays.Transfer.MAL");}       }
    void            SparseBinding_CHK2_(uint32_t k) { _CHK1_(); if (k >= TheArrays.SparseBinding.MAL)  {REY_LOG_EX("k >= TheArrays.SparseBinding.MAL");}  }

              VkQueue        GraphicsQ (uint32_t k) {      Graphics_CHK2_(k); return TheArrays.Graphics[k]; }
              VkQueue     VideoEncodeQ (uint32_t k) {   VideoEncode_CHK2_(k); return TheArrays.VideoEncode[k]; }
              VkQueue     VideoDecodeQ (uint32_t k) {   VideoDecode_CHK2_(k); return TheArrays.VideoDecode[k]; }
              VkQueue         ComputeQ (uint32_t k) {       Compute_CHK2_(k); return TheArrays.Compute[k]; }
              VkQueue        TransferQ (uint32_t k) {      Transfer_CHK2_(k); return TheArrays.Transfer[k]; }
              VkQueue   SparseBindingQ (uint32_t k) { SparseBinding_CHK2_(k); return TheArrays.SparseBinding[k]; }
};