cmake_minimum_required(VERSION 3.13)
enable_testing()

file(GLOB sources "./*.cpp")
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(exe_type "WIN32")
else()
    set(exe_type "")
endif()

find_package(SDL2 REQUIRED)
find_package(GLEW 2.0 REQUIRED)

add_executable("${CMAKE_PROJECT_NAME}" ${exe_type} ${sources})
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE
    ${SDL2_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
)
target_compile_definitions("${CMAKE_PROJECT_NAME}"
    PRIVATE PROJECT_VERSION="${CMAKE_PROJECT_VERSION}"
)
set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 17)
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries("${CMAKE_PROJECT_NAME}" pthread GL)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries("${CMAKE_PROJECT_NAME}" win_resource opengl32)
    install(FILES $<TARGET_RUNTIME_DLLS:${CMAKE_PROJECT_NAME}> TYPE BIN)
    set(glew_dll "bin/Release/x64/glew32.dll")
    find_path(glew_dll_parent "${glew_dll}")
    install(FILES "${glew_dll_parent}/${glew_dll}" TYPE BIN)
endif()
target_link_libraries("${CMAKE_PROJECT_NAME}" resource ${GLEW_LIBRARIES} SDL2::SDL2main SDL2::SDL2)
install(TARGETS "${CMAKE_PROJECT_NAME}" DESTINATION "bin")
