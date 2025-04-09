// As of now, this file probably only gets included inside amGHOST_WindowWIN32.cpp

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include "amGHOST_VkSurfaceKHR.hh"

#include "amGHOST_SystemWIN32.hh"
#include "amGHOST_WindowWIN32.hh" 

#include "amVK/intern/amVK_log.hh"

class amGHOST_VkSurfaceKHR_WIN32 : public amGHOST_VkSurfaceKHR {
  public:
    using amGHOST_VkSurfaceKHR::m_S;        // VkSurfaceKHR
    using amGHOST_VkSurfaceKHR::m_I;        // VkInstance
    amGHOST_WindowWIN32 *m_W = nullptr;

  public:
        /**
         * This function / CONSTRUCTOR -> called inside `amGHOST_WindowWIN32::init_VkSurface_interface();
         */
    amGHOST_VkSurfaceKHR_WIN32(amGHOST_WindowWIN32 *pW) {
        this->m_W = pW;
    }

  public:
    VkSurfaceKHR create(VkInstance I) 
    {
            // m_W got set during CONSTRUCTOR call
        if (m_W->m_hwnd == nullptr) {
            REY_LOG_EX("[amGHOST_VkSurfaceKHR_WIN32::create]:- Window has't been created yet. How can we create the VkSurface?");
        }

        amGHOST_SystemWIN32 *heart_win32 = (amGHOST_SystemWIN32 *) amGHOST_System::heart;
        VkWin32SurfaceCreateInfoKHR CI = {
            .sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
            .pNext = NULL,
            .flags = 0,
            .hinstance = heart_win32->_hInstance,
            .hwnd = this->m_W->m_hwnd
        };

        VkSurfaceKHR S = nullptr;
        VkResult return_code = vkCreateWin32SurfaceKHR(I, &CI, nullptr, &S);
        amVK_return_code_log( "vkCreateWin32SurfaceKHR()" );  // above variable "return_code" can't be named smth else

        this->m_I = I;
        this->m_S = S;
        return this->m_S;
    }

    void destroy(void) {
        // TODO: Maybe trigger a event into the Parent window 💁‍♀️

        vkDestroySurfaceKHR(m_I, m_S, nullptr);
        m_I = nullptr;
        m_S = nullptr;
    }
};