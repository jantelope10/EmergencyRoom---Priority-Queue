#pragma once

#include <iostream>
#include <string>
using namespace std;

// The Patient class holds all information for a single patient
class Patient
{
private:
	// Member variables for patient details
	string name;
	int age;
	string illness;
	int severity; // This will be used for the priority queue (bigger number is higher priority)

public:

	// Constructor
	Patient(string name, int age, string illness, int severity);

	// Getters
	string getName() const;
	int getAge() const;
	string getIllness() const;
	int getSeverity() const;

	// Setters
	void setName(string newName);
	void setAge(int newAge);
	void setIllness(string newIllness);
	void setSeverity(int newSeverity);

	// Ostream operator for easy printing
	friend ostream& operator<<(ostream& os, const Patient& currentPatient);
};

// Comparison struct to tell the priority queue how to order Patient objects (as a max heap)
// Defines the rule that patient1 should go behind patient2 in the queue if its severity is less than that of patient2
struct ComparePatient
{
	bool operator()(const Patient& patient1, const Patient& patient2) const
	{
		// This makes the priority queue a max heap based on severity
		return patient1.getSeverity() < patient2.getSeverity();
	}
};