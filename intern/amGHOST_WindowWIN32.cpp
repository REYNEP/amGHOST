#pragma region PURE_VIRTUAL
/*
                    Convert To ASCII Art:- `bitbelt.converttoasciiart` -> REYNEP's_Journal\21.mar22_ASCII_ART.md

    .______    __    __  .______       _______       ____    ____  __  .______     .___________. __    __       ___       __      
    |   _  \  |  |  |  | |   _  \     |   ____|      \   \  /   / |  | |   _  \    |           ||  |  |  |     /   \     |  |     
    |  |_)  | |  |  |  | |  |_)  |    |  |__          \   \/   /  |  | |  |_)  |   `---|  |----`|  |  |  |    /  ^  \    |  |     
    |   ___/  |  |  |  | |      /     |   __|          \      /   |  | |      /        |  |     |  |  |  |   /  /_\  \   |  |     
    |  |      |  `--'  | |  |\  \----.|  |____          \    /    |  | |  |\  \----.   |  |     |  `--'  |  /  _____  \  |  `----.
    | _|       \______/  | _| `._____||_______|          \__/     |__| | _| `._____|   |__|      \______/  /__/     \__\ |_______|
                                                                                                                              
*/

#include "amGHOST_WindowWIN32.hh"
#include "amGHOST_VkSurfaceKHR_WIN32.hh"
amGHOST_VkSurfaceKHR* amGHOST_WindowWIN32::init_VkSurface_interface(void) {
    if (this->m_amGHOST_VkSurface != nullptr) {
        REY_LOG_EX("[amGHOST_WindowWIN32::init_VkSurface_interface]:- A m_amGHOST_VkSurface Already Exists.");
    }
    else {
        amGHOST_VkSurfaceKHR_WIN32 *REY = new amGHOST_VkSurfaceKHR_WIN32(this);
        this->m_amGHOST_VkSurface = REY;
    }
    
    return this->m_amGHOST_VkSurface;
}


    /** 
     * 1. `this->m_VkSurface->destroy();`
     * 2. Sends WM_DESTROY Message
     * 3. Destroys the Window
     */
void amGHOST_WindowWIN32::destroy(void)   
{
    if (this->m_amGHOST_VkSurface->m_S != nullptr) {
        this->m_amGHOST_VkSurface->destroy();
    }

    if (!::DestroyWindow(this->m_hwnd)) {
        /** Fails if:
             a) Window not valid
            b) Called from wrong thread
            c) Window already destroyed */
        amG_FAILED1("::DestroyWindow()");
        REY_LOG_status("Could Not Destroy: amGHOST_WindowWIN32.m_hwnd --> " << "[" << (uint64_t)m_hwnd << "]")
    }
        amG_PASSED1("::DestroyWindow()");
        REY_LOG_status("Destroyed:- amGHOST_WindowWIN32.m_hwnd --> " << "[" << (uint64_t)m_hwnd << "]");

    this->m_hwnd = nullptr;
}
#pragma endregion









#pragma region default_EK
#include "amGHOST_logWIN32.hh"
void amGHOST_WindowWIN32::internal_update_window_and_client_area_sizes(void) {
    // ------------------------- Client / Render Area ----------------------------
        // This is what is reported inside WndProc() 😅
        RECT rect;
        if (::GetClientRect(this->m_hwnd, &rect)) {
            this->m_clientSizeX = rect.right - rect.left;
            this->m_clientSizeY = rect.bottom - rect.top;
            REY_LOG("[REY_EK] GetClientRect: " << this->m_clientSizeX << "x" << this->m_clientSizeY);
        } else {
            amG_FAILED("::GetClientRect(this->m_hwnd, &rect)");
        }
    // ------------------------- Client / Render Area ----------------------------

    // ------------------------- Window Area with MENUs ----------------------------
        // This is what we save inside amGHOST_Window::m_sizeX m_sizeY 💁‍♀️
        if (::GetWindowRect(this->m_hwnd, &rect)) {
            this->m_oldSizeX = this->m_sizeX;
            this->m_oldSizeY = this->m_sizeY;
            this->m_sizeX = rect.right - rect.left;
            this->m_sizeY = rect.bottom - rect.top;
            REY_LOG("[REY_EK] GetWindowRect: " << this->m_sizeX << "x" << this->m_sizeY);
        } else {
            amG_FAILED("::GetWindowRect(this->m_hwnd, &rect)");
        }
    // ------------------------- Window Area with MENUs ----------------------------
}

/*
 _______   _______  _______    ___      __    __   __      .___________.             _______  __  ___ 
|       \ |   ____||   ____|  /   \    |  |  |  | |  |     |           |            |   ____||  |/  / 
|  .--.  ||  |__   |  |__    /  ^  \   |  |  |  | |  |     `---|  |----`            |  |__   |  '  /  
|  |  |  ||   __|  |   __|  /  /_\  \  |  |  |  | |  |         |  |                 |   __|  |    <   
|  '--'  ||  |____ |  |    /  _____  \ |  `--'  | |  `----.    |  |                 |  |____ |  .  \  
|_______/ |_______||__|   /__/     \__\ \______/  |_______|    |__|     ______ _____|_______||__|\__\ 
                                                                       |______|______|                
*/
void amGHOST_WindowWIN32::call_default_eventKonsument(amGHOST_Event lightweight_event) {
    if (lightweight_event.m_Type == amGE::Type::WindowResize) {
        this->internal_update_window_and_client_area_sizes();
    }
}
#pragma endregion