#define MEM_SIZE 512
//#define MULTI

#include <iostream>
#include <iomanip>
#include <systemc.h>

#include "memory.h"
#include "processor.h"

#ifndef MULTI
    #include "bus.h"
#else
    #include "bus_multi_socket.h"
#endif


int sc_main (int, char **)
{
    processor cpu0("cpu0", "/Users/eb/Projekte/scvp_playground/Exercise_6/stimuli1.txt", sc_time(1, SC_NS));
    processor cpu1("cpu1", "/Users/eb/Projekte/scvp_playground/Exercise_6/stimuli2.txt", sc_time(1, SC_NS));
    memory<512> memory0("memory0");
    memory<512> memory1("memory1");
    // TODO: add your code here
    #ifdef MULTI
    bus_ms bus0("bus0", MEM_SIZE, SC_ZERO_TIME);
    cpu0.iSocket.bind(bus0.tSocket);
    cpu1.iSocket.bind(bus0.tSocket);
    bus0.iSocket.bind(memory0.tSocket);
    bus0.iSocket.bind(memory1.tSocket);
    #else
    bus<2,2> bus0("bus0", MEM_SIZE, SC_ZERO_TIME);
    cpu0.iSocket.bind(bus0.tSocket[0]);
    cpu1.iSocket.bind(bus0.tSocket[1]);
    bus0.iSocket[0].bind(memory0.tSocket);
    bus0.iSocket[1].bind(memory1.tSocket);
    #endif

    std::cout << std::endl << "Name "
              << std::setfill(' ') << std::setw(10)
              << "Time" << " "
              << std::setfill(' ') << std::setw(5)
              << "CMD" << "   "
              << std::setfill(' ') << std::setw(8)
              << "Address"
              << "   " << std::hex
              << std::setfill(' ') << std::setw(8)
              << "Data"
              << " " << std::endl
              << "-------------------------------------------"
              << std::endl;

    sc_start();

    std::cout << std::endl;
    return 0;
}