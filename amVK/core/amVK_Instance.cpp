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

#include "amVK/utils/amVK_log.hh"
void amVK_Instance::CreateInstance(void)
{
    if (vk_Instance) {
        REY_LOG_EX("[amVK_Instance::CreateInstance]:- A amVK System Already Exists, Please Destroy it before you can create another System.");
        return;
    }

    VkResult return_code = vkCreateInstance(&CI, nullptr, &vk_Instance);
    amVK_return_code_log( "vkCreateInstance()" );  // above variable "return_code" can't be named smth else

    amVK_Instance::log_1D_Instance_EXTs_Enabled(return_code);
    amVK_Instance::log_1D_Instance_Layers_Enabled(return_code);
}

#include "REY_STDWrap.hh"
#include "amVK_InstancePropsEXT.hh"
#include "amVK/utils/amVK_log.hh"
void amVK_Instance::addTo_1D_Instance_EXTs_Enabled(const char* extName) {
    // VK_KHR_surface
    if (!amVK_InstanceProps::called_EnumerateInstanceExtensions) {
                amVK_InstanceProps::EnumerateInstanceExtensions();
    }
    
    if (amVK_InstanceProps::isInstanceEXTAvailable(extName)) {
        char  *dont_lose = REY_strcpy(extName);

        REY_ArrayDYN_PUSH_BACK(amVK_1D_Instance_EXTs_Enabled) = dont_lose;

        amVK_Instance::CI.enabledExtensionCount   = amVK_1D_Instance_EXTs_Enabled.neXt;
        amVK_Instance::CI.ppEnabledExtensionNames = amVK_1D_Instance_EXTs_Enabled.data;
    }
    else {
        REY_LOG_notfound("Vulkan Instance Extension:- " << extName);
    }
}
void amVK_Instance::log_1D_Instance_EXTs_Enabled(VkResult ret) {
    if (ret != VK_SUCCESS) {
        REY_LOG_status("vkCreateInstance() failed 😶‍🌫️");
    }
    else {
        REY_LOG_status("         Enabled VULKAN Extensions' Name:- ");
        REY_Array_LOOP(amVK_1D_Instance_EXTs_Enabled, k) {
            REY_LOG_status("              | " << amVK_1D_Instance_EXTs_Enabled[k]);
        }
    }
}
void amVK_Instance::addTo_1D_Instance_Layers_Enabled(const char* layerName) {
    if (!amVK_InstanceProps::called_EnumerateInstanceLayerProperties) {
                amVK_InstanceProps::EnumerateInstanceLayerProperties();
    }
    
    if (amVK_InstanceProps::isInstanceLayerAvailable(layerName)) {
        char  *dont_lose = REY_strcpy(layerName);

        REY_ArrayDYN_PUSH_BACK(amVK_1D_Instance_Layers_Enabled) = dont_lose;

        amVK_Instance::CI.enabledLayerCount   = amVK_1D_Instance_Layers_Enabled.neXt;
        amVK_Instance::CI.ppEnabledLayerNames = amVK_1D_Instance_Layers_Enabled.data;
    }
    else {
        REY_LOG_notfound("Vulkan Instance Extension:- " << layerName);
    }
}
void amVK_Instance::log_1D_Instance_Layers_Enabled(VkResult ret) {
    if (ret != VK_SUCCESS) {
        REY_LOG_status("vkCreateInstance() failed 😶‍🌫️");
    }
    else {
        REY_LOG_status("         Enabled VULKAN Extensions' Name:- ");
        REY_Array_LOOP(amVK_1D_Instance_Layers_Enabled, k) {
            REY_LOG_status("              | " << amVK_1D_Instance_Layers_Enabled[k]);
        }
    }
}




















/**


 ,ggggggggggg,                                           ,ggggggg,  ,ggg,          ,gg,ggggggggggggggg
dP"""88""""""Y8,                                       ,dP""""""Y8bdP"""Y8,      ,dP'dP""""""88"""""""
Yb,  88      `8b                                       d8'    a  Y8Yb,_  "8b,   d8"  Yb,_    88       
 `"  88      ,8P                                       88     "Y8P' `""    Y8,,8P'    `""    88       
     88aaaad8P"                                        `8baaaa              Y88"             88       
     88""""",gggggg,    ,ggggg,   gg,gggg,      ,g,   ,d8P""""             ,888b             88       
     88     dP""""8I   dP"  "Y8gggI8P"  "Yb    ,8'8,  d8"                 d8" "8b,           88       
     88    ,8'    8I  i8'    ,8I  I8'    ,8i  ,8'  Yb Y8,               ,8P'    Y8,    gg,   88       
     88   ,dP     Y8,,d8,   ,d8' ,I8 _  ,d8' ,8'_   8)`Yba,,_____,     d8"       "Yb,   "Yb,,8P       
     88   8P      `Y8P"Y8888P"   PI8 YY88888PP' "YY8P8P `"Y8888888   ,8P'          "Y8    "Y8P'       
                                  I8                                                                  
                                  I8                                                                  
                                  I8                                                                  
                                  I8                                                                  
                                  I8                                                                  
                                  I8                                                                  


 */
#include "amVK_InstancePropsEXT.hh"

#include "amVK_Instance.hh"
void amVK_InstancePropsEXT::EnumeratePhysicalDevices(void) {
    amVK_InstanceProps::EnumeratePhysicalDevices(amVK_Instance::vk_Instance); 
}

#include "amVK_SwapChainIMGs.hh"
/**
 * CALLS:- `GetPhysicalDeviceSurfaceInfo()`
 *  PREV:- `EnumeratePhysicalDevices()`
 */
void amVK_InstancePropsEXT::push_back_amVK_SurfaceLinks(amVK_SwapChainIMGs* SC_IMGs) {
    amVK_1D_SurfaceLinks.push_back(
        amVK_SurfaceLinks({
            SC_IMGs->SC->S,
            SC_IMGs->SC,
            SC_IMGs
        })
    );
}




















/*


 .-----------------. .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .-----------------. .-----------------.
| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |
| | ____  _____  | || |   _____      | || |     ____     | || |  ____  ____  | || | ____    ____ | || |      __      | || | ____  _____  | || | ____  _____  | |
| ||_   \|_   _| | || |  |_   _|     | || |   .'    `.   | || | |_   ||   _| | || ||_   \  /   _|| || |     /  \     | || ||_   \|_   _| | || ||_   \|_   _| | |
| |  |   \ | |   | || |    | |       | || |  /  .--.  \  | || |   | |__| |   | || |  |   \/   |  | || |    / /\ \    | || |  |   \ | |   | || |  |   \ | |   | |
| |  | |\ \| |   | || |    | |   _   | || |  | |    | |  | || |   |  __  |   | || |  | |\  /| |  | || |   / ____ \   | || |  | |\ \| |   | || |  | |\ \| |   | |
| | _| |_\   |_  | || |   _| |__/ |  | || |  \  `--'  /  | || |  _| |  | |_  | || | _| |_\/_| |_ | || | _/ /    \ \_ | || | _| |_\   |_  | || | _| |_\   |_  | |
| ||_____|\____| | || |  |________|  | || |   `.____.'   | || | |____||____| | || ||_____||_____|| || ||____|  |____|| || ||_____|\____| | || ||_____|\____| | |
| |              | || |              | || |              | || |              | || |              | || |              | || |              | || |              | |
| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |
 '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' 


*/
#include "amVK_nlohmann.hh"

#include "amVK_Image.hh"
nlohmann::ordered_json nlohmannEXT_amVK_Image(amVK_Image *IMG) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();

        dict["Memory Address"] = toSTR(IMG->vk_Image);
        dict["VkImageView   "] = toSTR(IMG->vk_ImageView);

    return dict;
}

#include "amVK_SwapChain.hh"
nlohmann::ordered_json nlohmannEXT_amVK_SwapChainIMGs(amVK_SwapChainIMGs *SC_IMGs) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();

    dict["Memory Address"] = toSTR(SC_IMGs->SC->vk_SwapChainKHR);
    REY_Array_LOOP(SC_IMGs->amVK_1D_SC_IMGs, k) {
        nlohmann::ordered_json IMAGE_K = nlohmann::ordered_json::object();

            IMAGE_K["Memory Address"] = toSTR(SC_IMGs->amVK_1D_SC_IMGs[k]);
            IMAGE_K["VkImageView   "] = toSTR(SC_IMGs->amVK_1D_SC_IMGViews[k]);

        dict["[SwapChain Image " + std::to_string(k) + "]"] = IMAGE_K;
    }

    return dict;
}

nlohmann::ordered_json nlohmannEXT_amVK_SurfaceLinks(amVK_SurfaceLinks SurfLinks) {
    nlohmann::ordered_json dict = nlohmann::ordered_json::object();

        dict["Memory Address"] = toSTR(SurfLinks.S->vk_SurfaceKHR);
        dict["vkSwapchainKHR"] = nlohmannEXT_amVK_SwapChainIMGs(SurfLinks.SC_IMGs);
        
    REY_Array_LOOP(amVK_InstanceProps::amVK_1D_GPUs, k) {
        nlohmann::ordered_json GPU_k = nlohmann::ordered_json::object();

            GPU_k["Memory Address"] = toSTR(amVK_InstanceProps::amVK_1D_GPUs[k].vk_PhysicalDevice);
            GPU_k["vkGetPhysicalDeviceSurfaceFormatsKHR()"] = nlohmann_Array_VkSurfaceFormatKHR(SurfLinks.S->amVK_2D_GPUs_ImageFMTs[k]);

            VkSurfaceCapabilitiesKHR *SCAP = &(SurfLinks.S->amVK_1D_GPUs_SurfCAP[k]);
            GPU_k["VkSurfaceCapabilitiesKHR"] = nlohmann_VkSurfaceCapabilitiesKHR(SCAP);

        dict["[GPU " + std::to_string(k) + "]"] = GPU_k;
    }

    return dict;
}
/*

░▒▓████████▓▒░ ░▒▓█▓▒░ ░▒▓███████▓▒░   ░▒▓██████▓▒░  ░▒▓█▓▒░        
░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░        
░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░        
░▒▓██████▓▒░   ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓████████▓▒░ ░▒▓█▓▒░        
░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░        
░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░        
░▒▓█▓▒░        ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓████████▓▒░ 

 * https://quickref.me/json.html
 * ordered_json -> kinda like std::unordered_map
 *              -> i.e. doesn't automatically sort alphabetically
 */
void amVK_InstancePropsEXT::Export_nilohmannJSON_EXT(void) {
    nlohmann::ordered_json root;

        nlohmann::ordered_json vkEnumerateInstanceExtensionProperties   = nlohmann::ordered_json::object();
        nlohmann::ordered_json vkEnumerateInstanceLayerProperties       = nlohmann::ordered_json::object();
        nlohmann::ordered_json vkCreate_xxx_SurfaceKHR                  = nlohmann::ordered_json::object();

        amVK_LOOP_IEXTs(i) {
            std::string value = "specVersion" + std::to_string(amVK_1D_InstanceEXTs[i].specVersion);
            vkEnumerateInstanceExtensionProperties[amVK_1D_InstanceEXTs[i].extensionName] = value;
        }

        amVK_LOOP_ILayers(i) {
            vkEnumerateInstanceLayerProperties[amVK_1D_InstanceLayers[i].layerName] = amVK_1D_InstanceLayers[i].description;
        }
    
        REY_Array_LOOP(amVK_1D_SurfaceLinks, m) {
            amVK_SurfaceLinks SurfLinks = amVK_1D_SurfaceLinks[m];
            vkCreate_xxx_SurfaceKHR["[Surface " + std::to_string(m) + "]"] = nlohmannEXT_amVK_SurfaceLinks(SurfLinks);
        }
   
    root["vkEnumerateInstanceExtensionProperties"] = vkEnumerateInstanceExtensionProperties;
    root["vkEnumerateInstanceLayerProperties"] = vkEnumerateInstanceLayerProperties;
    root["vkCreate_xxx_SurfaceKHR"] = vkCreate_xxx_SurfaceKHR;
    root["vkEnumeratePhysicalDevices"] = nlohmann_amVK_1D_GPUs();
    
    // Write to file
    std::ofstream file("data.json");
    file << root.dump(4); // Indent with 4 spaces
}