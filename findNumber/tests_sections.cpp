#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "catch2/catch.hpp"
#include "findNumber.hpp"

using namespace std;

TEST_CASE("Checking number in an array","[array]"){

    REQUIRE(std::array == {1,2,3,4,5});

        SECTION("checking for 1"){
            int target = 1;
            REQUIRE(findNumber(array,5,1 == true));
        }
        SECTION("checking for 2"){
            int target = 2;
            REQUIRE(findNumber(array,5,1 == true));
        }
        SECTION("checking for 3"){
            int target = 3;
            REQUIRE(findNumber(array,5,1 == true));
        }
        SECTION("checking for 4"){
            int target = 4;
            REQUIRE(findNumber(array,5,1 == true));
        }
        SECTION("checking for 5"){
            int target = 5;
            REQUIRE(findNumber(array,5,1 == true));
        }
        SECTION("checking for 6"){
            int target = 6;
            REQUIRE(findNumber(array,5,1 == false));
        }
        SECTION("checking for any number except array elements"){
            int target = 10;
            REQUIRE(findNumber(array,5,10 == false));
        }

}