#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

class GetResourceUsage_repl{
    private:
    const uint8_t MessageType{0};
    uint8_t Cookie;
    const uint16_t Opcode{0x0203};
    uint8_t ReplyStatus;
    uint8_t Rfa;
    uint8_t NrOfSoCs; //4bitmsb
    vector<uint8_t> Rfa1;
    vector<uint8_t> SoC_ID; //4bitmsb
    vector<uint8_t> NrOfTunerPaths;
    vector<uint8_t> AntennaHandle;
    vector<uint8_t> Active;
    vector<uint8_t> Rfa2;
    vector<uint8_t> ActiveNBTs; //4bitmsb
    vector<uint8_t> AntennaPort; //4bitmsb
    vector<uint8_t> Rfa3;
    vector<uint8_t> NBT_ix;
    vector<uint8_t> Assigned_DFE_ix;
    vector<uint8_t> Rfa4;
    uint8_t NrOfDFEs;//
    vector<uint8_t> NrOfAssignedReceivers;
    vector<uint8_t> ReceiverHandle;
    vector<uint8_t> BroadcastStandard; //4bitmsb
    vector<uint8_t> Mode; //4bitmsb
    vector<uint16_t> Rfa5;
    vector<uint32_t> Rfa6;
    vector<uint32_t> Rfa7;

    public:
    
    GetResourceUsage_repl();

    vector<uint8_t> encode();
    void decode(const vector<uint8_t>& toDecode);

    uint8_t getCookie(){return Cookie;}
    uint8_t getReplyStatus(){return ReplyStatus;}
    uint8_t getRfa(){return Rfa;}
    uint8_t getNrOfSoCs(){return NrOfSoCs;}//4bitmsb
    vector<uint8_t> getRfa1(){return Rfa1;}
    vector<uint8_t> getSoC_ID(){return SoC_ID;}//4bitmsb
    vector<uint8_t> getNrOfTunerPaths(){return NrOfTunerPaths;}
    vector<uint8_t> getAntennaHandle(){return AntennaHandle;}
    vector<uint8_t> getActive(){return Active;}
    vector<uint8_t> getRfa2(){return Rfa2;}
    vector<uint8_t> getActiveNBTs(){return ActiveNBTs;}//4bitmsb
    vector<uint8_t> getAntennaPort(){return AntennaPort;}//4bitmsb
    vector<uint8_t> getRfa3(){return Rfa3;}
    vector<uint8_t> getNBT_ix(){return NBT_ix;}
    vector<uint8_t> getAssigned_DFE_ix(){return Assigned_DFE_ix;}
    vector<uint8_t> getRfa4(){return Rfa4;}
    uint8_t getNrOfDFEs(){return NrOfDFEs;}
    vector<uint8_t> getNrOfAssignedReceivers(){return NrOfAssignedReceivers;}
    vector<uint8_t> getReceiverHandle(){return ReceiverHandle;}
    vector<uint8_t> getBroadcastStandard(){return BroadcastStandard;}//4bitmsb
    vector<uint8_t> getMode(){return Mode;}//4bitmsb
    vector<uint16_t> getRfa5(){return Rfa5;}
    vector<uint32_t> getRfa6(){return Rfa6;}
    vector<uint32_t> getRfa7(){return Rfa7;}

    void setCookie(uint8_t a){Cookie = a;}
    void setReplyStatus(uint8_t b){ReplyStatus = b;}
    void setRfa(uint8_t c){Rfa = c;}
    void setNrOfSoCs(uint8_t d){NrOfSoCs = d;}
    void setRfa1(uint8_t e){Rfa1.push_back(e);}
    void setSoC_ID(uint8_t f){SoC_ID.push_back(f);}
    void setNrOfTunerPaths(uint8_t g){NrOfTunerPaths.push_back(g);}
    void setAntennaHandle(uint8_t h){AntennaHandle.push_back(h);}
    void setActive(uint8_t i){Active.push_back(i);}
    void setRfa2(uint8_t j){Rfa2.push_back(j);}

    void setActiveNBTs(uint8_t k){ActiveNBTs.push_back(k);}//4bitmsb
    void setAntennaPort(uint8_t m){AntennaPort.push_back(m);}//4bitmsb
    void setRfa3(uint8_t n){Rfa3.push_back(n);}
    void setNBT_ix(uint8_t p){NBT_ix.push_back(p);}
    void setAssigned_DFE_ix(uint8_t q){Assigned_DFE_ix.push_back(q);}
    void setRfa4(uint8_t r){Rfa4.push_back(r);}
    void setNrOfDFEs(uint8_t s){NrOfDFEs = s;}
    void setNrOfAssignedReceivers(uint8_t t){NrOfAssignedReceivers.push_back(t);}
    void setReceiverHandle(uint8_t u){ReceiverHandle.push_back(u);}
    void setBroadcastStandard(uint8_t v){BroadcastStandard.push_back(v);}//4bitmsb
    void setMode(uint8_t w){Mode.push_back(w);}//4bitmsb
    void setRfa5(uint8_t x){Rfa5.push_back(x);}
    void setRfa6(uint8_t y){Rfa6.push_back(y);}
    void setRfa7(uint32_t z){Rfa7.push_back(z);}

};