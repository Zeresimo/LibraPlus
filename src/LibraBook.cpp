#include <iostream>
#include "LibraBook.h"
#include <unordered_map>
#include <string>
#include <vector>

void LibBook::ByGenre(const std::string& genre) const
{
    auto it = genreIndex.find(genre); // Find the genre in the index

    if (it != genreIndex.end()) // If the genre exists in the index
    {
        std::cout << "Books in genre " << genre << ":" << std::endl;
        for (const Book* book : it->second) // Iterate through the books in that genre
        {
            std::cout << "Title: " << book->title << "\n Author: " << book->author << "\n Borrowed: " << (book->borrowed ? "Yes" : "No") << "\n -------- " << std::endl; 
        }
    }

    else // If the genre does not exist in the index
    {
        std::cout << "No books found in genre " << genre << "." <<  std::endl; 
    }
}

void LibBook::ByTitle(const std::string& title) const
{
    auto it = titleIndex.find(title); // Find matching books by title

    if (it != titleIndex.end()) // If the title exists in the index
    {
        for (const Book* book: it->second) // Loop through the matching books
        {
            std::cout << "Title: " << book->title << "\n Author: " << book->author << "\n Genre: " << book->genre << "\n Borrowed: " << (book->borrowed ? "Yes" : "No") << "\n -------- " << std::endl; 
        }
    }

    else // If the title does not exist in the index
    {
        std::cout << "No books found with title " << title << "." << std::endl; 
    }
    return;
}

void LibBook::ByAuthor(const std::string& author) const
{
    auto it = authorIndex.find(author); // Find matching books by author

    if (it != authorIndex.end()) // If the author exists in the index
    {
        for (const Book* book: it->second) // Loop through the matching books
        {
            std::cout << "Title: " << book->title << "\n Author: " << book->author << "\n Genre: " << "\n Borrowed: " << (book->borrowed ? "Yes" : "No") << "\n -------- " << std::endl; 
        }
    }

    else // If the author does not exist in the index
    {
        std::cout << "No books found by author " << author << "." << std::endl; 
    }
    return;
}

void LibBook::displayCollection() const
{
    if (LibraPlus.empty()) // If the collection is empty
    {
        std::cout << "No books in the collection." << std::endl; 
        return; 
    }

    std::cout << "Books in the collection:" << std::endl;
    for(const Book& book : LibraPlus) // Iterate through the collection vector
    {
        std::cout << "Title: " <<  book.title << "\n" <<", Author: " << book.author << 
        "\n" << ", Genre: " << book.genre << "\n" << ", Borrowed: " << (book.borrowed ? "Yes" : "No") << std::endl; 
    }
    return;
}

std::vector<LibBook::Book>& LibBook::getBooks()
{
    return LibraPlus; // Return the collection of books
}

void LibBook::createbook() // Creates a new book as defined by user
{
    Book newBook; // Create a new Book object
    newBook.borrowed = false; // Set borrowed status to false
    newBook.borrowedby = ""; // Set borrowed by to empty string

    std::cout << "Enter the title of the book: ";
    std::getline(std::cin, newBook.title); // Get title from user

    std::cout << "Enter the author of the book: ";
    std::getline(std::cin, newBook.author); // Get author from user

    std::cout << "Enter the genre of the book: ";
    std::getline(std::cin, newBook.genre); // Get genre from user

    addBook(newBook); // Add the book to the collection
}

void LibBook::addBook(const Book& book) // Adds book into the collection vector
{
    LibraPlus.push_back(book); // Add book to the collection vector
    Book* ptr = &LibraPlus.back(); // Get pointer to the last book added
    ptr->borrowed = false; // Set borrowed status to false
    titleIndex[book.title].push_back(ptr); // Index book by title
    authorIndex[book.author].push_back(ptr); // Index book by author
    genreIndex[book.genre].push_back(ptr); // Index book by genre
}

bool LibBook::BorrowBook(const std::string& title, const std::string& username)
{
    auto it = titleIndex.find(title); // Find the book by title

    if (it != titleIndex.end()) // If the book exists
    {
        for (Book* book : it->second) // Loop through the matching books
        {
            if (!book->borrowed) // If the book is not borrowed
            {
                book->borrowed = true; // Mark the book as borrowed
                book->borrowedby = username; // Set the user who borrowed the book
                std::cout << "Book borrowed successfully." << std::endl; 
                return true; // Return success
            }
        }
    }

    std::cout << "Book is already borrowed." << std::endl; 
    return false; // Return failure
}

bool LibBook::ReturnBook(const std::string& title, const std::string& username)
{
    auto it = titleIndex.find(title); // Find the book by title

    if (it != titleIndex.end()) // If the book exists
    {
        for (Book* book : it->second) // Loop through the matching books
        {
            if (book->borrowed && book->borrowedby == username) // If the book is borrowed by the user
            {
                book->borrowed = false; // Mark the book as returned
                book->borrowedby = ""; // Clear the user who borrowed the book
                std::cout << "Book returned successfully." << std::endl; 
                return true; // Return success
            }
        }
    }

    std::cout << "Book return failed. Book may not be borrowed by you." << std::endl;
    return false; // Return failure
}

void LibBook::BorrowedBooks() const
{
    std::cout << "Borrowed books:" << std::endl; // Display borrowed books
    bool found = false; // Flag to check if any borrowed books exist

    for (const auto& pair : titleIndex)
    {
        for (const Book* book : pair.second) // Loop through the books in the index
        {
            if (book->borrowed) // If the book is borrowed
            {
                std::cout << "Title: " << book->title << "\n Author: " << book->author << "\n Genre: " << book->genre << "\n Borrowed by: " << book->borrowedby << "\n -------- " << std::endl; 
                found = true; // Set flag to true
            }
        }
    }

    if (!found) // If no borrowed books exist
    {
        std::cout << "No borrowed books." << std::endl; // Display message
    }
}

void LibBook::BorrowedBooksByUser(const std::string& username) const
{
    std::cout << "Borrowed books by " << username << std::endl; // Display borrowed books
    bool found = false; // Flag to check if any borrowed books exist

    for (const auto& pair : titleIndex)
    {
        for (const Book* book : pair.second) // Loop through the books in the index
        {
            if (book->borrowedby == username) // If the book is borrowed
            {
                std::cout << "Title: " << book->title << "\n Author: " << book->author << "\n Genre: " << book->genre << "\n -------- " << std::endl; 
                found = true; // Set flag to true
            }
        }
    }
    
    if (!found) // If no borrowed books exist
    {
        std::cout << "No borrowed books." << std::endl; // Display message
    }
}