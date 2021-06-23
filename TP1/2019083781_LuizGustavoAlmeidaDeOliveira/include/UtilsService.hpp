#include <Clinic.hpp>
#include <Patient.hpp>


/*
    This class helps avoiding circular dependency issues with the Clinic and Patient Class
*/
class UtilService {
public:
    static bool doesTheFirstHaveHigherPriority(Patient p, Patient v);
};