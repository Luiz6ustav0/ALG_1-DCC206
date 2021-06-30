#include <UtilsService.hpp>
#include <iostream>
#include <queue>

bool UtilService::doesTheFirstHaveHigherPriority(const Patient &p, const Patient &v) {
    if (p.getAge() > v.getAge())
        return true;
    if (p.getAge() == v.getAge() && p.getId() < v.getId())
        return true;
    return false;
}

bool UtilService::clinicHasSomeoneWithLowerPriorityThan(const Patient &p, const Clinic &c) {
    Patient clinicsLowest = c.getPatientWithLowestPriority();
    bool result = doesTheFirstHaveHigherPriority(p, clinicsLowest);
    return result;
}

void UtilService::galeShapleyMatching(std::queue<Patient> &patientQueue, std::unordered_map<int, Clinic> &clinicsRefMap) {
    while (!patientQueue.empty()) {
        Patient currentPatient = patientQueue.front();
        patientQueue.pop();
        if (!currentPatient.proposedToAllClinics()) {
            while (!currentPatient.proposedToAllClinics()) {
                int clinicIdFromPatient = currentPatient.getNextClinicId();
                Clinic &currentClinic = clinicsRefMap[clinicIdFromPatient];
                if (currentClinic.hasSpaceLeft()) {
                    currentClinic.insertPatient(currentPatient);
                    break;
                } else if (clinicHasSomeoneWithLowerPriorityThan(currentPatient, currentClinic)) {
                    Patient pRemovedFromClinic = currentClinic.substituteForNewPatientAndReturnOld(currentPatient);
                    patientQueue.push(pRemovedFromClinic);
                    break;
                } else
                    continue;
            }
        }
    }
}

void UtilService::printExpectedOutput(std::unordered_map<int, Clinic> &clinicsRefMapsMap) {
    int mapSize = clinicsRefMapsMap.size();
    for (int clinicId = 0; clinicId < mapSize; ++clinicId) {
        Clinic currentClinic = clinicsRefMapsMap[clinicId];
        int currentClinicPatientsSize = currentClinic.getRegisteredPatients().size();
        if (currentClinicPatientsSize == 0)
            continue;
        else {
            std::cout << clinicId << std::endl;
            for (int i = currentClinicPatientsSize - 1; i >= 1; --i) {
                std::cout << currentClinic.getRegisteredPatients()[i].getId() << " ";
            } // Printing the last one separately just for formatting reasons(auto-correction)
            std::cout << currentClinic.getRegisteredPatients()[0].getId() << std::endl;
        }
    }
}