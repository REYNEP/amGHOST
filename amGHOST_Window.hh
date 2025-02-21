#pragma once
#include <stdint.h>  // uint32_t [TODO:- Make our CUSTOM Version of this, cz this thing is kinda heavy]

class amGHOST_Window {
  public:
    uint32_t    m_posX = 0;
    uint32_t    m_posY = 0;
    uint32_t    m_sizeX = 0;
    uint32_t    m_sizeY = 0;
    const wchar_t* m_title = L"amGHOST_WINDOW:- TITLE WASNT SET";

    amGHOST_Window() {};
   ~amGHOST_Window() {};

  public:
    /**
     * Creates a New Window obviously
     * \param title: should be ASCII characters only (as its char*)
     * \param posX: =_= Position in X-axis
     * \param posY: +_+ Position in Y-axis
     * \param sizeX: WIDTH
     * \param sizeY: HEIGHT
     * \param instantShow: Yes, WIN32/X11 does distinguish between creating the window in memory 
     *                     and actually showing the Window on Screen/Monitor. 
     *                     SO WE Give you the choice too.
     * 
     * \todo CAP according to DISPLAY/SCREEN/MONITOR/MULTI_MONITOR resolution
     */
    virtual void create(const wchar_t* title, int posX, int posY, int sizeX, int sizeY, bool instantShow = true) = 0;
    virtual void destroy(void) = 0;
    virtual void show_window(void) = 0;
    virtual void hide_window(void) = 0;
};