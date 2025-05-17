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
        std::string borrowedby; // User who borrowed the book
    };

    //  Displays the book's information
    void displayCollection() const;

    // Returns the collection of books
    std::vector<Book>& getBooks();

    // Displays books based on genre
    void ByGenre(const std::string& genre) const;

    // Displays books based on title
    void ByTitle(const std::string& title) const;

    // Displays books based on author
    void ByAuthor(const std::string& author) const;

    // Creates a new book as defined by user
    void createbook(); 

    // Adds a book to the collection
    void addBook(const Book& book); 

    bool BorrowBook(const std::string& title, const std::string& username); // Borrow a book
    bool ReturnBook(const std::string& title, const std::string& username); // Return a book

    void BorrowedBooks() const; // Displays borrowed books
    void BorrowedBooksByUser(const std::string& username) const; // Displays borrowed books by user

private: // Methods or variables that can only be accessed from within the class
    std::vector<Book> LibraPlus; // Vector to store books
    std::unordered_map<std::string, std::vector<Book*>> titleIndex; // Map to index books by title
    std::unordered_map<std::string, std::vector<Book*>> authorIndex; // Map to index books by author
    std::unordered_map<std::string, std::vector<Book*>> genreIndex; // Map to index books by genre

}; // Signals the end of the class definition LibBook

#endif // LIBRABOOK_H
