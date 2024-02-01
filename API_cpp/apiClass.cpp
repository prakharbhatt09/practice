#include<iostream>
#include <string>
#include <vector>
#include "math.h"

using namespace std;

class RadioMessage{
    private:

    public:
    const uint8_t MessageType = 0;
    uint8_t Cookie;
    const uint16_t OpCode = 0x0204;
    uint8_t ReceiverHandle;
    uint8_t rfa{0};
    uint8_t NrOfAntennaHandles;
    uint8_t AntennaHandle;
    uint8_t rfa1;
    uint32_t rfa2;

    void repeatMessage(){
            for (int i=1; i<=NrOfAntennaHandles; i++)
                {
                   cout<<"AntennaHandle: "<<AntennaHandle<<endl;
                   cout<<"rfa1: "<<rfa1<< endl;
                }
    };

    void printParameters(){
            cout<<"MessageType: "<<MessageType<<endl;
            cout<<"Cookie: "<<Cookie<<endl;
            cout<<"OpCode: "<<OpCode<<endl;
            cout<<"ReceiverHandle: "<<ReceiverHandle<<endl;
            cout<<"rfa: "<<rfa<<endl;
            cout<<"rfa2: "<<rfa2<<endl;

    };

    int hex2dec(char hexValue){
        if (isdigit(hexValue)){
            return hexValue;
        }
        else{
            return toupper(hexValue) - 'A' + 10;
        }
    };

    string decode(){
        vector<uint32_t> vec_hex{RadioMessage::Cookie, RadioMessage::ReceiverHandle, RadioMessage::rfa, RadioMessage::NrOfAntennaHandles, RadioMessage::AntennaHandle, RadioMessage::rfa1, RadioMessage::rfa2};
        vector<uint32_t> vec_dec{};
        
        for (int i=0; i<vec_hex.size(); i++){
            vec_dec.push_back(hex2dec(vec_hex[i]));
        }
        return vec_dec;
    };

};

int main(){
    RadioMessage Message1;
        Message1.Cookie = 1;
        Message1.ReceiverHandle = 0x01;
        Message1.rfa = 0;
        Message1.NrOfAntennaHandles = 0x01;
        Message1.AntennaHandle = 0x45;
        Message1.rfa1 = 0;
        Message1.rfa2 = 0;
        
        Message1.decode();

}