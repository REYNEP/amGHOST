#pragma once
#include "amVK_RenderPassFBs.hh"

class amVK_RenderPassCMDs {
  public:
    amVK_RenderPass*         RP = nullptr;
    amVK_SwapChain*          SC = nullptr;
    amVK_SwapChainIMGs* SC_IMGs = nullptr;
    amVK_RenderPassFBs* RP_FBs  = nullptr;
    VkCommandBuffer     CMDBUF  = nullptr;
    void change_CMDBUF(VkCommandBuffer CMDBUF)     { this->CMDBUF = CMDBUF; }

  public:
    amVK_RenderPassCMDs(amVK_RenderPassFBs *RP_FBs, VkCommandBuffer CMDBUF) {
        this->RP_FBs  = RP_FBs;
        this->SC_IMGs = RP_FBs->SC_IMGs;
        this->RP      = RP_FBs->RP;
        this->SC      = RP_FBs->SC_IMGs->SC;
        this->CMDBUF  = CMDBUF;
    }
   ~amVK_RenderPassCMDs() {}

  public:
    void RPBI_AcquireNextFrameBuffer(void);
    void RPBI_SyncSurfCaps(void);

  public:
    void CMDBeginRenderPass(void);
    void   CMDEndRenderPass(void);
    void CMDSetViewport_n_Scissor(void);
};