#include <Clinic.hpp>
#include <exception>
#include <string>

Clinic::Clinic(int _id, int _capacity, int posX, int posY) {
    this->id = _id;
    this->capacity = _capacity;
    this->spotsLeft = _capacity;
    this->positionXY = {posX, posY};
}

int Clinic::getId() { return this->id; }

int Clinic::getCapacity() { return this->capacity; }

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
    int numOfRegisteredPatients = this->getRegisteredPatients().size();

    for (int i = 1; i < numOfRegisteredPatients; ++i) {
        Patient patientToInsert = this->registeredPatients[i];
        int pos = i;

        while (
            ( pos > 0 && patientToInsert.getAge() < this->registeredPatients[pos - 1].getAge() ) ||
            ( patientToInsert.getAge() == this->registeredPatients[pos - 1].getAge() &&
              patientToInsert.getId() > this->registeredPatients[pos - 1].getId())) { 
            this->registeredPatients[pos] = this->registeredPatients[pos - 1];
            pos -= 1;
        }
        this->registeredPatients[pos] = patientToInsert;
    }
}

Patient Clinic::getPatientWithLowestPriority() const {
    if (this->capacity > this->spotsLeft) {
        return this->registeredPatients[0];
    }
    throw std::string("No patients registered when asking for lowest priority");
}

Patient Clinic::substituteForNewPatientAndReturnOld(Patient newPatient) {
    if (this->spotsLeft == 0) {
        Patient pastPatient = this->getPatientWithLowestPriority();
        this->registeredPatients[0] = newPatient;
        this->sortRegisteredPatients();
        return pastPatient;
    }
    throw std::string("The Clinic isn't full! You should NOT REMOVE patients");
}