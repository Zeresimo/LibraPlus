#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include "LibraFile.h"

LibFile::LibFile() : filename("Library.csv")
{
    filestrm.open(filename, std::ios::in); // Open file with filename Library.csv

    if (!filestrm) // If file does not exist
    {
        filestrm.open(filename, std::ios::out); // Create file with filename books.txt
        filestrm << "Title,Author,Genre,Borrowed\n"; // Write header to file
        std::cout << "File created and header added: " << filename << std::endl; 
        created = true; 
    }
}

LibFile::LibFile(const std::string& filePath) : filename(filePath)
{
    filestrm.open(filename, std::ios::in); // Open specified file

    if (!filestrm) // If file does not exist
    {
        filestrm.open(filename, std::ios::out); // Create file with filename
        filestrm << "Title,Author,Genre,Borrowed\n"; // Write header to file
        std::cout << "File created and header added: " << filename << std::endl; 
        created = true; 
    }
}

void LibFile::addBook(const Book& book) // Adds book into the collection vector
{
    LibraPlus.push_back(book); // Add book to the collection vector
    Book* ptr = &LibraPlus.back(); // Get pointer to the last book added
    ptr->borrowed = false; // Set borrowed status to false
    titleIndex[book.title].push_back(ptr); // Index book by title
    authorIndex[book.author].push_back(ptr); // Index book by author
    genreIndex[book.genre].push_back(ptr); // Index book by genre
}

int LibFile::csvload(const Book& book) // Extracts needed info from csv file
{
    std::string initial;
    std::string final;
    int titleIndex = -1; 
    int authorIndex = -1; 
    int genreIndex = -1; 
    std::string column;; // Variable to store each column name
    std::vector<std::string> headers; // Vector to store header names

    if (created)
    {
        filestrm.close(); // Close the file stream if it was just created
        filestrm.open(filename, std::ios::in); // Reopen the file in read mode
    }

    std::getline(filestrm, initial); // Read the header line
    std::stringstream header_ss(initial); // Create a stringstream from the header line

    while (std::getline(header_ss, column, ',')) // Read each column name from the header line
    {
        headers.push_back(column); // Add column name to vector
    }

    for(int i =0; i < headers.size(); i++)
    {
        if (headers[i] == "Title") 
            titleIndex = i; 
        else if (headers[i] == "Author") 
            authorIndex = i; 
        else if (headers[i] == "Genre") 
            genreIndex = i; 
    }

    if (titleIndex == -1 || authorIndex == -1 || genreIndex == -1) // If any of the indices are not found
    {
        std::cerr << "Error: Header not found in file." << std::endl; // Print error message
        filestrm.close(); // Close the file stream
        return -1; // Exit the function
    } // Error Handling in case of missing header, or csv doesn't have data needed

    while(std::getline(filestrm, final))
    {
        std::stringstream ss(final);
        std::string temp;

        Book tempBook; // Create a temporary Book object

        for(int k = 0; std::getline(ss, temp, ','); k++)
        {
            if (k == titleIndex) 
                tempBook.title = temp; 
            else if (k == authorIndex) 
                tempBook.author = temp; 
            else if (k == genreIndex) 
                tempBook.genre = temp; 
        }

        if(tempBook.title.empty() || tempBook.author.empty() || tempBook.genre.empty()) // If any of the fields are empty
        {
            std::cerr << "Error: Missing data in file." << std::endl; 
            continue; // Skip this iteration
        }

        addBook(tempBook); // Add the book to the collection
    }
    
}

LibFile::~LibFile() // Destructor: closes the file stream
{
    if (filestrm.is_open()) // If file is open
    {
        filestrm.close(); // Close the file stream
    }
}