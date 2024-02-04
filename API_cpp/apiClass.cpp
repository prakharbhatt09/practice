#include "apiClass.hpp"

using namespace std;

RadioMessage::RadioMessage() : Cookie(0), ReceiverHandle(0), NrOfAntennaHandles(0) {}
    
    vector<uint8_t> RadioMessage::encode() {
        vector<uint8_t> hex_val;
        hex_val.push_back(Cookie);
        hex_val.push_back((OpCode >> 8)& 0xFF); //check
        hex_val.push_back(ReceiverHandle);
        hex_val.push_back(NrOfAntennaHandles);
    
        for (uint8_t i = 0; i < NrOfAntennaHandles; i++) {
            hex_val.push_back(AntennaHandle[i]);
            hex_val.push_back(rfa1[i]);
        }
        return hex_val;
    };

    void RadioMessage::decode(const vector<uint8_t>& hex_val){
        Cookie = hex_val.at(0);
        ReceiverHandle = hex_val.at(3);
        NrOfAntennaHandles = hex_val.at(4);
        AntennaHandle.clear();
        rfa1.clear();
        //0x45 0x00 0x45 0x00  ?
    }