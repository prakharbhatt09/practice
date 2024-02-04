#include "apiClass.hpp"

using namespace std;

int main() {
    RadioMessage message1;

    message1.Cookie = 0x01;
    message1.ReceiverHandle = 0x01;
    message1.NrOfAntennaHandles = 0x01;
    //message1.AntennaHandle.push_back(0x45);
    //message1.rfa1.push_back(0x00);

    vector<uint8_t> encoded_msg = message1.encode();

    for (auto i : encoded_msg) {
        cout<<hex<<static_cast<uint8_t>(i)<<" ";
    }
    cout << endl;

    RadioMessage message2;
    vector<uint8_t> hexValues = {0x01, 0x02, 0x04, 0x01, 0x01, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00};
    message2.decode(hexValues);
    cout<<"Decoded Cookie:"<<hex<<static_cast<uint8_t>(message2.Cookie);

    return 0;
}