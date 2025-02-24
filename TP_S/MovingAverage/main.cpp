#include <systemc.h>

#include "dflip.h"
#include "stim.h"

SC_MODULE(movAvg) {
    sc_in<unsigned int> data;
    sc_in<bool> clk, reset;
    sc_out<float> avg;
    dflipflop q1, q2, q3;
    sc_signal<unsigned int> h1, h2, h3;

    SC_CTOR(movAvg) : data("data"), clk("clk"), reset("reset"), avg("avg"), q1("q1"), q2("q2"), q3("q3")
    {
        q1.D.bind(data);
        q1.Q.bind(h1);
        q1.clk.bind(clk);
        q1.reset.bind(reset);

        q2.D.bind(h1);
        q2.Q.bind(h2);
        q2.clk.bind(clk);
        q2.reset.bind(reset);

        q3.D.bind(h2);
        q3.Q.bind(h3);
        q3.clk.bind(clk);
        q3.reset.bind(reset);

        SC_METHOD(compute);
        sensitive << clk.pos() << reset.pos();
    }

    void compute() {
        unsigned int val_a, val_b, val_c, val_d;
        if(reset) {
            avg.write(0);
        }
        else {
            val_a = data.read();
            val_b = h1.read();
            val_c = h2.read();
            val_d = h3.read();
            avg.write((val_a + val_b + val_c + val_d) / 4.0);
        }
        std::cout << "in:" << val_a << " q1: " << val_b << " q2: " << val_c << " q3: " << val_d << std::endl;
        std::cout << avg.read() << std::endl;
    }
};

int sc_main(int, char**)
{
    sc_clock clk("clk", 1, SC_NS, 0.5, 0, SC_NS, true);

    sc_signal<bool> rst;
    sc_signal<float> out;
    sc_signal<unsigned int> data;

    stim Stim1("Stimulus");
    Stim1.A(data);
    Stim1.B(rst);
    Stim1.clk(clk);

    movAvg mv1("mv1");
    mv1.clk(clk);
    mv1.reset(rst);
    mv1.data(data);
    mv1.avg(out);


    sc_start();

    return 0;
}