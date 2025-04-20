#include "amGHOST_WindowWIN32.hh"
#include "amGHOST_VkSurfaceKHR_WIN32.hh"

// Convert To ASCII Art:- `bitbelt.converttoasciiart` -> REYNEP's_Journal\21.mar22_ASCII_ART.md
/**                                                                              
        //   ) )                           ||   / /                                         
       //___/ /           __      ___      ||  / / ( )  __    __  ___           ___     //  
      / ____ / //   / / //  ) ) //___) )   || / / / / //  ) )  / /   //   / / //   ) ) //   
     //       //   / / //      //          ||/ / / / //       / /   //   / / //   / / //    
    //       ((___( ( //      ((____       |  / / / //       / /   ((___( ( ((___( ( //     
    
*/
/** PureVirtual Funcs from amGHOST_System  */
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
