#pragma once
#include "vulkan/vulkan.h"

namespace amVK_ImageFormat 
{
        // 8bpc = 8-bits per channel
    inline constexpr VkFormat RGBA_8bpc_UNORM    = VK_FORMAT_R8G8B8A8_UNORM;    // 37
    inline constexpr VkFormat RGBA_8bpc_SNORM    = VK_FORMAT_R8G8B8A8_SNORM;    // 38
    inline constexpr VkFormat RGBA_8bpc_USCALED  = VK_FORMAT_R8G8B8A8_USCALED;  // 39
    inline constexpr VkFormat RGBA_8bpc_SSCALED  = VK_FORMAT_R8G8B8A8_SSCALED;  // 40
    inline constexpr VkFormat RGBA_8bpc_UINT     = VK_FORMAT_R8G8B8A8_UINT;     // 41
    inline constexpr VkFormat RGBA_8bpc_SINT     = VK_FORMAT_R8G8B8A8_SINT;     // 42
    inline constexpr VkFormat RGBA_8bpc_SRGB     = VK_FORMAT_R8G8B8A8_SRGB;     // 43

        // Common Depth/Stencil Formats
    inline constexpr VkFormat D32_SFLOAT         = VK_FORMAT_D32_SFLOAT;
    inline constexpr VkFormat D24_UNORM_S8_UINT  = VK_FORMAT_D24_UNORM_S8_UINT;
}

namespace amVK_ColorSpace 
{
    inline constexpr VkColorSpaceKHR sRGB = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
}

#define amVK_IF                 amVK_ImageFormat
#define amVK_PF                 amVK_ImageFormat
#define amVK_PixelFormat        amVK_ImageFormat
#define amVK_CS                 amVK_ColorSpace






    
namespace amVK_ImageUsage 
{
    inline constexpr VkImageUsageFlagBits Color_Display         = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    inline constexpr VkImageUsageFlagBits Color_Presentation    = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    inline constexpr VkImageUsageFlagBits Color_Screen          = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
}

namespace amVK_PresentMode 
{
    inline constexpr VkPresentModeKHR IMMEDIATE = VK_PRESENT_MODE_IMMEDIATE_KHR;
    inline constexpr VkPresentModeKHR MAILBOX = VK_PRESENT_MODE_MAILBOX_KHR;
    inline constexpr VkPresentModeKHR FIFO = VK_PRESENT_MODE_FIFO_KHR;
    inline constexpr VkPresentModeKHR FIFO_Relaxed = VK_PRESENT_MODE_FIFO_RELAXED_KHR;
    inline constexpr VkPresentModeKHR Shared_Demand = VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR;
    inline constexpr VkPresentModeKHR Shared_Continuous = VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR;
    inline constexpr VkPresentModeKHR FIFO_LatestReady = VK_PRESENT_MODE_FIFO_LATEST_READY_EXT;
}

#define amVK_IU                 amVK_ImageUsage
#define amVK_ITF                amVK_ImageUsage
#define amVK_ImageTilingFlag    amVK_ImageUsage
#define amVK_PM                 amVK_PresentMode






    
namespace amVK_CompositeAlpha 
{
    inline constexpr VkCompositeAlphaFlagBitsKHR Opaque             = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    inline constexpr VkCompositeAlphaFlagBitsKHR Pre_Multiplied     = VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR;
    inline constexpr VkCompositeAlphaFlagBitsKHR Post_Multiplied    = VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR;
    inline constexpr VkCompositeAlphaFlagBitsKHR Inherit            = VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR;
}
    
namespace amVK_CompositeClipping_NS 
{
        // VkSwapchainCreateInfoKHR.clipped 
    inline constexpr VkBool32  YES = VK_TRUE;
    inline constexpr VkBool32 NOPE = VK_FALSE; 
}

#define amVK_CA                 amVK_CompositeAlpha
#define amVK_Transparency       amVK_CompositeAlpha
#define amVK_TransparencyAlpha  amVK_CompositeAlpha
#define amVK_GlassEffect        amVK_CompositeAlpha
#define amVK_GL                 amVK_CompositeAlpha
#define amVK_TA                 amVK_CompositeAlpha
#define amVK_CC                 amVK_CompositeClipping_NS
typedef VkBool32                amVK_CompositeClipping;