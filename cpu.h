#ifndef CPU_H
#define CPU_H

#include <unistd.h> // For POSIX operating system calls
#include <ctime>    // For srand() and time()
#include <cstdlib>  // For exit() and other utility functions

// Create registers in a struct
struct Registers {
    int PC;
    int SP;
    int IR;
    int AC;
    int X;
    int Y;
};

struct CpuDataFlags{
    int CURRENT_TIME;  // Track CPU iterations
    int MAXTIME;       // Max iterations

    int U_K_MODE;

    bool CPU_EXIT;     // Keep CPU while loop running  
};

 struct DataSaves{
    int W_CPU_RAM;     // Save write pipe from CPU to RAM
    int R_RAM_CPU;     // Save read pipe from RAM to CPU
    
    int TEMP_DATA;     // Tempoary hold data
    char END_RAM;      // Save 'e' to end RAM

    int USER;
    int KERNEL;

    int STACK_SIZE;
 };


// Intializte struct Registers and set "*registers" to null
Registers *registers = NULL;

// Intialize struct CPU Data Flags and set "*flagkeeper" to NULL
CpuDataFlags *cpu_flagtracker = NULL;

// Intialize struct to save important information
DataSaves *data_saves = NULL;

#endif /* CPU_H */