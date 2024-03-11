#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "GetReceivers_repl.hpp"

using namespace std;

TEST_CASE("decoding for 0 receiver and 0 AntennaHandle")
{
   GetReceivers_repl message1;
   vector<uint8_t> toDecode{0x81,0x01,0x02,0x01,0x00,0,0,0,0}; 

   message1.decode(toDecode);

   REQUIRE(toDecode.size() == 9);
   CHECK(message1.getMessageType() == 1);
   CHECK(message1.getCookie() == 1);
   CHECK(message1.getReplyStatus() == 1);
   CHECK(message1.getNrOfReceivers() == 0);
   CHECK(message1.getReceiversVector().size() == 0);

}

TEST_CASE("decoding for 1 receiver and 0 AntennaHandle")
{
   GetReceivers_repl message2;
   vector<uint8_t> toDecode{0x81,0x01,0x02,0x01,0x01,//msgInfo
   0x01,0x11,0x11,1,0x00,0,0,0,0,
   0,0,0,0};

   message2.decode(toDecode);

   REQUIRE(toDecode.size() == 18);
   CHECK(message2.getMessageType() == 1);
   CHECK(message2.getCookie() == 1);
   CHECK(message2.getReplyStatus() == 1);
   CHECK(message2.getNrOfReceivers() == 1);
   CHECK(message2.getReceiversVector().size() == 1);
   CHECK(message2.getReceiversVector().at(0).getReceiverHandle() == 1);
   CHECK(message2.getReceiversVector().at(0).getPHY_ID() == 1);
   CHECK(message2.getReceiversVector().at(0).getCTRL_ID() == 1);
   CHECK(message2.getReceiversVector().at(0).getBroadcastStandard() == 1);
   CHECK(message2.getReceiversVector().at(0).getReceiverMode() == 1);
   CHECK(message2.getReceiversVector().at(0).getReceiverState() == 1);
   CHECK(message2.getReceiversVector().at(0).getNrOfAntennaHandles() == 0);
   CHECK(message2.getReceiversVector().at(0).getAntennaHandlesVector().size() == 0);
}

TEST_CASE("decoding for 1 receiver and 2 AntennaHandle")
{
   GetReceivers_repl message3;
   vector<uint8_t> toDecode{0x81,0x01,0x02,0x01,0x01,//msgInfo
   0x01,0x11,0x11,1,0x02,//rec
   1,0,2,0,//AH
   0,0,0,0,
   0,0,0,0};

   message3.decode(toDecode);

   REQUIRE(toDecode.size() == 22);
   CHECK(message3.getMessageType() == 1);
   CHECK(message3.getCookie() == 1);
   CHECK(message3.getReplyStatus() == 1);
   CHECK(message3.getNrOfReceivers() == 1);
   CHECK(message3.getReceiversVector().size() == 1);
   CHECK(message3.getReceiversVector().at(0).getReceiverHandle() == 1);
   CHECK(message3.getReceiversVector().at(0).getPHY_ID() == 1);
   CHECK(message3.getReceiversVector().at(0).getCTRL_ID() == 1);
   CHECK(message3.getReceiversVector().at(0).getBroadcastStandard() == 1);
   CHECK(message3.getReceiversVector().at(0).getReceiverMode() == 1);
   CHECK(message3.getReceiversVector().at(0).getReceiverState() == 1);
   CHECK(message3.getReceiversVector().at(0).getNrOfAntennaHandles() == 2);
   CHECK(message3.getReceiversVector().at(0).getAntennaHandlesVector().size() == 2);
   CHECK(message3.getReceiversVector().at(0).getAntennaHandlesVector().at(0).getAntennaHandle() == 1);
   CHECK(message3.getReceiversVector().at(0).getAntennaHandlesVector().at(1).getAntennaHandle() == 2);
}

TEST_CASE("decoding for 4 receivers and 2 AntennaHandle")
{
    GetReceivers_repl message4;
    vector<uint8_t> toDecode{0x81,0x01,0x02,0x01,0x04,//msgInfo
    0x01,0x11,0x11,1,0x02,//rec1
    1,0,2,0,//AH
    0,0,0,0,//rfa
    0x01,0x11,0x11,1,0x00,//rec2,AHis0
    0,0,0,0,//rfa
    0x01,0x11,0x11,1,0x02,//rec3
    3,0,4,0,//AH
    0,0,0,0,//rfa
    0x01,0x11,0x11,1,0x01,//rec4
    2,0,//AH
    0,0,0,0,
    0,0,0,0};

    message4.decode(toDecode);
    REQUIRE(toDecode.size() == 55);
    CHECK(message4.getMessageType() == 1);
    CHECK(message4.getCookie() == 1);
    CHECK(message4.getReplyStatus() == 1);
    CHECK(message4.getNrOfReceivers() == 4);
    CHECK(message4.getReceiversVector().size() == 4);

    CHECK(message4.getReceiversVector().at(0).getReceiverHandle() == 1);
    CHECK(message4.getReceiversVector().at(0).getPHY_ID() == 1);
    CHECK(message4.getReceiversVector().at(0).getCTRL_ID() == 1);
    CHECK(message4.getReceiversVector().at(0).getBroadcastStandard() == 1);
    CHECK(message4.getReceiversVector().at(0).getReceiverMode() == 1);
    CHECK(message4.getReceiversVector().at(0).getReceiverState() == 1);
    CHECK(message4.getReceiversVector().at(0).getNrOfAntennaHandles() == 2);
    CHECK(message4.getReceiversVector().at(0).getAntennaHandlesVector().size() == 2);
    CHECK(message4.getReceiversVector().at(0).getAntennaHandlesVector().at(0).getAntennaHandle() == 1);
    CHECK(message4.getReceiversVector().at(0).getAntennaHandlesVector().at(1).getAntennaHandle() == 2);

    CHECK(message4.getReceiversVector().at(1).getReceiverHandle() == 1);
    CHECK(message4.getReceiversVector().at(1).getPHY_ID() == 1);
    CHECK(message4.getReceiversVector().at(1).getCTRL_ID() == 1);
    CHECK(message4.getReceiversVector().at(1).getBroadcastStandard() == 1);
    CHECK(message4.getReceiversVector().at(1).getReceiverMode() == 1);
    CHECK(message4.getReceiversVector().at(1).getReceiverState() == 1);
    CHECK(message4.getReceiversVector().at(1).getNrOfAntennaHandles() == 0);
    CHECK(message4.getReceiversVector().at(1).getAntennaHandlesVector().size() == 0);

    CHECK(message4.getReceiversVector().at(2).getReceiverHandle() == 1);
    CHECK(message4.getReceiversVector().at(2).getPHY_ID() == 1);
    CHECK(message4.getReceiversVector().at(2).getCTRL_ID() == 1);
    CHECK(message4.getReceiversVector().at(2).getBroadcastStandard() == 1);
    CHECK(message4.getReceiversVector().at(2).getReceiverMode() == 1);
    CHECK(message4.getReceiversVector().at(2).getReceiverState() == 1);
    CHECK(message4.getReceiversVector().at(2).getNrOfAntennaHandles() == 2);
    CHECK(message4.getReceiversVector().at(2).getAntennaHandlesVector().size() == 2);
    CHECK(message4.getReceiversVector().at(2).getAntennaHandlesVector().at(0).getAntennaHandle() == 3);
    CHECK(message4.getReceiversVector().at(2).getAntennaHandlesVector().at(1).getAntennaHandle() == 4);

    CHECK(message4.getReceiversVector().at(3).getReceiverHandle() == 1);
    CHECK(message4.getReceiversVector().at(3).getPHY_ID() == 1);
    CHECK(message4.getReceiversVector().at(3).getCTRL_ID() == 1);
    CHECK(message4.getReceiversVector().at(3).getBroadcastStandard() == 1);
    CHECK(message4.getReceiversVector().at(3).getReceiverMode() == 1);
    CHECK(message4.getReceiversVector().at(3).getReceiverState() == 1);
    CHECK(message4.getReceiversVector().at(3).getNrOfAntennaHandles() == 1);
    CHECK(message4.getReceiversVector().at(3).getAntennaHandlesVector().size() == 1);
    CHECK(message4.getReceiversVector().at(3).getAntennaHandlesVector().at(0).getAntennaHandle() == 2);
}