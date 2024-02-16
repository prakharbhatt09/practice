#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "CreateReceiver_repl.hpp"

using namespace std;

TEST_CASE("encode a message")
{
    CreateReceiver_repl message1(0x01,0x01,0x01,0x01);

        auto encoded_msg = message1.encode();
        CHECK(encoded_msg.at(0) == 0x01);
        CHECK(encoded_msg.at(1) == 0x02);
        CHECK(encoded_msg.at(2) == 0x03);
        CHECK(encoded_msg.at(3) == 0x01);
        CHECK(encoded_msg.at(4) == 0x01);
        CHECK(encoded_msg.at(5) == 0x00);
        CHECK(encoded_msg.at(6) == 0x00);
        CHECK(encoded_msg.at(7) == 0x00);
        CHECK(encoded_msg.at(8) == 0x01);

}

TEST_CASE("decode a message")
{
  CreateReceiver_repl message2;
  vector<uint8_t> toDecode{0x01,0x02,0x03,0x01,0x01,0x00,0x00,0x00,0x01};

  message2.decode(toDecode);

    CHECK(message2.getCookie() == 0x01);
    CHECK(message2.getReplyStatus() == 0x01);
    CHECK(message2.getReceiverHandle() == 0x01);
    CHECK(message2.getRfa() == 0x01);
    
}