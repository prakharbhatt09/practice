#ifndef SoC_H
#define SoC_H

#include <iostream>
#include <vector>
#include <cstdint>
#include "TunerPath.hpp"
#include "DFE.hpp"

using namespace std;

class SoC{
    private:
    uint8_t Rfa1;
    uint8_t SoC_ID; //4bitmsb
    uint8_t NrOfTunerPaths; //Max8
    uint8_t NrOfDFEs; //Max8
    uint32_t Rfa6;

    public:
    SoC() = default;
    SoC(uint8_t Rfa1_val, uint8_t SoC_ID_val, uint8_t NrOfTunerPaths_val, uint8_t NrOfDFEs_val, uint8_t Rfa6_val)
      :Rfa1{Rfa1_val}, SoC_ID{SoC_ID_val}, NrOfTunerPaths{NrOfTunerPaths_val}, NrOfDFEs{NrOfDFEs_val}, Rfa6{Rfa6_val}{
    }

    uint8_t getRfa1(){return Rfa1;}
    uint8_t getSoC_ID(){return SoC_ID;}//4bitmsb
    uint8_t getNrOfTunerPaths(){return NrOfTunerPaths;}
    uint8_t getNrOfDFEs(){return NrOfDFEs;}
    uint32_t getRfa6(){return Rfa6;}

    void setRfa1(uint8_t e){Rfa1 = e;}
    void setSoC_ID(uint8_t f){SoC_ID = f;}
    void setNrOfTunerPaths(uint8_t g){NrOfTunerPaths = g;}
    void setNrOfDFEs(uint8_t s){NrOfDFEs = s;}
    void setRfa6(uint8_t y){Rfa6 = y;}

    vector<TunerPath> tunerPaths;
    vector<DFE> dfes;

    void addtunerPathInstance(TunerPath &tunerPathObject);
    void addDFEInstance(DFE &DFEObject);
};
#endif