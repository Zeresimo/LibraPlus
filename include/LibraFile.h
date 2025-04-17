#ifndef LIBRAFILE_H
#define LIBRAFILE_H

#include <fstream>
#include <string>
#include <iostream>

class LibFile 
{
private: // Methods or variables that can be accessed within the class
    std::string filename; // Name of file
    std::fstream filestrm; // File stream
    bool created = false; // File creation status
    struct Book
    {
        std::string title; // Title of the book
        std::string author; // Author of the book
        std::string genre; // Genre of the book
        bool borrowed; // Borrowed status of the book
    };

public: // Methods or variables that can be accessed outside the class

    // Constructor: initializes a file with a default filename
    LibFile(); 

    // Constructor: initializes a file with a specified filename
    LibFile(const std::string& filePath);

    int csvload(const Book& book); // Loads the csv file and filters needed data
    void addBook(const Book& book); // Adds a book to the collection

};
#endif // LIBRAFILE_H
