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
     * 
        ```cpp
        // 4. Why not just 
            -> virtual VkSurfaceKHR amGHOST_Window::create_VkSurface(VkInstance I);
            // -> Explained @ Docs of amGHOST_Window::init_VkSurface_interface()
        ```
     */
    static inline VkSurfaceKHR create_surface(amGHOST_Window *W, VkInstance I) {
                            W->init_VkSurface_interface();  // Just creating an Object, nothin else 😊
        VkSurfaceKHR VK_S = W->m_amGHOST_VkSurface->create(I);
              return VK_S;
    }
};