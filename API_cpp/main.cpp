#include "apiClass.hpp"

using namespace std;

int main()
{
    RadioMessage message1(0x02,0x01,0x01,0x45,0x00);
    vector<uint8_t> hexValues = {0x01, 0x02, 0x04, 0x01, 0x01, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00};
    message1.decode(hexValues);

    cout<<"Decoded Cookie:"<<hex<<static_cast<uint8_t>(message1.Cookie);

    RadioMessage message2(0x01,0x01,0x01,0x45,0x00);

    //message2.Cookie = 0x01;
    //message2.ReceiverHandle = 0x01;
    //message2.NrOfAntennaHandles = 0x01;
    //message2.AntennaHandle.push_back(0x45);
    //message2.rfa1.push_back(0x00);

    vector<uint8_t> encoded_msg = message2.encode();

    for (auto i : encoded_msg) {
        cout<<hex<<static_cast<uint8_t>(i)<<" ";
    }
    cout << endl;

    return 0;
}