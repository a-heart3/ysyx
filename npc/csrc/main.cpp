#include "Vtop.h"
#include <nvboard.h>
#include "verilated_fst_c.h"
#include "verilated.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void nvboard_bind_all_pins(TOP_NAME* top);

int main(int argc, char** argv) {
	VerilatedContext* contextp = new VerilatedContext;
	contextp->commandArgs(argc, argv);
	Vtop* top = new Vtop{contextp};
	Verilated::traceEverOn(true);
	VerilatedFstC* tfp = new VerilatedFstC;
	nvboard_bind_all_pins(top);
	nvboard_init();
	while(1) {
		top->eval();
		nvboard_update();
	}
	delete top;
	delete contextp;
	return 0;
}
