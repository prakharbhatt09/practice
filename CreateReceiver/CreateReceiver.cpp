#include "CreateReceiver.hpp"

using namespace std;

    CreateReceiver::CreateReceiver(){}

    vector<uint8_t> CreateReceiver::encode(){
        vector<uint8_t> toEncode;

        toEncode.push_back(getCookie()); //0
        toEncode.push_back((Opcode >> 8) & 0xFF);//1,2
        toEncode.push_back(Opcode & 0xFF); 
        toEncode.push_back((getPHY_ID() << 4)|(getCTRL_ID() & 0x0F)); //3
        toEncode.push_back((getBroadcastStandard() << 4)|(getReceiverMode() & 0x0F)); //4
        toEncode.push_back((getRfa() >> 8) & 0xFF);//5,6
        toEncode.push_back(getRfa() & 0xFF);

        return toEncode;
    };

    void CreateReceiver::decode(const vector<uint8_t>& toDecode){
        
        Cookie = (toDecode.at(0));
        //Opcode = ((toDecode.at(1) << 8)|(toDecode.at(2)));
        PHY_ID = (toDecode.at(3) >> 4) & 0x0F;
        CTRL_ID = (toDecode.at(3) & 0x0F);
        BroadcastStandard = (toDecode.at(4) >> 4) & 0x0F;
        ReceiverMode = (toDecode.at(4) & 0x0F);
        Rfa = ((toDecode.at(5) << 8) & 0xFF);
        Rfa = (toDecode.at(6) & 0xFF);
    };

    //Cookie Opcode1 Opcode2 PHY CTRL BS RM     Rfa
    //   0       1      2      3   3   4  4     5,6