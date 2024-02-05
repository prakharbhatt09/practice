#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

class RadioMessage{
    public:
    const uint8_t MessageType = 0;
    uint8_t Cookie; //0
    const uint16_t OpCode = 0x0204;//1&2
    uint8_t ReceiverHandle;//3
    uint8_t rfa{0};
    uint8_t NrOfAntennaHandles;//4
    vector <uint8_t> AntennaHandle;//5
    vector <uint8_t> rfa1;//6
    uint32_t rfa2;//7,8,9,10

    RadioMessage();//set default
    RadioMessage(uint8_t Cookie_val,uint8_t ReceiverHandle_val,uint8_t NrOfAntennaHandles_val,uint8_t AntennaHandle_val,uint8_t rfa1_val)
        :Cookie{Cookie_val}, ReceiverHandle{ReceiverHandle_val}, NrOfAntennaHandles{NrOfAntennaHandles_val}, AntennaHandle{AntennaHandle_val}, rfa1{rfa1_val}{

    }
    vector<uint8_t> encode();
    void decode(const vector<uint8_t>& hex_val);
    ~RadioMessage();
};