#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "CheckPrime.hpp"

TEST_CASE("Checking single digit Prime number(1)")
{
    int num = 1;

    bool output = isPrime(1);

    CHECK(output == false);
}	
TEST_CASE("Checking single digit Prime number(2)")
{
    int num = 2;

    bool output = isPrime(2);

    CHECK(output == true);
}	

TEST_CASE("Checking single digit Prime number(3)")
{
    int num = 3;

    bool output = isPrime(3);

    CHECK(output == true);
}	

TEST_CASE("Checking multiple digit Prime number(17124)")
{
    int num = 17124;

    bool output = isPrime(17124);

    CHECK(output == true);
}	