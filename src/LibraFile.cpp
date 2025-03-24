#include <iostream>
#include <fstream>
#include <string>
#include "LibraFile.h"

LibFile::LibFile() : filename("books.txt")
{
    filestrm.open(filename, std::ios::in); // Open file with filename books.txt

    if (!filestrm) // If file does not exist
    {
        filestrm.open(filename, std::ios::out); // Create file with filename books.txt
        std::cout << "File created: " << filename << std::endl; // Inform User
    }
}

LibFile::LibFile(const std::string& filePath) : filename(filePath)
{
    filestrm.open(filename, std::ios::in); // Open specified file

    if (!filestrm) // If file does not exist
    {
        filestrm.open(filename, std::ios::out); // Create file with filename
        std::cout << "File created: " << filename << std::endl; // Inform User
    }
}
