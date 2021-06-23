#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <Clinic.hpp>
#include <Patient.hpp>
#include <UtilsService.hpp>

std::unordered_map<int, Clinic<Patient>> clinicsData = std::unordered_map<int, Clinic<Patient>>({{1, Clinic<Patient>(1, 4, 5, 2)}, {2, Clinic<Patient>(2, 4, 0, 1)}, {3, Clinic<Patient>(3, 4, 0, 5)}, {4, Clinic<Patient>(4, 4, 5, 0)}});

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

/* *****************************
    TESTS REGARDING THE CLINIC CLASS
*/

TEST_CASE("Should order clinics by distance") {
    // given
    int id = 0, age = 12, posX = 0, posY = 0;

    // when
    Patient p(id, age, posX, posY, clinicsData);

    // then
    // expected rank by id is {2, 3, 4, 1}, considering distance and lower id
    CHECK_EQ(p.getRankById(2), 1);
    CHECK_EQ(p.getRankById(3), 2);
    CHECK_EQ(p.getRankById(4), 3);
    CHECK_EQ(p.getRankById(1), 4);
}

TEST_CASE("Basic instantiation contract for Clinic") {
    // given when
    int id = 1, capacity = 4, posX = 3, posY = 4;
    Clinic<Patient> c(id, capacity, posX, posY);

    // then
    CHECK_EQ(c.getId(), id);
    CHECK_EQ(c.getCapacity(), capacity);
    CHECK_EQ(c.getPosition().first, posX);
    CHECK_EQ(c.getPosition().second, posY);
}

TEST_CASE("Should insert patient") {
    // given
    int id = 1, capacity = 4, posX = 3, posY = 4;
    int idPatient = 13, age = 19, posXPatient = 13, posYPatient = 15;
    Clinic<Patient> c(id, capacity, posX, posY);

    // when
    c.insertPatient({idPatient, age, posXPatient, posYPatient, clinicsData});

    // then
    CHECK_EQ(c.getRegisteredPatients()[0].getId(), idPatient);
}

TEST_CASE("Should order inserted patients by priority to allow constant lookup") {
    // given
    int id = 1, capacity = 4, posX = 3, posY = 4;
    int idPatient = 13, age = 19, posXPatient = 13, posYPatient = 15;
    int idPatient2 = 11;
    int idPatient3 = 20, age3 = 70;
    Clinic<Patient> c(id, capacity, posX, posY);

    // when inserting should always sort by priority asc
    c.insertPatient({idPatient3, age3, posXPatient, posYPatient, clinicsData});
    c.insertPatient({idPatient, age, posXPatient, posYPatient, clinicsData});
    c.insertPatient({idPatient2, age, posXPatient, posYPatient, clinicsData});

    // then
    CHECK_EQ(c.getRegisteredPatients()[0].getId(), idPatient); // lowest priority
    CHECK_EQ(c.getRegisteredPatients()[1].getId(), idPatient2); // medium priority becaue of lower id
    CHECK_EQ(c.getRegisteredPatients()[2].getId(), idPatient3); // highest priority because of age
}

/* *****************************
TESTS REGARDING THE UTIL CLASS
*/

TEST_CASE("Should tell which patient has higher priority by age") {
    // given
    int idPatient = 13, age = 19, posXPatient = 13, posYPatient = 15;
    int idPatient2 = 23, age2 = 39;
    UtilService utilsService;

    // when
    Patient p(idPatient, age, posXPatient, posYPatient, clinicsData);
    Patient v(idPatient2, age2, posXPatient, posYPatient, clinicsData);

    // then
    CHECK_EQ(utilsService.doesTheFirstHaveHigherPriority(p, v), false);
}

TEST_CASE("Should tell which patient has higher priority by id if age is equal") {
    // given
    int idPatient = 13, age = 39, posXPatient = 13, posYPatient = 15;
    int idPatient2 = 23;
    UtilService utilsService;

    // when
    Patient p(idPatient, age, posXPatient, posYPatient, clinicsData);
    Patient v(idPatient2, age, posXPatient, posYPatient, clinicsData);

    // then
    CHECK_EQ(utilsService.doesTheFirstHaveHigherPriority(p, v), true);
}