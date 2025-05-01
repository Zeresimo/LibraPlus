#ifndef LIBRABOOK_H // If LIBRABOOK_H is not defined
#define LIBRABOOK_H // Define LIBRABOOK_H

#include <string>
#include <vector> // Include vector library for dynamic arrays
#include <unordered_map> // Include unordered_map library for hash tables

class LibBook // Class definition LibBook
{
public: // Methods or variables that can be accessed from outside the class
    struct Book
    {
        std::string title; // Title of the book
        std::string author; // Author of the book
        std::string genre; // Genre of the book
        bool borrowed; // Borrowed status of the book
    };
    // Constructor: initializes a book with a title, author, and year
    LibBook(const std::string& title, const std::string& author, int year);

    // Getter for the title of the book
    std::string LibBook::getTitle() const;

    // Getter for the author of the book
    std::string LibBook::getAuthor() const;

    // Getter for the genre of the book
    std::string LibBook::getGenre() const;

    //  Displays the book's information
    void displayBookInfo() const;

    // Returns the collection of books
    std::vector<Book>& getBooks();

    // Creates a new book as defined by user
    void createbook(); 

    // Adds a book to the collection
    void addBook(const Book& book); 

private: // Methods or variables that can only be accessed from within the class
    std::string title;
    std::string author;
    int year;
    std::vector<Book> LibraPlus; // Vector to store books
    std::unordered_map<std::string, std::vector<Book*>> titleIndex; // Map to index books by title
    std::unordered_map<std::string, std::vector<Book*>> authorIndex; // Map to index books by author
    std::unordered_map<std::string, std::vector<Book*>> genreIndex; // Map to index books by genre

}; // Signals the end of the class definition LibBook

#endif // LIBRABOOK_H
