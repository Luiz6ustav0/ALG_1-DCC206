#ifndef CLINIC_H
#define CLINIC_H
#include <utility>
#include <vector>

template <class T>
class Clinic {
  public:

    Clinic(int _id=-1, int _capacity=-1, int posX=-1, int posY=-1);

    int getId();
    int getCapacity();
    bool hasSpaceLeft();
    std::pair<int,int> getPosition();
    std::vector<T> getRegisteredPatients();
    void insertPatient(T p);

    // TODO:
    // isThereAnyoneYoungerThan(int age)

  private:
    int id, capacity, spotsLeft;
    std::pair<int, int> positionXY;
    // TODO:
    /*
        I need to implement a vector where I'll insert the current patients, and everytime
        someone new gets inserted I'll call insertion sort because this will give me better
        timing in the following operations:
            - constant time to check if the clinic has someone younger y than the one who's asking
            - constant time to insert this new person on y's place(copy y and return while just making
                vector[0] equals to the new person)
        The downside is calling insertion sort everytime but we should be fine since our array
        will be sorted including one person at a time will be O(n)
    */
    std::vector<T> registeredPatients;
};

template <class T>
Clinic<T>::Clinic(int _id, int _capacity, int posX, int posY) {
    this->id = _id;
    this->capacity = _capacity;
    this->spotsLeft = _capacity;
    this->positionXY = {posX, posY};
}

template <class T> int Clinic<T>::getId() { return this->id; }
template <class T> int Clinic<T>::getCapacity() { return this->capacity; }
template <class T> bool Clinic<T>::hasSpaceLeft() { return this->spotsLeft > 0; }
template <class T> std::pair<int, int> Clinic<T>::getPosition() { return this->positionXY; }

template <class T> 
std::vector<T> Clinic<T>::getRegisteredPatients() {
    return this->registeredPatients;
}

template <class T> 
void Clinic<T>::insertPatient(T p) {
    this->registeredPatients.push_back(p);
}

#endif