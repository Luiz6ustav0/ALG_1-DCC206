#ifndef CLINIC_H
#define CLINIC_H
#include <utility>
#include <vector>

class Patient; // forward declaration

class Clinic {
public:
    explicit Clinic(int _id = -1, int _capacity = -1, int posX = -1, int posY = -1);
    
    int getId() const;
    int getCapacity() const;
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
    Patient getPatientWithLowestPriority() const;
    Patient substituteForNewPatientAndReturnOld(Patient newPatient);
    
private:
    int id, capacity, spotsLeft;
    std::pair<int, int> positionXY;
    std::vector<Patient> registeredPatients;
    void sortRegisteredPatients();
};

#include <Patient.hpp>
#endif