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

// Create global ram variable
int data_elements[SIZE] = {0};

//bool initializeRam(string);
void getDataFromFile(ifstream *);
//void testingRam();

#endif /* RAM_H */