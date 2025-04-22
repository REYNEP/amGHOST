#include "amVK_PipelineLayout.hh"
#include "amVK/utils/amVK_log.hh"
void    amVK_PipelineLayout::CreatePipelineLayout(void) {
    VkResult return_code = vkCreatePipelineLayout(D->vk_Device, &CI, nullptr, &vk_PipelineLayout);
    amVK_return_code_log( "vkCreatePipelineLayout()" );
}

#include "amVK_PipelineGRAPHICS.hh"
void  amVK_PipelineGRAPHICS::CreateGraphicsPipeline(void) {
    if (PL.vk_PipelineLayout == nullptr) {
        PL.CreatePipelineLayout();
    }

    VkResult return_code = vkCreateGraphicsPipelines(
        D->vk_Device, nullptr,
        1, &CI, 
        nullptr, &vk_Pipeline
    );
    amVK_return_code_log( "vkCreateGraphicsPipelines()" );
}