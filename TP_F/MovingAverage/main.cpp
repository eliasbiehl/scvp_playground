#include <systemc.h>
#include "Moving_Average.h"
#include "dflip.h"
#include "stim.h"

int sc_main(int, char**) {
    sc_clock clk("clk", 1, SC_NS, 0.5, 0, SC_NS, true);
    
    sc_signal<bool> rst;
    sc_signal<float> out;
    sc_signal<int> data;

    stim Stim1("Stimulus");
    Stim1.A(data);
    Stim1.B(rst);
    Stim1.clk(clk);

    moving_average mv1("mv1");
    mv1.clk(clk);
    mv1.reset(rst);
    mv1.data_in(data);
    mv1.out(out);

    sc_start();

    return 0;
}