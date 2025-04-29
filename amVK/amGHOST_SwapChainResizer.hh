#pragma once

#include "amVK_RenderPassFBs.hh"
#include "amGHOST_Window.hh"
#include "REY_Logger.hh"

class amGHOST_SwapChainResizer {
  public:
    amGHOST_SwapChainResizer(amVK_RenderPassFBs* RP_FBs, amGHOST_Window* amGW) : EK(this) {
        this->SC      = RP_FBs->SC_IMGs->SC;
        this->SC_IMGs = RP_FBs->SC_IMGs;
        this->RP_FBs  = RP_FBs;
        this->amGW    = amGW;
        this->amGW->replace_eventKonsument(reinterpret_cast<amGHOST_EK* >(&(this->EK)), true);
    }
   ~amGHOST_SwapChainResizer(void) {}

    amVK_SwapChain*     SC          = nullptr;
    amVK_SwapChainIMGs* SC_IMGs     = nullptr;
    amVK_RenderPassFBs* RP_FBs      = nullptr;
    amGHOST_Window*     amGW        = nullptr;
    bool                isResizing  = false;
    bool               canResizeNow = true;

  public:
    void reSize(void) {
        while(canResizeNow == false) {
            REY_NoobTimer::wait(5);     // wait 5ms ==> 200fps
            REY_LOG("Waiting because:- canResizeNow == false")
        }

        isResizing = true;              // For Other Threads
         RP_FBs->DestroyFrameBuffers();
        SC_IMGs->DestroySwapChainImageViews();

        SC->reCreateSwapChain();        // calls --> sync_SurfCaps();

        SC_IMGs->GetSwapChainImagesKHR();
        SC_IMGs->CreateSwapChainImageViews();
         RP_FBs->CreateFrameBuffers();
        isResizing = false;             // For Other Threads
    }

    class EKClass : amGHOST_EK {
      public:
        EKClass(amGHOST_SwapChainResizer* Resizer) : amGHOST_EK(Resizer) {}
       ~EKClass() {}

        using amGHOST_EK::m_userData;

        int processEvent(amGHOST_Event lightweight_event) {
            amGHOST_SwapChainResizer* Resizer = reinterpret_cast<amGHOST_SwapChainResizer*>(m_userData);
            if (lightweight_event.m_Type == amE::Type::WindowResize) {
                Resizer->reSize();
            }
            return 0;
        }
    } EK;
};