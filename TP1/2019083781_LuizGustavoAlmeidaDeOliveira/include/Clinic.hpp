#ifndef CLINIC_H
#define CLINIC_H
#include <utility>

class Clinic {
  public:

    Clinic(int _id, int _capacity, int posX, int posY);

    int getId();
    int getCapacity();
    bool isFull();
    std::pair<int,int> getPosition();

  private:
    int id, capacity, spotsLeft;
    std::pair<int, int> positionXY;
};

#endif