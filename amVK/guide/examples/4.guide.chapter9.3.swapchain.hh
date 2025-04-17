#pragma once
#include "amVK_SurfacePresenter.hh"
#include "amVK_Instance.hh"
#include "amVK_Device.hh"
#include "amVK_Image.hh"
#include "amVK_Surface.hh"
#include "amVK_ColorSpace.hh"

/**
 * konf = konfigurieren = configure 💁‍♀️
 */
class amVK_SwapChain  {
    /*
     ,ggg, ,ggg,_,ggg,                                       ,gggg,                                 
    dP""Y8dP""Y88P""Y8b                                    ,88"""Y8b,                   8I          
    Yb, `88'  `88'  `88                                   d8"     `Y8                   8I          
     `"  88    88    88                                  d8'   8b  d8                   8I          
         88    88    88                                 ,8I    "Y88P'                   8I          
         88    88    88    ,ggggg,   ,gggggg,   ,ggg,   I8'            ,ggggg,    ,gggg,8I   ,ggg,  
         88    88    88   dP"  "Y8gggdP""""8I  i8" "8i  d8            dP"  "Y8gggdP"  "Y8I  i8" "8i 
         88    88    88  i8'    ,8I ,8'    8I  I8, ,8I  Y8,          i8'    ,8I i8'    ,8I  I8, ,8I 
         88    88    Y8,,d8,   ,d8',dP     Y8, `YbadP'  `Yba,,_____,,d8,   ,d8',d8,   ,d8b, `YbadP' 
         88    88    `Y8P"Y8888P"  8P      `Y8888P"Y888   `"Y8888888P"Y8888P"  P"Y8888P"`Y8888P"Y888
    */
  public:
    /**
     * USE:- amVK_SurfacePresenter::create_SwapChain_interface()
     */
    amVK_SwapChain(amVK_SurfacePresenter *PR) {
        this->PR = PR;
        this->CI.surface = PR->S->vk_SurfaceKHR;
    }

  public:
    amVK_SurfacePresenter *PR = nullptr;
    VkSwapchainKHR vk_SwapChainKHR = nullptr;
    VkSemaphore    vk_Semaphore = nullptr;

    REY_Array<VkImage>    amVK_1D_SC_IMGs;
    REY_Array<amVK_Image> amVK_1D_SC_IMGs_amVK_WRAP;
        // Will we be able to keep sync of these two different thingies correctly?

    bool called_GetSwapChainImagesKHR = false;
    void        GetSwapChainImagesKHR(void);
    bool called_CreateSwapChainImageViews = false;
    void        CreateSwapChainImageViews(void);

  public:
    void CreateSwapChain(void) {
        VkResult return_code = vkCreateSwapchainKHR(this->PR->D->vk_Device, &CI, nullptr, &this->vk_SwapChainKHR);
        amVK_return_code_log( "vkCreateSwapchainKHR()" );     // above variable "return_code" can't be named smth else
    }

    void CreateSemaPhore(void) {
        VkSemaphoreCreateInfo SP_CI = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0
        };

        VkResult return_code = vkCreateSemaphore(this->PR->D->vk_Device, &SP_CI, nullptr, &this->vk_Semaphore);
        amVK_return_code_log( "vkCreateSemaphore()" );     // above variable "return_code" can't be named smth else
    }

    uint32_t AcquireNextImage(void) {
        uint64_t ns_per_second = 1'000'000'000;
        uint32_t imageIndex = UINT32_MAX;

        if (this->vk_Semaphore == nullptr) {
            this->CreateSemaPhore();
        }

        VkResult return_code = vkAcquireNextImageKHR(this->PR->D->vk_Device, this->vk_SwapChainKHR, 1'000'000'000, vk_Semaphore, nullptr, &imageIndex);
        if (return_code == VK_ERROR_OUT_OF_DATE_KHR) {
            REY_LOG_EX("[VK_ERROR_OUT_OF_DATE_KHR] ----> WIP:- WindowResize()");
        }
        else if (return_code == VK_SUBOPTIMAL_KHR) {
            REY_LOG_EX("[VK_ERROR_OUT_OF_DATE_KHR] ----> WIP:- Figure out what to do");
        }
        else {
            amVK_return_code_log( "vkCreateSemaphore()" ); // above variable "return_code" can't be named smth else
        }

        return imageIndex;
    }
};