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
        nlohmann::ordered_json vkCreate_xxx_SurfaceKHR                  = nlohmann::ordered_json::object();

        amVK_LOOP_IEXTs(i) {
            std::string value = "specVersion" + std::to_string(amVK_1D_InstanceEXTs[i].specVersion);
            vkEnumerateInstanceExtensionProperties[amVK_1D_InstanceEXTs[i].extensionName] = value;
        }
    
        REY_Array_LOOP(amVK_1D_SurfaceLinks, m) {
            amVK_SurfaceLinks SurfLinks = amVK_1D_SurfaceLinks[m];
            vkCreate_xxx_SurfaceKHR["[Surface " + std::to_string(m) + "]"] = nlohmannEXT_amVK_SurfaceLinks(SurfLinks);
        }
   
    root["vkEnumerateInstanceExtensionProperties"] = vkEnumerateInstanceExtensionProperties; 
    root["vkCreate_xxx_SurfaceKHR"] = vkCreate_xxx_SurfaceKHR;
    root["vkEnumeratePhysicalDevices"] = nlohmann_amVK_1D_GPUs();
    
    // Write to file
    std::ofstream file("data.json");
    file << root.dump(4); // Indent with 4 spaces
}