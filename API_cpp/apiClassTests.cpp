#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "apiClass.hpp"

using namespace std;

TEST_CASE("encode a message with one antenna handle")
{
  RadioMessage message;
  message.Cookie = 0x01;
  message.ReceiverHandle = 0x01;
  message.NrOfAntennaHandles = 0x01;

  auto encoded_msg = message.encode();
 
    CHECK(encoded_msg.at(0) == 0x01);
    CHECK(encoded_msg.at(3) == 0x01);
    CHECK(encoded_msg.at(4) == 0x01);
}

TEST_CASE("Decode a message with one antenna handle")
{
  RadioMessage message1;
  std::vector<uint8_t> hexValues{0x01, 0x02, 0x04, 0x01, 0x01, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00};
 
  message1.decode(hexValues);
 
    CHECK(message1.Cookie == 0x01);
    CHECK(message1.ReceiverHandle == 0x01);
    CHECK(message1.NrOfAntennaHandles == 0x01);
}

TEST_CASE("Decode a message with two antenna handle")
{
  RadioMessage message3;
  std::vector<uint8_t> hexValues{0x02, 0x02, 0x04, 0x03, 0x02, 0x45, 0x00, 0x45, 0x00, 0x00, 0x00};
  
  message3.decode(hexValues);
 
    CHECK(message3.Cookie == 0x02);
    CHECK(message3.ReceiverHandle == 0x03);
    CHECK(message3.NrOfAntennaHandles == 0x01);
}
