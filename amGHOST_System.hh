#pragma once
#include "amGHOST_Window.hh"

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
    virtual amGHOST_Window* new_window_interface(void) = 0;               /** However, To Initialize/Create \see amGHOST_Window.hh */
};