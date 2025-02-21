# CMAKE_CURRENT_LIST_DIR = Where this file is located
# Here in These files ---> We can do Library Specific Extra Stuffs

include(${CMAKE_CURRENT_LIST_DIR}/REY_FetchV4_X.REY_LoggerNUtils.cmake)

if(  (DEFINED REY_FetchV4_MODS_PATH)   AND   (${REY_FetchV4_MODS_PATH} NOT STREQUAL ""))
    if (EXISTS  ${REY_FetchV4_MODS_PATH}/REY_FetchV4_MOD.REY_LoggerNUtils.cmake)
        include(${REY_FetchV4_MODS_PATH}/REY_FetchV4_MOD.REY_LoggerNUtils.cmake)
    endif()
endif()

include(${CMAKE_CURRENT_LIST_DIR}/REY_FetchV4.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/REY_FetchV4_X_RESET.cmake)