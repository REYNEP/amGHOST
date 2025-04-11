## Read the [`./guide/4.guide.md`](https://github.com/REYNEP/amGHOST/blob/main/amVK/guide/4.guide.md)

## amVK vs amGHOST
- This is a little bit different than `amGHOST`. 
    - `amGHOST`:- Window & Such objects are instanced from `amG_HEART->new_window_interface()` and such and such. 
    - `amVK`:- but in, `amVK`, you rather gotta do `amVK_Device *D = new amVK_Device();` 
        - -> i.e. you can just create the object yourself.
1. `naming convention`:- different
2. `amGHOST_System` === `amVK_Instance`
3. `amGHOST`:- object types are `pure virtual`
    - which means that you cannot _**'instantiate'**_ these `pure virtual` classes directly.... 
        - but rather take instance of `derived classes` that implements those `pure virtual functions`. 
        - this idea is also called `interface`
    - `amVK` doesn't have that problem, 
        - cz there's nothing to me made _**"platform independent"**_

## Example
```cpp
#include "amGHOST_System.hh"
#include "amGHOST_VkSurfaceKHR.hh"
#include "amVK.hh"
#include "amVK_Surface.hh"
#include "amVK_Device.hh"
#include "amVK_SwapChain.hh"
#include "amVK_Image.hh"
#include "amVK_RenderPass.hh"
#include "amVK_ColorSpace.hh"
#include "amVK_CommandBuffer.hh"
#include "REY_Logger.hh"

int main(int argumentCount, char* argumentVector[]) {
    REY::cout << "\n";

    amGHOST_System::create_system();    // initializes amG_HEART

    amGHOST_Window* W = amG_HEART->new_window_interface();
    W->create(L"Whatever", 0, 0, 500, 600);


    // Let's get an image rendering
    {
            REY_LOG("");
        amVK_Props::EnumerateInstanceExtensions();
        amVK_Instance::Add_InstanceEXT_ToEnable("VK_KHR_surface");
        amVK_Instance::Add_InstanceEXT_ToEnable(amGHOST_System::get_vulkan_os_surface_ext_name());
        amVK_Instance::CreateInstance();    // initializes amVK_HEART

            REY_LOG("");
        VkSurfaceKHR  VK_S = amGHOST_VkSurfaceKHR::create_surface(W, amVK_Instance::s_vk);

            REY_LOG("");
        amVK_Props::EnumeratePhysicalDevices();
        amVK_Props::GetPhysicalDeviceQueueFamilyProperties();
        amVK_Props::EnumerateDeviceExtensionProperties();

        amVK_Device* D = new amVK_Device(amVK_Props::GetARandom_GPU());
            D->select_QFAM_Graphics();
            D->Add_GPU_EXT_ToEnable("VK_KHR_swapchain");
            D->CreateDevice();
        
            REY_LOG("")
        amVK_Surface   *S  = new amVK_Surface(VK_S);
        amVK_Presenter *PR = S->PR;
                                PR->bind_Device(D);
                                PR->create_SwapChain();       // This amVK_SwapChain is Bound to this amVK_Surface
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
            SC->GetSwapChainImagesKHR();
            SC->CreateSwapChainImageViews();

        amVK_RenderPass *RP = PR->create_RenderPass(); 
            RP->AttachmentInfos.push_back({
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
            RP->SubpassInfos.push_back({
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

            RP->Dependencies.push_back({
                // Setup dependency and add implicit layout transition from final to initial layout for the color attachment.
                // (The actual usage layout is preserved through the layout specified in the attachment reference).
                .srcSubpass = VK_SUBPASS_EXTERNAL,
                .dstSubpass = 0,
                .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                .srcAccessMask = VK_ACCESS_NONE,
                .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_COLOR_ATTACHMENT_READ_BIT,
            });

            RP->sync_Attachments_Subpasses_Dependencies();
            RP->CreateRenderPass();
        
        PR->create_FrameBuffers();
        amVK_CommandPool *CP = PR->create_CommandPool();
            CP->CreateCommandPool();
    }

    REY::cout << "\n" << "Press Enter to export data.json & exit 😊 ";
    REY::cin.get();
    // char *cs50_string = get_string("Hello from cs50! Press anything to end! ");

    W->destroy();
    amVK_Props::Export_nilohmannJSON();
    
    REY::cout << "\n";
    return 0;
}

```

## Naming Conventions
1. Simple Wrappers around `vulkan` functions
    ```cpp
    bool called_GetPhysicalDeviceSurfaceFormatsKHR = false;
    bool called_GetPhysicalDeviceSurfaceCapabilitiesKHR = false;
    void        GetPhysicalDeviceSurfaceInfo(void);
    void        GetPhysicalDeviceSurfaceCapabilitiesKHR(void);

    amVK_SwapChain {
            // Notice the "Capital-C" @ 'Chain', i didn't do this at any other functions
        void CreateSwapChain(void) {
            VkResult return_code = vkCreateSwapchainKHR(this->D->m_device, &CI, nullptr, &this->SC);
            amVK_return_code_log( "vkCreateSwapchainKHR()" );     // above variable "return_code" can't be named smth else
        }
    }
    ```
2. amVK Object/Instances Creation
    ```cpp
    amVK_SwapChain* amVK_Presenter::create_SwapChain(void);
    ```
3. 


## Vulkan Structure
```cpp
VkInstance 
    VkPhysicalDevices
        VkDevice
            VkComandPool
                VkCommandBuffer
            VkSemaPhore
            VkFench

    VkSurfaceKHR
        VkPhysicalDevice
            Capabilities
        VkSwapchainKHR(VkDevice)
            VkImage
                VkImageView
        VkRenderPass(VkDevice)
            VkAttachments
            VkSubPasses
            VkFrameBuffers
    
    RenderLoop
        Record(VkCommandBuffer)
```

## Verbs to Remember
1. query_SurfCap 🕵️♂️
2. update_SurfCap 🔄
3. load_SurfCap 📥
4. acquire_SurfCap 🔗
5. get_SurfCap 📤
6. grab_SurfCap	👐
7. snag_SurfCap	🎣 (Quick pull)
8. pluck_SurfCap	✂️ (Precision)
9. selected_gpu_surfCap	🎯 (Targeted)	Emphasizes the GPU_Index selection.
10. current_surfCap	⏳ (Stateful)
11. yoink_SurfCap	🦄 (Playful)	VkSurfaceCapabilitiesKHR* cap = yoink_SurfCap();
12. procure_SurfCap	🕴️ (Formal)	procure_SurfCap() → Sounds like a business transaction!
13. obtain_SurfCap	🏆 (Success)
14. collect_SurfCap	📚 (Gathering)
15. retrieve_SurfCap	🎯 (Accuracy)
16. sync_SurfCap	🔄 (Sync State)
17. pull_SurfCap	🪢 (Tug-of-war)
18. refresh_SurfCap	💫 (Update)
19. reload_SurfCap	♻️ (Reload)
20. populate_SurfCap	🌱 (Fill Data)
21. enumerate_SurfCap	📇 (Listing)
22. summon_SurfCap	🧙♂️ (Magic)
23. harvest_SurfCap	🌾 (Farm)
24. fish_SurfCap	🎣 (Fishing)
25. dial in	🎛️ (Precision)
26. shape up	🌟 (Polishing)
27. rig	🛠️ (Hacky)
28. tailor	👗 (Custom-fit)
29. access_SurfCap 🔍
30. craft	🧙♂️ (Artisan)
31. surfCap 📋 (property-style)
32. surfCap_ptr 🎯 (or surfCapRef)