#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "catch2/catch.hpp"
#include "findNumber.hpp"

SCENARIO( "Number entered is 1" ) {
    GIVEN( "An array of size 5" ) {
        const int array[] = {1,2,3,4,5};
        
        THEN( "Search for number 1" ) {
            int target = 1;
            REQUIRE(findNumber(array,5,1 == true));
        }

        WHEN( "number 2 is searched" ) {
            int target = 2;

            THEN( "Search for 2" ) {
                REQUIRE(findNumber(array,5,2 == true));
            }
        }

        WHEN( "number 3 is searched" ) {
            int target = 3;

            THEN( "Search for 3" ) {
                REQUIRE(findNumber(array,5,3 == true));
            }
        }

        WHEN( "number 4 is searched" ) {
            int target = 4;

            THEN( "Search for 4" ) {
                REQUIRE(findNumber(array,5,4 == true));
            }
        }

        WHEN( "number 5 is searched" ) {
            int target = 5;

            THEN( "Search for 5" ) {
                REQUIRE(findNumber(array,5,5 == true));
            }
        }

        AND_WHEN( "any number from 5 to 10 is searched" ) {
            int target = 7;

            THEN( "Search for 7" ) {
                REQUIRE(findNumber(array,5,7 == false));
            }
        }
    }
}