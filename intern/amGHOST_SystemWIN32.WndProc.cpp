#include "amGHOST_SystemWIN32.hh"
#include "amGHOST_WindowWIN32.hh"








#pragma region BUG

/** RIGHT NOW THIS CAUSES A BUG */
/*



                                                             
                                                             
BBBBBBBBBBBBBBBBB   UUUUUUUU     UUUUUUUU       GGGGGGGGGGGGG
B::::::::::::::::B  U::::::U     U::::::U    GGG::::::::::::G
B::::::BBBBBB:::::B U::::::U     U::::::U  GG:::::::::::::::G
BB:::::B     B:::::BUU:::::U     U:::::UU G:::::GGGGGGGG::::G
  B::::B     B:::::B U:::::U     U:::::U G:::::G       GGGGGG
  B::::B     B:::::B U:::::D     D:::::UG:::::G              
  B::::BBBBBB:::::B  U:::::D     D:::::UG:::::G              
  B:::::::::::::BB   U:::::D     D:::::UG:::::G    GGGGGGGGGG
  B::::BBBBBB:::::B  U:::::D     D:::::UG:::::G    G::::::::G
  B::::B     B:::::B U:::::D     D:::::UG:::::G    GGGGG::::G
  B::::B     B:::::B U:::::D     D:::::UG:::::G        G::::G
  B::::B     B:::::B U::::::U   U::::::U G:::::G       G::::G
BB:::::BBBBBB::::::B U:::::::UUU:::::::U  G:::::GGGGGGGG::::G
B:::::::::::::::::B   UU:::::::::::::UU    GG:::::::::::::::G
B::::::::::::::::B      UU:::::::::UU        GGG::::::GGG:::G
BBBBBBBBBBBBBBBBB         UUUUUUUUU             GGGGGG   GGGG
                                                             
                                                             
                                                             
                                                             
                                                             
                                                             
                                                             



during resizing, when i let go of my mouse button.... the last event occured is WM_ENTERSIZEMOVE .... 
so there's double WM_ENTERSIZEMOVE instead of one ENTER another EXIT.... 
then i have to click on my mouse again for the WM_EXITSIZEMOVE to occur....

this only happens when i call ::ValidateRect(hwnd, nullptr); if i turn that off. 
which weird behavior doesn't happen. but without validate rect obviously VkQUeuePresent won't work
*/

#pragma endregion














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

/*

____    __    ____ .__   __.  _______  .______   .______        ______     ______ 
\   \  /  \  /   / |  \ |  | |       \ |   _  \  |   _  \      /  __  \   /      |
 \   \/    \/   /  |   \|  | |  .--.  ||  |_)  | |  |_)  |    |  |  |  | |  ,----'
  \            /   |  . `  | |  |  |  ||   ___/  |      /     |  |  |  | |  |     
   \    /\    /    |  |\   | |  '--'  ||  |      |  |\  \----.|  `--'  | |  `----.
    \__/  \__/     |__| \__| |_______/ | _|      | _| `._____| \______/   \______|


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
    amGHOST_WindowWIN32  *WND = amGHOST_SystemWIN32::get_amGHOST_WindowWIN32(hwnd);
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
            /** if you call DefWindowProc(WM_PAINT).... Then when resizing, Even after MOUSE RELEASE, it won't work properly wnough */
            return 0; // Indicate that the message has been handled
        }

        case WM_EXITSIZEMOVE: {
            ValidateRect(hwnd, nullptr);
            return DefWindowProc(hwnd, msg, wParam, lParam);
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
            //::ValidateRect(hwnd, nullptr); // Mark the entire client area as valid
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        #pragma region WM_SYSCMD
        /*
             __          ____  __           _______     _______  _____ ____  __  __ __  __          _   _ _____  
             \ \        / /  \/  |         / ____\ \   / / ____|/ ____/ __ \|  \/  |  \/  |   /\   | \ | |  __ \ 
              \ \  /\  / /| \  / |        | (___  \ \_/ / (___ | |   | |  | | \  / | \  / |  /  \  |  \| | |  | |
               \ \/  \/ / | |\/| |         \___ \  \   / \___ \| |   | |  | | |\/| | |\/| | / /\ \ | . ` | |  | |
                \  /\  /  | |  | |         ____) |  | |  ____) | |___| |__| | |  | | |  | |/ ____ \| |\  | |__| |
                 \/  \/   |_|  |_|        |_____/   |_| |_____/ \_____\____/|_|  |_|_|  |_/_/    \_\_| \_|_____/ 
                               ______ ______                                                                     
                              |______|______|                                                                    
        */
        case WM_SYSCOMMAND: {
            /**
             * This is the one responsible for starting that ModalLoop 💁‍♀️
             * 
             * A window receives this message
             *         when the user chooses a command from the Window menu (formerly known as the system or control menu) 
             *      or when the user chooses the maximize button, minimize button, restore button, or close button.
             * 
             * Any WM_SYSCOMMAND messages not handled by the application must be passed to DefWindowProc.
             */
            REY_LOG("WM_SYSCOMMAND");
            LRESULT xD = DefWindowProc(hwnd, msg, wParam, lParam);
            REY_LOG("Returned: DefWindowProcW");
            return xD;
        }
        case WM_NCLBUTTONDOWN: {
            REY_LOG("WM_NCLBUTTONDOWN");
            LRESULT xD = DefWindowProc(hwnd, msg, wParam, lParam);
            REY_LOG("Returned: DefWindowProcW");
            return xD;
        }
        case WM_NCLBUTTONUP: {
            REY_LOG("WM_NCLBUTTONDOWN");
            LRESULT xD = DefWindowProc(hwnd, msg, wParam, lParam);
            REY_LOG("Returned: DefWindowProcW");
            return xD;
        }
        case WM_SIZING: {
            REY_LOG("WM_SIZING");
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        case WM_ENTERSIZEMOVE: {
            REY_LOG("WM_ENTERSIZEMOVE");
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        case WM_NCMOUSELEAVE: {
            REY_LOG("WM_NCMOUSELEAVE");
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        case WM_WINDOWPOSCHANGING: {
            REY_LOG("WM_WINDOWPOSCHANGING");
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        case WM_NCPAINT: {
            REY_LOG("WM_NCPAINT");
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        case WM_GETMINMAXINFO: {
            REY_LOG("WM_GETMINMAXINFO");
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        case WM_WINDOWPOSCHANGED: {
            REY_LOG("WM_WINDOWPOSCHANGED");
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        case 96: {
            REY_LOG("96");
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        case 802: {
            REY_LOG("802");
            return DefWindowProc(hwnd, msg, wParam, lParam);
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
                ::GetClientRect(hwnd, &rect);
                ::FillRect((HDC)(wParam), &rect, bgBrush);
                /* Clear the background brush after the initial fill as we don't
                 * need or want any default Windows fill behavior on redraw. */
                ::SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR) nullptr);
            }
            return DefWindowProc(hwnd, msg, wParam, lParam);
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
        case WM_KEYDOWN: {
            REY_LOG("WM_KEYDOWN");
            if (wParam == VK_ESCAPE) {
                ::DestroyWindow(hwnd);
            }
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }

        default: {
            REY_LOG_WIN32_message_name(msg);
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
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
void amGHOST_SystemWIN32::dispatch_events_with_OSModalLoops(void) 
{
    if              (::GetCurrentThreadId() != this->_mainThread) {
        REY_LOG_EX( "::GetCurrentThreadId() != this->_mainThread 😰 ");
            // TODO: Log WarningID & Point to online Wiki/Docs
    }

    MSG msg;
    #pragma region ::PeekMSG
    bool HI = true;
    while (HI)
    {
        //REY_LOG("Calling PeekMessage()");
        HI = ::PeekMessageW(    // Returns false when no event is available
            &msg,               // OUT Variable
            nullptr,            // [hwnd] nullptr:- retrieves messages for any window created by the calling thread
            0,                  // minimum value of the range of messages to be retrieved.     Use 0 to retrieve all messages
            0,                  // maximum value of the range of messages to be retrieved.     Use 0 to retrieve all messages
            PM_REMOVE           // [PM_REMOVE]:- Messages are removed from the queue after being retrieved.    / [PM_NOREMOVE] / [PM_NOYIELD]
        );
        //REY_LOG("Returned From PeekMessage()");
        /**
         * ZERO
         *      ::GetMessage() / ::PeekMessage() does not retrieve all the Messages that get's passed on to WndProc.
         *          - Instead, when you pass events like WM_SYSCOMMAND --> ::DefWindowProc()
         *              - That's what starts the MODAL-LOOP
         *              - And it starts calling the WndProc tied to your window (by WNDCLASSEXW: amGHOST_SystemWIN32::_reg_wc()) all by itself
         *              - That's issss the meaning of MODAL-LOOP
         *                  - Kinda of like an IMPLICIT later of ::PeekMessage() that you don't have any control over
         * 
         *      Things to Know about
         *          - WM_SYSCOMMAND
         *          - WM_NCLBUTTONDOWN
         *          - if any of these two are not passed to ::DefWindowProc() 
         *              - ---> Then EVENTs like RESIZE / MINIMIZE / MAXIMIZE won't have any effect @ OS Level.... 
         *              - ---> Like you won't see anything changing, when you, let's say, try to grab onto the OS Window Rectangle's One corner and drag it
         *              - 💁‍♀️
         *       
         *      What actually does start the MODAL LOOP?
         *          ---> ::DefWindowProc(WM_SYSCOMMAND)
         * 
         *      Where does the program actually get stuck?
         *          ---> inside       ::DispatchMessage() --> amGHOST_SystemWIN32::WndProc() --> case WM_SYSCOMMAND --> ::DefWindowProc(WM_SYSCOMMAND)
         *      
         *      ::DefWindowProc()
         *          - that we are calling inside amGHOST_SystemWIN32::WndProc()
         *          - is the real culprit
         *          - it calls our amGHOST_SystemWIN32::WndProc() by itself 💁‍♀️ when we pass events like WM_SYSCOMMAND into it
         *          - kinda create's it's very own little MAINLOOP untill MOUSE RELEASE (which is exactly what's called MODAL-LOOP)
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
        //REY_LOG("Calling DispatchMessageW()");
        ::DispatchMessage(&msg);    // Send the message to WndProc
        //REY_LOG("Returned From DispatchMessageW()");
        

        #pragma region ModalLoopIMPL
        /**
         * Windows ALPC:-   https://stackoverflow.com/questions/71964485/whats-the-windows-message-of-id-96-0x0060
         *                  https://csandker.io/2022/05/24/Offensive-Windows-IPC-3-ALPC.html
         * 
         * Chinese blog of undefined Codes:- https://www.cnblogs.com/shangdawei/p/4014535.html
         *                                   https://www.google.com/search?q=win32+message+96+code
         * 
         *        Windows ERROR-CODES:- https://jomirife.blogspot.com/2017/11/win32-error-codes.html
         * Microsoft Docs as MARKDOWN:- https://github.com/MicrosoftDocs/win32/tree/docs/desktop-src/winmsg
         * 
         * I thought that the Message Loop was being caused by ::DistpatchMessage()
         *      So I searched for some over-riding implementations of it 💁‍♀️
         *          https://github.com/rousseaux/netlabs.odin32/blob/b903164a4f158fbd671048d294ac642fcca060be/src/user32/windowmsg.cpp#L45
         *          https://github.com/rousseaux/netlabs.odin32/blob/master/src/user32/winproc.cpp#L296
         * 
         * 
         * ## MODAL LOOP IMPL
         * 
         * Now that i know that the ModalLoop is actually caused inside ::DefWindowProcA() when handling WM_SYSCOMMAND
         *             https://github.com/rousseaux/netlabs.odin32/blob/b903164a4f158fbd671048d294ac642fcca060be/src/user32/win32wbase.cpp#L1581
         *          -> https://github.com/rousseaux/netlabs.odin32/blob/b903164a4f158fbd671048d294ac642fcca060be/src/user32/win32wbase.cpp#L1922
         *          -> https://github.com/rousseaux/netlabs.odin32/blob/b903164a4f158fbd671048d294ac642fcca060be/src/user32/win32wbasenonclient.cpp#L1318
         *          -> SC_SIZE: This is the key for Window Resizing event
         *          -> https://github.com/rousseaux/netlabs.odin32/blob/b903164a4f158fbd671048d294ac642fcca060be/src/user32/wintrack.cpp#L441
         *          -> & Here goes the ModalLoop 
         *          -> https://github.com/rousseaux/netlabs.odin32/blob/b903164a4f158fbd671048d294ac642fcca060be/src/user32/wintrack.cpp#L564
         * 
         * This guy did some great amount of work. Kudos to him TwT
         *      FORKS:- https://github.com/windows1988/netlabs.odin32
         *              https://github.com/bubach/netlabs.odin32
         *              https://github.com/CyberSys/netlabs.odin32
         * 
         * 
         * ## MODAL LOOP IMPL 2
         *          -> https://github.com/reactos/reactos/blob/378a335468a6e27fc0e4d7fc4b3fda2957bc4c74/win32ss/user/ntuser/defwnd.c#L121
         *          -> https://github.com/reactos/reactos/blob/378a335468a6e27fc0e4d7fc4b3fda2957bc4c74/win32ss/user/ntuser/nonclient.c#L251
         *          -> & Here goes the ModalLoop
         *          -> https://github.com/reactos/reactos/blob/378a335468a6e27fc0e4d7fc4b3fda2957bc4c74/win32ss/user/ntuser/nonclient.c#L403
         * 
         * 
         * ## SEARCHES, Books, Samples, Tools to test out
         *          -> https://www.google.com/search?q=dispatchmessageW
         *          -> https://learn.microsoft.com/en-us/visualstudio/debugger/introducing-spy-increment?view=vs-2022
         *          -> https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/
         *          -> https://github.com/Adityasakare/Books/blob/main/Charles%20Petzold%20-%20Programming%20Windows%20-%205th%20Ed.pdf
         *          -> https://github.com/DavidNash2024/Win32xx/tree/master/samples
         *          -> https://github.com/search?q=WM_SYSCOMMAND&type=wikis&p=1
         *          -> https://github.com/ocornut/imgui/discussions/8394#discussioncomment-12212793
         *          -> https://github.com/search?q=SC_SIZE&type=issues
         *          -> https://github.com/search?q=case+WM_SYSCOMMAND%3A+language%3AC%2B%2B&type=code&l=C%2B%2B
         *          -> https://github.com/libsdl-org/SDL/issues/1059
         *          -> https://sourceforge.net/p/win32loopl/code/ci/d5b990499f4041e6c848e7900f616ab629467730/tree/LooplessSizeMove.c#L311
         *          -> https://github.com/aldrik-ramaekers/project-base/blob/8794444ad3f1c44cad11f94efb54f42d55f409a1/src/external/LooplessSizeMove.c#L311
         *          -> https://stackoverflow.com/questions/3102074/win32-my-application-freezes-while-the-user-resizes-the-window/21240384#21240384
         *          -> https://github.com/glfw/glfw/issues/561
         *          -> https://www.google.com/search?q=Win32+Modal+loops+list
         *          -> https://www.mvps.org/user32/modal.html
         *          -> https://github.com/microsoft/Windows-classic-samples
         *          -> https://www.google.com/search?q=Win32+Loopless+Window+Size+%2F+Move+Code+github
         *          -> https://github.com/blender/blender/blob/b513ff9a8f935de394db543405525a3d6f8c8b7d/intern/ghost/intern/GHOST_SystemWin32.cc#L2096
         *          -> https://github.com/JacquesLucke/blender/commit/f652b11ed13b4d9e6705ede9cc990042a2fad4b4
         *          -> https://github.com/search?q=repo%3AJacquesLucke%2Fblender+window+resizing&type=commits&p=7
         *          -> https://learn.microsoft.com/en-us/windows/win32/gdi/about-painting-and-drawing
         *          -> https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-peekmessagea
         *          -> https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-dispatchmessagew
         *          -> https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getqueuestatus
         *          -> https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getqueuestatus
         *          -> https://learn.microsoft.com/en-us/windows/win32/gdi/the-update-region
         *          -> https://learn.microsoft.com/en-us/windows/win32/gdi/wm-paint#example
         *          -> https://learn.microsoft.com/en-us/windows/win32/menurc/wm-syscommandhttps://learn.microsoft.com/en-us/windows/win32/menurc/wm-syscommand
         *          -> https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-entersizemove
         *          -> https://learn.microsoft.com/en-us/windows/win32/winmsg/using-messages-and-message-queues
         *          -> https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-dispatchmessagew
         *          -> https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
         *          -> https://github.com/search?q=VkInstanceCreateFlagBits+language%3AMarkdown&type=code
         *          -> https://www.google.com/search?q=%22VkInstanceCreateFlagBits%22
         * 
         * 
         * 
         * 
         * 
         * 
         * ##UNREAL ENGINE's WndProc implementation
         *          -> https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Runtime/UELibrary/Private/UELibrary.cpp#L131
         *          -> https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Runtime/ApplicationCore/Private/Windows/WindowsApplication.cpp#L935
         *          -> https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Runtime/ApplicationCore/Private/Windows/WindowsApplication.cpp#L947
         *          -> They do call DefWindowProc() for every event
         *          -> https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Runtime/ApplicationCore/Private/Windows/WindowsApplication.cpp#L935
         * 
         *  
         *      DUMMY ProcessEvents: 
         *          https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Developer/StandaloneRenderer/Private/Windows/OpenGL/SlateOpenGLContext.cpp#L11
         *          https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Developer/ShaderFormatOpenGL/Private/OpenGLShaderCompiler.cpp#L107
         *          https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Runtime/OpenGLDrv/Private/Windows/WindowsOpenGLPlatform.cpp#L104
         *          https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Private/DatasmithMaxDirectLinkMaxScript.cpp#L446
         *          
         *      ConsoleSmth
         *          https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Runtime/ApplicationCore/Private/Windows/WindowsConsoleOutputDevice2.cpp#L321
         * 
         *      CrashReport
         *          https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Programs/CrashReportClient/Private/CrashReportAnalyticsSessionSummary.cpp#L172
         *
         *      LogHwndWndProc
         *          https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Runtime/ApplicationCore/Private/Windows/WindowsConsoleOutputDevice2.cpp#L1210
         * 
         *      IDK:-
         *          https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Runtime/ApplicationCore/Private/Windows/WindowsPlatformApplicationMisc.cpp#L113
         *          https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Developer/DesktopPlatform/Private/Windows/WindowsNativeFeedbackContext.cpp#L268
         *          https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Runtime/ApplicationCore/Private/Windows/WindowsApplication.cpp#L2792
         *          https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Runtime/ApplicationCore/Private/Windows/WindowsPlatformSplash.cpp#L584
         *          https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Runtime/Core/Private/Windows/WindowsPlatformMisc.cpp#L4106
         *          https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Private/DatasmithMaxDirectLinkMaxScript.cpp#L451
         *          https://github.com/EpicGames/UnrealEngine/blob/2d53fcab0066b1f16dd956b227720841cad0f6f7/Engine/Source/Programs/UnrealTraceServer/src/SystemTray.cpp#L23
         *          https://github.com/search?q=repo%3AEpicGames%2FUnrealEngine+WndProc&type=code
         *          https://github.com/search?q=repo%3AEpicGames%2FUnrealEngine+PeekMessage&type=code
         *          https://github.com/search?q=repo%3AEpicGames%2FUnrealEngine+DispatchMessage&type=code
         *          https://github.com/search?q=repo%3AEpicGames%2FUnrealEngine+DefWindowProc&type=code
         *          https://github.com/search?q=repo%3AEpicGames%2FUnrealEngine+WM_SYSCOMMAND&type=code
         */
    }
}