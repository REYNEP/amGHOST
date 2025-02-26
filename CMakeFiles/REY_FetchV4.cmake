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
#      *************** This File will be maintained @ https://github.com/REYNEP/REY_LoggerNUtils ***************      ]]

# --------------------
#       "REY_FetchV4.fmt.cmake" calls ----> "REY_FetchV4_X.<lib-name>.cmake" [SET Variables]
#       "REY_FetchV4.fmt.camke" calls ----> "REY.FetchV4_MOD.<lib-name>.cmake"
#       "REY_FetchV4.fmt.cmake" calls ----> "REY_FetchV4.cmake" [This File]
#       "REY_FetchV4.fmt.cmake" calls ----> "REY_FetchV4_X_RESET.cmake"    [RESET Variables]
# --------------------

# Pseudocode for this file
# ----------------------------------------
    # if (REY_SCOUT_${TN}_PATHS != "")
        # find_library(${Binary_Hints})
        # find_path(${TN}/${Header_Name})
        # USE:- REY_SCOUT_${TN}_PATHS
        # Check FOUND / LOG FATAL ERROR

    # else if(  (DEFINED Git_SubModule)   AND   (NOT "${Git_SubModule}" STREQUAL "")  )
        # git submodule init / update

    # else if(   (DEFINED Zip_Links)     AND     (NOT "${Zip_Links}" STREQUAL "")  )
        # download ${Zip_Links} --> unzip
        
    # else()
        # if( NOT EXISTS ${REY_FETCH_${TN}_BASE_DIR}/${Git_CloneDir_Name} )
            # git clone ${Git_Link}
            # add_subdirectory(${Git_CloneDir_Name})
        # else()
            # if(NOT EXISTS ${Git_CheckFiles})
                # LOG FATAL ERROR
            # else()
                # add_subdirectory(${Git_CloneDir_Name})
            # endif()
        # endif()
    # endif()
# ----------------------------------------







# --------------------
    if(NOT DEFINED ${CMAKE_BUILD_TYPE})
        set(CMAKE_BUILD_TYPE Debug)
    endif()
# --------------------
if (  (DEFINED REY_SCOUT_${TN}_PATHS)   AND   (NOT "${REY_SCOUT_${TN}_PATHS}" STREQUAL "")  )
    # ================================ FINDING ${Binary_Hints} =================================
        find_library(tmp_scout_${TN}_lib
            NAMES
                ${Binary_Hints}
            DOC
                ""
            PATHS
                ${REY_SCOUT_${TN}_PATHS}
            PATH_SUFFIXES
                Debug
                Release
                Lib         # Windows
                lib         # UNIX/MAC
                libs
                extern-libs

            NO_CACHE
            #NO_DEFAULT_PATH
        )

        if (EXISTS ${tmp_scout_${TN}_lib})
            set(  
                  REY_FOUND_${TN}_LIBRARY
                ${tmp_scout_${TN}_lib}
                CACHE STRING "" FORCE
            )
            message(STATUS "[REY_FetchV4_SCOUT]")
            message(STATUS "    Found 1 File:- ${tmp_scout_${TN}_lib}")
        endif()
    # ================================ FINDING ${Binary_Hints} =================================


    # ================================ FINDING ${Header_Name} =================================
        find_path(tmp_scout_${TN}_inc
            NAMES
                ${Header_Name}
            PATHS
                ${REY_SCOUT_${TN}_PATHS}
            PATH_SUFFIXES
                include/
                includes/
                include/include/
                extern-includes/
                ${TN}
                ${TN}/include
                ${TN}/include/${TN}
                include/${TN}
                include/include/${TN}
                includes/${TN}
                includes/include/${TN}
                extern-includes/${TN}
                extern-includes/include/${TN}

            NO_CACHE
        )

        if (tmp_scout_${TN}_inc)
            set(
                  REY_FOUND_${TN}_INCLUDE
                ${tmp_scout_${TN}_inc}
                CACHE STRING "" FORCE
            )
            message(STATUS "[REY_FetchV4_SCOUT]")
            message(STATUS "    Found include dir: ${tmp_scout_${TN}_inc}")
        endif()
    # ================================ FINDING ${Header_Name} =================================


    # =============================== if BOTH ARE FOUND =================================
        if (DEFINED REY_FOUND_${TN}_LIBRARY AND DEFINED REY_FOUND_${TN}_INCLUDE)
            #         see Target_Name
            add_library(
                ${Target_Name} STATIC 
                IMPORTED
            )
            set_target_properties(
                ${Target_Name} 
                PROPERTIES
                    IMPORTED_LOCATION ${REY_FOUND_${TN}_LIBRARY}
                    INTERFACE_INCLUDE_DIRECTORIES ${REY_FOUND_${TN}_INCLUDE}
            )
            message(STATUS "[REY_FetchV4_SCOUT]")
            message(STATUS " REY_FetchV4_X.${TN}.cmake::Target_Name:- ${Target_Name}")
            message(STATUS "       [cached] REY_FOUND_${TN}_LIBRARY:- ${REY_FOUND_${TN}_LIBRARY}")
            message(STATUS "       [cached] REY_FOUND_${TN}_INCLUDE:- ${REY_FOUND_${TN}_INCLUDE}")
        else ()
            message(STATUS "REY_SCOUT_${TN}_PATHS:- ${REY_SCOUT_${TN}_PATHS}")
            message(STATUS "tmp_scout_${TN}_lib:---   ${tmp_scout_${TN}_lib}")
            message(STATUS "tmp_scout_${TN}_inc:---   ${tmp_scout_${TN}_inc}")
            message(FATAL_ERROR "REY_SCOUT_${TN}_PATHS is defined but Could not find ${TN} library. 
                                Please Undefine it or make it EMPTY-STRING, if you want us to automatically `git clone ${Git_Link}`")
        endif()
    # =============================== if BOTH ARE FOUND =================================



elseif(  (DEFINED Git_SubModule)   AND   (NOT "${Git_SubModule}" STREQUAL "")  )


        message(STATUS "[UPDATING SUBMODULE]:- ${Git_SubModule}")
        message(STATUS "[Command Outputs in]:- ${CMAKE_CURRENT_SOURCE_DIR}/.forge/REY_FetchV4_git_submodule_stdout.log")
    execute_process(
        COMMAND             git submodule init
        COMMAND             git submodule update
        WORKING_DIRECTORY ${Git_SubModule}

        OUTPUT_FILE     ${CMAKE_CURRENT_SOURCE_DIR}/.forge/REY_FetchV4_git_submodule_stdout.log
        ERROR_FILE      ${CMAKE_CURRENT_SOURCE_DIR}/.forge/REY_FetchV4_git_submodule_stdout.log  
        TIMEOUT 60              # seconds
        COMMAND_ECHO STDOUT     # output's the part after "COMMAND" few lines above
    )
        message(STATUS "Updating Done")

        add_subdirectory(${Git_SubModule})    #Output:- ${Target_Name}


elseif(  (DEFINED Zip_Links)   AND   (NOT "${Zip_Links}" STREQUAL "")  )

    list(LENGTH Zip_Links N)
    math(EXPR N "${N} - 1")

    set(loopStep 3)
    foreach(i RANGE 0 ${N} ${loopStep})
        math(EXPR j "${i} + 1")
        math(EXPR k "${i} + 2")
        list(GET Zip_Links ${i} LINK)
        list(GET Zip_Links ${j} SAVE_DIR)
        list(GET Zip_Links ${k} FILE_NAME)
        
        message(STATUS "                        ")
        message(STATUS "Link: ${LINK}")
        message(STATUS "Save_Dir: ${SAVE_DIR}")
        message(STATUS "File_Name:- ${FILE_NAME}")
        message(STATUS "                        ")
        
        if(NOT EXISTS ${SAVE_DIR}/${FILE_NAME})
            # Download the zip file
            message(STATUS "Downloading File")
            file(DOWNLOAD ${LINK} ${SAVE_DIR}/${FILE_NAME})

            # Extract the zip file
            message(STATUS "UnZipping File")
            if(WIN32)
                message(STATUS "Windows PowerShell")
                execute_process(
                    COMMAND powershell -Command "Expand-Archive -Path ${SAVE_DIR}/${FILE_NAME} -DestinationPath ${SAVE_DIR} -Force"
                    RESULT_VARIABLE   result
                    OUTPUT_FILE       ${FILE_NAME}.unzip.log  ERROR_FILE      ${FILE_NAME}.unzip.log
                    WORKING_DIRECTORY ${SAVE_DIR}
                )
            else()
                message(STATUS "unix 'unzip' command")
                execute_process(
                    COMMAND unzip -o -d ${SAVE_DIR} ${SAVE_DIR}/${FILE_NAME}
                    # -o means overwrite
                    # -o option should be placed immediately after the unzip command
                    # -d means directory to unzip into
                    RESULT_VARIABLE result
                    OUTPUT_FILE       ${FILE_NAME}.unzip.log  ERROR_FILE      ${FILE_NAME}.unzip.log
                    WORKING_DIRECTORY ${SAVE_DIR}
                )
            endif()
        endif()

        if(result)
            message(FATAL_ERROR "Failed to extract ${SAVE_DIR}/${FILE_NAME}")
        endif()
    endforeach()

else()



    if( (NOT EXISTS ${REY_FETCH_${TN}_BASE_DIR}/${Git_CloneDir_Name}) )
        message(STATUS "Fetching ${Git_Link}"   "inside ${REY_FETCH_${TN}_BASE_DIR}")
        message(STATUS "Download Progress logged inside ${REY_FETCH_${TN}_BASE_DIR}/${TN}_Download_stdout.log ")

            execute_process(
                #COMMAND powershell -Command "Start-Process git -ArgumentList 'clone https://github.com/fmtlib/fmt' 
                #                   -NoNewWindow -RedirectStandardOutput hoga.txt -RedirectStandardError hoga.txt -Wait"
                # https://www.baeldung.com/linux/git-clone-redirect-output-file
                #COMMAND cmd /c "git clone --progress ${Git_Link} ${Git_CloneDir_Name} > ${TN}_Download.log 2>&1"
                 COMMAND         git clone --progress ${Git_Link} ${Git_CloneDir_Name}

                #COMMAND        "git clone https://github.com/fmtlib/fmt"
                # With Quotation marks, it doesn't redirect stdout to OUTPUT_FILE/VARIABLE

                WORKING_DIRECTORY ${REY_FETCH_${TN}_BASE_DIR}

                # OUTPUT_VARIABLE tmp_stdout               ERROR_VARIABLE tmp_stdout
                  OUTPUT_FILE     fmt_Download_stdout.log  ERROR_FILE     fmt_Download_stdout.log   
                # Both doesn't work @ the same time

                RESULT_VARIABLE result_code

                TIMEOUT 10              # seconds
                COMMAND_ECHO STDOUT     # output's the part after "COMMAND" few lines above
            )

        if (result_code NOT EQUAL 0)
            message(FATAL_ERROR "git clone ${Git_Link} failed.... check ${REY_FETCH_${TN}_BASE_DIR}/fmt_Download_stdout.log")
        endif()
        #file(READ "${REY_FETCH_${TN}_BASE_DIR}/${TN}_Download_stdout.log" tmp_stdout)
        #message(STATUS "tmp_stdout:- ${tmp_stdout}")
         message(STATUS "Fetching Done")


        add_subdirectory(${REY_FETCH_${TN}_BASE_DIR}/${Git_CloneDir_Name})    #Output:- ${Target_Name}
    else()
        set(GitHub_FILES_isOK TRUE)
        foreach(file_x ${Git_CheckFiles})
            if(NOT EXISTS "${REY_FETCH_${TN}_BASE_DIR}/${file_x}")
                set(GitHub_FILES_isOK FALSE)

                message(STATUS "[REY_FetchV3_${TN}]")
                message(STATUS "     REY_FETCH_${TN}_BASE_DIR:- ${REY_FETCH_${TN}_BASE_DIR}")
                message(STATUS "dA = REY_FETCH_${TN}_BASE_DIR/${Git_CloneDir_Name} ----> EXISTS")
                message(STATUS "             Git_CheckFiles --> ${file_x} ----> DOESN't EXIST")
                message(STATUS "                                     ")
                message(STATUS "As Long as 'dA' exists ---> `git clone ${Git_Link}` won't work")

                message(FATAL_ERROR "ERROR INFO Has been Logged above\n
                                     ERROR:- REY_FETCH_${TN}_BASE_DIR/${Git_CloneDir_Name} exists, but it's not a proper GIT CLONE\n
                                     see .REY_FetchV3.cmake TOP Documentation part for INPUT-Settings/Variables")
            endif()
        endforeach()
        add_subdirectory(${REY_FETCH_${TN}_BASE_DIR}/${Git_CloneDir_Name})    #Output:- ${Target_Name}
    endif()



endif()