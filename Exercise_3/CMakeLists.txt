cmake_minimum_required(VERSION 3.10)



add_executable(Exercise_3
    main.cpp
    state_machine.cpp
    stimuli.cpp
)

target_include_directories(Exercise_3
    PRIVATE ${SYSTEMC_INCLUDE}
)

target_link_libraries(Exercise_3
    PRIVATE ${SYSTEMC_LIBRARY}
)





