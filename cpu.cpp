
#include "cpu.h"

void allocateRegisters(int);
void testingRegisters();

void CPUconnection(int maxtime, int write_cpu_ram, int read_ram_cpu){
    allocateRegisters(maxtime);

    
}





















void allocateRegisters(int maxtime){
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
