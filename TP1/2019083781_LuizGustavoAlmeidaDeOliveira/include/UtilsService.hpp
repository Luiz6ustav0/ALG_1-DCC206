#include <Clinic.hpp>
#include <Patient.hpp>
#include <queue>


/*
    This class helps avoiding circular dependency issues with the Clinic and Patient Class
*/
class UtilService {
public:
    /**
     * Compares two Patients first by age and then by id.
     * Older patients have higher priority and if both ages are the same lower ID has higher priority.
     @param Patient p
     @param Patient v
     @returns bool
     */
    static bool doesTheFirstHaveHigherPriority(const Patient& p, const Patient& v);
    static bool clinicHasSomeoneWithLowerPriorityThan(const Patient& p, const Clinic& c);
    static void galeShapleyMatching(std::queue<Patient>& patientQ, std::unordered_map<int, Clinic> &clinicsRefMap);
};