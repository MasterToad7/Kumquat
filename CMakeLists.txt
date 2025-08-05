cmake_minimum_required(VERSION 3.22.1)
project(kumquat VERSION 1.0)
project(kumquat_util VERSION 1.0)

option(BUILD_UTIL "Build kumquat_util executable" OFF)

add_library(kumquat STATIC src/kqt_sanityCheck.c src/kqt_initialize.c src/kqt_generateSceneHandle.c src/kqt_generateFramebuffer.c src/kqt_setiChannel.c src/kqt_renderFramebuffer.c src/kqt_loadTexture.c deps/glad/glad.c deps/stb/stb_image.c)

target_include_directories(kumquat PUBLIC include deps)

find_package(OpenGL REQUIRED)
target_link_libraries(kumquat OpenGL::GL)

if(BUILD_UTIL)
    include(FetchContent)
    FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG master
    )
    FetchContent_MakeAvailable(glfw)

    add_executable(kumquat_util src/kumquat_util.c)
    target_link_libraries(kumquat_util kumquat glfw OpenGL::GL)
    target_include_directories(kumquat_util PUBLIC include deps)
endif()