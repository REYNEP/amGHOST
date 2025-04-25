#pragma once
#include "amVK_CommandPool.hh"
#include "amVK_CommandBufferPrimary.hh"

/**
 * As per QueueFamily
 * When you Create VkDevice, you already define How many Queues/QueueFamilities you are gonna use
 * 
 *  This is a CommandPool Manager based on the #QueueFamilies on a GPU/PhysicalDevice
 */
class amVK_CommandPoolMAN {
  public:
    amVK_CommandPoolMAN(amVK_Device *D);
   ~amVK_CommandPoolMAN(void) {}

  public:
    amVK_Device *D = nullptr;

  public:
    struct amVK_CommandPoolCATs {
           amVK_CommandPool*       Graphics = nullptr;
           amVK_CommandPool*    VideoEncode = nullptr;
           amVK_CommandPool*    VideoDecode = nullptr;
           amVK_CommandPool*        Compute = nullptr; 
           amVK_CommandPool*       Transfer = nullptr;
           amVK_CommandPool*  SparseBinding = nullptr;
        REY_Array<amVK_CommandPool *> amVK_1D_QFAMs_CMDPOOL;    // [USER Ones] 1 CMDPOOL per QFam
    } CATs;

    #define _CHK1_(_X_)             if (CATs._X_) {            REY_LOG_EX("CATs." << #_X_ << " already exists! Can't initialize again 😫");                  }
    #define _CMN1_(_X_) \
        _CHK1_(_X_)     \
          CATs._X_ = new amVK_CommandPool(D, D->Queues.Used_QFamID._X_);

    void init_CMDPool_Graphics(void)                { _CMN1_(Graphics);      }
    void init_CMDPool_VideoEncode(void)             { _CMN1_(VideoEncode);   }
    void init_CMDPool_VideoDecode(void)             { _CMN1_(VideoDecode);   }
    void init_CMDPool_Compute(void)                 { _CMN1_(Compute);       }
    void init_CMDPool_Transfer(void)                { _CMN1_(Transfer);      }
    void init_CMDPool_SparseBinding(void)           { _CMN1_(SparseBinding); }
    amVK_CommandPool* 
         init_CMDPool_USER(uint32_t queueFamilyIndex);

    #define _CHK2_(_X_) if (CATs._X_->vk_CommandPool) { REY_LOG_EX("CATs." << #_X_ << "->vk_CommandPool already exists! Can't Create again 😫");}
    #define _CMN2_(_X_) \
        _CHK2_(_X_)     \
          CATs._X_->CreateCommandPool(flags)

    #define _PARAM2_ amVK_Sync::CommandPoolCreateFlags flags
    void CreateCommandPool_Graphics     (_PARAM2_)  { _CMN2_(Graphics);      }
    void CreateCommandPool_VideoEncode  (_PARAM2_)  { _CMN2_(VideoEncode);   }
    void CreateCommandPool_VideoDecode  (_PARAM2_)  { _CMN2_(VideoDecode);   }
    void CreateCommandPool_Compute      (_PARAM2_)  { _CMN2_(Compute);       }
    void CreateCommandPool_Transfer     (_PARAM2_)  { _CMN2_(Transfer);      }
    void CreateCommandPool_SparseBinding(_PARAM2_)  { _CMN2_(SparseBinding); }

    struct amVK_CommandBuffersPRIMARY {
           REY_ArrayDYN<VkCommandBuffer>      Graphics;
           REY_ArrayDYN<VkCommandBuffer>   VideoEncode;
           REY_ArrayDYN<VkCommandBuffer>   VideoDecode;
           REY_ArrayDYN<VkCommandBuffer>       Compute;
           REY_ArrayDYN<VkCommandBuffer>      Transfer;
           REY_ArrayDYN<VkCommandBuffer> SparseBinding;
        REY_Array<REY_ArrayDYN<VkCommandBuffer>> amVK_2D_QFAMs_CMDBUFFs1;
    } BUFFs1;

    #define _CHK3_(_X_)    if (CATs._X_ == nullptr)                 { REY_LOG_EX("CATs." << #_X_ << " doesn't exists! initialize & create it first TwT 😫");}
    #define _CHK4_(_X_)    if (CATs._X_->vk_CommandPool == nullptr) { REY_LOG_EX("CATs." << #_X_ << "->vk_CommandPool doesn't exists! CreateCommandPool it first TwT 😫");}
    
    #define _CMN11_()        this->s_AI.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    #define _CMN12_()        this->s_AI.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;

    #define _CMN21_(_X_)     AllocateCommandBuffers(CATs._X_->vk_CommandPool, k, &BUFFs1._X_);
    #define _CMN22_(_X_)     AllocateCommandBuffers(CATs._X_->vk_CommandPool, k, &BUFFs2._X_);

    #define _CMN100_(_X_)   \
        _CHK3_(_X_);        \
        _CHK4_(_X_);        \
        _CMN11_();          \
        _CMN21_(_X_)        \
    
    #define _CMN200_(_X_)   \
        _CHK3_(_X_);        \
        _CHK4_(_X_);        \
        _CMN12_();          \
        _CMN22_(_X_)        \

    void AllocateCommandBuffers(VkCommandPool CMDPool, uint32_t N, REY_ArrayDYN<VkCommandBuffer>* BUFFs_PTR);

    void AllocateCommandBuffers1_Graphics     (uint32_t k) { _CMN100_(Graphics);      }
    void AllocateCommandBuffers1_VideoEncode  (uint32_t k) { _CMN100_(VideoEncode);   }
    void AllocateCommandBuffers1_VideoDecode  (uint32_t k) { _CMN100_(VideoDecode);   }
    void AllocateCommandBuffers1_Compute      (uint32_t k) { _CMN100_(Compute);       }
    void AllocateCommandBuffers1_Transfer     (uint32_t k) { _CMN100_(Transfer);      }
    void AllocateCommandBuffers1_SparseBinding(uint32_t k) { _CMN100_(SparseBinding); }

    void AllocateCommandBuffers2_Graphics     (uint32_t k) { _CMN200_(Graphics);      }
    void AllocateCommandBuffers2_VideoEncode  (uint32_t k) { _CMN200_(VideoEncode);   }
    void AllocateCommandBuffers2_VideoDecode  (uint32_t k) { _CMN200_(VideoDecode);   }
    void AllocateCommandBuffers2_Compute      (uint32_t k) { _CMN200_(Compute);       }
    void AllocateCommandBuffers2_Transfer     (uint32_t k) { _CMN200_(Transfer);      }
    void AllocateCommandBuffers2_SparseBinding(uint32_t k) { _CMN200_(SparseBinding); }

    struct amVK_CommandBuffersSECONDARY {
           REY_ArrayDYN<VkCommandBuffer>      Graphics;
           REY_ArrayDYN<VkCommandBuffer>   VideoEncode;
           REY_ArrayDYN<VkCommandBuffer>   VideoDecode;
           REY_ArrayDYN<VkCommandBuffer>       Compute;
           REY_ArrayDYN<VkCommandBuffer>      Transfer;
           REY_ArrayDYN<VkCommandBuffer> SparseBinding;
        REY_Array<REY_ArrayDYN<VkCommandBuffer>> amVK_2D_QFAMs_CMDBUFFs2;
    } BUFFs2;

    static inline VkCommandBufferAllocateInfo s_AI = {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .pNext = nullptr,

        .commandPool = nullptr,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = 1
    };
};