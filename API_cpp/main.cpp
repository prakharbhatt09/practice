#include "apiClass.hpp"

int main(){
{
    RadioMessage Message1;
        cout<<"Message1 attributes"<<endl;
        Message1.Cookie = 1;
        Message1.ReceiverHandle = 0x01;
        Message1.rfa = 0;
        Message1.NrOfAntennaHandles = 0x01;
        Message1.AntennaHandle = 0x45;
        Message1.rfa1 = 0;
        Message1.rfa2 = 0;

        Message1.printParameters();
        //Message1.repeatMessage();

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
{
    RadioMessage Message2;
        cout<<"Message2 attributes"<<endl;
        Message2.Cookie = 1;
        Message2.ReceiverHandle = 0x01;
        Message2.rfa = 0;
        Message2.NrOfAntennaHandles = 0x01;
        Message2.AntennaHandle = 0x45;
        Message2.rfa1 = 1;
        Message2.rfa2 = 11;

        Message2.printParameters();
        //Message2.repeatMessage();
        vector<string> hexValues = {to_string(Message2.Cookie), to_string(Message2.ReceiverHandle), to_string(Message2.rfa), to_string(Message2.NrOfAntennaHandles), to_string(Message2.AntennaHandle), to_string(Message2.rfa1), to_string(Message2.rfa2)};
        vector<uint32_t> decodedValues = Message2.decode(hexValues);
            cout<<"Decoded Values: ";
            for (uint32_t& v:decodedValues){
                cout<<v<<" ";
            }
            cout<<endl;

        vector<string> encodedValues = Message2.encode(decodedValues);
            cout<<"Encoded Values: ";
            for (string& v:encodedValues){
                cout<<hex<<v<<" ";
            }
            cout<<endl;

}
}       