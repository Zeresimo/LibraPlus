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
    std::vector<Book> LibraPlus; // Vector to store books
    std::unordered_map<std::string, std::vector<Book*>> titleIndex; // Map to index books by title
    std::unordered_map<std::string, std::vector<Book*>> authorIndex; // Map to index books by author
    std::unordered_map<std::string, std::vector<Book*>> genreIndex; // Map to index books by genre

public: // Methods or variables that can be accessed outside the class

    // Constructor: initializes a file with a default filename
    LibFile(); 

    // Constructor: initializes a file with a specified filename
    LibFile(const std::string& filePath);

    int csvload(const Book& book); // Loads the csv file and filters needed data
    void addBook(const Book& book); // Adds a book to the collection
    void createbook(); // Creates a new book as defined by user
    void LibFile::savetoCSV(); // Saves all data to CSV file

};
#endif // LIBRAFILE_H
