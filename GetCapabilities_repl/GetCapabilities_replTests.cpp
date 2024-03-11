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
    GetCapabilities_repl message3;
    vector<uint8_t> encodedMessage{0x81,0x01,0x02,0x01,0x11,
    0x01,0x03,0x04,0x05,0x01,0,
    0x01,0x01,0,0x02,0x03,0xFC,0,0,0,0,0};

    message3.decode(encodedMessage);
    REQUIRE(encodedMessage.size() == 22);
    CHECK(message3.getMessageType() == 1);
    CHECK(message3.getCookie() == 1);
    CHECK(message3.getReplyStatus() == 1);
    CHECK(message3.getNrOfStandards() == 1);
    CHECK(message3.getNrOfSoCs() == 1);
    CHECK(message3.getstandardsVector().size() == 1);
    CHECK(message3.getstandardsVector().at(0).getbroadcastStandard() == 1);
    CHECK(message3.getstandardsVector().at(0).getcreatableReceiverCount() == 3);
    CHECK(message3.getstandardsVector().at(0).getconfigurableReceiverCount() == 4);
    CHECK(message3.getstandardsVector().at(0).getdualAntennaReceiverCount() == 5);
    CHECK(message3.getstandardsVector().at(0).getsharedByBroadcastStandard() == 1);
    CHECK(message3.getsocsVector().size() == 1);
    CHECK(message3.getsocsVector().at(0).getSOC_ID() == 1);
    CHECK(message3.getsocsVector().at(0).getSoC_Type() == 1);
    CHECK(message3.getsocsVector().at(0).getNrOfTunerPaths() == 0);
    CHECK(message3.getsocsVector().at(0).getNrOfNBTs() == 2);
    CHECK(message3.getsocsVector().at(0).getNrOfDFEs() == 3);
    CHECK(message3.getsocsVector().at(0).getCanDemodulateAM() == 1);
    CHECK(message3.getsocsVector().at(0).getCanDemodulateFM() == 1);
    CHECK(message3.getsocsVector().at(0).getCanDecodeHD() == 1);
    CHECK(message3.getsocsVector().at(0).getCanDecodeDAB() == 1);
    CHECK(message3.getsocsVector().at(0).getCanDecodeDRM() == 1);
    CHECK(message3.getsocsVector().at(0).getCanDecodeCDR() == 1);
       
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

TEST_CASE("decoding a message with 6 standard 4 soc and 8tuner path"){
    GetCapabilities_repl message5;
    vector<uint8_t> encodedMessage{0x81,0x01,0x02,0x01,0x64,//msgInfo
    0x01,0x03,0x04,0x05,0x01,0,//standard1
    0x02,0x03,0x04,0x05,0x02,0,//standard2
    0x01,0x03,0x04,0x05,0x01,0,//standard3
    0x02,0x03,0x04,0x05,0x02,0,//standard4
    0x01,0x03,0x04,0x05,0x01,0,//standard5
    0x02,0x03,0x04,0x05,0x02,0,//standard6
    0x01,1,0,3,5,0xFC,0,//soc1,path1isZero
    0x02,1,2,           //soc2,path2is2
    0xE0,0,0,0x01,      //11100000,p1
    0x00,0,0,0x01,      //p2
    2,3,0xFC,0,         //remaining soc2, 1111 1100
    0x03,1,4,           //soc3
    0xE0,0,0,0x01,      //p1 1110 0000
    0x80,0,0,0x01,      //p2 1000 0000
    0x40,0,0,0x00,      //p3 0100 0000
    0x20,0,0,0x00,      //p4 0010 0000
    2,3,0xC0,0,          //remaining soc3, 1100 0000
    0x04,1,8,           //soc4
    0xE0,0,0,0x01,      //p1 1110 0000
    0xE0,0,0,0x00,      //p2
    0x80,0,0,0x01,      //p3 1000 0000
    0x40,0,0,0x00,      //p4 0100 0000
    0x20,0,0,0x00,      //p5 0010 0000
    0xE0,0,0,0x01,      //p6 1110 0000
    0xE0,0,0,0x00,      //p7
    0x00,0,0,0x00,      //p8 0000 0000
    2,3,0x3C,0,         //remanining soc4, 0011 1100
    0,0,0,0};

    message5.decode(encodedMessage);
    REQUIRE(encodedMessage.size() == 129);
    CHECK(message5.getMessageType() == 1);
    CHECK(message5.getCookie() == 1);
    CHECK(message5.getReplyStatus() == 1);
    CHECK(message5.getNrOfStandards() == 6);
    CHECK(message5.getNrOfSoCs() == 4);
    CHECK(message5.getstandardsVector().size() == 6);
    CHECK(message5.getsocsVector().size() == 4);  
    CHECK(message5.getstandardsVector().at(0).getbroadcastStandard() == 1);
    CHECK(message5.getstandardsVector().at(0).getcreatableReceiverCount() == 3);
    CHECK(message5.getstandardsVector().at(0).getconfigurableReceiverCount() == 4);
    CHECK(message5.getstandardsVector().at(0).getdualAntennaReceiverCount() == 5);
    CHECK(message5.getstandardsVector().at(0).getsharedByBroadcastStandard() == 1);

    CHECK(message5.getstandardsVector().at(1).getbroadcastStandard() == 2);
    CHECK(message5.getstandardsVector().at(1).getcreatableReceiverCount() == 3);
    CHECK(message5.getstandardsVector().at(1).getconfigurableReceiverCount() == 4);
    CHECK(message5.getstandardsVector().at(1).getdualAntennaReceiverCount() == 5);
    CHECK(message5.getstandardsVector().at(1).getsharedByBroadcastStandard() == 2);

    CHECK(message5.getstandardsVector().at(2).getbroadcastStandard() == 1);
    CHECK(message5.getstandardsVector().at(2).getcreatableReceiverCount() == 3);
    CHECK(message5.getstandardsVector().at(2).getconfigurableReceiverCount() == 4);
    CHECK(message5.getstandardsVector().at(2).getdualAntennaReceiverCount() == 5);
    CHECK(message5.getstandardsVector().at(2).getsharedByBroadcastStandard() == 1);

    CHECK(message5.getstandardsVector().at(3).getbroadcastStandard() == 2);
    CHECK(message5.getstandardsVector().at(3).getcreatableReceiverCount() == 3);
    CHECK(message5.getstandardsVector().at(3).getconfigurableReceiverCount() == 4);
    CHECK(message5.getstandardsVector().at(3).getdualAntennaReceiverCount() == 5);
    CHECK(message5.getstandardsVector().at(3).getsharedByBroadcastStandard() == 2);

    CHECK(message5.getstandardsVector().at(4).getbroadcastStandard() == 1);
    CHECK(message5.getstandardsVector().at(4).getcreatableReceiverCount() == 3);
    CHECK(message5.getstandardsVector().at(4).getconfigurableReceiverCount() == 4);
    CHECK(message5.getstandardsVector().at(4).getdualAntennaReceiverCount() == 5);
    CHECK(message5.getstandardsVector().at(4).getsharedByBroadcastStandard() == 1);

    CHECK(message5.getstandardsVector().at(5).getbroadcastStandard() == 2);
    CHECK(message5.getstandardsVector().at(5).getcreatableReceiverCount() == 3);
    CHECK(message5.getstandardsVector().at(5).getconfigurableReceiverCount() == 4);
    CHECK(message5.getstandardsVector().at(5).getdualAntennaReceiverCount() == 5);
    CHECK(message5.getstandardsVector().at(5).getsharedByBroadcastStandard() == 2);

    CHECK(message5.getsocsVector().at(0).getSOC_ID() == 1);
    CHECK(message5.getsocsVector().at(0).getSoC_Type() == 1);
    CHECK(message5.getsocsVector().at(0).getNrOfTunerPaths() == 0);
    CHECK(message5.getsocsVector().at(0).gettunerPathsVector().size() == 0);
    CHECK(message5.getsocsVector().at(0).getNrOfNBTs() == 3);
    CHECK(message5.getsocsVector().at(0).getNrOfDFEs() == 5);
    CHECK(message5.getsocsVector().at(0).getCanDemodulateAM() == 1);
    CHECK(message5.getsocsVector().at(0).getCanDemodulateFM() == 1);
    CHECK(message5.getsocsVector().at(0).getCanDecodeHD() == 1);
    CHECK(message5.getsocsVector().at(0).getCanDecodeDAB() == 1);
    CHECK(message5.getsocsVector().at(0).getCanDecodeDRM() == 1);
    CHECK(message5.getsocsVector().at(0).getCanDecodeCDR() == 1);

    CHECK(message5.getsocsVector().at(1).getSOC_ID() == 2);
    CHECK(message5.getsocsVector().at(1).getSoC_Type() == 1);
    CHECK(message5.getsocsVector().at(1).getNrOfTunerPaths() == 2);
    CHECK(message5.getsocsVector().at(1).gettunerPathsVector().size() == 2);
    CHECK(message5.getsocsVector().at(1).gettunerPathsVector().at(0).getCanReceiveAM() == 1);
    CHECK(message5.getsocsVector().at(1).gettunerPathsVector().at(0).getCanReceiveFM() == 1);
    CHECK(message5.getsocsVector().at(1).gettunerPathsVector().at(0).getCanReceiveDAB() == 1);
    CHECK(message5.getsocsVector().at(1).gettunerPathsVector().at(0).getProvidedAsExternal() == 1);
    CHECK(message5.getsocsVector().at(1).gettunerPathsVector().at(1).getCanReceiveAM() == 0);
    CHECK(message5.getsocsVector().at(1).gettunerPathsVector().at(1).getCanReceiveFM() == 0);
    CHECK(message5.getsocsVector().at(1).gettunerPathsVector().at(1).getCanReceiveDAB() == 0);
    CHECK(message5.getsocsVector().at(1).gettunerPathsVector().at(1).getProvidedAsExternal() == 1);
    CHECK(message5.getsocsVector().at(1).getNrOfNBTs() == 2);
    CHECK(message5.getsocsVector().at(1).getNrOfDFEs() == 3);
    CHECK(message5.getsocsVector().at(1).getCanDemodulateAM() == 1);
    CHECK(message5.getsocsVector().at(1).getCanDemodulateFM() == 1);
    CHECK(message5.getsocsVector().at(1).getCanDecodeHD() == 1);
    CHECK(message5.getsocsVector().at(1).getCanDecodeDAB() == 1);
    CHECK(message5.getsocsVector().at(1).getCanDecodeDRM() == 1);
    CHECK(message5.getsocsVector().at(1).getCanDecodeCDR() == 1);

    CHECK(message5.getsocsVector().at(2).getSOC_ID() == 3);
    CHECK(message5.getsocsVector().at(2).getSoC_Type() == 1);
    CHECK(message5.getsocsVector().at(2).getNrOfTunerPaths() == 4);
    CHECK(message5.getsocsVector().at(2).gettunerPathsVector().size() == 4);
    CHECK(message5.getsocsVector().at(2).gettunerPathsVector().at(0).getCanReceiveAM() == 1);
    CHECK(message5.getsocsVector().at(2).gettunerPathsVector().at(0).getCanReceiveFM() == 1);
    CHECK(message5.getsocsVector().at(2).gettunerPathsVector().at(0).getCanReceiveDAB() == 1);
    CHECK(message5.getsocsVector().at(2).gettunerPathsVector().at(0).getProvidedAsExternal() == 1);

    CHECK(message5.getsocsVector().at(2).gettunerPathsVector().at(1).getCanReceiveAM() == 1);
    CHECK(message5.getsocsVector().at(2).gettunerPathsVector().at(1).getCanReceiveFM() == 0);
    CHECK(message5.getsocsVector().at(2).gettunerPathsVector().at(1).getCanReceiveDAB() == 0);
    CHECK(message5.getsocsVector().at(2).gettunerPathsVector().at(1).getProvidedAsExternal() == 1);

    CHECK(message5.getsocsVector().at(2).gettunerPathsVector().at(2).getCanReceiveAM() == 0);
    CHECK(message5.getsocsVector().at(2).gettunerPathsVector().at(2).getCanReceiveFM() == 1);
    CHECK(message5.getsocsVector().at(2).gettunerPathsVector().at(2).getCanReceiveDAB() == 0);
    CHECK(message5.getsocsVector().at(2).gettunerPathsVector().at(2).getProvidedAsExternal() == 0);

    CHECK(message5.getsocsVector().at(2).gettunerPathsVector().at(3).getCanReceiveAM() == 0);
    CHECK(message5.getsocsVector().at(2).gettunerPathsVector().at(3).getCanReceiveFM() == 0);
    CHECK(message5.getsocsVector().at(2).gettunerPathsVector().at(3).getCanReceiveDAB() == 1);
    CHECK(message5.getsocsVector().at(2).gettunerPathsVector().at(3).getProvidedAsExternal() == 0);

    CHECK(message5.getsocsVector().at(2).getNrOfNBTs() == 2);
    CHECK(message5.getsocsVector().at(2).getNrOfDFEs() == 3);
    CHECK(message5.getsocsVector().at(2).getCanDemodulateAM() == 1);
    CHECK(message5.getsocsVector().at(2).getCanDemodulateFM() == 1);
    CHECK(message5.getsocsVector().at(2).getCanDecodeHD() == 0);
    CHECK(message5.getsocsVector().at(2).getCanDecodeDAB() == 0);
    CHECK(message5.getsocsVector().at(2).getCanDecodeDRM() == 0);
    CHECK(message5.getsocsVector().at(2).getCanDecodeCDR() == 0);

    CHECK(message5.getsocsVector().at(3).getSOC_ID() == 4);
    CHECK(message5.getsocsVector().at(3).getSoC_Type() == 1);
    CHECK(message5.getsocsVector().at(3).getNrOfTunerPaths() == 8);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().size() == 8);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(0).getCanReceiveAM() == 1);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(0).getCanReceiveFM() == 1);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(0).getCanReceiveDAB() == 1);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(0).getProvidedAsExternal() == 1);

    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(1).getCanReceiveAM() == 1);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(1).getCanReceiveFM() == 1);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(1).getCanReceiveDAB() == 1);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(1).getProvidedAsExternal() == 0);

    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(2).getCanReceiveAM() == 1);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(2).getCanReceiveFM() == 0);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(2).getCanReceiveDAB() == 0);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(2).getProvidedAsExternal() == 1);

    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(3).getCanReceiveAM() == 0);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(3).getCanReceiveFM() == 1);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(3).getCanReceiveDAB() == 0);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(3).getProvidedAsExternal() == 0);

    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(4).getCanReceiveAM() == 0);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(4).getCanReceiveFM() == 0);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(4).getCanReceiveDAB() == 1);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(4).getProvidedAsExternal() == 0);

    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(5).getCanReceiveAM() == 1);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(5).getCanReceiveFM() == 1);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(5).getCanReceiveDAB() == 1);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(5).getProvidedAsExternal() == 1);

    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(6).getCanReceiveAM() == 1);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(6).getCanReceiveFM() == 1);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(6).getCanReceiveDAB() == 1);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(6).getProvidedAsExternal() == 0);

    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(7).getCanReceiveAM() == 0);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(7).getCanReceiveFM() == 0);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(7).getCanReceiveDAB() == 0);
    CHECK(message5.getsocsVector().at(3).gettunerPathsVector().at(7).getProvidedAsExternal() == 0);

    CHECK(message5.getsocsVector().at(3).getNrOfNBTs() == 2);
    CHECK(message5.getsocsVector().at(3).getNrOfDFEs() == 3);
    CHECK(message5.getsocsVector().at(3).getCanDemodulateAM() == 0);
    CHECK(message5.getsocsVector().at(3).getCanDemodulateFM() == 0);
    CHECK(message5.getsocsVector().at(3).getCanDecodeHD() == 1);
    CHECK(message5.getsocsVector().at(3).getCanDecodeDAB() == 1);
    CHECK(message5.getsocsVector().at(3).getCanDecodeDRM() == 1);
    CHECK(message5.getsocsVector().at(3).getCanDecodeCDR() == 1);
}