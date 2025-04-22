#pragma once
#include <vulkan/vulkan.h>

    // PO = PipelineObject
namespace amVK_PO {
    namespace VertexInputRate
    {
        inline constexpr VkVertexInputRate VERTEX_INDEX   = VK_VERTEX_INPUT_RATE_VERTEX;
        inline constexpr VkVertexInputRate INSTANCE_INDEX = VK_VERTEX_INPUT_RATE_INSTANCE;
    };
};