#include "Patient.h"

// --- Constructor Implementation ---
// We use a member initializer list (the part after the colon) to initialize
// our private members.
Patient::Patient(string name, int age, string illness, int severity)
    : name(name), age(age), illness(illness), severity(severity)
{
    // The constructor body is empty because all initialization
    // was handled in the initializer list.
}

// --- Getter Implementations ---
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

// --- Setter Implementations ---
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

// --- Friend Function Implementation ---
// This is the implementation for our overloaded << operator.
// It takes an output stream (os) and a Patient object (p).
ostream& operator<<(ostream& os, const Patient& p)
{
    // We use the public getters to access the patient's private data.
    os << "  - Name:     " << p.getName()
        << "\n  - Age:      " << p.getAge()
        << "\n  - Illness:  " << p.getIllness()
        << "\n  - Severity: " << p.getSeverity();

    // We must return the stream to allow for chaining (e.g., cout << p1 << p2;)
    return os;
}