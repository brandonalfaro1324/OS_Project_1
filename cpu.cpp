
#include "cpu.h"

// NOTE:
// write_cpu_ram <= fd_cpu_ram[0] <= writing from CPU to RAM
// read_ram_cpu <= fd_ram_cpu[1] <= reading from RAM to CPU

void allocateRegisters(int, int, int);
void computeInstruction();

void testingRegisters();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////

// Begin running the CPU
void CPUrunning(int maxtime, int write_cpu_ram, int read_ram_cpu){
    
    // Allocate Registers
    allocateRegisters(maxtime, write_cpu_ram, read_ram_cpu); 

    //while(cpu_flagtracker->CPU_EXIT == false){
        // Computer instruction 
        computeInstruction();
    //}

    ////////////////////////////////
    // Temporary code to end RAM
    char send_test = 'e';
    write(write_cpu_ram , &send_test, sizeof(send_test));
    ////////////////////////////////

    // Delete and set NULL to registers
    delete registers;
    delete cpu_flagtracker;

    registers = NULL;
    cpu_flagtracker = NULL;
}

// Compute instructions by retrieving data from RAM
void computeInstruction(){

    // Instruct read case in RAM and send current PC
    write(cpu_flagtracker->W_CPU_RAM, "r", sizeof(char));
    write(cpu_flagtracker->W_CPU_RAM, &(registers->PC), sizeof(registers->PC));

    // Increase PC
    registers->PC++;

    // Read data from RAM and store it in IR register
    read(cpu_flagtracker->R_RAM_CPU, &(registers->IR), sizeof(registers->IR));
}
////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HELPER FUNCTIONS

// Examine data for "registers"
void testingRegisters(){
 printf(" PC %d\n SP %d\n IR %d\n AC %d\n X %d\n Y %d\n", 
    registers->PC,
    registers->SP,
    registers->IR,
    registers->AC,
    registers->X,
    registers->Y);
}

// Intilize "registers" and set data to each register
void allocateRegisters(int maxtime, int write_cpu_ram, int read_ram_cpu){

    // Allocating registers and setting correct values to registers
    registers = new Registers;

    registers->PC = 0;
    registers->SP = 1000;
    registers->IR = 0;
    registers->AC = 0;
    registers->X = 0;
    registers->Y = 0;

    // Allocating flags and variables
    cpu_flagtracker = new CpuDataFlags;
    
    cpu_flagtracker->CURRENT_TIME = 0;
    cpu_flagtracker->MAXTIME = maxtime;
    cpu_flagtracker->CPU_EXIT = false;
    cpu_flagtracker->W_CPU_RAM = write_cpu_ram;
    cpu_flagtracker->R_RAM_CPU = read_ram_cpu;
}