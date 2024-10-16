cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(treasure_chest)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(observer)
add_subdirectory(sync_queue)
add_subdirectory(producer_consumer)

