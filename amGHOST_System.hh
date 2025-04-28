#pragma once
#include "amGHOST_Window.hh"
#include "REY_Logger.hh"
#include "REY_Array.hh"

/**
 * SINGLETON Class
 * 
 *        I:  CREATE & DISPOSE
 *       II:      EK & EVENT
 *      III: PROCESS & DISPATCH [event]
 *       IV: Some internally used funcs
 *        V: GENERIC - STUFFS   [window]        [ \todo Pop-Ups, Time, Directories ]
 * 
 */
class amGHOST_System {
  public:
    #define  amG_HEART amGHOST_System::heart
    static inline      amGHOST_System* heart = nullptr;         /** C++17 */
    static         void create_system(void);                    /** Created System ==> Stored inside    .heart   */
    static amGHOST_System* get_system(void);
    /* */         void dispose_system(void);                    /** I want people to    heart->dispose_system() */
    
  protected:                                                    /** SINGLETON */
    amGHOST_System(const amGHOST_System&) = delete;             /** Copy-Constructor    ==> DELETED */
    amGHOST_System& operator=(const amGHOST_System&) = delete;  /** Assignment Operator ==> DELETED */

    amGHOST_System() {};  
    virtual ~amGHOST_System() = default;                        /** Fixes:  -Wnon-virtual-dtor   [using G++/GCC] */
                                                                /** making it virtual means, even if you  `delete amGHOST_System *system`  it will call e.g. `~amGHOST_SystemWIN32()` */


  public:
    static inline REY_ArrayDYN<amGHOST_Window*> REY_1D_Windows = REY_ArrayDYN<amGHOST_Window*>(1);
        // There'll be static OS-Specific functions like ---> static amGHOST_WindowWIN32* get_amGHOST_WindowWIN32(HWND hwnd);

  public:
    virtual amGHOST_Window* new_window_interface(void) = 0;     /** TO-CREATE:- amGHOST_Window::create() */
    virtual void dispatch_events_with_OSModalLoops(void) = 0;   /** win32: won't return before MouseButton Released when Resizing Window */
    virtual void dispatch_events_without_OSModalLoops(void) = 0;/** win32: NOT IMPLEMENTED 😰 */

  public:
    /**
     * Also See:- `amGHOST_VkSurfaceKHR::create_surface()`
     * Can be called: `anytime, [NoDependency]`
     */
    static const char* get_vulkan_os_surface_ext_name(void);
};