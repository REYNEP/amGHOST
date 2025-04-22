#pragma once
#include "amVK_Device.hh"

class amVK_PipelineLayout {
  public:
    amVK_PipelineLayout(amVK_Device *D) : D(D) {}
   ~amVK_PipelineLayout(void) {}

  public:
    amVK_Device *D;
    VkPipelineLayout vk_PipelineLayout = nullptr;

  public:
    VkPipelineLayoutCreateInfo CI = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .setLayoutCount = 0,
        .pSetLayouts = nullptr,
        .pushConstantRangeCount = 0,
        .pPushConstantRanges = nullptr
    };

  public:
    void CreatePipelineLayout(void);
};