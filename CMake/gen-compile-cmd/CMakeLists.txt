cmake_minimum_required (VERSION 3.10)

project (main)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

aux_source_directory (. SOURCE_FILE)

add_executable (main ${SOURCE_FILE})
