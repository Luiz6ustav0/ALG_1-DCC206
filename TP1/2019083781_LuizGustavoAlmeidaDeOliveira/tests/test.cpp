#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <Clinic.hpp>
#include <Patient.hpp>
#include <UtilsService.hpp>

/* *******
    Data
*/
std::unordered_map<int, Clinic> clinicsData = std::unordered_map<int, Clinic>(
    {{0, Clinic(0, 4, 5, 2)}, {1, Clinic(1, 4, 0, 1)}, 
    {2, Clinic(2, 4, 0, 5)}, {3, Clinic(3, 4, 5, 0)}});


/* *****************************
TESTS REGARDING THE UTIL CLASS
*/

TEST_CASE("Util Should tell which patient has higher priority by age") {
    // given
    int idPatient = 13, age = 19, posXPatient = 13, posYPatient = 15;
    int idPatient2 = 23, age2 = 39;

    // when
    Patient p(idPatient, age, posXPatient, posYPatient, clinicsData);
    Patient v(idPatient2, age2, posXPatient, posYPatient, clinicsData);

    // then
    CHECK_EQ(UtilService::doesTheFirstHaveHigherPriority(p, v), false);
}

TEST_CASE("Util Should tell which patient has higher priority by id if age is equal") {
    // given
    int idPatient = 13, age = 39, posXPatient = 13, posYPatient = 15;
    int idPatient2 = 23;

    // when
    Patient p(idPatient, age, posXPatient, posYPatient, clinicsData);
    Patient v(idPatient2, age, posXPatient, posYPatient, clinicsData);

    // then
    CHECK_EQ(UtilService::doesTheFirstHaveHigherPriority(p, v), true);
}

TEST_CASE("Util should tell if clinic has patient with lower priority by age") {
    // given
    int idClinic = 1, clinicCapacity = 3, clinicPosX = 3, clinicPosY = 4;
    int idPatient = 3, age = 19, posXPatient = 13, posYPatient = 15;
    int idPatient2 = 11;
    int idPatient3 = 20, age3 = 70;
    Clinic c(idClinic, clinicCapacity, clinicPosX, clinicPosY);
    Patient pHigherPriority(50, 79, posXPatient, posYPatient, clinicsData);

    // when
    c.insertPatient({idPatient3, age3, posXPatient, posYPatient, clinicsData});
    c.insertPatient({idPatient, age, posXPatient, posYPatient, clinicsData});
    c.insertPatient({idPatient2, age, posXPatient, posYPatient, clinicsData});
    bool result = UtilService::clinicHasSomeoneWithLowerPriorityThan(pHigherPriority, c);
    
    // then
    bool expected = true; // patient with ID 
    CHECK_EQ(expected, result);
}

TEST_CASE("Util should tell if clinic has patient with lower priority by id") {
    // given
    int idClinic = 0, clinicCapacity = 3, clinicPosX = 3, clinicPosY = 4;
    int idPatient = 2, age = 19, posXPatient = 13, posYPatient = 15;
    int idPatient2 = 3;
    int idPatient3 = 4;
    Clinic c(idClinic, clinicCapacity, clinicPosX, clinicPosY);
    Patient pHigherPriority(3, age, posXPatient, posYPatient, clinicsData);

    // when
    c.insertPatient({idPatient3, age, posXPatient, posYPatient, clinicsData});
    c.insertPatient({idPatient, age, posXPatient, posYPatient, clinicsData});
    c.insertPatient({idPatient2, age, posXPatient, posYPatient, clinicsData});
    bool result = UtilService::clinicHasSomeoneWithLowerPriorityThan(pHigherPriority, c);
    
    // then
    bool expected = true; // patient with ID 
    CHECK_EQ(expected, result);
}


/* ********************************
    TESTS REGARDING THE PATIENT CLASS
*/

TEST_CASE("Basic instantiation contract for Patient") {
    // given
    int id = 0, age = 12, posX = 5, posY = 3;

    // when
    Patient p(id, age, posX, posY, clinicsData);

    // then
    CHECK_EQ(id, p.getId());
    CHECK_EQ(age, p.getAge());
    CHECK_EQ(posX, p.getPosition().first);
    CHECK_EQ(posY, p.getPosition().second);
}

TEST_CASE("Patient Should order clinics by distance") {
    // given
    int id = 0, age = 12, posX = 0, posY = 0;

    // when
    Patient p(id, age, posX, posY, clinicsData);

    // then
    // expected rank by id is {2, 3, 4, 1}, considering distance and lower id
    CHECK_EQ(p.getRankById(1), 0);
    CHECK_EQ(p.getRankById(2), 1);
    CHECK_EQ(p.getRankById(3), 2);
    CHECK_EQ(p.getRankById(0), 3);
}

/* *****************************
    TESTS REGARDING THE CLINIC CLASS
*/

TEST_CASE("Basic instantiation contract for Clinic") {
    // given when
    int id = 1, capacity = 4, posX = 3, posY = 4;
    Clinic c(id, capacity, posX, posY);

    // then
    CHECK_EQ(c.getId(), id);
    CHECK_EQ(c.getCapacity(), capacity);
    CHECK_EQ(c.getPosition().first, posX);
    CHECK_EQ(c.getPosition().second, posY);
}

TEST_CASE("Clinic Should insert patient") {
    // given
    int id = 1, capacity = 4, posX = 3, posY = 4;
    int idPatient = 13, age = 19, posXPatient = 13, posYPatient = 15;
    Clinic c(id, capacity, posX, posY);

    // when
    c.insertPatient({idPatient, age, posXPatient, posYPatient, clinicsData});

    // then
    CHECK_EQ(c.getRegisteredPatients()[0].getId(), idPatient);
}

TEST_CASE("Clinic Should order inserted patients by priority to allow constant lookup") {
    // given
    int idClinic = 1, clinicCapacity = 4, clinicPosX = 3, clinicPosY = 4;
    int idPatient = 13, age = 19, posXPatient = 13, posYPatient = 15;
    int idPatient2 = 11;
    int idPatient3 = 20, age3 = 70;
    Clinic c(idClinic, clinicCapacity, clinicPosX, clinicPosY);

    // when inserting should always sort by priority asc
    c.insertPatient({idPatient3, age3, posXPatient, posYPatient, clinicsData});
    c.insertPatient({idPatient, age, posXPatient, posYPatient, clinicsData});
    c.insertPatient({idPatient2, age, posXPatient, posYPatient, clinicsData});

    // then
    CHECK_EQ(c.getRegisteredPatients()[0].getId(), idPatient);  // lowest priority
    CHECK_EQ(c.getRegisteredPatients()[1].getId(), idPatient2); // medium priority because of lower id
    CHECK_EQ(c.getRegisteredPatients()[2].getId(), idPatient3); // highest priority because of age
}

TEST_CASE("Clinic Should return patient with lowest priority(index 0)") {
    // given
    int idClinic = 1, clinicCapacity = 4, clinicPosX = 3, clinicPosY = 4;
    int idPatient = 13, age = 19, posXPatient = 13, posYPatient = 15;
    int idPatient2 = 11;
    int idPatient3 = 20, age3 = 70;
    Clinic c(idClinic, clinicCapacity, clinicPosX, clinicPosY);

    // when inserting should always sort by priority asc
    c.insertPatient({idPatient3, age3, posXPatient, posYPatient, clinicsData});
    c.insertPatient({idPatient, age, posXPatient, posYPatient, clinicsData});
    c.insertPatient({idPatient2, age, posXPatient, posYPatient, clinicsData});

    // then
    CHECK_EQ(c.getPatientWithLowestPriority().getId(), idPatient);  // lowest priority
}

TEST_CASE("Clinic should tell correctly it has no space left") {
    // given
    int idClinic = 1, clinicCapacity = 3, clinicPosX = 3, clinicPosY = 4;
    int idPatient = 13, age = 19, posXPatient = 13, posYPatient = 15;
    int idPatient2 = 11, idPatient3 = 20;
    Clinic c(idClinic, clinicCapacity, clinicPosX, clinicPosY);

    // when
    c.insertPatient({idPatient, age, posXPatient, posYPatient, clinicsData});
    c.insertPatient({idPatient2, age, posXPatient, posYPatient, clinicsData});

    // then
    bool expected = true; // 1 spot left
    CHECK_EQ(c.hasSpaceLeft(), expected);
    c.insertPatient({idPatient3, age, posXPatient, posYPatient, clinicsData});
    expected = false; // total patients = 3 = full
    CHECK_EQ(c.hasSpaceLeft(), expected);
}

TEST_CASE("Clinic should substitute patients if it has lower priority by id") {
    // given
    int idClinic = 1, clinicCapacity = 3, clinicPosX = 3, clinicPosY = 4;
    int idPatient = 13, age = 19, posXPatient = 13, posYPatient = 15;
    int idPatient2 = 11, idPatient3 = 20, highestPriorityId = 3;
    Clinic c(idClinic, clinicCapacity, clinicPosX, clinicPosY);
    Patient patient4(highestPriorityId, age, posXPatient, posYPatient, clinicsData); // priority by id

    // when
    c.insertPatient({idPatient, age, posXPatient, posYPatient, clinicsData});
    c.insertPatient({idPatient2, age, posXPatient, posYPatient, clinicsData});
    c.insertPatient({idPatient3, age, posXPatient, posYPatient, clinicsData});
    bool hasSomeoneWithLowerPriority = UtilService::clinicHasSomeoneWithLowerPriorityThan(patient4, c);

    // then
    CHECK_EQ(true, hasSomeoneWithLowerPriority);
    Patient returnedPatient = c.substituteForNewPatientAndReturnOld(patient4);
    CHECK_EQ(idPatient3, returnedPatient.getId());
    CHECK_EQ(c.getRegisteredPatients()[clinicCapacity-1].getId(), highestPriorityId);
}