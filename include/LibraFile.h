#ifndef LIBRAFILE_H
#define LIBRAFILE_H

#include <fstream>
#include <string>
#include <iostream>

class LibFile 
{
public: // Methods or variables that can be accessed outside the class

    // Constructor: initializes a file with a default filename
    LibFile(); 

    // Constructor: initializes a file with a specified filename
    LibFile(const std::string& filePath);

private: // Methods or variables that can be accessed within the class
    std::string filename; // Name of file
    std::fstream filestrm; // File stream
};
#endif // LIBRAFILE_H
