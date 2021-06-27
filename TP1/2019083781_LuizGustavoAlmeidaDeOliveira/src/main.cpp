#include <UtilsService.hpp>
#include <iostream>
#include <queue>

int main() {

    int numberOfClinics = 0, numberOfPatients = 0;
    int capacity = 0, x = 0, y = 0, age = 0;

    std::unordered_map<int, Clinic> clinicsMap;
    std::queue<Patient> patientsQueue;

    std::cin >> numberOfClinics;
    for (int i = 0; i < numberOfClinics; ++i) {
        std::cin >> capacity >> x >> y;
        clinicsMap[i] = Clinic(i, capacity, x, y);
    }

    std::cin >> numberOfPatients;
    x = 0, y = 0;
    for (int i = 0; i < numberOfPatients; ++i) {
        std::cin >> age >> x >> y;
        patientsQueue.push(Patient(i, age, x, y, clinicsMap));
    }

    UtilService::galeShapleyMatching(patientsQueue, clinicsMap);

    for (int clinicId = 0; clinicId < clinicsMap.size(); ++clinicId) {
        Clinic currentClinic = clinicsMap[clinicId];
        std::cout << clinicId << std::endl;
        int patientsLen = currentClinic.getRegisteredPatients().size() - 1;
        for (int i = patientsLen; i >= 1; --i) {
            std::cout << currentClinic.getRegisteredPatients()[i].getId() << " ";
        } // Printing the last one separately just for formatting reasons(auto-correction)
        std::cout << currentClinic.getRegisteredPatients()[0].getId() << std::endl;
    }
}
