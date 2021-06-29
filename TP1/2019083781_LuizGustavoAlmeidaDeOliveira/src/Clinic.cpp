#include <Clinic.hpp>
#include <algorithm>
#include <iostream>

Clinic::Clinic(int _id, int _capacity, int posX, int posY) {
    this->id = _id;
    this->capacity = _capacity;
    this->spotsLeft = _capacity;
    this->positionXY = {posX, posY};
}

int Clinic::getId() const { return this->id; }

int Clinic::getCapacity() const { return this->capacity; }

bool Clinic::hasSpaceLeft() { return this->spotsLeft > 0; }

std::pair<int, int> Clinic::getPosition() { return this->positionXY; }

std::vector<Patient> Clinic::getRegisteredPatients() {
    return this->registeredPatients;
}

void Clinic::insertPatient(Patient p) {
    this->registeredPatients.push_back(p);
    this->spotsLeft--;
    this->sortRegisteredPatients();
}

void Clinic::sortRegisteredPatients() {
    std::sort(this->registeredPatients.begin(), this->registeredPatients.end(), [](Patient p, Patient v) {
        if (p.getAge() < v.getAge() || (p.getAge() == v.getAge() && p.getId() > v.getId()))
            return true;
        return false;
    });
}

Patient Clinic::getPatientWithLowestPriority() const {
    if (this->capacity > this->spotsLeft) {
        return this->registeredPatients[0];
    }
    throw "No patients registered when asking for lowest priority";
}

Patient Clinic::substituteForNewPatientAndReturnOld(Patient newPatient) {
    if (this->spotsLeft == 0) {
        Patient pastPatient = this->getPatientWithLowestPriority();
        this->registeredPatients[0] = newPatient;
        this->sortRegisteredPatients();
        return pastPatient;
    }
    throw "The Clinic isn't full! You should NOT REMOVE patients";
}