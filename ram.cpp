
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
    
    // Testing connection beetween RAM and CPU
    //while (flagkeeper->exit_loop == false){

        /* TESTIG CONNECTION */
        read(read_cpu_ram, &(flagkeeper->exit_loop), sizeof(flagkeeper->exit_loop));
        printf("Printing Result: %s\n", flagkeeper->exit_loop ? "TRUE" : "FALSE");
        /* TESTIG CONNECTION */
    //}

    // Delete and set "flagkeeper" to NULL
    delete flagkeeper;
    flagkeeper = NULL;    
}
////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HELPER FUNCTIONS

//Function to examine "flagkeeper" variables
void printDataFlags(){
    printf("Exit Loop: %s\n", flagkeeper->exit_loop ? "True" : "False");
    printf("Index: %i\n", flagkeeper->index_data);
    printf("CaseSwtich: %c\n", flagkeeper->case_swtich);
}

// Examine RAM array
void testingRam(){
    for(int i = 0; i < SIZE; i++){
        cout << data_elements[i] << endl;
    }
}

// Intilize "flagkeeper" and assign data to variables
void IntilizeDataFlags(){
    flagkeeper = new RamDataFlags;
    flagkeeper->exit_loop = false;
    flagkeeper->index_data = 0;
    flagkeeper->case_swtich = '\0';
}