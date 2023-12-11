/*
|| reader.cpp ||
This file contains code that reads user input and launches 
the necessary functions in response; Handles errors sent 
by functions.
*/
#include "functions.h"                      // All custom functions for program 
#include <boost/program_options.hpp>        // Module for terminal interface

namespace po = boost::program_options;      



int main(int argc, char** argv) {
    const string Path = "Data/tasks.json";          // Road for file
    const string curr_version = "TaskForge 0.1";
    const string usage[] = {"usage: tf [options] -n [name] -d [description]", 
                            "usage: tf -A -n 'Task1' -d 'Chill'"};    
    int Error_counter;                              // Accepts responses from functions

    json MainData;                                  // JSON object to write to a data file
    json TempData;                                  // JSON object for temporary storage of the base.
    
    // Create space command
    po::variables_map var_map;
    po::options_description commands("Allowed options");            // Create all command var
    commands.add_options()                                          // Add all commands and decriptions
        ("help,H", "produce help message")                      
        ("version,V", "show current version")
        ("show,S", "show all tasks")
        ("marked,M", "mark select task")
        ("delete,D", "deleted select task")
        ("add,A", "add a new task")
        ("all,a", "argument 'all'")
        ("name,n", po::value<std::string>(), 
        "name of the task")
        ("description,d", po::value<std::string>(), 
        "description of the task");

    // Parsing user enter commands
    try 
    {
        po::store(po::command_line_parser(argc, argv)           // Parsing user command
                      .options(commands)                        // Comparison of сommands
                      .allow_unregistered()                     // None
                      .run(),                                   // Run parsing
                  var_map);                                     // Copy the finished values to a variable
    } 
    catch (const po::error& e) 
    {
        Errors::IC();
        return 1;
    }
    po::notify(var_map);                                // Notification when a user request is being processed
    Error_counter = Copy_data(MainData, Path);          // From functions module
    // Didn't open
    if(Error_counter)
    {
        Errors::UtRF();                                 // From errors module
    }
    // Help commmand
    if(var_map.count("help")) 
    {
        //Output_array(usage);
        cout << commands << endl;
    }
    // Version command
    else if(var_map.count("version"))
    {
        cout << curr_version << endl;
    }
    // Show command
    else if(var_map.count("show")) 
    {
        Output_data(MainData);                                              // From fuction module
    }
    // Marked task
    else if(var_map.count("marked") && var_map.count("name")) 
    {
        Error_counter = 
        Marked_task(MainData, var_map["name"].as<std::string>());           // From fuction module
        if(Error_counter) 
        {
            Errors::NFV();                                                  // From errors module
        }
    }
    // Delete task
    else if(var_map.count("delete") && (var_map.count("name") || var_map.count("all"))) 
    {
        if(var_map.count("all")) 
        {
            Error_counter = 
            Clear_all(MainData);            // From fuction module 
            if(Error_counter) 
            {
                Errors::NFV();              // From errors
            }
        }
        else 
        {
            Error_counter = 
            Delete_task(MainData, var_map["name"].as<std::string>());           // From fuction module 
            if(Error_counter) 
            {
                Errors::NFV();                                                  // From errors
            }
        }
    }
    // Add command
    else if(var_map.count("add") && var_map.count("name") 
                                    && var_map.count("description")) 
    {
        Error_counter = 
        Update_data(MainData, TempData, var_map["name"].as<std::string>(), 
                                    var_map["description"].as<std::string>());          // From fuction module
        if(Error_counter) 
        {
            Errors::TNWtF();            // From errors module
        }
    }
    else 
    {
        Errors::UA();                   // From functions
    }
    Error_counter = Save_data(MainData, Path);          // From functions 
    // Didn't open
    if (Error_counter)
    {
        Errors::UtOF();                                 // From errors module
    }
    
    return 0;
}


