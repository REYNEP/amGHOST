# -------------------- SEE DOCUMENTATION in https://github.com/REYNEP/REY_LoggerNUtils/blob/main/REY_FetchV4/REY_FetchV4_X_DOCS.cmake -------------------- #
    set(Tool_Name vulkan)   # usually i set this ==> into this file's name `REY_FetchV4_X.vulkan.cmake` 😊
    set(TN ${Tool_Name})

    # Way-1. REY_SCOUT_${TN}_PATHS -------> Trying to Find    [if] [REY_SCOUT_${TN}_PATHS != empty]
        # Environment Variables
        # VULKAN_SDK - Base SDK path
        # VK_SDK_PATH - Alternative SDK path
        # VULKAN_VERSION - SDK version
    set(REY_SCOUT_${TN}_PATHS
        # Windows paths
        "$ENV{VULKAN_SDK}"
        "$ENV{VK_SDK_PATH}"
        "C:/VulkanSDK"
        # Linux paths
        "/usr/local/include"
        "/usr/include"
        # macOS paths
        "/usr/local/include"
        "/opt/homebrew/include"
    )
    set(Binary_Hints
        # Windows binaries
        vulkan-1 vulkan-1.lib 
        # Linux binaries
        vulkan libvulkan
        # MacOS binaries
        libMoltenVK MoltenVK
    )
    set(Header_Name  "vulkan/vulkan.h")
    set(Target_Name  REY_FetchV4::vulkan)   # You will have to LINK THIS [case-sensitive] to your executable/binary

    # Way-2. Git_SubModule ---------------> Git SubModule     [elseif] [Git_SubModule != empty]
    set(Git_SubModule)

    # Way-3. Zip_Links -------------------> cmake Download    [elseif] [Zip_Links != empty]
    set(Zip_Links)

    # Way-4. REY_FETCH_${TN}_BASE_DIR ----> Git Clone         [else]
    set(REY_FETCH_${TN}_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.forge)
    set(Git_Link)
    set(Git_CloneDir_Name REY_LoggerNUtils)
    set(Git_CheckFiles
        ${Git_CloneDir_Name}/CMakeLists.txt
        ${Git_CloneDir_Name}/REY_Logger.hh
        ${Git_CloneDir_Name}/REY_Logger.cpp
    )
# --------------------