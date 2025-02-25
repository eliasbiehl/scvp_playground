#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <tlm.h>
#include <systemc.h>


// TODO: add your code here

// =======================================
// Templated Memory Module for SystemC-TLM
// =======================================
template <unsigned int SIZE = 1024>
class memory : public sc_module,public tlm::tlm_fw_transport_if<> 
{
    private:
        // Internal memory storage (byte-addressable array)
        // Mem size is in template, defaults to 1024
        unsigned char mem[SIZE];

    public:

        // Initiate the Member, TLM target socket
        tlm::tlm_target_socket<> tSocket;

        // Construct the Member, initializing memory
        SC_CTOR(memory) : tSocket("tSocket")
        {   
            // Bind the socket to this class, this memory instance
            // -> incoming transactions use this module's b_transport method
            tSocket.bind(*this);
        }

        // ===================================================
        // Blocking Transport Interface (Handles Reads/Writes)
        // ===================================================
        void b_transport(tlm::tlm_generic_payload &trans, sc_time &delay)
        {
            // Catch memory access out of bounds
            if (trans.get_address() >= SIZE)
            {
                trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
                return;
            }

            // ensure data transfer size is 4 bytes since processor 32-bit and already fixed in processor.h
            // see line 169: trans.set_data_length(4);
            if (trans.get_data_length() != 4)
            {
                trans.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
                return;
            }

            // Handle write transactions
            if (trans.get_command() == tlm::TLM_WRITE_COMMAND)
            {
                // Use get_data_ptr() to access data from trans!!
                // Copy 4 bytes of data from the transaction payload to the memory at the given address
                memcpy( &mem[trans.get_address()], /*Destination with pointer access*/
                        trans.get_data_ptr(), /*Source via Interface Method*/
                        trans.get_data_length()); /*Data Size via Interface Method*/
            }
            else /* If no write -> READ */
            {
                // Memory safe handling of data
                memcpy(trans.get_data_ptr(), 
                        &mem[trans.get_address()], 
                        trans.get_data_length());
            }

            // Add a fixed memory access delay of 20 ns to simulate hardware latency
            delay = delay + sc_time(20, SC_NS);

            // Set response after action to OK
            trans.set_response_status(tlm::TLM_OK_RESPONSE);
        }

        // Dummy method
        virtual tlm::tlm_sync_enum nb_transport_fw(
            tlm::tlm_generic_payload& trans,
            tlm::tlm_phase& phase,
            sc_time& delay )
        {
            SC_REPORT_FATAL(this->name(),"nb_transport_fw is not implemented");
            return tlm::TLM_ACCEPTED;
        }

        // Dummy method
        bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans,
                                tlm::tlm_dmi& dmi_data)
        {
            SC_REPORT_FATAL(this->name(),"get_direct_mem_ptr is not implemented");
            return false;
        }

        // Dummy method
        unsigned int transport_dbg(tlm::tlm_generic_payload& trans)
        {
            SC_REPORT_FATAL(this->name(),"transport_dbg is not implemented");
            return 0;
        }
        
};

#endif // MEMORY_H