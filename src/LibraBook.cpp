#include <iostream>
#include "LibraBook.h"


LibBook::LibBook(const std::string &title, const std::string &author, int year)
{
}

std::string LibBook::getTitle() const
{

}

std::string LibBook::getAuthor() const
{

}

std::string LibBook::getGenre() const
{

}

void LibBook::displayBookInfo() const
{

}

std::vector<LibBook::Book>& LibBook::getBooks()
{
    return LibraPlus; // Return the collection of books
}

void LibBook::createbook() // Creates a new book as defined by user
{
    Book newBook; // Create a new Book object

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