/*
                    Convert To ASCII Art:- `bitbelt.converttoasciiart` -> REYNEP's_Journal\21.mar22_ASCII_ART.md

    .______    __    __  .______       _______       ____    ____  __  .______     .___________. __    __       ___       __      
    |   _  \  |  |  |  | |   _  \     |   ____|      \   \  /   / |  | |   _  \    |           ||  |  |  |     /   \     |  |     
    |  |_)  | |  |  |  | |  |_)  |    |  |__          \   \/   /  |  | |  |_)  |   `---|  |----`|  |  |  |    /  ^  \    |  |     
    |   ___/  |  |  |  | |      /     |   __|          \      /   |  | |      /        |  |     |  |  |  |   /  /_\  \   |  |     
    |  |      |  `--'  | |  |\  \----.|  |____          \    /    |  | |  |\  \----.   |  |     |  `--'  |  /  _____  \  |  `----.
    | _|       \______/  | _| `._____||_______|          \__/     |__| | _| `._____|   |__|      \______/  /__/     \__\ |_______|
                                                                                                                              
*/

#include "amGHOST_SystemWIN32.hh"
#include "amGHOST_WindowWIN32.hh"
amGHOST_Window* amGHOST_SystemWIN32::new_window_interface(void) {
    amGHOST_WindowWIN32 *REY = new amGHOST_WindowWIN32();

        amGHOST_System::REY_1D_Windows.push_back((amGHOST_Window*) REY);

    return REY;
}


/*

         _______.___________.    ___   .___________. __    ______           _______  __    __  .__   __.   ______     _______.
        /       |           |   /   \  |           ||  |  /      |         |   ____||  |  |  | |  \ |  |  /      |   /       |
       |   (----`---|  |----`  /  ^  \ `---|  |----`|  | |  ,----'         |  |__   |  |  |  | |   \|  | |  ,----'  |   (----`
        \   \       |  |      /  /_\  \    |  |     |  | |  |              |   __|  |  |  |  | |  . `  | |  |        \   \    
    .----)   |      |  |     /  _____  \   |  |     |  | |  `----.         |  |     |  `--'  | |  |\   | |  `----.----)   |   
    |_______/       |__|    /__/     \__\  |__|     |__|  \______|         |__|      \______/  |__| \__|  \______|_______/    
                                                                                                                          

*/
amGHOST_WindowWIN32* amGHOST_SystemWIN32::get_amGHOST_WindowWIN32(HWND hwnd) {
    amGHOST_WindowWIN32* WND = nullptr;

    for (int k = 0, lim = amGHOST_System::REY_1D_Windows.neXt; k < lim; k++) {
        WND = (amGHOST_WindowWIN32 *) amGHOST_System::REY_1D_Windows[k];

        if (WND->m_hwnd == hwnd) {return WND;}
    }

    // REY_LOG_EX("[amGHOST_Window = " << WND << "]:- not found in `amGHOST_System::REY_1D_Windows` .... 😭");
    return nullptr;
}






















#pragma region WndClassExW

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
        .hbrBackground = nullptr,
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




















#pragma    region WndProc
#include "WIN32_EXT/amGHOST_DebugWIN32.hh"
LRESULT WINAPI amGHOST_SystemWIN32::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    amGHOST_WindowWIN32  *WND = amGHOST_SystemWIN32::get_amGHOST_WindowWIN32(hwnd);
    bool found_amGHOST_Window = (WND != nullptr) ? true : false;

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
            WND->_konsume_event(amGHOST_Event(amGE::Type::WindowResize, amGE::Category::Window));
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
#pragma endregion
#pragma    region amG_dispatch
/** Written with help from Github Copilot vscode extension */
void amGHOST_SystemWIN32::dispatch_events_with_OSModalLoops(void) {
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
#pragma engregion