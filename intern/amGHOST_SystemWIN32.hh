#pragma once
#include "amGHOST_System.hh"
#include "amGHOST_logWIN32.hh"

// Including amGHOST_SystemWIN32.hh ==> you include WINDOWS Specific Stuffs too 😄
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>  // Need: <sdkddkver.h>, <winresrc.h>, <WinDef.h> [HWND m_hwnd; HDC m_hdc; HGLRC m_hglrc]
#include <wchar.h>
// Possible Mini Windows include:- https://github.com/nomdenom/devilution/blob/98a0692d14f338dc8f509c8424cab1ee6067a950/Stub/miniwin.h#L492

class amGHOST_WindowWIN32;

class amGHOST_SystemWIN32 : public amGHOST_System {
  public:
    amGHOST_SystemWIN32() {REY_LOG("amGHOST_SystemWIN32::CONSTRUCTOR");    _reg_wc(); }
   ~amGHOST_SystemWIN32() {REY_LOG("amGHOST_SystemWIN32::DESTRUCTOR");   _unreg_wc(); }

   using amGHOST_System::REY_1D_Windows;
   static inline bool log_ModalLoopEventsHandling = true;
    
  public:                                                   /**               PureVirtual Funcs from amGHOST_System             */
    virtual amGHOST_Window* new_window_interface(void);
    virtual void dispatch_events_with_OSModalLoops(void);   /**                 Must call this on the mainThread                */
    virtual void dispatch_events_without_OSModalLoops(void) {REY_LOG_EX("[WIP] For now, without_OSModalLoops isn't do-able 😰");}
        // April 28, 2025:- I found a way to do this on win32, we gotta manage WM_SYSCOMMAND ourselves.... instead of calling ::DefWindowProc() on it

  public:                                                   /**                   Windows Specific Stuffs here                  */
    WNDCLASSEXW _wc = {                                     /**            Every Window in win32 must have a WNDCLASS           */
        .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,            /** https://learn.microsoft.com/en-us/windows/win32/winmsg/window-class-styles */
        .lpfnWndProc = &amGHOST_SystemWIN32::WndProc,           /**   I wanted to be explicit about how WndProc() binds to a Window on win32   */
    };                                                      /**        All elements of _wc --> will be set inside _reg_wc       */
    void    _reg_wc();
    void  _unreg_wc();
    const wchar_t* _wndClassName = L"amGHOST_WndClass1";    /** which we link by passing in s_wndClassName to \fn CreateWindowA */
    HMODULE  _hInstance   = ::GetModuleHandleW(nullptr);    /**      \param nullptr returns initial main EXE file's Handle      */
    DWORD _mainThread     = ::GetCurrentThreadId();
        // must not be static, otherwise GetModuleHandleW() doesn't work

  public:
    static amGHOST_WindowWIN32* get_amGHOST_WindowWIN32(HWND hwnd);                     // amGHOST_System::REY_1D_Windows
    static LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);   // 😉
};