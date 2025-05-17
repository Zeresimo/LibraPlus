#include <iostream>
#include <fstream>
#include "LibraUsers.h"
#include "LibraBook.h"
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

void Librarian::Displaymenu() const // Override Displaymenu function
    {
        std::cout << "Librarian Menu:" << std::endl;
        std::cout << "1. Add Book\n2. View Borrowed Books\n3. View whole collection\n4. My Info \n5. Exit" << std::endl; 
    }

void Librarian::displayInfo() const // Override displayInfo function
    {
        std::cout << "Librarian Username: " << username << std::endl; 
        std::cout << "Privileges: Full access to the library system." << std::endl; 
    }

void Librarian::handleLibrarianMenu(User* user, LibBook& bookManager)
{
    int choice;
    do
    {
        user->Displaymenu(); // Display librarian menu
        std::cout << "Enter your choice: ";
        std::cin >> choice; // Get user choice from input

        if (choice == 1) // If user chooses to add a book
        {
            bookManager.createbook(); // Call createbook function
        }

        else if (choice == 2) // If user chooses to view borrowed books
        {
            bookManager.BorrowedBooks(); // Call BorrowedBooks function
        }

        else if (choice == 3) // If user chooses to view the whole collection
        {
            bookManager.displayCollection(); // Call displayCollection function
        }

        else if (choice == 4) // If user chooses to view their information
        {
            user->displayInfo(); // Call displayInfo function
        }

        else
        {
            std::cout << "Invalid choice. Please try again." << std::endl; // Prompt for re-entry
        }

    } while (choice != 5); // Loop until user chooses to exit

    std::cout << "Exiting Librarian Menu." << std::endl; // Exit message
    
}

void Student::Displaymenu() const // Override Displaymenu function
    {
        std::cout << "Student Menu:" << std::endl;
        std::cout << "1. Borrow Book\n2. Return Book\n3. View borrowed books \n4. View whole collection\n5. My Info \n6. Exit" << std::endl; 
    }

void Student::displayInfo() const // Override displayInfo function
    {
        std::cout << "Student Username: " << username << std::endl; // Display student information
        std::cout << "Privileges: Limited access to the library system." << std::endl; // Display privileges
    }

void Student::handleStudentMenu(User* user, LibBook& bookManager)
{
    int choice;

    do
    {
        user->Displaymenu(); // Display student menu
        std::cout << "Enter your choice: ";
        std::cin >> choice; // Get user choice from input

        if (choice == 1) // If user chooses to borrow a book
        {
            std::string title;
            std::cout << "Enter the title of the book you want to borrow: ";
            std::cin.ignore(); // Ignore any newline characters left in the input buffer
            std::getline(std::cin, title); // Get book title from input
            bookManager.BorrowBook(title, user->getUsername()); // Call BorrowBook function
        }

        else if (choice == 2) // If user chooses to return a book
        {
            std::string title;
            std::cout << "Enter the title of the book you want to return: ";
            std::cin.ignore(); // Ignore any newline characters left in the input buffer
            std::getline(std::cin, title); // Get book title from input
            bookManager.ReturnBook(title, user->getUsername()); // Call ReturnBook function
        }

        else if (choice == 3) // If user chooses to view borrowed books
        {
            bookManager.BorrowedBooksByUser(user->getUsername()); // Call BorrowedBooksByUser function
        }

        else if (choice == 4) // If user chooses to view the whole collection
        {
            bookManager.displayCollection(); // Call displayCollection function
        }

        else if (choice == 5) // If user chooses to view their information
        {
            user->displayInfo(); // Call displayInfo function
        }

        else
        {
            std::cout << "Invalid choice. Please try again." << std::endl; // Prompt for re-entry
        }

    } while (choice != 6); // Loop until user chooses to exit

    std::cout << "Exiting Student Menu." << std::endl; // Exit message
    
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

User* UserManagement::loginUser()
{
    std::string username, password;
    std::cout << "Welcome to the Library System!" << std::endl;
    std::cout << "Please log in to continue." << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    for(int i = 0; i < 3; i++)
    {
        std::cout << "Enter username: ";
        std::cin >> username; // Get username from input
        std::cout << "Enter password: ";
        std::cin >> password; // Get password from input

        for (auto user : LoginInfo) // Iterate through the vector of users
        {
            if (user->getUsername() == username && user->checkPassword(password)) // Check if username and password match
            {
                return user; // Return the user object if credentials are correct
            }
        }

        std::cout << "Invalid username or password. Please try again." << std::endl; // Prompt for re-entry

    }

    std::cout << "Too many failed attempts. Exiting." << std::endl; // Exit if too many attempts
    return nullptr; // Return nullptr if no matching user is found

}

User* UserManagement::handleLoginOrRegister()
{
    int choice;

    while(true)
    {
        std::cout << "1. Register\n2. Login\n3. Exit" << std::endl; // Display options
        std::cout << "Please choose an option: ";
        std::cin >> choice; // Get user choice from input

        if(choice == 1) // If user chooses to register
        {
            addUser(); // Call addUser function
        }

        else if(choice == 2) // If user chooses to login
        {
            User* user = loginUser(); // Call loginUser function
            if(user != nullptr) // If user is not null
            {
                return user; // Return the logged-in user
            }
        }

        else if(choice == 3) // If user chooses to exit
        {
            std::cout << "Exiting program." << std::endl; // Exit message
            exit(0); // Exit the program
        }

        else
        {
            std::cout << "Invalid choice. Please try again." << std::endl; // Prompt for re-entry
        }

    }

}

void UserManagement::handleRoleMenu(User* user, LibBook& bookManager)
{
    if (user == nullptr) return; // Exit the function if user is null

    if (user->canAddBook()) // If user is librarian
    {
        std::cout << "Welcome, Librarian!" << std::endl; // Welcome message
        static_cast<Librarian*>(user)->handleLibrarianMenu(user, bookManager); // Assumes librarian role to continue
    }

    else // If user is student
    {
        std::cout << "Welcome, Student!" << std::endl; // Welcome message
        static_cast<Student*>(user)->handleStudentMenu(user, bookManager); // Assumes student role to continue
    }

}

bool UserManagement::saveUsersToFile(const std::string& filename)
{
    std::ofstream outFile(filename); // Open file for writing

    if (!outFile) // Check if file opened successfully
    {
        std::cerr << "Error opening file for writing." << std::endl; // Error message
        return false; // Exit function if file cannot be opened
    }

    outFile << "Username,Password,Role\n"; // Write header to file

    for (const auto& user : LoginInfo) // Iterate through the vector of users
    {
        if (user != nullptr)
        {
            outFile << user->getUsername() << "," << user->getPassword() << "," << (user->canAddBook() ? "Librarian" : "Student") << std::endl; 
            // Write username, password, role to file
        }
        
    }

    outFile.close(); // Close the file
    return true; // Return true to indicate success
}

bool UserManagement::loadUsersFromFile(const std::string& filename)
{
    std::ifstream inFile(filename);

    if (!inFile)
    {
        std::cerr << "Error opening file for reading." << std::endl;
        return false;
    }

    std::string line;
    std::getline(inFile, line); // Skip header

    while (std::getline(inFile, line))
    {
        std::stringstream ss(line);
        std::string username, password, role;

        std::getline(ss, username, ',');
        std::getline(ss, password, ',');
        std::getline(ss, role, ',');

        if (role == "Librarian")
        {
            LoginInfo.push_back(new Librarian(username, password));
        }

        else if (role == "Student")
        {
            LoginInfo.push_back(new Student(username, password));
        }
        
    }

    inFile.close();
    return true;
}

UserManagement::~UserManagement()
{
    for (auto user : LoginInfo) // Iterate through the vector of users
    {
        delete user; // Delete each user pointer to free memory
    }
    LoginInfo.clear(); // Clear the vector
}