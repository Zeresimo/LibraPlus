#ifndef LIBRABOOK_H // If LIBRABOOK_H is not defined
#define LIBRABOOK_H // Define LIBRABOOK_H

#include <string>

class LibBook // Class definition LibBook
{
public: // Methods or variables that can be accessed from outside the class
    // Constructor: initializes a book with a title, author, and year
    LibBook(const std::string& title, const std::string& author, int year);

    // Getter for the title of the book
    std::string getTitle() const;

    // Setter for the title of the book
    void setTitle(const std::string& title);

    // Getter for the author of the book
    std::string getAuthor() const;

    // Setter for the author of the book
    void setAuthor(const std::string& author);

    // Getter for the year the book was published
    int getYear() const;

    // Setter for the year the book was published
    void setYear(int year);

    //  Displays the book's information
    void displayBookInfo() const;

private: // Methods or variables that can only be accessed from within the class
    std::string title;
    std::string author;
    int year;
}; // Signals the end of the class definition LibBook

#endif // LIBRABOOK_H
