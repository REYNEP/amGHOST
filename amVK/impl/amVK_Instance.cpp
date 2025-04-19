#include "amVK_Instance.hh"

    // [1 Per VkInstance]:- All of these options should basically be set by the one who is gonna use amVK and create an APP/Software 🤷‍♀️
VkApplicationInfo amVK_Instance::AppInfo = {
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pNext = nullptr,
    .pApplicationName = "amVK_ApplicationInfo.pApplicationName not given",
        // [implicit valid usage]:- must not be NULL
    .applicationVersion = VK_MAKE_API_VERSION(0, 0, 0, 0),
    .pEngineName = "amVK_ApplicationInfo.pEngineName not given",
        // [implicit valid usage]:- must not be NULL
    .engineVersion = VK_MAKE_API_VERSION(0, 0, 0, 0),
    .apiVersion = VK_API_VERSION_1_0
        // version of the Vulkan API against which the application expects to run on
};

VkInstanceCreateInfo amVK_Instance::CI = {
    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        // [implicit valid usage]:- must     be <above_value>
    .pNext = nullptr,
        // [implicit valid usage]:- must     be NULL
    .flags = 0,
        // [implicit valid usage]:- must     be 0
    .pApplicationInfo = &AppInfo,
    .enabledLayerCount = 0,
    .ppEnabledLayerNames = nullptr,
    .enabledExtensionCount = 0,
    .ppEnabledExtensionNames = nullptr
};


#include "amVK/common/amVK_log.hh"
#include "amVK_InstanceProps.hh"

void amVK_Instance::CreateInstance(void)
{
    if (vk_Instance) {
        REY_LOG_EX("[amVK_Instance::CreateInstance]:- A amVK System Already Exists, Please Destroy it before you can create another System.");
        return;
    }

    VkResult return_code = vkCreateInstance(&CI, nullptr, &vk_Instance);
    amVK_return_code_log( "vkCreateInstance()" );  // above variable "return_code" can't be named smth else

    amVK_InstanceProps::log_1D_InstanceEXTs_Enabled(return_code);
}