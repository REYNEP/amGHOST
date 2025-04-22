#include "amVK_PipelineLayout.hh"
#include "amVK/utils/amVK_log.hh"
void    amVK_PipelineLayout::CreatePipelineLayout(void) {
    VkResult return_code = vkCreatePipelineLayout(D->vk_Device, &CI, nullptr, &vk_PipelineLayout);
    amVK_return_code_log( "vkCreatePipelineLayout()" );
}

#include "amVK_PipelineGRAPHICS.hh"
void  amVK_PipelineGRAPHICS::CreateGraphicsPipeline(void) {
    if (PL->vk_PipelineLayout == nullptr) {
        PL->CreatePipelineLayout();
    }

    amVK_PSCI::Shaders.push_back({
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .stage = VK_SHADER_STAGE_VERTEX_BIT,
            .module = LoadSPIRVShaderModule(D->vk_Device, "./amGHOST/amVK/mesh/shader.vert.spv"),
            .pName = "main",
            .pSpecializationInfo = nullptr,
    });
    amVK_PSCI::Shaders.push_back({
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
            .module = LoadSPIRVShaderModule(D->vk_Device, "./amGHOST/amVK/mesh/shader.frag.spv"),
            .pName = "main",
            .pSpecializationInfo = nullptr,
    });

        CI.stageCount = amVK_PSCI::Shaders.neXt;
        CI.pStages    = amVK_PSCI::Shaders.data;
        CI.layout     = this->PL->vk_PipelineLayout;
        CI.renderPass = this->RP_FBs->RP->vk_RenderPass;
        amVK_PSCI::Viewport.pViewports = &this->RP_FBs->Viewport;
        amVK_PSCI::Viewport.pScissors  = &this->RP_FBs->Scissor;

    VkResult return_code = vkCreateGraphicsPipelines(
        D->vk_Device, nullptr,
        1, &CI, 
        nullptr, &vk_Pipeline
    );
    amVK_return_code_log( "vkCreateGraphicsPipelines()" );
}