cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(KotlinTest LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SHARED_LINKER_FLAGS
        "${CMAKE_SHARED_LINKER_FLAGS} -u Java_com_google_androidgamesdk_GameActivity_initializeNativeCode")

add_subdirectory(Source/Runtime)
add_subdirectory(Source/Application)
add_subdirectory(Source/Player)