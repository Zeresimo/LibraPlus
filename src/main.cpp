#include <iostream>
#include "LibraFile.h"
#include "LibraBook.h"
#include "LibraUsers.h"
using namespace std;

int main()
{
    LibBook bookManager;
    UserManagement userManager;

    // Automatically load users
    userManager.loadUsersFromFile("users.csv");

    // Prompt for filename and action with temporary LibFile instance
    LibFile temp;
    std::pair<std::string, int> fileData = temp.PromptFileOption();
    std::string filename = fileData.first;
    int choice = fileData.second;

    // Create a new fileManager with filename
    LibFile FileManager(filename);

    // If opening an existing file, load book data
    if (choice == 2) {
        if (FileManager.csvload(bookManager) == 0) {
            std::cout << "File successfully loaded!" << std::endl;
        } 

        else 
        {
            std::cout << "Failed to load file." << std::endl;
        }
    } 

    else 
    {
        std::cout << "New file created!" << std::endl;
    }

    // Handle login/registration and roles
    User* user = userManager.handleLoginOrRegister();
    userManager.handleRoleMenu(user, bookManager);

    FileManager.savetoCSV(bookManager); // Save book data to file

    // Save user data on exit
    userManager.saveUsersToFile("users.csv");

    return 0;
}
