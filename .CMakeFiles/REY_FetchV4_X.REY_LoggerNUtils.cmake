# -------------------- SEE DOCUMENTATION in https://github.com/REYNEP/REY_LoggerNUtils/blob/main/REY_FetchV4/REY_FetchV4_X_DOCS.cmake -------------------- #
    set(Tool_Name REY_LoggerNUtils)
    set(TN ${Tool_Name})

    # Way-1. REY_SCOUT_${TN}_PATHS -------> Trying to Find    [if] [REY_SCOUT_${TN}_PATHS != empty]
    set(REY_SCOUT_${TN}_PATHS)
    set(Binary_Hints REY_LoggerNUtils.lib)
    set(Header_Name  REY_Logger.hh)
    set(Target_Name  REY_LoggerNUtils)

    # Way-2. Git_SubModule ---------------> Git SubModule     [elseif] [Git_SubModule != empty]
    set(Git_SubModule    ${CMAKE_CURRENT_SOURCE_DIR}/REY_LoggerNUtils)

    # Way-3. Zip_Links -------------------> cmake Download    [elseif] [Zip_Links != empty]
    set(Zip_Links)

    # Way-4. REY_FETCH_${TN}_BASE_DIR ----> Git Clone         [else] [these won't be used 😉]
    set(REY_FETCH_${TN}_BASE_DIR)
    set(Git_Link)
    set(Git_CloneDir_Name)
    set(Git_Clone_Recursive OFF)
    set(Git_CheckFiles
        ${Git_CloneDir_Name}/CMakeLists.txt
        ${Git_CloneDir_Name}/REY_Logger.hh
        ${Git_CloneDir_Name}/REY_Logger.cpp
    )
    set(Git_AddSubdirectory ON)
# --------------------