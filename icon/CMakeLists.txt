cmake_minimum_required(VERSION 3.13)

set(BASE_DIR "hicolor")
set(RESOLUTIONS 16 22 32 48 256 512)
foreach(RESOLUTION ${RESOLUTIONS})
    set(OUTPUT_DIR "${BASE_DIR}/${RESOLUTION}x${RESOLUTION}/apps")
    set(OUTPUT_PNG "${OUTPUT_DIR}/${CMAKE_PROJECT_NAME}.png")
    add_custom_command(OUTPUT "${OUTPUT_PNG}"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${OUTPUT_DIR}"
        COMMAND inkscape -o "${OUTPUT_PNG}" -w ${RESOLUTION} -h ${RESOLUTION} "${CMAKE_CURRENT_SOURCE_DIR}/icon.svg"
        MAIN_DEPENDENCY "icon.svg")
    add_custom_target("${RESOLUTION}-png" ALL DEPENDS "${OUTPUT_PNG}")
    list(APPEND png_targets "${RESOLUTION}-png")
    list(APPEND png_files "${OUTPUT_PNG}")
endforeach()
add_custom_target("app_icon" ALL DEPENDS "app.ico")
add_custom_command(OUTPUT "app.ico"
    COMMAND convert ${png_files} "app.ico" 
    DEPENDS ${png_targets})
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${BASE_DIR}" DESTINATION "share/icons")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_library("win_resource" OBJECT)
    target_sources("win_resource" PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/res.rc")
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/res.rc"
        COMMAND ${CMAKE_COMMAND} -E echo "108 ICON \\\"app.ico\\\"" > "${CMAKE_CURRENT_BINARY_DIR}/res.rc")
    add_dependencies("win_resource" "app_icon")
endif()
