# CMAKE_CURRENT_LIST_DIR = Where this file is located
# Here in These files ---> We can do Library Specific Extra Stuffs

include(${CMAKE_CURRENT_LIST_DIR}/REY_FetchV4_X.vulkan.cmake)

if(  (DEFINED REY_FetchV4_MODS_PATH)   AND   (NOT "${REY_FetchV4_MODS_PATH}" STREQUAL ""))
    if (EXISTS  ${REY_FetchV4_MODS_PATH}/REY_FetchV4_MOD.vulkan.cmake)
        include(${REY_FetchV4_MODS_PATH}/REY_FetchV4_MOD.vulkan.cmake)
    endif()
endif()

include(${CMAKE_CURRENT_LIST_DIR}/REY_FetchV4.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/REY_FetchV4_X_RESET.cmake)