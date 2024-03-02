#ifndef CPU_H
#define CPU_H

/*
#include <string>    // C++ string 
#include <cstring>   // C string 
#include <iostream>  // cout, endl
#include <unistd.h>  // POSIX operating system calls
*/

#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <ctype.h>

using std::cout;
using std::endl;
using std::string;

#define TIMER_ADDRESS 1000;

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

    bool CPU_EXIT;     // Keep CPU while loop running  
};

 struct DataSaves{
    int W_CPU_RAM;     // Save write pipe from CPU to RAM
    int R_RAM_CPU;     // Save read pipe from RAM to CPU
    
    int TEMP_DATA;     // Tempoary hold data
    char END_RAM;      // Save 'e' to end RAM
 };


// Intializte struct Registers and set "*registers" to null
Registers *registers = NULL;

// Intialize struct CPU Data Flags and set "*flagkeeper" to NULL
CpuDataFlags *cpu_flagtracker = NULL;

// Intialize struct to save important information
DataSaves *data_saves = NULL;

#endif /* CPU_H */