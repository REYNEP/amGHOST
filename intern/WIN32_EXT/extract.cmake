# Extract the zip file
set(SAVE_DIR ${CMAKE_CURRENT_LIST_DIR})
set(ZIP_NAME "WIN32_EXT.zip")

if(NOT EXISTS ${SAVE_DIR}/spy.h)

    message(STATUS "UnZipping ${SAVE_DIR}/${ZIP_NAME}")
    if(WIN32)
        message(STATUS "Windows PowerShell")
        execute_process(
            COMMAND powershell -Command "Expand-Archive -Path ${SAVE_DIR}/${ZIP_NAME} -DestinationPath ${SAVE_DIR} -Force"
            RESULT_VARIABLE   result
            OUTPUT_FILE       ${ZIP_NAME}.unzip.log  ERROR_FILE      ${ZIP_NAME}.unzip.log
            WORKING_DIRECTORY ${SAVE_DIR}
        )
    else()
        message(STATUS "unix 'unzip' command")
        execute_process(
            COMMAND unzip -o -d ${SAVE_DIR} ${SAVE_DIR}/${ZIP_N@AME}
            # -o means overwrite
            # -o option should be placed immediately after the unzip command
            # -d means directory to unzip into
            RESULT_VARIABLE result
            OUTPUT_FILE       ${ZIP_NAME}.unzip.log  ERROR_FILE      ${ZIP_NAME}.unzip.log
            WORKING_DIRECTORY ${SAVE_DIR}
        )
    endif()

endif()