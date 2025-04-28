
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

#pragma region ::WndProc

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
    amGHOST_WindowWIN32  *WND = amGHOST_SystemWIN32::get_amGHOST_Window(hwnd);
    bool found_amGHOST_Window = (WND != nullptr) ? true : false;

    switch (msg) {
        #pragma region WM_PAINT
        /*
             __          ____  __          _____        _____ _   _ _______ 
             \ \        / /  \/  |        |  __ \ /\   |_   _| \ | |__   __|
              \ \  /\  / /| \  / |        | |__) /  \    | | |  \| |  | |   
               \ \/  \/ / | |\/| |        |  ___/ /\ \   | | | . ` |  | |   
                \  /\  /  | |  | |        | |  / ____ \ _| |_| |\  |  | |   
                 \/  \/   |_|  |_|        |_| /_/    \_\_____|_| \_|  |_|   
                               ______ ______                                
                              |______|______|                               
         */
        case WM_PAINT: {
            /** 
             * 1. The WM_PAINT message is generated by the system and should not be sent by an application.
             * 2. The system sends this message when there are no other messages in the application's message queue.
             *      - ::DispatchMessage() ---> determines where to send the message; 
             *      - ::     GetMessage() ---> determines which message to dispatch;
             *      - ::    PeekMessage() ---> IGuess, does the same as above
             * 
             * 3. Default Handling Example:- 
             *      - https://learn.microsoft.com/en-us/windows/win32/gdi/wm-paint#example
             * 
             * 4.     ::GetMessage() / ::PeekMessage() returns the WM_PAINT message when there are no other messages in the application's message queue, &
             *   ::DispatchMessage() sends the message to the appropriate window procedure.
             * 
             * 5. [REY] implicit MODAL-LOOP:-
             *      - This is kind of like the last message that the     ::DispatchMessage() is gonna dispatch 💁‍♀️
             *      - But the thing is,           DURING ReSizing, win32 ::DispatchMessage() starts a "ModalLoop", kinda implicitly 🫡
             *      - kinda like a win32 internal ::waitMessage() inside ::DispatchMessage() 😵‍💫
             *      - I genuinely Hate this idea of MODAL-LOOP
             *      - So I asked ChatGPT (vscode-copilot-sidebar), 3 questions
             *          1. Is there any alternative to DispatchMessage?                             ---> NO
             *          2. What if I wanna end the modal Loops? (say during drag & drop / resizing) ---> Can't
             *          3. as a last resort if none of the above is doable, can't we just call WndProc ourselves? after calling GetMessage....
             *              - Just call WndProc() instead of calling ::DispatchMessage()
             *      - UNREAL:-
             *          - https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Runtime/ApplicationCore/Private/Windows/WindowsApplication.cpp#L1595
             * 
             * 6. A window may receive internal paint messages as a result of calling ::RedrawWindow() with the RDW_INTERNALPAINT flag set.
             *      - In this case, the window may not have an update region.
             *      - An application may call the GetUpdateRect function to determine whether the window has an update region.
             *      - If GetUpdateRect returns zero, the application need not call the BeginPaint and EndPaint functions.
             * 
             * 7. The WM_PAINT message is generated by the system and should not be sent by an application.
             *      - The system sends an internal WM_PAINT message only once.
             *      - After an internal WM_PAINT message is returned from ::GetMessage() or ::PeekMessage() or is sent to a window by ::UpdateWindow()
             *              - the system does not post or send further WM_PAINT messages until the window is invalidated
             *              - or until ::RedrawWindow() is called again with the RDW_INTERNALPAINT flag set.
             * 
             * 8. An application must check for any necessary internal painting 
             *      - you do this by "looking at its internal data structures for each WM_PAINT message"
             *          - (REY: I don't quite understand what they exactly meant by the above Quote)
             *      - because a WM_PAINT message may have been caused by both:-
             *          1) a non-NULL update region and
             *          2) a call to RedrawWindow with the RDW_INTERNALPAINT flag set.
             * 
             * 9. default WM_PAINT message processing:-
             *      - For some common controls, the default WM_PAINT message processing checks the wParam parameter. 
             *      - If wParam is non-NULL, the control assumes that the value is an HDC and paints using that device context.
             * 
             *      TODO: read the Full Remarks @ https://learn.microsoft.com/en-us/windows/win32/gdi/wm-paint
             */
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Perform drawing operations here
            // Example: Fill the client area with a solid color
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);
            return 0;
        }

        #pragma region WM_SIZE
        /*
             __          ____  __           _____ _____ ____________ 
             \ \        / /  \/  |         / ____|_   _|___  /  ____|
              \ \  /\  / /| \  / |        | (___   | |    / /| |__   
               \ \/  \/ / | |\/| |         \___ \  | |   / / |  __|  
                \  /\  /  | |  | |         ____) |_| |_ / /__| |____ 
                 \/  \/   |_|  |_|        |_____/|_____/_____|______|
                               ______ ______                         
                              |______|______|                        
         */
        case WM_SIZE: {
            /* The WM_SIZE message is sent to a window after its size has changed.
             * The WM_SIZE and WM_MOVE messages are not sent if an application handles the WM_WINDOWPOSCHANGED message without calling DefWindowProc.
             *      - Altho, It is more efficient to perform any move or size change processing 
             *        during the WM_WINDOWPOSCHANGED message without calling DefWindowProc.
             */
            WND->_konsume_event(amGHOST_Event(amGE::Type::WindowResize, amGE::Category::Window));
            PostMessage(hwnd, WM_QUIT, 0, 0);
            return 0;
        }
        case WM_SIZING: {
            REY_LOG("WM_SIZING");
            return 0;
        }
        case WM_ENTERSIZEMOVE: {
            REY_LOG("WM_ENTERSIZEMOVE");
            return 0;
        }
        case WM_EXITSIZEMOVE: {
            REY_LOG("WM_EXITSIZEMOVE");
            return 0;
        }
        case WM_NCMOUSELEAVE: {
            REY_LOG("WM_NCMOUSELEAVE");
            return 0;
        }
        case WM_WINDOWPOSCHANGING: {
            REY_LOG("WM_WINDOWPOSCHANGING");
            return 0;
        }
        case WM_NCPAINT: {
            REY_LOG("WM_NCPAINT");
            return 0;
        }
        case WM_GETMINMAXINFO: {
            REY_LOG("WM_GETMINMAXINFO");
            return 0;
        }
        case WM_WINDOWPOSCHANGED: {
            REY_LOG("WM_WINDOWPOSCHANGED");
            return 0;
        }
        case WM_SYSCOMMAND: {
            REY_LOG("WM_SYSCOMMAND");
            LRESULT xD = DefWindowProcW(hwnd, msg, wParam, lParam);
            REY_LOG("Returned: DefWindowProcW");
            return xD;
        }
        case WM_NCLBUTTONDOWN: {
            REY_LOG("WM_NCLBUTTONDOWN");
            LRESULT xD = DefWindowProcW(hwnd, msg, wParam, lParam);
            REY_LOG("Returned: DefWindowProcW");
            return xD;
        }
        case 96: {
            REY_LOG("96");
            return 0;
        }
        case 802: {
            REY_LOG("802");
            return 0;
        }

        #pragma region WM_ERASEBKGND
        /*
             __          ____  __          ______ _____             _____ ______ ____  _  _______ _   _ _____  
             \ \        / /  \/  |        |  ____|  __ \     /\    / ____|  ____|  _ \| |/ / ____| \ | |  __ \ 
              \ \  /\  / /| \  / |        | |__  | |__) |   /  \  | (___ | |__  | |_) | ' / |  __|  \| | |  | |
               \ \/  \/ / | |\/| |        |  __| |  _  /   / /\ \  \___ \|  __| |  _ <|  <| | |_ | . ` | |  | |
                \  /\  /  | |  | |        | |____| | \ \  / ____ \ ____) | |____| |_) | . \ |__| | |\  | |__| |
                 \/  \/   |_|  |_|        |______|_|  \_\/_/    \_\_____/|______|____/|_|\_\_____|_| \_|_____/ 
                               ______ ______                                                                   
                              |______|______|                                                                  
        */
        case WM_ERASEBKGND: {
            /* An application sends the WM_ERASEBKGND message when the window background must be
             * erased (for example, when a window is resized). The message is sent to prepare an
             * invalidated portion of a window for painting. */
            HBRUSH bgBrush = (HBRUSH)GetClassLongPtr(hwnd, GCLP_HBRBACKGROUND);
            if (bgBrush) {
                RECT rect;
                GetClientRect(hwnd, &rect);
                FillRect((HDC)(wParam), &rect, bgBrush);
                /* Clear the background brush after the initial fill as we don't
                 * need or want any default Windows fill behavior on redraw. */
                SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR) nullptr);
            }
            return 0;
        }

        #pragma region WM_CREATE
        /*
             __          ____  __          _____ _____  ______       _______ ______ 
             \ \        / /  \/  |        / ____|  __ \|  ____|   /\|__   __|  ____|
              \ \  /\  / /| \  / |       | |    | |__) | |__     /  \  | |  | |__   
               \ \/  \/ / | |\/| |       | |    |  _  /|  __|   / /\ \ | |  |  __|  
                \  /\  /  | |  | |       | |____| | \ \| |____ / ____ \| |  | |____ 
                 \/  \/   |_|  |_|        \_____|_|  \_\______/_/    \_\_|  |______|
                               ______ ______                                        
                              |______|______|                                       
         */
        case WM_CREATE: {
            REY_LOG("WM_CREATE");
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        case WM_NCCREATE: {
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        case WM_NCCALCSIZE: {
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        case WM_DESTROY: {
            REY_LOG("WM_DESTROY");
            ::PostQuitMessage(0);
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        

        #pragma region WM_KEYDOWN
        /*
             __          ____  __          _  __________     _______   ______          ___   _ 
             \ \        / /  \/  |        | |/ /  ____\ \   / /  __ \ / __ \ \        / / \ | |
              \ \  /\  / /| \  / |        | ' /| |__   \ \_/ /| |  | | |  | \ \  /\  / /|  \| |
               \ \/  \/ / | |\/| |        |  < |  __|   \   / | |  | | |  | |\ \/  \/ / | . ` |
                \  /\  /  | |  | |        | . \| |____   | |  | |__| | |__| | \  /\  /  | |\  |
                 \/  \/   |_|  |_|        |_|\_\______|  |_|  |_____/ \____/   \/  \/   |_| \_|
                               ______ ______                                                   
                              |______|______|                                                  
        */
        case WM_KEYDOWN:
            REY_LOG("WM_KEYDOWN");
            if (wParam == VK_ESCAPE) {
                ::DestroyWindow(hwnd);
            }
            return 0;

        default:
            REY_LOG_WIN32_message_name(msg);
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}























#pragma region amG_dispatch
/*
                   _____ _    _  ____   _____ _______          _ _                 _       _                                  _       
                  / ____| |  | |/ __ \ / ____|__   __|        | (_)               | |     | |                                | |      
   __ _ _ __ ___ | |  __| |__| | |  | | (___    | |         __| |_ ___ _ __   __ _| |_ ___| |__           _____   _____ _ __ | |_ ___ 
  / _` | '_ ` _ \| | |_ |  __  | |  | |\___ \   | |        / _` | / __| '_ \ / _` | __/ __| '_ \         / _ \ \ / / _ \ '_ \| __/ __|
 | (_| | | | | | | |__| | |  | | |__| |____) |  | |       | (_| | \__ \ |_) | (_| | || (__| | | |       |  __/\ V /  __/ | | | |_\__ \
  \__,_|_| |_| |_|\_____|_|  |_|\____/|_____/   |_|        \__,_|_|___/ .__/ \__,_|\__\___|_| |_|        \___| \_/ \___|_| |_|\__|___/
                                                ______ ______         | |                     ______ ______                           
                                               |______|______|        |_|                    |______|______|                          
*/
void amGHOST_SystemWIN32::dispatch_events_with_OSModalLoops(void) {
    MSG msg;
    #pragma region ::PeekMSG
    bool HI = true;
    while (HI)
    {
        REY_LOG("Calling PeekMessage()");
        HI = ::PeekMessageW(    // Returns false when no event is available
            &msg,               // OUT Variable
            nullptr,            // [hwnd] nullptr:- retrieves messages for any window created by the calling thread
            0,                  // minimum value of the range of messages to be retrieved.     Use 0 to retrieve all messages
            0,                  // maximum value of the range of messages to be retrieved.     Use 0 to retrieve all messages
            PM_REMOVE           // [PM_REMOVE]:- Messages are removed from the queue after being retrieved.    / [PM_NOREMOVE] / [PM_NOYIELD]
        );
        REY_LOG("Returned From PeekMessage()");
        /**
         * ZERO
         *      ::GetMessage() / ::PeekMessage() does not retrieve all the Messages that get's pased on to WndProc
         *      Instead the      ::DefWindowProc() 
         *          - that we are calling inside amGHOST_SystemWIN32::WndProc()
         *          - is the real culprit
         *          - it calls our amGHOST_SystemWIN32::WndProc() by itself 💁‍♀️
         *          - i am guessing, it's because, we have already tied our WndProc to WndClass insige amGHOST_SystemWIN32::_reg_wc()
         *          - So, ::DefWindowProc() doesn't care about the STACK_TRACE nor the fact that ::PeekMessage() is beind called outside
         *              - all by itself, it calls up WndProc()
         * 
         * ONE
         *       ::GetMessage() / ::PeekMessage() returns the WM_PAINT message when there are no other messages in the application's message queue, &
         *   ::DispatchMessage() sends the message to the appropriate window procedure.
         * 
         * TWO
            If no filter is specified, messages are processed in the following order:
                Sent messages
                Posted messages
                Input (hardware) messages and system internal events
                Sent messages (again)
                WM_PAINT messages
                WM_TIMER messages
         *
         * THREE
         *   If a top-level window stops responding to messages for more than several seconds, 
         *      - the system considers the window to be not responding 
         *      - and replaces it with a ghost window that has the same z-order, location, size, and visual attributes. 
         *      - This allows the user to move it, resize it, or even close the application. 
         *      - However, 
         *          - these are the only actions available because the application is actually not responding. 
         *          - When an application is being debugged, the system does not generate a ghost window.
         */

        ::TranslateMessage(&msg);    // Preprocess keyboard messages (optional)

        #pragma region ::DispatchMSG
        /**
         * This Function does not return while window is being resized. 
         *      - WM_SIZE, WM_SIZING, WM_PAINT, even after all of these messaged being dispatched, this function does not return.
         * This function Waits.
         *      - Waits till WM_EXITSIZEMOVE or similar operation. 
         *      - Under the hood, windows only lets ::DispatchMessage() return after mouse-button has been "Released"! 💁‍♀️
         * 
         ***** 
             * - The WM_PAINT message is generated by the system and should not be sent by an application.
             * - The system sends this message when there are no other messages in the application's message queue.
             *      - ::DispatchMessage() ---> determines where to send the message; + Get's into win32 ModalLoops
             *      - ::     GetMessage() ---> determines which message to dispatch;
             *      - ::    PeekMessage() ---> IGuess, does the same as above
         *****
         *
         * I got curious about 'how the heck do they even implement this piece of shit trash function that goes into MODAL-LOOP
         *      But sadly, windows is CLOSED-SOURCE / PROPRIETARY.... 
         *      Still, there are some openSource people who tried to implement win32 subsystem on Linux or smth idk
         *          - https://doxygen.reactos.org/d4/d8c/win32ss_2user_2user32_2windows_2message_8c_source.html
         * 
         * Altho:- UNREAL Does call   ::DispatchMessage()   & then does Modal-Loop handling
         *      - https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Runtime/ApplicationCore/Private/Windows/WindowsApplication.cpp#L1595
         */
        REY_LOG("Calling DispatchMessageW()");
        ::DispatchMessageW(&msg);    // Send the message to WndProc
        REY_LOG("Returned From DispatchMessageW()");

        #pragma region ModalLoops
    }
}
void amGHOST_SystemWIN32::dispatch_events_without_OSModalLoops(void) {
    MSG msg;
    bool HI = true;
    while (HI)
    {
        REY_LOG("Calling PeekMessage()");
        HI = ::PeekMessageW(    // Returns false when no event is available
            &msg,               // OUT Variable
            nullptr,            // [hwnd] nullptr:- retrieves messages for any window created by the calling thread
            0,                  // minimum value of the range of messages to be retrieved.     Use 0 to retrieve all messages
            0,                  // maximum value of the range of messages to be retrieved.     Use 0 to retrieve all messages
            PM_REMOVE           // [PM_REMOVE]:- Messages are removed from the queue after being retrieved.    / [PM_NOREMOVE] / [PM_NOYIELD]
        );
        REY_LOG("Returned From PeekMessage()");

        if (msg.message == WM_QUIT) {
            break; // Exit the loop on WM_QUIT
        }
        // ::TranslateMessage(&msg);
        // Alternatively can all ::CallWindowProc()
        REY_LOG("Calling amGHOST_SystemWIN32::WndProc()")
        amGHOST_SystemWIN32::WndProc(msg.hwnd, msg.message, msg.wParam, msg.lParam);
        REY_LOG("Returned From amGHOST_SystemWIN32::WndProc()")
    }
}