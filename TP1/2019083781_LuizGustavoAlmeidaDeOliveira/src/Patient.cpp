#include <Clinic.hpp>
#include <Patient.hpp>
#include <algorithm>
#include <cmath>

Patient::Patient(int _id, int _age, int posX, int posY, std::unordered_map<int, Clinic> &allClinics) {
    this->id = _id;
    this->age = _age;
    this->positionXY = {posX, posY};
    this->rankListIndexedById = sortClinicsByDistance(allClinics);
    this->proposedToClinic = std::vector<bool>(allClinics.size(), false);
}

int Patient::getId() const { return this->id; };
int Patient::getAge() const { return this->age; };
bool Patient::isMatched() const { return this->matched; }
bool Patient::proposedToAllClinics() const { return this->proposedToAll; }
std::pair<int, int> Patient::getPosition() const { return this->positionXY; };
int Patient::getRankById(int id) const {
    if (id < rankListIndexedById.size())
        return this->rankListIndexedById[id];
    return -99; // TODO: Throw exception instead of this dumb code
};

std::vector<int> Patient::sortClinicsByDistance(std::unordered_map<int, Clinic> &IdToClinicMap) {
    std::vector<std::pair<int, float>> sortedByDistVec;

    // criando vetor apenas com as IDs e distancia para fazer a ordenacao
    for (auto &clinic : IdToClinicMap) {
        float distance = calculateDistanceToClinic(clinic.second);
        sortedByDistVec.push_back({clinic.first, distance});
    }

    std::sort(sortedByDistVec.begin(), sortedByDistVec.end(), Patient::comparatorTwoClinicsByDistanceId);

    std::vector<int> rankVec = createRankVecFromSortedByDistVec(sortedByDistVec);

    return rankVec;
}

float Patient::calculateDistanceToClinic(Clinic c) const {
    float distance = sqrt(
        pow(this->getPosition().first - c.getPosition().first, 2) + pow(this->getPosition().second - c.getPosition().second, 2));
    return distance;
}

bool Patient::comparatorTwoClinicsByDistanceId(std::pair<int, float> i, std::pair<int, float> j) {
    if (i.second < j.second || (i.second == j.second && i.first < j.first))
        return true;
    // if (i.second > j.second || (i.second == j.second && j.first < i.first))
    return false;
}

std::vector<int> Patient::createRankVecFromSortedByDistVec(std::vector<std::pair<int, float>> sortedVec) {
    std::vector<int> rankIndexedByIdVec(sortedVec.size() + 1);
    for (int i = 1; i < sortedVec.size() + 1; ++i) {
        rankIndexedByIdVec[sortedVec[i - 1].first] = i;
    }
    return rankIndexedByIdVec;
}