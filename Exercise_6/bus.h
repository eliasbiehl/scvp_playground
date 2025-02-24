#ifndef BUS_H
#define BUS_H

#include <iostream>
#include <systemc.h>
#include <tlm.h>

#include <tlm_utils/multi_passthrough_initiator_socket.h>
#include <tlm_utils/multi_passthrough_target_socket.h>


// TODO: add your code here
template<unsigned int iSockets = 1, unsigned int tSockets = 1>
class bus : sc_module, tlm::tlm_fw_transport_if<>, tlm::tlm_bw_transport_if<>
{
    public:
    tlm::tlm_initiator_socket<> iSocket[iSockets];
    tlm::tlm_target_socket<> tSocket[tSockets];
    
    SC_HAS_PROCESS(bus);
    bus(sc_module_name name, uint64_t memSize, sc_time routingDelay) : sc_module(name), _memSize(memSize), _routingDelay(routingDelay) {
            for(int i = 0; i < iSockets; i++) {
                iSocket[i].bind(*this);
            }
            for(int j = 0; j < tSockets; j++) {
                tSocket[j].bind(*this);
            }
    }

    uint64_t _memSize; // Size of each memory
    sc_time _routingDelay; // Routing delay

    void b_transport(tlm::tlm_generic_payload &trans, sc_time &delay) {
        // add Bus delay
        delay += _routingDelay;

        // compute Initiator Socket
        unsigned int socket_num = trans.get_address() / _memSize;
        
        // ensure target exists
        if (socket_num > iSockets)
        {
            trans.set_response_status( tlm::TLM_ADDRESS_ERROR_RESPONSE );
            return;
        }
        
        // set new address according to mapping
        trans.set_address(trans.get_address() % _memSize);

        // send b_transport to target
        iSocket[socket_num]->b_transport(trans, delay);
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

    // Dummy method:
    void invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                   sc_dt::uint64 end_range)
    {
        SC_REPORT_FATAL(this->name(),"invalidate_direct_mem_ptr not implement");
    }

    // Dummy method:
    tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload& trans,
                                        tlm::tlm_phase& phase,
                                        sc_time& delay)
    {
        SC_REPORT_FATAL(this->name(),"nb_transport_bw is not implemented");
        return tlm::TLM_ACCEPTED;
    }

};

#endif // BUS_H