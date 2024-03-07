#include<vector>
#include<cstdint>
#include"TunerPath.hpp"

using namespace std;

class SoC{
    private:
    uint8_t Rfa4;
    uint8_t SoC_ID;
    uint8_t SoC_Type;
    uint8_t NrOfTunerPaths;
    uint8_t NrOfNBTs;
    uint8_t NrOfDFEs;
    uint8_t CanDemodulateAM;
    uint8_t CanDemodulateFM;
    uint8_t CanDecodeHD;
    uint8_t CanDecodeDAB;
    uint8_t CanDecodeDRM;
    uint8_t CanDecodeCDR;
    uint8_t Rfa6;
    vector<TunerPath> tunerPathsVector;

    public:
    uint8_t getRfa4(){return Rfa4;}
    uint8_t getSOC_ID(){return SoC_ID;}
    uint8_t getSoC_Type(){return SoC_Type;}
    uint8_t getNrOfTunerPaths(){return NrOfTunerPaths;}
    uint8_t getNrOfNBTs(){return NrOfNBTs;}
    uint8_t getNrOfDFEs(){return NrOfDFEs;}
    uint8_t getCanDemodulateAM(){return CanDemodulateAM;}
    uint8_t getCanDemodulateFM(){return CanDemodulateFM;}
    uint8_t getCanDecodeHD(){return CanDecodeHD;}
    uint8_t getCanDecodeDAB(){return CanDecodeDAB;}
    uint8_t getCanDecodeDRM(){return CanDecodeDRM;}
    uint8_t getCanDecodeCDR(){return CanDecodeCDR;}
    uint8_t getRfa6(){return Rfa6;}
    vector<TunerPath> gettunerPathsVector(){return tunerPathsVector;}

    void setRfa4(uint8_t Rfa4_val){Rfa4 = Rfa4_val;}
    void setSOC_ID(uint8_t SOCID_val){SoC_ID = SOCID_val;}
    void setSoC_Type(uint8_t SOCType_val){SoC_Type = SOCType_val;}
    void setNrOfTunerPaths(uint8_t NrOfTunerpaths_val){NrOfTunerPaths = NrOfTunerpaths_val;}
    void setNrOfNBTs(uint8_t NrOfNBTs_val){NrOfNBTs = NrOfNBTs_val;}
    void setNrOfDFEs(uint8_t NrOfDFEs_val){NrOfDFEs = NrOfDFEs_val;}
    void setCanDemodulateAM(uint8_t CanDem_AM_val){CanDemodulateAM = CanDem_AM_val;}
    void setCanDemodulateFM(uint8_t CanDem_FM_val){CanDemodulateFM = CanDem_FM_val;}
    void setCanDecodeHD(uint8_t CanDecHD_val){CanDecodeHD = CanDecHD_val;}
    void setCanDecodeDAB(uint8_t CanDecDAB_val){CanDecodeDAB = CanDecDAB_val;}
    void setCanDecodeDRM(uint8_t CanDecDRM_val){CanDecodeDRM = CanDecDRM_val;}
    void setCanDecodeCDR(uint8_t CanDecCDR_val){CanDecodeCDR = CanDecCDR_val;}
    void setRfa6(uint8_t Rfa6_val){Rfa6 = Rfa6_val;}

    void addTunerPathInstance(TunerPath &pathObject);
};