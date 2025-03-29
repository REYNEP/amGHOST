#include "amGHOST_SystemWIN32.hh"

// Convert To ASCII Art:- `bitbelt.converttoasciiart` -> REYNEP's_Journal\21.mar22_ASCII_ART.md
/**                                                                              
        //   ) )                           ||   / /                                         
       //___/ /           __      ___      ||  / / ( )  __    __  ___           ___     //  
      / ____ / //   / / //  ) ) //___) )   || / / / / //  ) )  / /   //   / / //   ) ) //   
     //       //   / / //      //          ||/ / / / //       / /   //   / / //   / / //    
    //       ((___( ( //      ((____       |  / / / //       / /   ((___( ( ((___( ( //     
    
*/
/** PureVirtual Funcs from amGHOST_System  */
#include "amGHOST_WindowWIN32.hh"
amGHOST_Window* amGHOST_SystemWIN32::new_window_interface(void) {
    amGHOST_WindowWIN32 *REY = new amGHOST_WindowWIN32();
    return REY;
}





/**
    ┏━┓┏━┓┏━┓╺┳╸┏━╸┏━╸╺┳╸┏━╸╺┳┓
    ┣━┛┣┳┛┃ ┃ ┃ ┣╸ ┃   ┃ ┣╸  ┃┃
    ╹  ╹┗╸┗━┛ ╹ ┗━╸┗━╸ ╹ ┗━╸╺┻┛
 */
void amGHOST_SystemWIN32::_reg_wc() 
{
    // Documentation:- https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexw
    this->_wc = {
        .cbSize = sizeof(WNDCLASSEXW),
            // [NEW][Ex] Required for Ex version
        .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
            // openGL -> requires it to be CS_OWNDC, see https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL)
        .lpfnWndProc = this->WndProc,
            // This is a [func_PTR]:- 'WndProc' Still Needs to be a PUBLIC_STATIC_FUNC / FREE_FUNC / GLOBAL_FUNC
        .cbClsExtra = 0,
        .cbWndExtra = 0,
            // Parameters to allocate extra-bytes to the WNDClass. Access extra-bytes with `get/setClassLong()`
        .hInstance = this->_hInstance,
            // Whoever is gonna use this WNDCLASS ==> would communicate THROUGH (eg. MSG message, events) this hInstance
        .hIcon = ::LoadIcon(nullptr, IDI_APPLICATION),
            // LoadIcon        Needs NULL param when Loading System Standard Icon [Probably "Loads" only, And 'Displaying it' is on a whole another lvl]
        .hCursor = ::LoadCursor(nullptr, IDC_ARROW),
            // LoadCursor Also Needs NULL param when Loading System Standard Cursor, later you can change it
        .hbrBackground = 0x00000000,
            // I would like to call this background color
        .lpszMenuName = nullptr,
            // You will need to pass name of the menu that you create and want to associate with the window
        .lpszClassName = this->_wndClassName,
            /**
             * CreateWindow will need this, (although i think passing &wc in CreateWindow would have been better, as WNDCLASS is a typedef struct)
             * 
             * Class names are local to the current process, so the name only needs to be unique within the process.
             * However, the standard Windows controls also have classes. 
             * 
             * If you use any of those controls, you must pick class names that don't conflict with the control class names.
             *   For example, the window class for the button control is named Button.
             */
        .hIconSm = nullptr
            // [NEW][Ex] Small icon version
    };

    if (::RegisterClassExW(&(this->_wc)) == 0) {
        amG_FAILED("::RegisterClassExW(amGHOST_SystemWIN32.wndclass)")
    }
    else {
        amG_PASSED("::RegisterClassExW(amGHOST_SystemWIN32.wndclass)");
    }
}

void amGHOST_SystemWIN32::_unreg_wc(void) {
    // No  UnregisterClassExW()  
    if (!::UnregisterClassW(this->_wndClassName, this->_hInstance)) {
        amG_FAILED_hint("::UnregisterClassW(amGHOST_SystemWIN32.wndclass)", "(most prolly).... a Window Still Exists!");
    }
}
























/** 
 * -------------------------------------
 * SECOND LOWER LEVEL (2LVL LOW) FUNCTIONS.... 
 * WINDOWS SPECIFIC FUNCTIONS [see .h of this file, these are all static funcs]
 * MOST Of these are 'MUST REQUIREMENT' For Win32 Apps/Programs
 * Some are Executed Automatically or By other WIN32 Functions
 * -------------------------------------
 *
 * For Docs On these Functions, Check MSDN
 */

/**
 * NOT EVERYTHING SHOULD BE HERE....
 *  EG: WM_SIZE should call \fn amGHOST_WindowWIN32::_MSG_kWindowResized()
 */
LRESULT WINAPI amGHOST_SystemWIN32::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            // Handle window creation
            return 0;

        case WM_DESTROY:
            // Handle window destruction
            PostQuitMessage(0);
            return 0;

        case WM_PAINT: {
            // Handle window painting
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_SIZE:
            // Handle window resizing
            return 0;

        case WM_KEYDOWN:
            // Handle key press
            if (wParam == VK_ESCAPE) {
                DestroyWindow(hwnd);
            }
            return 0;

        default:
            // Handle other messages
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}