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

#pragma endregion
























void _send_message_WM_MINMAXINFO(HWND hwnd) 
{
    INT xINC = 0, yINC = 0;

    // ================================================== Calculate xINC, yINC ==================================================
        LONG window_styles    = GetWindowLongPtr(hwnd, GWL_STYLE);
        LONG window_EXstyles  = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
        bool has_border       = (window_styles & WS_BORDER)      != 0;
        bool is_maximizable   = (window_styles & WS_MAXIMIZEBOX) != 0;
        bool is_child_window  = (window_styles & WS_CHILD)       != 0;
        bool is_ThickFrame    = (window_styles & WS_THICKFRAME)  != 0;
        bool is_DialogueFrame = (window_styles & WS_DLGFRAME)    != 0;
            /**
             TODO: Gotta improve:- https://github.com/rousseaux/netlabs.odin32/blob/master/src/user32/win32wbasepos.cpp#L88
                  HAS_THICKFRAME:- https://github.com/rousseaux/netlabs.odin32/blob/master/src/user32/win32wbase.h#L72
                         dwStyle:- https://github.com/rousseaux/netlabs.odin32/blob/master/src/user32/win32wbase.h#L386

                This guy also followed WINE (Windows on Linux) Project's Implementation
                    https://github.com/rousseaux/netlabs.odin32/blob/master/src/user32/win32wbasepos.cpp#L93

             Altho:- We are only supposed to check this about ThickFrame during ReSizing event:-
                https://github.com/rousseaux/netlabs.odin32/blob/master/src/user32/wintrack.cpp#L503
                https://github.com/rousseaux/netlabs.odin32/blob/master/src/user32/win32wbasenonclient.cpp#L350
             */

        if (is_ThickFrame)        {
                // The padded border was introduced in Windows 8     
                // [Assist: DeepSeek](was asking:- why am i getting xINC = 4 while win32 internally sends xINC = 8)
            xINC += ::GetSystemMetricsForDpi(SM_CXSIZEFRAME, ::GetDpiForWindow(hwnd)) + ::GetSystemMetrics(SM_CXPADDEDBORDER); 
            yINC += ::GetSystemMetricsForDpi(SM_CYSIZEFRAME, ::GetDpiForWindow(hwnd)) + ::GetSystemMetrics(SM_CXPADDEDBORDER);
        }
        else if (has_border)      {
            xINC += ::GetSystemMetricsForDpi(SM_CXBORDER, ::GetDpiForWindow(hwnd)); 
            yINC += ::GetSystemMetricsForDpi(SM_CYBORDER, ::GetDpiForWindow(hwnd));
        }
        else if (is_DialogueFrame){
            xINC += ::GetSystemMetricsForDpi(SM_CXDLGFRAME, ::GetDpiForWindow(hwnd)); 
            yINC += ::GetSystemMetricsForDpi(SM_CYDLGFRAME, ::GetDpiForWindow(hwnd));
        }
    // ================================================== Calculate xINC, yINC ==================================================


        /** 
         * For top-level windows, these values are based on the width of the primary monitor.
         * MINMAXINFO: Information about 'when' MINIMIZED / MAXIMIZED
         * https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-minmaxinfo  
         * 
         * TODO:- Handle ptMaxSize for Child Window:-  https://github.com/rousseaux/netlabs.odin32/blob/master/src/user32/win32wbasepos.cpp#L58
         **/
    MINMAXINFO MinMax = {
        .ptMaxSize = {
            .x = ::GetSystemMetrics(SM_CXSCREEN) + (2*xINC),
            .y = ::GetSystemMetrics(SM_CYSCREEN) + (2*yINC),
        },
        .ptMaxPosition = {
            .x = 0 - xINC,
            .y = 0 - yINC
        },
        .ptMinTrackSize = {
            .x = ::GetSystemMetrics(SM_CXMINTRACK),
            .y = ::GetSystemMetrics(SM_CYMINTRACK)
        },
        .ptMaxTrackSize = {
            .x = ::GetSystemMetrics(SM_CXMAXTRACK),
            .y = ::GetSystemMetrics(SM_CYMAXTRACK)
        }
    };

    ::SendMessageA(hwnd, WM_GETMINMAXINFO, 0, (LPARAM) &MinMax);
}





#define log_Func1() REY_LOG_win32_message (hwnd, msg, wParam, lParam)
#define log_Func2() REY_GET_win32_message2(hwnd, msg, wParam, lParam)
#define log_ModalLoop amGHOST_SystemWIN32::log_ModalLoopEventsHandling

#define Entering "  --> Entering: DefWindowProc"
#define Returned "  --> Returned: DefWindowProc"

#define LOG_ModalLoop_P1(x) if (log_ModalLoop) {log_Func2(); REY_LOG("  [REY_MODAL_LOOP]:- " << x << Entering);}   else  {log_Func1();}
#define LOG_ModalLoop_P2(x) if (log_ModalLoop) {             REY_LOG("  [REY_MODAL_LOOP]:- " << x << Returned);}

#define Wrap_ModalLoop_Event(x)                     \
        LOG_ModalLoop_P1(#x)                        \
            LRESULT xD = DefWindowProc(hwnd, msg, wParam, lParam);  \
        LOG_ModalLoop_P2(#x)                        \


#pragma    region WndProc
#include "WIN32_EXT/amGHOST_DebugWIN32.hh"
LRESULT WINAPI amGHOST_SystemWIN32::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    amGHOST_WindowWIN32  *WND = amGHOST_SystemWIN32::get_amGHOST_WindowWIN32(hwnd);
    bool found_amGHOST_Window = (WND != nullptr) ? true : false;

    switch (msg) {
        /*
            ____    __    ____ .___  ___.        ______ .______       _______     ___   .___________. _______ 
            \   \  /  \  /   / |   \/   |       /      ||   _  \     |   ____|   /   \  |           ||   ____|
             \   \/    \/   /  |  \  /  |      |  ,----'|  |_)  |    |  |__     /  ^  \ `---|  |----`|  |__   
              \            /   |  |\/|  |      |  |     |      /     |   __|   /  /_\  \    |  |     |   __|  
               \    /\    /    |  |  |  |      |  `----.|  |\  \----.|  |____ /  _____  \   |  |     |  |____ 
                \__/  \__/     |__|  |__|  _____\______|| _| `._____||_______/__/     \__\  |__|     |_______|
                                          |______|                                                            
        */
        case WM_CREATE: {
            REY_LOG("WM_CREATE");
            return 0;
        }

        case WM_DESTROY: {
            REY_LOG("WM_DESTROY");
            ::PostQuitMessage(0);
            return 0;
        }

        /*
            ____    __    ____ .___  ___.       .______      ___       __  .__   __. .___________.
            \   \  /  \  /   / |   \/   |       |   _  \    /   \     |  | |  \ |  | |           |
             \   \/    \/   /  |  \  /  |       |  |_)  |  /  ^  \    |  | |   \|  | `---|  |----`
              \            /   |  |\/|  |       |   ___/  /  /_\  \   |  | |  . `  |     |  |     
               \    /\    /    |  |  |  |       |  |     /  _____  \  |  | |  |\   |     |  |     
                \__/  \__/     |__|  |__|  _____| _|    /__/     \__\ |__| |__| \__|     |__|     
                                          |______|                                                
        */
        case WM_PAINT: {
            REY_LOG("WM_PAINT");
                PAINTSTRUCT ps;
                HDC hdc = ::BeginPaint(hwnd, &ps);
                ::FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
                ::EndPaint(hwnd, &ps);
            return 0;
        }

        /*
            ____    __    ____ .___  ___.            _______. __   ________   _______ 
            \   \  /  \  /   / |   \/   |           /       ||  | |       /  |   ____|
             \   \/    \/   /  |  \  /  |          |   (----`|  | `---/  /   |  |__   
              \            /   |  |\/|  |           \   \    |  |    /  /    |   __|  
               \    /\    /    |  |  |  |       .----)   |   |  |   /  /----.|  |____ 
                \__/  \__/     |__|  |__|  _____|_______/    |__|  /________||_______|
                                          |______|                                    
        */
        case WM_SIZE: {
            REY_LOG("WM_SIZE");
            WND->_konsume_event(amGHOST_Event(amE::Type::WindowResize, amE::Category::Window));
            return 0;
        }

        /*
            ____    __    ____ .___  ___.            _______.____    ____  _______.  ______   ______   .___  ___. .___  ___.      ___      .__   __.  _______  
            \   \  /  \  /   / |   \/   |           /       |\   \  /   / /       | /      | /  __  \  |   \/   | |   \/   |     /   \     |  \ |  | |       \ 
             \   \/    \/   /  |  \  /  |          |   (----` \   \/   / |   (----`|  ,----'|  |  |  | |  \  /  | |  \  /  |    /  ^  \    |   \|  | |  .--.  |
              \            /   |  |\/|  |           \   \      \_    _/   \   \    |  |     |  |  |  | |  |\/|  | |  |\/|  |   /  /_\  \   |  . `  | |  |  |  |
               \    /\    /    |  |  |  |       .----)   |       |  | .----)   |   |  `----.|  `--'  | |  |  |  | |  |  |  |  /  _____  \  |  |\   | |  '--'  |
                \__/  \__/     |__|  |__|  _____|_______/        |__| |_______/     \______| \______/  |__|  |__| |__|  |__| /__/     \__\ |__| \__| |_______/ 
                                          |______|                                                                                                             
        */
        case WM_SYSCOMMAND: {
            if ((wParam & 0xFFF0)== SC_SIZE) {
                LOG_ModalLoop_P1("WM_SYSCOMMAND");

                    REY_LOG("[REY] Trynna Handle WM_SYSCOMMAND.[wParam]SC_SIZE ourselves");

                    _send_message_WM_MINMAXINFO(hwnd);
                    //::SendMessageA(hwnd, WM_ENTERSIZEMOVE, 0, 0);
                    //::SendMessageA(hwnd, WM_NCMOUSELEAVE,  0, 0);

                    LRESULT xD = DefWindowProc(hwnd, msg, wParam, lParam);
                    // Now gotta implement:- Whatever is happening inside the Loop
                        // https://github.com/rousseaux/netlabs.odin32/blob/master/src/user32/wintrack.cpp#L564

                    //::SendMessageA(hwnd, WM_CAPTURECHANGED,  0, 0);
                    //::SendMessageA(hwnd, WM_WINDOWPOSCHANGING,  0, 0);  // Gotta Handle this one
                    //_send_message_WM_MINMAXINFO(hwnd);
                    //::SendMessageA(hwnd, WM_EXITSIZEMOVE, 0, 0);

                LOG_ModalLoop_P2("WM_SYSCOMMAND");
                return xD;
            } else {
                Wrap_ModalLoop_Event(WM_SYSCOMMAND);
                return xD;
            }
        }
        case WM_NCLBUTTONDOWN: {
            Wrap_ModalLoop_Event(WM_NCLBUTTONDOWN);
            return xD;
        }
        case WM_GETMINMAXINFO: {
            LPMINMAXINFO pMMI = (LPMINMAXINFO)lParam;
            REY_LOG_win32_message(hwnd, msg, wParam, lParam);
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }

        /*
            ____    __    ____ .___  ___.        __  ___  ___________    ____  _______   ______   ____    __    ____ .__   __. 
            \   \  /  \  /   / |   \/   |       |  |/  / |   ____\   \  /   / |       \ /  __  \  \   \  /  \  /   / |  \ |  | 
             \   \/    \/   /  |  \  /  |       |  '  /  |  |__   \   \/   /  |  .--.  |  |  |  |  \   \/    \/   /  |   \|  | 
              \            /   |  |\/|  |       |    <   |   __|   \_    _/   |  |  |  |  |  |  |   \            /   |  . `  | 
               \    /\    /    |  |  |  |       |  .  \  |  |____    |  |     |  '--'  |  `--'  |    \    /\    /    |  |\   | 
                \__/  \__/     |__|  |__|  _____|__|\__\ |_______|   |__|     |_______/ \______/      \__/  \__/     |__| \__| 
                                          |______|                                                                             
        */
        case WM_KEYDOWN: {
            REY_LOG("WM_KEYDOWN");
            if (wParam == VK_ESCAPE) {
                ::DestroyWindow(hwnd);
            }
            return 0;
        }

        default: {
            REY_LOG_win32_message(hwnd, msg, wParam, lParam);
            return  DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }
}
#pragma endregion
#pragma    region amG_dispatch
/** This function will be called by `amGHOST_Window::dispatch_events_with_OSModalLoops()` & it's better to rather use that function */
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
        ::DispatchMessage(&msg);    // Send the message to amGHOST_SystemWIN32::WndProc
    }
}
#pragma endregion