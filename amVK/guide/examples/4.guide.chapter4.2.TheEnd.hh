// ------------------------ amGHOST_Window.hh ------------------------
class amGHOST_VkSurfaceKHR; 
    // forward declaration, we strictly don't #include "amGHOST_VkSurfaceKHR.hh"
    // The reason:- documented @ amGHOST_Window::init_VkSurface_interface(void);

class amGHOST_Window {
    ...
    amGHOST_VkSurfaceKHR* m_VkSurface = nullptr;    // this->destroy() ==> destroys m_VkSurface
    virtual amGHOST_VkSurfaceKHR* init_VkSurface_interface(void) = 0;
    ...
}
// ------------------------ amGHOST_Window.hh ------------------------

// --------------------- amGHOST_WindowWIN32.cpp ---------------------
amGHOST_VkSurfaceKHR* amGHOST_WindowWIN32::init_VkSurface_interface(void) {
    if (amGHOST_Window::m_VkSurface != nullptr) {
        REY_LOG_EX("[amGHOST_WindowWIN32::init_VkSurface_interface]:- A m_VkSurface Already Exists.");
    }
    else {
        amGHOST_VkSurfaceKHR_WIN32 *REY = new amGHOST_VkSurfaceKHR_WIN32(this);
        amGHOST_Window::m_VkSurface = REY;
    }
    
    return amGHOST_Window::m_VkSurface;
}

// and we also call
amGHOST_WindowWIN32::destroy() {
    ...
    amGHOST_Window::m_VkSurface.destroy() 
    ...
}
// --------------------- amGHOST_WindowWIN32.cpp --------------------- 
        













// --------------------- amGHOST_VkSurfaceKHR.hh --------------------- 
#pragma once
#include <vulkan/vulkan.h>
#include "amGHOST_Window.hh"

/**
 * `DOCUMENTATION BEGIN`
```ruby
Implementation inside
-> `amGHOST_VkSurfaceKHR_WIN32.cpp`
-> `amGHOST_VkSurfaceKHR_OSZZZ.cpp`

Do Define 
-> `VK_USE_PLATFORM_WIN32_KHR`
-> `VK_USE_PLATFORM_OSZZZ_KHR`
    before including the header for this class
```
 * `DOCUMENTATION END`
 */
class amGHOST_VkSurfaceKHR {
  public:
    VkSurfaceKHR m_S = nullptr;
    VkInstance m_I = nullptr;
    virtual VkSurfaceKHR create(VkInstance I) = 0;
    virtual void destroy(void) = 0;

    /**
     * This thing is like a GROUP node inside of Houdini, haha 😄
     */
    static inline VkSurfaceKHR create_surface(amGHOST_Window *W, VkInstance I) {
                            W->init_VkSurface_interface();  // Just creating an Object, nothin else 😊
        VkSurfaceKHR VK_S = W->   m_VkSurface-> create(I);
              return VK_S;
    }
};
// --------------------- amGHOST_VkSurfaceKHR.hh --------------------- 






// ------------------ amGHOST_VkSurfaceKHR_WIN32.hh ------------------ 
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include "amGHOST_VkSurfaceKHR.hh"

#include "amGHOST_SystemWIN32.hh"
#include "amGHOST_WindowWIN32.hh" 

#include "amVK/amVK_log.hh"

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
        vkDestroySurfaceKHR(m_I, m_S, nullptr);
        m_I = nullptr;
        m_S = nullptr;
    }
};
// ------------------ amGHOST_VkSurfaceKHR_WIN32.hh ------------------ 