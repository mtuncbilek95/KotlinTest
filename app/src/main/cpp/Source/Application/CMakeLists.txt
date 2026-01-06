cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

file(GLOB_RECURSE SUBDIRECTORIES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SUBDIRECTORIES})
add_library(Application STATIC ${SUBDIRECTORIES})

target_include_directories(Application PRIVATE "${CMAKE_SOURCE_DIR}/Source")
target_link_libraries(Application PUBLIC Runtime)

find_package(game-activity REQUIRED CONFIG)
target_link_libraries(Application PUBLIC game-activity::game-activity_static)