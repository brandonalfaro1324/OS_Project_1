
#include "cpu.h"

// NOTE:
// write_cpu_ram <= fd_cpu_ram[0] <= writing from CPU to RAM
// read_ram_cpu <= fd_ram_cpu[1] <= reading from RAM to CPU

void allocateRegisters(int, int, int);
int gatherData(int);

void testingRegisters(int);
void computeInstruction();
void writeData(int, int);


int PRINT_DATA = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS THAT MAKE UP THE CPU

// Begin running the CPU
void CPUrunning(int maxtime, int write_cpu_ram, int read_ram_cpu){
    
    // Allocate Registers
    allocateRegisters(maxtime, write_cpu_ram, read_ram_cpu); 

    srand (time(NULL));

    // Loop infinitely until program end's
    while(cpu_flagtracker->CPU_EXIT == false){
        // Get data from RAM and store it
        // to IR and increment PC by 1
        registers->IR = gatherData(registers->PC++);

        // With the newly aquired IR, compute case instruction
        computeInstruction();        
    }

    // Delete and set NULL to allocated data
    delete registers;
    delete cpu_flagtracker;
    delete data_saves;

    registers = NULL;
    cpu_flagtracker = NULL;
    data_saves = NULL;
}


// Function retrieves data from RAM
int gatherData(int current_index){

    // Instruct read case in RAM and send current PC
    write(data_saves->W_CPU_RAM, "r", sizeof(char));
    write(data_saves->W_CPU_RAM, &(current_index), sizeof(current_index));

    // Read data from RAM and return result
    int return_result;
    read(data_saves->R_RAM_CPU, &(return_result), sizeof(return_result));

    // Return the data back to any register that needs it
    return return_result;
}


// Function wries data to RAM 
void writeData(int index_, int data_){

    // Instruct write case to RAM
    write(data_saves->W_CPU_RAM, "w", sizeof(char));

    // Send index to the location of array we want to write
    write(data_saves->W_CPU_RAM, &(index_), sizeof(index_));

    // Send data we want to store in index of array
    write(data_saves->W_CPU_RAM, &(data_), sizeof(data_));
}


////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CPU INSTRUCTIONS

// This function carries different specific instructions that the IR needs to carry
void computeInstruction(){


    switch(registers->IR){

        case 1: 
            testingRegisters(registers->IR);
            registers->AC = gatherData(registers->PC++);
        break;

        case 2: 
            testingRegisters(registers->IR);
            registers->AC = gatherData(gatherData(registers->PC++));
        break;

        case 3: 
            testingRegisters(registers->IR);
            registers->AC = gatherData(gatherData(gatherData(registers->PC++)));
        break;

        case 4: 
            testingRegisters(registers->IR);
            registers->AC = gatherData(gatherData(registers->PC++) + registers->X);
        break;
        
        case 5: 
            testingRegisters(registers->IR);
            registers->AC = gatherData(gatherData(registers->PC++) + registers->Y);
        break;
      
        case 6: 
            testingRegisters(registers->IR);
            registers->AC = gatherData(registers->SP + registers->X);
        break;
             
        case 7: 
            testingRegisters(registers->IR);
            writeData(gatherData(registers->PC++), registers->AC);    
        break;
        
        case 8: 
            testingRegisters(registers->IR);
            registers->AC = rand() % 100 + 1;
        break;
        
        case 9: 
            testingRegisters(registers->IR);
            data_saves->TEMP_DATA = gatherData(registers->PC++);
            if(data_saves->TEMP_DATA == 1){
                printf("%i", registers->AC);
            }
            else if (data_saves->TEMP_DATA == 2) {
                printf("%c",(char)registers->AC);
            }
        break;

        case 10: 
            testingRegisters(registers->IR);
            registers->AC += registers->X;
        break;
        
        case 11:           
            testingRegisters(registers->IR);
            registers->AC += registers->Y;
        break;

        case 12: 
            testingRegisters(registers->IR);
            registers->AC -= registers->X;
        break;

        case 13: 
            testingRegisters(registers->IR);
            registers->AC -= registers->Y;
        break;

        case 14: 
            testingRegisters(registers->IR);
            registers->X = registers->AC;
        break;

        case 15: 
            testingRegisters(registers->IR);
            registers->AC = registers->X;
        break;

        case 16: 
            testingRegisters(registers->IR);
            registers->Y = registers->AC;
        break;

        case 17: 
            testingRegisters(registers->IR);
            registers->AC = registers->Y;
        break;

        case 18: 
            testingRegisters(registers->IR);
            registers->SP = registers->AC;
        break;  

        case 19: 
            testingRegisters(registers->IR);
            registers->AC = registers->SP;
        break;

        case 20: 
            testingRegisters(registers->IR);
            registers->PC = gatherData(registers->PC++);
        break;

        case 21: 
            testingRegisters(registers->IR);
            data_saves->TEMP_DATA = gatherData(registers->PC++);
            if(registers->AC == 0){
                registers->PC = data_saves->TEMP_DATA;
            }
        break;

        case 22: 
            testingRegisters(registers->IR);
            data_saves->TEMP_DATA = gatherData(registers->PC++);
            if(registers->AC != 0){
                registers->PC = data_saves->TEMP_DATA;
            }
        break;

        case 23: 
            testingRegisters(registers->IR);
            data_saves->TEMP_DATA = gatherData(registers->PC++);
            writeData(--registers->SP,registers->PC);
            registers->PC = data_saves->TEMP_DATA;
        break;

        case 24: 
            testingRegisters(registers->IR);
            registers->PC = gatherData(registers->SP);
            writeData(registers->SP++, 0);
        break;

        case 25: 
            testingRegisters(registers->IR);
            registers->X++;

        break;

        case 26: 
            testingRegisters(registers->IR);
            registers->X--;
        break;

        case 27: 
            testingRegisters(registers->IR);
            writeData(--registers->SP, registers->AC);            
        break;

        case 28: 
            testingRegisters(registers->IR);
            registers->AC = gatherData(registers->SP);
            registers->SP++;
        break;


        // In progress...
        /*
        case 29: 
            cout << "Instruction 29" << endl;
        break;

        case 30: 
            cout << "Instruction 30" << endl;
        break;
        */

        case 50: 
            testingRegisters(registers->IR);
            cpu_flagtracker->CPU_EXIT = true;
            write(data_saves->W_CPU_RAM, 
                &(data_saves->END_RAM), 
                sizeof(data_saves->END_RAM));
        break;
        
        // If error occurs, end program
        default: 
            cout << "ERROR" << endl;
        break;
    }
}
////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HELPER FUNCTIONS

// Examine data for "registers"
void testingRegisters(int instruction_set){
    if(PRINT_DATA == 1){
        printf("INSTRUCTION: %i",instruction_set);

        printf(" PC %d\n SP %d\n IR %d\n AC %d\n X %d\n Y %d\n", 
        registers->PC,
        registers->SP,
        registers->IR,
        registers->AC,
        registers->X,
        registers->Y);

        printf("\nTEMPORARY DATA: %i\n\n", data_saves->TEMP_DATA);

    }
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

    // Allocate important data to save
    data_saves = new DataSaves;

    data_saves->W_CPU_RAM = write_cpu_ram;
    data_saves->R_RAM_CPU = read_ram_cpu;
    data_saves->TEMP_DATA = 0;
    data_saves->END_RAM = 'e';

}

