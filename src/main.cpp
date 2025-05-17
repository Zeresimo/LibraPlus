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
    userManager.loadUsersFromFile("LoginInfo.csv");

    // Prompt for filename and action with temporary LibFile instance
    LibFile temp;
    pair<string, int> fileData = temp.PromptFileOption();
    string filename = fileData.first;
    int choice = fileData.second;

    // Create a new fileManager with filename
    LibFile FileManager(filename);

    // If opening an existing file, load book data
    if (choice == 2) 
    {

        if (FileManager.loadFromCSV(bookManager) == 0) 
        {
            cout << "File successfully loaded!" << endl;
        } 

        else 
        {
            cout << "Failed to load file." << endl;
        }
        
    } 

    else 
    {
        cout << "New file created!" << endl;
    }

    // Handle login/registration and roles
    User* user = userManager.handleLoginOrRegister();
    userManager.handleRoleMenu(user, bookManager);

    FileManager.saveToCSV(bookManager); // Save book data to file

    // Save user data on exit
    userManager.saveUsersToFile("LoginInfo.csv");

    return 0;
}
