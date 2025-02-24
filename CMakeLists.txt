cmake_minimum_required(VERSION 3.10)

project(SCVP_Playground)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED True)

find_library(SYSTEMC_LIBRARY 
    NAMES systemc
    PATHS /Users/eb/systemc-2.3.3/lib
)
include_directories(/Users/eb/systemc-2.3.3/)

find_library(SYSTEMC_AMS_LIBRARY 
    NAMES systemc-ams
    PATHS /Users/eb/systemc-ams/lib
)
include_directories(/Users/eb/systemc-ams/)



set(SYSTEMC_INCLUDE /Users/eb/systemc-2.3.3/include)
set(SYSTEMC_AMS_INCLUDE /Users/eb/systemc-ams/include)


add_subdirectory(Exercise_2)

add_subdirectory(Exercise_3)

add_subdirectory(Exercise_4)

add_subdirectory(Exercise_5)

add_subdirectory(Exercise_6)

add_subdirectory(Exercise_8)