#pragma once
#include "amVK_Instance.hh"
#include "amVK_Device.hh"

class amVK_RenderPass  {
  public:
    VkRenderPassCreateInfo CI = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0,
        .pAttachments = nullptr,
        .pSubpasses = nullptr,
        .pDependencies = nullptr
    };

    REY_ArrayDYN<VkAttachmentDescription> attachments;
    REY_ArrayDYN<VkSubpassDescription> subpasses;
    REY_ArrayDYN<VkSubpassDependency> dependencies;
    void set_attachments(void) {
        CI.attachmentCount = attachments.neXt;
        CI.pAttachments = attachments.data;
    }
    void set_subpasses(void) {
        CI.subpassCount = subpasses.neXt;
        CI.pSubpasses = subpasses.data;
    }
    void set_dependencies(void) {
        CI.dependencyCount = dependencies.neXt;
        CI.pDependencies = dependencies.data;
    }
    void set_attachments_subpasses_dependencies(void) {
         set_attachments();
         set_subpasses();
         set_dependencies();
    }

  public:
    amVK_RenderPass(amVK_Device *paramD) {
        D = paramD;
    }

  public:
    amVK_Device *D = nullptr;
    VkRenderPass RP = nullptr;

  public:
    void createRenderPass(void) {
        VkResult return_code = vkCreateRenderPass(this->D->m_device, &CI, nullptr, &this->RP);
        amVK_return_code_log( "vkCreateRenderPass()" );     // above variable "return_code" can't be named smth else
    }
};