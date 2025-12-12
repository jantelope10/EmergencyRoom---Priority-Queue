#include "Hospital.h"
#include "ClearScreen.h"

int main() 
{
    // Create the Hospital object
    Hospital er_sim;

    // Variable to hold the user's menu selection
    int choice = 0;

    // The main application loop, it continues until the user selects '8' (exit).
    while (choice != 8) 
    {
        // Display the menu and get the user's choice
        er_sim.displayMenu();
        cin >> choice;

        // Checks if an integer wasn't inputted, clears input if true
        if (cin.fail()) 
        {
            cout << "\nERROR: Invalid input. Please enter a number.\n";
            cin.clear();
            while (cin.get() != '\n') {}
            choice = -1;
            cout << "\nPress Enter to continue...";
            cin.get();
            
            clearScreen();
        }

        // Action to decide function
        switch (choice) 
        {
        case 1:
            er_sim.admitRandomPatient();
            break;
        case 2:
            er_sim.addPatientManually();
            break;
        case 3:
            er_sim.treatNextPatient();
            break;
        case 4:
            er_sim.viewNextPatient();
            break;
        case 5:
            er_sim.viewAllPatients();
            break;
        case 6:
            clearScreen();
            er_sim.showUpgradeMenu();
            break;
        case 7:
            er_sim.showFloorPlan();
            break;
        case 8:
            cout << "\nExiting ER Simulator. Thank you!\n";
            break;
        default:
            if (choice != -1) 
            {
                cout << "\nERROR: Invalid choice. Please select from 1-8.\n";
            }
            break;
        }

        // Continuation
        if (choice != 8 && choice != -1) 
        {
            cout << "\nPress Enter to continue...";
            while (cin.get() != '\n') {}
            cin.get();

            clearScreen();
        }
    }

    return 0;
}