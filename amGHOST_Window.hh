#pragma once
#include "REY_Types.hh"
// Must   not include         "amGHOST_System.hh" -> otherwise ♾️-loop of includes😶‍🌫️
// But we can include that in `amGHOST_Window.cpp`

#include "amGHOST_EventKonsument.hh"

class amGHOST_VkSurfaceKHR;

/** Curently only supports only 1 EventConsumer/EventKonsument function 💁‍♀️ */
class amGHOST_Window {
  public:
    uint32_t                m_posX              = 0;
    uint32_t                m_posY              = 0;
    uint32_t                m_sizeX             = 0;
    uint32_t                m_sizeY             = 0;
    uint32_t                m_oldSizeX          = 0;
    uint32_t                m_oldSizeY          = 0;
    uint32_t                m_clientSizeX       = 0;                                        // Without the TitleBar / Borders on windows
    uint32_t                m_clientSizeY       = 0;                                        // Without the TitleBar / Borders on windows
    const wchar_t*          m_title             = L"amGHOST_WINDOW:- TITLE WASNT SET";
    amGHOST_VkSurfaceKHR*   m_amGHOST_VkSurface = nullptr;                                  // amGHOST_Window::destroy() destroys ===> m_VkSurface
    bool                    m_callDefaultEK     = true;
    amGHOST_EK*             m_eventKonsument    = nullptr;
    inline  void      replace_eventKonsument(amGHOST_EK* ek, bool callDefault) {m_eventKonsument = ek; m_callDefaultEK = callDefault;}
    inline  void hand_over_to_eventKonsument(amGHOST_Event  lightweight_event) {m_eventKonsument->processEvent(lightweight_event);}
    virtual void call_default_eventKonsument(amGHOST_Event  lightweight_event) = 0;
    inline  void              _konsume_event(amGHOST_Event  lightweight_event)  {            // Internally called by amGHOST
        if (m_callDefaultEK) { call_default_eventKonsument (lightweight_event); }
        if (m_eventKonsument){ hand_over_to_eventKonsument (lightweight_event); }
    }

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
    virtual void dispatch_events_with_OSModalLoops(void) = 0;   // Must call this on the mainThread

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