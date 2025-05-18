#ifndef LIBRAUSERS_H
#define LIBRAUSERS_H

#include <string>
#include <vector>
#include "LibraBook.h" // Include LibraBook header for book management

class User // Class definition User
{
protected:
    std::string username;
    std::string password;
public:
    // Constructor to initialize username and password
    User(const std::string& user, const std::string& pass) 
    : username(user), password(pass) {}
    // Virtual destructor for proper cleanup of derived classes
    virtual ~User() {}
    // Pure virtual function to display user menu 
    virtual void Displaymenu() const = 0;
    // Pure virtual function to display user information 
    virtual void displayInfo() const = 0; 

    void searchMenu(const LibBook& bookManager); // Function to search for books in the library
    void clearScreen(); // Function to clear the console screen;
    
    std::string getUsername() const { return username; } 
    std::string getPassword() const { return password; } 

    bool checkPassword(const std::string& pass) const { return password == pass; } 

    // Functions to check user privileges
    virtual bool canAddBook() const { return false; }
    virtual bool canRemoveBook() const { return false; }
    virtual bool canViewBorrowedBooks() const { return false; }
    virtual bool canBorrowBook() const { return false; }
};

class Librarian : public User // Class definition Librarian inheriting from User
{
public:
    using User::User; // Inherit constructor from User
    void Displaymenu() const override; // Override Displaymenu function
    void displayInfo() const override; // Override displayInfo function
    bool canAddBook() const override { return true; } // Librarian can add books
    bool canRemoveBook() const override { return true; } // Librarian can remove books
    bool canViewBorrowedBooks() const override { return true; } // Librarian can view borrowed books
    void handleLibrarianMenu(User* user, LibBook& bookManager); // Function to handle librarian menu
};

class Student : public User // Class definition Student inheriting from User
{
public:
    using User::User; // Inherit constructor from User
    void Displaymenu() const override; // Override Displaymenu function
    void displayInfo() const override; // Override displayInfo function
    bool canBorrowBook() const override { return true; } // Student can borrow books
    void handleStudentMenu(User* user, LibBook& bookManager); // Function to handle student menu 
};

class UserManagement // Class definition UserManagement
{
private:
    std::vector<User*> LoginInfo; // Vector to store users
public:
    void addUser(); // Function to add a new user
    User* loginUser(); // Function to log in a user
    User* handleLoginOrRegister(); // Function to handle login or registration
    void handleRoleMenu(User* user, LibBook& bookManager); // Function to handle role menu
    bool saveUsersToFile(const std::string& filename); // Function to save users to a file
    bool loadUsersFromFile(const std::string& filename); // Function to load users from a file
    ~UserManagement(); // Destructor to clean up user pointers
};

#endif // LIBRAUSERS_H
