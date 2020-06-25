cmake_minimum_required(VERSION 3.15)
set(NAME open_gl_test)
project(${NAME} VERSION 0.0.1 LANGUAGES CXX DESCRIPTION "A unit conversion library")

# Configure the release by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE release)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)


include_directories(${PROJECT_SOURCE_DIR})
# WARNING this is set to the current architecture
set(CMAKE_CXX_FLAGS "-Wall -std=c++17 -march=native")
message("Build type " ${CMAKE_BUILD_TYPE})

# Configure threading
#find_package(Threads REQUIRED)


if(${CMAKE_BUILD_TYPE} STREQUAL release)
    message("Building in release mode")
    #add_executable()
    # target_compile_options()
elseif(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    message("Building in debug mode")
    #enable_testing()
    #include(GoogleTest)
    #message("Found GoogleTests")
    #message("Building TESTS")
    add_compile_options(-ggdb3 -O0 -fno-eliminate-unused-debug-symbols)
    add_subdirectory(src)
    #add_subdirectory(tests)

endif()
