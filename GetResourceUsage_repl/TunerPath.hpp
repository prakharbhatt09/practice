#ifndef tunerPath_H
#define tunerPath_H

#include <iostream>
#include <vector>
#include <cstdint>
#include "NBT.hpp"

using namespace std;

class TunerPath{
    private:
    uint8_t AntennaHandle;
    uint8_t Active;
    uint8_t Rfa2;
    uint8_t ActiveNBTs;
    uint8_t AntennaPort;
    uint8_t Rfa3;

    public:
    TunerPath();  
    TunerPath(uint8_t AntennaHandle_val, uint8_t Active_val, uint8_t Rfa2_val, uint8_t ActiveNBTs_val, uint8_t AntennaPort_val, uint8_t Rfa3_val)
        :AntennaHandle{AntennaHandle_val}, Active{Active_val}, Rfa2{Rfa2_val}, ActiveNBTs{ActiveNBTs_val}, AntennaPort{AntennaPort_val}, Rfa3{Rfa3_val}{

    }

    uint8_t getAntennaHandle(){return AntennaHandle;}
    uint8_t getActive(){return Active;}
    uint8_t getRfa2(){return Rfa2;}
    uint8_t getActiveNBTs(){return ActiveNBTs;}//4bitmsb
    uint8_t getAntennaPort(){return AntennaPort;}//4bitmsb
    uint8_t getRfa3(){return Rfa3;}

    void setAntennaHandle(uint8_t h){AntennaHandle = h;}
    void setActive(uint8_t i){Active = i;}
    void setRfa2(uint8_t j){Rfa2 = j;}
    void setActiveNBTs(uint8_t k){ActiveNBTs = k;}//4bitmsb
    void setAntennaPort(uint8_t m){AntennaPort = m;}//4bitmsb
    void setRfa3(uint8_t n){Rfa3 = n;}  

    void addtunerPathInstance(TunerPath);
    vector<NBT> nbts;
};
#endif