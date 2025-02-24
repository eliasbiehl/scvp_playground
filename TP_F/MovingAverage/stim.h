#ifndef STIMULUS_H
#define STIMULUS_H

#include <systemc.h>

SC_MODULE(stim)
{
public:
    sc_out<bool> B;
    sc_out<int> A;
    sc_in<bool> clk;

    SC_CTOR(stim)
    {
        SC_THREAD(StimGen);
        sensitive << clk.pos();
    }

private:
    void StimGen()
    {
        wait(SC_ZERO_TIME);
        A.write(2);
        B.write(false);
        wait();
        A.write(4);
        B.write(false);
        wait();
        A.write(6);
        B.write(false);
        wait();
        A.write(8);
        B.write(false);
        wait();
        A.write(10);
        B.write(false);
        wait();
        sc_stop();
    }
};

#endif