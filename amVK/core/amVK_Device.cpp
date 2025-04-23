#include "amVK_Device.hh"
#include "amVK/utils/amVK_log.hh"
#include "amVK_InstancePropsEXT.hh"

void amVK_Device::CreateDevice(uint32_t GraphicQueueCount) {
    this->Queues.QCount.Graphics = GraphicQueueCount;
    this->sync_1D_QCIs();
    
        VkResult return_code = vkCreateDevice(vk_PhysicalDevice, &CI, nullptr, &this->vk_Device);
        amVK_return_code_log( "vkCreateDevice()" );     // above variable "return_code" can't be named smth else

    log_1D_GPU_EXTs_Enabled(return_code);
}
void amVK_Device::DestroyDevice(void) {
    vkDestroyDevice(this->vk_Device, nullptr);
}










/*

   _____ _____  _    _         ______      _                 _                 
  / ____|  __ \| |  | |       |  ____|    | |               (_)                
 | |  __| |__) | |  | |       | |__  __  _| |_ ___ _ __  ___ _  ___  _ __  ___ 
 | | |_ |  ___/| |  | |       |  __| \ \/ / __/ _ \ '_ \/ __| |/ _ \| '_ \/ __|
 | |__| | |    | |__| |       | |____ >  <| ||  __/ | | \__ \ | (_) | | | \__ \
  \_____|_|     \____/        |______/_/\_\\__\___|_| |_|___/_|\___/|_| |_|___/
                   ______ ______                                               
                  |______|______|                                              

 */

#include "REY_STDWrap.hh"
void amVK_Device::addTo_1D_GPU_EXTs_Enabled(const char* extName) {
        // VK_KHR_swapchain
    if (GPUProps->isExtensionAvailable(extName)) {
        char  *dont_lose = REY_strcpy(extName);

        REY_ArrayDYN_PUSH_BACK(this->amVK_1D_GPU_EXTs_Enabled) = dont_lose;

        this->CI.enabledExtensionCount = this->amVK_1D_GPU_EXTs_Enabled.neXt;
        this->CI.ppEnabledExtensionNames = this->amVK_1D_GPU_EXTs_Enabled.data;
    }
    else {
        REY_LOG_notfound("Vulkan (Physical) Device Extension:- " << extName);
    }
}

void amVK_Device::log_1D_GPU_EXTs_Enabled(VkResult ret) {
    if (ret != VK_SUCCESS) {
        REY_LOG_status("vkCreateInstance() failed 😶‍🌫️");
    }
    else {
        REY_LOG_status("         Enabled VULKAN Extensions' Name:- ");
        for (uint32_t k = 0,     lim = amVK_1D_GPU_EXTs_Enabled.n;     k < lim; k++) {
            REY_LOG_status("              | " << amVK_1D_GPU_EXTs_Enabled[k]);
        }
    }
}








/*

              __      ___  __         _____             _           ____                             
              \ \    / / |/ /        |  __ \           (_)         / __ \                            
   __ _ _ __ __\ \  / /| ' /         | |  | | _____   ___  ___ ___| |  | |_   _  ___ _   _  ___  ___ 
  / _` | '_ ` _ \ \/ / |  <          | |  | |/ _ \ \ / / |/ __/ _ \ |  | | | | |/ _ \ | | |/ _ \/ __|
 | (_| | | | | | \  /  | . \         | |__| |  __/\ V /| | (_|  __/ |__| | |_| |  __/ |_| |  __/\__ \
  \__,_|_| |_| |_|\/   |_|\_\        |_____/ \___| \_/ |_|\___\___|\___\_\\__,_|\___|\__,_|\___||___/
                          ______ ______                                                              
                         |______|______|                                                             

*/

#include "amVK_DeviceQueues.hh"
amVK_DeviceQueues::amVK_DeviceQueues(amVK_GPUProps *GPUProps) {
    this->GPUProps = GPUProps;
    this->Used_QFamID.Graphics      = GPUProps->QFamID.Graphics;
    this->Used_QFamID.VideoEncode   = GPUProps->QFamID.VideoEncode;
    this->Used_QFamID.VideoDecode   = GPUProps->QFamID.VideoDecode;
    this->Used_QFamID.Compute       = GPUProps->QFamID.Compute;
    this->Used_QFamID.Transfer      = GPUProps->QFamID.Transfer;
    this->Used_QFamID.SparseBinding = GPUProps->QFamID.SparseBinding;

    REY_Array_RESERVE(amVK_1D_QFAMs_QCount_Internal, GPUProps->get_QFamCount(), 0);
    REY_Array_RESERVE(amVK_1D_QFAMs_QCount_TOTAL,    GPUProps->get_QFamCount(), 0);
    REY_Array_RESERVE(amVK_1D_QFAMs_QCount_USER,     GPUProps->get_QFamCount(), 0);
}
void amVK_DeviceQueues::generate_1D_QCIs(void) {
    this->generate_1D_QFam_QCount();

        REY_Array_LOOP(amVK_1D_QFAMs_QCount_Internal, k) {
            uint32_t queueCount;
                queueCount = amVK_1D_QFAMs_QCount_Internal[k] + amVK_1D_QFAMs_QCount_USER[k];
            if (queueCount > 0) {
                amVK_DeviceQueues::s_CI_Template.queueFamilyIndex = k;
                amVK_DeviceQueues::s_CI_Template.queueCount = queueCount;

                amVK_1D_QCIs.push_back(amVK_DeviceQueues::s_CI_Template);
            }
            this->amVK_1D_QFAMs_QCount_TOTAL[k] = queueCount;
        }

    called_generate_1D_QCIs = true;
}
void amVK_DeviceQueues::sync_1D_QCIs(VkDeviceCreateInfo* DeviceCI) {
    if (    amVK_1D_QCIs.data == nullptr) {
        generate_1D_QCIs();
    }
    DeviceCI->queueCreateInfoCount = this->amVK_1D_QCIs.neXt;
    DeviceCI->pQueueCreateInfos    = this->amVK_1D_QCIs.data;
}
void amVK_DeviceQueues::GetDeviceQueues(VkDevice vk_Device) {
    TheArrays.Graphics      .reserve(QCount.Graphics);
    TheArrays.VideoEncode   .reserve(QCount.VideoEncode);
    TheArrays.VideoDecode   .reserve(QCount.VideoDecode);
    TheArrays.Compute       .reserve(QCount.Compute);
    TheArrays.Transfer      .reserve(QCount.Transfer);
    TheArrays.SparseBinding .reserve(QCount.SparseBinding);

    REY_Array<uint32_t>   amVK_1D_QFAMs_QCount_Gotten;
        REY_Array_RESERVE(amVK_1D_QFAMs_QCount_Gotten, amVK_1D_QFAMs_QCount_USER.n, 0);

    #define _GetDeviceQueue(vk_Device, QFAM_k, pQueue)   \
           vkGetDeviceQueue(vk_Device, QFAM_k, amVK_1D_QFAMs_QCount_Gotten[QFAM_k], pQueue);  \
           amVK_1D_QFAMs_QCount_Gotten[QFAM_k]++;

    for (int i = 0;  i < QCount.Graphics; i++)       { _GetDeviceQueue(vk_Device, Used_QFamID.Graphics, &this->TheArrays.Graphics[i]);           }
    for (int i = 0;  i < QCount.VideoEncode; i++)    { _GetDeviceQueue(vk_Device, Used_QFamID.VideoEncode, &this->TheArrays.VideoEncode[i]);     }
    for (int i = 0;  i < QCount.VideoDecode; i++)    { _GetDeviceQueue(vk_Device, Used_QFamID.VideoDecode, &this->TheArrays.VideoDecode[i]);     }
    for (int i = 0;  i < QCount.Compute; i++)        { _GetDeviceQueue(vk_Device, Used_QFamID.Compute, &this->TheArrays.Compute[i]);             }
    for (int i = 0;  i < QCount.Transfer; i++)       { _GetDeviceQueue(vk_Device, Used_QFamID.Transfer, &this->TheArrays.Transfer[i]);           }
    for (int i = 0;  i < QCount.SparseBinding; i++)  { _GetDeviceQueue(vk_Device, Used_QFamID.SparseBinding, &this->TheArrays.SparseBinding[i]); }

    this->  TheArrays.amVK_2D_QFAMs_Queues.reserve(amVK_1D_QFAMs_QCount_USER.n);
    REY_Array_LOOP   (amVK_1D_QFAMs_QCount_USER, k) {
        if           (amVK_1D_QFAMs_QCount_USER[k] > 0) {
            TheArrays.amVK_2D_QFAMs_Queues[k].reserve(amVK_1D_QFAMs_QCount_USER[k]);

            for (uint32_t i = 0, lim = amVK_1D_QFAMs_QCount_USER[k]; i < lim; i++) {
                _GetDeviceQueue(vk_Device, k, &this->TheArrays.amVK_2D_QFAMs_Queues[k][i]);
            }
        }
    }

    called_GetDeviceQueues = true;
}