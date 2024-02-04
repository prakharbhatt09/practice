#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "apiClass.hpp"

TEST_CASE("Decode a message with one antenna handle")
{
  RadioMessage message1;
  std::vector<uint8_t> hexValues{0x01, 0x02, 0x04, 0x01, 0x01, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00};
 
  message1.decode(hexValues);
 
    CHECK(message1.Cookie == 0x01);
    CHECK(message1.ReceiverHandle == 0x01);
    CHECK(message1.NrOfAntennaHandles == 0x01);
}

/*
TEST_CASE("Decode a message with two antenna handle")
{
  RadioMessage message1;
  std::vector<uint8_t> hexValues{0x02, 0x02, 0x04, 0x03, 0x02, 0x45, 0x00, 0x45, 0x00, 0x00, 0x00};
  
  message1.decode(hexValues);
 
    CHECK(message1.Cookie == 0x02);
    CHECK(message1.ReceiverHandle == 0x03);
    CHECK(message1.NrOfAntennaHandles == 0x01);

}*/