#include <UtilsService.hpp>

bool UtilService::doesTheFirstHaveHigherPriority(Patient p, Patient v) {
    if (p.getAge() > v.getAge()) return true;
    if (p.getAge() == v.getAge() && p.getId() < v.getId()) return true;
    return false;
}

bool UtilService::clinicHasSomeoneWithLowerPriorityThan(const Patient p, const Clinic c) {
    Patient clinicsLowest = c.getPatientWithLowestPriority();
    bool result = doesTheFirstHaveHigherPriority(p, clinicsLowest);
    return result;
}