cmake_minimum_required(VERSION 3.10)



add_executable(Exercise_2
    #nand_main.cpp
    exor_main.cpp
)

target_include_directories(Exercise_2
    PRIVATE ${SYSTEMC_INCLUDE}
)

target_link_libraries(Exercise_2
    PRIVATE ${SYSTEMC_LIBRARY}
)





