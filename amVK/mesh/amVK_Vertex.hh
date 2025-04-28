#pragma once

struct amVK_Vertex {
    float position[3];
    float color[4];
};


/** C++17 Feature:- Inline Global Variable [no need to use `extern` anymore 💁‍♀️] */
#include "amVK/common/amVK_PipelineObjects.hh"
inline VkVertexInputBindingDescription amVK_VertexInputBinding = {
    .binding = 0,
    .stride = sizeof(amVK_Vertex),
    .inputRate = amVK_PO::VertexInputRate::INSTANCE_INDEX
};

// <vulkan/vulkan.h> --> "vk_platform.h" --> `stddef.h` --> offsetof()
#include "amVK/common/amVK_ColorSpace.hh"
inline VkVertexInputAttributeDescription amVK_VertexInputAttributs_BAKED[2] = {
    {
        .location = 0,
        .binding = 0,
        .format = amVK_IF::RGB_32bpc_SFLOAT,
        .offset = offsetof(amVK_Vertex, position)
    },
    {
        .location = 1,
        .binding = 0,
        .format = amVK_IF::RGBA_32bpc_SFLOAT,
        .offset = offsetof(amVK_Vertex, color)
    }
};

#include "REY_Array.hh"
inline REY_Array<VkVertexInputAttributeDescription> amVK_VertexInputAttributs(amVK_VertexInputAttributs_BAKED, 2, 2);

namespace amVK_PSCI {
        // PSCI = PipelineStateCreateInfo
    inline VkPipelineVertexInputStateCreateInfo VertexInput = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .vertexBindingDescriptionCount = 0, // 1,
        .pVertexBindingDescriptions = nullptr, // &amVK_VertexInputBinding,
        .vertexAttributeDescriptionCount = 0, // 2,
        .pVertexAttributeDescriptions = nullptr// amVK_VertexInputAttributs_BAKED
    };
};