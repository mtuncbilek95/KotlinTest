cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

file(GLOB_RECURSE SUBDIRECTORIES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SUBDIRECTORIES})
add_library(Runtime STATIC ${SUBDIRECTORIES})

target_include_directories(Runtime PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Runtime PUBLIC EGL GLESv3 jnigraphics android log)

find_library(vulkan-lib vulkan)
target_link_libraries(Runtime PUBLIC ${vulkan-lib})