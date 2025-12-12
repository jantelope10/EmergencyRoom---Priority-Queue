#include "Hospital.h"
#include "Patient.h"
#include "ClearScreen.h"
#include <ctime>

// Constructor, sets hospital simulation variables
Hospital::Hospital()
{
    hospital_balance = 10.0;
    doctor_count = 1;
    bed_capacity = 3;

    initializeData();
}

// Populates illness and random names banks
void Hospital::initializeData()
{
    // Makes illness and severity into a pair to add to illness_bank vector
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

// Initial function that displays main menu
void Hospital::displayMenu()
{
    cout << "\n=========================================\n";
    cout << "== EMERGENCY ROOM SIMULATOR - MainMenu ==\n";
    cout << "=========================================\n";
    cout << "|  Current Status:\n";
    cout << "|   - Balance:   $" << hospital_balance << "\n";
    cout << "|   - Doctors:   " << doctor_count << "\n";
    cout << "|   - Beds:      " << er_queue.size() << " / " << bed_capacity << "\n";
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

// Adds random patient to er_queue using data banks
void Hospital::admitRandomPatient()
{
    // Checks if a bed is available for the patient
    if (er_queue.size() >= bed_capacity) 
    {
        cout << "\nThe ER is at full capacity! Cannot admit new patient.\n";
        return;
    }

    cout << "\n--- Automatic Patient Addition ---\n";

    // Checks if data banks have names to be selected at random
    if (illness_bank.empty() || random_names.empty()) 
    {
        cout << "\nERROR: Data banks are empty. Cannot admit random patient.\n";
        return;
    }
    
    // Sets seed to randomly select name, illness, severity, and age
    srand(time(0));

    int nameIndex = rand() % random_names.size();
    int illnessIndex = rand() % illness_bank.size();
    int randomAge = rand() % 120 + 1;

    string randomName = random_names[nameIndex];
    string randomIllness = illness_bank[illnessIndex].first;
    int randomSeverity = illness_bank[illnessIndex].second;

    // Eliminates the selected name from the random_names bank to prevent duplication
    random_names.erase(random_names.begin() + nameIndex);

    // Create and add the new patient
    Patient newPatient(randomName, randomAge, randomIllness, randomSeverity);
    er_queue.push(newPatient);

    cout << "\nNew Patient Admitted!\n";
    cout << newPatient << endl;
}

// Adds patient based on user input
void Hospital::addPatientManually()
{
    // Checks if a bed is available for the patient
    if (er_queue.size() >= bed_capacity) 
    {
        cout << "\nThe ER is at full capacity! Cannot admit new patient.\n";
        return;
    }

    cout << "\n--- Manual Patient Addition ---\n";

    string name, illness;
    int age, severity;

    // Receive patient name
    while (cin.get() != '\n') {}
    cout << "Enter patient name: ";
    getline(cin, name);

    // Receive patient age, loops until valid age is inputted
    while (true) 
    {
        cout << "Enter patient age: ";
        if (cin >> age && age > 0 && age <= 120) 
        {
            break;
        }
        else 
        {
            cout << "Invalid age. Please enter a number between 1 and 120.\n";
            cin.clear();
            while (cin.get() != '\n') {}
        }
    }

    // Receive patient illness
    while (cin.get() != '\n') {}
    cout << "Enter patient illness: ";
    getline(cin, illness);

    // Receive patient severity, loops until valid severity is inputted
    while (true) 
    {
        cout << "Enter severity (1-10): ";
        if (cin >> severity && severity >= 1 && severity <= 10) 
        {
            break;
        }
        else 
        {
            cout << "Invalid severity. Please enter a number between 1 and 10.\n";
            cin.clear();
            while (cin.get() != '\n') {}
        }
    }

    // Create and add the new patient
    Patient newPatient(name, age, illness, severity);
    er_queue.push(newPatient);

    cout << "\nManual Patient Admitted!\n";
    cout << newPatient << endl;
}

// Treats next patient with the highest priority (severity)
void Hospital::treatNextPatient()
{
    // Checks if the priority queue is empty
    if (er_queue.empty()) 
    {
        cout << "\nThere are no patients to treat.\n";
        return;
    }

    cout << "\n--- Doctors are Treating Patients... ---\n";

    int patientsTreated = 0;
    double totalPayout = 0.0;

    // Loop for however many doctors are available
    for (int i = 0; i < doctor_count; i++) 
    {
        // Check if there are patients in queue
        if (er_queue.empty()) 
        {
            cout << "All available patients have been treated.\n";
            break;
        }

        // Get a copy of the top patient (allows for ostream operator to work, since the element is getting deleted)
        Patient currentPatient = er_queue.top();

        // Remove them from the queue
        er_queue.pop();

        // Add the treated patient name back to the random name bank
        random_names.push_back(currentPatient.getName());

        // Calculate the payout ($100 per severity point)
        double patientPayout = currentPatient.getSeverity() * 100.0;
        totalPayout += patientPayout;

        // Print this specific patient's details
        cout << "\nDoctor " << (i + 1) << " treated:\n" << currentPatient << "\n";
        cout << "  - Payout: $" << patientPayout << "\n";

        patientsTreated++;
    }

    // Add the total payout to the hospital balance
    hospital_balance += totalPayout;

    // Print a summary of the treatment round
    cout << "\n--- Treatment Round Summary ---\n";
    cout << "Patients Treated: " << patientsTreated << "\n";
    cout << "Total Payout Earned: $" << totalPayout << "\n";
    cout << "New Hospital Balance: $" << hospital_balance << "\n";
}

// Views the next/top patient based on priority (severity)
void Hospital::viewNextPatient()
{
    // Check if there are patients in the queue
    if (er_queue.empty()) 
    {
        cout << "\nThere are no patients in the queue.\n";
        return;
    }

    // Get top patient as const to reference the actual element in the queue (nothing is being deleted)
    const Patient& nextPatient = er_queue.top();

    cout << "\n--- Next Patient in Queue ---\n";
    cout << nextPatient << endl;
}

// View all patients in queue in order based on priority (severity)
void Hospital::viewAllPatients()
{
    // Check if there are patients in the queue
    if (er_queue.empty()) 
    {
        cout << "\nThere are no patients in the queue.\n";
        return;
    }

    cout << "\n--- Full Patient List  ---\n";

    // Traversing priority queue requires making an exact copy to properly display each patient
    // Uses the copy constructor that's built into the <queue> package
    priority_queue<Patient, vector<Patient>, ComparePatient> temp_queue = er_queue;

    int count = 1;
    // Loop through the copy, printing and popping until it's empty
    while (!temp_queue.empty()) 
    {
        // Get a copy of the top patient (allows for ostream operator to work, since the element is getting deleted)
        Patient currentPatient = temp_queue.top();
        temp_queue.pop();

        cout << "\nPatient " << count << ":\n" << currentPatient << "\n";

        count++;
    }
}

// Sub-menu that displays the hospital simulation options
void Hospital::showUpgradeMenu()
{
    int choice = 0;
    // Loops until the user enters 3 to return to the main menu
    while (choice != 3) 
    {
        cout << "--- Hospital Upgrade Menu ---\n";
        cout << "Current Balance: $" << hospital_balance << "\n";
        cout << "---------------------------------\n";

        // Use helper functions to get the current costs (through a formula)
        double bedCost = getNextBedCost();
        double doctorCost = getNextDoctorCost();

        cout << "1. Buy Bed (Cost: $" << bedCost << ")\n";
        cout << "   (Current Beds: " << bed_capacity << ")\n\n";
        cout << "2. Hire Doctor (Cost: $" << doctorCost << ")\n";
        cout << "   (Current Doctors: " << doctor_count << ")\n\n";
        cout << "3. Return to Main Menu\n";
        cout << "---------------------------------\n";
        cout << "Enter your choice (1-3): ";

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
            buyBed();
            break;
        case 2:
            hireDoctor();
            break;
        case 3:
            cout << "\nReturning to main menu...\n";
            break;
        default:
            if (choice != -1) 
            {
                cout << "\nERROR: Invalid choice. Please select from 1-3.\n";
            }
            break;
        }

        // Continuation
        if (choice != 3 && choice != -1)
        {
            cout << "\nPress Enter to continue...";
            while (cin.get() != '\n') {}
            cin.get();

            clearScreen();
        }
    }
}

// Buys extra bed for hospital if the user has a sufficient balance
void Hospital::buyBed()
{
    double bedCost = getNextBedCost();

    // Checks if user can afford the bed
    if (hospital_balance >= bedCost)
    {
        hospital_balance -= bedCost;
        bed_capacity++;
        cout << "\n--- Bed Purchase Successful! ---\n";
        cout << "You bought a new bed! Total beds: " << bed_capacity << "\n";
        cout << "Remaining balance: $" << hospital_balance << "\n";
    }
    else 
    {
        cout << "\n--- Insufficient Funds! ---\n";
        cout << "You need $" << bedCost << " to buy a new bed.\n";
    }
}

// Buys extra doctor for hospital if the user has a sufficient balance
void Hospital::hireDoctor()
{
    double doctorCost = getNextDoctorCost();

    // Checks if user can afford the doctor
    if (hospital_balance >= doctorCost)
    {
        hospital_balance -= doctorCost;
        doctor_count++;
        cout << "\n--- Doctor Purchase Successful! --\n";
        cout << "You hired a new doctor! Total doctors: " << doctor_count << "\n";
        cout << "Remaining balance: $" << hospital_balance << "\n";
    }
    else 
    {
        cout << "\n--- Insufficient Funds! ---\n";
        cout << "You need $" << doctorCost << " to hire a new doctor.\n";
    }
}

// Displays unique design based on the number of beds and doctors in the hospital
void Hospital::showFloorPlan() const
{
    // Clear screen
    clearScreen();

    cout << "\n=========================================\n";
    cout << "==       HOSPITAL FLOOR PLAN           ==\n";
    cout << "=========================================\n\n";

    // Display doctors in hospital
    cout << "Emergency Room Doctors: (" << doctor_count << ")\n";
    // Prints head for each doctor
    for (int i = 0; i < doctor_count; i++) 
    {
        cout << "    o    " << "   ";
    }
    cout << "\n"; // New line after all doctors in that row
    // Prints body/arms for each doctor
    for (int i = 0; i < doctor_count; i++) 
    {
        cout << "   /|\\   " << "   ";
    }
    cout << "\n";
    // Prints legs for each doctor
    for (int i = 0; i < doctor_count; i++) 
    {
        cout << "   / \\   " << "   ";
    }
    cout << "\n";
    // Displays the title for each doctor
    for (int i = 0; i < doctor_count; i++) 
    {
        cout << " [Doctor]" << "   ";
    }
    cout << "\n\n-----------------------------------------\n";

    // Display beds in hospital
    cout << "\nEmergency Room Beds: (" << er_queue.size() << " / " << bed_capacity << ")\n";

    // Displays the title for each occupied bed
    int occupiedBeds = er_queue.size();
    for (int i = 0; i < occupiedBeds; i++) 
    {
        cout << " [Occupied] ";
        if ((i + 1) % 5 == 0) 
        {
            cout << "\n";
        }
    }

    // Displays the title for each empty bed
    int emptyBeds = bed_capacity - occupiedBeds;
    for (int i = 0; i < emptyBeds; i++) 
    {
        cout << " [Empty]    ";
        if ((occupiedBeds + i + 1) % 5 == 0) 
        {
            cout << "\n";
        }
    }

    cout << "\n\n-----------------------------------------\n";
}

// Private helper functions
double Hospital::getNextBedCost() const
{
    // Base cost of 100 plus 125 for every existing bed
    return 100.0 + (bed_capacity * 125.0);
}

double Hospital::getNextDoctorCost() const
{
    // Base cost of 1000, plus 500 for every existing doctor
    return 1000.0 + (doctor_count * 500.0);
}