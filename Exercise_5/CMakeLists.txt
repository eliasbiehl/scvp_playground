cmake_minimum_required(VERSION 3.10)



add_executable(Exercise_5
    main.cpp
    kpn.cpp
)

target_include_directories(Exercise_5
    PRIVATE ${SYSTEMC_INCLUDE}
)

target_link_libraries(Exercise_5
    PRIVATE ${SYSTEMC_LIBRARY}
)





