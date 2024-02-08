#include <iostream>
#include <vector>
#include <cstdint>

class CreateReceiver{
    private:


    public:
    const uint8_t MessageType{0};
    uint8_t Cookie;     
    const uint16_t Opcode{0x0203}; 
    uint8_t PHY_ID;
    uint8_t CTRL_ID;
    uint8_t BroadcastStandard;
    uint8_t ReceiverMode;
    uint16_t Rfa;

    CreateReceiver();

    CreateReceiver(uint8_t PHY_val,uint8_t CTRL_val,uint8_t BS_val,uint8_t RM_val,uint16_t Rfa_val)
        :PHY_ID{PHY_val}, CTRL_ID{CTRL_val}, BroadcastStandard{BS_val}, ReceiverMode{RM_val}, Rfa{Rfa_val}{
    }

    std::vector<uint8_t> encode();
    void decode(const std::vector<uint8_t>& toDecode);
};

    //Cookie Opcode1 Opcode2 PHY CTRL BS RM     Rfa
    // 0           1,2        3    4   5  6     7,8