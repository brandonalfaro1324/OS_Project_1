
#include "cpu.h"

// NOTE:
// write_cpu_ram <= fd_cpu_ram[0] <= writing from CPU to RAM
// read_ram_cpu <= fd_ram_cpu[1] <= reading from RAM to CPU

void allocateRegisters(int);
void testingRegisters();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////
void CPUconnection(int maxtime, int write_cpu_ram, int read_ram_cpu){
    
    // Allocate Registers
    allocateRegisters(maxtime); 

    /* TESTIG CONNECTION */
    bool send_test = true;
    write(write_cpu_ram , &send_test, sizeof(send_test));
    /* TESTIG CONNECTION */


    // Delete and set NULL to registers
    delete registers;
    registers = NULL;
}
////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HELPER FUNCTIONS

// Examine data for "registers"
void testingRegisters(){
 printf(" PC %d\n SP %d\n IR %d\n AC %d\n X %d\n Y %d\n TIME %d\n MAXTIME %d\n", 
    registers->PC,
    registers->SP,
    registers->IR,
    registers->AC,
    registers->X,
    registers->Y,
    registers->TIME,
    registers->MAXTIME);
}

// Intilize "registers" and set data to each register
void allocateRegisters(int maxtime){

    // Allocating registers and setting necessary values to registers
    registers = new Registers;

    registers->PC = 0;
    registers->SP = 1000;
    registers->IR = 0;
    registers->AC = 0;
    registers->X = 0;
    registers->Y = 0;
    registers->TIME = 0;
    registers->MAXTIME = maxtime;
}