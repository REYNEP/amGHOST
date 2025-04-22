#pragma once
#include "amVK_GPUProps.hh"

class amVK_DeviceQueues {
  public:
    amVK_DeviceQueues(amVK_GPUProps *GPUProps);
   ~amVK_DeviceQueues(void) {}

  public:
    amVK_GPUProps *GPUProps = nullptr;

  public:
    struct amVK_QueueCount {                    /** "That's gonna be Queried to vkCreateDevice()" */
        uint32_t       Graphics = 0;
        uint32_t    VideoEncode = 0;
        uint32_t    VideoDecode = 0;
        uint32_t        Compute = 0;
        uint32_t       Transfer = 0;
        uint32_t  SparseBinding = 0;
    } QCount;                                   /** Also, for QueueFamilies \see amVK_GPUProps::QFamID [amVK_QueueFamilyIndex] */

    struct amVK_QueueFamilyIndex {              /** CONSTRUCTOR  --->   D->GPU_Props->QFamID.Graphics */
        uint32_t       Graphics = UINT32_MAX;
        uint32_t    VideoEncode = UINT32_MAX;
        uint32_t    VideoDecode = UINT32_MAX;
        uint32_t        Compute = UINT32_MAX;
        uint32_t       Transfer = UINT32_MAX;
        uint32_t  SparseBinding = UINT32_MAX;
    } Used_QFamID;                              /** So that you can set it to smth other than amVK_GPUProps::QFramID::Transfer 💁‍♀️ */

    static inline const float s_QueuePrority = 1.0f;
    static inline VkDeviceQueueCreateInfo s_CI_Template = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .queueFamilyIndex = 0,
        .queueCount = 0,
        .pQueuePriorities = &s_QueuePrority
    };

    void generate_1D_QFam_QCount(void) {        /**     generate_1D_QCI() calls ---> generate_1D_QFam_QCount()     */
        REY_Array_RESERVE(amVK_1D_QFam_QCount, this->GPUProps->amVK_1D_GPUs_QFAMs.n, 0);
        amVK_1D_QFam_QCount[this->Used_QFamID.Graphics]      += this->QCount.Graphics;
        amVK_1D_QFam_QCount[this->Used_QFamID.VideoEncode]   += this->QCount.VideoEncode;
        amVK_1D_QFam_QCount[this->Used_QFamID.VideoDecode]   += this->QCount.VideoDecode;
        amVK_1D_QFam_QCount[this->Used_QFamID.Compute]       += this->QCount.Compute;
        amVK_1D_QFam_QCount[this->Used_QFamID.Transfer]      += this->QCount.Transfer;
        amVK_1D_QFam_QCount[this->Used_QFamID.SparseBinding] += this->QCount.SparseBinding;
    }

              REY_Array<uint32_t>           amVK_1D_QFam_QCount;                        // == GPUProps::amVK_1D_GPUs_QFAMs.n
    REY_ArrayDYN<VkDeviceQueueCreateInfo>   amVK_1D_QCIs;                               // != GPUProps::amVK_1D_GPUs_QFAMs.n
    void                                generate_1D_QCIs(void);                         // generate_1D_QCI() calls ---> generate_1D_QFam_QCount()
    bool                         called_generate_1D_QCIs = false;
    void                                    sync_1D_QCIs(VkDeviceCreateInfo* DeviceCI); // Use this, instead of manually using amVK_1D_QCI

                        REY_Array<uint32_t> amVK_1D_QFam_QCount_EXT_incUserPushed;      // uses:- amVK_1D_QCI
    void                      REY_Calculate_amVK_1D_QFam_QCount_EXT_incUserPushed(void);
    bool               called_REY_Calculate_amVK_1D_QFam_QCount_EXT_incUserPushed = false;

  public:
    REY_Array<REY_Array<VkQueue>>           amVK_2D_Queues;
    void                                   GetDeviceQueues(VkDevice D);                 // uses:- amVK_1D_QFam_QCount_EXT_incUserPushed

        // WIP:- What if       Used_QFamID.Graphics = Used_QFamID.Transfer     ?
        // Solution:
        struct amVK_Queues {
            REY_Array<VkQueue>       Graphics;
            REY_Array<VkQueue>    VideoEncode;
            REY_Array<VkQueue>    VideoDecode;
            REY_Array<VkQueue>        Compute;
            REY_Array<VkQueue>       Transfer;
            REY_Array<VkQueue>  SparseBinding;
            REY_Array<REY_Array<VkQueue>> amVK_2D_QFAMs_Queues; // Doesn't include the ones above
        } TheArrays;
        // NOT IMPLEMENTED YET

    void                         _CHK1_(void)       {              if (amVK_2D_Queues.n == 0) {REY_LOG_EX("amVK_2D_Queues.n == 0");} }
    REY_Array<VkQueue>       GraphicsQs(void)       { _CHK1_(); return amVK_2D_Queues[Used_QFamID.Graphics]; }
    REY_Array<VkQueue>    VideoEncodeQs(void)       { _CHK1_(); return amVK_2D_Queues[Used_QFamID.VideoEncode]; }
    REY_Array<VkQueue>    VideoDecodeQs(void)       { _CHK1_(); return amVK_2D_Queues[Used_QFamID.VideoDecode]; }
    REY_Array<VkQueue>        ComputeQs(void)       { _CHK1_(); return amVK_2D_Queues[Used_QFamID.Compute]; }
    REY_Array<VkQueue>       TransferQs(void)       { _CHK1_(); return amVK_2D_Queues[Used_QFamID.Transfer]; }
    REY_Array<VkQueue>  SparseBindingQs(void)       { _CHK1_(); return amVK_2D_Queues[Used_QFamID.SparseBinding]; }

    void                 Graphics_CHK2_(uint32_t k) { _CHK1_(); if (k >= QCount.Graphics) {REY_LOG_EX("k >= QCount.Graphics");}}
    void              VideoEncode_CHK2_(uint32_t k) { _CHK1_(); if (k >= QCount.Graphics) {REY_LOG_EX("k >= QCount.Graphics");}}
    void              VideoDecode_CHK2_(uint32_t k) { _CHK1_(); if (k >= QCount.Graphics) {REY_LOG_EX("k >= QCount.Graphics");}}
    void                  Compute_CHK2_(uint32_t k) { _CHK1_(); if (k >= QCount.Graphics) {REY_LOG_EX("k >= QCount.Graphics");}}
    void                 Transfer_CHK2_(uint32_t k) { _CHK1_(); if (k >= QCount.Graphics) {REY_LOG_EX("k >= QCount.Graphics");}}
    void            SparseBinding_CHK2_(uint32_t k) { _CHK1_(); if (k >= QCount.Graphics) {REY_LOG_EX("k >= QCount.Graphics");}}

              VkQueue        GraphicsQ (uint32_t k) {      Graphics_CHK2_(k); return amVK_2D_Queues[Used_QFamID.Graphics][k]; }
              VkQueue     VideoEncodeQ (uint32_t k) {   VideoEncode_CHK2_(k); return amVK_2D_Queues[Used_QFamID.VideoEncode][k]; }
              VkQueue     VideoDecodeQ (uint32_t k) {   VideoDecode_CHK2_(k); return amVK_2D_Queues[Used_QFamID.VideoDecode][k]; }
              VkQueue         ComputeQ (uint32_t k) {       Compute_CHK2_(k); return amVK_2D_Queues[Used_QFamID.Compute][k]; }
              VkQueue        TransferQ (uint32_t k) {      Transfer_CHK2_(k); return amVK_2D_Queues[Used_QFamID.Transfer][k]; }
              VkQueue   SparseBindingQ (uint32_t k) { SparseBinding_CHK2_(k); return amVK_2D_Queues[Used_QFamID.SparseBinding][k]; }
};