#pragma once
#include "amVK_Device.hh"
#include "amVK_Vertex.hh"

class amVK_VertexBuffer {
  public:
    amVK_VertexBuffer(amVK_Device *D, uint64_t bufferSize) : D(D) { CI.size = bufferSize; }
   ~amVK_VertexBuffer(void) {}

  public:
    amVK_Device *D;
    VkBuffer vk_Buffer;

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

    void CreateBuffer(void) {
        VkResult return_code = vkCreateBuffer(this->D->vk_Device, &CI, nullptr, &this->vk_Buffer);
        amVK_return_code_log( "vkCreateBuffer()" );     // above variable "return_code" can't be named smth else
    }
};