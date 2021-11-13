#define amGHOST_WindowWIN32_CPP
#include "amGHOST_Logger.hh"
#include "amGHOST_WindowWIN32.hh"
#include "amGHOST_SystemWIN32.hh" //includes windows.h

amGHOST_WindowWIN32::amGHOST_WindowWIN32(char *title, int posX, int posY, int sizeX, int sizeY) 
  : amGHOST_Window(title, posX, posY, sizeX, sizeY)
{
  amGHOST_SystemWIN32 *s_win32 = (amGHOST_SystemWIN32 *) amGHOST_System::heart;
  HWND hwnd = ::CreateWindowA(
    s_win32->s_wndClassName,        //Name of the WNDCLASS [see protected vars of amGHOST_SystemWIN32]
    this->m_title,                  //Title at the Top bar of the Window
    WS_OVERLAPPEDWINDOW,            //Style of the window, all styles: https://docs.microsoft.com/en-us/windows/win32/winmsg/window-styles
    this->m_posX, this->m_posY,     //Horizontal, Vertical Position of window (top-left corner)
    this->m_sizeX, this->m_sizeY,   //Width, Height of window
    (HWND) NULL,                    //NULL makes the CMD as the parent of this Window, for GUI apps, getDesktopWindow would return the entire Screen as Window
    (HMENU) NULL,                   //The Handle to the Menu, remember that wndcls.lpszMenuName should have the menu Name TOO, or it wont work
    s_win32->s_hInstance,           //Handle to the Instance the window is gonna get be Linked with.... I still don't why both wndclass and hInstance need this
    (LPVOID) NULL                   //using this value as lParam of WndProc, CreatwWindowA Send WM_CREATE message to WndProc 
  );

  if (hwnd == NULL) {
    LOG_DEV("[create_window FAILED]" << " WIN32 CreateWindowA Failed with exit code:- " << GetLastError() << "[HEX:- " << GetLastError() << "]");
    return;
  } 
  else {
    this->m_hwnd = hwnd;
  }
}

bool amGHOST_WindowWIN32::destroyer() {
  return ::DestroyWindow(this->m_hwnd);  //Sends WM_DESTROY Message and Destroyes the Window
}

void amGHOST_WindowWIN32::show_window(void) {
  ::ShowWindow(this->m_hwnd, SW_SHOW);
  ::SetFocus(this->m_hwnd);
}
void amGHOST_WindowWIN32::hide_window(void) {
  ::ShowWindow(this->m_hwnd, SW_HIDE);
}




/***********************************************************
----------- OpenGL Creation Functios Below [WGL] -----------
***********************************************************/
#ifdef amGHOST_BUILD_OPENGL
  #include "amGHOST_ContextWGL.hh"  //has GLEW.h needed in openGL_clear() + basically all openGL Functions including openGL_create_context()
#endif

amGHOST_Context* amGHOST_WindowWIN32::opengl_create_context(void) {
#ifdef amGHOST_BUILD_OPENGL

  HWND hwnd = this->m_hwnd;
  HDC hdc = ::GetDC(hwnd);
  HGLRC hglrc = NULL;
  if (hwnd == NULL || hdc == NULL) {return NULL;}
  
  amGHOST_ContextWGL *C = new amGHOST_ContextWGL(hwnd, hdc, hglrc);
  this->m_render_context = (amGHOST_Context *) C;
  C->opengl_clear();
  return (amGHOST_Context*) C;

#else
  LOG("amGHOST_OPENGL macro Not defined [WARNING: Note that If you define Multiple Context Macros like amGHOST_BUILD_VULKAN and amGHOST_OPENGL, your Application can get heavy!!!!]");
  return (amGHOST_Context *) NULL;
#endif  //amGHOST_OPENGL
}


/*****************************************************
----------- VULKAN Creation Function Below -----------
*****************************************************/
#if defined(amGHOST_BUILD_VULKAN) // || defined(amGHOST_VULKAN)   [Internally only amGHOST_BUILD_VULKAN needed]

VkSurfaceKHR amGHOST_WindowWIN32::create_vulkan_surface(VkInstance instance) {
  //--------- Well, this turned Out to be SHORT, Have Fun ---------
  VkWin32SurfaceCreateInfoKHR createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  createInfo.hwnd = this->m_hwnd;
  createInfo.hinstance = ((amGHOST_SystemWIN32 *)(amGHOST_System::heart))->s_hInstance;
  //Don't Need CreateDevice to do this obviously, Thus Not everything in vulkan_load is not needed to actually create a Vulkan Window Context or rather VK-SURFACE 
  VkSurfaceKHR surface;
  VkResult res = vkCreateWin32SurfaceKHR(instance, &createInfo, nullptr, &surface);

  if (res != VK_SUCCESS) {LOG_DEV(res << "Thats the output that vkCreateWin32SurfaceKHR() gave me...."); return nullptr;}
  return surface;
}

#endif  //amGHOST_BUILD_VULKAN


/**********************************************
--------- RenderContext Related Funcs ---------
**********************************************/
void amGHOST_WindowWIN32::activate_context() {
  if (this->m_render_context != NULL) {
    this->m_render_context->activate_context();
  }
  else {
    LOG("No Rendering Context Was Created for This Window. Please Create one.. See amGHOST_Window.hh for Rendering Context Options lke Vulkan/Opengl");
  }
}