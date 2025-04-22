#pragma once
#include "amVK_PipelineLayout.hh"
#include "amVK_RenderPassFBs.hh"
#include "amVK/common/amVK_PipelineObjects.hh"
#include "amVK/mesh/amVK_Vertex.hh"
#include "amVK/mesh/amVK_GeoMetry.hh"

class amVK_PipelineGRAPHICS {
  public:
    amVK_PipelineGRAPHICS(amVK_RenderPassFBs *RP_FBs) : RP_FBs(RP_FBs) {
        D = RP_FBs->RP->D;
        PL = new amVK_PipelineLayout(D);
    }
   ~amVK_PipelineGRAPHICS(void) {}

  public:
    amVK_Device *D = nullptr;
    amVK_RenderPassFBs *RP_FBs;
    amVK_PipelineLayout *PL;
    VkPipeline vk_Pipeline = nullptr;

  public:
    VkGraphicsPipelineCreateInfo CI = {
        .sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .pNext               = nullptr,
        .flags               = 0,
        .stageCount          = 0,       // amVK_PSCI::Shaders.neXt,     Set before creation
        .pStages             = nullptr, // amVK_PSCI::Shaders.data,
        .pVertexInputState   = &amVK_PSCI::VertexInput,
        .pInputAssemblyState = &amVK_PSCI::InputAssembly,
        .pTessellationState  = nullptr,
        .pViewportState      = &amVK_PSCI::Viewport,
        .pRasterizationState = &amVK_PSCI::Rasterization,
        .pMultisampleState   = &amVK_PSCI::Multisample,
        .pDepthStencilState  = nullptr,
        .pColorBlendState    = &amVK_PSCI::ColorBlend,
        .pDynamicState       = &amVK_PSCI::Dynamic,
        .layout              = nullptr, // this->PL.vk_PipelineLayout,
        .renderPass          = nullptr, // this->RP->vk_RenderPass,
        .subpass             = 0,
        .basePipelineHandle  = VK_NULL_HANDLE,
        .basePipelineIndex   = INT32_MIN
    };

    void CreateGraphicsPipeline(void);

  public:
    void  CMDBindPipeline(VkCommandBuffer CMDBUF) {
        vkCmdBindPipeline(CMDBUF, VK_PIPELINE_BIND_POINT_GRAPHICS, vk_Pipeline);
    }
};