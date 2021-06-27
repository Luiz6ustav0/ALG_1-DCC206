#include <UtilsService.hpp>
#include <queue>

bool UtilService::doesTheFirstHaveHigherPriority(const Patient &p, const Patient &v) {
    if (p.getAge() > v.getAge()) return true;
    if (p.getAge() == v.getAge() && p.getId() < v.getId()) return true;
    return false;
}

bool UtilService::clinicHasSomeoneWithLowerPriorityThan(const Patient &p, const Clinic &c) {
    Patient clinicsLowest = c.getPatientWithLowestPriority();
    bool result = doesTheFirstHaveHigherPriority(p, clinicsLowest);
    return result;
}

void
UtilService::galeShapleyMatching(std::queue<Patient> &patientQueue, std::unordered_map<int, Clinic> &clinicsRefMap) {
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
                }
                else continue;
            }
        }
    }

}
