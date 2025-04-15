#include "amVK_Instance.hh"

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
void amVK_Instance::ExportJSON(void) {
    nlohmann::ordered_json root;
    nlohmann::ordered_json vkEnumeratePhysicalDevices = nlohmann::ordered_json::array();
                    
    for (int k = 0, lim = amVK_GPU_List.n; k < lim; k++) {
        vkEnumeratePhysicalDevices.push_back(toSTR(amVK_GPU_List[k]))
    }

    root["vkEnumeratePhysicalDevices"] = vkEnumeratePhysicalDevices;
    
    // Write to file
    std::ofstream file("data.json");
    file << root.dump(4); // Indent with 4 spaces
}