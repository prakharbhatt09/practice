#ifndef GETRESOURCEUSAGE_REPL_H
#define GETRESOURCEUSAGE_REPL_H
#include <iostream>
#include <vector>
#include <cstdint>
#include "SoC.hpp"

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
    GetResourceUsage_repl() = default;
    GetResourceUsage_repl(uint8_t Cookie_val, uint8_t ReplyStatus_val, uint8_t Rfa_val, uint8_t NrOfSoCs_val, uint8_t Rfa7_val)
                    :Cookie{Cookie_val}, ReplyStatus{ReplyStatus_val},  Rfa{Rfa_val}, NrOfSoCs{NrOfSoCs_val}, Rfa7{Rfa7_val}{
                    }

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
    
    vector<SoC> socs;

    void addsocInstance(SoC &socObject);

    vector<uint8_t> encode();
    void decode(const vector<uint8_t>& toDecode);

};
#endif