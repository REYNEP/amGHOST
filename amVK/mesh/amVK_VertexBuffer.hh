#pragma once
#include "amVK_Device.hh"
#include "amVK_Vertex.hh"

class amVK_VertexBuffer {
  public:
    amVK_VertexBuffer(amVK_Device *D, REY_Array<amVK_Vertex> Vertices) { 
        this->D = D;
        this->Vertices = Vertices;
        this->CI.size  = sizeof(amVK_Vertex) * Vertices.n;
    }
   ~amVK_VertexBuffer(void) {}

  public:
    amVK_Device *D;
    REY_Array<amVK_Vertex> Vertices;
    VkBuffer vk_Buffer;
    VkMemoryRequirements vk_MemoryReq;
    VkDeviceMemory vk_DeviceMemory;
    void* vk_MappedMemoryData = nullptr;
    //    vk_MemoryReq.size  v/s  CI.size ..... 🤔

  public:
    VkBufferCreateInfo CI = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,

        .size = sizeof(amVK_Vertex) * 0,
        .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,

        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
            .queueFamilyIndexCount = 0,
            .pQueueFamilyIndices = nullptr
    };

    void     CreateBuffer(void);
    bool called_GetBufferMemoryRequirements = false;
    void        GetBufferMemoryRequirements(void);
    void   AllocateMemory(void);
    void        MapMemory(void);
    void   CopyIntoMemory(void);
    void      UnMapMemory(void);
    void BindBufferMemory(void);

  public:
    VkMemoryAllocateInfo AI = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .pNext = nullptr,
        .allocationSize = 0,
        .memoryTypeIndex = 0
    };

    VkMemoryRequirements MemReq = {
        .size = 0,
        .alignment = 0,
        .memoryTypeBits = 0
    };

  public:
    VkDeviceSize offsets[1] = { 0 };
    void  CMDBindVertexBuffers(VkCommandBuffer CMDBUF) {
        vkCmdBindVertexBuffers(CMDBUF, 0, 1, &vk_Buffer, offsets);
    }
    void  CMDDraw(VkCommandBuffer CMDBUF) {
        vkCmdDraw(CMDBUF, Vertices.n, 1, 0, 0);
    }
};