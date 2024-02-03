#include "apiClass.hpp"

int main(){
   RadioMessage message1;
    std::vector<uint8_t> hexValues{0x01, 0x02, 0x04, 0x01, 0x01, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00};
    
    message1.Cookie = 0x01;
    message1.ReceiverHandle = 0x01;
    message1.NrOfAntennaHandles = 0x45;
    message1.rfa1 = 0x00;

    message1.decode(hexValues);
  
}