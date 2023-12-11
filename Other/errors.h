/*
|| errors.h ||
This file contains the code for all reactions 
to various errors.
*/
#include "includes.h"           // Imports for program


string R = "\033[0;31m";            // Code color red       
string RE = "\033[0m";              // Code reset


namespace Errors
/* Namespace, which saves all messages to 
explain errors */
{
    void IC() 
    /* An unfamiliar command */ 
    {
        cerr << R << "Error: An incomprehensible command!" 
        << RE << endl;
    }
    void UA()
    /* Unclear arguments */
    {
        cerr << R << "Error: Unclear arguments!" 
        << RE << endl;
    }
    void NFV()
    /* Not found value */
    {
        cerr << R << "Error: The value you entered was not found!" 
        << RE << endl;
    }
    void TNWtF()
    {
        cerr << R << "The task was not written to the file!"
        << RE << endl;
    }
    void UtOF() 
    /* Unable to open file for writing */
    {
        cerr << R << "Error: Unable to open file for writing!" 
        << RE << endl;
    }
    void UtRF() 
    /* Unable to open file for reading */
    {
        cerr << R << "Error: Unable to open file for reading!" 
        << RE << endl;
    }
};