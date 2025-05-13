#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include "LibraFile.h"
#include "LibraBook.h"

LibFile::LibFile() : filename("Library.csv")
{
    filestrm.open(filename, std::ios::in); // Open file with filename Library.csv

    if (!filestrm) // If file does not exist
    {
        filestrm.open(filename, std::ios::out); // Create file "Library.csv"
        std::cout << "File created: " << filename << std::endl; 
        created = true; 
    }
}

LibFile::LibFile(const std::string& filePath) : filename(filePath)
{
    filestrm.open(filename, std::ios::in); // Open specified file

    if (!filestrm) // If file does not exist
    {
        filestrm.open(filename, std::ios::out); // Create file with filename
        std::cout << "File created: " << filename << std::endl; 
        created = true; 
    }
}

int LibFile::csvload(LibBook& libBookInstance) // Extracts needed info from csv file
{
    std::string initial;
    std::string final;
    int titleIndex = -1; 
    int authorIndex = -1; 
    int genreIndex = -1; 
    std::string column; // Variable to store each column name
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
        std::cout << "Error: Header not found in file." << std::endl; // Print error message
        filestrm.close(); // Close the file stream
        return -1; // Exit the function
    } // Error Handling in case of missing header, or csv doesn't have data needed

    while(std::getline(filestrm, final))
    {
        std::stringstream ss(final);
        std::string temp;

        LibBook::Book tempBook; // Create a temporary Book object

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
            std::cout << "Error: Missing data in file." << std::endl; 
            continue; // Skip this iteration
        }

        libBookInstance.addBook(tempBook); // Add the book to the collection
    }

    return 0;
    
}

void LibFile::savetoCSV(LibBook& libBookInstance) // Saves the current collection to the CSV file
{
    char choice;
    std::cout << "Do you want to save the file? (y/n): ";
    std::cin >> choice; 
    if (choice == 'y' || choice == 'Y' ) // If user chooses save
    {
        char choice2; // Choice for overwrite
        if (!created)
        {
            std::cout << "File already exists. Do you want to overwrite it? (y/n): ";
            std::cin >> choice2; 
        }
        if (choice2 == 'y' || choice2 == 'Y' || created) 
        {
            std::ofstream NewFile(filename, std::ios::out); // Open file in overwrite mode
            NewFile << "Title,Author,Genre,Borrowed\n"; // Write header to file
            for (const LibBook::Book& book : libBookInstance.getBooks()) // Iterate through the collection vector
            {
                NewFile << book.title << "," << book.author << "," << book.genre << "," << book.borrowed << "\n"; // Write book data to file
            }
            NewFile.close(); // Close the file stream
        }
        else // If user chooses not to overwrite
        {
            std::cout << "File not saved." << std::endl; 
            return; 
        }
    }
    else // If user chooses not to save
    {
        std::cout << "File not saved." << std::endl; 
        return; 
    }
}

LibFile::~LibFile() // Destructor: closes the file stream
{
    if (filestrm.is_open()) // If file is open
    {
        filestrm.close(); // Close the file stream
    }
}