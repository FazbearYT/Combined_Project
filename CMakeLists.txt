cmake_minimum_required(VERSION 3.10)
project(CombinedGraphicsLab)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

set(FREEGLUT_INCLUDE_DIR "C:/vcpkg/installed/x64-windows/include")
set(FREEGLUT_LIBRARY "C:/vcpkg/installed/x64-windows/lib/freeglut.lib")
set(FREEGLUT_DLL "C:/vcpkg/installed/x64-windows/bin/freeglut.dll")

if(NOT EXISTS ${FREEGLUT_LIBRARY})
    message(FATAL_ERROR "freeglut.lib not found at ${FREEGLUT_LIBRARY}")
endif()

if(NOT EXISTS "${FREEGLUT_INCLUDE_DIR}/GL/freeglut.h")
    message(FATAL_ERROR "freeglut.h not found at ${FREEGLUT_INCLUDE_DIR}/GL/")
endif()

file(GLOB CORE_SOURCES "core/*.cpp")
file(GLOB MODULE_SOURCES "modules/*/*.cpp")

add_executable(LabApp
    ${CORE_SOURCES}
    ${MODULE_SOURCES}
)

target_include_directories(LabApp PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/core
    ${FREEGLUT_INCLUDE_DIR}
)

target_link_libraries(LabApp PRIVATE
    ${FREEGLUT_LIBRARY}
    OpenGL::GL
    opengl32.lib
    glu32.lib
)

add_custom_command(TARGET LabApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${FREEGLUT_DLL}"
    $<TARGET_FILE_DIR:LabApp>
)

message(STATUS "=== FreeGLUT Configuration ===")
message(STATUS "Include: ${FREEGLUT_INCLUDE_DIR}")
message(STATUS "Library: ${FREEGLUT_LIBRARY}")
message(STATUS "DLL: ${FREEGLUT_DLL}")
message(STATUS "==============================")