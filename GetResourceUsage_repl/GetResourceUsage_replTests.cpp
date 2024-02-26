#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "GetResourceUsage_repl.hpp"
#include "SoC.hpp"
#include "TunerPath.hpp"
#include "NBT.hpp"
#include "DFE.hpp"
#include "Receiver.hpp"

using namespace std;

TEST_CASE("encoding a message with zero SoCs")
{
  GetResourceUsage_repl message1(1,1,0,0,0);
  vector<uint8_t> encoded_msg = message1.encode();
  CHECK(encoded_msg.at(0) == 0x01);//Msgtyp+cookie
  CHECK(encoded_msg.at(1) == 0x02);//op1
  CHECK(encoded_msg.at(2) == 0x03);//op2
  CHECK(encoded_msg.at(3) == 1);//ReplyStatus
  CHECK(encoded_msg.at(4) == 0);//rfa+SoC
}
TEST_CASE("encoding a message with 1 SoC, zero TunerPath and zero DFE")
{
  GetResourceUsage_repl message2(1,1,0,1,0);
  SoC soc1(0,1,0,0,0);
  message2.addsocInstance(soc1);

  vector<uint8_t> encoded_msg = message2.encode();
  cout<<"size"<<size(encoded_msg);
  CHECK(encoded_msg.at(0) == 1);
  CHECK(encoded_msg.at(0) == 1);
  CHECK(encoded_msg.at(1) == 0x02);
  CHECK(encoded_msg.at(2) == 0x03);
  CHECK(encoded_msg.at(3) == 1);
  CHECK(encoded_msg.at(4) == 0x01);
  CHECK(encoded_msg.at(5) == 0x01);
  CHECK(encoded_msg.at(6) == 0x00);
  CHECK(encoded_msg.at(7) == 0x00);//dfe
  CHECK(encoded_msg.at(8) == 0x00);
  CHECK(encoded_msg.at(9) == 0x00);
  CHECK(encoded_msg.at(10) == 0x00);
  CHECK(encoded_msg.at(11) == 0x00);
  CHECK(encoded_msg.at(12) == 0x00);
  CHECK(encoded_msg.at(13) == 0x00);
  CHECK(encoded_msg.at(14) == 0x00);
  CHECK(encoded_msg.at(15) == 0x00);
  CHECK(size(encoded_msg) == 16);
}

TEST_CASE("encoding a message with 1 SoCs, 1 TunerPath, 1 NBT, 1 DFE, 1 AssignedReceiver")
{
  GetResourceUsage_repl message3(1,1,0,1,0x0000);
  SoC soc1(0,1,1,1,0x0000);
  TunerPath path1(0x11,1,0x00,0x01,1,0);
  NBT nbt1(0x10,0x05,0x001);
  DFE dfe1(1);
  Receiver rec1(0x20,2,2,0x000);
  dfe1.addReceiverInstance(rec1);
  soc1.addDFEInstance(dfe1);
  path1.addNBTInstance(nbt1);
  soc1.addtunerPathInstance(path1);
  message3.addsocInstance(soc1);

  vector<uint8_t> encoded_msg = message3.encode();
  cout<<"size"<<size(encoded_msg);
  CHECK(encoded_msg.at(0) == 1);
  CHECK(encoded_msg.at(1) == 0x02);
  CHECK(encoded_msg.at(2) == 0x03);
  CHECK(encoded_msg.at(3) == 1);//replystatus
  CHECK(encoded_msg.at(4) == 0x01);//rfa+nrofsocs
  CHECK(encoded_msg.at(5) == 0x01);//rfa+socid
  CHECK(encoded_msg.at(6) == 0x01);//tunerpaths
  CHECK(encoded_msg.at(7) == 0x11);//AHandle
  CHECK(encoded_msg.at(8) == 0x11);//1,0,1 how?
  CHECK(encoded_msg.at(9) == 0x10);//AP+Rfa3
  CHECK(encoded_msg.at(10) == 0x10);
  CHECK(encoded_msg.at(11) == 0x05);
  CHECK(encoded_msg.at(12) == 0x00);
  CHECK(encoded_msg.at(13) == 0x01);
  CHECK(encoded_msg.at(14) == 0x01);//dfe
  CHECK(encoded_msg.at(15) == 0x01);//assgn rec
  CHECK(encoded_msg.at(16) == 0x20);//rec handle
  CHECK(encoded_msg.at(17) == 0x22);//broadcaststd+Mode
  CHECK(encoded_msg.at(18) == 0x00);
  CHECK(encoded_msg.at(19) == 0x00);
  CHECK(encoded_msg.at(20) == 0x00);
  CHECK(encoded_msg.at(21) == 0x00);
  CHECK(encoded_msg.at(22) == 0x00);
  CHECK(encoded_msg.at(23) == 0x00);
  CHECK(encoded_msg.at(24) == 0x00);
  CHECK(encoded_msg.at(25) == 0x00);
  CHECK(encoded_msg.at(26) == 0x00);
  CHECK(encoded_msg.at(27) == 0x00);
  CHECK(size(encoded_msg) == 28);
}

/*TEST_CASE("encoding a message with 2 SoCs, 1 TunerPath, 1 NBT, 1 DFE, 1 AssignedReceiver")
{
  GetResourceUsage_repl message4(1,1,0,1,0x0000);
  SoC soc1(0,1,1,1,0x0000);
  TunerPath path1(0x11,1,0x00,0x01,1,0);
  NBT nbt1(0x10,0x05,0x001);
  DFE dfe1(1);
  Receiver rec1(0x20,2,2,0x000);
  dfe1.addReceiverInstance(rec1);
  soc1.addDFEInstance(dfe1);
  path1.addNBTInstance(nbt1);
  soc1.addtunerPathInstance(path1);
  message4.addsocInstance(soc1);

  vector<uint8_t> encoded_msg = message4.encode();
  cout<<"size"<<size(encoded_msg);
  CHECK(encoded_msg.at(0) == 1);
  CHECK(encoded_msg.at(1) == 0x02);
  CHECK(encoded_msg.at(2) == 0x03);
  CHECK(encoded_msg.at(3) == 1);//replystatus
  CHECK(encoded_msg.at(4) == 0x01);//rfa+nrofsocs
  CHECK(encoded_msg.at(5) == 0x01);//rfa+socid
  CHECK(encoded_msg.at(6) == 0x01);//tunerpaths
  CHECK(encoded_msg.at(7) == 0x11);//AHandle
  CHECK(encoded_msg.at(8) == 0x11);//1,0,1 how?
  CHECK(encoded_msg.at(9) == 0x10);
  CHECK(encoded_msg.at(10) == 0x05);
  CHECK(encoded_msg.at(11) == 0x00);
  CHECK(encoded_msg.at(12) == 0x01);
  CHECK(encoded_msg.at(13) == 0x01);//dfe
  CHECK(encoded_msg.at(14) == 0x01);//assgn rec
  CHECK(encoded_msg.at(15) == 0x20);//rec handle
  CHECK(encoded_msg.at(16) == 0x22);//broadcaststd+Mode
  CHECK(encoded_msg.at(17) == 0x00);
  CHECK(encoded_msg.at(18) == 0x00);
  CHECK(encoded_msg.at(19) == 0x00);
  CHECK(encoded_msg.at(20) == 0x00);
  CHECK(encoded_msg.at(21) == 0x00);
  CHECK(encoded_msg.at(22) == 0x00);
  CHECK(encoded_msg.at(23) == 0x00);
  CHECK(encoded_msg.at(24) == 0x00);
  CHECK(encoded_msg.at(25) == 0x00);
  CHECK(encoded_msg.at(26) == 0x00);
  CHECK(size(encoded_msg) == 27);
}

TEST_CASE("decoding a message")
{
GetResourceUsage_repl message5;
vector<uint8_t> toDecode {0x01, 0x02, 0x03, 0x01, 0x00};

  message5.decode(toDecode);
  CHECK(message5.getCookie() == 0x01);
  CHECK(message5.getReplyStatus() == 0x01);
  CHECK(message5.getRfa() == 0);
  CHECK(message5.getNrOfSoCs() == 0);
  CHECK(message5.getRfa7() == 0);
}*/