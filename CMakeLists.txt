#[[                 ********** Boost Software License - Version 1.0 - August 17th, 2003 **********
Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and accompa
nying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute, and transm
it the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the Software is fu
rnished to do so, all subject to the following:

The copyright notices in the Software and this entire statement, including the above license grant, this restriction and
the following disclaimer, must be included in all copies of the Software, in whole or in part, and all derivative works
of the Software, unless such copies or derivative works are solely in the form of machine-executable object code genera
ted by a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WAR
RANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE COPYRIGH
T HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#                           *************** END Boost Software License BLOCK ***************                          ]]
#                   *************** The Original Code is Copyright (C) 2025, REYNEP ***************                   ]]


cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project("amGHOST_PROJECT" VERSION 0.1)

    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------
    set(SRC
        "amGHOST_System.cpp"
        "amGHOST_Event.cpp"
        "intern/amGHOST_SystemWIN32.cpp"
        "intern/amGHOST_WindowWIN32.cpp"
        "intern/WIN32_EXT/spy.cpp"
        
        "amVK/utils/amVK_log.cpp"
        "amVK/utils/amVK_InstanceProps.cpp"
        "amVK/utils/amVK_GPUProps.cpp"
        "amVK/utils/amVK_Enum2String.cpp"
        "amVK/utils/amVK_InstancePropsExport_nlohmann.cpp"

        "amVK/core/amVK_Instance.cpp"
        "amVK/core/amVK_Device.cpp"
        "amVK/core/amVK_Surface.cpp"
        "amVK/core/amVK_SwapChain.cpp"
        "amVK/core/amVK_RenderPass.cpp"
        "amVK/core/amVK_PipelineGRAPHICS.cpp"
        "amVK/core/amVK_Commands.cpp"
        
        "amVK/impl/amVK_SurfacePresenter.cpp"
        "amVK/mesh/amVK_VertexBuffer.cpp"
    )

    set(INC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/intern/
        ${CMAKE_CURRENT_SOURCE_DIR}/intern/WIN32_EXT
        ${CMAKE_CURRENT_SOURCE_DIR}/amE/
        ${CMAKE_CURRENT_SOURCE_DIR}/amTHREAD/
        
        ${CMAKE_CURRENT_SOURCE_DIR}/amVK/
        ${CMAKE_CURRENT_SOURCE_DIR}/amVK/common
        ${CMAKE_CURRENT_SOURCE_DIR}/amVK/core
        ${CMAKE_CURRENT_SOURCE_DIR}/amVK/extras
        ${CMAKE_CURRENT_SOURCE_DIR}/amVK/mesh
        ${CMAKE_CURRENT_SOURCE_DIR}/amVK/utils
    )
# --------------------
include(${CMAKE_CURRENT_SOURCE_DIR}/intern/WIN32_EXT/extract.cmake)

# --------------------
            add_library    (amGHOST ${SRC})
target_include_directories (amGHOST PUBLIC ${INC})
set_target_properties      (amGHOST  PROPERTIES  OUTPUT_NAME "lib-amGHOST"  PREFIX "")

# --REY_LoggerNUtils--
    include(${CMAKE_CURRENT_SOURCE_DIR}/.CMakeFiles/REY_FetchV4.REY_LoggerNUtils.cmake)     # SubModule
    target_link_libraries  (amGHOST PUBLIC REY_LoggerNUtils)

# ------vulkan--------
    include(${CMAKE_CURRENT_SOURCE_DIR}/.CMakeFiles/REY_FetchV4.vulkan.cmake)               # SubModule
    target_link_libraries  (amGHOST PUBLIC REY_FetchV4::vulkan)

# ------install-------
    install(TARGETS amGHOST
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/.install)