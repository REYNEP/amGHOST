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
        amG_FAILED1("::RegisterClassExW(amGHOST_SystemWIN32.wndclass)")
    }
    else {
        amG_PASSED1("::RegisterClassExW(amGHOST_SystemWIN32.wndclass)");
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
 * NOT EVERYTHING SHOULD BE HERE.... inside WndProc
 *  EG: WM_SIZE should call \fn amGHOST_WindowWIN32::_MSG_kWindowResized()
 */

#include "WIN32_EXT/amGHOST_DebugWIN32.hh"
/** 
 * ## 😉 win32 "Window Procedure Function" [WndProc]
 * - INFO
 *      - - called by process_events() -> ::DispatchMessageA()
 *      - - Deals with OS Messages and Events, hwnd is the Handle to Window
 * 
 * - Windows asks for this function to be a GLOBAL STATIC function. But why would this work while being defined inside a Class?
 * - WHY-THIS-WORKS:-
 *   - - C++ treats MEMBER_FUNCs and free functions [i.e. PUBLIC_STATIC_FUNCs] differently 
 *              MEMBER_FUNCs need to have access to a "this" pointer, and typically that's passed in as a hidden first parameter to MEMBER_FUNCs
 *   You can, however, declare "WndProc" as a PUBLIC_STATIC_FUNC, which eliminates the this pointer. [https://stackoverflow.com/a/17221900]
 * 
 * - EASTER:- Let's See if anyone can use the Power of this being Public, 
 *       - - [I mean you could just call amGHOST_SystemWIN32::WndProc() & pass in aruments to it, MANUALLY CREATING "EVENTS"]
 *           That's It POWERRRRRR
 */
LRESULT WINAPI amGHOST_SystemWIN32::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    switch (msg) {
        case WM_CREATE:
            // Handle window creation
            REY_LOG("WM_CREATE");
            return 0;

        case WM_DESTROY:
            // Handle window destruction
            ::PostQuitMessage(0);
            REY_LOG("WM_DESTROY");
            return 0;

        case WM_PAINT: {
            // Handle window painting
            PAINTSTRUCT ps;
            HDC hdc = ::BeginPaint(hwnd, &ps);
            ::FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
            ::EndPaint(hwnd, &ps);
            REY_LOG("WM_PAINT");
            return 0;
        }

        case WM_SIZE:
            // Handle window resizing
            REY_LOG("WM_SIZE");
            return 0;

        case WM_KEYDOWN:
            // Handle key press
            if (wParam == VK_ESCAPE) {
                ::DestroyWindow(hwnd);
            }
            REY_LOG("WM_KEYDOWN");
            return 0;

        default:
            // Handle other messages
            REY_LOG_WIN32_message_name(msg);
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

/** Written with help from Github Copilot vscode extension */
void amGHOST_SystemWIN32::dispatch_events(void) {
    MSG msg;
    while (
        ::PeekMessage(          // Returns false when no event is available
            &msg,               // OUT Variable
            nullptr,            // [hwnd] nullptr:- retrieves messages for any window created by the calling thread
            0,                  // minimum value of the range of messages to be retrieved.     Use 0 to retrieve all messages
            0,                  // maximum value of the range of messages to be retrieved.     Use 0 to retrieve all messages
            PM_REMOVE           // [PM_REMOVE]:- Messages are removed from the queue after being retrieved.    / [PM_NOREMOVE] / [PM_NOYIELD]
        )
    )
    {
        ::TranslateMessage(&msg);   // Preprocess keyboard messages (optional)
        ::DispatchMessage(&msg);    // Send the message to WndProc
    }
}