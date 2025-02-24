cmake_minimum_required(VERSION 3.10)



add_executable(Exercise_8
    main.cpp
    initiator.h
    target.h
    memory_manager.cpp
    memory_manager.h
    util.h
    tlm2_base_protocol_checker.h
)

target_include_directories(Exercise_8
    PRIVATE ${SYSTEMC_INCLUDE}
)

target_link_libraries(Exercise_8
    PRIVATE ${SYSTEMC_LIBRARY}
    #/Users/eb/systemc-2.3.3/lib/libsystemc.dylib
)



