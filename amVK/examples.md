## Example 1
```cpp
#include "amGHOST_System.hh"

#include "amVK_InstancePropsEXPORT.hh"
#include "amVK_Instance.hh"
#include "amVK_Device.hh"
#include "amVK_DeviceQueues.hh"

#include "amGHOST_VkSurfaceKHR.hh"
#include "amVK_Surface.hh"

#include "amVK_SurfacePresenter.hh"
#include "amGHOST_SwapChainResizer.hh"

#include "amVK_SwapChain.hh"
#include "amVK_ColorSpace.hh"
#include "amVK_RenderPass.hh"
#include "amVK_RenderPass_Descriptors.hh"
#include "amVK_CommandPoolMAN.hh"

#include "mesh/amVK_Vertex.hh"
#include "mesh/amVK_VertexBuffer.hh"

#include "amVK_PipelineGRAPHICS.hh"

#include "amGHOST_Event.hh"
#include "amTHREAD.hh"

int main(int argumentCount, char* argumentVector[]) {
    REY::cout << "\n";

    // ------------------------- amGHOST ----------------------------
        amGHOST_System::create_system();

        amGHOST_Window *W = amGHOST_System::heart->new_window_interface();
        W->create(L"Whatever", 0, 0, 500, 600);
    // ------------------------- amGHOST ----------------------------

    REY_LOG("");
    REY_LOG("");
    // --------------------------- amVK -----------------------------
            REY_LOG("");
        amVK_Instance::EnumerateInstanceExtensions();
        amVK_Instance::EnumerateInstanceLayerProperties();
        amVK_Instance::addTo_1D_Instance_Layers_Enabled("VK_LAYER_KHRONOS_validation");
        amVK_Instance::addTo_1D_Instance_EXTs_Enabled("VK_KHR_surface");
        amVK_Instance::addTo_1D_Instance_EXTs_Enabled(amGHOST_System::get_vulkan_os_surface_ext_name());
        amVK_Instance::CreateInstance();

            REY_LOG("");
        VkSurfaceKHR  VK_S = amGHOST_VkSurfaceKHR::create_surface(W, amVK_Instance::vk_Instance);

            REY_LOG("");
        amVK_Instance::EnumeratePhysicalDevices();
        amVK_GPUProps  *GPUProps = amVK_InstanceProps::GetARandom_GPU();
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
        amVK_SurfacePresenter  *PR = new amVK_SurfacePresenter();
                                PR->bind_Surface(S);
                                PR->bind_Device(D);
                                // PR->create_SwapChain_interface();       // This amVK_SwapChain is Bound to this amVK_Surface
            
            REY_LOG("")
        amVK_SwapChain *SC =    new amVK_SwapChain(S, D);
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

        amVK_SwapChainIMGs *SC_IMGs = new amVK_SwapChainIMGs(SC);
            SC_IMGs->   GetSwapChainImagesKHR();
            SC_IMGs->CreateSwapChainImageViews();

        amVK_RenderPass *RP = new amVK_RenderPass(D);
            amVK_RPADes::ColorPresentation.format = SC->CI.imageFormat;

            RP->AttachmentInfos.push_back(amVK_RPADes::ColorPresentation);
            RP->SubpassInfos   .push_back(amVK_RPSDes::ColorPresentation);
            RP->Dependencies   .push_back(amVK_RPSDep::ColorPresentation);

            RP->sync_Attachments_Subpasses_Dependencies();
            RP->CreateRenderPass();

        amVK_RenderPassFBs *RP_FBs = new amVK_RenderPassFBs(SC_IMGs, RP);
            RP_FBs->CreateFrameBuffers();

        amGHOST_SwapChainResizer*   SC_Resizer = new amGHOST_SwapChainResizer(RP_FBs, W);

        amVK_CommandPoolMAN  *CPMAN = new amVK_CommandPoolMAN(D);
                              CPMAN->init_CMDPool_Graphics();
                              CPMAN->CreateCommandPool_Graphics(amVK_Sync::CommandPoolCreateFlags::RecordBuffer_MoreThanOnce);
                              CPMAN->AllocateCommandBuffers1_Graphics(1);

        amVK_CommandBufferPrimary *CB = new amVK_CommandBufferPrimary(CPMAN->BUFFs1.Graphics[0]);

        // ------------------------- Pipeline & VkTriangle ----------------------------
            amVK_Vertex vertices[3] = {
                { {  0.00f,  0.25f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },   // v0 (red)
                { { -0.25f, -0.25f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },   // v1 (green)
                { {  0.25f, -0.25f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },   // v2 (blue)
            };
            amVK_VertexBuffer VB(D, REY_Array<amVK_Vertex>(vertices, 3, 3));
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
        
        // ------------------------- Render Loop ----------------------------
            amTHREAD phoenix;
            phoenix.run([&]() {
                REY_LOG("Thread started.");

                while(true) {
                    // ------------------------- CommandBufferRecording ----------------------------
                            CB->BeginCommandBuffer(amVK_Sync::CommandBufferUsageFlags::Submit_Once);
                        while (SC_Resizer->isResizing) {
                            REY_NoobTimer::wait(1); // wait 100ms
                        }
                    SC_Resizer->canResizeNow = false;
                        RP_FBs->RPBI_AcquireNextFrameBuffer();
                        RP_FBs->CMDBeginRenderPass(CB->vk_CommandBuffer);
                        RP_FBs->CMDSetViewport_n_Scissor(CB->vk_CommandBuffer);
                        PLG->CMDBindPipeline(CB->vk_CommandBuffer);
                            VB.CMDBindVertexBuffers(CB->vk_CommandBuffer);
                            VB.CMDDraw(CB->vk_CommandBuffer);
                        RP_FBs->CMDEndRenderPass(CB->vk_CommandBuffer);
                            CB->EndCommandBuffer();
                    // ------------------------- CommandBufferRecording ----------------------------

                    PR->set_CommandBuffer(CB->vk_CommandBuffer);
                    PR->submit_CMDBUF(D->Queues.GraphicsQ(0), SC_IMGs->AcquireNextImage_SemaPhore);
                    PR->Present(D->Queues.GraphicsQ(0), SC->vk_SwapChainKHR, SC_IMGs->NextImageIndex_Acquired);

                    SC_Resizer->canResizeNow = true;

                    //REY_LOG("HI From another thread");

                    vkQueueWaitIdle(D->Queues.GraphicsQ(0));
                    REY_NoobTimer::wait(10); // wait 10ms
                }

                REY_LOG("Thread finished.");
            });

            while(true) {
                W->dispatch_events_with_OSModalLoops(); // dispatch events
                REY_NoobTimer::wait(1);               // wait 100ms
            }
        // ------------------------- Render Loop ----------------------------
    // --------------------------- amVK -----------------------------
    REY_LOG("");
    REY_LOG("");


    // ------------------------- CleanUp & ExportJSON ----------------------------
        REY::cin.get();     // wait for terminal input
            amVK_InstancePropsEXPORT::Export_nilohmannJSON_EXT();
                PR->destroy_everything_serially();
                W->m_amGHOST_VkSurface->destroy();
                amVK_Instance::DestroyInstance();
            W->destroy();
    // ------------------------- CleanUp & ExportJSON ----------------------------

    REY::cout << "\n";
}
```