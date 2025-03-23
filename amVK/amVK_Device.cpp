#include "amVK_Device.hh"

amVK_Device::amVK_Device(VkPhysicalDevice PD) 
{
    amVK_Props::PD_Index index = amVK_Props::VkPhysicalDevice_2_amVK_Index(PD);
    if (index == amVK_PhysicalDevice_NOT_FOUND) {
        REY_LOG("Can't find VkPhysicalDevice:- " << PD)
    }
    else {
        m_PD_index = index;
        m_physicalDevice = amVK_Props::s_HardwareGPU_List[index];
    }
}