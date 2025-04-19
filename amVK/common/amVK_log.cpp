#include "amVK_log.hh"
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