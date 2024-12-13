#include "Vtop.h"
#include "verilated_fst_c.h"
#include "verilated.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char** argv) {
	VerilatedContext* contextp = new VerilatedContext;
	contextp->commandArgs(argc, argv);
	Vtop* top = new Vtop{contextp};
	Verilated::traceEverOn(true);
	VerilatedFstC* tfp = new VerilatedFstC;
	top->trace(tfp, 1);
	tfp->open("simx.fst");
	while(1) {
		int a = rand() & 1;	
		int b = rand() & 1;
		top->a = a;
		top->b = b;
		top->eval();
		printf("a = %d, b = %d, f = %d\n", a, b, top->f);
		assert(top->f == (a ^ b));
		contextp->timeInc(1);
		tfp->dump(contextp->time());
		if(contextp->time() == 60) break;
	}
	tfp->close();
	delete top;
	delete contextp;
	return 0;
}
