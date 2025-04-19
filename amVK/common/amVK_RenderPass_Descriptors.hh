#pragma once
#include "vulkan/vulkan.h"

namespace amVK_RP_AttachmentDescription
{
        // Change .format before using
    inline VkAttachmentDescription ColorPresentation = {
        .format = VK_FORMAT_UNDEFINED ,                     // you should Use the color format selected by the swapchain
        .samples = VK_SAMPLE_COUNT_1_BIT,                   // We don't use multi sampling in this example
        .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,              // Clear this attachment at the start of the render pass
        .storeOp = VK_ATTACHMENT_STORE_OP_STORE,            // Keep its contents after the render pass is finished (for displaying it)
        .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,   // Similar to loadOp, but for stenciling (we don't use stencil here)
        .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE, // Similar to storeOp, but for stenciling (we don't use stencil here)
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,         // Layout at render pass start. Initial doesn't matter, so we use undefined
        .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,     // Layout to which the attachment is transitioned when the render pass is finished
                                                            // As we want to present the color attachment, we transition to PRESENT_KHR
    };
};

namespace amVK_RP_AttachmentReference
{
    inline VkAttachmentReference ColorPresentation = {
        .attachment = 0,
        .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
    };
};



#define amVK_RPADes amVK_RP_AttachmentDescription
#define amVK_RPARef amVK_RP_AttachmentReference
#define amVK_RPSDes amVK_RP_SubpassDescription
#define amVK_RPSDep amVK_RP_SubpassDependency



namespace amVK_RP_SubpassDescription
{
    inline VkSubpassDescription ColorPresentation = {
        .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,

        .inputAttachmentCount = 0,                            // Input attachments can be used to sample from contents of a previous subpass
        .pInputAttachments = nullptr,                         // (Input attachments not used by this example)
        .colorAttachmentCount = 1,                            // Subpass uses one color attachment
        .pColorAttachments = &amVK_RPARef::ColorPresentation, // Reference to the color attachment in slot 0

        .pResolveAttachments = nullptr,                       // Resolve attachments are resolved at the end of a sub pass and can be used for e.g. multi sampling
        .pDepthStencilAttachment = nullptr,                   // (Depth attachments not used by this sample)
        .preserveAttachmentCount = 0,                         // Preserved attachments can be used to loop (and preserve) attachments through subpasses
        .pPreserveAttachments = nullptr                       // (Preserve attachments not used by this example)
    };
};

namespace amVK_RP_SubpassDependency
{
    inline VkSubpassDependency ColorPresentation = {
        // Setup dependency and add implicit layout transition from final to initial layout for the color attachment.
        // (The actual usage layout is preserved through the layout specified in the attachment reference).
        .srcSubpass = VK_SUBPASS_EXTERNAL,
        .dstSubpass = 0,
        .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .srcAccessMask = VK_ACCESS_NONE,
        .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_COLOR_ATTACHMENT_READ_BIT,
    };
};