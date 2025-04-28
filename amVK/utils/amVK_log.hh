#pragma once
#include "REY_Logger.hh"
#include <vulkan/vulkan.h>

#define amVK_FAILED(x) \
    REY_LOG_EX("FAILED:- " << x << "\n"     \
            << "    | \n"                   \
            << "    | [" << return_code << "] --> " << vulkan_result_msg(return_code) << "\n"   \
            << "    | "                     \
    );

#define amVK_FAILED_hint(x, hint) \
    REY_LOG_EX("FAILED:- " << x << "\n"     \
            << "    | \n"                   \
            << "    | [" << return_code << "] --> " << vulkan_result_msg(return_code) << "\n"   \
            << "    | "                     \
            << "    | " << hint << "\n"     \
            << "    | "                     \
    );

#define amVK_PASSED(x) REY_LOG("PASSED:- " << x);
#define amVK_DONE(x)   REY_LOG("  DONE:- " << x);

#define amVK_return_code_log(x)           \
    if (return_code != VK_SUCCESS) {      \
        amVK_FAILED(x << " 😶‍🌫️");          \
    } else {                              \
        amVK_PASSED(x << " 😄");          \
    }

#define amVK_RC_silent_check(x)  \
    if (return_code != VK_SUCCESS) {      \
        amVK_FAILED(x << " 😶‍🌫️");          \
    }

#if false
    #ifndef REY_LOG_status
        #define REY_LOG_status(x) REY_LOG(x)
    #endif
    #ifndef REY_LOG_notfound
        #define REY_LOG_notfound(x) REY_LOG_EX("NotFound:- " << x);
    #endif

    #define amVK_return_code_log2(x) amVK_return_code_log(x)
#else
    #define amVK_return_code_log2(x)
    #ifndef REY_LOG_status
        #define REY_LOG_status(x)
    #endif
    #ifndef REY_LOG_notfound
        #define REY_LOG_notfound(x)
    #endif
#endif

const char *vulkan_result_msg(VkResult return_code);