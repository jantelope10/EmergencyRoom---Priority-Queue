#pragma once

#include <string>
#include <iostream>
using namespace std;

// The Patient class holds all information for a single patient.
class Patient
{
private:
	// Member variables for the patient's details.
	string name;
	int age;
	string illness;
	int severity; // This will be used for the priority queue. Higher is more urgent.

public:

	// --- Constructor ---
	// Initializes a new Patient object with all required details.
	Patient(string name, int age, string illness, int severity);

	// --- Getters (Read-Only) ---
	string getName() const;
	int getAge() const;
	string getIllness() const;
	int getSeverity() const;

	// --- Setters (Write) ---
	void setName(string newName);
	void setAge(int newAge);
	void setIllness(string newIllness);
	void setSeverity(int newSeverity);

	// --- Friend Functions ---
	// Overloads the stream insertion operator (<<) for easy printing.
	// This allows us to write: cout << some_patient;
	// It is a 'friend' so it can access the private members of Patient.
	friend ostream& operator<<(ostream& os, const Patient& p);
};

// --- Comparison Struct for Priority Queue ---
// This struct tells the priority_queue HOW to order Patient objects.
struct ComparePatient
{
	bool operator()(const Patient& p1, const Patient& p2) const
	{
		// This makes the priority queue a "max-heap" based on severity.
		// It treats patients with higher severity as "greater" than
		// patients with lower severity.
		return p1.getSeverity() < p2.getSeverity();
	}
};