#include <Clinic.hpp>
#include <utility>

Clinic::Clinic(int _id, int _capacity, int posX, int posY) {
    this->id = _id;
    this->capacity = _capacity;
    this->spotsLeft = _capacity;
    this->positionXY = {posX, posY};
}

int Clinic::getId() { return this->id; }
int Clinic::getCapacity() { return this->capacity; }
bool Clinic::isFull() { return this->spotsLeft == 0; }
std::pair<int, int> Clinic::getPosition() { return this->positionXY; }