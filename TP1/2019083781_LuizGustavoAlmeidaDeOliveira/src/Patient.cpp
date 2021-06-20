#include <Clinic.hpp>
#include <Patient.hpp>
#include <algorithm>
#include <cmath>

Patient::Patient(int _id, int _age, int posX, int posY, std::unordered_map<int, Clinic> &allClinics) {
    this->id = _id;
    this->age = _age;
    this->positionXY = {posX, posY};
    this->preferenceListClinicsById = sortClinicsByDistance(allClinics);
    this->proposedToClinic = std::vector<bool>(allClinics.size(), false);
}

int Patient::getId() const { return this->id; };
int Patient::getAge() const { return this->age; };
bool Patient::isMatched() const { return this->matched; }
bool Patient::proposedToAllClinics() const { return this->proposedToAll; }
std::pair<int, int> Patient::getPosition() const { return this->positionXY; };
std::vector<int> Patient::rankById() const { return this->preferenceListClinicsById; };

std::vector<int> Patient::sortClinicsByDistance(std::unordered_map<int, Clinic> &clinics) {
    std::vector<std::pair<int, float>> sortedByDistVec;

    // criando vetor apenas com as IDs e distancia para fazer a ordenacao
    for (auto &clinic : clinics) {
        int clinicX = clinic.second.getPosition().first;
        int clinicY = clinic.second.getPosition().second;
        float distance = sqrt(
                            pow(this->getPosition().first-clinicX,2) - pow(this->getPosition().second-clinicY,2)
                        );
        sortedByDistVec.push_back({clinic.first, distance});
    }

    std::sort(sortedByDistVec.begin(), sortedByDistVec.end(), [](std::pair<int, float> i, std::pair<int, float> j) {
        if (i.second < j.second)
            return true;
        else if (i.second == j.second && i.first < j.first) // dist de i e j eh igual porem ID de i eh menor
            return true;
        else
            return false; // a distancia de j eh menor ou a distancia e igual e o id de j eh menor
    });

    std::vector<int> rankVec(sortedByDistVec.size() + 1);
    for (int i = 1; i < sortedByDistVec.size() + 1; ++i) {
        rankVec[sortedByDistVec[i - 1].first] = i;
    }

    return rankVec;
}