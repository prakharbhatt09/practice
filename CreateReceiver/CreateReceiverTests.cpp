#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "CreateReceiver.hpp"

using namespace std;

TEST_CASE("encode a message")
{
  CreateReceiver receiver1(0x01,0x01,0x02,0x01,0x02,0x0000);

    auto encoded_msg = receiver1.encode();
 
    CHECK(encoded_msg.at(0) == 0x01);
    CHECK(encoded_msg.at(1) == 0x02);
    CHECK(encoded_msg.at(2) == 0x03);
    CHECK(encoded_msg.at(3) == 0x12);
    CHECK(encoded_msg.at(4) == 0x12);
    CHECK(encoded_msg.at(5) == 0x00);
    CHECK(encoded_msg.at(6) == 0x00);

}

TEST_CASE("decode a message")
{
  CreateReceiver receiver2;
  vector<uint8_t> toDecode{0x01,0x02,0x03,0x10,0x10,0x00,0x00};

  receiver2.decode(toDecode);

    CHECK(receiver2.getCookie() == 1);
    CHECK(receiver2.getPHY_ID() == 1);
    CHECK(receiver2.getCTRL_ID() == 0);
    CHECK(receiver2.getBroadcastStandard() == 1);
    CHECK(receiver2.getReceiverMode() == 0);
    CHECK(receiver2.getRfa() == 0x00);
    
}