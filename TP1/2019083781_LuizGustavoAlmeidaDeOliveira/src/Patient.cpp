#include <Clinic.hpp>
#include <Patient.hpp>
#include <algorithm>
#include <cmath>

Patient::Patient(int _id, int _age, int posX, int posY, std::unordered_map<int, Clinic> &allClinics) {
    this->id = _id;
    this->age = _age;
    this->positionXY = {posX, posY};
    this->rankStack = sortClinicsByDistance(allClinics);
    this->proposedToClinic = std::vector<bool>(allClinics.size(), false);
}

int Patient::getId() const { return this->id; };
int Patient::getAge() const { return this->age; };
bool Patient::isMatched() const { return this->matched; }
bool Patient::proposedToAllClinics() const { return this->proposedToAll; }
std::pair<int, int> Patient::getPosition() const { return this->positionXY; };
int Patient::getNextClinicId() {
    if (!this->matched && !this->proposedToAll) {
        int nextId = rankStack.top();
        this->rankStack.pop();
        if (this->rankStack.size() == 0) proposedToAll = true;
        return nextId;
    }
    throw "Already matched. NO need for next ID";
};

std::stack<int> Patient::sortClinicsByDistance(std::unordered_map<int, Clinic> &IdToClinicMap) {
    std::vector<std::pair<int, float>> sortedByDistVec;

    // criando vetor apenas com as IDs e distancia para fazer a ordenacao
    for (auto &clinic : IdToClinicMap) {
        float distance = calculateDistanceToClinic(clinic.second);
        sortedByDistVec.push_back({clinic.first, distance});
    }

    std::stable_sort(sortedByDistVec.begin(), sortedByDistVec.end(), Patient::comparatorTwoClinicsByDistanceId);

    std::stack<int> newRankStack = createRankStackFromSortedByDistVec(sortedByDistVec);

    return newRankStack;
}

float Patient::calculateDistanceToClinic(Clinic c) const {
    float distance = sqrt(
        pow(this->getPosition().first - c.getPosition().first, 2) + pow(this->getPosition().second - c.getPosition().second, 2));
    return distance;
}

bool Patient::comparatorTwoClinicsByDistanceId(std::pair<int, float> i, std::pair<int, float> j) {
    if (i.second < j.second || (i.second == j.second && i.first < j.first))
        return false;
    // if (i.second > j.second || (i.second == j.second && j.first < i.first))
    return true;
}

std::stack<int> Patient::createRankStackFromSortedByDistVec(std::vector<std::pair<int, float>> sortedVec) {
    std::stack<int> rankS;
    int vecSize = sortedVec.size();
    for (int i = 0; i < vecSize; ++i) {
        rankS.push(sortedVec[i].first); // pushing only the id since we can reference the clinics later through it
    }
    return rankS;
}