#pragma once
#include "amVK_CommandPool.hh"

/**
 * As per QueueFamily
 * When you Create VkDevice, you already define How many Queues/QueueFamilities you are gonna use
 * 
 *  This is a CommandPool Manager based on the #QueueFamilies on a GPU/PhysicalDevice
 */
class amVK_CommandPoolMAN {
  public:
    amVK_CommandPoolMAN(amVK_Device *D);
   ~amVK_CommandPoolMAN(void) {}

  public:
    amVK_Device *D = nullptr;
    REY_Array<amVK_CommandPool *> amVK_1D_QFAMs_CMDPOOL;    // 1 CMDPOOL per QFam

  public:
    amVK_CommandPool* InitializeCommandPool(uint32_t queueFamilyIndex);
};