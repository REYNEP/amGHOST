#include "amVK.hh"

void amVK_Props::EnumeratePhysicalDevices(void) 
{
    uint32_t deviceCount = 0;     
        // [implicit valid usage]:- must be 0     [if 3rd-param = nullptr]

        vkEnumeratePhysicalDevices(amVK_Props::s_vk, &deviceCount, nullptr);
            // This function is 'output-ing into' deviceCount

    amVK_GPU_List.n    = deviceCount;
    amVK_GPU_List.data = new VkPhysicalDevice[deviceCount];

        VkResult return_code = vkEnumeratePhysicalDevices(amVK_Props::s_vk, &amVK_GPU_List.n, amVK_GPU_List.data);
        amVK_return_code_log("vkEnumeratePhysicalDevices()");

    amVK_Props::called_EnumeratePhysicalDevices = true;
}

/** 
 * i don't wanna scatter all the Properties All around my code. So, i'm gonna keep them here 😊
 *   --> Right inside `amVK_Props` class
 * 
 * Don't Call before you have called `amVK_Props::EnumeratePhysicalDevices()`
 * TODO: 
 *   --> Make all the Memory Allocation within this function -> in one block of RAM
 */
void amVK_Props::GetPhysicalDeviceQueueFamilyProperties(void) {
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
    amVK_Props::called_GetPhysicalDeviceQueueFamilyProperties = true;
}







/** 
 * @param p_flagBits:- can be a mixture of multiple bits. use `|` operator a.k.a 'or' operator, which can join flags together
 * @param ID:- Use:- `amVK_Props::VkPhysicalDevice_2_amVK_Index()` if you wanna pass in `VkPhysicalDevice` 
 * @returns `VkDeviceQCI.queueFamilyIndex` to be used
 */
uint32_t amVK_Props::ChooseAQueueFamily(VkQueueFlags p_flagBits, amVK_Props::PD_Index p_ID) {
    uint32_t k = p_ID;
    REY_Array<VkQueueFamilyProperties> GPU_k_QFAM_Array = amVK_2D_QFAM_PROPs[k];

    for (uint32_t i = 0, lim = amVK_2D_QFAM_PROPs[k].n; i < lim; i++) {
        if (amVK_2D_QFAM_PROPs[k][i].queueFlags & p_flagBits) {
            return i;
        }
    }

    return amVK_QueueFamily_NOT_FOUND;
}

amVK_Props::PD_Index amVK_Props::VkPhysicalDevice_2_amVK_Index(VkPhysicalDevice PDevice) {
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
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
std::string toSTR(void* ptr) {
    std::stringstream ss;
    ss << ptr;
    return ss.str();
}

/*
 * https://quickref.me/json.html
 * ordered_json -> kinda like std::unordered_map
 *              -> i.e. doesn't automatically sort alphabetically
 */
void amVK_Props::ExportJSON(void) {
    nlohmann::ordered_json root;
    nlohmann::ordered_json vkEnumeratePhysicalDevices  = nlohmann::ordered_json::object();
                    
    for (uint32_t k = 0, lim = amVK_GPU_List.n; k < lim; k++) {
        nlohmann::ordered_json GPU_k = nlohmann::ordered_json::object();

            nlohmann::ordered_json QFAM_Array = nlohmann::ordered_json::object(); 

            for (uint32_t i = 0, lim = amVK_2D_QFAM_PROPs[k].n; i < lim; i++) {
                nlohmann::ordered_json QFAM_i = nlohmann::ordered_json::object();

                nlohmann::ordered_json qF = nlohmann::ordered_json::array();
                    VkQueueFlags _qF = amVK_2D_QFAM_PROPs[k][i].queueFlags;
                    if (_qF & VK_QUEUE_GRAPHICS_BIT)         { qF.push_back("VK_QUEUE_GRAPHICS_BIT"); }
                    if (_qF & VK_QUEUE_COMPUTE_BIT)          { qF.push_back("VK_QUEUE_COMPUTE_BIT"); }
                    if (_qF & VK_QUEUE_TRANSFER_BIT)         { qF.push_back("VK_QUEUE_TRANSFER_BIT"); }
                    if (_qF & VK_QUEUE_SPARSE_BINDING_BIT)   { qF.push_back("VK_QUEUE_SPARSE_BINDING_BIT"); }
                    if (_qF & VK_QUEUE_PROTECTED_BIT)        { qF.push_back("VK_QUEUE_PROTECTED_BIT"); }
                    if (_qF & VK_QUEUE_VIDEO_DECODE_BIT_KHR) { qF.push_back("VK_QUEUE_VIDEO_DECODE_BIT_KHR"); }
                    if (_qF & VK_QUEUE_VIDEO_ENCODE_BIT_KHR) { qF.push_back("VK_QUEUE_VIDEO_ENCODE_BIT_KHR"); }
                    if (_qF & VK_QUEUE_OPTICAL_FLOW_BIT_NV)  { qF.push_back("VK_QUEUE_OPTICAL_FLOW_BIT_NV"); }
                    qF.push_back(std::string("VkQueueFlagBits:- ") + std::to_string(_qF));
                
                QFAM_i["queueFlags"] = qF;
                QFAM_i["queueCount"] = amVK_2D_QFAM_PROPs[k][i].queueCount;
                QFAM_i["timestampValidBits"] = amVK_2D_QFAM_PROPs[k][i].timestampValidBits;

                nlohmann::ordered_json minImageTransferGranularity = nlohmann::json::object();
                    minImageTransferGranularity["width"] = amVK_2D_QFAM_PROPs[k][i].minImageTransferGranularity.width;
                    minImageTransferGranularity["height"] = amVK_2D_QFAM_PROPs[k][i].minImageTransferGranularity.height;
                    minImageTransferGranularity["depth"] = amVK_2D_QFAM_PROPs[k][i].minImageTransferGranularity.depth;

                QFAM_i["minImageTransferGranularity"] = minImageTransferGranularity;

                std::string index_id  = "QueueFamily" + std::to_string(i) + "_Properties";
                QFAM_Array[index_id] = QFAM_i;
            }

            GPU_k["Memory Address"] = toSTR(amVK_GPU_List[k]);
            GPU_k["vkGetPhysicalDeviceQueueFamilyProperties()"] = QFAM_Array;

        vkEnumeratePhysicalDevices["[GPU " + std::to_string(k) + "]"] = GPU_k;
    }

    root["vkEnumeratePhysicalDevices"] = vkEnumeratePhysicalDevices;
    
    // Write to file
    std::ofstream file("data.json");
    file << root.dump(4); // Indent with 4 spaces
}












#include <vulkan/vulkan.h>
/**
 * Based on GLFW's function https://github.com/glfw/glfw/blob/master/src/vulkan.c#L164
 */
const char *vulkan_result_msg(VkResult return_code) {
    switch (return_code)
    {
      case VK_SUCCESS:
          return "Success";
  
      case VK_NOT_READY:
          return "[VK_NOT_READY] --> A fence or query has not yet completed.";
  
      case VK_TIMEOUT:
          return "[VK_TIMEOUT] --> A wait operation has not completed in the specified time";
  
      case VK_EVENT_SET:
          return "[VK_EVENT_SET] --> An event is signaled";
  
      case VK_EVENT_RESET:
          return "[VK_EVENT_RESET] --> An event is unsignaled";
  
      case VK_INCOMPLETE:
          return "[VK_INCOMPLETE] --> A return array was too small for the result";
          
  
  
  
      case VK_ERROR_OUT_OF_HOST_MEMORY:
          return "[VK_ERROR_OUT_OF_HOST_MEMORY] --> A host memory allocation has failed";
      case VK_ERROR_OUT_OF_DEVICE_MEMORY:
          return "[VK_ERROR_OUT_OF_DEVICE_MEMORY] --> A device memory allocation has failed";
      case VK_ERROR_INITIALIZATION_FAILED:
          return "[VK_ERROR_INITIALIZATION_FAILED] --> Initialization of an object could not be completed for implementation-specific reasons";
      case VK_ERROR_DEVICE_LOST:
          return "[VK_ERROR_DEVICE_LOST] --> The logical or physical device has been lost";
      case VK_ERROR_MEMORY_MAP_FAILED:
          return "[VK_ERROR_MEMORY_MAP_FAILED] --> Mapping of a memory object has failed ";
  
  
  
  
      case VK_ERROR_LAYER_NOT_PRESENT:
          return "[VK_ERROR_LAYER_NOT_PRESENT] --> A requested layer is not present or could not be loaded";
  
      case VK_ERROR_EXTENSION_NOT_PRESENT:
          return "[VK_ERROR_EXTENSION_NOT_PRESENT] --> A requested extension is not supported";
  
      case VK_ERROR_FEATURE_NOT_PRESENT:
          return "[VK_ERROR_FEATURE_NOT_PRESENT] --> A requested feature is not supported";
  
      case VK_ERROR_INCOMPATIBLE_DRIVER:   
          //[VkApplicationInfo] Specs Specified that Above VK1.1 should not return this for any .apiVersion [passed on to vkCreateInstance in CONSTRUCTOR]
          return "[VK_ERROR_IMCOMPATIBLE_DRIVER] --> The requested version of Vulkan is not supported by the driver or is otherwise incompatible";
  
      case VK_ERROR_TOO_MANY_OBJECTS:
          return "[VK_ERROR_TOO_MANY_OBJECTS] --> Too many objects of the type have already been created";
  
      case VK_ERROR_FORMAT_NOT_SUPPORTED:
          return "[VK_ERROR_FORMAT_NOT_SUPPORTED] --> A requested format is not supported on this device";
  
          
  
  
  
      case VK_ERROR_SURFACE_LOST_KHR:
          return "[VK_ERROR_SURFACE_LOST_KHR] --> A surface is no longer available";
          
      case VK_SUBOPTIMAL_KHR:
          return "[VK_SUBOPTIMAL_KHR] --> A swapchain no longer matches the surface properties exactly, but can still be used";
      case VK_ERROR_OUT_OF_DATE_KHR:
          return "[VK_ERROR_OUT_OF_DATE_KHR] --> A surface has changed in such a way that it is no longer compatible with the swapchain";
      case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
          return "[VK_ERROR_INCOMPATIBLE_DISPLAY_KHR] --> The display used by a swapchain does not use the same presentable ImageLayout";
  
      case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
          return "[VK_ERROR_NATIVE_WINDOW_IN_USE_KHR] --> The requested window is already connected to a VkSurfaceKHR, or to some other non-Vulkan API";
      case VK_ERROR_VALIDATION_FAILED_EXT:
          return "[VK_ERROR_VALIDATION_FAILED_EXT] --> A validation layer found an error";
      default:
          return "ERROR: UNKNOWN VULKAN ERROR";
    }
}














/**
                   _  _____  ____  _   _ 
                  | |/ ____|/ __ \| \ | |
  _   _ _   _     | | (___ | |  | |  \| |
 | | | | | | |_   | |\___ \| |  | | . ` |
 | |_| | |_| | |__| |____) | |__| | |\  |
  \__, |\__, |\____/|_____/ \____/|_| \_|
   __/ | __/ |                           
  |___/ |___/                            

*/

// yyJSON [new] -> Kinda based on gason
// Couldn't get STRING to work unless using `yyjson_mut_strcpy`
    // REY_MALLOC_COPY_STD_STRING wasn't working 
        // --> QueueFamily0_Properties, QueueFamily1_Properties, etc. were not being printed
        // --> it was like all of them were --> QueueFamily0_Properties or like QueueFamily4_Properties
#include <yyjson.h>

void amVK_Props::Export_yyJSON(void) {
    yyjson_mut_doc *doc = yyjson_mut_doc_new(NULL);
    yyjson_mut_val *root = yyjson_mut_obj(doc);
    yyjson_mut_val *vkEnumeratePhysicalDevices = yyjson_mut_obj(doc);

    for (int i = 0, lim = amVK_GPU_List.n; i < lim; i++) {
        yyjson_mut_val *GPU = yyjson_mut_obj(doc);

        for (int j = 0, lim = amVK_2D_QFAM_PROPs[i].n; j < lim; j++) {
            yyjson_mut_val *QFam = yyjson_mut_obj(doc);

            yyjson_mut_obj_add_int(doc, QFam, "queueFlags", amVK_2D_QFAM_PROPs[i][j].queueFlags);
            yyjson_mut_obj_add_int(doc, QFam, "queueCount", amVK_2D_QFAM_PROPs[i][j].queueCount);
            yyjson_mut_obj_add_int(doc, QFam, "timestampValidBits", amVK_2D_QFAM_PROPs[i][j].timestampValidBits);

            yyjson_mut_val *minImageTransferGranularity = yyjson_mut_obj(doc);
            yyjson_mut_obj_add_int(doc, minImageTransferGranularity, "width", amVK_2D_QFAM_PROPs[i][j].minImageTransferGranularity.width);
            yyjson_mut_obj_add_int(doc, minImageTransferGranularity, "height", amVK_2D_QFAM_PROPs[i][j].minImageTransferGranularity.height);
            yyjson_mut_obj_add_int(doc, minImageTransferGranularity, "depth", amVK_2D_QFAM_PROPs[i][j].minImageTransferGranularity.depth);

            yyjson_mut_obj_add_val(doc, QFam, "minImageTransferGranularity", minImageTransferGranularity);

            std::string      key = "QueueFamily" + std::to_string(j) + "_Properties";
            yyjson_mut_val *_key = yyjson_mut_strcpy(doc, key.c_str());
            yyjson_mut_obj_add_val(doc, GPU, _key->uni.str, QFam);
        }

        std::string      gpu_key = toSTR(amVK_GPU_List[i]);
        yyjson_mut_val *_gpu_key = yyjson_mut_strcpy(doc, gpu_key.c_str());
        yyjson_mut_obj_add_val(doc, vkEnumeratePhysicalDevices, _gpu_key->uni.str, GPU);
    }

    yyjson_mut_obj_add_val(doc, root, "vkEnumeratePhysicalDevices", vkEnumeratePhysicalDevices);




    // -------------------- Write to file -------------------- //
        yyjson_write_flag flg = YYJSON_WRITE_PRETTY | YYJSON_WRITE_ESCAPE_UNICODE;
        yyjson_mut_doc_set_root(doc, root);

        yyjson_write_err err;
        bool result = yyjson_mut_write_file("data.json", doc, flg, NULL, &err);

            if (!result) {
                std::cerr << "Failed to write JSON file. Error code: " << err.code 
                        << ", Message: " << err.msg << std::endl;
                
                // Check if file can be opened for writing
                FILE* test = fopen("data.json", "w");
                if (!test) {
                    std::cerr << "Cannot open file for writing. Error: " << strerror(errno) << std::endl;
                } else {
                    fclose(test);
                    std::cerr << "File can be opened but yyjson write failed" << std::endl;
                }
            }

        yyjson_mut_doc_free(doc);
    // -------------------- Write to file -------------------- //
}














/**
                       _ 
                      | |
  _ __ _   _ _ __ ___ | |
 | '__| | | | '_ ` _ \| |
 | |  | |_| | | | | | | |
 |_|   \__, |_| |_| |_|_|
        __/ |            
       |___/             

*/

#include <vulkan/vulkan.h>
#include <ryml.hpp>
#include <ryml_std.hpp> // for std::string support
#include <iostream>
#include <fstream>

namespace c4 {
namespace yml {

void write(NodeRef* n, VkExtent3D const& v) {
    *n |= MAP;
    (*n)["width"] << v.width;
    (*n)["height"] << v.height;
    (*n)["depth"] << v.depth;
}

} // namespace yml
} // namespace c4

#define REY_MALLOC_COPY_STD_STRING(new_var, str)  \
    new char[str.length() + 1]; \
    strcpy(new_var, str.c_str()); \
    new_var[str.length()] = '\0';

char* REY_malloc_copy_std_string(std::string str) {
    char* new_var = new char[str.length() + 1];
    strcpy(new_var, str.c_str());
    new_var[str.length()] = '\0';

    return new_var;
}

void amVK_Props::_ExportYAML(void) {
    ryml::Tree tree;                      // Create a YAML tree
    ryml::NodeRef root = tree.rootref();  // Root node (map)

    root |= ryml::MAP; 
        // SEQ = yaml array             --> seq[int_index]      --> Doesn't print INDEX
        // MAP = yaml object/mapping    --> map["string_KEY"]   --> ryml doesn't keep copies of `key` & `val`
        // VAL = yaml val/scalar        --> constant/single-val
        // NODE = smth that won't be printed

        ryml::NodeRef Rx  = root["vkEnumeratePhysicalDevices()"];
                      Rx |= ryml::MAP;

        for (int i = 0, lim = amVK_GPU_List.n; i < lim; i++) 
        {
            char* GPU_key = REY_MALLOC_COPY_STD_STRING(GPU_key, toSTR(amVK_GPU_List[i]));

            ryml::NodeRef GPU  = Rx[GPU_key];
                          GPU |= ryml::MAP;

            ryml::NodeRef  Qx  = GPU["vkGetPhysicalDeviceQueueFamilyProperties()"];
                           Qx |= ryml::MAP;

            for (int j = 0, lim = amVK_2D_QFAM_PROPs[i].n; j < lim; j++) 
            {
                std::string _key = std::string("QueueFamily") + std::to_string(j) + "_Properties";
                       char* key = REY_MALLOC_COPY_STD_STRING(key, _key);

                std::cout << key << std::endl;
                ryml::NodeRef QFam  = Qx[key];
                              QFam |= ryml::MAP;

                QFam["queueFlags"] << amVK_2D_QFAM_PROPs[i][j].queueFlags;
                    // see --> void write(NodeRef* n, VkQueueFlags const& QF)
                QFam["queueCount"] << amVK_2D_QFAM_PROPs[i][j].queueCount;
                QFam["timestampValidBits"] << amVK_2D_QFAM_PROPs[i][j].timestampValidBits;
                QFam["minImageTransferGranularity"] << amVK_2D_QFAM_PROPs[i][j].minImageTransferGranularity;
                    // see --> void write(NodeRef* n, VkExtent3D const& v)
            }
        }


    // Emit YAML to a string
    std::string yaml = ryml::emitrs<std::string>(tree);

    // Write to file
    std::ofstream("data.yaml") << yaml;

    // Open the file for writing
    FILE* json_file = std::fopen("data_ryml.json", "w");
    if (json_file) {
        // Emit JSON to the file
        ryml::emit_json(tree, json_file);

        // Close the file
        std::fclose(json_file);
    }
}
