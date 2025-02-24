cmake_minimum_required(VERSION 3.10)



add_executable(Exercise_6
    main.cpp
    memory.h
    processor.h
    bus.h
    bus_multi_socket.h

    stimuli1.txt
    stimuli2.txt
)

target_include_directories(Exercise_6
    PRIVATE ${SYSTEMC_INCLUDE}
)

target_link_libraries(Exercise_6
    PRIVATE ${SYSTEMC_LIBRARY}
    #/Users/eb/systemc-2.3.3/lib/libsystemc.dylib
)



