#include "amGHOST_System.hh"
#include "REY_Logger.hh"

#if defined(amGHOST_BUILD_WIN32) || defined(_WIN32)
    #include "amGHOST_SystemWIN32.hh"
#elif defined(amGHOST_BUILD_X11)
    #include "amGHOST_SystemX11.hh"
#elif defined(amGHOST_BUILD_XCB) || defined(__unix__)
    #include "amGHOST_SystemXCB.hh"
#endif

void amGHOST_System::create_system(void) {
    if (heart) {
        REY_LOG_EX("[amGHOST_System::create_system]:- A GHOST System Already Exists, Please Destroy it before you can create Another System.");
        return;
    }

    #if defined(amGHOST_BUILD_WIN32) || defined(_WIN32)
        heart = (amGHOST_System *) new amGHOST_SystemWIN32();
    #elif defined(amGHOST_BUILD_X11)
        heart = (amGHOST_System *) new amGHOST_SystemX11();
    #elif defined(amGHOST_BUILD_XCB) || defined(__unix__)
        heart = (amGHOST_System *) new amGHOST_SystemXCB();
    #endif
}

amGHOST_System* amGHOST_System::get_system(void) {
    if (!heart) {
        REY_LOG_EX("[amGHOST_System::create_system]:- NO GHOST System Exists, Please Create One Before you can Get one, Returning NULL back");
        return nullptr;
    }
    return heart;
}