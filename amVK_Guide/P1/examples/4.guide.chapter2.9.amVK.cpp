#include "amVK_Instance.hh"

void amVK_InstanceProps::EnumeratePhysicalDevices(void) 
{
    uint32_t deviceCount = 0;     
        // [implicit valid usage]:- must be 0     [if 3rd-param = nullptr]

        vkEnumeratePhysicalDevices(amVK_InstanceProps::s_vk, &deviceCount, nullptr);
            // This function is 'output-ing into' deviceCount

    amVK_GPU_List.n    = deviceCount;
    amVK_GPU_List.data = new VkPhysicalDevice[deviceCount];

        VkResult return_code = vkEnumeratePhysicalDevices(amVK_InstanceProps::s_vk, &amVK_GPU_List.n, amVK_GPU_List.data);
        amVK_return_code_log("vkEnumeratePhysicalDevices()");

    amVK_InstanceProps::called_EnumeratePhysicalDevices = true;
}

/** 
 * i don't wanna scatter all the Properties All around my code. So, i'm gonna keep them here 😊
 *   --> Right inside `amVK_InstanceProps` class
 * 
 * Don't Call before you have called `amVK_InstanceProps::EnumeratePhysicalDevices()`
 * TODO: 
 *   --> Make all the Memory Allocation within this function -> in one block of RAM
 */
void amVK_InstanceProps::GetPhysicalDeviceQueueFamilyProperties(void) {
    amVK_2D_QFAM_PROPs.reserve(amVK_GPU_List.n);
        
        // for each GPU
    for (uint32_t k = 0; k < amVK_GPU_List.n; k++) 
    {
        REY_Array<VkQueueFamilyProperties> *k_QFamProps = &amVK_2D_QFAM_PROPs.data[k];

        uint32_t queueFamilyCount = 0;
            // [implicit valid usage]:- must be 0     [if 3rd-param = nullptr]
            vkGetPhysicalDeviceQueueFamilyProperties(amVK_GPU_List[k], &queueFamilyCount, nullptr);

        k_QFamProps->n = queueFamilyCount;
        k_QFamProps->data = new VkQueueFamilyProperties[queueFamilyCount];
            vkGetPhysicalDeviceQueueFamilyProperties(amVK_GPU_List[k], &k_QFamProps->n, k_QFamProps->data);
    }

    amVK_DONE("vkGetPhysicalDeviceQueueFamilyProperties()" << " 😄");
    amVK_InstanceProps::called_GetPhysicalDeviceQueueFamilyProperties = true;
}







/** 
 * @param p_flagBits:- can be a mixture of multiple bits. use `|` operator a.k.a 'or' operator, which can join flags together
 * @param ID:- Use:- `amVK_InstanceProps::VkPhysicalDevice_2_amVK_Index()` if you wanna pass in `VkPhysicalDevice` 
 * @returns `VkDeviceQCI.queueFamilyIndex` to be used
 */
uint32_t amVK_InstanceProps::ChooseAQueueFamily(VkQueueFlags p_flagBits, amVK_InstanceProps::PD_Index p_ID) {
    uint32_t k = p_ID;
    REY_Array<VkQueueFamilyProperties> GPU_k_QFAM_Array = amVK_2D_QFAM_PROPs[k];

    for (uint32_t i = 0, lim = amVK_2D_QFAM_PROPs[k].n; i < lim; i++) {
        if (amVK_2D_QFAM_PROPs[k][i].queueFlags & p_flagBits) {
            return i;
        }
    }

    return amVK_QueueFamily_NOT_FOUND;
}

amVK_InstanceProps::PD_Index amVK_InstanceProps::VkPhysicalDevice_2_amVK_Index(VkPhysicalDevice PDevice) {
        // for each GPU
    for (uint32_t k = 0; k < amVK_GPU_List.n; k++) {
        if (amVK_GPU_List[k] == PDevice) {
            return k;
        }
    }

    return amVK_PhysicalDevice_NOT_FOUND;
}












// nlohmann - Handles String Stuffs automatically
#include <nlohmann/json.hpp>
// ExportJSON & Other export stuffs below
// https://github.com/REYNEP/amGHOST/blob/3e44b982902a3f3fa4ac584aefb19da3d4cdfcc6/amVK/amVK.cpp