#ifndef LIBRAFILE_H
#define LIBRAFILE_H

#include <fstream>
#include <string>
#include <iostream>
#include "LibraBook.h" // Include the header file for the LibBook class

class LibFile 
{
private: // Methods or variables that can be accessed within the class
    std::string filename; // Name of file
    std::fstream filestrm; // File stream
    bool created = false; // File creation status

public: // Methods or variables that can be accessed outside the class
    LibFile(); 
    LibFile(const std::string& filePath); // Constructor with file path
    int csvload(LibBook& libBookInstance); // Loads the csv file and filters needed data
    void savetoCSV(LibBook& libBookInstance); // Saves all data to CSV file
    ~LibFile(); // Destructor to close file stream

};
#endif // LIBRAFILE_H
