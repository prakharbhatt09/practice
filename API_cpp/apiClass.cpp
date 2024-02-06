#include "apiClass.hpp"

using namespace std;

    RadioMessage::RadioMessage(){}

     vector<uint8_t> RadioMessage::encode() {
        vector<uint8_t> hex_val;
        hex_val.clear();
        hex_val.push_back(Cookie);
        hex_val.push_back((OpCode >> 8)& 0xFF); //check
        hex_val.push_back(OpCode & 0xFF); 
        hex_val.push_back(ReceiverHandle);
        hex_val.push_back(NrOfAntennaHandles);
    /*
        for (uint8_t i = 0; i < NrOfAntennaHandles; i++) {
            hex_val.push_back(AntennaHandle.at(i));
            hex_val.push_back(rfa1.at(i));
        }
         */
        for (uint8_t i:hex_val){
            cout<<uint8_t(i)<<" ";
        }

        return hex_val;
        
    };

     void RadioMessage::decode(const vector<uint8_t>& hex_val){
        Cookie = hex_val.at(0);
        ReceiverHandle = hex_val.at(3);
        NrOfAntennaHandles = hex_val.at(4);
        AntennaHandle.clear();
        rfa1.clear();
        /*
        for (uint8_t i = 0; i<NrOfAntennaHandles; i++){
            AntennaHandle.push_back(hex_val.at((2*i)+5));
            rfa1.push_back(hex_val.at((2*i)+6));
        }*/
    };