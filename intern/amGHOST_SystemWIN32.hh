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
    
  public:                                                   /** PureVirtual Funcs from amGHOST_System */
    amGHOST_Window* new_window_interface(void);
    void dispatch_events(void);

  public:                                                   /** Windows Specific Stuffs here */
    WNDCLASSEXW _wc;                                        /** Every Window in win32 must have a WNDCLASS */
    void    _reg_wc();
    void  _unreg_wc();
    const wchar_t* _wndClassName = L"amGHOST_WndClass1";    /** which we link by passing in s_wndClassName to \fn CreateWindowA */
    HMODULE _hInstance = ::GetModuleHandleW(nullptr);       /** \param nullptr returns initial main EXE file's Handle */
        // must not be static, otherwise GetModuleHandleW() doesn't work

  public:
    static LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);   // 😉
};