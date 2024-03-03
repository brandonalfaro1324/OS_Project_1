#ifndef RAM_H
#define RAM_H

#include <stdio.h>   // For printf
#include <fstream>   // For getting Input/Output files
#include <cstdlib>   // For exit() function
#include <unistd.h>  // For POSIX operating system calls

#define SIZE 2000

using std::string;
using std::ifstream;
using std::ios;

// Create global ram variable and assign every element to 0
int data_elements[SIZE] = {0};

struct RamDataFlags{
    bool exit_loop;
    int index_data;
    char case_swtich;
    int data_variable;
    int W_RAM_TO_CPU;
    int R_CPU_TO_RAM;
};

RamDataFlags *ram_flagtracker = NULL;
#endif /* RAM_H */