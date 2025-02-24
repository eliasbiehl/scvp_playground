#ifndef DFLIP_H
#define DFLIP_H

#include <systemc.h>

SC_MODULE(dflip){
    private:

    public:

    sc_in<int> D;
    sc_in<bool> reset;
    sc_in<bool> clk;
    sc_out<int> Q;

    SC_CTOR(dflip) : D("D"), Q("Q"), clk("CLK"), reset("RESET")  {
        SC_METHOD(process);
        sensitive << clk.pos() << reset;
    }

    void process(){
        if (reset){
            Q.write(0);
        } else {
            Q.write(D.read());
        }
    }
};

#endif // DFLIP_H