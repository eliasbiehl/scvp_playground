#include <systemc.h>

SC_MODULE(dflipflop) {
    sc_in<unsigned int> D;
    sc_in<bool> clk;
    sc_in<bool> reset;
    sc_out<unsigned int> Q;

    SC_CTOR(dflipflop) : D("D"), Q("Q"), clk("clk"), reset("reset") {
        SC_METHOD(process);
        sensitive << clk.pos() << reset.pos();
    }

    void process() {
        if(reset) {
            Q.write(0);
        }
        else {
            Q.write(D.read());
        }
    }
};