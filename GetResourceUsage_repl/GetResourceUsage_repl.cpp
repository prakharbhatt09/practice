#include "GetResourceUsage_repl.hpp"

using namespace std;

GetResourceUsage_repl::GetResourceUsage_repl(){}

vector<uint8_t> GetResourceUsage_repl::encode(){
    vector<uint8_t> toEncode;
    toEncode.push_back(getCookie());//0
    toEncode.push_back((Opcode>>8) & 0xFF);//1
    toEncode.push_back(Opcode & 0xFF);//2
    toEncode.push_back(getReplyStatus());//3
    toEncode.push_back(getRfa());//4
    toEncode.push_back(getNrOfSoCs() & 0x0F);//5-uimsbf-4bit in 1 byte
    
    for(uint8_t i=0; i<(getNrOfSoCs()); i++){
        //toEncode.push_back((getRfa1().at(i)));//one byte
        //toEncode.push_back(((getSoC_ID().at(i))<<4) & 0x0F);//one byte
        toEncode.push_back((getRfa1().at(i)<<4)|(getSoC_ID().at(i) & 0x0F));//6
        toEncode.push_back((getNrOfTunerPaths().at(i)));//7
    
        for(uint8_t j=0; j<size(getNrOfTunerPaths()); j++){
            toEncode.push_back(getAntennaHandle().at(j));
            toEncode.push_back(getActive().at(j));
            toEncode.push_back(getRfa2().at(j));
            toEncode.push_back((getActiveNBTs().at(j)<<4)|(getAntennaPort().at(j) & 0x0F));//-uimsbf-4bit in 1 byte
            toEncode.push_back(getRfa3().at(j));
        
            for(uint8_t k=0; k<size(getActiveNBTs()); k++){
                toEncode.push_back(getNBT_ix().at(k));
                toEncode.push_back(getAssigned_DFE_ix().at(k));
                toEncode.push_back((getRfa4().at(k)>>8)|((getRfa4().at(k)>>16) & 0xFF));
            }
        }
    }/*
            toEncode.push_back(getNrOfDFEs());
            for(uint8_t x=0; x<getNrOfDFEs(); x++){
                toEncode.push_back(getNrOfAssignedReceivers().at(x));

                    for(uint8_t y=0; y<size(getNrOfAssignedReceivers()); y++){
                        toEncode.push_back(getReceiverHandle().at(y));
                        toEncode.push_back((getBroadcastStandard().at(y)<<4)|(getMode().at(y) & 0x0F));
                        toEncode.push_back((getRfa5().at(y)>>8)|((getRfa5().at(y)>>16) & 0xFF));
                    }
            }
            toEncode.push_back((getRfa6().at(0) >> 24) & 0xFF);
            toEncode.push_back((getRfa6().at(1) >> 16) & 0xFF);
            toEncode.push_back((getRfa6().at(2) >> 8) & 0xFF);
            toEncode.push_back(getRfa6().at(3) & 0xFF);
    }
    toEncode.push_back((getRfa7().at(0) >> 24) & 0xFF);
    toEncode.push_back((getRfa7().at(1) >> 16) & 0xFF);
    toEncode.push_back((getRfa7().at(2) >> 8) & 0xFF);
    toEncode.push_back(getRfa7().at(3) & 0xFF);*/

    return toEncode;
};