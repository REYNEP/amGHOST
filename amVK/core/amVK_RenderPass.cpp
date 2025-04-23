#include "amVK_RenderPass.hh"

void amVK_RenderPass::sync_Attachments(void) {
    CI.attachmentCount = AttachmentInfos.neXt;
    CI.pAttachments = AttachmentInfos.data;
}
void amVK_RenderPass::sync_Subpasses(void) {
    CI.subpassCount = SubpassInfos.neXt;
    CI.pSubpasses = SubpassInfos.data;
}
void amVK_RenderPass::sync_Dependencies(void) {
    CI.dependencyCount = Dependencies.neXt;
    CI.pDependencies = Dependencies.data;
}
void amVK_RenderPass::sync_Attachments_Subpasses_Dependencies(void) {
        sync_Attachments();
        sync_Subpasses();
        sync_Dependencies();
}

void        amVK_RenderPass::CreateRenderPass(void) {
    VkResult return_code = vkCreateRenderPass(D->vk_Device, &CI, nullptr, &vk_RenderPass);
    amVK_return_code_log( "vkCreateRenderPass()" );     // above variable "return_code" can't be named smth else
}
void amVK_RenderPass::DestroyRenderPass(void) {
    vkDestroyRenderPass(D->vk_Device, vk_RenderPass, nullptr);
}


















/*

              __      ___  __         _____  _____  ______                        ____         __  __              
              \ \    / / |/ /        |  __ \|  __ \|  ____|                      |  _ \       / _|/ _|             
   __ _ _ __ __\ \  / /| ' /         | |__) | |__) | |__ _ __ __ _ _ __ ___   ___| |_) |_   _| |_| |_ ___ _ __ ___ 
  / _` | '_ ` _ \ \/ / |  <          |  _  /|  ___/|  __| '__/ _` | '_ ` _ \ / _ \  _ <| | | |  _|  _/ _ \ '__/ __|
 | (_| | | | | | \  /  | . \         | | \ \| |    | |  | | | (_| | | | | | |  __/ |_) | |_| | | | ||  __/ |  \__ \
  \__,_|_| |_| |_|\/   |_|\_\        |_|  \_\_|    |_|  |_|  \__,_|_| |_| |_|\___|____/ \__,_|_| |_| \___|_|  |___/
                          ______ ______                                                                            
                         |______|______|                                                                           

 */
#include "amVK_RenderPassFBs.hh"
void amVK_RenderPassFBs::CreateFrameBuffers(void) {
    if (this->SC_IMGs->called_GetSwapChainImagesKHR == false) {
        this->SC_IMGs->       GetSwapChainImagesKHR();
    }
    if (this->SC_IMGs->called_CreateSwapChainImageViews == false) {
        this->SC_IMGs->       CreateSwapChainImageViews();
    }

        RPBI.renderArea.extent = this->SC_IMGs->SC->active_ImageExtent();
        Scissor.extent         = RPBI.renderArea.extent;
        Viewport.width         = Scissor.extent.width;
        Viewport.height        = Scissor.extent.height;
        this->CI.width         = Scissor.extent.width;
        this->CI.height        = Scissor.extent.height;
        this->CI.renderPass    = this->RP->vk_RenderPass;

    this->amVK_1D_RP_FBs.reserve(this->SC_IMGs->amVK_1D_SC_IMGs.n);

    REY_Array_LOOP(this->amVK_1D_RP_FBs, k) {
        this->CI.attachmentCount = 1;
        this->CI.pAttachments = &(this->SC_IMGs->amVK_1D_SC_IMGViews[k]);

            VkResult return_code = vkCreateFramebuffer(this->RP->D->vk_Device, &CI, nullptr, &this->amVK_1D_RP_FBs[k]);
            amVK_return_code_log( "vkCreateFramebuffer()" );     // above variable "return_code" can't be named smth else
    }
}
void amVK_RenderPassFBs::DestroyFrameBuffers(void) {
    REY_Array_LOOP(this->amVK_1D_RP_FBs, k) {
        vkDestroyFramebuffer(this->RP->D->vk_Device, this->amVK_1D_RP_FBs[k], nullptr);
    }
}











/*

  _______ .______    __    __         ______   ______   .___  ___. .___  ___.      ___      .__   __.  _______  
 /  _____||   _  \  |  |  |  |       /      | /  __  \  |   \/   | |   \/   |     /   \     |  \ |  | |       \ 
|  |  __  |  |_)  | |  |  |  |      |  ,----'|  |  |  | |  \  /  | |  \  /  |    /  ^  \    |   \|  | |  .--.  |
|  | |_ | |   ___/  |  |  |  |      |  |     |  |  |  | |  |\/|  | |  |\/|  |   /  /_\  \   |  . `  | |  |  |  |
|  |__| | |  |      |  `--'  |      |  `----.|  `--'  | |  |  |  | |  |  |  |  /  _____  \  |  |\   | |  '--'  |
 \______| | _|       \______/   _____\______| \______/  |__|  |__| |__|  |__| /__/     \__\ |__| \__| |_______/ 
                               |______|                                                                         
 
 */
#include "amVK_RenderPassFBs.hh"
void amVK_RenderPassFBs::RPBI_AcquireNextFrameBuffer(void) {
    uint32_t nextImageIndex         = this->SC_IMGs->AcquireNextImage();
             RPBI.framebuffer       = this->amVK_1D_RP_FBs[nextImageIndex];
}
void  amVK_RenderPassFBs::CMDBeginRenderPass(VkCommandBuffer CMDBUF) {
                        vkCmdBeginRenderPass(CMDBUF, &RPBI, VK_SUBPASS_CONTENTS_INLINE);
               REY_LOG("vkCmdBeginRenderPass()");
}
void  amVK_RenderPassFBs::CMDEndRenderPass(VkCommandBuffer CMDBUF) {
                        vkCmdEndRenderPass(CMDBUF);
               REY_LOG("vkCmdEndRenderPass()");
}
void amVK_RenderPassFBs::CMDSetViewport_n_Scissor(VkCommandBuffer CMDBUF) {
             vkCmdSetViewport(CMDBUF, 0, 1, &Viewport);
    REY_LOG("vkCmdSetViewport()");
             vkCmdSetScissor (CMDBUF, 0, 1, &Scissor);
    REY_LOG("vkCmdSetScissor()");
}