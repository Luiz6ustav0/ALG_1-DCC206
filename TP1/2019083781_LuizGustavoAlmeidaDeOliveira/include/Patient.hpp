#ifndef PATIENT_H
#define PATIENT_H
#include <Clinic.hpp>
#include <stack>
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
    int getNextClinicId();

private:
    int id, age;
    bool matched = false, proposedToAll = false;
    std::pair<int, int> positionXY;
    std::stack<int> rankStack;
    std::vector<bool> proposedToClinic;

    /** 
        * Funcao usada para ordenar as clinicas com base na distancia
        @param std::unordered_map<int,Clinic> clinic id para objeto Clinic
        @returns vector<int>, onde vec[i] eh o rank da clinica com ID = i
     */
    std::stack<int> sortClinicsByDistance(std::unordered_map<int, Clinic> &clinics);

    static bool comparatorTwoClinicsByDistanceId(std::pair<int, float> i, std::pair<int, float> j);

    std::stack<int> createRankStackFromSortedByDistVec(std::vector<std::pair<int, float>> sortedByDistVec);

    float calculateDistanceToClinic(Clinic c) const;
};

#endif