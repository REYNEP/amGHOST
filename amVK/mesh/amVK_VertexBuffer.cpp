#include "amVK_VertexBuffer.hh"
#include "amVK/utils/amVK_log.hh"

void amVK_VertexBuffer::CreateBuffer(void) {
    VkResult return_code = vkCreateBuffer(this->D->vk_Device, &CI, nullptr, &this->vk_Buffer);
    amVK_return_code_log( "vkCreateBuffer()" );
}

void amVK_VertexBuffer::GetBufferMemoryRequirements(void) {
         vkGetBufferMemoryRequirements(this->D->vk_Device, this->vk_Buffer, &this->vk_MemoryReq);
    called_GetBufferMemoryRequirements = true;
}

void amVK_VertexBuffer::AllocateMemory(void) {
    if(called_GetBufferMemoryRequirements == false) {
        this->GetBufferMemoryRequirements();
    }
    if (this->D->GPU_Props->called_REY_CategorizeMemoryHeaps == false) {
        this->D->GPU_Props->       REY_CategorizeMemoryHeaps();
    }
        AI.allocationSize  = vk_MemoryReq.size;
        AI.memoryTypeIndex = this->D->GPU_Props->MEMTypeID.CPU_GPU_Synced;

    VkResult return_code = vkAllocateMemory(this->D->vk_Device, &AI, nullptr, &this->vk_DeviceMemory);
    amVK_return_code_log( "vkAllocateMemory()" );
}

void      amVK_VertexBuffer::MapMemory(void) {
    VkResult return_code = vkMapMemory(D->vk_Device, vk_DeviceMemory, 0, vk_MemoryReq.size, 0, &vk_MappedMemoryData);
    amVK_return_code_log( "vkMapMemory()" );
}
void   amVK_VertexBuffer::CopyIntoMemory(void) {
    REY_memcpy(vk_MappedMemoryData, Vertices.data, CI.size);
}
void      amVK_VertexBuffer::UnMapMemory(void) {
    vkUnmapMemory(D->vk_Device, vk_DeviceMemory);
}
void      amVK_VertexBuffer::BindBufferMemory(void) {
    VkResult return_code = vkBindBufferMemory(D->vk_Device, vk_Buffer, vk_DeviceMemory, 0);
    amVK_return_code_log( "vkBindBufferMemory()" );
}