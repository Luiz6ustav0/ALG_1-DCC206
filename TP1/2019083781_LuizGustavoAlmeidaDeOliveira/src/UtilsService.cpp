#include <UtilsService.hpp>

bool UtilService::doesTheFirstHaveHigherPriority(Patient p, Patient v) {
    if (p.getAge() > v.getAge()) return true;
    if (p.getAge() == v.getAge() && p.getId() < v.getId()) return true;
    return false;
}