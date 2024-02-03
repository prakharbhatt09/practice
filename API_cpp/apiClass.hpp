#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

class RadioMessage{
    private:
    vector<uint8_t> hex_val;
    
    public:
    const uint8_t MessageType = 0;
    uint8_t Cookie; //0
    const uint16_t OpCode = 0x0204;//1&2
    uint8_t ReceiverHandle;//3
    uint8_t rfa{0};
    uint8_t NrOfAntennaHandles;//4
    uint8_t AntennaHandle;//5
    uint8_t rfa1;//6
    uint32_t rfa2;//7

     void decode(const vector<uint8_t>& hex_val) {
        
        Cookie = hex_val.at(0);
        ReceiverHandle = hex_val.at(3);
        NrOfAntennaHandles = hex_val.at(4);
        AntennaHandle = hex_val.at(5);
        rfa1 = hex_val.at(6);
        
        cout << " " <<Cookie;
        cout << " " <<OpCode;
        cout << " "  <<ReceiverHandle;
        cout << " " <<NrOfAntennaHandles;
        //cout << "AntennaHandle: " <<AntennaHandle;
        //cout << "rfa1: " <<rfa1;
        //cout << "rfa2: " <<rfa2;
    };
};