
#include "ram.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////
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
    return file_sucess;
}


// getDataFromFile() assigns elements from sampletxt to array
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
    sample_file->close();
    sample_file = NULL;
}
////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////
void RAMconnection(int write_ram_cpu, int read_cpu_ram){
    cout << write_ram_cpu << " RAM " << read_cpu_ram <<endl; 
}




void testingRam(){
    for(int i = 0; i < SIZE; i++){
        cout << data_elements[i] << endl;
    }
}


