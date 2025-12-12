#include "Patient.h"

// Constructor, sets patient variables
Patient::Patient(string patientName, int patientAge, string patientIllness, int patientSeverity)
{
    name = patientName;
    age = patientAge;
    illness = patientIllness;
    severity = patientSeverity;
}

// Getters
string Patient::getName() const
{
    return name;
}

int Patient::getAge() const
{
    return age;
}

string Patient::getIllness() const
{
    return illness;
}

int Patient::getSeverity() const
{
    return severity;
}

// Setters
void Patient::setName(string newName)
{
    name = newName;
}

void Patient::setAge(int newAge)
{
    age = newAge;
}

void Patient::setIllness(string newIllness)
{
    illness = newIllness;
}

void Patient::setSeverity(int newSeverity)
{
    severity = newSeverity;
}

// Ostream operator for easy printing
ostream& operator<<(ostream& os, const Patient& p)
{
    // Assigns everything to ostream object to be returned
    os << "  - Name:     " << p.getName()
        << "\n  - Age:      " << p.getAge()
        << "\n  - Illness:  " << p.getIllness()
        << "\n  - Severity: " << p.getSeverity();
    
    return os;
}