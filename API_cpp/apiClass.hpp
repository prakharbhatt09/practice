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
        // Decode the byte sequence
        Cookie = hex_val.at(0);
        ReceiverHandle = hex_val.at(3);
        NrOfAntennaHandles = hex_val.at(4);
        AntennaHandle = hex_val.at(5);
        rfa1 = hex_val.at(6);
        // Combining 4 bytes for rfa2, assuming little-endian format
        rfa2 = (uint32_t(hex_val.at(9)) << 24) | (uint32_t(hex_val.at(8)) << 16) |
               (uint32_t(hex_val.at(7)) << 8) | uint32_t(hex_val.at(6));

        // Immediately print the bitstream for each attribute
        cout << " " << bitset<8>(Cookie);
        cout << " " << bitset<16>(OpCode);
        cout << " "  << bitset<8>(ReceiverHandle);
        cout << " " << bitset<8>(NrOfAntennaHandles);
        //cout << "AntennaHandle: " << bitset<8>(AntennaHandle);
        //cout << "rfa1: " << bitset<8>(rfa1);
        //cout << "rfa2: " << bitset<32>(rfa2);
    }
};