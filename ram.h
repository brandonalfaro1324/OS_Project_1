#ifndef RAM_H
#define RAM_H

#include <fstream>  /* get Input/Output files */
#include <string>   /* string */
#include <iostream> /* cout, endl */
#include <unistd.h>     // POSIX operating system calls

#define SIZE 2000

using std::cout;
using std::endl;
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

void getDataFromFile(ifstream *);

#endif /* RAM_H */