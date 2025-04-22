#include "amVK_CommandPool.hh"
#include "amVK/utils/amVK_log.hh"

void amVK_CommandPool::CreateCommandPool( amVK_Sync::CommandPoolCreateFlags flags) {
    CI.flags = flags;
    VkResult return_code = vkCreateCommandPool(this->D->vk_Device, &this->CI, nullptr, &this->vk_CommandPool);
    amVK_return_code_log( "vkCreateCommandPool()" );    // above variable "return_code" can't be named smth else
}
void amVK_CommandPool::DestroyCommandPool(void) {
                     vkDestroyCommandPool(this->D->vk_Device, vk_CommandPool, nullptr);
}


/*

     ___       __       __        ______     ______     ___   .___________. _______ 
    /   \     |  |     |  |      /  __  \   /      |   /   \  |           ||   ____|
   /  ^  \    |  |     |  |     |  |  |  | |  ,----'  /  ^  \ `---|  |----`|  |__   
  /  /_\  \   |  |     |  |     |  |  |  | |  |      /  /_\  \    |  |     |   __|  
 /  _____  \  |  `----.|  `----.|  `--'  | |  `----./  _____  \   |  |     |  |____ 
/__/     \__\ |_______||_______| \______/   \______/__/     \__\  |__|     |_______|
                                                                                    

 */
REY_Array<VkCommandBuffer> amVK_CommandPool::AllocateCommandBuffers(void) 
{
    this->AI.commandPool = this->vk_CommandPool;
    this->vk_CommandBuffers.reserve(this->AI.commandBufferCount); 

        VkResult return_code = vkAllocateCommandBuffers(this->D->vk_Device, &this->AI, this->vk_CommandBuffers.data);
        amVK_return_code_log( "vkAllocateCommandBuffers()" );

    return vk_CommandBuffers;
}
void  amVK_CommandPool::FreeCommandBuffers(void) {
                      vkFreeCommandBuffers(this->D->vk_Device, vk_CommandPool, vk_CommandBuffers.n, vk_CommandBuffers.data);
}


/*

  _______ .______    __    __         ______   ______   .___  ___. .___  ___.      ___      .__   __.  _______  
 /  _____||   _  \  |  |  |  |       /      | /  __  \  |   \/   | |   \/   |     /   \     |  \ |  | |       \ 
|  |  __  |  |_)  | |  |  |  |      |  ,----'|  |  |  | |  \  /  | |  \  /  |    /  ^  \    |   \|  | |  .--.  |
|  | |_ | |   ___/  |  |  |  |      |  |     |  |  |  | |  |\/|  | |  |\/|  |   /  /_\  \   |  . `  | |  |  |  |
|  |__| | |  |      |  `--'  |      |  `----.|  `--'  | |  |  |  | |  |  |  |  /  _____  \  |  |\   | |  '--'  |
 \______| | _|       \______/   _____\______| \______/  |__|  |__| |__|  |__| /__/     \__\ |__| \__| |_______/ 
                               |______|                                                                         
 
 */
VkCommandBuffer amVK_CommandPool::BeginCommandBuffer(void) {
    VkResult return_code = vkBeginCommandBuffer(this->get_active_CMDBUF(), &g_CMDBUF_BI);
    amVK_return_code_log( "vkBeginCommandBuffer()" );

    return this->get_active_CMDBUF();
}
    // Ending the render pass will add an implicit barrier, transitioning the frame buffer color attachment to
    // `VK_IMAGE_LAYOUT_PRESENT_SRC_KHR` for presenting it to the windowing system
void amVK_CommandPool::EndCommandBuffer(void) {
    VkResult return_code = vkEndCommandBuffer(this->get_active_CMDBUF());
    amVK_return_code_log( "vkEndCommandBuffer()" );
}






/*

              __      ___  __         _____ __  __ _____  _____            _ __  __                                   
              \ \    / / |/ /        / ____|  \/  |  __ \|  __ \          | |  \/  |                                  
   __ _ _ __ __\ \  / /| ' /        | |    | \  / | |  | | |__) |__   ___ | | \  / | __ _ _ __   __ _  __ _  ___ _ __ 
  / _` | '_ ` _ \ \/ / |  <         | |    | |\/| | |  | |  ___/ _ \ / _ \| | |\/| |/ _` | '_ \ / _` |/ _` |/ _ \ '__|
 | (_| | | | | | \  /  | . \        | |____| |  | | |__| | |  | (_) | (_) | | |  | | (_| | | | | (_| | (_| |  __/ |   
  \__,_|_| |_| |_|\/   |_|\_\        \_____|_|  |_|_____/|_|   \___/ \___/|_|_|  |_|\__,_|_| |_|\__,_|\__, |\___|_|   
                          ______ ______                                                                __/ |          
                         |______|______|                                                              |___/           

*/
#include "amVK_CommandPoolMAN.hh"
amVK_CommandPoolMAN::amVK_CommandPoolMAN(amVK_Device *D) {
    this->D = D;
    
    if            ( D->GPUProps->called_GetPhysicalDeviceQueueFamilyProperties == false ) {
        REY_LOG_EX("D->GPU_Props->called_GetPhysicalDeviceQueueFamilyProperties == false")
    }

    REY_Array_RESERVE(amVK_1D_QFAMs_CMDPOOL, D->GPUProps->amVK_1D_GPUs_QFAMs.n, nullptr);
}

/** \see amVK_GPUProps::amVK_QueueFamilyIndex + \see amVK_Device::amVK_1D_QCIs */
amVK_CommandPool* amVK_CommandPoolMAN::InitializeCommandPool(uint32_t queueFamilyIndex)
{
    if              (queueFamilyIndex >= D->Queues.amVK_2D_Queues.n) {
        REY_LOG_EX( "queueFamilyIndex >= D->Queues.amVK_2D_Queues.n")
    }
    if (D->Queues.amVK_1D_QFam_QCount_EXT_incUserPushed[queueFamilyIndex] == 0) {
        REY_LOG_EX( "0 Queues Queried from QFam-" << queueFamilyIndex << "\n    Stil Initializing");
    }

    amVK_1D_QFAMs_CMDPOOL[queueFamilyIndex] = new amVK_CommandPool(D, queueFamilyIndex);
    return amVK_1D_QFAMs_CMDPOOL[queueFamilyIndex];
}