#ifndef CLINIC_H
#define CLINIC_H
#include <utility>
#include <vector>

class Patient; // forward declaration

class Clinic {
public:
    Clinic(int _id = -1, int _capacity = -1, int posX = -1, int posY = -1);
    
    int getId();
    int getCapacity();
    bool hasSpaceLeft();
    std::pair<int, int> getPosition();
    /**
     * Returns all registered patients ordered by priority ASC
    */
    std::vector<Patient> getRegisteredPatients();
    /**
        * Inserts Patient and sorts current registered Patients by priority
    */
    void insertPatient(Patient p);

private:
    int id, capacity, spotsLeft;
    std::pair<int, int> positionXY;
    std::vector<Patient> registeredPatients;
    /**
     * Insertion sort on registered patients.
     * Insertion sort was selected because since patients will be inserted one by one, 
     * the array will be sorted and insertion sort gives best timing for sorted or
     * quasi sorted arrays. 
     */
    void sortRegisteredPatients();
};

#include <Patient.hpp>
#endif