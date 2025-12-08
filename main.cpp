#include <iostream>
#include <limits>    // For numeric_limits
#include "Hospital.h"
using namespace std;

int main() {
    // Create our one Hospital object.
    Hospital er_sim;

    // Variable to hold the user's menu selection
    int choice = 0;

    // The main application loop. It continues until the user selects '8' (Exit).
    while (choice != 8) {
        // Display the menu and get the user's choice
        er_sim.displayMenu();

        // --- Input Validation ---
        if (!(cin >> choice)) {
            cout << "\n*** Invalid input. Please enter a number. ***\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        // --- Action ---
        switch (choice) {
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
            er_sim.showUpgradeMenu();
            break;
        case 7:
            er_sim.showFloorPlan();
            break;
        case 8:
            cout << "\nExiting ER Simulator. Thank you!\n";
            break;
        default:
            if (choice != -1) {
                cout << "\n*** Invalid choice. Please select from 1-8. ***\n";
            }
            break;
        }

        // --- Pause ---
        if (choice != 8) {
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            clearScreen();
        }
    }

    return 0; // Program finished successfully
}