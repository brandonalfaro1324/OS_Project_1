
#include "cpu.h"

// NOTE:
// write_cpu_ram <= fd_cpu_ram[0] <= writing from CPU to RAM
// read_ram_cpu <= fd_ram_cpu[1] <= reading from RAM to CPU

void allocateRegisters(int, int, int);
int gatherData(int);

void testingRegisters(int);
void computeInstruction();
void writeData(int, int);
void checkTimeout();


const int USER = 0;
const int KERNEL =  1;
const int SYTEM_STACK_SIZE = 2000;
const int INT_INSTRUCTION = 1500;


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

        // Increment timer by 1
        cpu_flagtracker->CURRENT_TIME++;

        // Check if we are over the timer limit
        checkTimeout();
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


// Function writes data to RAM 
void writeData(int index_, int data_){

    // Instruct write case to RAM
    write(data_saves->W_CPU_RAM, "w", sizeof(char));

    // Send index to the location of array we want to write
    write(data_saves->W_CPU_RAM, &(index_), sizeof(index_));

    // Send data we want to store in index of array
    write(data_saves->W_CPU_RAM, &(data_), sizeof(data_));
}


// When Timer goes over the limit, function will save everything and swith to KERNEL
void checkTimeout(){

    // Check if current timer is over the limit and user/kernel mode is set to USER
    if(cpu_flagtracker->MAXTIME <= cpu_flagtracker->CURRENT_TIME && 
        cpu_flagtracker->U_K_MODE == USER)
    {
        
        // Reduce timer  by max time and set user/kernel to KERNEL mode
        cpu_flagtracker->CURRENT_TIME-= cpu_flagtracker->MAXTIME;
        cpu_flagtracker->U_K_MODE = KERNEL;

        // Temporary save SP and replace SP to Size of System, 2000
        data_saves->TEMP_DATA = registers->SP;
        registers->SP = SYTEM_STACK_SIZE;

        // Write Temporary Data to RAM follow by PC
        writeData(--registers->SP,  data_saves->TEMP_DATA);   
        writeData(--registers->SP,  registers->PC); 

        // Set PC to 1000
        registers->PC = 1000;
    }
}


////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CPU INSTRUCTIONS

// This function carries different specific instructions that the IR needs to carry
void computeInstruction(){

    switch(registers->IR){

        // Load data to AC
        case 1: 
            testingRegisters(registers->IR);
            registers->AC = gatherData(registers->PC++);
        break;

        // Load data follow by another load 
        // from that data and store it to AC
        case 2: 
            testingRegisters(registers->IR);
            registers->AC = gatherData(gatherData(registers->PC++));
        break;
        
        // Load data from another load then another
        // another and store it to AC
        case 3: 
            testingRegisters(registers->IR);
            registers->AC = gatherData(gatherData(gatherData(registers->PC++)));
        break;

        // Load value from, using (PC + X)
        //  and set it to AC
        case 4: 
            testingRegisters(registers->IR);
            registers->AC = gatherData(gatherData(registers->PC++) + registers->X);
        break;
        
        // Load value from, using (PC + Y)
        // and  set it to AC
        case 5: 
            testingRegisters(registers->IR);
            registers->AC = gatherData(gatherData(registers->PC++) + registers->Y);
        break;
      
        // Load value from, using (SP + X) 
        // and set it to to AC
        case 6: 
            testingRegisters(registers->IR);
            registers->AC = gatherData(registers->SP + registers->X);
        break;
             
        // Store AC value to PC address
        case 7: 
            testingRegisters(registers->IR);
            writeData(gatherData(registers->PC++), registers->AC);    
        break;
        
        // Get random data and store it to AC
        case 8: 
            testingRegisters(registers->IR);
            registers->AC = rand() % 100 + 1;
        break;
        
        // Get data and if print AC depedning 
        // of data collected from memory
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

        // Add X to AC
        case 10: 
            testingRegisters(registers->IR);
            registers->AC += registers->X;
        break;
        
        // Add Y to AC
        case 11:           
            testingRegisters(registers->IR);
            registers->AC += registers->Y;
        break;

        // Subtract X to AC
        case 12: 
            testingRegisters(registers->IR);
            registers->AC -= registers->X;
        break;

        // Subtract Y to AC
        case 13: 
            testingRegisters(registers->IR);
            registers->AC -= registers->Y;
        break;

        // Assign AC to X
        case 14: 
            testingRegisters(registers->IR);
            registers->X = registers->AC;
        break;

        // Assign X to AC
        case 15: 
            testingRegisters(registers->IR);
            registers->AC = registers->X;
        break;

        // Assign AC to Y
        case 16: 
            testingRegisters(registers->IR);
            registers->Y = registers->AC;
        break;

        // Assign Y to AC
        case 17: 
            testingRegisters(registers->IR);
            registers->AC = registers->Y;
        break;

        // Assign SP to AC
        case 18: 
            testingRegisters(registers->IR);
            registers->SP = registers->AC;
        break;  

        // Assign AC to SP
        case 19: 
            testingRegisters(registers->IR);
            registers->AC = registers->SP;
        break;

        // Jump to address
        case 20: 
            testingRegisters(registers->IR);
            registers->PC = gatherData(registers->PC++);
        break;

        // Jump address if data retrieve 
        // is equal to 0
        case 21: 
            testingRegisters(registers->IR);
            data_saves->TEMP_DATA = gatherData(registers->PC++);
            if(registers->AC == 0){
                registers->PC = data_saves->TEMP_DATA;
            }
        break;

        // Jump address if data retrieve 
        // is NOT equal to 0
        case 22: 
            testingRegisters(registers->IR);
            data_saves->TEMP_DATA = gatherData(registers->PC++);
            if(registers->AC != 0){
                registers->PC = data_saves->TEMP_DATA;
            }
        break;

        // Push return address to SC
        // and jump to address
        case 23: 
            testingRegisters(registers->IR);
            data_saves->TEMP_DATA = gatherData(registers->PC++);
            writeData(--registers->SP,registers->PC);
            registers->PC = data_saves->TEMP_DATA;
        break;

        // Pop return address from SP and jump to 
        // the address
        case 24: 
            testingRegisters(registers->IR);
            registers->PC = gatherData(registers->SP);
            writeData(registers->SP++, 0);
        break;

        // Increase X by 1
        case 25: 
            testingRegisters(registers->IR);
            registers->X++;

        break;

        // Decrease X by 1
        case 26: 
            testingRegisters(registers->IR);
            registers->X--;
        break;

        // Push AC to SP
        case 27: 
            testingRegisters(registers->IR);
            writeData(--registers->SP, registers->AC);            
        break;

        // Pop SP and assign data to AC
        case 28: 
            testingRegisters(registers->IR);
            registers->AC = gatherData(registers->SP);
            registers->SP++;
        break;

        // Computer System Call
        case 29: 
            testingRegisters(registers->IR);
            // Check if User/Kernel mode is User Mode 
            if(cpu_flagtracker->U_K_MODE == USER){

                // Change Mode to Kernel
                cpu_flagtracker->U_K_MODE = KERNEL;

                // Temporary save SP  and set it to Stack Size
                data_saves->TEMP_DATA = registers->SP;
                registers->SP = SYTEM_STACK_SIZE;

                // Write Temporary Data to RAM follow by PC
                writeData(--registers->SP,  data_saves->TEMP_DATA);   
                writeData(--registers->SP,  registers->PC);   

                // Assign PC to 1500, the instruction point
                registers->PC = INT_INSTRUCTION;
            }
        break;
        
        // Return back to USER mode from System Call
        case 30: 
            testingRegisters(registers->IR);
            // Collect data from SP follow by the PC 
            registers->PC = gatherData(registers->SP++);
            registers->SP = gatherData(registers->SP);

            // Change user/kernel mode to USER
            cpu_flagtracker->U_K_MODE = USER;
        break;
        
        // End CPU
        case 50: 
            testingRegisters(registers->IR);
            // Set "CPU_EXIT" to end while loop
            cpu_flagtracker->CPU_EXIT = true;
            
            // Write to RAM to end RAM process
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

    cpu_flagtracker->U_K_MODE = USER;

    cpu_flagtracker->CPU_EXIT = false;

    // Allocate important data to save
    data_saves = new DataSaves;

    data_saves->W_CPU_RAM = write_cpu_ram;
    data_saves->R_RAM_CPU = read_ram_cpu;

    data_saves->USER = USER;
    data_saves->KERNEL = KERNEL;
    data_saves->STACK_SIZE = SYTEM_STACK_SIZE;

    data_saves->TEMP_DATA = 0;
    data_saves->END_RAM = 'e';
}