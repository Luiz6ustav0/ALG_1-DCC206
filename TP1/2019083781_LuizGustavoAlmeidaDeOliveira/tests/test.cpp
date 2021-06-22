#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Patient.hpp"
#include "doctest.h"

std::unordered_map<int, Clinic> clinicsData = std::unordered_map<int, Clinic>({
            {1, Clinic(1, 4, 5, 2)}, {2, Clinic(2, 4, 0, 1)}, {3, Clinic(3, 4, 0, 5)}, {4, Clinic(4, 4, 5, 0)} 
        }
);

TEST_CASE("Testing basic instantiation") {
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