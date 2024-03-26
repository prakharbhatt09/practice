#ifndef RECEIVER_H
#define RECEIVER_H

#include <vector>
#include <cstdint>
#include "Antenna.hpp"

using namespace std;

class I_Receiver{
    public:
    virtual void addAntennaHandleInstance(I_Antenna &AntennaHandleObject) = 0;

    virtual ~I_Receiver(){};
};

class Receiver : public I_Receiver{
    private:
    uint8_t ReceiverHandle;
    uint8_t PHY_ID;
    uint8_t CTRL_ID;
    uint8_t BroadcastStandard;
    uint8_t ReceiverMode;
    uint8_t ReceiverState;
    uint8_t Rfa2;
    uint8_t NrOfAntennaHandles;
    uint32_t Rfa4;
    vector<I_Antenna*> AntennaHandlesVector;

    public:
    uint8_t getReceiverHandle(){return ReceiverHandle;}
    uint8_t getPHY_ID(){return PHY_ID;}
    uint8_t getCTRL_ID(){return CTRL_ID;}
    uint8_t getBroadcastStandard(){return BroadcastStandard;}
    uint8_t getReceiverMode(){return ReceiverMode;}
    uint8_t getReceiverState(){return ReceiverState;}
    uint8_t getRfa2(){return Rfa2;}
    uint8_t getNrOfAntennaHandles(){return NrOfAntennaHandles;}
    uint32_t getRfa4(){return Rfa4;}
    vector<I_Antenna*> getAntennaHandlesVector(){return AntennaHandlesVector;}

    void setReceiverHandle(uint8_t ReceiverHandle_val){ReceiverHandle = ReceiverHandle_val;}
    void setPHY_ID(uint8_t PHY_ID_val){PHY_ID = PHY_ID_val;}
    void setCTRL_ID(uint8_t CTRL_ID_val){CTRL_ID = CTRL_ID_val;}
    void setBroadcastStandard(uint8_t BroadcastStandard_val){BroadcastStandard = BroadcastStandard_val;}
    void setReceiverMode(uint8_t ReceiverMode_val){ReceiverMode = ReceiverMode_val;}
    void setReceiverState(uint8_t ReceiverState_val){ReceiverState = ReceiverState_val;}
    void setRfa2(uint8_t Rfa2_val){Rfa2 = Rfa2_val;}
    void setNrOfAntennaHandles(uint8_t NrOfAntennaHandles_val){NrOfAntennaHandles = NrOfAntennaHandles_val;}
    void setRfa4(uint32_t Rfa4_val){Rfa4 = Rfa4_val;}
    void addAntennaHandleInstance(I_Antenna &AntennaHandleObject) override;
};
#endif