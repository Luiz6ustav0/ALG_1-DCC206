#ifndef CLINIC_H
#define CLINIC_H
#include <utility>
#include <vector>

template <class T>
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
    std::vector<T> getRegisteredPatients();
    /**
        * Inserts Patient and sorts current registered Patients by priority
    */
    void insertPatient(T p);

private:
    int id, capacity, spotsLeft;
    std::pair<int, int> positionXY;
    std::vector<T> registeredPatients;
};

/*
    Implementation needs to be in the same file as the declaration when using templates
*/

template <class T>
Clinic<T>::Clinic(int _id, int _capacity, int posX, int posY) {
    this->id = _id;
    this->capacity = _capacity;
    this->spotsLeft = _capacity;
    this->positionXY = {posX, posY};
}

template <class T>
int Clinic<T>::getId() { return this->id; }
template <class T>
int Clinic<T>::getCapacity() { return this->capacity; }
template <class T>
bool Clinic<T>::hasSpaceLeft() { return this->spotsLeft > 0; }
template <class T>
std::pair<int, int> Clinic<T>::getPosition() { return this->positionXY; }

template <class T>
std::vector<T> Clinic<T>::getRegisteredPatients() {
    return this->registeredPatients;
}

template <class T>
void Clinic<T>::insertPatient(T p) {
    this->registeredPatients.push_back(p);
}

#endif