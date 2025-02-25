#include <iostream>
#include <iomanip>
#include <systemc.h>

#include "memory.h"
#include "processor.h"
#include "bus.h"

#include <tlm_utils/multi_passthrough_initiator_socket.h> // allows multiple initiators (masteres) 
#include <tlm_utils/multi_passthrough_target_socket.h> // allows multiple targets (slaves)

// ========================================
// Entry Point for SystemC Simulation
// ========================================
int sc_main (int, char **)
{
    // TODO: add your code here


    // ==========================
    // Instantiate Components
    // ==========================
    // Two processors (or CPUs) that will generate transactions
    // Each processor reads input commands (stimuli) from a text file
    processor cpu0("cpu0", "stimuli1.txt", sc_time(1, SC_NS));
    processor cpu1("cpu1", "stimuli2.txt", sc_time(1, SC_NS));

    // A bus that connects multiple processors and memories using TLM sockets
    bus bus0("bus0");

    memory<512> memory0("memory0");
    memory<512> memory1("memory1");

    // Connecting CPU initiator sockets to the bus target sockets
    cpu0.iSocket.bind(bus0.tSocket[0]);
    cpu1.iSocket.bind(bus0.tSocket[1]);

    // Connecting the bus initiator sockets to the memory target sockets
    bus0.iSocket[0].bind(memory0.tSocket);
    bus0.iSocket[1].bind(memory1.tSocket);

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