#include "amVK_Instance.hh"
#include "amVK_InstanceProps.hh"
#include "amVK_Enum2String.hh"
#include <string>
#include <sstream>
#include <iostream>


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

void amVK_InstanceProps::Export_yyJSON(void) {
    yyjson_mut_doc *doc = yyjson_mut_doc_new(NULL);
    yyjson_mut_val *root = yyjson_mut_obj(doc);
    yyjson_mut_val *vkEnumeratePhysicalDevices = yyjson_mut_obj(doc);

    for (int i = 0, lim = amVK_1D_GPUs.n; i < lim; i++) {
        yyjson_mut_val *GPU = yyjson_mut_obj(doc);

        for (int j = 0, lim = amVK_2D_GPUs_QFAMs[i].n; j < lim; j++) {
            yyjson_mut_val *QFam = yyjson_mut_obj(doc);

            yyjson_mut_obj_add_int(doc, QFam, "queueFlags", amVK_2D_GPUs_QFAMs[i][j].queueFlags);
            yyjson_mut_obj_add_int(doc, QFam, "queueCount", amVK_2D_GPUs_QFAMs[i][j].queueCount);
            yyjson_mut_obj_add_int(doc, QFam, "timestampValidBits", amVK_2D_GPUs_QFAMs[i][j].timestampValidBits);

            yyjson_mut_val *minImageTransferGranularity = yyjson_mut_obj(doc);
            yyjson_mut_obj_add_int(doc, minImageTransferGranularity, "width", amVK_2D_GPUs_QFAMs[i][j].minImageTransferGranularity.width);
            yyjson_mut_obj_add_int(doc, minImageTransferGranularity, "height", amVK_2D_GPUs_QFAMs[i][j].minImageTransferGranularity.height);
            yyjson_mut_obj_add_int(doc, minImageTransferGranularity, "depth", amVK_2D_GPUs_QFAMs[i][j].minImageTransferGranularity.depth);

            yyjson_mut_obj_add_val(doc, QFam, "minImageTransferGranularity", minImageTransferGranularity);

            std::string      key = "QueueFamily" + std::to_string(j) + "_Properties";
            yyjson_mut_val *_key = yyjson_mut_strcpy(doc, key.c_str());
            yyjson_mut_obj_add_val(doc, GPU, _key->uni.str, QFam);
        }

        std::string      gpu_key = toSTR(amVK_1D_GPUs[i]);
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
                FILE* test = nullptr;

                #ifdef _MSC_VER
                    errno_t err = fopen_s(&test, "data.json", "w");
                    if (err != 0) {
                        std::cerr << "Error: Failed to open file 'data.json' for writing. "
                                << "Error code: " << err << std::endl;
                        return;
                    }
                #else
                    test = std::fopen("data.json", "w"); // POSIX-compliant
                    if (!test) {
                        std::cerr << "Error: Failed to open file 'data.json' for writing." << std::endl;
                        return;
                    }
                #endif

                if (!test) {
                    size_t bufferSize = 1024; // Start with a reasonable size
                    char* errorMessage = new char[bufferSize];

                    #ifdef _MSC_VER
                        strerror_s(errorMessage, bufferSize, err);
                    #else
                        strerror_r(err, errorMessage, bufferSize); // POSIX-compliant
                    #endif

                    std::cerr << "Cannot open file for writing. Error: " << errorMessage << std::endl;

                    delete[] errorMessage;
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

#define REY_MALLOC_COPY_STD_STRING(new_var, str)    \
    REY_strcpy(str.c_str());                        \
    new_var[str.length()] = '\0';

char* REY_malloc_copy_std_string(std::string str) {
    char* new_var = REY_strcpy(str.c_str());
    new_var[str.length()] = '\0';

    return new_var;
}

void amVK_InstanceProps::_ExportYAML(void) {
    ryml::Tree tree;                      // Create a YAML tree
    ryml::NodeRef root = tree.rootref();  // Root node (map)

    root |= ryml::MAP; 
        // SEQ = yaml array             --> seq[int_index]      --> Doesn't print INDEX
        // MAP = yaml object/mapping    --> map["string_KEY"]   --> ryml doesn't keep copies of `key` & `val`
        // VAL = yaml val/scalar        --> constant/single-val
        // NODE = smth that won't be printed

        ryml::NodeRef Rx  = root["vkEnumeratePhysicalDevices()"];
                      Rx |= ryml::MAP;

        for (int i = 0, lim = amVK_1D_GPUs.n; i < lim; i++) 
        {
            char* GPU_key = REY_MALLOC_COPY_STD_STRING(GPU_key, toSTR(amVK_1D_GPUs[i]));

            ryml::NodeRef GPU  = Rx[GPU_key];
                          GPU |= ryml::MAP;

            ryml::NodeRef  Qx  = GPU["vkGetPhysicalDeviceQueueFamilyProperties()"];
                           Qx |= ryml::MAP;

            for (int j = 0, lim = amVK_2D_GPUs_QFAMs[i].n; j < lim; j++) 
            {
                std::string _key = std::string("QueueFamily") + std::to_string(j) + "_Properties";
                       char* key = REY_MALLOC_COPY_STD_STRING(key, _key);

                std::cout << key << std::endl;
                ryml::NodeRef QFam  = Qx[key];
                              QFam |= ryml::MAP;

                QFam["queueFlags"] << amVK_2D_GPUs_QFAMs[i][j].queueFlags;
                    // see --> void write(NodeRef* n, VkQueueFlags const& QF)
                QFam["queueCount"] << amVK_2D_GPUs_QFAMs[i][j].queueCount;
                QFam["timestampValidBits"] << amVK_2D_GPUs_QFAMs[i][j].timestampValidBits;
                QFam["minImageTransferGranularity"] << amVK_2D_GPUs_QFAMs[i][j].minImageTransferGranularity;
                    // see --> void write(NodeRef* n, VkExtent3D const& v)
            }
        }


    // Emit YAML to a string
    std::string yaml = ryml::emitrs_yaml<std::string>(tree);

    // Write to file
    std::ofstream("data.yaml") << yaml;

    // Open the file for writing
    
    FILE* json_file = nullptr;
    #ifdef _MSC_VER
        errno_t err = fopen_s(&json_file, "data_ryml.json", "w");
        if (err != 0) {
            std::cerr << "Error: Failed to open file 'data_ryml.json' for writing. "
                    << "Error code: " << err << std::endl;
            return;
        }
    #else
        json_file = std::fopen("data_ryml.json", "w"); // POSIX-compliant
        if (!json_file) {
            std::cerr << "Error: Failed to open file 'data_ryml.json' for writing." << std::endl;
            return;
        }
    #endif
    
    if (json_file) {
        // Emit JSON to the file
        ryml::emit_json(tree, json_file);

        // Close the file
        std::fclose(json_file);
    }
}
