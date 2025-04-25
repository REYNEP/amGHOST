#pragma once
#include <vulkan/vulkan.h>

    // PO = PipelineObject
namespace amVK_PO 
{
    struct  VertexInputRate {
            VertexInputRate(VkVertexInputRate rate): _value_(rate) {}
            inline operator VkVertexInputRate() const {return _value_;}       // static_cast<> Operator
                            VkVertexInputRate _value_;
            static inline   VkVertexInputRate VERTEX_INDEX   = VK_VERTEX_INPUT_RATE_VERTEX;
            static inline   VkVertexInputRate INSTANCE_INDEX = VK_VERTEX_INPUT_RATE_INSTANCE;
    };
};