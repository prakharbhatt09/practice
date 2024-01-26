#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "addNum.hpp"

    TEST_CASE("Adding max two digit integers")
{
    // Arrange
    float num1 = 10;
	float num2 = 2;

    // Act
    float output = sum(10,2);

    // Assert
    CHECK(output == 12);
}	
	TEST_CASE("Adding max 4 digit integers")
{
    // Arrange
    float num1 = 1000;
	float num2 = 10;

    // Act
    float output = sum(1000,10);

    // Assert
    CHECK(output == 1010);
}	
	TEST_CASE("Adding two integers")
{
    // Arrange
    float num1 = -1;
	float num2 = 10;

    // Act
    float output = sum(-1,10);

    // Assert
    CHECK(output == 9);	
}	
	TEST_CASE("Adding two integers")
{
    // Arrange
    float num1 = -10;
	float num2 = 100;

    // Act
    float output = sum(-10,100);

    // Assert
    CHECK(output == 90);	
}
	TEST_CASE("Adding two integers")
{
    // Arrange
    float num1 = -10;
	float num2 = -100;

    // Act
    float output = sum(-10,-100);

    // Assert
    CHECK(output == -110);	
}
	TEST_CASE("Adding two integers")
{
    // Arrange
    float num1 = 1.10f;
	float num2 = -100;

    // Act
    float output = sum(0.10,-100);

    // Assert
    CHECK(output == 0);	
}

	TEST_CASE("Sum something")
{
    // Arrange
    float num1 = 1.10f;
	float num2 = -10.50f;

    // Act
    float output = sum(0.10,-100);

    // Assert
    CHECK(output == 0);	
}