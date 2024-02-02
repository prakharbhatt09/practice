#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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
            cout<<"NrOfAntennaHandles: "<<NrOfAntennaHandles<<endl;

    };

    vector<uint32_t> decode(vector<string>& vec_hex){
        vector<uint32_t> vec_dec;
        
        for (auto i:vec_hex){
            uint32_t hex2dec = stoul(i, nullptr, 16);
            vec_dec.push_back(hex2dec);
        }
        return vec_dec;
    };

    vector<string> encode(vector<uint32_t>& vec_dec){
        vector<string> vec_hex;

        for (auto i:vec_dec){
            stringstream ss;
            ss<<hex<<i;
            vec_hex.push_back(ss.str());
        }
        return vec_hex;
    }
    ~RadioMessage(){}


};


