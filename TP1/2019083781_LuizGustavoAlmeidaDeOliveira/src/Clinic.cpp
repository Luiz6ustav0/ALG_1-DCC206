#include <Clinic.hpp>

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