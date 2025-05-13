#include <iostream>
#include "LibraUsers.h"
#include <vector>
#include <string>
#include <algorithm>

void Librarian::Displaymenu() const // Override Displaymenu function
    {
        std::cout << "Librarian Menu:" << std::endl;
        std::cout << "1. Add Book\n2. Remove Book\n3. View Borrowed Books\n4. Exit\n" << std::endl; 
    }

void Librarian::displayInfo() const // Override displayInfo function
    {
        std::cout << "Librarian Username: " << username << std::endl; 
        std::cout << "Privileges: Full access to the library system." << std::endl; 
    }

void Student::Displaymenu() const // Override Displaymenu function
    {
        std::cout << "Student Menu:" << std::endl;
        std::cout << "1. Borrow Book\n2. Return Book\n3. Exit" << std::endl; 
    }

void Student::displayInfo() const // Override displayInfo function
    {
        std::cout << "Student Username: " << username << std::endl; // Display student information
        std::cout << "Privileges: Limited access to the library system." << std::endl; // Display privileges
    }


void UserManagement::addUser()
{
    std::string username, password, confirmPassword;
    char userType;
    int counter = -1;
    std::cout << "Are you 1.) Librarian or 2.) Student? (1/2): ";
    std::cin >> userType; // Get user type from input
    while (userType != '1' && userType != '2') // Validate input
    {
        std::cout << "Invalid input. Please enter 1 for Librarian or 2 for Student: ";
        std::cin >> userType; // Get user type from input
    }
    // Checks if username already exists
    while (counter == -1)
    {
        bool usernameExists = false; // Flag to check if username exists
        std::cout << "Enter username: ";
        std::cin >> username;
        for (const auto& user : LoginInfo) // Check if username already exists
        {
            if (user->getUsername() == username) // If username exists
            {
                std::cout << "Username already exists. Please choose a different one." << std::endl;
                usernameExists = true; // Set flag to true
                break; // Continue to prompt for a new username 
            }
        }
        if (!usernameExists)
        {
            counter = 0; // Set counter to 0 to exit the loop
        }
        
    }

    while(true) // Loop until valid password is entered
    {
        std::cout << "Enter password: ";
        std::cin >> password; // Get password from input
        std::cout << "Confirm password: ";
        std::cin >> confirmPassword; // Get confirmation password from input
        if (password == confirmPassword) // Check if passwords match
        {
            break; // Exit loop if passwords match
        }
        else
        {
            std::cout << "Passwords do not match. Please try again." << std::endl; // Prompt for re-entry
        }
    }

    if (userType == '1') // If user is a librarian
    {
        LoginInfo.push_back(new Librarian(username, password)); // Add new librarian to the vector
    }
    else if (userType == '2') // If user is a student
    {
        LoginInfo.push_back(new Student(username, password)); // Add new student to the vector
    }
}

UserManagement::~UserManagement()
{
    for (auto user : LoginInfo) // Iterate through the vector of users
    {
        delete user; // Delete each user pointer to free memory
    }
    LoginInfo.clear(); // Clear the vector
}