#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "GetResourceUsage_repl.hpp"

using namespace std;

/*
TEST_CASE("encode a message with zero SoCs")
{
  GetResourceUsage_repl message1;
  cout<<"object created";
  message1.setCookie(1);
  message1.setReplyStatus(1);
  message1.setRfa(0);
  message1.setNrOfSoCs(0);
  message1.setRfa7(0);

  vector<uint8_t> encoded_msg = message1.encode(); //0x01 0x02 0x03 0x01 0x00 0x00

  cout<<"size"<<size(encoded_msg)<<endl;

    CHECK(encoded_msg.at(0) == 0x01);
    CHECK(encoded_msg.at(1) == 0x02);
    CHECK(encoded_msg.at(2) == 0x03);
    CHECK(encoded_msg.at(3) == 0x01);  
    CHECK(encoded_msg.at(4) == 0x00);
    CHECK(encoded_msg.at(5) == 0x00);
    CHECK(encoded_msg.at(6) == 0x00);
}

TEST_CASE("encode a message with 1 SoCs, zero TunerPath")
{
  GetResourceUsage_repl message2;

  message2.setCookie(1);
  message2.setReplyStatus(1);
  message2.setRfa(0);
  message2.setNrOfSoCs(1);
  message2.setRfa1(0);
  message2.setSoC_ID(1);
  message2.setNrOfTunerPaths(0);

  vector<uint8_t> encoded_msg = message2.encode();
  cout<<"size"<<size(encoded_msg)<<endl;

  CHECK(encoded_msg.at(0) == 0x01);
  CHECK(encoded_msg.at(1) == 0x02);
  CHECK(encoded_msg.at(2) == 0x03);
  CHECK(encoded_msg.at(3) == 0x01);  
  CHECK(encoded_msg.at(4) == 0x00);
  CHECK(encoded_msg.at(5) == 0x01);
  CHECK(encoded_msg.at(6) == 0x01);//Rfa and SoC_ID
  CHECK(encoded_msg.at(7) == 0x00);
}

TEST_CASE("encode a message with 1 SoCs and 1 TunerPath")
{
  GetResourceUsage_repl message3;

  message3.setCookie(1);
  message3.setReplyStatus(0x10);
  message3.setRfa(0);
  message3.setNrOfSoCs(1);
  message3.setRfa1(0);
  message3.setSoC_ID(1);
  message3.setNrOfTunerPaths(1);
  message3.setAntennaHandle(4);
  message3.setActive(1);
  message3.setRfa2(0);
  message3.setActiveNBTs(0x00);
  message3.setAntennaPort(0x02);
  message3.setRfa3(0);
  message3.setNBT_ix(0x05);
  message3.setAssigned_DFE_ix(0x03);
  message3.setRfa4(0x000);

  vector<uint8_t> encoded_msg = message3.encode();
  cout<<"size"<<size(encoded_msg)<<endl;

  CHECK(encoded_msg.at(0) == 0x01);
  CHECK(encoded_msg.at(1) == 0x02);
  CHECK(encoded_msg.at(2) == 0x03);
  CHECK(encoded_msg.at(3) == 0x10);  
  CHECK(encoded_msg.at(4) == 0x00);
  CHECK(encoded_msg.at(5) == 0x01);
  CHECK(encoded_msg.at(6) == 0x01);//Rfa and SoC_ID
  CHECK(encoded_msg.at(7) == 0x01);
  CHECK(encoded_msg.at(8) == 0x04);
  CHECK(encoded_msg.at(9) == 0x01);
  CHECK(encoded_msg.at(10) == 0x00);
  CHECK(encoded_msg.at(11) == 0x02);
  CHECK(encoded_msg.at(12) == 0x00);   
}*/

TEST_CASE("encode a message with 1-SoCs, 1-TunerPath, 1-Active NBT")
{
  GetResourceUsage_repl message4;

  message4.setCookie(1);
  message4.setReplyStatus(0x10);
  message4.setRfa(0);
  message4.setNrOfSoCs(1);
  message4.setRfa1(0);
  message4.setSoC_ID(1);
  message4.setNrOfTunerPaths(1);
  message4.setAntennaHandle(4);
  message4.setActive(1);
  message4.setRfa2(0);
  message4.setActiveNBTs(0x01);
  message4.setAntennaPort(0x02);
  message4.setRfa3(0);
  message4.setNBT_ix(0x10);
  message4.setAssigned_DFE_ix(0x05);
  message4.setRfa4(0x000);

  vector<uint8_t> encoded_msg = message4.encode();
  cout<<"size"<<size(encoded_msg)<<endl;

  CHECK(encoded_msg.at(0) == 0x01);
  CHECK(encoded_msg.at(1) == 0x02);
  CHECK(encoded_msg.at(2) == 0x03);
  CHECK(encoded_msg.at(3) == 0x10);  
  CHECK(encoded_msg.at(4) == 0x00);
  CHECK(encoded_msg.at(5) == 0x01);
  CHECK(encoded_msg.at(6) == 0x01);//Rfa and SoC_ID
  CHECK(encoded_msg.at(7) == 0x01);
  CHECK(encoded_msg.at(8) == 0x04);
  CHECK(encoded_msg.at(9) == 0x01);
  CHECK(encoded_msg.at(10) == 0x00);
  CHECK(encoded_msg.at(11) == 0x12);//ActiveNBTs+AntennaPort
  CHECK(encoded_msg.at(12) == 0x00);
  CHECK(encoded_msg.at(13) == 0x10);
  CHECK(encoded_msg.at(14) == 0x05);
  CHECK(encoded_msg.at(15) == 0x00);

}