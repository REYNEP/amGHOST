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
}
void amVK_DeviceQueues::generate_1D_QCIs(void) {
    this->generate_1D_QFam_QCount();

        REY_Array_LOOP(amVK_1D_QFam_QCount, k) {
            if (amVK_1D_QFam_QCount[k] > 0) {
                amVK_DeviceQueues::s_CI_Template.queueFamilyIndex = k;
                amVK_DeviceQueues::s_CI_Template.queueCount = amVK_1D_QFam_QCount[k];

                amVK_1D_QCIs.push_back(amVK_DeviceQueues::s_CI_Template);
            }
        }

    called_generate_1D_QCIs = true;
}
void amVK_DeviceQueues::REY_Calculate_amVK_1D_QFam_QCount_EXT_incUserPushed(void) {
    if        (amVK_1D_QFam_QCount_EXT_incUserPushed.data != nullptr) {
        delete amVK_1D_QFam_QCount_EXT_incUserPushed.data;
    }

    REY_Array_RESERVE(amVK_1D_QFam_QCount_EXT_incUserPushed, this->GPUProps->amVK_1D_GPUs_QFAMs.n, 0);

    REY_Array_LOOP(amVK_1D_QCIs, k) {
        uint32_t QFamID = amVK_1D_QCIs[k].queueFamilyIndex;
        uint32_t QCount = amVK_1D_QCIs[k].queueCount;
           this->amVK_1D_QFam_QCount_EXT_incUserPushed[QFamID] += QCount;
    }

    called_REY_Calculate_amVK_1D_QFam_QCount_EXT_incUserPushed = true;
}
void amVK_DeviceQueues::sync_1D_QCIs(VkDeviceCreateInfo* DeviceCI) {
    if (    amVK_1D_QCIs.data == nullptr) {
        generate_1D_QCIs();
    }
    DeviceCI->queueCreateInfoCount = this->amVK_1D_QCIs.neXt;
    DeviceCI->pQueueCreateInfos    = this->amVK_1D_QCIs.data;
}
void amVK_DeviceQueues::GetDeviceQueues(VkDevice vk_Device) {
    if (called_REY_Calculate_amVK_1D_QFam_QCount_EXT_incUserPushed == false) {
        this-> REY_Calculate_amVK_1D_QFam_QCount_EXT_incUserPushed();
    }
    this->amVK_2D_Queues.reserve(amVK_1D_QFam_QCount_EXT_incUserPushed.n);

    REY_Array_LOOP(amVK_1D_QFam_QCount_EXT_incUserPushed, k) {
        if        (amVK_1D_QFam_QCount_EXT_incUserPushed[k] == 0) { continue; }

        this->amVK_2D_Queues[k].reserve(amVK_1D_QFam_QCount_EXT_incUserPushed[k]);

        for (uint32_t i = 0, lim = amVK_1D_QFam_QCount_EXT_incUserPushed[k]; i < lim; i++) {
            vkGetDeviceQueue(vk_Device, k, i, &this->amVK_2D_Queues[k][i]);
        }
    }
}