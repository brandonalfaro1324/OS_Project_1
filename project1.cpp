
#include <stdio.h>      // printf use
#include <iostream>     // Get cout, endl
#include <unistd.h>     // POSIX operating system calls

// Include files created for this project
#include "cpu.cpp"
#include "ram.cpp"

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

                // Close pipes and exit
                
                close(fd_ram_cpu[1]);
                close(fd_cpu_ram[0]);

                exit(0);
            } 
            // Parent Process
            else if (ram_process > 0) { 
                CPUrunning(stoi(timer_set) , fd_cpu_ram[1], fd_ram_cpu[0]);
                
                // Close pipes and exit
                close(fd_cpu_ram[1]);
                close(fd_ram_cpu[0]);

                exit(0);       
            }     
            // Error creating child process
            else { 
                // Print error and exit process
                printf("ERROR CREATING CHILD, ENDING APPLICATION...");
                exit(-1);
            } 
        }
    }
    return 0;
}