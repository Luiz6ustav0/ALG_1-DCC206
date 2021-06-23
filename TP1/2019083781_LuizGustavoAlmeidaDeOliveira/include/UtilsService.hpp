#include <Clinic.hpp>
#include <Patient.hpp>


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
    static bool doesTheFirstHaveHigherPriority(Patient p, Patient v);
};