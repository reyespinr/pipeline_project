cmake_minimum_required(VERSION 3.16)
project(pipeline_project)
enable_testing()

# In CMake 3.21, PROJECT_IS_TOP_LEVEL is provided, so if block can be removed when the
# project upgrades to that CMake version
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(PROJECT_IS_TOP_LEVEL TRUE CACHE INTERNAL "")
else()
    set(PROJECT_IS_TOP_LEVEL FALSE CACHE INTERNAL "")
endif()

option(pipeline_project_ENABLE_TESTING "Enable unit tests for pipeline_project" ${PROJECT_IS_TOP_LEVEL})
option(pipeline_project_EXPORT_COMPILE_COMMANDS "Export compile commands" ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ${pipeline_project_EXPORT_COMPILE_COMMANDS})

# Add C++11 support
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(dependencies.cmake)

add_subdirectory(src)

if(pipeline_project_ENABLE_TESTING OR PROJECT_IS_TOP_LEVEL)
    add_subdirectory(test)
endif()
