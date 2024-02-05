#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "apiClass.hpp"

TEST_CASE("Encode a message with one antenna handle")
{
  RadioMessage message2;
  message2.Cookie = 0x02;
  message2.ReceiverHandle = 0x01;
  message2.NrOfAntennaHandles = 0x01;
  //message2.AntennaHandle.push_back(0x45);
  //message2.rfa1.push_back(0x00);
  
  vector<uint8_t> encoded_msg = message2.encode();
 
    CHECK(encoded_msg.at(0) == 0x02);
    CHECK(encoded_msg.at(3) == 0x01);
    CHECK(encoded_msg.at(4) == 0x01);
    //CHECK(encoded_msg.at(5) == 0x45);
    //CHECK(encoded_msg.at(6) == 0x00);
}

/*
TEST_CASE("Decode a message with one antenna handle")
{
  RadioMessage message1;
  std::vector<uint8_t> hexValues{0x02, 0x02, 0x04, 0x01, 0x01, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00};
 
  message1.decode(hexValues);
 
    CHECK(message1.Cookie == 0x02);
    CHECK(message1.ReceiverHandle == 0x01);
    CHECK(message1.NrOfAntennaHandles == 0x01);
}
TEST_CASE("Decode a message with two antenna handle")
{
  RadioMessage message1;
  std::vector<uint8_t> hexValues{0x02, 0x02, 0x04, 0x03, 0x02, 0x45, 0x00, 0x45, 0x00, 0x00, 0x00};
  
  message1.decode(hexValues);
 
    CHECK(message1.Cookie == 0x02);
    CHECK(message1.ReceiverHandle == 0x03);
    CHECK(message1.NrOfAntennaHandles == 0x01);

}*/