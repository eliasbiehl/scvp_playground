cmake_minimum_required(VERSION 3.10)



add_executable(Exercise_4
    main.cpp
)    

target_include_directories(Exercise_4
    PRIVATE ${SYSTEMC_INCLUDE}
)

target_link_libraries(Exercise_4
    PRIVATE ${SYSTEMC_LIBRARY}
)





