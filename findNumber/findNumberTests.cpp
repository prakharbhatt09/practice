#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "findNumber.hpp"

TEST_CASE("Checking number at first index"){
    const int array[] = {1,2,3,4,5};
    int target = 1;

    bool output = (array,5,1);

    CHECK(output == true);

}

TEST_CASE("Checking number at second index"){
    const int array[] = {1,2,3,4,5};
    int target = 2;

    bool output = (array,5,2);

    CHECK(output == true);

}

TEST_CASE("Checking number at third index"){
    const int array[] = {1,2,3,4,5};
    int target = 3;

    bool output = (array,5,3);

    CHECK(output == true);

}

TEST_CASE("Checking number at fourth index"){
    const int array[] = {1,2,3,4,5};
    int target = 4;

    bool output = (array,5,4);

    CHECK(output == true);

}

TEST_CASE("Checking number at fifth index"){
    const int array[] = {1,2,3,4,5};
    int target = 5;

    bool output = (array,5,5);

    CHECK(output == true);

}

TEST_CASE("Checking number not present in array"){
    const int array[] = {1,2,3,4,5};
    int target = 10;

    bool output = (array,5,10);

    CHECK(output == false);

}