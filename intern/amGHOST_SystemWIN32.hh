#pragma once
#include "amGHOST_System.hh"
#include "amGHOST_logWIN32.hh"

// Including amGHOST_SystemWIN32.hh ==> you include WINDOWS Specific Stuffs too 😄
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>  // Need: <sdkddkver.h>, <winresrc.h>, <WinDef.h> [HWND m_hwnd; HDC m_hdc; HGLRC m_hglrc]
#include <wchar.h>



class amGHOST_SystemWIN32 : public amGHOST_System {
  public:
    amGHOST_SystemWIN32() {REY_LOG("amGHOST_SystemWIN32::CONSTRUCTOR");    _reg_wc(); }
   ~amGHOST_SystemWIN32() {REY_LOG("amGHOST_SystemWIN32::DESTRUCTOR");   _unreg_wc(); }
    
    /** PureVirtual Funcs from amGHOST_System */
    amGHOST_Window* new_window(void);


  public:                                                   /** Windows Specific Stuffs here */
    WNDCLASSEXW _wc;                                        /** Every Window in win32 must have a WNDCLASS */
    void    _reg_wc();
    void  _unreg_wc();
    HMODULE _hInstance = ::GetModuleHandleW(nullptr);       /** \param nullptr returns initial main EXE file's Handle */
    const wchar_t* _wndClassName = L"amGHOST_WndClass1";    /** which we link by passing in s_wndClassName to \fn CreateWindowA */

  public:
    static LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    /** 😉
     * called by process_events() -> ::DispatchMessageA()
     * 
     * win32 "Window Procedure Function" [WndProc] - Deals with OS Messages and Events, hwnd is the Handle to Window
     * 
     * Windows asks for this function to be a GLOBAL STATIC function. But why would this work while being defined inside a Class?
     * WHY-THIS-WORKS:-
     *   C++ treats MEMBER_FUNCs and free functions [i.e. PUBLIC_STATIC_FUNCs] differently 
     *              MEMBER_FUNCs need to have access to a "this" pointer, and typically that's passed in as a hidden first parameter to MEMBER_FUNCs
     *   You can, however, declare "WndProc" as a PUBLIC_STATIC_FUNC, which eliminates the this pointer. [https://stackoverflow.com/a/17221900]
     * 
     * EASTER:- Let's See if anyone can use the Power of this being Public, 
     *          [I mean you could just call amGHOST_SystemWIN32::WndProc() & pass in aruments to it, MANUALLY CREATING "EVENTS"]
     *           That's It POWERRRRRR
     */
};