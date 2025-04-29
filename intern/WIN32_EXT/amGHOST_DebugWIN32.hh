/** @GITHUB:- https://github.com/moyamejiasr/Win32GUI/blob/c7bf6f24f2d4a66456c701017005e58f75a57c3c/Win32/Debug.h#L206 */
/** Some Events were Missing in the spy.h     But I wanna be sure if some events are missing here */
/** More Promising One:- https://github.com/elishacloud/dxwrapper/blob/a93f68b9b325f50e67136456f125232cd408ff9b/Logging/Logging.cpp#L1419 */
/** Probably found a copy of this file:- https://github.com/D4koon/WhatsappTray/blob/accfba3c5fc2470408906a25b4ae2eb3e2d0ae57/WhatsappTray/WindowsMessage.h#L166 */
/** https://gitlab.winehq.org/wine/wine/-/wikis/Wine-Developer's-Guide/List-of-Windows-Messages */
/** Another One:- https://github.com/clowd/Clowd/blob/a0ea74b2a1bbeaa4c611feef59c6cb857649f3fc/src/Clowd.Native/winmsg.cpp#L197 */
/** Another one:- https://github.com/shadeMe/Construction-Set-Extender/blob/8b87eb068f69ba3b9b138a56d000e1f0d68bf37b/%5BBGSEEBase%5D/UICommon.cpp#L209 */
/** https://github.com/Ilyaki/ProtoInput/blob/dd29bf8d22349605d0e1950c1c5dc4893d72670e/src/ProtoInput/ProtoInputHooks/MessageList.cpp#L152 */
/** https://github.com/nihilus/idaplugs/blob/d68bb14e5cf2a2dc42bd26d5553a3f2f9dff524e/csc/plugsys.cpp#L982 */
/** https://github.com/XZiar/RayRenderer/blob/2d134e2d01685deba6864f30b4d10656ffe113bc/WindowHost/Win32MsgName.hpp#L152 */
/** Search Term:- "SBM_GETSCROLLBARINFO" language:C++ */

#include "spy.h"
#include "Win32GUI.Debug.h"



static std::map<int, const char*> REY_wmTranslation = {
    {799, "WM_DWMNCRENDERINGCHANGED" },
    {257, "WM_KEYUP"},
    {49387, "[49387] Gotta Hunt Down the App that's sending this event 🤔"},
    {49364, "[49364] Gotta Hunt Down the App that's sending this event 🤔"},
    {96, "[96] win32 Internal ::DispatchMessage() event 🤔"},
    {802, "[802] win32 Internal ::DispatchMessage() event 🤔"}
};

const char* REY_get_REY_text(UINT msg) {
    auto it = REY_wmTranslation.find(msg); // Use find to avoid modifying the map
    if (it != REY_wmTranslation.end()) {
        return it->second;
    } 
    else if ((msg > 49000) && (msg < 49999)) {
        return "[49xxx] Gotta Hunt Down the App that's sending this event 🤔";
    } 
    else {
        return "UNKNOWN_MESSAGE";
    }
}


const char* REY_get_Win32GUI_text(UINT msg) {
    auto it = wmTranslation.find(msg); // Use find to avoid modifying the map
    if (it != wmTranslation.end()) {
        return it->second;
    } else {
        return "UNKNOWN_MESSAGE";
    }
}



#include "REY_Logger.hh"
#include "REY_Array.hh"
#include <cstring>
#include <iomanip>
#include <iostream>

#define REY_LOG_win32_inputEvent REY_LOG_win32_message

void REY_LOG_win32_message(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    const char* Win32GUI_text = REY_get_Win32GUI_text(msg);
    const char*      spy_text = spy_get_message_name(msg);
    const char*      REY_text = REY_get_REY_text(msg);

    if (strcmp(Win32GUI_text, spy_text) != 0) {
        REY_LOG("  [STRCMP] Win32GUI_text != spy_text 💁‍♀️");
        REY_LOG("     [spy]:- " << "[" << msg << "]" << " " << spy_text);
        REY_LOG("[Win32GUI]:- " << "[" << msg << "]" << " " << Win32GUI_text);
    }
    else if (strcmp(Win32GUI_text, "UNKNOWN_MESSAGE") == 0) {
         if      (strcmp(spy_text, "UNKNOWN_MESSAGE") == 0) {
            if   (strcmp(REY_text, "UNKNOWN_MESSAGE") == 0) {
                REY_LOG_EX("Found an entirely UNKNOWN_MESSAGE:- " << msg);
            }
            else {
                REY_LOG("[REY]:- " << REY_text);
            }
        }
    }
    else {
        const int TEXT_FIELD_WIDTH = 20;  // Adjust based on your longest expected text

        std::cout << "[Win32GUI]:- " << std::left << std::setw(TEXT_FIELD_WIDTH)
                    << Win32GUI_text
                    << std::hex << " [hwnd: "  << std::showbase << reinterpret_cast<uintptr_t>(hwnd) << "]"
                    << std::hex << " [wParam: "  << std::left << std::setw(10) << wParam << "]"
                    << std::dec << " [lParam: "  << std::left << std::setw(14) << lParam << "]" << "\n";
    }
}

void REY_GET_win32_message2(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    const int TEXT_FIELD_WIDTH = 20;  // Adjust based on your longest expected text

    std::cout << "[Win32GUI]:- " << std::left << std::setw(TEXT_FIELD_WIDTH)
                << REY_get_Win32GUI_text(msg)
                << std::hex << " [hwnd: "  << std::showbase << reinterpret_cast<uintptr_t>(hwnd) << "]"
                << std::hex << " [wParam: "  << std::left << std::setw(10) << wParam << "]"
                << std::dec << " [lParam: "  << std::left << std::setw(14) << lParam << "]";
}




#include <windows.h>
#include <stdio.h>

void PrintWindowStyles(HWND hwnd) {
    // Get standard and extended styles
    LONG styles = GetWindowLongPtr(hwnd, GWL_STYLE);
    LONG ex_styles = GetWindowLongPtr(hwnd, GWL_EXSTYLE);

    printf("Standard Styles (GWL_STYLE):\n");
    printf("WS_BORDER: %d\n", (styles & WS_BORDER) ? 1 : 0);
    printf("WS_CAPTION: %d\n", (styles & WS_CAPTION) ? 1 : 0);
    printf("WS_CHILD: %d\n", (styles & WS_CHILD) ? 1 : 0);
    printf("WS_MAXIMIZEBOX: %d\n", (styles & WS_MAXIMIZEBOX) ? 1 : 0);
    printf("WS_MINIMIZEBOX: %d\n", (styles & WS_MINIMIZEBOX) ? 1 : 0);
    printf("WS_OVERLAPPED: %d\n", (styles & WS_OVERLAPPED) ? 1 : 0);
    printf("WS_SYSMENU: %d\n", (styles & WS_SYSMENU) ? 1 : 0);
    printf("WS_VISIBLE: %d\n", (styles & WS_VISIBLE) ? 1 : 0);

    printf("\nExtended Styles (GWL_EXSTYLE):\n");
    printf("WS_EX_ACCEPTFILES: %d\n", (ex_styles & WS_EX_ACCEPTFILES) ? 1 : 0);
    printf("WS_EX_CLIENTEDGE: %d\n", (ex_styles & WS_EX_CLIENTEDGE) ? 1 : 0);
    printf("WS_EX_TOPMOST: %d\n", (ex_styles & WS_EX_TOPMOST) ? 1 : 0);
    printf("WS_EX_TRANSPARENT: %d\n", (ex_styles & WS_EX_TRANSPARENT) ? 1 : 0);
}