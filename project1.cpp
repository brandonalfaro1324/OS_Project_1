#include <iostream>     // Get cout, endl
#include <unistd.h>     // POSIX operating system calls
#include <cctype>       // Transform Individual Characters
#include <cstdio>       // Input and Output files
// #include <cstdlib>
#include <string>    



// Include files created for this project
#include "cpu.cpp"
#include "ram.cpp"

#define SUCCESS 0

using std::cout;
using std::endl;
using std::string;


int main(int argc, char* argv[]) { 

    // Collect sample file and integer
    string file_name = argv[1];
    string timer_set = argv[2];

    // If we we're able to extract data
    //  from file, begin the CPU work. 

    if(initializeRam(file_name) == true){

        int fd_cpu_ram[2];
        int fd_ram_cpu[2];

        // create two_pipes for ram and cpu and check if success
        // If sucess, begin the pipes and child process 
        if(pipe(fd_cpu_ram) == 0 && pipe(fd_ram_cpu) == 0){

            pid_t ram_process = fork(); 
    
            // Child process
            if (ram_process == 0) { 
                RAMconnection(fd_ram_cpu[1], fd_cpu_ram[0]);

            } 
            // Parent Process
            else if (ram_process > 0) { 
                CPUrunning(stoi(timer_set) , fd_cpu_ram[1], fd_ram_cpu[0]);
                //testingRegisters();
            } 
            else { 
                cout << "ERROR CREATING CHILD, ENDING APPLICATION..." << endl;
            } 
        }
    }
    

    return 0;
}