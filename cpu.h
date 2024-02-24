#ifndef CPU_H
#define CPU_H

#include <string>   /* string */
#include <iostream> /* cout, endl */
#include <unistd.h>     // POSIX operating system calls
#include <stdio.h>

using std::cout;
using std::endl;
using std::string;

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

Registers *registers = NULL;

#endif /* CPU_H */