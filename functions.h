/*
|| fuctions.h ||
This file contains the code for all the functions 
that the program needs.
*/
#include <fstream>                      // Filesystem module
#include <nlohmann/json.hpp>            // JSON module
#include "Other/includes.h"           // Imports for program
#include "Other/colors.h"
#include "Other/errors.h"               // Errors module for program
        
using json = nlohmann::json;   



int Delete_task(json& data, string name) 
/* A function that searches for and 
deletes the required task from the database */
{

    // If name is find
    if (data.find(name) != data.end()) 
    {
        data.erase(name);           // Delete a task by name
    }
    else 
    {
        return 1;                   // Sends an error
    }
    
    return 0;                               
}


int Marked_task(json& data, string name) 
/* Function for finding and marking the 
desired task */
{
    // If name is find
    if (data.find(name) != data.end()) 
    {
        if(data[name]["Done"] != "V")               // If "✓" is found
        { 
            data[name]["Done"] = "V";               // Marked task
        }
        else if(data[name]["Done"] != "X")          // If "✗" is found
        {
            data[name]["Done"] = "X";               // Unmarked task  
        }
    }
    else 
    {
        return 1;                                   // Sends an error
    }
    
    return 0;
}


int Update_data(json& maindata, json& tempdata,
                    string name, string description) 
/* A function to update a JSON variable */
{
    tempdata = {                                    // Create new Data object 
        {name, {                                    // Title Task
            {"Description", description},           // Description Task
            {"Done", "X"}                           // Mark Task
        }}
    };
    maindata.update(tempdata);                      // Update Data object
    
    return 0;
}


int Copy_data(json& data, const string& file) 
/* A function for reading a data file 
into a variable */
{
    ifstream InData(file);          // Write data file for InData
    // Checking for open
    if (InData.is_open())          
    {
        InData >> data;             // Write data in Task object
        InData.close();             // Close data file
    }
    else 
    {
        return 1;                   // Sends an error
    }
    
    return 0;
}


int Save_data(const json& data, const string& file) 
/* Overwriting a JSON file using an 
edited JSON variable */
{
    ofstream OuData(file);              // Open data file
    // Check if the data file is open
    if (OuData.is_open())               
    {
        OuData << data.dump(4);         // Write new information in the data file
        OuData.close();                 // Save and close data file
    } 
    else
    {
        return 1;                       // Sends an error
    }

    return 0;
}


int Output_data(const json& data) 
/* Display the entire data content 
in the terminal */
{   
    // If the file is empty.
    if(data.empty()) 
    {
        cout << Colors::R << "{ No tasks }" << Colors::RE << endl;
    }
    else 
    {
        // A loop to output all file data.
        for (auto i = data.begin(); i != data.end(); ++i) 
        {
            cout << i.key() << ": " << i.value()["Description"] << " [";
                if(i.value()["Done"] == "X") 
                {
                   cout << Colors::R << i.value()["Done"] 
                   << Colors::RE << "]" << "; " << endl;
                }
                else if(i.value()["Done"] == "V") 
                {
                   cout << Colors::G << i.value()["Done"] 
                   << Colors::RE << "]" << "; " << endl;
                }
        }
    }

    return 0;
}


int Clear_all(json& data) 
/* A function that completely cleans up data */
{
    data.clear();           // Clean up the file.

    return 0;
}

/*
int Output_array(const string array[]) 
{
    int size = sizeof(array) / sizeof(array[0]);

    for(int i = 0; i < size; i++) 
    {
        cout << array[i] << endl;
    }

    return 0;
}
*/