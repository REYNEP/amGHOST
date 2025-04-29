#include "amGHOST_System.hh"

#include "amVK_InstancePropsEXPORT.hh"
#include "amVK_Instance.hh"
#include "amVK_Device.hh"
#include "amVK_DeviceQueues.hh"

#include "amGHOST_VkSurfaceKHR.hh"
#include "amVK_Surface.hh"

#include "amVK_SurfacePresenter.hh"

#include "amVK_SwapChain.hh"
#include "amVK_ColorSpace.hh"
#include "amVK_RenderPass.hh"
#include "amVK_RenderPass_Descriptors.hh"
#include "amVK_CommandPoolMAN.hh"

#include "mesh/amVK_Vertex.hh"
#include "mesh/amVK_VertexBuffer.hh"

#include "amVK_PipelineGRAPHICS.hh"

int main(int argumentCount, char* argumentVector[]) {
    REY::cout << "\n";

    amGHOST_System::create_system();

    amGHOST_Window *W = amGHOST_System::heart->new_window_interface();
    W->create(L"Whatever", 0, 0, 500, 600);



    REY_LOG("");
    REY_LOG("");
    amVK_SurfacePresenter  *PR = new amVK_SurfacePresenter();
    // TwT
    {
            REY_LOG("");
        amVK_InstanceProps::EnumerateInstanceExtensions();
        amVK_InstanceProps::EnumerateInstanceLayerProperties();
        amVK_Instance::addTo_1D_Instance_Layers_Enabled("VK_LAYER_KHRONOS_validation");
        amVK_Instance::addTo_1D_Instance_EXTs_Enabled("VK_KHR_surface");
        amVK_Instance::addTo_1D_Instance_EXTs_Enabled(amGHOST_System::get_vulkan_os_surface_ext_name());
        amVK_Instance::CreateInstance();    // initializes amVK_HEART


            REY_LOG("");
        VkSurfaceKHR  VK_S = amGHOST_VkSurfaceKHR::create_surface(W, amVK_Instance::vk_Instance);


            REY_LOG("");
        amVK_InstancePropsEXPORT::EnumeratePhysicalDevices();
        amVK_GPUProps  *GPUProps = amVK_InstancePropsEXPORT::GetARandom_GPU();
                        GPUProps->GetPhysicalDeviceQueueFamilyProperties();
                        GPUProps->EnumerateDeviceExtensionProperties();
                        GPUProps->REY_CategorizeQueueFamilies();

        amVK_Device* D = new amVK_Device(GPUProps);
            D->addTo_1D_GPU_EXTs_Enabled("VK_KHR_swapchain");
            D->CreateDevice(1);
            D->GetDeviceQueues();

        
            REY_LOG("")
        amVK_Surface   *S  = new amVK_Surface(VK_S);
            S->GetPhysicalDeviceSurfaceInfo();
            S->GetPhysicalDeviceSurfaceCapabilitiesKHR();
        // amVK_SurfacePresenter   *PR = new amVK_SurfacePresenter();
                                    PR->bind_Surface(S);
                                    PR->bind_Device(D);
                                    PR->create_SwapChain_interface();       // This amVK_SwapChain is Bound to this amVK_Surface
            
            REY_LOG("")
        amVK_SwapChain *SC =    PR->SC;
            SC->konf_ImageSharingMode(VK_SHARING_MODE_EXCLUSIVE);
            SC->konf_Images(
                amVK_IF::RGBA_8bpc_UNORM,   // VK_FORMAT_R8G8B8A8_UNORM
                amVK_CS::sRGB,              // VK_COLOR_SPACE_SRGB_NONLINEAR_KHR
                amVK_IU::Color_Display      // VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
            );
            SC->konf_Compositing(
                amVK_PM::FIFO,              // VK_PRESENT_MODE_FIFO_KHR
                amVK_CC::YES,               // Clipping:- VK_TRUE
                amVK_TA::Opaque             // VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR
            );
            SC->sync_SurfCaps();            // refresh/fetch & set/sync ---> latest SurfCaps

            SC->CI.oldSwapchain     = nullptr;
            SC->CreateSwapChain();

        amVK_SwapChainIMGs *SC_IMGs = PR->create_SwapChainImages_interface();
            SC_IMGs->   GetSwapChainImagesKHR();
            SC_IMGs->CreateSwapChainImageViews();

        amVK_RenderPass *RP = PR->create_RenderPass_interface();
            amVK_RPADes::ColorPresentation.format = SC->CI.imageFormat;

            RP->AttachmentInfos.push_back(amVK_RPADes::ColorPresentation);
            RP->SubpassInfos   .push_back(amVK_RPSDes::ColorPresentation);
            RP->Dependencies   .push_back(amVK_RPSDep::ColorPresentation);

            RP->sync_Attachments_Subpasses_Dependencies();
            RP->CreateRenderPass();

        amVK_RenderPassFBs *RP_FBs = PR->create_FrameBuffers_interface();
            RP_FBs->CreateFrameBuffers();

        amVK_CommandPoolMAN  *CPMAN = PR->create_CommandPoolMAN_interface();
            amVK_CommandPool *CP = CPMAN->InitializeCommandPool(D->Queues.Used_QFamID.Graphics);
                CP->CreateCommandPool(amVK_Sync::CommandPoolCreateFlagBits::RecordBuffer_Once);
                CP->AllocateCommandBuffers();

        // ------------------------- Pipeline & VkTriangle ----------------------------
            amVK_Vertex vertices[3] = {
                { {  0.00f,  0.25f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },   // v0 (red)
                { { -0.25f, -0.25f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },   // v1 (green)
                { {  0.25f, -0.25f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },   // v2 (blue)
            };
            amVK_VertexBuffer VB(D, REY_Array<amVK_Vertex>(vertices, 3));
                VB.CreateBuffer();

            GPUProps->GetPhysicalDeviceFeatures();
            GPUProps->GetPhysicalDeviceMemoryProperties();
            GPUProps->REY_CategorizeMemoryHeaps();

                VB.GetBufferMemoryRequirements();
                VB.AllocateMemory();
                VB.MapMemory();
                VB.CopyIntoMemory();
                VB.UnMapMemory();
                VB.BindBufferMemory();

            amVK_PipelineGRAPHICS* PLG = new amVK_PipelineGRAPHICS(RP_FBs);
                PLG->CreateGraphicsPipeline();
        // ------------------------- Pipeline & VkTriangle ----------------------------
        
        // ------------------------- CommandBufferRecording ----------------------------
            VkCommandBuffer CB = CP->BeginCommandBuffer();
                RP_FBs->RPBI_AcquireNextFrameBuffer();
                RP_FBs->CMDBeginRenderPass(CB);
                RP_FBs->CMDSetViewport_n_Scissor(CB);
                PLG->CMDBindPipeline(CB);
                    VB.CMDBindVertexBuffers(CB);
                    VB.CMDDraw(CB);
                RP_FBs->CMDEndRenderPass(CB);
            CP->  EndCommandBuffer();

        // ------------------------- CommandBufferRecording ----------------------------
        
        // ------------------------- Render Loop ----------------------------
            while(true) {
                PR->set_CommandPool_Presentation(CP);
                PR->submit_CMDBUF(D->Queues.GraphicsQ(0));
                PR->Present(D->Queues.GraphicsQ(0));

                vkQueueWaitIdle(D->Queues.GraphicsQ(0));
                RP_FBs->RPBI_AcquireNextFrameBuffer();

                REY::cin.get();
            }
        // ------------------------- Render Loop ----------------------------
    }
    REY_LOG("");
    REY_LOG("");



    REY::cin.get();     // wait for terminal input
        amVK_InstancePropsEXPORT::Export_nilohmannJSON_EXT();
        PR->destroy_everything_serially();
        W->m_amGHOST_VkSurface->destroy();
        amVK_Instance::DestroyInstance();
    W->destroy();

    REY::cout << "\n";
}