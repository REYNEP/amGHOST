#include "amVK_CommandPool.hh"
#include "amVK/utils/amVK_log.hh"

void amVK_CommandPool::CreateCommandPool(amVK_Sync::CommandPoolCreateFlags flags) {
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
#include "amVK_CommandPoolMAN.hh"
void amVK_CommandPoolMAN::AllocateCommandBuffers(VkCommandPool CMDPool, uint32_t N, REY_ArrayDYN<VkCommandBuffer>* BUFFs_PTR) {
    this->s_AI.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    this->s_AI.commandPool = CMDPool;
    this->s_AI.commandBufferCount = N;

    REY_Array<VkCommandBuffer> TMP;
        TMP.reserve(N);

        VkResult return_code = vkAllocateCommandBuffers(this->D->vk_Device, &this->s_AI, TMP.data);
        amVK_return_code_log( "vkAllocateCommandBuffers()" );

    REY_Array_LOOP(TMP, k) {
        BUFFs_PTR->push_back(TMP[k]);
    }
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
VkCommandBuffer amVK_CommandBufferPrimary::BeginCommandBuffer(amVK_Sync::CommandBufferBeginFlags flags) {
    this->BI.flags = flags;

        VkResult return_code = vkBeginCommandBuffer(this->vk_CommandBuffer, &BI);
        amVK_return_code_log( "vkBeginCommandBuffer()" );

    return this->vk_CommandBuffer;
}
    // Ending the render pass will add an implicit barrier, transitioning the frame buffer color attachment to
    // `VK_IMAGE_LAYOUT_PRESENT_SRC_KHR` for presenting it to the windowing system
void amVK_CommandBufferPrimary::EndCommandBuffer(void) {
    VkResult return_code = vkEndCommandBuffer(this->vk_CommandBuffer);
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
        REY_LOG_EX("D->GPUProps->called_GetPhysicalDeviceQueueFamilyProperties == false")
    }

    REY_Array_RESERVE(CATs.amVK_1D_QFAMs_CMDPOOL, D->GPUProps->amVK_1D_GPUs_QFAMs.n, nullptr);
}

/** \see amVK_GPUProps::amVK_QueueFamilyIndex + \see amVK_Device::amVK_1D_QCIs */
amVK_CommandPool* amVK_CommandPoolMAN::init_CMDPool_USER(uint32_t queueFamilyIndex)
{
    if              (queueFamilyIndex >= D->GPUProps->get_QFamCount()) {
        REY_LOG_EX( "queueFamilyIndex >= D->GPUProps->get_QFamCount()")
    }
    if (D->Queues.amVK_1D_QFAMs_QCount_TOTAL[queueFamilyIndex] == 0) {
        REY_LOG_EX( "0 Queues Queried from QFam-" << queueFamilyIndex << "\n    Stil Initializing");
    }

    CATs.amVK_1D_QFAMs_CMDPOOL[queueFamilyIndex] = new amVK_CommandPool(D, queueFamilyIndex);
    return CATs.amVK_1D_QFAMs_CMDPOOL[queueFamilyIndex];
}