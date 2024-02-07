#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "apiClass.hpp"

using namespace std;

TEST_CASE("encode a message with zero antenna handle")
{
  RadioMessage message1(0x01,0x01,0x00,0x00,0x00);

  auto encoded_msg = message1.encode();
 
    CHECK(encoded_msg.at(0) == 0x01);
    CHECK(encoded_msg.at(1) == 0x02);
    CHECK(encoded_msg.at(2) == 0x04);
    CHECK(encoded_msg.at(3) == 0x01);
    CHECK(encoded_msg.at(4) == 0x00);

}

TEST_CASE("encode a message with one antenna handle")
{
  RadioMessage message2(0x01,0x01,0x01,0x45,0x00);

  auto encoded_msg = message2.encode();
 
    CHECK(encoded_msg.at(0) == 0x01);
    CHECK(encoded_msg.at(1) == 0x02);
    CHECK(encoded_msg.at(2) == 0x04);
    CHECK(encoded_msg.at(3) == 0x01);
    CHECK(encoded_msg.at(4) == 0x01);
    CHECK(encoded_msg.at(5) == 0x45);
    CHECK(encoded_msg.at(6) == 0x00);
}
TEST_CASE("encode a message with two antenna handle")
{
  RadioMessage message3(0x01,0x01,0x02,0x45,0x00);

  auto encoded_msg = message3.encode();
 
    CHECK(encoded_msg.at(0) == 0x01);
    CHECK(encoded_msg.at(3) == 0x01);
    CHECK(encoded_msg.at(4) == 0x02);
    CHECK(encoded_msg.at(5) == 0x45);
    CHECK(encoded_msg.at(6) == 0x00);
    CHECK(encoded_msg.at(7) == 0x45);
    CHECK(encoded_msg.at(8) == 0x00);
}

TEST_CASE("Decode a message with one antenna handle")
{
  RadioMessage message4;
  std::vector<uint8_t> hexValues{0x01, 0x02, 0x04, 0x01, 0x01, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00};
 
  message4.decode(hexValues);
 
    CHECK(message4.getCookie() == 0x01);
    CHECK(message4.getReceiverHandle() == 0x01);
    CHECK(message4.getNrOfAntennaHandles() == 0x01);
    CHECK(message4.getAntennaHandle().at(0) == 0x45);
    CHECK(message4.getrfa1().at(0) == 0x00);
}

TEST_CASE("Decode a message with two antenna handle")
{
  RadioMessage message5;
  std::vector<uint8_t> hexValues{0x02, 0x02, 0x04, 0x03, 0x02, 0x45, 0x00, 0x45, 0x00, 0x00, 0x00};
  
  message5.decode(hexValues);
 
    CHECK(message5.getCookie() == 0x02);
    CHECK(message5.getReceiverHandle() == 0x03);
    CHECK(message5.getNrOfAntennaHandles() == 0x02);
    CHECK(message5.getAntennaHandle().at(0) == 0x45);
    CHECK(message5.getrfa1().at(0) == 0x00);
    CHECK(message5.getAntennaHandle().at(1) == 0x45);
    CHECK(message5.getrfa1().at(1) == 0x00);
}

TEST_CASE("Decode a message with zero antenna handle")
{
  RadioMessage message6;
  std::vector<uint8_t> hexValues{0x02, 0x02, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  
  message6.decode(hexValues);
 
    CHECK(message6.getCookie() == 0x02);
    CHECK(message6.getReceiverHandle() == 0x03);
    CHECK(message6.getNrOfAntennaHandles() == 0x00);

}