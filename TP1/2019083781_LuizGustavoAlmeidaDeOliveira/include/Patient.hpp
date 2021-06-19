#ifndef PATIENT_H
#define PATIENT_H
#include <Clinic.hpp>
#include <vector>
#include <unordered_map>

class Patient {
  public:

    Patient(int _id, int _age, int _posX, int _posY, std::unordered_map<int, Clinic> &allClinics);
    
    int getId() const;
    int getAge() const;
    bool isMatched() const;
    bool proposedToAllClinics() const;
    std::pair<int,int> getPosition() const;
    std::vector<int> rankById() const;

  private:
    int id, age, nextIndexToClinicNotProposed=1; // ID das clinicas precisa ser inciado em 1 nessa implementacao
    bool matched=false, proposedToAll=false;
    std::pair<int,int> positionXY;
    std::vector<int> preferenceListClinicsById;
    std::vector<bool> proposedToClinic;

    std::vector<int> sortClinicsByDistance(std::unordered_map<int, Clinic> &clinics);
};

#endif