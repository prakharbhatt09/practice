#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "GetCapabilities_repl.hpp"

using namespace std;

TEST_CASE("decoding message with 0 socs and standards"){
    GetCapabilities_repl message1;
    vector<uint8_t> encodedMessage{0x81,0x01,0x02,0x01,0x00,0,0,0,0};

    message1.decode(encodedMessage);
    REQUIRE(encodedMessage.size() == 9);
    CHECK(message1.getMessageType() == 1);
    CHECK(message1.getCookie() == 1);
    CHECK(message1.getReplyStatus() == 1);
    CHECK(message1.getNrOfStandards() == 0);
    CHECK(message1.getNrOfSoCs() == 0);
}

TEST_CASE("decoding a message with 1 standard"){
    GetCapabilities_repl message2;
    vector<uint8_t> encodedMessage{0x81,0x01,0x02,0x01,0x10,
    0x01,0x03,0x04,0x05,0x01,0,
    0,0,0,0};

    message2.decode(encodedMessage);
    REQUIRE(encodedMessage.size() == 15);
    CHECK(message2.getMessageType() == 1);
    CHECK(message2.getCookie() == 1);
    CHECK(message2.getReplyStatus() == 1);
    CHECK(message2.getNrOfStandards() == 1);
    CHECK(message2.getNrOfSoCs() == 0);
    CHECK(message2.getstandardsVector().size() == 1);
    CHECK(message2.getstandardsVector().at(0).getbroadcastStandard() == 1);
    CHECK(message2.getstandardsVector().at(0).getcreatableReceiverCount() == 3);
    CHECK(message2.getstandardsVector().at(0).getconfigurableReceiverCount() == 4);
    CHECK(message2.getstandardsVector().at(0).getdualAntennaReceiverCount() == 5);
    CHECK(message2.getstandardsVector().at(0).getsharedByBroadcastStandard() == 1);
}

TEST_CASE("decoding a message with 1 soc, 0tuner path and 1 standard"){
    GetCapabilities_repl message2;
    vector<uint8_t> encodedMessage{0x81,0x01,0x02,0x01,0x11,
    0x01,0x03,0x04,0x05,0x01,0,
    0x01,0x01,0,0x02,0x03,0xFC,0,0,0,0,0};

    message2.decode(encodedMessage);
    REQUIRE(encodedMessage.size() == 22);
    CHECK(message2.getMessageType() == 1);
    CHECK(message2.getCookie() == 1);
    CHECK(message2.getReplyStatus() == 1);
    CHECK(message2.getNrOfStandards() == 1);
    CHECK(message2.getNrOfSoCs() == 1);
    CHECK(message2.getstandardsVector().size() == 1);
    CHECK(message2.getstandardsVector().at(0).getbroadcastStandard() == 1);
    CHECK(message2.getstandardsVector().at(0).getcreatableReceiverCount() == 3);
    CHECK(message2.getstandardsVector().at(0).getconfigurableReceiverCount() == 4);
    CHECK(message2.getstandardsVector().at(0).getdualAntennaReceiverCount() == 5);
    CHECK(message2.getstandardsVector().at(0).getsharedByBroadcastStandard() == 1);
    CHECK(message2.getsocsVector().size() == 1);
    CHECK(message2.getsocsVector().at(0).getSOC_ID() == 1);
    CHECK(message2.getsocsVector().at(0).getSoC_Type() == 1);
    CHECK(message2.getsocsVector().at(0).getNrOfTunerPaths() == 0);
    CHECK(message2.getsocsVector().at(0).getNrOfNBTs() == 2);
    CHECK(message2.getsocsVector().at(0).getNrOfDFEs() == 3);
    CHECK(message2.getsocsVector().at(0).getCanDemodulateAM() == 1);
    CHECK(message2.getsocsVector().at(0).getCanDemodulateFM() == 1);
    CHECK(message2.getsocsVector().at(0).getCanDecodeHD() == 1);
    CHECK(message2.getsocsVector().at(0).getCanDecodeDAB() == 1);
    CHECK(message2.getsocsVector().at(0).getCanDecodeDRM() == 1);
    CHECK(message2.getsocsVector().at(0).getCanDecodeCDR() == 1);
       
}

TEST_CASE("decoding a message with 1 soc, 1tuner path and 1 standard"){
    GetCapabilities_repl message4;
    vector<uint8_t> encodedMessage{0x81,0x01,0x02,0x01,0x11,
    0x01,0x03,0x04,0x05,0x01,0,
    0x01,0x01,1,0xE0,0,0,0x01,0x02,0x03,0xFC,0,0,0,0,0};

    message4.decode(encodedMessage);
    CHECK(message4.getMessageType() == 1);
    CHECK(message4.getCookie() == 1);
    CHECK(message4.getReplyStatus() == 1);
    CHECK(message4.getNrOfStandards() == 1);
    CHECK(message4.getNrOfSoCs() == 1);
    CHECK(message4.getstandardsVector().size() == 1);
    CHECK(message4.getstandardsVector().at(0).getbroadcastStandard() == 1);
    CHECK(message4.getstandardsVector().at(0).getcreatableReceiverCount() == 3);
    CHECK(message4.getstandardsVector().at(0).getconfigurableReceiverCount() == 4);
    CHECK(message4.getstandardsVector().at(0).getdualAntennaReceiverCount() == 5);
    CHECK(message4.getstandardsVector().at(0).getsharedByBroadcastStandard() == 1);
    CHECK(message4.getsocsVector().size() == 1);
    CHECK(message4.getsocsVector().at(0).getSOC_ID() == 1);
    CHECK(message4.getsocsVector().at(0).getSoC_Type() == 1);
    CHECK(message4.getsocsVector().at(0).getNrOfTunerPaths() == 1);
    CHECK(message4.getsocsVector().at(0).gettunerPathsVector().size() == 1);
    CHECK(message4.getsocsVector().at(0).gettunerPathsVector().at(0).getCanReceiveAM() == 1);
    CHECK(message4.getsocsVector().at(0).gettunerPathsVector().at(0).getCanReceiveFM() == 1);
    CHECK(message4.getsocsVector().at(0).gettunerPathsVector().at(0).getCanReceiveDAB() == 1);
    CHECK(message4.getsocsVector().at(0).gettunerPathsVector().at(0).getProvidedAsExternal() == 1);
    CHECK(message4.getsocsVector().at(0).getNrOfNBTs() == 2);
    CHECK(message4.getsocsVector().at(0).getNrOfDFEs() == 3);
    CHECK(message4.getsocsVector().at(0).getCanDemodulateAM() == 1);
    CHECK(message4.getsocsVector().at(0).getCanDemodulateFM() == 1);
    CHECK(message4.getsocsVector().at(0).getCanDecodeHD() == 1);
    CHECK(message4.getsocsVector().at(0).getCanDecodeDAB() == 1);
    CHECK(message4.getsocsVector().at(0).getCanDecodeDRM() == 1);
    CHECK(message4.getsocsVector().at(0).getCanDecodeCDR() == 1);
       
}