#pragma once
#include <systemc.h>

SC_MODULE(RSLatch)
{
    sc_in<bool> A; // Set (S) input: sets the latch when true.
    sc_in<bool> B; // Reset (R) input: resets the latch when true.

    sc_out<bool> D; // Primary latch output.

    sc_signal<bool> C; // Auxiliary signal used for latch feedback

    SC_CTOR(RSLatch) : A("A"), B("B"), D("D"), C("C")
    {
        SC_METHOD(process);
        //sensitive << A << B;
        sensitive << A << B << C <<D;
    }

    void process()
    {
        D.write(!B.read() && C.read()); // Nor Gate
        C.write((A.read() || D.read())); // Nor Gate
    }
};


