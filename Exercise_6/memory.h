#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <tlm.h>
#include <systemc.h>


// TODO: add your code here

template <unsigned int SIZE = 1024>
class memory : sc_module, tlm::tlm_fw_transport_if<> {
    private :
        unsigned char mem[SIZE];
    public :
        tlm::tlm_target_socket<> tSocket;

        SC_CTOR(memory) : tSocket("tSocket") {
            tSocket.bind(*this);
        }

        void b_transport(tlm::tlm_generic_payload &trans, sc_time &delay) {
                if(trans.get_address() >= MEM_SIZE){
                    SC_REPORT_FATAL(this->name(),"Out of Range");
                }

                if (trans.get_command() == tlm::TLM_WRITE_COMMAND){
                    memcpy(&mem[trans.get_address()], 
                    trans.get_data_ptr(), 
                    trans.get_data_length());
                }
                else {
                    memcpy(trans.get_data_ptr(),
                    &mem[trans.get_address()],
                    trans.get_data_length());
                }
                delay = delay + sc_time(20, SC_NS); 

                trans.set_response_status(tlm::TLM_OK_RESPONSE);
        }

        virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& delay ) {
            SC_REPORT_FATAL(this->name(),"nb_transport_fw is not implemented");
            return tlm::TLM_ACCEPTED;
        }

        bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data) {
            SC_REPORT_FATAL(this->name(),"get_direct_mem_ptr is not implemented");
            return false;
        }

        unsigned int transport_dbg(tlm::tlm_generic_payload& trans) {
            SC_REPORT_FATAL(this->name(),"transport_dbg is not implemented");
            return 0;
        }
};
#endif // MEMORY_H