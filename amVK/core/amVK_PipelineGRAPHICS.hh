#pragma once
#include "amVK_PipelineLayout.hh"
#include "amVK_RenderPass.hh"
#include "amVK/common/amVK_PipelineObjects.hh"
#include "amVK/mesh/amVK_Vertex.hh"
#include "amVK/mesh/amVK_GeoMetry.hh"

class amVK_PipelineGRAPHICS {
  public:
    amVK_PipelineGRAPHICS(amVK_RenderPass *RP) : RP(RP), D(RP->D), PL(D) {}
   ~amVK_PipelineGRAPHICS(void) {}

  public:
    amVK_Device *D;
    amVK_RenderPass *RP;
    amVK_PipelineLayout PL;
    VkPipeline vk_Pipeline = nullptr;

  public:
    VkGraphicsPipelineCreateInfo CI = {
        .sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .pNext               = nullptr,
        .flags               = 0,
        .stageCount          =  amVK_PSCI::Shaders.neXt,
        .pStages             =  amVK_PSCI::Shaders.data,
        .pVertexInputState   = &amVK_PSCI::VertexInput,
        .pInputAssemblyState = &amVK_PSCI::InputAssembly,
        .pTessellationState  = nullptr,
        .pViewportState      = &amVK_PSCI::Viewport,
        .pRasterizationState = &amVK_PSCI::Rasterization,
        .pMultisampleState   = &amVK_PSCI::Multisample,
        .pDepthStencilState  = &amVK_PSCI::DepthStencil,
        .pColorBlendState    = &amVK_PSCI::ColorBlend,
        .pDynamicState       = &amVK_PSCI::Dynamic,
        .layout              = this->PL.vk_PipelineLayout,
        .renderPass          = this->RP->vk_RenderPass,
        .subpass             = 0,
        .basePipelineHandle  = VK_NULL_HANDLE,
        .basePipelineIndex   = INT32_MIN
    };

    void CreateGraphicsPipeline(void);
};