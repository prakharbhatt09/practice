#include "CreateReceiver.hpp"

using namespace std;

    CreateReceiver::CreateReceiver(){}

    vector<uint8_t> CreateReceiver::encode(){
        vector<uint8_t> toEncode;

        toEncode.push_back((PHY_ID << 4) & 0xF0);
        toEncode.push_back((CTRL_ID << 4) & 0xF0);
        toEncode.push_back((BroadcastStandard << 4) & 0xF0);
        toEncode.push_back((ReceiverMode << 4) & 0xF0);
        toEncode.push_back((Rfa >> 8) & 0xFF);
        toEncode.push_back(Rfa & 0xFF);

        return toEncode;
    };

    void CreateReceiver::decode(const vector<uint8_t>& toDecode){

        PHY_ID = (toDecode.at(0) >> 4) & 0x0F;
        CTRL_ID = (toDecode.at(1) >> 4) & 0x0F;
        BroadcastStandard = (toDecode.at(2) >> 4) & 0x0F;
        ReceiverMode = (toDecode.at(3) >> 4) & 0x0F;
        Rfa = ((toDecode.at(4) << 8) & 0xFF);
        Rfa = (toDecode.at(5) & 0xFF);
    };

    //Cookie Opcode1 Opcode2 PHY CTRL BS RM     Rfa
    //                          0    1   2  3     4
