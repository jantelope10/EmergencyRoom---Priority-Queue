#pragma once

#include <string>
#include <queue>    // For priority_queue
#include <vector>   // For vector
#include <utility>  // For pair
#include "Patient.h"

class Hospital
{
public:
    // Constructor
    Hospital();

    // Emergency room functions
    void displayMenu();
    void admitRandomPatient();
    void addPatientManually();
    void treatNextPatient();
    void viewNextPatient();
    void viewAllPatients();

    // Hospital simulation functions
    void showUpgradeMenu();
    void buyBed();
    void hireDoctor();
    void showFloorPlan() const;

private:
    // Priority queue that organizes the order of Patients based on highest priority (severity)
    // Patient = type of object stored; vector<Patient> = container that stores objects; ComparePatient = comparison struct that determines priority (in Patient.h file))
    priority_queue<Patient, vector<Patient>, ComparePatient> er_queue;

    // Hospital simulation variables
    double hospital_balance;
    int doctor_count;
    int bed_capacity;

    // Data banks for auto-generating patients (admitRandomPatient() function)
    vector<pair<string, int>> illness_bank; // (illness, severity)
    vector<string> random_names; // (name)

    // Fills the illness_bank and random_names banks
    void initializeData();

    // Functions to calculate next bed/doctor cost
    double getNextBedCost() const;
    double getNextDoctorCost() const;
};