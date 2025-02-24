#ifndef mva
#define mva
#include <systemc.h>
#include "dflip.h"

SC_MODULE(moving_average){
    private:

    public:
    dflip d1, d2, d3;

    sc_in<int> data_in;
    sc_out<float> out;

    sc_in<bool> reset;
    sc_in<bool> clk;

    sc_signal<int> h1, h2, h3, h4;

    SC_CTOR(moving_average) : d1("d1"), d2("d2"), d3("d3"), clk("clk"), data_in("in"), reset("reset") {
        d1.D.bind(data_in);
        d1.Q.bind(h1);
        d1.clk.bind(clk);
        d1.reset.bind(reset);

        d2.D.bind(h1);
        d2.Q.bind(h2);
        d2.clk.bind(clk);
        d2.reset.bind(reset);

        d3.D.bind(h2);
        d3.Q.bind(h3);
        d3.clk.bind(clk);
        d3.reset.bind(reset);

        SC_METHOD(process);
        sensitive << clk.pos();
    }

    void process() {
        if (reset.read()) {
            h1.write(0);
            h2.write(0);
            h3.write(0);
            h4.write(0);
            out.write(0);
        } else {
            out.write((h1.read() + h2.read() + h3.read() + data_in.read()) / 4.0);
            std::cout << out.read() << std::endl;
        }
    }
};
#endif