#include "Hospital.h"
#include "Patient.h"
#include <iostream>
#include <string>
#include <limits>    // For numeric_limits
#include <stdexcept> // For invalid_argument (used in manual input)
using namespace std;

// --- Constructor ---
// Initializes the random number generator with a true random seed
// and calls the helper function to populate our data banks.
Hospital::Hospital() : rng(random_device{}()), hospital_balance(10.0), doctor_count(1), bed_capacity(3){
    initializeData();
}

// --- Private Helper Function ---
void Hospital::initializeData() {
    // Populate the illness bank with pairs of (Illness Name, Base Severity)
    illness_bank.push_back(make_pair("Common Cold", 1));
    illness_bank.push_back(make_pair("Minor Cut", 2));
    illness_bank.push_back(make_pair("Flu", 3));
    illness_bank.push_back(make_pair("Broken Arm", 4));
    illness_bank.push_back(make_pair("Pneumonia", 5));
    illness_bank.push_back(make_pair("Appendicitis", 6));
    illness_bank.push_back(make_pair("Severe Asthma Attack", 7));
    illness_bank.push_back(make_pair("Heart Attack", 8));
    illness_bank.push_back(make_pair("Stroke", 9));
    illness_bank.push_back(make_pair("Multi-Organ Failure", 10));

    // Populate the random name bank
    random_names.push_back("John Smith");
    random_names.push_back("Jane Doe");
    random_names.push_back("Robert Brown");
    random_names.push_back("Emily Davis");
    random_names.push_back("Michael Wilson");
    random_names.push_back("Sarah Johnson");
}

// --- Phase 1: Core ER Functions ---

void Hospital::displayMenu() {
    cout << "\n=========================================\n";
    cout << "== EMERGENCY ROOM SIMULATOR - MainMenu ==\n";
    cout << "=========================================\n";
    cout << "|  Current Status:\n";
    cout << "|   - Balance:   $" << hospital_balance << "\n";
    cout << "|   - Doctors:   " << doctor_count << "\n";
    cout << "|   - Beds:      " << er_queue.size() << " / " << bed_capacity << " (Waiting: " << er_queue.size() << ")\n";
    cout << "-----------------------------------------\n";
    cout << "|  Patient Options:                     |\n";
    cout << "|    1. Admit Random Patient            |\n";
    cout << "|    2. Add Patient Manually            |\n";
    cout << "|    3. Treat Next Patient(s)           |\n";
    cout << "|    4. View Next Patient               |\n";
    cout << "|    5. View All Waiting Patients       |\n";
    cout << "-----------------------------------------\n";
    cout << "|  Hospital Options:                    |\n";
    cout << "|    6. Go to Upgrade Menu              |\n";
    cout << "|    7. Show Hospital Floor Plan        |\n"; 
    cout << "|    8. Exit Simulation                 |\n"; 
    cout << "-----------------------------------------\n";
    cout << "Enter your choice (1-8): "; 
}

void Hospital::admitRandomPatient() {
    // --- Bed Capacity Check ---
    // If the queue is full, we can't admit anyone.
    if (er_queue.size() >= bed_capacity) {
        cout << "\n*** The ER is at full capacity! Cannot admit new patient. ***\n";
        return; // Exit the function
    }

    // --- Robustness Check ---
    if (illness_bank.empty() || random_names.empty()) {
        cout << "\n*** Error: Data banks are empty. Cannot admit random patient. ***\n";
        return; // Exit the function early
    }

    // --- Fix for the Warning (C4267) ---
    uniform_int_distribution<int> illness_dist(0, static_cast<int>(illness_bank.size() - 1));
    uniform_int_distribution<int> name_dist(0, static_cast<int>(random_names.size() - 1));
    uniform_int_distribution<int> age_dist(1, 90);

    // Get random data
    int name_index = name_dist(rng);
    int illness_index = illness_dist(rng);
    int random_age = age_dist(rng);

    string name = random_names[name_index];
    string illness = illness_bank[illness_index].first;
    int severity = illness_bank[illness_index].second;

    // Create and add the new patient
    Patient newPatient(name, random_age, illness, severity);
    er_queue.push(newPatient);

    cout << "\n*** New Patient Admitted ***\n";
    cout << newPatient << endl;
}

void Hospital::addPatientManually() {
    // --- Bed Capacity Check ---
    if (er_queue.size() >= bed_capacity) {
        cout << "\n*** The ER is at full capacity! Cannot admit new patient. ***\n";
        return; // Exit the function
    }

    string name, illness;
    int age, severity;

    cout << "\n--- Manual Patient Admission ---\n";

    // --- Get Name ---
    cout << "Enter patient name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    // --- Get Age ---
    while (true) {
        // ... (rest of the age input logic) ...
        cout << "Enter patient age: ";
        if (cin >> age && age > 0 && age < 130) {
            break; // Good input
        }
        else {
            cout << "Invalid age. Please enter a number between 1 and 129.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // --- Get Illness ---
    cout << "Enter patient illness: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, illness);

    // --- Get Severity ---
    while (true) {
        // ... (rest of the severity input logic) ...
        cout << "Enter severity (1-10): ";
        if (cin >> severity && severity >= 1 && severity <= 10) {
            break; // Good input
        }
        else {
            cout << "Invalid severity. Please enter a number between 1 and 10.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Create and add the new patient
    Patient newPatient(name, age, illness, severity);
    er_queue.push(newPatient);

    cout << "\n*** Manual Patient Admitted ***\n";
    cout << newPatient << endl;
}

void Hospital::treatNextPatient() {
    if (er_queue.empty()) {
        cout << "\nThere are no patients to treat.\n";
        return;
    }

    cout << "\n*** Doctors are treating patients... ***\n";

    int patientsTreated = 0;
    double payout = 0.0;

    // Loop for however many doctors we have
    for (int i = 0; i < doctor_count; ++i) {
        // We must check if the queue is empty *inside* the loop
        if (er_queue.empty()) {
            cout << "All available patients have been treated.\n";
            break; // Stop the loop if we run out of patients
        }

        // Get a copy of the top patient
        Patient patientToTreat = er_queue.top();

        // Remove them from the queue
        er_queue.pop();

        // Calculate the payout (e.g., $100 per severity point)
        double patientPayout = patientToTreat.getSeverity() * 100.0;
        payout += patientPayout;

        // Print this specific patient's details
        cout << "\nDoctor " << (i + 1) << " treated " << patientToTreat.getName() << " (Severity: " << patientToTreat.getSeverity() << ")\n";
        cout << "  - Payout: $" << patientPayout << "\n";

        patientsTreated++;
    }

    // Add the total payout to our balance
    hospital_balance += payout;

    // Print a summary of the turn
    cout << "\n--- Treatment Round Summary ---\n";
    cout << "Patients Treated: " << patientsTreated << "\n";
    cout << "Total Payout Earned: $" << payout << "\n";
    cout << "New Hospital Balance: $" << hospital_balance << "\n";
}

void Hospital::viewNextPatient() {
    if (er_queue.empty()) {
        cout << "\nThere are no patients in the queue.\n";
        return;
    }

    // Get a const reference to the top patient (efficient)
    const Patient& nextPatient = er_queue.top();

    cout << "\n*** Next Patient in Queue ***\n";
    cout << nextPatient << endl;
}

void Hospital::viewAllPatients() {
    if (er_queue.empty()) {
        cout << "\nThere are no patients in the queue.\n";
        return;
    }

    cout << "\n--- Full Patient List (Highest Priority First) ---\n";

    // Create a COPY of the main queue
    priority_queue<Patient, vector<Patient>, ComparePatient> temp_queue = er_queue;

    int count = 1;
    // Loop through the COPY, printing and popping until it's empty
    while (!temp_queue.empty()) {
        Patient p = temp_queue.top();
        temp_queue.pop();

        cout << "\n" << count++ << ". " << p.getName() << " (Severity: " << p.getSeverity() << ")\n";
        cout << "   Age: " << p.getAge() << ", Illness: " << p.getIllness() << "\n";
    }
    cout << "---------------------------------------------------\n";
}

// --- Phase 2: Private Helpers ---

// Calculates the scaling cost for the next bed
double Hospital::getNextBedCost() const {
    // Example formula: Base cost of 100, plus 125 for every existing bed
    return 100.0 + (bed_capacity * 125.0);
}

// Calculates the scaling cost for the next doctor
double Hospital::getNextDoctorCost() const {
    // Example formula: Base cost of 1000, plus 500 for every existing doctor
    return 1000.0 + (doctor_count * 500.0);
}

// --- Phase 2: Simulation Functions ---

void Hospital::showUpgradeMenu() {
    int choice = 0;
    while (choice != 3) {
        // Clear the screen for a clean menu
        clearScreen();

        cout << "--- Hospital Upgrade Menu ---\n";
        cout << "Current Balance: $" << hospital_balance << "\n";
        cout << "---------------------------------\n";

        // Use our helper functions to get the current costs
        double bedCost = getNextBedCost();
        double doctorCost = getNextDoctorCost();

        cout << "1. Buy Bed (Cost: $" << bedCost << ")\n";
        cout << "   (Current Beds: " << bed_capacity << ")\n\n";
        cout << "2. Hire Doctor (Cost: $" << doctorCost << ")\n";
        cout << "   (Current Doctors: " << doctor_count << ")\n\n";
        cout << "3. Return to Main Menu\n";
        cout << "---------------------------------\n";
        cout << "Enter your choice (1-3): ";

        // Input validation
        if (!(cin >> choice)) {
            cout << "\n*** Invalid input. Please enter a number. ***\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1; // Trigger default case
        }

        switch (choice) {
        case 1:
            buyBed();
            break;
        case 2:
            hireDoctor();
            break;
        case 3:
            cout << "\nReturning to main menu...\n";
            break;
        default:
            if (choice != -1) {
                cout << "\n*** Invalid choice. Please select from 1-3. ***\n";
            }
            break;
        }

        // Pause to let the user read the result of their action
        if (choice == 1 || choice == 2) {
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}

void Hospital::buyBed() {
    double cost = getNextBedCost();

    if (hospital_balance >= cost) {
        hospital_balance -= cost;
        bed_capacity++;
        cout << "\n*** Purchase Successful! ***\n";
        cout << "You bought a new bed. Total beds: " << bed_capacity << "\n";
        cout << "Remaining balance: $" << hospital_balance << "\n";
    }
    else {
        cout << "\n*** Insufficient Funds! ***\n";
        cout << "You need $" << cost << " to buy a new bed.\n";
    }
}

void Hospital::hireDoctor() {
    double cost = getNextDoctorCost();

    if (hospital_balance >= cost) {
        hospital_balance -= cost;
        doctor_count++;
        cout << "\n*** Purchase Successful! ***\n";
        cout << "You hired a new doctor. Total doctors: " << doctor_count << "\n";
        cout << "Remaining balance: $" << hospital_balance << "\n";
    }
    else {
        cout << "\n*** Insufficient Funds! ***\n";
        cout << "You need $" << cost << " to hire a new doctor.\n";
    }
}

// --- Phase 3: Polish ---

void Hospital::showFloorPlan() const {
    // Clear the screen to make the floor plan look clean
    clearScreen();

    cout << "\n=========================================\n";
    cout << "==       HOSPITAL FLOOR PLAN           ==\n";
    cout << "=========================================\n\n";

    // --- Print Doctors ---
    cout << "Doctors on Staff: (" << doctor_count << ")\n";
    for (int i = 0; i < doctor_count; ++i) {
        cout << "  __o__  " << "   "; // Print one doctor
    }
    cout << "\n"; // New line after all doctors in that row
    for (int i = 0; i < doctor_count; ++i) {
        cout << " /  |  \\ " << "   ";
    }
    cout << "\n";
    for (int i = 0; i < doctor_count; ++i) {
        cout << "   / \\   " << "   ";
    }
    cout << "\n";
    for (int i = 0; i < doctor_count; ++i) {
        cout << " [Doctor]" << "   ";
    }
    cout << "\n\n-----------------------------------------\n";

    // --- Print Beds ---
    cout << "Emergency Room Beds: (" << er_queue.size() << " / " << bed_capacity << ")\n";

    // 1. Print all the occupied beds
    int occupied = er_queue.size();
    for (int i = 0; i < occupied; ++i) {
        cout << " [Occupied] ";
        // Optional: add a new line every 5 beds to keep it clean
        if ((i + 1) % 5 == 0) {
            cout << "\n";
        }
    }

    // 2. Print all the empty beds
    int empty = bed_capacity - occupied;
    for (int i = 0; i < empty; ++i) {
        cout << " [Empty]    ";
        // Optional: add a new line
        if ((occupied + i + 1) % 5 == 0) {
            cout << "\n";
        }
    }

    cout << "\n\n=========================================\n";
}