#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main (int argc, char **argv, char**env){
    int i;
    int clk;
    
    Verilated::commandArgs(argc, argv);
    //init top verilog instance 
    Vcounter* top = new Vcounter;
    //init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp,99);
    tfp->open("counter.vcd");

    //init Vbuddy
    if(vbdOpen()!=1) return(-1);
    vbdHeader("Lab 1: Counter");

    //initalize simulation inputs 
    top->clk = 1;
    top->rst = 1;
     // remove enable 
    //run simulation for many clock cycles 
   

        //dump variables into VCD file and toggle clock 
        for (i=0; i<300; i++){
            for (clk=0;clk<2;clk++){
                tfp->dump(2*i+clk); //unit is in ps!!!
                top->clk = !top->clk;
                top->eval();
            }
            // Send coint value to Vbuddy
            vbdHex(4, (int(top->count)>>12)& 0xF);
            vbdHex(3, (int(top->count)>>8)& 0xF);
            vbdHex(2, (int(top->count)>>4)& 0xF);
            vbdHex(1, int(top->count) & 0xF);
            top->v = vbdValue();
            vbdSetMode(1);
            //keeps the counter running when value is set
            // add top v into the clock cycle so that you vdc value updates with the clock 
            vbdCycle(i+1);


            top->rst = (i<2)|(i==15);
            top->ld =  vbdFlag();
            if (Verilated::gotFinish()) exit(0);
    }

    vbdClose(); //+++
    tfp->close();
    exit(0);
}