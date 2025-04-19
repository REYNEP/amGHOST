#pragma once
#include "amVK/common/amVK.hh"
#include "amVK/common/amVK_GPU.hh"

namespace amVK_Array {
    class QCI {
      private:
        static inline const float Default_QP = 1.0f;
        static inline VkDeviceQueueCreateInfo Default = {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .queueFamilyIndex = 0,
            .queueCount = 1,
            .pQueuePriorities = &Default_QP
        };
        
      public:
        REY_ArrayDYN<VkDeviceQueueCreateInfo> TheArray;

        void                    init_Default(void) {TheArray.push_back(this->Default);}
        VkDeviceQueueCreateInfo grab_Default(void) { return  TheArray[0]; }
        VkDeviceQueueCreateInfo* ptr_Default(void) { return &TheArray[0]; } 
            // [Suggested For Use]

      public:
        QCI(void) {
            init_Default();
        }

      public:
        void   select_QFAM_Graphics     (amVK_GPU_Index GPU_ID);
        void      set_QFAM_Index          (uint32_t qFAM_Index) {
            this->ptr_Default()->queueFamilyIndex = qFAM_Index;
        }
    };
};