#include "amGHOST_System.hh"
#include "amGHOST_VkSurfaceKHR.hh"
#include "amVK_Instance.hh"
#include "amVK_Device.hh"
#include "amVK_SwapChain.hh"
#include "amVK_Image.hh"
#include "amVK_RenderPass.hh"
#include "REY_Logger.hh"

int main(int argumentCount, char* argumentVector[]) {
    REY::cout << "\n";

    amGHOST_System::create_system();    // initializes amG_HEART

    amGHOST_Window* W = amG_HEART->new_window_interface();
    W->create(L"Whatever", 0, 0, 500, 600);


    // Let's get an image rendering
    {
            REY_LOG("");
        amVK_InstanceProps::EnumerateInstanceExtensions();
        amVK_Instance::Add_InstanceEXT_ToEnable(VK_KHR_SURFACE_EXTENSION_NAME);
        amVK_Instance::Add_InstanceEXT_ToEnable(amGHOST_System::get_vulkan_os_surface_ext_name());
        amVK_Instance::CreateInstance();    // initializes amVK_HEART

            REY_LOG("");
        VkSurfaceKHR  VK_S = amGHOST_VkSurfaceKHR::create_surface(W, amVK_Instance::s_vk);

            REY_LOG("");
        amVK_InstanceProps::EnumeratePhysicalDevices();
        amVK_InstanceProps::GetPhysicalDeviceQueueFamilyProperties();
        amVK_InstanceProps::EnumerateDeviceExtensionProperties();

        amVK_Device* D = new amVK_Device(amVK_InstanceProps::GetARandom_PhysicalDevice());
        D->Select_QFAM_GRAPHICS();
        D->Add_GPU_EXT_ToEnable("VK_KHR_swapchain");
        D->CreateDevice();
        
            REY_LOG("")
        amVK_InstanceProps::push_back_VkSurfaceKHR(VK_S);
        amVK_SwapChain *SC = new amVK_SwapChain(VK_S, D);
            SC->CI.imageFormat = VK_FORMAT_B8G8R8A8_UNORM;
            SC->CI.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
            SC->CI.minImageCount    = amVK_InstanceProps::amVK_1D_SurfaceInfos[0].amVK_1D_GPUs_SurfCAP[0].minImageCount;
            SC->CI.imageExtent      = amVK_InstanceProps::amVK_1D_SurfaceInfos[0].amVK_1D_GPUs_SurfCAP[0].currentExtent;
            SC->CI.imageArrayLayers = amVK_InstanceProps::amVK_1D_SurfaceInfos[0].amVK_1D_GPUs_SurfCAP[0].maxImageArrayLayers;
            SC->CI.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            SC->CI.imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

            SC->CI.compositeAlpha   = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
            SC->CI.preTransform     = amVK_InstanceProps::amVK_1D_SurfaceInfos[0].amVK_1D_GPUs_SurfCAP[0].currentTransform;
            SC->CI.clipped          = VK_TRUE;
            SC->CI.presentMode      = VK_PRESENT_MODE_FIFO_KHR;
            SC->CI.oldSwapchain     = nullptr;
            SC->createSwapChain();
            SC->GetSwapchainImagesKHR();
            SC->CreateSwapChainImageViews();
        amVK_InstanceProps::amVK_1D_SurfaceInfos[0].SC = SC;

        amVK_RenderPass *RP = new amVK_RenderPass(D);
            RP->attachments.push_back({
                .format = SC->CI.imageFormat,                                   // Use the color format selected by the swapchain
                .samples = VK_SAMPLE_COUNT_1_BIT,                               // We don't use multi sampling in this example
                .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,                          // Clear this attachment at the start of the render pass
                .storeOp = VK_ATTACHMENT_STORE_OP_STORE,                        // Keep its contents after the render pass is finished (for displaying it)
                .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,               // Similar to loadOp, but for stenciling (we don't use stencil here)
                .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,             // Similar to storeOp, but for stenciling (we don't use stencil here)
                .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,                     // Layout at render pass start. Initial doesn't matter, so we use undefined
                .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,                 // Layout to which the attachment is transitioned when the render pass is finished
                                                                                // As we want to present the color attachment, we transition to PRESENT_KHR
            });

            VkAttachmentReference colorReference = {
                .attachment = 0,
                .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
            };
            RP->subpasses.push_back({
                .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,

                .inputAttachmentCount = 0,                            // Input attachments can be used to sample from contents of a previous subpass
                .pInputAttachments = nullptr,                         // (Input attachments not used by this example)
                .colorAttachmentCount = 1,                            // Subpass uses one color attachment
                .pColorAttachments = &colorReference,                 // Reference to the color attachment in slot 0

                .pResolveAttachments = nullptr,                       // Resolve attachments are resolved at the end of a sub pass and can be used for e.g. multi sampling
                .pDepthStencilAttachment = nullptr,                   // (Depth attachments not used by this sample)
                .preserveAttachmentCount = 0,                         // Preserved attachments can be used to loop (and preserve) attachments through subpasses
                .pPreserveAttachments = nullptr                       // (Preserve attachments not used by this example)
            });

            RP->dependencies.push_back({
                // Setup dependency and add implicit layout transition from final to initial layout for the color attachment.
                // (The actual usage layout is preserved through the layout specified in the attachment reference).
                .srcSubpass = VK_SUBPASS_EXTERNAL,
                .dstSubpass = 0,
                .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                .srcAccessMask = VK_ACCESS_NONE,
                .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_COLOR_ATTACHMENT_READ_BIT,
            });

            RP->set_attachments_subpasses_dependencies();
            RP->createRenderPass();
    }

    REY::cout << "\n" << "Press Enter to export data.json & exit 😊 ";
    REY::cin.get();
    // char *cs50_string = get_string("Hello from cs50! Press anything to end! ");

    W->destroy();
    amVK_InstanceProps::Export_nilohmannJSON();
    
    REY::cout << "\n";
    return 0;
}
