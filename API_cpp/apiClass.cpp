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
        
        vector<string> hexValues = {to_string(Message1.Cookie), to_string(Message1.ReceiverHandle), to_string(Message1.rfa), to_string(Message1.NrOfAntennaHandles), to_string(Message1.AntennaHandle), to_string(Message1.rfa1), to_string(Message1.rfa2)};
        vector<uint32_t> decodedValues = Message1.decode(hexValues);
        cout<<"Decoded Values: ";
        for (uint32_t& v:decodedValues){
            cout<<v<<" ";
        }
        cout<<endl;

        vector<string> encodedValues = Message1.encode(decodedValues);
        cout<<"Encoded Values: ";
        for (string& v:encodedValues){
            cout<<hex<<v<<" ";
        }
        cout<<endl;



}       