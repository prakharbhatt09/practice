#ifndef RECEIVER_H
#define RECEIVER_H
#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

class Receiver{
    private:
    uint8_t ReceiverHandle;
    uint8_t BroadcastStandard; //4bitmsb
    uint8_t Mode; //4bitmsb
    uint16_t Rfa5;

    public:
    Receiver() = default;
    Receiver(uint8_t ReceiverHandle_val, uint8_t BroadcastStandard_val, uint8_t Mode_val, uint8_t Rfa5_val)
    :ReceiverHandle{ReceiverHandle_val}, BroadcastStandard{BroadcastStandard_val}, Mode{Mode_val}, Rfa5{Rfa5_val}{

    }
    
    uint8_t getReceiverHandle(){return ReceiverHandle;}
    uint8_t getBroadcastStandard(){return BroadcastStandard;}//4bitmsb
    uint8_t getMode(){return Mode;}//4bitmsb
    uint16_t getRfa5(){return Rfa5;}
    
    void setReceiverHandle(uint8_t u){ReceiverHandle = u;}
    void setBroadcastStandard(uint8_t v){BroadcastStandard = v;}//4bitmsb
    void setMode(uint8_t w){Mode = w;}//4bitmsb
    void setRfa5(uint8_t x){Rfa5 = x;}
};
#endif