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
  REQUIRE(encoded_msg.size() == 9);
  CHECK(encoded_msg.at(0) == 0x01);//Msgtyp+cookie
  CHECK(encoded_msg.at(1) == 0x02);//op1
  CHECK(encoded_msg.at(2) == 0x03);//op2
  CHECK(encoded_msg.at(3) == 1);//ReplyStatus
  CHECK(encoded_msg.at(4) == 0);//rfa+SoC
  CHECK(encoded_msg.at(5) == 0);
  CHECK(encoded_msg.at(6) == 0);
  CHECK(encoded_msg.at(7) == 0);
  CHECK(encoded_msg.at(8) == 0);
}

TEST_CASE("decoding a message with zero SoCs")
{
  GetResourceUsage_repl msg1ToDecode;
  vector<uint8_t> encoded_msg{00000001,00000010,00000011,00000001,00000000,00000000,00000000,00000000,00000000};

  msg1ToDecode.decode(encoded_msg);

  CHECK(msg1ToDecode.getCookie() == 1);
  CHECK(msg1ToDecode.getNrOfSoCs() == 0);
  CHECK(msg1ToDecode.getReplyStatus() == 1);
  CHECK(msg1ToDecode.socs.size() == 0);

}

TEST_CASE("encoding a message with 1 SoC, zero TunerPath and zero DFE")
{
  GetResourceUsage_repl message2(1,1,0,1,0);
  SoC soc1(0,1,0,0,0);
  message2.addsocInstance(soc1);

  vector<uint8_t> encoded_msg = message2.encode();
  REQUIRE(encoded_msg.size() == 16);
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
}

TEST_CASE("decoding a message with 1 SoC, zero Tunerpath, zero DFEs")
{
  GetResourceUsage_repl msg2ToDecode; //Arrange
  vector<uint8_t> encoded_msg{00000001,00000010,00000011,00000001,00000001,00000001,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000};
  
  msg2ToDecode.decode(encoded_msg); //Act

  CHECK(msg2ToDecode.getNrOfSoCs() == 1);                   //Assert
  CHECK(msg2ToDecode.getCookie() == 1);
  CHECK(msg2ToDecode.getReplyStatus() == 1);
  CHECK(msg2ToDecode.socs.size() == 1);
  CHECK(msg2ToDecode.socs.at(0).getSoC_ID() == 1);
  CHECK(msg2ToDecode.socs.at(0).getNrOfTunerPaths() == 0);
  CHECK(msg2ToDecode.socs.at(0).getNrOfDFEs() == 0);
  CHECK(msg2ToDecode.socs.at(0).dfes.size() == 0);
  CHECK(msg2ToDecode.socs.at(0).tunerPaths.size() == 0);
}

TEST_CASE("encoding a message with 1 SoCs, 1 TunerPath, 1 NBT, 1 DFE, 1 AssignedReceiver")
{
  GetResourceUsage_repl message3(1,1,0,1,0x0000);
  SoC soc1(0,1,1,1,0x0000);
  TunerPath path1(0x11,1,0,1,1,0);
  NBT nbt1(0x10,0x05,0x001);
  DFE dfe1(1);
  Receiver rec1(0x20,2,2,0x000);

  dfe1.addReceiverInstance(rec1);
  soc1.addDFEInstance(dfe1);
  path1.addNBTInstance(nbt1);
  soc1.addtunerPathInstance(path1);
  message3.addsocInstance(soc1);

  vector<uint8_t> encoded_msg = message3.encode();
  REQUIRE(encoded_msg.size() == 28);
  CHECK(encoded_msg.at(0) == 1);
  CHECK(encoded_msg.at(1) == 0x02);
  CHECK(encoded_msg.at(2) == 0x03);
  CHECK(encoded_msg.at(3) == 1);//replystatus
  CHECK(encoded_msg.at(4) == 0x01);//rfa+nrofsocs
  CHECK(encoded_msg.at(5) == 0x01);//rfa+socid
  CHECK(encoded_msg.at(6) == 0x01);//tunerpaths
  CHECK(encoded_msg.at(7) == 0x11);//AHandle
  CHECK((uint16_t)encoded_msg.at(8) == 0x81);//1,0,1 check?
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
}

TEST_CASE("decoding a message with 1 SoCs, 1 TunerPath, 1 NBT, 1 DFE, 1 AssignedReceiver")
{
  GetResourceUsage_repl msg3ToDecode; //Arrange
  vector<uint8_t> encoded_msg{1,2,3,1,1,1,1,0x11,0x81,0x10,0x10,5,0,1,1,1,0x20,0x22,0,0,0,0,0,0,0,0,0,0};
  
  msg3ToDecode.decode(encoded_msg); //Act
                                    
  CHECK(msg3ToDecode.getCookie() == 1); //Assert
  CHECK(msg3ToDecode.getReplyStatus() == 1);
  CHECK(msg3ToDecode.getNrOfSoCs() == 1); 
  CHECK(msg3ToDecode.socs.size() == 1);
  CHECK(msg3ToDecode.socs.at(0).getSoC_ID() == 1);
  CHECK(msg3ToDecode.socs.at(0).getNrOfTunerPaths() == 1);
  CHECK(msg3ToDecode.socs.at(0).getNrOfDFEs() == 1);
  CHECK(msg3ToDecode.socs.at(0).tunerPaths.size() == 1);
  CHECK(msg3ToDecode.socs.at(0).dfes.size() == 1);
  CHECK(msg3ToDecode.socs.at(0).tunerPaths.at(0).getAntennaHandle() == 0x11);
  CHECK(msg3ToDecode.socs.at(0).tunerPaths.at(0).getActive() == 1);
  CHECK(msg3ToDecode.socs.at(0).tunerPaths.at(0).getActiveNBTs() == 1);
  CHECK(msg3ToDecode.socs.at(0).tunerPaths.at(0).getAntennaPort() == 1); 
  CHECK(msg3ToDecode.socs.at(0).tunerPaths.at(0).nbts.size() == 1);
  CHECK(msg3ToDecode.socs.at(0).tunerPaths.at(0).nbts.at(0).getNBT_ix() == 0x10);
  CHECK(msg3ToDecode.socs.at(0).tunerPaths.at(0).nbts.at(0).getAssigned_DFE_ix() == 0x05);  
  CHECK(msg3ToDecode.socs.at(0).dfes.at(0).getNrOfAssignedReceivers() == 1);
  CHECK(msg3ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.size() == 1);
  CHECK(msg3ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg3ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(0).getBroadcastStandard() == 2);
  CHECK(msg3ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(0).getMode() == 2);
}

TEST_CASE("encoding with 2 socs, 1 TunerPath & 0 activeNBT, 2DFE & 1Receiver")
{
  // Arrange
  GetResourceUsage_repl message4(1,1,0,2,0x0000);
  SoC soc1(0,1,1,2,0x0000);
  SoC soc2(0,2,0,0,0x0000);
  TunerPath path1(0x11,1,0,0,1,0);
  DFE dfe1(1);
  DFE dfe2(0);
  Receiver rec1(0x20,2,2,0x000);
  dfe1.addReceiverInstance(rec1);
  soc1.addDFEInstance(dfe1);
  soc1.addDFEInstance(dfe2);
  soc1.addtunerPathInstance(path1);
  message4.addsocInstance(soc1);
  message4.addsocInstance(soc2);


  // Act
  vector<uint8_t> encoded_msg = message4.encode();


  // Assert
  REQUIRE(encoded_msg.size() == 32);
  CHECK(encoded_msg.at(0) == 1);
  CHECK(encoded_msg.at(1) == 0x02);
  CHECK(encoded_msg.at(2) == 0x03);
  CHECK(encoded_msg.at(3) == 1);
  CHECK(encoded_msg.at(4) == 2);//rfa+nrofSoCs
  CHECK(encoded_msg.at(5) == 1);//rfa+socID
  CHECK(encoded_msg.at(6) == 1);//nroftunerPaths-soc1
  CHECK(encoded_msg.at(7) == 0x11);//antennahandle
  CHECK((uint16_t)encoded_msg.at(8) == 0x80);//Active+rfa+activenbts
  CHECK(encoded_msg.at(9) == 0x10);//APort+rfa
  CHECK(encoded_msg.at(10) == 2);//dfe
  CHECK(encoded_msg.at(11) == 1);
  CHECK(encoded_msg.at(12) == 0x20);
  CHECK(encoded_msg.at(13) == 0x22);
  CHECK(encoded_msg.at(14) == 0x00);
  CHECK(encoded_msg.at(15) == 0x00);
  CHECK(encoded_msg.at(16) == 0x00);//assgnrec-dfe2
  CHECK(encoded_msg.at(17) == 0x00);//rfa6
  CHECK(encoded_msg.at(18) == 0x00);
  CHECK(encoded_msg.at(19) == 0x00);
  CHECK(encoded_msg.at(20) == 0x00);//soc1 done
  CHECK(encoded_msg.at(21) == 2);//rfa+socID
  CHECK(encoded_msg.at(22) == 0);//nroftunerpaths.soc2
  CHECK(encoded_msg.at(23) == 0x00);//dfe
  CHECK(encoded_msg.at(24) == 0x00);
  CHECK(encoded_msg.at(25) == 0x00);
  CHECK(encoded_msg.at(26) == 0x00);
  CHECK(encoded_msg.at(27) == 0x00);//rfa6.soc2
  CHECK(encoded_msg.at(28) == 0x00);
  CHECK(encoded_msg.at(29) == 0x00);
  CHECK(encoded_msg.at(30) == 0x00);
  CHECK(encoded_msg.at(31) == 0x00);
}

TEST_CASE("decoding with 2 socs, 1 TunerPath & 0 activeNBT, 2DFE & 1Receiver")
{
  GetResourceUsage_repl msg4ToDecode; //Arrange
  vector<uint8_t> encoded_msg{1,2,3,1,2,1,1,0x11,0x80,0x10,2,1,0x20,0x22,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0};
  
  msg4ToDecode.decode(encoded_msg); //Act
                                    
  CHECK(msg4ToDecode.getCookie() == 1); //Assert
  CHECK(msg4ToDecode.getReplyStatus() == 1);
  CHECK(msg4ToDecode.getNrOfSoCs() == 2); 
  CHECK(msg4ToDecode.socs.size() == 2);
  CHECK(msg4ToDecode.socs.at(0).getSoC_ID() == 1);
  CHECK(msg4ToDecode.socs.at(0).getNrOfTunerPaths() == 1);
  CHECK(msg4ToDecode.socs.at(0).getNrOfDFEs() == 2);
  CHECK(msg4ToDecode.socs.at(0).tunerPaths.size() == 1);
  CHECK(msg4ToDecode.socs.at(0).dfes.size() == 2);
  CHECK(msg4ToDecode.socs.at(0).tunerPaths.at(0).getAntennaHandle() == 0x11);
  CHECK(msg4ToDecode.socs.at(0).tunerPaths.at(0).getActive() == 1);
  CHECK(msg4ToDecode.socs.at(0).tunerPaths.at(0).getActiveNBTs() == 0);
  CHECK(msg4ToDecode.socs.at(0).tunerPaths.at(0).getAntennaPort() == 1); 
  CHECK(msg4ToDecode.socs.at(0).tunerPaths.at(0).nbts.size() == 0); 
  CHECK(msg4ToDecode.socs.at(0).dfes.at(0).getNrOfAssignedReceivers() == 1);
  CHECK(msg4ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.size() == 1);
  CHECK(msg4ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg4ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(0).getBroadcastStandard() == 2);
  CHECK(msg4ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(0).getMode() == 2);
  CHECK(msg4ToDecode.socs.at(0).dfes.at(1).getNrOfAssignedReceivers() == 0);
  CHECK(msg4ToDecode.socs.at(1).getSoC_ID() == 2);
  CHECK(msg4ToDecode.socs.at(1).getNrOfTunerPaths() == 0);
  CHECK(msg4ToDecode.socs.at(1).getNrOfDFEs() == 0);
  }

TEST_CASE("encoding with 1 soc, 1 TunerPath & 4 activeNBT, 1DFE & 4Receiver")
{
  GetResourceUsage_repl message5(1,1,0,1,0x0000);
  SoC soc1(0,1,1,1,0x0000);
  TunerPath path1(0x11,1,0,4,1,0);
  NBT nbt1(1,1,0x000);
  NBT nbt2(2,2,0x000);
  NBT nbt3(3,3,0x000);
  NBT nbt4(4,4,0x000);
  DFE dfe1(4);
  Receiver rec1(0x20,2,2,0x000);
  Receiver rec2(0x20,1,1,0x000);
  Receiver rec3(0x20,2,2,0x000);
  Receiver rec4(0x20,1,1,0x000);
  path1.addNBTInstance(nbt1);
  path1.addNBTInstance(nbt2);
  path1.addNBTInstance(nbt3);
  path1.addNBTInstance(nbt4);
  soc1.addtunerPathInstance(path1);
  dfe1.addReceiverInstance(rec1);
  dfe1.addReceiverInstance(rec2);
  dfe1.addReceiverInstance(rec3);
  dfe1.addReceiverInstance(rec4);
  soc1.addDFEInstance(dfe1);
  message5.addsocInstance(soc1);


  vector<uint8_t> encoded_msg = message5.encode();
  REQUIRE(encoded_msg.size() == 52);
  //CHECK(encoded_msg.at() == );
  CHECK(encoded_msg.at(0) == 1);
  CHECK(encoded_msg.at(1) == 0x02);
  CHECK(encoded_msg.at(2) == 0x03);
  CHECK(encoded_msg.at(3) == 1);
  CHECK(encoded_msg.at(4) == 1);//rfa+nrofSoCs 
  CHECK(encoded_msg.at(5) == 1);//rfa+socID
  CHECK(encoded_msg.at(6) == 1);//tunerpaths
  CHECK(encoded_msg.at(7) == 0x11);//Ahandle
  CHECK((uint16_t)encoded_msg.at(8) == 0x84);//active+rfa+activeNbts
  CHECK(encoded_msg.at(9) == 0x10);
  CHECK(encoded_msg.at(10) == 1);
  CHECK(encoded_msg.at(11) == 1);
  CHECK(encoded_msg.at(12) == 0);
  CHECK(encoded_msg.at(13) == 0);
  CHECK(encoded_msg.at(14) == 2);//nbt2
  CHECK(encoded_msg.at(15) == 2);
  CHECK(encoded_msg.at(16) == 0);
  CHECK(encoded_msg.at(17) == 0);
  CHECK(encoded_msg.at(18) == 3);//nbt3
  CHECK(encoded_msg.at(19) == 3);
  CHECK(encoded_msg.at(20) == 0);
  CHECK(encoded_msg.at(21) == 0);
  CHECK(encoded_msg.at(22) == 4);//nbt4
  CHECK(encoded_msg.at(23) == 4);
  CHECK(encoded_msg.at(24) == 0);
  CHECK(encoded_msg.at(25) == 0);
  CHECK(encoded_msg.at(26) == 1);//dfe nr
  CHECK(encoded_msg.at(27) == 4);
  CHECK(encoded_msg.at(28) == 0x20);//rec1
  CHECK(encoded_msg.at(29) == 0x22);
  CHECK(encoded_msg.at(30) == 0);
  CHECK(encoded_msg.at(31) == 0);
  CHECK(encoded_msg.at(32) == 0x20);//rec2
  CHECK(encoded_msg.at(33) == 0x11);
  CHECK(encoded_msg.at(34) == 0);
  CHECK(encoded_msg.at(35) == 0);
  CHECK(encoded_msg.at(36) == 0x20);//rec3
  CHECK(encoded_msg.at(37) == 0x22);
  CHECK(encoded_msg.at(38) == 0);
  CHECK(encoded_msg.at(39) == 0);
  CHECK(encoded_msg.at(40) == 0x20);//rec4
  CHECK(encoded_msg.at(41) == 0x11);
  CHECK(encoded_msg.at(42) == 0);
  CHECK(encoded_msg.at(43) == 0);
  CHECK(encoded_msg.at(44) == 0);//rfa6
  CHECK(encoded_msg.at(45) == 0);
  CHECK(encoded_msg.at(46) == 0);
  CHECK(encoded_msg.at(47) == 0);
  CHECK(encoded_msg.at(48) == 0);//rfa7
  CHECK(encoded_msg.at(49) == 0);
  CHECK(encoded_msg.at(50) == 0);
  CHECK(encoded_msg.at(51) == 0);
}

TEST_CASE("decoding with 1 soc, 1 TunerPath & 4 activeNBT, 1DFE & 4Receiver")
{
  GetResourceUsage_repl msg5ToDecode; //Arrange
  vector<uint8_t> encoded_msg{1,2,3,1,1,1,1,0x11,0x84,0x10,1,1,0,0,2,2,0,0,3,3,0,0,4,4,0,0,1,4,0x20,0x22,0,0,0x20,0x11,0,0,0x20,0x22,0,0,0x20,0x11,0,0,0,0,0,0,0,0,0,0};
  
  msg5ToDecode.decode(encoded_msg); //Act
                                    
  CHECK(msg5ToDecode.getCookie() == 1); //Assert
  CHECK(msg5ToDecode.getReplyStatus() == 1);
  CHECK(msg5ToDecode.getNrOfSoCs() == 1); 
  CHECK(msg5ToDecode.socs.size() == 1);
  CHECK(msg5ToDecode.socs.at(0).getSoC_ID() == 1);
  CHECK(msg5ToDecode.socs.at(0).getNrOfTunerPaths() == 1);
  CHECK(msg5ToDecode.socs.at(0).getNrOfDFEs() == 1);
  CHECK(msg5ToDecode.socs.at(0).tunerPaths.size() == 1);
  CHECK(msg5ToDecode.socs.at(0).dfes.size() == 1);
  CHECK(msg5ToDecode.socs.at(0).tunerPaths.at(0).getAntennaHandle() == 0x11);
  CHECK(msg5ToDecode.socs.at(0).tunerPaths.at(0).getActive() == 1);
  CHECK(msg5ToDecode.socs.at(0).tunerPaths.at(0).getActiveNBTs() == 4);
  CHECK(msg5ToDecode.socs.at(0).tunerPaths.at(0).getAntennaPort() == 1); 
  CHECK(msg5ToDecode.socs.at(0).tunerPaths.at(0).nbts.size() == 4);
  CHECK(msg5ToDecode.socs.at(0).tunerPaths.at(0).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg5ToDecode.socs.at(0).tunerPaths.at(0).nbts.at(0).getAssigned_DFE_ix() == 1);
  CHECK(msg5ToDecode.socs.at(0).tunerPaths.at(0).nbts.at(1).getNBT_ix() == 2);
  CHECK(msg5ToDecode.socs.at(0).tunerPaths.at(0).nbts.at(1).getAssigned_DFE_ix() == 2);
  CHECK(msg5ToDecode.socs.at(0).tunerPaths.at(0).nbts.at(2).getNBT_ix() == 3);
  CHECK(msg5ToDecode.socs.at(0).tunerPaths.at(0).nbts.at(2).getAssigned_DFE_ix() == 3);
  CHECK(msg5ToDecode.socs.at(0).tunerPaths.at(0).nbts.at(3).getNBT_ix() == 4);
  CHECK(msg5ToDecode.socs.at(0).tunerPaths.at(0).nbts.at(3).getAssigned_DFE_ix() == 4);
  CHECK(msg5ToDecode.socs.at(0).dfes.at(0).getNrOfAssignedReceivers() == 4);
  CHECK(msg5ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.size() == 4);
  CHECK(msg5ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg5ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(0).getBroadcastStandard() == 2);
  CHECK(msg5ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(0).getMode() == 2);
  CHECK(msg5ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg5ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg5ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(1).getMode() == 1);
  CHECK(msg5ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(2).getReceiverHandle() == 0x20);
  CHECK(msg5ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(2).getBroadcastStandard() == 2);
  CHECK(msg5ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(2).getMode() == 2);
  CHECK(msg5ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(3).getReceiverHandle() == 0x20);
  CHECK(msg5ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(3).getBroadcastStandard() == 1);
  CHECK(msg5ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(3).getMode() == 1);
  }

TEST_CASE("encoding with 1 soc, 4 TunerPath & 4 activeNBT, 4DFE & 4Receiver")
{
  GetResourceUsage_repl message6(1,1,0,1,0x0000);
  SoC soc1(0,1,4,4,0x0000);
  TunerPath path1(0x11,1,0,1,1,0);
  TunerPath path2(0x11,1,0,2,1,0);
  TunerPath path3(0x11,0,0,1,1,0);
  TunerPath path4(0x11,1,0,4,1,0);
  NBT nbt1(1,1,0x000);
  NBT nbt2(2,2,0x000);
  NBT nbt3(3,3,0x000);
  NBT nbt4(4,4,0x000);
  DFE dfe1(2);
  DFE dfe2(4);
  DFE dfe3(0);
  DFE dfe4(1);
  Receiver rec1(0x20,2,2,0x000);
  Receiver rec2(0x20,1,1,0x000);
  Receiver rec3(0x20,2,2,0x000);
  Receiver rec4(0x20,1,1,0x000);
  path1.addNBTInstance(nbt1);
  path2.addNBTInstance(nbt1);
  path2.addNBTInstance(nbt2);
  path3.addNBTInstance(nbt3);
  path4.addNBTInstance(nbt1);
  path4.addNBTInstance(nbt2);
  path4.addNBTInstance(nbt3);
  path4.addNBTInstance(nbt4);
  soc1.addtunerPathInstance(path1);
  soc1.addtunerPathInstance(path2);
  soc1.addtunerPathInstance(path3);
  soc1.addtunerPathInstance(path4);
  dfe1.addReceiverInstance(rec1);
  dfe1.addReceiverInstance(rec2);
  dfe2.addReceiverInstance(rec1);
  dfe2.addReceiverInstance(rec2);
  dfe2.addReceiverInstance(rec3);
  dfe2.addReceiverInstance(rec4);
  dfe4.addReceiverInstance(rec4);
  soc1.addDFEInstance(dfe1);
  soc1.addDFEInstance(dfe2);
  soc1.addDFEInstance(dfe3);
  soc1.addDFEInstance(dfe4);
  message6.addsocInstance(soc1);


  vector<uint8_t> encoded_msg = message6.encode();
  REQUIRE(encoded_msg.size() == 92);
  //CHECK(encoded_msg.at() == );
  CHECK(encoded_msg.at(0) == 1);
  CHECK(encoded_msg.at(1) == 0x02);
  CHECK(encoded_msg.at(2) == 0x03);
  CHECK(encoded_msg.at(3) == 1);
  CHECK(encoded_msg.at(4) == 1);
  CHECK(encoded_msg.at(5) == 1);
  CHECK(encoded_msg.at(6) == 4);
  CHECK(encoded_msg.at(7) == 0x11);
  CHECK((uint16_t)encoded_msg.at(8) == 0x81);
  CHECK(encoded_msg.at(9) == 0x10);
  CHECK(encoded_msg.at(10) == 1);
  CHECK(encoded_msg.at(11) == 1);
  CHECK(encoded_msg.at(12) == 0);
  CHECK(encoded_msg.at(13) == 0);
  CHECK(encoded_msg.at(14) == 0x11);
  CHECK((uint16_t)encoded_msg.at(15) == 0x82);
  CHECK(encoded_msg.at(16) == 0x10);
  CHECK(encoded_msg.at(17) == 1);
  CHECK(encoded_msg.at(18) == 1);
  CHECK(encoded_msg.at(19) == 0);
  CHECK(encoded_msg.at(20) == 0);
  CHECK(encoded_msg.at(21) == 2);
  CHECK(encoded_msg.at(22) == 2);
  CHECK(encoded_msg.at(23) == 0);
  CHECK(encoded_msg.at(24) == 0);
  CHECK(encoded_msg.at(25) == 0x11);
  CHECK(encoded_msg.at(26) == 1);
  CHECK(encoded_msg.at(27) == 0x10);
  CHECK(encoded_msg.at(28) == 3);
  CHECK(encoded_msg.at(29) == 3);
  CHECK(encoded_msg.at(30) == 0);
  CHECK(encoded_msg.at(31) == 0);
  CHECK(encoded_msg.at(32) == 0x11);
  CHECK((uint16_t)encoded_msg.at(33) == 0x84);
  CHECK(encoded_msg.at(34) == 0x10);
  CHECK(encoded_msg.at(35) == 1);
  CHECK(encoded_msg.at(36) == 1);
  CHECK(encoded_msg.at(37) == 0);
  CHECK(encoded_msg.at(38) == 0);
  CHECK(encoded_msg.at(39) == 2);
  CHECK(encoded_msg.at(40) == 2);
  CHECK(encoded_msg.at(41) == 0);
  CHECK(encoded_msg.at(42) == 0);
  CHECK(encoded_msg.at(43) == 3);
  CHECK(encoded_msg.at(44) == 3);
  CHECK(encoded_msg.at(45) == 0);
  CHECK(encoded_msg.at(46) == 0);
  CHECK(encoded_msg.at(47) == 4);
  CHECK(encoded_msg.at(48) == 4);
  CHECK(encoded_msg.at(49) == 0);
  CHECK(encoded_msg.at(50) == 0);
  CHECK(encoded_msg.at(51) == 4);
  CHECK(encoded_msg.at(52) == 2);
  CHECK(encoded_msg.at(53) == 0x20);
  CHECK(encoded_msg.at(54) == 0x22);
  CHECK(encoded_msg.at(55) == 0);
  CHECK(encoded_msg.at(56) == 0);
  CHECK(encoded_msg.at(57) == 0x20);
  CHECK(encoded_msg.at(58) == 0x11);
  CHECK(encoded_msg.at(59) == 0);
  CHECK(encoded_msg.at(60) == 0);
  CHECK(encoded_msg.at(61) == 4);
  CHECK(encoded_msg.at(62) == 0x20);
  CHECK(encoded_msg.at(63) == 0x22);
  CHECK(encoded_msg.at(64) == 0);
  CHECK(encoded_msg.at(65) == 0);
  CHECK(encoded_msg.at(66) == 0x20);
  CHECK(encoded_msg.at(67) == 0x11);
  CHECK(encoded_msg.at(68) == 0);
  CHECK(encoded_msg.at(69) == 0);
  CHECK(encoded_msg.at(70) == 0x20);
  CHECK(encoded_msg.at(71) == 0x22);
  CHECK(encoded_msg.at(72) == 0);
  CHECK(encoded_msg.at(73) == 0);
  CHECK(encoded_msg.at(74) == 0x20);
  CHECK(encoded_msg.at(75) == 0x11);
  CHECK(encoded_msg.at(76) == 0);
  CHECK(encoded_msg.at(77) == 0);
  CHECK(encoded_msg.at(78) == 0);
  CHECK(encoded_msg.at(79) == 1);
  CHECK(encoded_msg.at(80) == 0x20);
  CHECK(encoded_msg.at(81) == 0x11);
  CHECK(encoded_msg.at(82) == 0);
  CHECK(encoded_msg.at(83) == 0);
  CHECK(encoded_msg.at(84) == 0);
  CHECK(encoded_msg.at(85) == 0);
  CHECK(encoded_msg.at(86) == 0);
  CHECK(encoded_msg.at(87) == 0);
  CHECK(encoded_msg.at(88) == 0);
  CHECK(encoded_msg.at(89) == 0);
  CHECK(encoded_msg.at(90) == 0);
  CHECK(encoded_msg.at(91) == 0);
  
}

TEST_CASE("decoding with 1 soc, 4 TunerPath & 4 activeNBT, 4DFE & 4Receiver")
{
  GetResourceUsage_repl msg6ToDecode; //Arrange
  vector<uint8_t> encoded_msg{1,2,3,1,1,//MsgInfo
  1,4,//soc
  0x11,0x81,0x10,1,1,0,0,//path1+nbt1
  0x11,0x82,0x10,1,1,0,0,2,2,0,0,//path2+nbt1,2
  0x11,1,0x10,3,3,0,0,//path3+nbt3
  0x11,0x84,0x10,1,1,0,0,2,2,0,0,3,3,0,0,4,4,0,0,//path4+nbt1,2,3,4
  4,//Nrofdfes
  2,0x20,0x22,0,0,0x20,0x11,0,0,//dfe1+rec1,2
  4,0x20,0x22,0,0,0x20,0x11,0,0,0x20,0x22,0,0,0x20,0x11,0,0,//dfe2+rec1,2,3,4
  0,//dfe3
  1,0x20,0x11,0,0,//dfe4+rec4
  0,0,0,0,0,0,0,0};//rfa6,7
  
  msg6ToDecode.decode(encoded_msg); //Act
                                    
  CHECK(msg6ToDecode.getCookie() == 1); //Assert
  CHECK(msg6ToDecode.getReplyStatus() == 1);
  CHECK(msg6ToDecode.getNrOfSoCs() == 1); 
  CHECK(msg6ToDecode.socs.size() == 1);
  CHECK(msg6ToDecode.socs.at(0).getSoC_ID() == 1);
  CHECK(msg6ToDecode.socs.at(0).getNrOfTunerPaths() == 4);
  CHECK(msg6ToDecode.socs.at(0).getNrOfDFEs() == 4);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.size() == 4);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(0).getAntennaHandle() == 0x11);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(0).getActive() == 1);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(0).getActiveNBTs() == 1);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(0).getAntennaPort() == 1); 
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(0).nbts.size() == 1);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(0).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(0).nbts.at(0).getAssigned_DFE_ix() == 1);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(1).getAntennaHandle() == 0x11);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(1).getActive() == 1);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(1).getActiveNBTs() == 2);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(1).getAntennaPort() == 1);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(1).nbts.size() == 2);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(1).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(1).nbts.at(0).getAssigned_DFE_ix() == 1);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(1).nbts.at(1).getNBT_ix() == 2);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(1).nbts.at(1).getAssigned_DFE_ix() == 2);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(2).getAntennaHandle() == 0x11);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(2).getActive() == 0);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(2).getActiveNBTs() == 1);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(2).getAntennaPort() == 1);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(2).nbts.size() == 1);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(2).nbts.at(0).getNBT_ix() == 3);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(2).nbts.at(0).getAssigned_DFE_ix() == 3);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(3).getAntennaHandle() == 0x11);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(3).getActive() == 1);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(3).getActiveNBTs() == 4);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(3).getAntennaPort() == 1);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(3).nbts.size() == 4);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(3).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(3).nbts.at(0).getAssigned_DFE_ix() == 1);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(3).nbts.at(1).getNBT_ix() == 2);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(3).nbts.at(1).getAssigned_DFE_ix() == 2);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(3).nbts.at(2).getNBT_ix() == 3);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(3).nbts.at(2).getAssigned_DFE_ix() == 3);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(3).nbts.at(3).getNBT_ix() == 4);
  CHECK(msg6ToDecode.socs.at(0).tunerPaths.at(3).nbts.at(3).getAssigned_DFE_ix() == 4);
  CHECK(msg6ToDecode.socs.at(0).dfes.size() == 4);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(0).getNrOfAssignedReceivers() == 2);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.size() == 2);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(0).getBroadcastStandard() == 2);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(0).getMode() == 2);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(1).getMode() == 1);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(1).getNrOfAssignedReceivers() == 4);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.size() == 4);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(0).getBroadcastStandard() == 2);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(0).getMode() == 2);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(1).getMode() == 1);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(2).getReceiverHandle() == 0x20);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(2).getBroadcastStandard() == 2);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(2).getMode() == 2);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(3).getReceiverHandle() == 0x20);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(3).getBroadcastStandard() == 1);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(3).getMode() == 1);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(2).getNrOfAssignedReceivers() == 0);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.size() == 0);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(3).getNrOfAssignedReceivers() == 1);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.size() == 1);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.at(0).getBroadcastStandard() == 1);
  CHECK(msg6ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.at(0).getMode() == 1);
}

TEST_CASE("encoding with 4 soc, 4 TunerPath & 4 activeNBT, 4DFE & 4Receiver")
{
  GetResourceUsage_repl message7(1,1,0,4,0x0000);
  SoC soc1(0,1,4,4,0x0000);
  SoC soc2(0,1,0,1,0x0000);
  SoC soc3(0,1,1,1,0x0000);
  SoC soc4(0,1,1,4,0x0000);
  TunerPath path1(0x11,1,0,1,1,0);
  TunerPath path2(0x11,1,0,2,1,0);
  TunerPath path3(0x11,0,0,1,1,0);
  TunerPath path4(0x11,1,0,4,1,0);
  NBT nbt1(1,1,0x000);
  NBT nbt2(2,2,0x000);
  NBT nbt3(3,3,0x000);
  NBT nbt4(4,4,0x000);
  DFE dfe1(2);
  DFE dfe2(4);
  DFE dfe3(0);
  DFE dfe4(1);
  Receiver rec1(0x20,2,2,0x000);
  Receiver rec2(0x20,1,1,0x000);
  Receiver rec3(0x20,2,2,0x000);
  Receiver rec4(0x20,1,1,0x000);
  dfe1.addReceiverInstance(rec1);
  dfe1.addReceiverInstance(rec2);
  dfe2.addReceiverInstance(rec1);
  dfe2.addReceiverInstance(rec2);
  dfe2.addReceiverInstance(rec3);
  dfe2.addReceiverInstance(rec4);
  dfe4.addReceiverInstance(rec4);
  soc1.addDFEInstance(dfe1);
  soc1.addDFEInstance(dfe2);
  soc1.addDFEInstance(dfe3);
  soc1.addDFEInstance(dfe4);
  path1.addNBTInstance(nbt1);
  path2.addNBTInstance(nbt1);
  path2.addNBTInstance(nbt2);
  path3.addNBTInstance(nbt3);
  path4.addNBTInstance(nbt1);
  path4.addNBTInstance(nbt2);
  path4.addNBTInstance(nbt3);
  path4.addNBTInstance(nbt4);
  soc1.addtunerPathInstance(path1);
  soc1.addtunerPathInstance(path2);
  soc1.addtunerPathInstance(path3);
  soc1.addtunerPathInstance(path4);
  message7.addsocInstance(soc1);

  soc2.addDFEInstance(dfe1);
  message7.addsocInstance(soc2);

  soc3.addDFEInstance(dfe4);
  soc3.addtunerPathInstance(path2);
  message7.addsocInstance(soc3);


  soc4.addDFEInstance(dfe1);
  soc4.addDFEInstance(dfe2);
  soc4.addDFEInstance(dfe3);
  soc4.addDFEInstance(dfe4);
  soc4.addtunerPathInstance(path3);
  message7.addsocInstance(soc4);


  vector<uint8_t> encoded_msg = message7.encode();
  //CHECK(encoded_msg.at() == );
  REQUIRE(encoded_msg.size() == 177);
  CHECK(encoded_msg.at(0) == 1);
  CHECK(encoded_msg.at(1) == 0x02);
  CHECK(encoded_msg.at(2) == 0x03);
  CHECK(encoded_msg.at(3) == 1);
  CHECK(encoded_msg.at(4) == 4);
  CHECK(encoded_msg.at(5) == 1);
  CHECK(encoded_msg.at(6) == 4);
  CHECK(encoded_msg.at(7) == 0x11);
  CHECK((uint16_t)encoded_msg.at(8) == 0x81);
  CHECK(encoded_msg.at(9) == 0x10);
  CHECK(encoded_msg.at(10) == 1);
  CHECK(encoded_msg.at(11) == 1);
  CHECK(encoded_msg.at(12) == 0);
  CHECK(encoded_msg.at(13) == 0);
  CHECK(encoded_msg.at(14) == 0x11);
  CHECK((uint16_t)encoded_msg.at(15) == 0x82);
  CHECK(encoded_msg.at(16) == 0x10);
  CHECK(encoded_msg.at(17) == 1);
  CHECK(encoded_msg.at(18) == 1);
  CHECK(encoded_msg.at(19) == 0);
  CHECK(encoded_msg.at(20) == 0);
  CHECK(encoded_msg.at(21) == 2);
  CHECK(encoded_msg.at(22) == 2);
  CHECK(encoded_msg.at(23) == 0);
  CHECK(encoded_msg.at(24) == 0);
  CHECK(encoded_msg.at(25) == 0x11);
  CHECK(encoded_msg.at(26) == 1);
  CHECK(encoded_msg.at(27) == 0x10);
  CHECK(encoded_msg.at(28) == 3);
  CHECK(encoded_msg.at(29) == 3);
  CHECK(encoded_msg.at(30) == 0);
  CHECK(encoded_msg.at(31) == 0);
  CHECK(encoded_msg.at(32) == 0x11);
  CHECK((uint16_t)encoded_msg.at(33) == 0x84);
  CHECK(encoded_msg.at(34) == 0x10);
  CHECK(encoded_msg.at(35) == 1);
  CHECK(encoded_msg.at(36) == 1);
  CHECK(encoded_msg.at(37) == 0);
  CHECK(encoded_msg.at(38) == 0);
  CHECK(encoded_msg.at(39) == 2);
  CHECK(encoded_msg.at(40) == 2);
  CHECK(encoded_msg.at(41) == 0);
  CHECK(encoded_msg.at(42) == 0);
  CHECK(encoded_msg.at(43) == 3);
  CHECK(encoded_msg.at(44) == 3);
  CHECK(encoded_msg.at(45) == 0);
  CHECK(encoded_msg.at(46) == 0);
  CHECK(encoded_msg.at(47) == 4);
  CHECK(encoded_msg.at(48) == 4);
  CHECK(encoded_msg.at(49) == 0);
  CHECK(encoded_msg.at(50) == 0);
  CHECK(encoded_msg.at(51) == 4);
  CHECK(encoded_msg.at(52) == 2);
  CHECK(encoded_msg.at(53) == 0x20);
  CHECK(encoded_msg.at(54) == 0x22);
  CHECK(encoded_msg.at(55) == 0);
  CHECK(encoded_msg.at(56) == 0);
  CHECK(encoded_msg.at(57) == 0x20);
  CHECK(encoded_msg.at(58) == 0x11);
  CHECK(encoded_msg.at(59) == 0);
  CHECK(encoded_msg.at(60) == 0);
  CHECK(encoded_msg.at(61) == 4);
  CHECK(encoded_msg.at(62) == 0x20);
  CHECK(encoded_msg.at(63) == 0x22);
  CHECK(encoded_msg.at(64) == 0);
  CHECK(encoded_msg.at(65) == 0);
  CHECK(encoded_msg.at(66) == 0x20);
  CHECK(encoded_msg.at(67) == 0x11);
  CHECK(encoded_msg.at(68) == 0);
  CHECK(encoded_msg.at(69) == 0);
  CHECK(encoded_msg.at(70) == 0x20);
  CHECK(encoded_msg.at(71) == 0x22);
  CHECK(encoded_msg.at(72) == 0);
  CHECK(encoded_msg.at(73) == 0);
  CHECK(encoded_msg.at(74) == 0x20);
  CHECK(encoded_msg.at(75) == 0x11);
  CHECK(encoded_msg.at(76) == 0);
  CHECK(encoded_msg.at(77) == 0);
  CHECK(encoded_msg.at(78) == 0);
  CHECK(encoded_msg.at(79) == 1);
  CHECK(encoded_msg.at(80) == 0x20);
  CHECK(encoded_msg.at(81) == 0x11);
  CHECK(encoded_msg.at(82) == 0);
  CHECK(encoded_msg.at(83) == 0);
  CHECK(encoded_msg.at(84) == 0);
  CHECK(encoded_msg.at(85) == 0);
  CHECK(encoded_msg.at(86) == 0);
  CHECK(encoded_msg.at(87) == 0);
  CHECK(encoded_msg.at(88) == 1);
  CHECK(encoded_msg.at(89) == 0);
  CHECK(encoded_msg.at(90) == 1);
  CHECK(encoded_msg.at(91) == 2);
  CHECK(encoded_msg.at(92) == 0x20);
  CHECK(encoded_msg.at(93) == 0x22);
  CHECK(encoded_msg.at(94) == 0);
  CHECK(encoded_msg.at(95) == 0);
  CHECK(encoded_msg.at(96) == 0x20);
  CHECK(encoded_msg.at(97) == 0x11);
  CHECK(encoded_msg.at(98) == 0);
  CHECK(encoded_msg.at(99) == 0);
  CHECK(encoded_msg.at(100) == 0);
  CHECK(encoded_msg.at(101) == 0);
  CHECK(encoded_msg.at(102) == 0);
  CHECK(encoded_msg.at(103) == 0);
  CHECK(encoded_msg.at(104) == 1);
  CHECK(encoded_msg.at(105) == 1);
  CHECK(encoded_msg.at(106) == 0x11);
  CHECK(encoded_msg.at(107) == 0x82);
  CHECK(encoded_msg.at(108) == 0x10);
  CHECK(encoded_msg.at(109) == 1);
  CHECK(encoded_msg.at(110) == 1);
  CHECK(encoded_msg.at(111) == 0);
  CHECK(encoded_msg.at(112) == 0);
  CHECK(encoded_msg.at(113) == 2);
  CHECK(encoded_msg.at(114) == 2);
  CHECK(encoded_msg.at(115) == 0);
  CHECK(encoded_msg.at(116) == 0);
  CHECK(encoded_msg.at(117) == 1);
  CHECK(encoded_msg.at(118) == 1);
  CHECK(encoded_msg.at(119) == 0x20);
  CHECK(encoded_msg.at(120) == 0x11);
  CHECK(encoded_msg.at(121) == 0);
  CHECK(encoded_msg.at(122) == 0);
  CHECK(encoded_msg.at(123) == 0);
  CHECK(encoded_msg.at(124) == 0);
  CHECK(encoded_msg.at(125) == 0);
  CHECK(encoded_msg.at(126) == 0);
  CHECK(encoded_msg.at(127) == 1);
  CHECK(encoded_msg.at(128) == 1);
  CHECK(encoded_msg.at(129) == 0x11);
  CHECK(encoded_msg.at(130) == 0x01);
  CHECK(encoded_msg.at(131) == 0x10);
  CHECK(encoded_msg.at(132) == 3);
  CHECK(encoded_msg.at(133) == 3);
  CHECK(encoded_msg.at(134) == 0);
  CHECK(encoded_msg.at(135) == 0);
  CHECK(encoded_msg.at(136) == 4);
  CHECK(encoded_msg.at(137) == 2);
  CHECK(encoded_msg.at(138) == 0x20);
  CHECK(encoded_msg.at(139) == 0x22);
  CHECK(encoded_msg.at(140) == 0);
  CHECK(encoded_msg.at(141) == 0);
  CHECK(encoded_msg.at(142) == 0x20);
  CHECK(encoded_msg.at(143) == 0x11);
  CHECK(encoded_msg.at(144) == 0);
  CHECK(encoded_msg.at(145) == 0);
  CHECK(encoded_msg.at(146) == 4);
  CHECK(encoded_msg.at(147) == 0x20);
  CHECK(encoded_msg.at(148) == 0x22);
  CHECK(encoded_msg.at(149) == 0);
  CHECK(encoded_msg.at(150) == 0);
  CHECK(encoded_msg.at(151) == 0x20);
  CHECK(encoded_msg.at(152) == 0x11);
  CHECK(encoded_msg.at(153) == 0);
  CHECK(encoded_msg.at(154) == 0);
  CHECK(encoded_msg.at(155) == 0x20);
  CHECK(encoded_msg.at(156) == 0x22);
  CHECK(encoded_msg.at(157) == 0);
  CHECK(encoded_msg.at(158) == 0);
  CHECK(encoded_msg.at(159) == 0x20);
  CHECK(encoded_msg.at(160) == 0x11);
  CHECK(encoded_msg.at(161) == 0);
  CHECK(encoded_msg.at(162) == 0);
  CHECK(encoded_msg.at(163) == 0);
  CHECK(encoded_msg.at(164) == 1);
  CHECK(encoded_msg.at(165) == 0x20);
  CHECK(encoded_msg.at(166) == 0x11);
  CHECK(encoded_msg.at(167) == 0);
  CHECK(encoded_msg.at(168) == 0);
  CHECK(encoded_msg.at(169) == 0);
  CHECK(encoded_msg.at(170) == 0);
  CHECK(encoded_msg.at(171) == 0);
  CHECK(encoded_msg.at(172) == 0);
  CHECK(encoded_msg.at(173) == 0);
  CHECK(encoded_msg.at(174) == 0);
  CHECK(encoded_msg.at(175) == 0);
  CHECK(encoded_msg.at(176) == 0);
}
////////////////////////////////////////////////
TEST_CASE("decoding with 4 soc, 4 TunerPath & 4 activeNBT, 4DFE & 4Receiver")
{
  GetResourceUsage_repl msg7ToDecode;
  vector<uint8_t> encoded_msg{1,2,3,1,4,//MsgInfo
  1,4,//soc1
  0x11,0x81,0x10,1,1,0,0,//path1+nbt1
  0x11,0x82,0x10,1,1,0,0,2,2,0,0,//path2+nbt1,2
  0x11,1,0x10,3,3,0,0,//path3+nbt3
  0x11,0x84,0x10,1,1,0,0,2,2,0,0,3,3,0,0,4,4,0,0,//path4+nbt1,2,3,4
  4,//Nrofdfes
  2,0x20,0x22,0,0,0x20,0x11,0,0,//dfe1+rec1,2
  4,0x20,0x22,0,0,0x20,0x11,0,0,0x20,0x22,0,0,0x20,0x11,0,0,//dfe2+rec1,2,3,4
  0,//dfe3
  1,0x20,0x11,0,0,//dfe4+rec4
  0,0,0,0,//rfa6
  1,0,//soc2
  1,//NROFdfe
  2,//Assgnrec
  0x20,0x22,0,0,0x20,0x11,0,0,//rec1,2
  0,0,0,0,//rfa6
  1,1,//soc3
  0x11,0x82,0x10,1,1,0,0,2,2,0,0,//p2+nbt1,2
  1,//NROFdfe
  1,0x20,0x11,0,0,//dfe4+rec4
  0,0,0,0,//rfa6
  1,1,//soc4
  0x11,0x01,0x10,3,3,0,0,//p3+nbt3
  4,//NROFdfe
  2,0x20,0x22,0,0,0x20,0x11,0,0,//dfe1+rec1,2
  4,0x20,0x22,0,0,0x20,0x11,0,0,0x20,0x22,0,0,0x20,0x11,0,0,//dfe2+rec1,2,3,4
  0,//dfe3
  1,0x20,0x11,0,0,//dfe4+rec4
  0,0,0,0,0,0,0,0};//rfa6,7
  
  
  msg7ToDecode.decode(encoded_msg);
                                    
  CHECK(msg7ToDecode.getCookie() == 1);
  CHECK(msg7ToDecode.getReplyStatus() == 1);
  CHECK(msg7ToDecode.getNrOfSoCs() == 4); 
  CHECK(msg7ToDecode.socs.size() == 4);

  CHECK(msg7ToDecode.socs.at(0).getSoC_ID() == 1);
  CHECK(msg7ToDecode.socs.at(0).getNrOfTunerPaths() == 4);
  CHECK(msg7ToDecode.socs.at(0).getNrOfDFEs() == 4);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.size() == 4);
  CHECK(msg7ToDecode.socs.at(0).dfes.size() == 4);

  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(0).getAntennaHandle() == 0x11);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(0).getActive() == 1);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(0).getActiveNBTs() == 1);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(0).getAntennaPort() == 1); 
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(0).nbts.size() == 1);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(0).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(0).nbts.at(0).getAssigned_DFE_ix() == 1);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(1).getAntennaHandle() == 0x11);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(1).getActive() == 1);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(1).getActiveNBTs() == 2);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(1).getAntennaPort() == 1);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(1).nbts.size() == 2);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(1).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(1).nbts.at(0).getAssigned_DFE_ix() == 1);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(1).nbts.at(1).getNBT_ix() == 2);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(1).nbts.at(1).getAssigned_DFE_ix() == 2);

  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(2).getAntennaHandle() == 0x11);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(2).getActive() == 0);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(2).getActiveNBTs() == 1);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(2).getAntennaPort() == 1);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(2).nbts.size() == 1);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(2).nbts.at(0).getNBT_ix() == 3);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(2).nbts.at(0).getAssigned_DFE_ix() == 3);

  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(3).getAntennaHandle() == 0x11);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(3).getActive() == 1);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(3).getActiveNBTs() == 4);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(3).getAntennaPort() == 1);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(3).nbts.size() == 4);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(3).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(3).nbts.at(0).getAssigned_DFE_ix() == 1);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(3).nbts.at(1).getNBT_ix() == 2);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(3).nbts.at(1).getAssigned_DFE_ix() == 2);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(3).nbts.at(2).getNBT_ix() == 3);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(3).nbts.at(2).getAssigned_DFE_ix() == 3);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(3).nbts.at(3).getNBT_ix() == 4);
  CHECK(msg7ToDecode.socs.at(0).tunerPaths.at(3).nbts.at(3).getAssigned_DFE_ix() == 4);

  CHECK(msg7ToDecode.socs.at(0).dfes.at(0).getNrOfAssignedReceivers() == 2);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.size() == 2);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(0).getBroadcastStandard() == 2);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(0).getMode() == 2);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(1).getMode() == 1);

  CHECK(msg7ToDecode.socs.at(0).dfes.at(1).getNrOfAssignedReceivers() == 4);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.size() == 4);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(0).getBroadcastStandard() == 2);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(0).getMode() == 2);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(1).getMode() == 1);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(2).getReceiverHandle() == 0x20);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(2).getBroadcastStandard() == 2);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(2).getMode() == 2);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(3).getReceiverHandle() == 0x20);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(3).getBroadcastStandard() == 1);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(3).getMode() == 1);

  CHECK(msg7ToDecode.socs.at(0).dfes.at(2).getNrOfAssignedReceivers() == 0);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.size() == 0);

  CHECK(msg7ToDecode.socs.at(0).dfes.at(3).getNrOfAssignedReceivers() == 1);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.size() == 1);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.at(0).getBroadcastStandard() == 1);
  CHECK(msg7ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.at(0).getMode() == 1);

  CHECK(msg7ToDecode.socs.at(1).getSoC_ID() == 1);
  CHECK(msg7ToDecode.socs.at(1).getNrOfTunerPaths() == 0);
  CHECK(msg7ToDecode.socs.at(1).getNrOfDFEs() == 1);
  CHECK(msg7ToDecode.socs.at(1).tunerPaths.size() == 0);
  CHECK(msg7ToDecode.socs.at(1).dfes.size() == 1);
  CHECK(msg7ToDecode.socs.at(1).dfes.at(0).getNrOfAssignedReceivers() == 2);
  CHECK(msg7ToDecode.socs.at(1).dfes.at(0).AssignedReceivers.size() == 2);
  CHECK(msg7ToDecode.socs.at(1).dfes.at(0).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg7ToDecode.socs.at(1).dfes.at(0).AssignedReceivers.at(0).getBroadcastStandard() == 2);
  CHECK(msg7ToDecode.socs.at(1).dfes.at(0).AssignedReceivers.at(0).getMode() == 2);
  CHECK(msg7ToDecode.socs.at(1).dfes.at(0).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg7ToDecode.socs.at(1).dfes.at(0).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg7ToDecode.socs.at(1).dfes.at(0).AssignedReceivers.at(1).getMode() == 1);
  
  CHECK(msg7ToDecode.socs.at(2).getSoC_ID() == 1);
  CHECK(msg7ToDecode.socs.at(2).getNrOfTunerPaths() == 1);
  CHECK(msg7ToDecode.socs.at(2).getNrOfDFEs() == 1);
  CHECK(msg7ToDecode.socs.at(2).tunerPaths.size() == 1);
  CHECK(msg7ToDecode.socs.at(2).dfes.size() == 1);

  CHECK(msg7ToDecode.socs.at(2).tunerPaths.at(0).getAntennaHandle() == 0x11);
  CHECK(msg7ToDecode.socs.at(2).tunerPaths.at(0).getActive() == 1);
  CHECK(msg7ToDecode.socs.at(2).tunerPaths.at(0).getActiveNBTs() == 2);
  CHECK(msg7ToDecode.socs.at(2).tunerPaths.at(0).getAntennaPort() == 1); 
  CHECK(msg7ToDecode.socs.at(2).tunerPaths.at(0).nbts.size() == 2);
  CHECK(msg7ToDecode.socs.at(2).tunerPaths.at(0).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg7ToDecode.socs.at(2).tunerPaths.at(0).nbts.at(0).getAssigned_DFE_ix() == 1);
  CHECK(msg7ToDecode.socs.at(2).tunerPaths.at(0).nbts.at(1).getNBT_ix() == 2);
  CHECK(msg7ToDecode.socs.at(2).tunerPaths.at(0).nbts.at(1).getAssigned_DFE_ix() == 2);

  CHECK(msg7ToDecode.socs.at(2).dfes.at(0).getNrOfAssignedReceivers() == 1);
  CHECK(msg7ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.size() == 1);
  CHECK(msg7ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg7ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(0).getBroadcastStandard() == 1);
  CHECK(msg7ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(0).getMode() == 1);

  CHECK(msg7ToDecode.socs.at(3).getSoC_ID() == 1);
  CHECK(msg7ToDecode.socs.at(3).getNrOfTunerPaths() == 1);
  CHECK(msg7ToDecode.socs.at(3).getNrOfDFEs() == 4);
  CHECK(msg7ToDecode.socs.at(3).tunerPaths.size() == 1);
  CHECK(msg7ToDecode.socs.at(3).dfes.size() == 4);

  CHECK(msg7ToDecode.socs.at(3).tunerPaths.at(0).getAntennaHandle() == 0x11);
  CHECK(msg7ToDecode.socs.at(3).tunerPaths.at(0).getActive() == 0);
  CHECK(msg7ToDecode.socs.at(3).tunerPaths.at(0).getActiveNBTs() == 1);
  CHECK(msg7ToDecode.socs.at(3).tunerPaths.at(0).getAntennaPort() == 1); 
  CHECK(msg7ToDecode.socs.at(3).tunerPaths.at(0).nbts.size() == 1);
  CHECK(msg7ToDecode.socs.at(3).tunerPaths.at(0).nbts.at(0).getNBT_ix() == 3);
  CHECK(msg7ToDecode.socs.at(3).tunerPaths.at(0).nbts.at(0).getAssigned_DFE_ix() == 3);

  CHECK(msg7ToDecode.socs.at(3).dfes.at(0).getNrOfAssignedReceivers() == 2);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(0).AssignedReceivers.size() == 2);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(0).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(0).AssignedReceivers.at(0).getBroadcastStandard() == 2);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(0).AssignedReceivers.at(0).getMode() == 2);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(0).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(0).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(0).AssignedReceivers.at(1).getMode() == 1);

  CHECK(msg7ToDecode.socs.at(3).dfes.at(1).getNrOfAssignedReceivers() == 4);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(1).AssignedReceivers.size() == 4);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(1).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(1).AssignedReceivers.at(0).getBroadcastStandard() == 2);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(1).AssignedReceivers.at(0).getMode() == 2);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(1).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(1).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(1).AssignedReceivers.at(1).getMode() == 1);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(1).AssignedReceivers.at(2).getReceiverHandle() == 0x20);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(1).AssignedReceivers.at(2).getBroadcastStandard() == 2);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(1).AssignedReceivers.at(2).getMode() == 2);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(1).AssignedReceivers.at(3).getReceiverHandle() == 0x20);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(1).AssignedReceivers.at(3).getBroadcastStandard() == 1);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(1).AssignedReceivers.at(3).getMode() == 1);

  CHECK(msg7ToDecode.socs.at(3).dfes.at(2).getNrOfAssignedReceivers() == 0);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(2).AssignedReceivers.size() == 0);

  CHECK(msg7ToDecode.socs.at(3).dfes.at(3).getNrOfAssignedReceivers() == 1);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(3).AssignedReceivers.size() == 1);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(3).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(3).AssignedReceivers.at(0).getBroadcastStandard() == 1);
  CHECK(msg7ToDecode.socs.at(3).dfes.at(3).AssignedReceivers.at(0).getMode() == 1);
}

TEST_CASE("encoding with 4SoCs, 8TunerPaths, 5activeNBTs, 8 DFEs and 8 Receivers")
{
  GetResourceUsage_repl message8(1,1,0,4,0);
  SoC soc1(0,1,0,8,0);
  SoC soc2(0,2,8,0,0);
  SoC soc3(0,3,8,8,0);
  SoC soc4(0,4,0,0,0);
  TunerPath path1(0x11,1,0,1,1,0);
  TunerPath path2(0x11,1,0,2,2,0);
  TunerPath path3(0x11,1,0,3,3,0);
  TunerPath path4(0x11,1,0,4,4,0);
  TunerPath path5(0x11,1,0,5,5,0);
  TunerPath path6(0x11,1,0,5,6,0);
  TunerPath path7(0x11,1,0,0,7,0);
  TunerPath path8(0x11,0,0,0,8,0);
  NBT nbt1(1,1,0);
  NBT nbt2(2,2,0);
  NBT nbt3(3,3,0);  
  NBT nbt4(4,4,0);
  NBT nbt5(5,5,0);
  DFE dfe1(8);
  DFE dfe2(7);
  DFE dfe3(6);
  DFE dfe4(4);
  DFE dfe5(3);
  DFE dfe6(2);
  DFE dfe7(1);
  DFE dfe8(0);
  Receiver rec1(0x20,0,0,0);
  Receiver rec2(0x20,1,1,0);
  Receiver rec3(0x20,2,2,0);
  Receiver rec4(0x20,3,3,0);
  Receiver rec5(0x20,4,4,0);
  Receiver rec6(0x20,5,5,0);
  Receiver rec7(0x20,6,6,0);
  Receiver rec8(0x20,7,7,0);
  
  dfe1.addReceiverInstance(rec1);
  dfe1.addReceiverInstance(rec2);
  dfe1.addReceiverInstance(rec3);
  dfe1.addReceiverInstance(rec4);
  dfe1.addReceiverInstance(rec5);
  dfe1.addReceiverInstance(rec6);
  dfe1.addReceiverInstance(rec7);
  dfe1.addReceiverInstance(rec8);
  dfe2.addReceiverInstance(rec1);
  dfe2.addReceiverInstance(rec2);
  dfe2.addReceiverInstance(rec3);
  dfe2.addReceiverInstance(rec4);
  dfe2.addReceiverInstance(rec5);
  dfe2.addReceiverInstance(rec6);
  dfe2.addReceiverInstance(rec7);
  dfe3.addReceiverInstance(rec1);
  dfe3.addReceiverInstance(rec2);
  dfe3.addReceiverInstance(rec3);
  dfe3.addReceiverInstance(rec4);
  dfe3.addReceiverInstance(rec5);
  dfe3.addReceiverInstance(rec6);
  dfe4.addReceiverInstance(rec1);
  dfe4.addReceiverInstance(rec2);
  dfe4.addReceiverInstance(rec3);
  dfe4.addReceiverInstance(rec4);
  dfe5.addReceiverInstance(rec1);
  dfe5.addReceiverInstance(rec2);
  dfe5.addReceiverInstance(rec3);
  dfe6.addReceiverInstance(rec1);
  dfe6.addReceiverInstance(rec2);
  dfe7.addReceiverInstance(rec1);
  path1.addNBTInstance(nbt1);
  path2.addNBTInstance(nbt1);
  path2.addNBTInstance(nbt2);
  path3.addNBTInstance(nbt1);
  path3.addNBTInstance(nbt2);
  path3.addNBTInstance(nbt3);
  path4.addNBTInstance(nbt1);
  path4.addNBTInstance(nbt2);
  path4.addNBTInstance(nbt3);
  path4.addNBTInstance(nbt4);
  path5.addNBTInstance(nbt1);
  path5.addNBTInstance(nbt2);
  path5.addNBTInstance(nbt3);
  path5.addNBTInstance(nbt4);
  path5.addNBTInstance(nbt5);
  path6.addNBTInstance(nbt1);
  path6.addNBTInstance(nbt2);
  path6.addNBTInstance(nbt3);
  path6.addNBTInstance(nbt4);
  path6.addNBTInstance(nbt5);

  soc1.addDFEInstance(dfe1);
  soc1.addDFEInstance(dfe2);
  soc1.addDFEInstance(dfe3);
  soc1.addDFEInstance(dfe4);
  soc1.addDFEInstance(dfe5);
  soc1.addDFEInstance(dfe6);
  soc1.addDFEInstance(dfe7);
  soc1.addDFEInstance(dfe8);

  soc2.addtunerPathInstance(path1);
  soc2.addtunerPathInstance(path2);
  soc2.addtunerPathInstance(path3);
  soc2.addtunerPathInstance(path4);
  soc2.addtunerPathInstance(path5);
  soc2.addtunerPathInstance(path6);
  soc2.addtunerPathInstance(path7);
  soc2.addtunerPathInstance(path8);

  soc3.addtunerPathInstance(path1);
  soc3.addtunerPathInstance(path2);
  soc3.addtunerPathInstance(path3);
  soc3.addtunerPathInstance(path4);
  soc3.addtunerPathInstance(path5);
  soc3.addtunerPathInstance(path6);
  soc3.addtunerPathInstance(path7);
  soc3.addtunerPathInstance(path8);
  soc3.addDFEInstance(dfe1);
  soc3.addDFEInstance(dfe2);
  soc3.addDFEInstance(dfe3);
  soc3.addDFEInstance(dfe4);
  soc3.addDFEInstance(dfe5);
  soc3.addDFEInstance(dfe6);
  soc3.addDFEInstance(dfe7);
  soc3.addDFEInstance(dfe8);

  message8.addsocInstance(soc1);
  message8.addsocInstance(soc2);
  message8.addsocInstance(soc3);
  message8.addsocInstance(soc4);

  vector<uint8_t> encoded_msg = message8.encode();
  REQUIRE(encoded_msg.size() == 509);
  CHECK(encoded_msg.at(0) == 1);
  CHECK(encoded_msg.at(1) == 2);
  CHECK(encoded_msg.at(2) == 3);
  CHECK(encoded_msg.at(3) == 1);
  CHECK(encoded_msg.at(4) == 4);
  CHECK(encoded_msg.at(5) == 01);
  CHECK(encoded_msg.at(6) == 0);
  CHECK(encoded_msg.at(7) == 8);
  CHECK(encoded_msg.at(8) == 8);
  CHECK(encoded_msg.at(9) == 0x20);
  CHECK(encoded_msg.at(10) == 00);
  CHECK(encoded_msg.at(11) == 0);
  CHECK(encoded_msg.at(12) == 0);
  CHECK(encoded_msg.at(13) == 0x20);
  CHECK(encoded_msg.at(14) == 0x11);
  CHECK(encoded_msg.at(15) == 0);
  CHECK(encoded_msg.at(16) == 0);
  CHECK(encoded_msg.at(17) == 0x20);
  CHECK(encoded_msg.at(18) == 0x22);
  CHECK(encoded_msg.at(19) == 0);
  CHECK(encoded_msg.at(20) == 0);
  CHECK(encoded_msg.at(21) == 0x20);
  CHECK(encoded_msg.at(22) == 0x33);
  CHECK(encoded_msg.at(23) == 0);
  CHECK(encoded_msg.at(24) == 0);
  CHECK(encoded_msg.at(25) == 0x20);
  CHECK(encoded_msg.at(26) == 0x44);
  CHECK(encoded_msg.at(27) == 0);
  CHECK(encoded_msg.at(28) == 0);
  CHECK(encoded_msg.at(29) == 0x20);
  CHECK(encoded_msg.at(30) == 0x55);
  CHECK(encoded_msg.at(31) == 0);
  CHECK(encoded_msg.at(32) == 0);
  CHECK(encoded_msg.at(33) == 0x20);
  CHECK(encoded_msg.at(34) == 0x66);
  CHECK(encoded_msg.at(35) == 0);
  CHECK(encoded_msg.at(36) == 0);
  CHECK(encoded_msg.at(37) == 0x20);
  CHECK(encoded_msg.at(38) == 0x77);
  CHECK(encoded_msg.at(39) == 0);
  CHECK(encoded_msg.at(40) == 0);
  CHECK(encoded_msg.at(41) == 7);
  CHECK(encoded_msg.at(42) == 0x20);
  CHECK(encoded_msg.at(43) == 0x00);
  CHECK(encoded_msg.at(44) == 0);
  CHECK(encoded_msg.at(45) == 0);
  CHECK(encoded_msg.at(46) == 0x20);
  CHECK(encoded_msg.at(47) == 0x11);
  CHECK(encoded_msg.at(48) == 0);
  CHECK(encoded_msg.at(49) == 0);
  CHECK(encoded_msg.at(50) == 0x20);
  CHECK(encoded_msg.at(51) == 0x22);
  CHECK(encoded_msg.at(52) == 0);
  CHECK(encoded_msg.at(53) == 0);
  CHECK(encoded_msg.at(54) == 0x20);
  CHECK(encoded_msg.at(55) == 0x33);
  CHECK(encoded_msg.at(56) == 0);
  CHECK(encoded_msg.at(57) == 0);
  CHECK(encoded_msg.at(58) == 0x20);
  CHECK(encoded_msg.at(59) == 0x44);
  CHECK(encoded_msg.at(60) == 0);
  CHECK(encoded_msg.at(61) == 0);
  CHECK(encoded_msg.at(62) == 0x20);
  CHECK(encoded_msg.at(63) == 0x55);
  CHECK(encoded_msg.at(64) == 0);
  CHECK(encoded_msg.at(65) == 0);
  CHECK(encoded_msg.at(66) == 0x20);
  CHECK(encoded_msg.at(67) == 0x66);
  CHECK(encoded_msg.at(68) == 0);
  CHECK(encoded_msg.at(69) == 0);
  CHECK(encoded_msg.at(70) == 6);
  CHECK(encoded_msg.at(71) == 0x20);
  CHECK(encoded_msg.at(72) == 0);
  CHECK(encoded_msg.at(73) == 0);
  CHECK(encoded_msg.at(74) == 0);
  CHECK(encoded_msg.at(75) == 0x20);
  CHECK(encoded_msg.at(76) == 0x11);
  CHECK(encoded_msg.at(77) == 0);
  CHECK(encoded_msg.at(78) == 0);
  CHECK(encoded_msg.at(79) == 0x20);
  CHECK(encoded_msg.at(80) == 0x22);
  CHECK(encoded_msg.at(81) == 0);
  CHECK(encoded_msg.at(82) == 0);
  CHECK(encoded_msg.at(83) == 0x20);
  CHECK(encoded_msg.at(84) == 0x33);
  CHECK(encoded_msg.at(85) == 0);
  CHECK(encoded_msg.at(86) == 0);
  CHECK(encoded_msg.at(87) == 0x20);
  CHECK(encoded_msg.at(88) == 0x44);
  CHECK(encoded_msg.at(89) == 0);  
  CHECK(encoded_msg.at(90) == 0);
  CHECK(encoded_msg.at(91) == 0x20);
  CHECK(encoded_msg.at(92) == 0x55);
  CHECK(encoded_msg.at(93) == 0);
  CHECK(encoded_msg.at(94) == 0);
  CHECK(encoded_msg.at(95) == 4);
  CHECK(encoded_msg.at(96) == 0x20);
  CHECK(encoded_msg.at(97) == 0x00);
  CHECK(encoded_msg.at(98) == 0);
  CHECK(encoded_msg.at(99) == 0);
  CHECK(encoded_msg.at(100) == 0x20);
  CHECK(encoded_msg.at(101) == 0x11);
  CHECK(encoded_msg.at(102) == 0);
  CHECK(encoded_msg.at(103) == 0);
  CHECK(encoded_msg.at(104) == 0x20);
  CHECK(encoded_msg.at(105) == 0x22);
  CHECK(encoded_msg.at(106) == 0);
  CHECK(encoded_msg.at(107) == 0);
  CHECK(encoded_msg.at(108) == 0x20);
  CHECK(encoded_msg.at(109) == 0x33);
  CHECK(encoded_msg.at(110) == 0);
  CHECK(encoded_msg.at(111) == 0);
  CHECK(encoded_msg.at(112) == 3);
  CHECK(encoded_msg.at(113) == 0x20);
  CHECK(encoded_msg.at(114) == 0);
  CHECK(encoded_msg.at(115) == 0);
  CHECK(encoded_msg.at(116) == 0);
  CHECK(encoded_msg.at(117) == 0x20);
  CHECK(encoded_msg.at(118) == 0x11);
  CHECK(encoded_msg.at(119) == 0);
  CHECK(encoded_msg.at(120) == 0);
  CHECK(encoded_msg.at(121) == 0x20);
  CHECK(encoded_msg.at(122) == 0x22);
  CHECK(encoded_msg.at(123) == 0);
  CHECK(encoded_msg.at(124) == 0);
  CHECK(encoded_msg.at(125) == 2);
  CHECK(encoded_msg.at(126) == 0x20);
  CHECK(encoded_msg.at(127) == 0);
  CHECK(encoded_msg.at(128) == 0);
  CHECK(encoded_msg.at(129) == 0);
  CHECK(encoded_msg.at(130) == 0x20);
  CHECK(encoded_msg.at(131) == 0x11);
  CHECK(encoded_msg.at(132) == 0);
  CHECK(encoded_msg.at(133) == 0);
  CHECK(encoded_msg.at(134) == 1);
  CHECK(encoded_msg.at(135) == 0x20);
  CHECK(encoded_msg.at(136) == 0);
  CHECK(encoded_msg.at(137) == 0);
  CHECK(encoded_msg.at(138) == 0);
  CHECK(encoded_msg.at(139) == 0);
  CHECK(encoded_msg.at(140) == 0);
  CHECK(encoded_msg.at(141) == 0);
  CHECK(encoded_msg.at(142) == 0);
  CHECK(encoded_msg.at(143) == 0);
  CHECK(encoded_msg.at(144) == 2);
  CHECK(encoded_msg.at(145) == 8);
  CHECK(encoded_msg.at(146) == 0x11);
  CHECK(encoded_msg.at(147) == 0x81);
  CHECK(encoded_msg.at(148) == 0x10);
  CHECK(encoded_msg.at(149) == 1);
  CHECK(encoded_msg.at(150) == 1);
  CHECK(encoded_msg.at(151) == 0);
  CHECK(encoded_msg.at(152) == 0);
  CHECK(encoded_msg.at(153) == 0x11);
  CHECK(encoded_msg.at(154) == 0x82);
  CHECK(encoded_msg.at(155) == 0x20);
  CHECK(encoded_msg.at(156) == 1);
  CHECK(encoded_msg.at(157) == 1);
  CHECK(encoded_msg.at(158) == 0);
  CHECK(encoded_msg.at(159) == 0);
  CHECK(encoded_msg.at(160) == 2);
  CHECK(encoded_msg.at(161) == 2);
  CHECK(encoded_msg.at(162) == 0);
  CHECK(encoded_msg.at(163) == 0);
  CHECK(encoded_msg.at(164) == 0x11);
  CHECK(encoded_msg.at(165) == 0x83);
  CHECK(encoded_msg.at(166) == 0x30);
  CHECK(encoded_msg.at(167) == 1);
  CHECK(encoded_msg.at(168) == 1);
  CHECK(encoded_msg.at(169) == 0);
  CHECK(encoded_msg.at(170) == 0);
  CHECK(encoded_msg.at(171) == 2);
  CHECK(encoded_msg.at(172) == 2);
  CHECK(encoded_msg.at(173) == 0);
  CHECK(encoded_msg.at(174) == 0);
  CHECK(encoded_msg.at(175) == 3);
  CHECK(encoded_msg.at(176) == 3);
  CHECK(encoded_msg.at(177) == 0);
  CHECK(encoded_msg.at(178) == 0);
  CHECK(encoded_msg.at(179) == 0x11);
  CHECK(encoded_msg.at(180) == 0x84);
  CHECK(encoded_msg.at(181) == 0x40);
  CHECK(encoded_msg.at(182) == 1);
  CHECK(encoded_msg.at(183) == 1);
  CHECK(encoded_msg.at(184) == 0);
  CHECK(encoded_msg.at(185) == 0);
  CHECK(encoded_msg.at(186) == 2);
  CHECK(encoded_msg.at(187) == 2);
  CHECK(encoded_msg.at(188) == 0);
  CHECK(encoded_msg.at(189) == 0);
  CHECK(encoded_msg.at(190) == 3);
  CHECK(encoded_msg.at(191) == 3);
  CHECK(encoded_msg.at(192) == 0);
  CHECK(encoded_msg.at(193) == 0);
  CHECK(encoded_msg.at(194) == 4);
  CHECK(encoded_msg.at(195) == 4);
  CHECK(encoded_msg.at(196) == 0);
  CHECK(encoded_msg.at(197) == 0);
  CHECK(encoded_msg.at(198) == 0x11);
  CHECK(encoded_msg.at(199) == 0x85);
  CHECK(encoded_msg.at(200) == 0x50);
  CHECK(encoded_msg.at(201) == 1);
  CHECK(encoded_msg.at(202) == 1);
  CHECK(encoded_msg.at(203) == 0);
  CHECK(encoded_msg.at(204) == 0);
  CHECK(encoded_msg.at(205) == 2);
  CHECK(encoded_msg.at(206) == 2);
  CHECK(encoded_msg.at(207) == 0);
  CHECK(encoded_msg.at(208) == 0);
  CHECK(encoded_msg.at(209) == 3);
  CHECK(encoded_msg.at(210) == 3);
  CHECK(encoded_msg.at(211) == 0);
  CHECK(encoded_msg.at(212) == 0);
  CHECK(encoded_msg.at(213) == 4);
  CHECK(encoded_msg.at(214) == 4);
  CHECK(encoded_msg.at(215) == 0);
  CHECK(encoded_msg.at(216) == 0);
  CHECK(encoded_msg.at(217) == 5);
  CHECK(encoded_msg.at(218) == 5);
  CHECK(encoded_msg.at(219) == 0);
  CHECK(encoded_msg.at(220) == 0);
  CHECK(encoded_msg.at(221) == 0x11);
  CHECK((uint16_t)encoded_msg.at(222) == 0x85);
  CHECK(encoded_msg.at(223) == 0x60);
  CHECK(encoded_msg.at(224) == 1);
  CHECK(encoded_msg.at(225) == 1);
  CHECK(encoded_msg.at(226) == 0);
  CHECK(encoded_msg.at(227) == 0);
  CHECK(encoded_msg.at(228) == 2);
  CHECK(encoded_msg.at(229) == 2);
  CHECK(encoded_msg.at(230) == 0);
  CHECK(encoded_msg.at(231) == 0);
  CHECK(encoded_msg.at(232) == 3);
  CHECK(encoded_msg.at(233) == 3);
  CHECK(encoded_msg.at(234) == 0);
  CHECK(encoded_msg.at(235) == 0);
  CHECK(encoded_msg.at(236) == 4);
  CHECK(encoded_msg.at(237) == 4);
  CHECK(encoded_msg.at(238) == 0);
  CHECK(encoded_msg.at(239) == 0);
  CHECK(encoded_msg.at(240) == 5);
  CHECK(encoded_msg.at(241) == 5);
  CHECK(encoded_msg.at(242) == 0);
  CHECK(encoded_msg.at(243) == 0);
  CHECK(encoded_msg.at(244) == 0x11);
  CHECK(encoded_msg.at(245) == 0x80);
  CHECK(encoded_msg.at(246) == 0x70);
  CHECK(encoded_msg.at(247) == 0x11);
  CHECK((uint16_t)encoded_msg.at(248) == 0);
  CHECK(encoded_msg.at(249) == 0x80);
  CHECK(encoded_msg.at(250) == 0);
  CHECK(encoded_msg.at(251) == 0);
  CHECK(encoded_msg.at(252) == 0);
  CHECK(encoded_msg.at(253) == 0);
  CHECK(encoded_msg.at(254) == 0);
  CHECK(encoded_msg.at(255) == 03);
  CHECK(encoded_msg.at(256) == 8);
  CHECK(encoded_msg.at(257) == 0x11);
  CHECK(encoded_msg.at(258) == 0x81);
  CHECK(encoded_msg.at(259) == 0x10);
  CHECK(encoded_msg.at(260) == 1);
  CHECK(encoded_msg.at(261) == 1);
  CHECK(encoded_msg.at(262) == 0);
  CHECK(encoded_msg.at(263) == 0);
  CHECK(encoded_msg.at(264) == 0x11);
  CHECK(encoded_msg.at(265) == 0x82);
  CHECK(encoded_msg.at(266) == 0x20);
  CHECK(encoded_msg.at(267) == 1);
  CHECK(encoded_msg.at(268) == 1);
  CHECK(encoded_msg.at(269) == 0);
  CHECK(encoded_msg.at(270) == 0);
  CHECK(encoded_msg.at(271) == 2);
  CHECK(encoded_msg.at(272) == 2);
  CHECK(encoded_msg.at(273) == 0);
  CHECK(encoded_msg.at(274) == 0);
  CHECK(encoded_msg.at(275) == 0x11);
  CHECK(encoded_msg.at(276) == 0x83);
  CHECK(encoded_msg.at(277) == 0x30);
  CHECK(encoded_msg.at(278) == 1);
  CHECK(encoded_msg.at(279) == 1);
  CHECK(encoded_msg.at(280) == 0);
  CHECK(encoded_msg.at(281) == 0);
  CHECK(encoded_msg.at(282) == 2);
  CHECK(encoded_msg.at(283) == 2);
  CHECK(encoded_msg.at(284) == 0);
  CHECK(encoded_msg.at(285) == 0);
  CHECK(encoded_msg.at(286) == 3);
  CHECK(encoded_msg.at(287) == 3);
  CHECK(encoded_msg.at(288) == 0);
  CHECK(encoded_msg.at(289) == 0);
  CHECK(encoded_msg.at(290) == 0x11);
  CHECK(encoded_msg.at(291) == 0x84);
  CHECK(encoded_msg.at(292) == 0x40);
  CHECK(encoded_msg.at(293) == 1);
  CHECK(encoded_msg.at(294) == 1);
  CHECK(encoded_msg.at(295) == 0);
  CHECK(encoded_msg.at(296) == 0);
  CHECK(encoded_msg.at(297) == 2);
  CHECK(encoded_msg.at(298) == 2);
  CHECK(encoded_msg.at(299) == 0);
  CHECK(encoded_msg.at(300) == 0);
  CHECK(encoded_msg.at(301) == 3);
  CHECK(encoded_msg.at(302) == 3);
  CHECK(encoded_msg.at(303) == 0);
  CHECK(encoded_msg.at(304) == 0);
  CHECK(encoded_msg.at(305) == 4);
  CHECK(encoded_msg.at(306) == 4);
  CHECK(encoded_msg.at(307) == 0);
  CHECK(encoded_msg.at(308) == 0);
  CHECK(encoded_msg.at(309) == 0x11);
  CHECK(encoded_msg.at(310) == 0x85);
  CHECK(encoded_msg.at(311) == 0x50);
  CHECK(encoded_msg.at(312) == 1);
  CHECK(encoded_msg.at(313) == 1);
  CHECK(encoded_msg.at(314) == 0);
  CHECK(encoded_msg.at(315) == 0);
  CHECK(encoded_msg.at(316) == 2);
  CHECK(encoded_msg.at(317) == 2);
  CHECK(encoded_msg.at(318) == 0);
  CHECK(encoded_msg.at(319) == 0);
  CHECK(encoded_msg.at(320) == 3);
  CHECK(encoded_msg.at(321) == 3);
  CHECK(encoded_msg.at(322) == 0);
  CHECK(encoded_msg.at(323) == 0);
  CHECK(encoded_msg.at(324) == 4);
  CHECK(encoded_msg.at(325) == 4);
  CHECK(encoded_msg.at(326) == 0);
  CHECK(encoded_msg.at(327) == 0);
  CHECK(encoded_msg.at(328) == 5);
  CHECK(encoded_msg.at(329) == 5);
  CHECK(encoded_msg.at(330) == 0);
  CHECK(encoded_msg.at(331) == 0);
  CHECK(encoded_msg.at(332) == 0x11);
  CHECK(encoded_msg.at(333) == 0x85);
  CHECK(encoded_msg.at(334) == 0x60);
  CHECK(encoded_msg.at(335) == 1);
  CHECK(encoded_msg.at(336) == 1);
  CHECK(encoded_msg.at(337) == 0);
  CHECK(encoded_msg.at(338) == 0);
  CHECK(encoded_msg.at(339) == 2);
  CHECK(encoded_msg.at(340) == 2);
  CHECK(encoded_msg.at(341) == 0);
  CHECK(encoded_msg.at(342) == 0);
  CHECK(encoded_msg.at(343) == 3);
  CHECK(encoded_msg.at(344) == 3);
  CHECK(encoded_msg.at(345) == 0);
  CHECK(encoded_msg.at(346) == 0);
  CHECK(encoded_msg.at(347) == 4);
  CHECK(encoded_msg.at(348) == 4);
  CHECK(encoded_msg.at(349) == 0);
  CHECK(encoded_msg.at(350) == 0);
  CHECK(encoded_msg.at(351) == 5);
  CHECK(encoded_msg.at(352) == 5);
  CHECK(encoded_msg.at(353) == 0);
  CHECK(encoded_msg.at(354) == 0);
  CHECK(encoded_msg.at(355) == 0x11);
  CHECK(encoded_msg.at(356) == 0x80);
  CHECK(encoded_msg.at(357) == 0x70);
  CHECK(encoded_msg.at(358) == 0x11);
  CHECK(encoded_msg.at(359) == 0);
  CHECK(encoded_msg.at(360) == 0x80);
  CHECK(encoded_msg.at(361) == 8);
  CHECK(encoded_msg.at(362) == 8);
  CHECK(encoded_msg.at(363) == 0x20);
  CHECK(encoded_msg.at(364) == 0);
  CHECK(encoded_msg.at(365) == 0);
  CHECK(encoded_msg.at(366) == 0);
  CHECK(encoded_msg.at(367) == 0x20);
  CHECK(encoded_msg.at(368) == 0x11);
  CHECK(encoded_msg.at(369) == 0);
  CHECK(encoded_msg.at(370) == 0);
  CHECK(encoded_msg.at(371) == 0x20);
  CHECK(encoded_msg.at(372) == 0x22);
  CHECK(encoded_msg.at(373) == 0);
  CHECK(encoded_msg.at(374) == 0);
  CHECK(encoded_msg.at(375) == 0x20);
  CHECK(encoded_msg.at(376) == 0x33);
  CHECK(encoded_msg.at(377) == 0);
  CHECK(encoded_msg.at(378) == 0);
  CHECK(encoded_msg.at(379) == 0x20);
  CHECK(encoded_msg.at(380) == 0x44);
  CHECK(encoded_msg.at(381) == 0);
  CHECK(encoded_msg.at(382) == 0);
  CHECK(encoded_msg.at(383) == 0x20);
  CHECK(encoded_msg.at(384) == 0x55);
  CHECK(encoded_msg.at(385) == 0);
  CHECK(encoded_msg.at(386) == 0);
  CHECK(encoded_msg.at(387) == 0x20);
  CHECK(encoded_msg.at(388) == 0x66);
  CHECK(encoded_msg.at(389) == 0);
  CHECK(encoded_msg.at(390) == 0);
  CHECK(encoded_msg.at(391) == 0x20);
  CHECK(encoded_msg.at(392) == 0x77);
  CHECK(encoded_msg.at(393) == 0);
  CHECK(encoded_msg.at(394) == 0);
  CHECK(encoded_msg.at(395) == 7);
  CHECK(encoded_msg.at(396) == 0x20);
  CHECK(encoded_msg.at(397) == 0);
  CHECK(encoded_msg.at(398) == 0);
  CHECK(encoded_msg.at(399) == 0);
  CHECK(encoded_msg.at(400) == 0x20);
  CHECK(encoded_msg.at(401) == 0x11);
  CHECK(encoded_msg.at(402) == 0);
  CHECK(encoded_msg.at(403) == 0);
  CHECK(encoded_msg.at(404) == 0x20);
  CHECK(encoded_msg.at(405) == 0x22);
  CHECK(encoded_msg.at(406) == 0);
  CHECK(encoded_msg.at(407) == 0);
  CHECK(encoded_msg.at(408) == 0x20);
  CHECK(encoded_msg.at(409) == 0x33);
  CHECK(encoded_msg.at(410) == 0);
  CHECK(encoded_msg.at(411) == 0);
  CHECK(encoded_msg.at(412) == 0x20);
  CHECK(encoded_msg.at(413) == 0x44);
  CHECK(encoded_msg.at(414) == 0);
  CHECK(encoded_msg.at(415) == 0);
  CHECK(encoded_msg.at(416) == 0x20);
  CHECK(encoded_msg.at(417) == 0x55);
  CHECK(encoded_msg.at(418) == 0);
  CHECK(encoded_msg.at(419) == 0);
  CHECK(encoded_msg.at(420) == 0x20);
  CHECK(encoded_msg.at(421) == 0x66);
  CHECK(encoded_msg.at(422) == 0);
  CHECK(encoded_msg.at(423) == 0);
  CHECK(encoded_msg.at(424) == 6);
  CHECK(encoded_msg.at(425) == 0x20);
  CHECK(encoded_msg.at(426) == 0);
  CHECK(encoded_msg.at(427) == 0);
  CHECK(encoded_msg.at(428) == 0);
  CHECK(encoded_msg.at(429) == 0x20);
  CHECK(encoded_msg.at(430) == 0x11);
  CHECK(encoded_msg.at(431) == 0);
  CHECK(encoded_msg.at(432) == 0);
  CHECK(encoded_msg.at(433) == 0x20);
  CHECK(encoded_msg.at(434) == 0x22);
  CHECK(encoded_msg.at(435) == 0);
  CHECK(encoded_msg.at(436) == 0);
  CHECK(encoded_msg.at(437) == 0x20);
  CHECK(encoded_msg.at(438) == 0x33);
  CHECK(encoded_msg.at(439) == 0);
  CHECK(encoded_msg.at(440) == 0);
  CHECK(encoded_msg.at(441) == 0x20);
  CHECK(encoded_msg.at(442) == 0x44);
  CHECK(encoded_msg.at(443) == 0);
  CHECK(encoded_msg.at(444) == 0);
  CHECK(encoded_msg.at(445) == 0x20);
  CHECK(encoded_msg.at(446) == 0x55);
  CHECK(encoded_msg.at(447) == 0);
  CHECK(encoded_msg.at(448) == 0);
  CHECK(encoded_msg.at(449) == 4);
  CHECK(encoded_msg.at(450) == 0x20);
  CHECK(encoded_msg.at(451) == 0);
  CHECK(encoded_msg.at(452) == 0);
  CHECK(encoded_msg.at(453) == 0);
  CHECK(encoded_msg.at(454) == 0x20);
  CHECK(encoded_msg.at(455) == 0x11);
  CHECK(encoded_msg.at(456) == 0);
  CHECK(encoded_msg.at(457) == 0);
  CHECK(encoded_msg.at(458) == 0x20);
  CHECK(encoded_msg.at(459) == 0x22);
  CHECK(encoded_msg.at(460) == 0);
  CHECK(encoded_msg.at(461) == 0);
  CHECK(encoded_msg.at(462) == 0x20);
  CHECK(encoded_msg.at(463) == 0x33);
  CHECK(encoded_msg.at(464) == 0);
  CHECK(encoded_msg.at(465) == 0);
  CHECK(encoded_msg.at(466) == 3);
  CHECK(encoded_msg.at(467) == 0x20);
  CHECK(encoded_msg.at(468) == 0);
  CHECK(encoded_msg.at(469) == 0);
  CHECK(encoded_msg.at(470) == 0);
  CHECK(encoded_msg.at(471) == 0x20);
  CHECK(encoded_msg.at(472) == 0x11);
  CHECK(encoded_msg.at(473) == 0);
  CHECK(encoded_msg.at(474) == 0);
  CHECK(encoded_msg.at(475) == 0x20);
  CHECK(encoded_msg.at(476) == 0x22);
  CHECK(encoded_msg.at(477) == 0);
  CHECK(encoded_msg.at(478) == 0);
  CHECK(encoded_msg.at(479) == 2);
  CHECK(encoded_msg.at(480) == 0x20);
  CHECK(encoded_msg.at(481) == 0);
  CHECK(encoded_msg.at(482) == 0);
  CHECK(encoded_msg.at(483) == 0);
  CHECK(encoded_msg.at(484) == 0x20);
  CHECK(encoded_msg.at(485) == 0x11);
  CHECK(encoded_msg.at(486) == 0);
  CHECK(encoded_msg.at(487) == 0);
  CHECK(encoded_msg.at(488) == 1);
  CHECK(encoded_msg.at(489) == 0x20);
  CHECK(encoded_msg.at(490) == 0);
  CHECK(encoded_msg.at(491) == 0);
  CHECK(encoded_msg.at(492) == 0);
  CHECK(encoded_msg.at(493) == 0);
  CHECK(encoded_msg.at(494) == 0);
  CHECK(encoded_msg.at(495) == 0);
  CHECK(encoded_msg.at(496) == 0);
  CHECK(encoded_msg.at(497) == 0);
  CHECK(encoded_msg.at(498) == 0x04);
  CHECK(encoded_msg.at(499) == 0);
  CHECK(encoded_msg.at(500) == 0);
  CHECK(encoded_msg.at(501) == 0);
  CHECK(encoded_msg.at(502) == 0);
  CHECK(encoded_msg.at(503) == 0);
  CHECK(encoded_msg.at(504) == 0);
  CHECK(encoded_msg.at(505) == 0);
  CHECK(encoded_msg.at(506) == 0);
  CHECK(encoded_msg.at(507) == 0);
  CHECK(encoded_msg.at(508) == 0);
}

TEST_CASE("decoding with 4SoCs, 8TunerPaths, 5activeNBTs, 8 DFEs and 8 Receivers")
{
  GetResourceUsage_repl msg8ToDecode;
  vector<uint8_t> encoded_msg{1,2,3,1,4,//MsgInfo
  1,0,//soc1
  8,//NrOfdfes
  8,0x20,0,0,0,0x20,0x11,0,0,0x20,0x22,0,0,0x20,0x33,0,0,0x20,0x44,0,0,0x20,0x55,0,0,0x20,0x66,0,0,0x20,0x77,0,0,//dfe1-42
  7,0x20,0,0,0,0x20,0x11,0,0,0x20,0x22,0,0,0x20,0x33,0,0,0x20,0x44,0,0,0x20,0x55,0,0,0x20,0x66,0,0,//dfe2
  6,0x20,0,0,0,0x20,0x11,0,0,0x20,0x22,0,0,0x20,0x33,0,0,0x20,0x44,0,0,0x20,0x55,0,0,//dfe3
  4,0x20,0,0,0,0x20,0x11,0,0,0x20,0x22,0,0,0x20,0x33,0,0,//dfe4
  3,0x20,0,0,0,0x20,0x11,0,0,0x20,0x22,0,0,//dfe5
  2,0x20,0,0,0,0x20,0x11,0,0,//dfe6
  1,0x20,0,0,0,//7
  0,//dfe8
  0,0,0,0,//rfa6
  2,8,//soc2
  0x11,0x81,0x10,1,1,0,0,//p1+nbt1
  0x11,0x82,0x20,1,1,0,0,2,2,0,0,//p2+nbt1,2
  0x11,0x83,0x30,1,1,0,0,2,2,0,0,3,3,0,0,//p3+nbt1,2,3
  0x11,0x84,0x40,1,1,0,0,2,2,0,0,3,3,0,0,4,4,0,0,//p4+nbt1,2,3,4
  0x11,0x85,0x50,1,1,0,0,2,2,0,0,3,3,0,0,4,4,0,0,5,5,0,0,//p5+nbt1,2,3,4,5
  0x11,0x85,0x60,1,1,0,0,2,2,0,0,3,3,0,0,4,4,0,0,5,5,0,0,//p6+nbt1,2,3,4,5
  0x11,0x80,0x70,//p7
  0x11,0,0x80,//p8
  0,//NrOfdfes
  0,0,0,0,//rfa6
  3,8,//soc3
  0x11,0x81,0x10,1,1,0,0,//p1+nbt1
  0x11,0x82,0x20,1,1,0,0,2,2,0,0,//p2+nbt1,2
  0x11,0x83,0x30,1,1,0,0,2,2,0,0,3,3,0,0,//p3+nbt1,2,3
  0x11,0x84,0x40,1,1,0,0,2,2,0,0,3,3,0,0,4,4,0,0,//p4+nbt1,2,3,4
  0x11,0x85,0x50,1,1,0,0,2,2,0,0,3,3,0,0,4,4,0,0,5,5,0,0,//p5+nbt1,2,3,4,5
  0x11,0x85,0x60,1,1,0,0,2,2,0,0,3,3,0,0,4,4,0,0,5,5,0,0,//p6+nbt1,2,3,4,5
  0x11,0x80,0x70,//p7
  0x11,0,0x80,//p8
  8,//NrOfdfes
  8,0x20,0,0,0,0x20,0x11,0,0,0x20,0x22,0,0,0x20,0x33,0,0,0x20,0x44,0,0,0x20,0x55,0,0,0x20,0x66,0,0,0x20,0x77,0,0,//dfe1
  7,0x20,0,0,0,0x20,0x11,0,0,0x20,0x22,0,0,0x20,0x33,0,0,0x20,0x44,0,0,0x20,0x55,0,0,0x20,0x66,0,0,//dfe2
  6,0x20,0,0,0,0x20,0x11,0,0,0x20,0x22,0,0,0x20,0x33,0,0,0x20,0x44,0,0,0x20,0x55,0,0,//dfe3
  4,0x20,0,0,0,0x20,0x11,0,0,0x20,0x22,0,0,0x20,0x33,0,0,//dfe4
  3,0x20,0,0,0,0x20,0x11,0,0,0x20,0x22,0,0,//dfe5
  2,0x20,0,0,0,0x20,0x11,0,0,//dfe6
  1,0x20,0,0,0,//dfe7
  0,//dfe8
  0,0,0,0,//rfa6
  4,0,//soc4
  0,//NrOfdfes
  0,0,0,0,//rfa6
  0,0,0,0};
  
  msg8ToDecode.decode(encoded_msg);
  CHECK(msg8ToDecode.getCookie() == 1);
  CHECK(msg8ToDecode.getReplyStatus() == 1);
  CHECK(msg8ToDecode.getNrOfSoCs() == 4);
  CHECK(msg8ToDecode.socs.at(0).getSoC_ID() == 1);
  CHECK(msg8ToDecode.socs.at(0).getNrOfTunerPaths() == 0);
  CHECK(msg8ToDecode.socs.at(0).getNrOfDFEs() == 8);
  CHECK(msg8ToDecode.socs.size() == 4);
  CHECK(msg8ToDecode.socs.at(0).tunerPaths.size() == 0);
  CHECK(msg8ToDecode.socs.at(0).dfes.size() == 8);

  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).getNrOfAssignedReceivers() == 8);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(0).getBroadcastStandard() == 0);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(0).getMode() == 0);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(1).getMode() == 1);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(2).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(2).getBroadcastStandard() == 2);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(2).getMode() == 2);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(3).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(3).getBroadcastStandard() == 3);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(3).getMode() == 3);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(4).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(4).getBroadcastStandard() == 4);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(4).getMode() == 4);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(5).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(5).getBroadcastStandard() == 5);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(5).getMode() == 5);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(6).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(6).getBroadcastStandard() == 6);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(6).getMode() == 6);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(7).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(7).getBroadcastStandard() == 7);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(0).AssignedReceivers.at(7).getMode() == 7);

  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).getNrOfAssignedReceivers() == 7);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(0).getBroadcastStandard() == 0);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(0).getMode() == 0);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(1).getMode() == 1);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(2).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(2).getBroadcastStandard() == 2);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(2).getMode() == 2);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(3).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(3).getBroadcastStandard() == 3);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(3).getMode() == 3);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(4).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(4).getBroadcastStandard() == 4);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(4).getMode() == 4);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(5).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(5).getBroadcastStandard() == 5);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(5).getMode() == 5);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(6).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(6).getBroadcastStandard() == 6);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(1).AssignedReceivers.at(6).getMode() == 6);

  CHECK(msg8ToDecode.socs.at(0).dfes.at(2).getNrOfAssignedReceivers() == 6);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.at(0).getBroadcastStandard() == 0);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.at(0).getMode() == 0);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.at(1).getMode() == 1);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.at(2).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.at(2).getBroadcastStandard() == 2);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.at(2).getMode() == 2);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.at(3).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.at(3).getBroadcastStandard() == 3);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.at(3).getMode() == 3);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.at(4).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.at(4).getBroadcastStandard() == 4);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.at(4).getMode() == 4);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.at(5).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.at(5).getBroadcastStandard() == 5);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(2).AssignedReceivers.at(5).getMode() == 5);

  CHECK(msg8ToDecode.socs.at(0).dfes.at(3).getNrOfAssignedReceivers() == 4);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.at(0).getBroadcastStandard() == 0);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.at(0).getMode() == 0);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.at(1).getMode() == 1);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.at(2).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.at(2).getBroadcastStandard() == 2);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.at(2).getMode() == 2);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.at(3).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.at(3).getBroadcastStandard() == 3);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(3).AssignedReceivers.at(3).getMode() == 3);

  CHECK(msg8ToDecode.socs.at(0).dfes.at(4).getNrOfAssignedReceivers() == 3);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(4).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(4).AssignedReceivers.at(0).getBroadcastStandard() == 0);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(4).AssignedReceivers.at(0).getMode() == 0);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(4).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(4).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(4).AssignedReceivers.at(1).getMode() == 1);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(4).AssignedReceivers.at(2).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(4).AssignedReceivers.at(2).getBroadcastStandard() == 2);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(4).AssignedReceivers.at(2).getMode() == 2);

  CHECK(msg8ToDecode.socs.at(0).dfes.at(5).getNrOfAssignedReceivers() == 2);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(5).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(5).AssignedReceivers.at(0).getBroadcastStandard() == 0);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(5).AssignedReceivers.at(0).getMode() == 0);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(5).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(5).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(5).AssignedReceivers.at(1).getMode() == 1);

  CHECK(msg8ToDecode.socs.at(0).dfes.at(6).getNrOfAssignedReceivers() == 1);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(6).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(6).AssignedReceivers.at(0).getBroadcastStandard() == 0);
  CHECK(msg8ToDecode.socs.at(0).dfes.at(6).AssignedReceivers.at(0).getMode() == 0);

  CHECK(msg8ToDecode.socs.at(0).dfes.at(7).getNrOfAssignedReceivers() == 0);

  CHECK(msg8ToDecode.socs.at(1).getSoC_ID() == 2);
  CHECK(msg8ToDecode.socs.at(1).getNrOfTunerPaths() == 8);
  CHECK(msg8ToDecode.socs.at(1).getNrOfDFEs() == 0);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.size() == 8);
  CHECK(msg8ToDecode.socs.at(1).dfes.size() == 0);
  
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(0).getAntennaHandle() == 0x11);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(0).getActive() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(0).getActiveNBTs() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(0).getAntennaPort() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(0).nbts.size() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(0).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(0).nbts.at(0).getAssigned_DFE_ix() == 1);

  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(1).getAntennaHandle() == 0x11);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(1).getActive() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(1).getActiveNBTs() == 2);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(1).getAntennaPort() == 2);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(1).nbts.size() == 2);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(1).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(1).nbts.at(0).getAssigned_DFE_ix() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(1).nbts.at(1).getNBT_ix() == 2);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(1).nbts.at(1).getAssigned_DFE_ix() == 2);

  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(2).getAntennaHandle() == 0x11);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(2).getActive() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(2).getActiveNBTs() == 3);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(2).getAntennaPort() == 3);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(2).nbts.size() == 3);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(2).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(2).nbts.at(0).getAssigned_DFE_ix() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(2).nbts.at(1).getNBT_ix() == 2);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(2).nbts.at(1).getAssigned_DFE_ix() == 2);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(2).nbts.at(2).getNBT_ix() == 3);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(2).nbts.at(2).getAssigned_DFE_ix() == 3);

  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(3).getAntennaHandle() == 0x11);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(3).getActive() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(3).getActiveNBTs() == 4);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(3).getAntennaPort() == 4);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(3).nbts.size() == 4);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(3).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(3).nbts.at(0).getAssigned_DFE_ix() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(3).nbts.at(1).getNBT_ix() == 2);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(3).nbts.at(1).getAssigned_DFE_ix() == 2);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(3).nbts.at(2).getNBT_ix() == 3);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(3).nbts.at(2).getAssigned_DFE_ix() == 3);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(3).nbts.at(3).getNBT_ix() == 4);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(3).nbts.at(3).getAssigned_DFE_ix() == 4);

  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(4).getAntennaHandle() == 0x11);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(4).getActive() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(4).getActiveNBTs() == 5);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(4).getAntennaPort() == 5);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(4).nbts.size() == 5);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(4).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(4).nbts.at(0).getAssigned_DFE_ix() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(4).nbts.at(1).getNBT_ix() == 2);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(4).nbts.at(1).getAssigned_DFE_ix() == 2);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(4).nbts.at(2).getNBT_ix() == 3);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(4).nbts.at(2).getAssigned_DFE_ix() == 3);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(4).nbts.at(3).getNBT_ix() == 4);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(4).nbts.at(3).getAssigned_DFE_ix() == 4);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(4).nbts.at(4).getNBT_ix() == 5);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(4).nbts.at(4).getAssigned_DFE_ix() == 5);

  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(5).getAntennaHandle() == 0x11);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(5).getActive() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(5).getActiveNBTs() == 5);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(5).getAntennaPort() == 6);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(5).nbts.size() == 5);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(5).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(5).nbts.at(0).getAssigned_DFE_ix() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(5).nbts.at(1).getNBT_ix() == 2);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(5).nbts.at(1).getAssigned_DFE_ix() == 2);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(5).nbts.at(2).getNBT_ix() == 3);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(5).nbts.at(2).getAssigned_DFE_ix() == 3);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(5).nbts.at(3).getNBT_ix() == 4);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(5).nbts.at(3).getAssigned_DFE_ix() == 4);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(5).nbts.at(4).getNBT_ix() == 5);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(5).nbts.at(4).getAssigned_DFE_ix() == 5);

  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(6).getAntennaHandle() == 0x11);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(6).getActive() == 1);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(6).getActiveNBTs() == 0);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(6).getAntennaPort() == 7);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(6).nbts.size() == 0);

  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(7).getAntennaHandle() == 0x11);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(7).getActive() == 0);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(7).getActiveNBTs() == 0);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(7).getAntennaPort() == 8);
  CHECK(msg8ToDecode.socs.at(1).tunerPaths.at(7).nbts.size() == 0);

  CHECK(msg8ToDecode.socs.at(2).getSoC_ID() == 3);
  CHECK(msg8ToDecode.socs.at(2).getNrOfTunerPaths() == 8);
  CHECK(msg8ToDecode.socs.at(2).getNrOfDFEs() == 8);
  CHECK(msg8ToDecode.socs.at(2).dfes.size() == 8);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.size() == 8);

  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(0).getAntennaHandle() == 0x11);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(0).getActive() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(0).getActiveNBTs() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(0).getAntennaPort() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(0).nbts.size() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(0).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(0).nbts.at(0).getAssigned_DFE_ix() == 1);

  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(1).getAntennaHandle() == 0x11);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(1).getActive() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(1).getActiveNBTs() == 2);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(1).getAntennaPort() == 2);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(1).nbts.size() == 2);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(1).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(1).nbts.at(0).getAssigned_DFE_ix() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(1).nbts.at(1).getNBT_ix() == 2);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(1).nbts.at(1).getAssigned_DFE_ix() == 2);

  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(2).getAntennaHandle() == 0x11);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(2).getActive() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(2).getActiveNBTs() == 3);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(2).getAntennaPort() == 3);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(2).nbts.size() == 3);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(2).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(2).nbts.at(0).getAssigned_DFE_ix() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(2).nbts.at(1).getNBT_ix() == 2);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(2).nbts.at(1).getAssigned_DFE_ix() == 2);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(2).nbts.at(2).getNBT_ix() == 3);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(2).nbts.at(2).getAssigned_DFE_ix() == 3);

  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(3).getAntennaHandle() == 0x11);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(3).getActive() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(3).getActiveNBTs() == 4);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(3).getAntennaPort() == 4);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(3).nbts.size() == 4);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(3).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(3).nbts.at(0).getAssigned_DFE_ix() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(3).nbts.at(1).getNBT_ix() == 2);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(3).nbts.at(1).getAssigned_DFE_ix() == 2);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(3).nbts.at(2).getNBT_ix() == 3);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(3).nbts.at(2).getAssigned_DFE_ix() == 3);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(3).nbts.at(3).getNBT_ix() == 4);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(3).nbts.at(3).getAssigned_DFE_ix() == 4);

  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(4).getAntennaHandle() == 0x11);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(4).getActive() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(4).getActiveNBTs() == 5);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(4).getAntennaPort() == 5);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(4).nbts.size() == 5);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(4).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(4).nbts.at(0).getAssigned_DFE_ix() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(4).nbts.at(1).getNBT_ix() == 2);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(4).nbts.at(1).getAssigned_DFE_ix() == 2);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(4).nbts.at(2).getNBT_ix() == 3);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(4).nbts.at(2).getAssigned_DFE_ix() == 3);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(4).nbts.at(3).getNBT_ix() == 4);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(4).nbts.at(3).getAssigned_DFE_ix() == 4);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(4).nbts.at(4).getNBT_ix() == 5);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(4).nbts.at(4).getAssigned_DFE_ix() == 5);

  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(5).getAntennaHandle() == 0x11);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(5).getActive() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(5).getActiveNBTs() == 5);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(5).getAntennaPort() == 6);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(5).nbts.size() == 5);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(5).nbts.at(0).getNBT_ix() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(5).nbts.at(0).getAssigned_DFE_ix() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(5).nbts.at(1).getNBT_ix() == 2);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(5).nbts.at(1).getAssigned_DFE_ix() == 2);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(5).nbts.at(2).getNBT_ix() == 3);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(5).nbts.at(2).getAssigned_DFE_ix() == 3);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(5).nbts.at(3).getNBT_ix() == 4);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(5).nbts.at(3).getAssigned_DFE_ix() == 4);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(5).nbts.at(4).getNBT_ix() == 5);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(5).nbts.at(4).getAssigned_DFE_ix() == 5);

  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(6).getAntennaHandle() == 0x11);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(6).getActive() == 1);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(6).getActiveNBTs() == 0);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(6).getAntennaPort() == 7);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(6).nbts.size() == 0);

  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(7).getAntennaHandle() == 0x11);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(7).getActive() == 0);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(7).getActiveNBTs() == 0);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(7).getAntennaPort() == 8);
  CHECK(msg8ToDecode.socs.at(2).tunerPaths.at(7).nbts.size() == 0);

  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).getNrOfAssignedReceivers() == 8);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.size() == 8);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(0).getBroadcastStandard() == 0);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(0).getMode() == 0);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(1).getMode() == 1);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(2).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(2).getBroadcastStandard() == 2);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(2).getMode() == 2);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(3).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(3).getBroadcastStandard() == 3);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(3).getMode() == 3);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(4).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(4).getBroadcastStandard() == 4);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(4).getMode() == 4);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(5).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(5).getBroadcastStandard() == 5);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(5).getMode() == 5);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(6).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(6).getBroadcastStandard() == 6);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(6).getMode() == 6);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(7).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(7).getBroadcastStandard() == 7);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(0).AssignedReceivers.at(7).getMode() == 7);

  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).getNrOfAssignedReceivers() == 7);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.size() == 7);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(0).getBroadcastStandard() == 0);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(0).getMode() == 0);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(1).getMode() == 1);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(2).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(2).getBroadcastStandard() == 2);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(2).getMode() == 2);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(3).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(3).getBroadcastStandard() == 3);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(3).getMode() == 3);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(4).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(4).getBroadcastStandard() == 4);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(4).getMode() == 4);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(5).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(5).getBroadcastStandard() == 5);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(5).getMode() == 5);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(6).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(6).getBroadcastStandard() == 6);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(1).AssignedReceivers.at(6).getMode() == 6);

  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).getNrOfAssignedReceivers() == 6);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).AssignedReceivers.size() == 6);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).AssignedReceivers.at(0).getBroadcastStandard() == 0);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).AssignedReceivers.at(0).getMode() == 0);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).AssignedReceivers.at(1).getMode() == 1);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).AssignedReceivers.at(2).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).AssignedReceivers.at(2).getBroadcastStandard() == 2);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).AssignedReceivers.at(2).getMode() == 2);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).AssignedReceivers.at(3).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).AssignedReceivers.at(3).getBroadcastStandard() == 3);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).AssignedReceivers.at(3).getMode() == 3);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).AssignedReceivers.at(4).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).AssignedReceivers.at(4).getBroadcastStandard() == 4);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).AssignedReceivers.at(4).getMode() == 4);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).AssignedReceivers.at(5).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).AssignedReceivers.at(5).getBroadcastStandard() == 5);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(2).AssignedReceivers.at(5).getMode() == 5);

  CHECK(msg8ToDecode.socs.at(2).dfes.at(3).AssignedReceivers.size() == 4);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(3).getNrOfAssignedReceivers() == 4);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(3).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(3).AssignedReceivers.at(0).getBroadcastStandard() == 0);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(3).AssignedReceivers.at(0).getMode() == 0);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(3).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(3).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(3).AssignedReceivers.at(1).getMode() == 1);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(3).AssignedReceivers.at(2).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(3).AssignedReceivers.at(2).getBroadcastStandard() == 2);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(3).AssignedReceivers.at(2).getMode() == 2);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(3).AssignedReceivers.at(3).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(3).AssignedReceivers.at(3).getBroadcastStandard() == 3);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(3).AssignedReceivers.at(3).getMode() == 3);

  CHECK(msg8ToDecode.socs.at(2).dfes.at(4).getNrOfAssignedReceivers() == 3);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(4).AssignedReceivers.size() == 3);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(4).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(4).AssignedReceivers.at(0).getBroadcastStandard() == 0);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(4).AssignedReceivers.at(0).getMode() == 0);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(4).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(4).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(4).AssignedReceivers.at(1).getMode() == 1);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(4).AssignedReceivers.at(2).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(4).AssignedReceivers.at(2).getBroadcastStandard() == 2);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(4).AssignedReceivers.at(2).getMode() == 2);

  CHECK(msg8ToDecode.socs.at(2).dfes.at(5).getNrOfAssignedReceivers() == 2);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(5).AssignedReceivers.size() == 2);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(5).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(5).AssignedReceivers.at(0).getBroadcastStandard() == 0);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(5).AssignedReceivers.at(0).getMode() == 0);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(5).AssignedReceivers.at(1).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(5).AssignedReceivers.at(1).getBroadcastStandard() == 1);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(5).AssignedReceivers.at(1).getMode() == 1);

  CHECK(msg8ToDecode.socs.at(2).dfes.at(6).getNrOfAssignedReceivers() == 1);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(6).AssignedReceivers.size() == 1);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(6).AssignedReceivers.at(0).getReceiverHandle() == 0x20);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(6).AssignedReceivers.at(0).getBroadcastStandard() == 0);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(6).AssignedReceivers.at(0).getMode() == 0);

  CHECK(msg8ToDecode.socs.at(2).dfes.at(7).getNrOfAssignedReceivers() == 0);
  CHECK(msg8ToDecode.socs.at(2).dfes.at(7).AssignedReceivers.size() == 0);

  CHECK(msg8ToDecode.socs.at(3).getSoC_ID() == 4);
  CHECK(msg8ToDecode.socs.at(3).getNrOfTunerPaths() == 0);
  CHECK(msg8ToDecode.socs.at(3).getNrOfDFEs() == 0);
  CHECK(msg8ToDecode.socs.at(3).dfes.size() == 0);
  CHECK(msg8ToDecode.socs.at(3).tunerPaths.size() == 0);

}