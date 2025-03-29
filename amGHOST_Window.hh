#pragma once
#include "REY_Types.hh"
// Must   not include         "amGHOST_System.hh" -> otherwise ♾️-loop of includes😶‍🌫️
// But we can include that in `amGHOST_Window.cpp`

class amGHOST_VkSurfaceKHR;

class amGHOST_Window {
  public:
    uint32_t    m_posX = 0;
    uint32_t    m_posY = 0;
    uint32_t    m_sizeX = 0;
    uint32_t    m_sizeY = 0;
    const wchar_t* m_title = L"amGHOST_WINDOW:- TITLE WASNT SET";
    amGHOST_VkSurfaceKHR* m_amGHOST_VkSurface = nullptr;    // this->destroy() ==> destroys m_VkSurface

    amGHOST_Window() {};
   ~amGHOST_Window() {};

  public:
    /**
     * Creates a New Window obviously
     * \param title: should be ASCII characters only (as its char*)
     * \param posX: =_= Position in X-axis
     * \param posY: +_+ Position in Y-axis
     * \param sizeX: WIDTH
     * \param sizeY: HEIGHT
     * \param instantShow: Yes, WIN32/X11 does distinguish between creating the window in memory 
     *                     and actually showing the Window on Screen/Monitor. 
     *                     SO WE Give you the choice too.
     * 
     * \todo CAP according to DISPLAY/SCREEN/MONITOR/MULTI_MONITOR resolution
     */
    virtual void create(const wchar_t* title, int posX, int posY, int sizeX, int sizeY, bool instantShow = true) = 0;
    virtual void destroy(void) = 0;
    virtual void show_window(void) = 0;
    virtual void hide_window(void) = 0;

  public:
    /**
      ```cpp
      // 1. Only 2 Line of Code inside
            -> amGHOST_VkSurfaceKHR_OS *REY = new amGHOST_VkSurfaceKHR_OS(this);
            -> amGHOST_Window::m_VkSurface = REY;

      // 2. The Only task of this function is to take a "new" object for:-
            -> amGHOST_Window::m_VkSurface [variable]
            -> // but do nothing with it yet
      
      // 3. Implementation/Definition inside 
            -> amGHOST_WindowOS.cpp
      
      // 4. Why not just 
            -> virtual VkSurfaceKHR amGHOST_Window::create_VkSurface();
            // -> Then we would have to include <vulkan/vulkan.hh> inside this header
                    -> Thus <vulkan/vulkan.hh> would be everywhere 
                    -> So we just decided not to include <vulkan/vulkan.hh> in this header
      
      // 5. We dont include "amGHOST_VkSurfaceKHR.hh" in this file either, cz that has <vulkan/vulkan.hh>
            -> So do #include "amGHOST_VkSurfaceKHR.hh" in the file you are gonna make use of amGHOST_VkSurfaceKHR
      ```
     */
    virtual amGHOST_VkSurfaceKHR* init_VkSurface_interface(void) = 0;
};