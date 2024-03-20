#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "fakeit.hpp"
#include "GetReceivers_repl.hpp"
#include "Receiver.hpp"
#include "Antenna.hpp"
#include "GetReceiverReplAdapter.hpp"

using namespace std;
using namespace fakeit;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_CASE("decoding a msg with 0 receiver and 0 antenna handles"){

//Instantiate a mock object
Mock<I_GetReceiversRepl> mock1;
When(Method(mock1,addReceiverInstance)).Return();
When(Method(mock1,decode)).Return();

I_GetReceiversRepl& mockMessage = mock1.get();
MsgReplAdapter myAdapter(&mockMessage);

 vector<uint8_t> toDecode{};
 myAdapter.decode(toDecode);

//assert
Verify(Method(mock1,addReceiverInstance)).Never();
Verify(Method(mock1,decode)).Exactly(1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("decoding a msg with 1 receiver"){

 Mock<I_GetReceiversRepl> mock1;
 Mock<I_Receiver> mockRec;
 
 When(Method(mock1,addReceiverInstance)).AlwaysReturn();
 When(Method(mock1,decode)).AlwaysReturn();
 
 I_GetReceiversRepl & mockMessage = mock1.get();
 MsgReplAdapter myAdapter(&mockMessage);
 
 I_Receiver & mockR = mockRec.get();
 myAdapter.addReceiverInstance(&mockR);
 
 vector<uint8_t> toDecode{};
 myAdapter.decode(toDecode);
 
 Verify(Method(mock1,addReceiverInstance)).Once();
 Verify(Method(mock1,decode)).Exactly(Once);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Zustands-statebased

TEST_CASE("decoding with 1 receiver and 2 antenna handle"){
 Mock<I_GetReceiversRepl> mockMsg;
 Mock<I_Receiver> mockRec;
 Mock<I_Antenna> mockAnt1;
 Mock<I_Antenna> mockAnt2;

 When(Method(mockMsg,decode)).AlwaysReturn();
 When(Method(mockMsg,addReceiverInstance)).AlwaysReturn();
 When(Method(mockRec,addAntennaHandleInstance)).AlwaysReturn();

 I_GetReceiversRepl & mockM = mockMsg.get();
 MsgReplAdapter msgAdapter(&mockM);
 I_Receiver & mockR = mockRec.get();

 msgAdapter.addReceiverInstance(&mockR);

 ReceiverAdapter recAdapter(&mockR);
 
 I_Antenna & mockA1 = mockAnt1.get();
 I_Antenna & mockA2 = mockAnt2.get();
 recAdapter.addAntennaHandleInstance(&mockA1);
 recAdapter.addAntennaHandleInstance(&mockA2);

 vector<uint8_t> toDecode{0x00,0x00,0x00,0x00};
 msgAdapter.decode(toDecode);

 Verify(Method(mockMsg,addReceiverInstance)).AtLeastOnce();
 Verify(Method(mockRec,addAntennaHandleInstance)).Twice();
 Verify(Method(mockMsg,decode)).Once();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("decode with 2 receiver and 4 antenna for each"){
 Mock<I_GetReceiversRepl> mockMsg;
 Mock<I_Receiver> mockRec1;
 Mock<I_Receiver> mockRec2;
 Mock<I_Antenna> mockAnt1;
 Mock<I_Antenna> mockAnt2;
 Mock<I_Antenna> mockAnt3;
 Mock<I_Antenna> mockAnt4;

 When(Method(mockMsg,decode)).AlwaysReturn();
 When(Method(mockMsg,addReceiverInstance)).AlwaysReturn();
 When(Method(mockRec1,addAntennaHandleInstance)).AlwaysReturn();
 When(Method(mockRec2,addAntennaHandleInstance)).AlwaysReturn();

 I_GetReceiversRepl & testMessage = mockMsg.get();
 MsgReplAdapter myMsgAdapter(&testMessage);

 I_Receiver & testReceiver1 = mockRec1.get();
 I_Receiver & testReceiver2 = mockRec2.get();

 myMsgAdapter.addReceiverInstance(&testReceiver1);
 myMsgAdapter.addReceiverInstance(&testReceiver2);

 ReceiverAdapter myRecAdapter1(&testReceiver1);
 ReceiverAdapter myRecAdapter2(&testReceiver2);

 I_Antenna & testAntenna1 = mockAnt1.get();
 I_Antenna & testAntenna2 = mockAnt2.get(); 
 I_Antenna & testAntenna3 = mockAnt3.get();
 I_Antenna & testAntenna4 = mockAnt4.get();

 myRecAdapter1.addAntennaHandleInstance(&testAntenna1);
 myRecAdapter1.addAntennaHandleInstance(&testAntenna2);
 myRecAdapter1.addAntennaHandleInstance(&testAntenna3);
 myRecAdapter1.addAntennaHandleInstance(&testAntenna4);

 myRecAdapter2.addAntennaHandleInstance(&testAntenna1);
 myRecAdapter2.addAntennaHandleInstance(&testAntenna2);
 myRecAdapter2.addAntennaHandleInstance(&testAntenna3);
 myRecAdapter2.addAntennaHandleInstance(&testAntenna4);
 
 vector<uint8_t> toDecode{};
 myMsgAdapter.decode(toDecode);

 Verify(Method(mockMsg,addReceiverInstance)).Twice();
 Verify(Method(mockRec1,addAntennaHandleInstance)).Exactly(4);
 Verify(Method(mockRec2,addAntennaHandleInstance)).Exactly(4);
 Verify(Method(mockMsg,decode)).Exactly(1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("decode with 2 receiver and 4 and 0 antenna respectively"){
 Mock<I_GetReceiversRepl> mockMsg;
 Mock<I_Receiver> mockRec1;
 Mock<I_Receiver> mockRec2;
 Mock<I_Antenna> mockAnt1;
 Mock<I_Antenna> mockAnt2;
 Mock<I_Antenna> mockAnt3;
 Mock<I_Antenna> mockAnt4;

 When(Method(mockMsg,decode)).AlwaysReturn();
 When(Method(mockMsg,addReceiverInstance)).AlwaysReturn();
 When(Method(mockRec1,addAntennaHandleInstance)).AlwaysReturn();
 When(Method(mockRec2,addAntennaHandleInstance)).AlwaysReturn();

 I_GetReceiversRepl & testMessage = mockMsg.get();
 MsgReplAdapter myMsgAdapter(&testMessage);

 I_Receiver & testReceiver1 = mockRec1.get();
 I_Receiver & testReceiver2 = mockRec2.get();

 myMsgAdapter.addReceiverInstance(&testReceiver1);
 myMsgAdapter.addReceiverInstance(&testReceiver2);

 ReceiverAdapter myRecAdapter1(&testReceiver1);
 ReceiverAdapter myRecAdapter2(&testReceiver2);

 I_Antenna & testAntenna1 = mockAnt1.get();
 I_Antenna & testAntenna2 = mockAnt2.get(); 
 I_Antenna & testAntenna3 = mockAnt3.get();
 I_Antenna & testAntenna4 = mockAnt4.get();

 myRecAdapter1.addAntennaHandleInstance(&testAntenna1);
 myRecAdapter1.addAntennaHandleInstance(&testAntenna2);
 myRecAdapter1.addAntennaHandleInstance(&testAntenna3);
 myRecAdapter1.addAntennaHandleInstance(&testAntenna4);

 vector<uint8_t> toDecode{};
 myMsgAdapter.decode(toDecode);

 Verify(Method(mockMsg,addReceiverInstance)).Twice();
 Verify(Method(mockRec1,addAntennaHandleInstance)).Exactly(4);
 Verify(Method(mockRec2,addAntennaHandleInstance)).Never();
 Verify(Method(mockMsg,decode)).Exactly(1);
 VerifyNoOtherInvocations(mockMsg);
 VerifyNoOtherInvocations(mockRec1);
 VerifyNoOtherInvocations(mockRec2);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


