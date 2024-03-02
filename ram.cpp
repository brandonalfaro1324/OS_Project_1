
#include "ram.h"

// NOTE:
// write_ram_cpu <= fd_ram_cpu[0] <= writing from RAM to CPU
// read_cpu_ram <= fd_cpu_ram[1] <= reading from CPU to RAM

void IntilizeDataFlags();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS THAT MAKE UP THE RAM

// Opening file and creating "RAM"
bool initializeRam(string sample_text){

    // Return success signal back to main
    bool file_sucess = false;

    // Open file
    ifstream new_file;
    new_file.open(sample_text, ios :: in);

    // Check if file exist
    // If false, return false back to main
    if(new_file.is_open()){
        getDataFromFile(&new_file); 
        file_sucess = true;
    }

    // return sucess of opening file
    return file_sucess;
}

// Collecting data from file and adding them to "RAM" indexes
void getDataFromFile(ifstream *sample_file){

    // Create counter and string
    int index = 0;
    string string_element;

    // Get integer of each line and assign it to ram array "data_elements[]"
    while(getline(*sample_file, string_element)){

        // Check if "string_element" is not empty
        if(string_element.empty()==false){
            
            // If first character in newline is number, assign it 
            // to current ram location and increment ram by 1 
            if(isdigit(string_element[0])==true){
                data_elements[index++] = stoi(string_element);
            }
            // If first character is '.',  
            // then change location of ram
            else if(string_element[0] == '.'){

                // Changing ram location
                string testin = &string_element[1];
                index = stoi(testin);
            }
        }
    }
    // Close file
    sample_file->close();
}
////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////
void RAMconnection(int write_ram_cpu, int read_cpu_ram){

    // Allocate "RamDataFlags" for flag's and data variables
    IntilizeDataFlags();
    
    // Read from CPU before going in while loop
    read(read_cpu_ram, &(ram_flagtracker->case_swtich), sizeof(ram_flagtracker->case_swtich));

    // Testing connection beetween RAM and CPU
    while (ram_flagtracker->exit_loop == false){

        switch (ram_flagtracker->case_swtich){
            case 'e':
                printf("EXITING RAM...\n");
                // Exit the loop
                ram_flagtracker->exit_loop = true;
            break;
            case 'r':
                printf("READ INSTRUCTION FROM CPU...\n");
                int read_pc;
                read(read_cpu_ram, &read_pc, sizeof(read_pc));
                write(write_ram_cpu, &(data_elements[read_pc]), sizeof(data_elements[read_pc]));

            break;
            case 'w':
                printf("WRITING IN RAM...\n");
            break;

        }
        // Read next instruction from CPU
        read(read_cpu_ram, &(ram_flagtracker->case_swtich), sizeof(ram_flagtracker->case_swtich));
    }

    // Delete and set "ram_flagtracker" to NULL
    delete ram_flagtracker;
    ram_flagtracker = NULL;   

    exit(0);
}
////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HELPER FUNCTIONS

//Function to examine "ram_flagtracker" variables
void printDataFlags(){
    printf("Exit Loop: %s\n", ram_flagtracker->exit_loop ? "True" : "False");
    printf("Index: %i\n", ram_flagtracker->index_data);
    printf("CaseSwtich: %c\n", ram_flagtracker->case_swtich);
}

// Examine RAM array
void testingRam(){
    for(int i = 0; i < SIZE; i++){
        cout << data_elements[i] << endl;
    }
}

// Intilize "ram_flagtracker" and assign data to variables
void IntilizeDataFlags(){
    ram_flagtracker = new RamDataFlags;
    
    ram_flagtracker->exit_loop = false;
    ram_flagtracker->index_data = 0;
    ram_flagtracker->case_swtich = '\0';
}