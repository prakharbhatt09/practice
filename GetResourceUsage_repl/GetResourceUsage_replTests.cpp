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