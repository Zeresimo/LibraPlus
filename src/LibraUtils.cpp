#include <iostream>
#include <cstdlib>
#include "LibraUtils.h"

void clearScreen() 
{
#ifdef _WIN32
    std::system("cls"); // Windows
#else
    std::system("clear"); // Unix/Linux/macOS
#endif
}
