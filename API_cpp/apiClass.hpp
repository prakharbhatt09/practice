#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

class RadioMessage{
    public:
    static const uint8_t MessageType = 0;
    uint8_t Cookie; //0
    static const uint16_t OpCode = 0x0204;//1&2
    uint8_t ReceiverHandle;//3
    uint8_t rfa{0};
    uint8_t NrOfAntennaHandles;//4
    vector <uint8_t> AntennaHandle;//5
    vector <uint8_t> rfa1;//6
    uint32_t rfa2;//7,8,9,10

    RadioMessage();
    vector<uint8_t> encode();
    void decode(const vector<uint8_t>& hex_val);
    
};