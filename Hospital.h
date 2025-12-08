#pragma once

#include <iostream>
#include <string>
#include <queue>    // For priority_queue
#include <vector>   // For vector
#include <random>   // For mt19937 (modern random number generator)
#include <utility>  // For pair
#include <cstdlib>

#include "Patient.h"

class Hospital
{
public:
    // --- Constructor ---
    // Initializes the hospital, sets up the random number generator,
    // and calls initializeData() to fill our data banks.
    Hospital();

    // --- Phase 1: Core ER Functions ---

    // Displays the main menu and current hospital status.
    void displayMenu();

    // Auto-generates a patient from the data banks and adds them to the queue.
    void admitRandomPatient();

    // Prompts the user for all patient details and adds them to the queue.
    void addPatientManually();

    // Treats the highest-priority patient (top() and pop()).
    void treatNextPatient();

    // Views the highest-priority patient (top() only).
    void viewNextPatient();

    // Prints all patients in the queue without removing them.
    void viewAllPatients();

    // --- Phase 2: Simulation Functions ---
   
    // Displays the upgrade menu
    void showUpgradeMenu();

    // Buys a new bed, increasing bed_capacity.
    void buyBed();

    // Hires a new doctor, increasing doctor_count
    void hireDoctor();

    // --- Phase 3: Polish ---
    void showFloorPlan() const;

private:
    // --- Core Data Structures ---

    /*
        PROJECT REQUIREMENT:
        This priority_queue is the core of our project. It is the perfect
        container for an ER, where patients are treated by SEVERITY, not
        first-come, first-served.

        A simple queue would be incorrect, as the sickest patient
        would be stuck behind a patient with a common cold. This priority_queue,
        combined with our ComparePatient struct, ensures that the .top()
        element is always the patient with the highest severity,
        which is exactly how an ER should function.
    */
    priority_queue<Patient, vector<Patient>, ComparePatient> er_queue;

    // --- Phase 2: Sim Variables ---
    double hospital_balance;
    int doctor_count;
    int bed_capacity;

    // Data banks for auto-generating patients
    vector<pair<string, int>> illness_bank;
    vector<string> random_names;

    // --- Random Number Generation ---
    // This is our modern random number generator engine.
    mt19937 rng;

    // --- Private Helper Functions ---

    // Fills the illness_bank and random_names vectors with data.
    // Called by the constructor.
    void initializeData();

    // --- Phase 2: Private Helpers ---
    double getNextBedCost() const;
    double getNextDoctorCost() const;
};

// --- Inline Helper Function ---
// We mark this function 'inline' to tell the compiler
// it's okay that this is in a header file. It prevents
// the LNK2005 "multiply defined" linker error.
inline void clearScreen() {
    // Check if the system is Windows
#if defined(_WIN32)
    system("cls");
    // Otherwise, assume it's a Unix-like system (macOS, Linux)
#else
    system("clear");
#endif
}