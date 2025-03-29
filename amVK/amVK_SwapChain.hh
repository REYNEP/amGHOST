#pragma once
#include "amVK.hh"
#include "amVK_Device.hh"

class amVK_SwapChain  {
  public:
    VkSwapchainCreateInfoKHR CI = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0,
        .surface = nullptr,
        .queueFamilyIndexCount = 0,
        .pQueueFamilyIndices = nullptr,
    };

  public:
    amVK_SwapChain(VkSurfaceKHR S, amVK_Device *paramD) {
        CI.surface = S;
        D = paramD;
    }

  public:
    amVK_Device *D = nullptr;
    VkSwapchainKHR SC = nullptr;

  public:
    void createSwapChain(void) {
        VkResult return_code = vkCreateSwapchainKHR(this->D->m_device, &CI, nullptr, &this->SC);
        amVK_return_code_log( "vkCreateSwapchainKHR()" );     // above variable "return_code" can't be named smth else
    }
};