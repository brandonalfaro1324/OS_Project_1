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
};

RamDataFlags *flagkeeper = NULL;

void getDataFromFile(ifstream *);

#endif /* RAM_H */