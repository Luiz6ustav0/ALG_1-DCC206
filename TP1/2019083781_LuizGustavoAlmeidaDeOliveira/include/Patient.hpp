#ifndef PATIENT_H
#define PATIENT_H
#include <Clinic.hpp>
#include <unordered_map>
#include <vector>

class Patient {
public:
    Patient(int _id, int _age, int _posX, int _posY, std::unordered_map<int, Clinic> &allClinics);

    int getId() const;
    int getAge() const;
    bool isMatched() const;
    bool proposedToAllClinics() const;
    std::pair<int, int> getPosition() const;
    int getRankById(int id) const;

private:
    int id, age, nextIndexToClinicNotProposed = 1; // ID das clinicas precisa ser inciado em 1 nessa implementacao
    bool matched = false, proposedToAll = false;
    std::pair<int, int> positionXY;
    std::vector<int> rankListIndexedById;
    std::vector<bool> proposedToClinic;

    /** 
        * Funcao usada para ordenar as clinicas com base na distancia
        @returns vector<int> vec, onde vec[i] eh o rank da clinica com ID=i
     */
    std::vector<int> sortClinicsByDistance(std::unordered_map<int, Clinic> &clinics);

    static bool comparatorTwoClinicsByDistanceId(std::pair<int, float> i, std::pair<int, float> j);

    std::vector<int> createRankVecFromSortedByDistVec(std::vector<std::pair<int,float>> sortedByDistVec);

    float calculateDistanceToClinic(Clinic c) const;
};

#endif