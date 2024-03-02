#ifndef CPU_H
#define CPU_H

#include <string>    /* C++ string */
#include <cstring>   /* C string */
#include <iostream>  /* cout, endl */
#include <unistd.h>     // POSIX operating system calls

using std::cout;
using std::endl;
using std::string;

// Create registers in a struct
struct Registers {
    int PC;
    int SP;
    int IR;
    int AC;
    int X;
    int Y;
    int MAXTIME;
    int TIME;
};

// Intializte struct Registers and set "*registers" to null
Registers *registers = NULL;

#endif /* CPU_H */