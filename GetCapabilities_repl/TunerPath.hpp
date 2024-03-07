#include<vector>
#include<cstdint>

using namespace std;

class TunerPath{
    private:
    uint8_t CanReceiveAM;
    uint8_t CanReceiveFM;
    uint8_t CanReceiveDAB;
    uint32_t Rfa5;
    uint8_t ProvidedAsExternal;

    public:
    uint8_t getCanReceiveAM(){return CanReceiveAM;}
    uint8_t getCanReceiveFM(){return CanReceiveFM;}
    uint8_t getCanReceiveDAB(){return CanReceiveDAB;}
    uint32_t getRfa5(){return Rfa5;}
    uint8_t getProvidedAsExternal(){return ProvidedAsExternal;}

    void setCanReceiveAM(uint8_t CanRecAM_val){CanReceiveAM = CanRecAM_val;}
    void setCanReceiveFM(uint8_t CanRecFM_val){CanReceiveFM = CanRecFM_val;}
    void setCanReceiveDAB(uint8_t CanRecDAB_val){CanReceiveDAB = CanRecDAB_val;}
    void setRfa5(uint32_t Rfa5_val){Rfa5 = Rfa5_val;}
    void setProvidedAsExternal(uint8_t pAsExternal_val){ProvidedAsExternal = pAsExternal_val;}

};