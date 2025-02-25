#include <systemc.h>

#include "dflip.h"
#include "stim.h"


// ============================
// Moving Average Filter Module
// ============================
SC_MODULE(movAvg) {
    // Input and Output Ports
    sc_in<unsigned int> data;
    sc_in<bool> clk, reset;
    sc_out<float> avg; // Moving average output

    // Three D Flip-Flop instances for delaying data
    dflipflop q1, q2, q3; // Represents a delay chain (pipeline)
    sc_signal<unsigned int> h1, h2, h3; // Intermediate signals for storing delayed data

    // Constructor for initialization and process registration
    SC_CTOR(movAvg) : data("data"), clk("clk"), reset("reset"), avg("avg"), q1("q1"), q2("q2"), q3("q3")
    {
        // Connecting input data to the first flip-flop
        q1.D.bind(data);
        q1.Q.bind(h1);
        q1.clk.bind(clk);
        q1.reset.bind(reset);

        // Connecting delayed data to the second flip-flop
        q2.D.bind(h1);
        q2.Q.bind(h2);
        q2.clk.bind(clk);
        q2.reset.bind(reset);

        // Connecting further delayed data to the third flip-flop
        q3.D.bind(h2);
        q3.Q.bind(h3);
        q3.clk.bind(clk);
        q3.reset.bind(reset);

        // Registering the compute method, sensitive to positive clock edges and reset
        SC_METHOD(compute);
        sensitive << clk.pos() << reset.pos();
    }

    // Compute method for calculating the moving average
    void compute() {
        unsigned int val_a, val_b, val_c, val_d; // Variables to hold input and delayed data values

        // Reset condition: Clear the output average to zero
        if(reset) {
            avg.write(0);
        }
        else {
            // Read the most recent data values from the input and delay registers
            val_a = data.read();
            val_b = h1.read();
            val_c = h2.read();
            val_d = h3.read();

            // Calculate the average of the current and last three data samples
            avg.write((val_a + val_b + val_c + val_d) / 4.0);
        }
        // Debugging output for tracing the internal states
        std::cout << "in:" << val_a << " q1: " << val_b << " q2: " << val_c << " q3: " << val_d << std::endl;
        std::cout << avg.read() << std::endl;
    }
};

// =============================
// SystemC Main Function (sc_main)
// =============================

int sc_main(int, char**)
{
    // Clock signal with a period of 1 ns, 50% duty cycle
    sc_clock clk("clk", 1, SC_NS, 0.5, 0, SC_NS, true);

    // Signals for reset, output average, and input data
    sc_signal<bool> rst;
    sc_signal<float> out;
    sc_signal<unsigned int> data;

    // Stimulus generator to drive input data and reset signals
    stim Stim1("Stimulus");
    Stim1.A(data);
    Stim1.B(rst);
    Stim1.clk(clk);

    // Instantiate the Moving Average module
    movAvg mv1("mv1");
    mv1.clk(clk);
    mv1.reset(rst);
    mv1.data(data);
    mv1.avg(out);


    sc_start();

    return 0;
}