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
    uint8_t NrOfSoCs;
    uint32_t Rfa7;

    public:
    GetResourceUsage_repl();

        class SoC{
        private:
        uint8_t Rfa1;
        uint8_t SoC_ID; //4bitmsb
        uint8_t NrOfTunerPaths; //Max8
        uint32_t Rfa6;
        public:
        SoC();

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
        
                class NBT{
                private:
                uint8_t NBT_ix;
                uint8_t Assigned_DFE_ix;
                uint8_t Rfa4;

                public:
                NBT();

                uint8_t getNBT_ix(){return NBT_ix;}
                uint8_t getAssigned_DFE_ix(){return Assigned_DFE_ix;}
                uint8_t getRfa4(){return Rfa4;}

                void setNBT_ix(uint8_t p){NBT_ix = p;}
                void setAssigned_DFE_ix(uint8_t q){Assigned_DFE_ix = q;}
                void setRfa4(uint8_t r){Rfa4 = r;}

            };
            vector<NBT> nbts;
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

        };
            class DFE{
              private:
                uint8_t NrOfDFEs;//Max 8

              public:  
                DFE();

                class Receiver{
                    private:
                    uint8_t NrOfAssignedReceivers;//Max 8
                    uint8_t ReceiverHandle;
                    uint8_t BroadcastStandard; //4bitmsb
                    uint8_t Mode; //4bitmsb
                    uint16_t Rfa5;

                    public:
                    Receiver();
                    uint8_t getNrOfAssignedReceivers(){return NrOfAssignedReceivers;}
                    uint8_t getReceiverHandle(){return ReceiverHandle;}
                    uint8_t getBroadcastStandard(){return BroadcastStandard;}//4bitmsb
                    uint8_t getMode(){return Mode;}//4bitmsb
                    uint16_t getRfa5(){return Rfa5;}

                    void setNrOfAssignedReceivers(uint8_t t){NrOfAssignedReceivers = t;}
                    void setReceiverHandle(uint8_t u){ReceiverHandle = u;}
                    void setBroadcastStandard(uint8_t v){BroadcastStandard = v;}//4bitmsb
                    void setMode(uint8_t w){Mode = w;}//4bitmsb
                    void setRfa5(uint8_t x){Rfa5 = x;}
                };
                vector<Receiver> AssignedReceivers;

                uint8_t getNrOfDFEs(){return NrOfDFEs;}
                void setNrOfDFEs(uint8_t s){NrOfDFEs = s;}
            };
            vector<TunerPath> tunerPaths;
            vector<DFE> dfes;
            uint8_t getRfa1(){return Rfa1;}
            uint8_t getSoC_ID(){return SoC_ID;}//4bitmsb
            uint8_t getNrOfTunerPaths(){return NrOfTunerPaths;}
            uint32_t getRfa6(){return Rfa6;}

            void setRfa1(uint8_t e){Rfa1 = e;}
            void setSoC_ID(uint8_t f){SoC_ID = f;}
            void setNrOfTunerPaths(uint8_t g){NrOfTunerPaths = g;}
            void setRfa6(uint8_t y){Rfa6 = y;}
    };
    vector<SoC> socs;
    
    uint8_t getCookie(){return Cookie;}
    uint8_t getReplyStatus(){return ReplyStatus;}
    uint8_t getRfa(){return Rfa;}
    uint8_t getNrOfSoCs(){return NrOfSoCs;}//4bitmsb
    uint32_t getRfa7(){return Rfa7;}
    void setCookie(uint8_t a){Cookie = a;}
    void setReplyStatus(uint8_t b){ReplyStatus = b;}
    void setRfa(uint8_t c){Rfa = c;}
    void setNrOfSoCs(uint8_t d){NrOfSoCs = d;}
    void setRfa7(uint32_t z){Rfa7 = z;}

    vector<uint8_t> encode();
    void decode(const vector<uint8_t>& toDecode);

};
