#pragma once

#include <cstdlib>

// Inline allows this function to be defined in a header file
inline void clearScreen() 
{
    // If the system is Windows
#if defined(_WIN32)
    system("cls");
    // If the system is Unix-like
#else
    system("clear");
#endif
}