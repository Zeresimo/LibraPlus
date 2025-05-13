#ifndef LIBRAUSERS_H
#define LIBRAUSERS_H

#include <string>
#include <vector>

class User // Class definition User
{
protected:
    std::string username;
    std::string password;
public:
    User(const std::string& user, const std::string& pass) // Constructor to initialize username and password
    : username(user), password(pass) {}
    virtual ~User() {} // Virtual destructor for proper cleanup of derived classes

    virtual void Displaymenu() const = 0; // Pure virtual function to display user menu
    virtual void displayInfo() const = 0; // Pure virtual function to display user information
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
};

class Student : public User // Class definition Student inheriting from User
{
public:
    using User::User; // Inherit constructor from User
    void Displaymenu() const override; // Override Displaymenu function
    void displayInfo() const override; // Override displayInfo function
    bool canBorrowBook() const override { return true; } // Student can borrow books
};

class UserManagement // Class definition UserManagement
{
private:
    std::vector<User*> LoginInfo; // Vector to store users
public:
    void addUser(); // Function to add a new user
    ~UserManagement(); // Destructor to clean up user pointers
};

#endif // LIBRAUSERS_H
