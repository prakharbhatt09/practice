#include <vector>
#include <cstdint>
#include "Receiver.hpp"

using namespace std;

class GetReceivers_repl{

    private:
    uint8_t MessageType;
    uint8_t Cookie;
    const uint16_t Opcode{0x0102};
    uint8_t ReplyStatus;
    uint8_t Rfa1;
    uint8_t NrOfReceivers;
    vector<Receiver> receiversVector;
    uint32_t Rfa5;

    public:
    uint8_t getMessageType(){return MessageType;}
    uint8_t getCookie(){return Cookie;}
    uint8_t getReplyStatus(){return ReplyStatus;}
    uint8_t getRfa1(){return Rfa1;}
    uint8_t getNrOfReceivers(){return NrOfReceivers;}
    uint8_t getRfa5(){return Rfa5;}
    vector<Receiver> getReceiversVector(){return receiversVector;}

    void addReceiverInstance(Receiver &ReceiverObject);
    void decode(const vector<uint8_t> &toDecode);

    void setMessageType(uint8_t MessageType_val){MessageType = MessageType_val;}
    void setCookie(uint8_t Cookie_val){Cookie = Cookie_val;}
    void setReplyStatus(uint8_t ReplyStatus_val){ReplyStatus = ReplyStatus_val;}
    void setRfa1(uint8_t Rfa1_val){Rfa1 = Rfa1_val;}
    void setNrOfReceivers(uint8_t NrOfReceivers_val){NrOfReceivers = NrOfReceivers_val;}
    void setRfa5(uint8_t Rfa5_val){Rfa5 = Rfa5_val;}
    
};