#pragma once
#include "amGHOST_Window.hh"
#include "amGHOST_SystemWIN32.hh"
#include "amGHOST_logWIN32.hh"

class amGHOST_WindowWIN32 : public amGHOST_Window {
  public:
    HWND m_hwnd = NULL;
    using amGHOST_Window::m_amGHOST_VkSurface;
        // We, still inside this header, as of this line, using a FORWARD-DECLARATION of `class amGHOST_VkSurfaceKHR`

  public:
    void create(const wchar_t* title, int posX, int posY, int sizeX, int sizeY, bool instantShow = true) {
        REY_LOG("amGHOST_WindowWIN32::create");
        this->m_posX = posX;
        this->m_posY = posY;
        this->m_sizeX = sizeX;
        this->m_sizeY = sizeY;

        amGHOST_SystemWIN32 *heart_win32 = (amGHOST_SystemWIN32 *) amGHOST_System::heart;
        HWND hwnd = ::CreateWindowExW(
            0L,
            heart_win32->_wndClassName,   /** Name of the WNDCLASS [see protected vars of amGHOST_SystemWIN32] */
            title,                        /** Title at the Top bar of the Window */
            WS_OVERLAPPEDWINDOW,          /** Style of the window, all styles: https://docs.microsoft.com/en-us/windows/win32/winmsg/window-styles */
            posX, posY,                   /** Horizontal, Vertical Position of window (top-left corner) */
            sizeX, sizeY,                 /** NULL makes the CMD as the parent of this Window, for GUI apps, getDesktopWindow would return the entire Screen as Window */
            (HWND)  nullptr,              /** parent window */
            (HMENU) nullptr,              /** The Handle to the Menu, remember that wndcls.lpszMenuName should have the menu Name TOO, or it wont work */
            heart_win32->_hInstance,      /** Handle to the Instance the window is gonna get be Linked with.... I still don't why both wndclass and hInstance need this */
            (LPVOID) nullptr              /** using this value as lParam of WndProc, CreatwWindowA Send WM_CREATE message to WndProc */
        );

        if (hwnd == nullptr) {
            amG_FAILED1("::CreateWindowExW()");
            this->destroy();
            return;
        }
        else {
            this->m_hwnd = hwnd;
            amG_PASSED1("::CreateWindowExW()");
            if (instantShow) this->show_window();
        }
    }

  public:
    ~amGHOST_WindowWIN32() {};
     amGHOST_WindowWIN32() {};

    /** PureVirtual Funcs from amGHOST_System */
    amGHOST_VkSurfaceKHR* init_VkSurface_interface(void);

  public:
    void destroy(void);
    void show_window(void) {
        ::ShowWindow(this->m_hwnd, SW_SHOW);
        ::SetFocus(this->m_hwnd);
    }
    void hide_window(void) {
        ::ShowWindow(this->m_hwnd, SW_HIDE);
    }
};