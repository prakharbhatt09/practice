#include <iostream>
#include <vector>
#include <cstdint>

class CreateReceiver_repl{
    private:
    const int8_t MessageType{0};
    uint8_t Cookie;
    const uint16_t Opcode{0x0203};
    uint8_t ReplyStatus;
    uint8_t ReceiverHandle;
    uint32_t Rfa;

    public:

    CreateReceiver_repl();

    CreateReceiver_repl(uint8_t Cookie_val, uint8_t ReplyStatus_val, uint8_t ReceiverHandle_val, uint32_t Rfa_val)
            :Cookie{Cookie_val}, ReplyStatus{ReplyStatus_val}, ReceiverHandle{ReceiverHandle_val}, Rfa{Rfa_val}{
    }
                

    std::vector<uint8_t> encode();
    void decode(const std::vector<uint8_t>& toDecode);

    uint8_t getCookie(){return Cookie;}
    uint8_t getReplyStatus(){return ReplyStatus;}
    uint8_t getReceiverHandle(){return ReceiverHandle;}
    uint32_t getRfa(){return Rfa;}
    
};