#include "GetResourceUsage_repl.hpp"
#include "SoC.hpp"
#include "TunerPath.hpp"
#include "NBT.hpp"
#include "DFE.hpp"
#include "Receiver.hpp"

using namespace std;

void GetResourceUsage_repl::addsocInstance(SoC &socObject){
    socs.push_back(socObject);
};

vector<uint8_t> GetResourceUsage_repl::encode(){
    vector<uint8_t> toEncode;

    toEncode.push_back(((MessageType<<1))|(getCookie() & 0x0F));//0
    toEncode.push_back((Opcode>>8) & 0xFF);//1
    toEncode.push_back(Opcode & 0xFF);//2
    toEncode.push_back(getReplyStatus());//3
    toEncode.push_back((getRfa()<<4)|(getNrOfSoCs() & 0x0F)); //4

    for(uint8_t i=0; i<getNrOfSoCs(); i++){
        auto &soc = socs.at(i);
        toEncode.push_back((soc.getRfa1())|(soc.getSoC_ID()));//5
        toEncode.push_back(soc.getNrOfTunerPaths());//6

        for(uint8_t j=0; j<soc.getNrOfTunerPaths(); j++){
            auto &tunerPath = soc.tunerPaths.at(j);
            toEncode.push_back(tunerPath.getAntennaHandle());//7
            toEncode.push_back((tunerPath.getActive()<<1)|(tunerPath.getRfa2()<<3)|(tunerPath.getActiveNBTs()<<4 & 0x0F));
                                                            //8
            for(uint8_t k=0; k<tunerPath.getActiveNBTs(); k++){
                auto &nbt = tunerPath.nbts.at(k);
                toEncode.push_back(nbt.getNBT_ix());//9
                toEncode.push_back(nbt.getAssigned_DFE_ix());//10
                toEncode.push_back(nbt.getRfa4()>>8 & 0xFF);//11
                toEncode.push_back(nbt.getRfa4() & 0xFF);//12

                }
        }
            toEncode.push_back(soc.getNrOfDFEs());//13
            for(uint8_t m=0; m<soc.getNrOfDFEs(); m++){
                auto &dfe = soc.dfes.at(m);
                toEncode.push_back(dfe.getNrOfAssignedReceivers());//14

                for(uint8_t n=0; n<dfe.getNrOfAssignedReceivers(); n++){
                    auto &rec = dfe.AssignedReceivers.at(n);
                    toEncode.push_back(rec.getReceiverHandle());//15
                    toEncode.push_back((rec.getBroadcastStandard()<<4)|(rec.getMode()<<4 & 0x0F));//16
                    toEncode.push_back(rec.getRfa5()>>8 & 0xFF);//17
                    toEncode.push_back(rec.getRfa5() & 0xFF);//18
                }
            }
        toEncode.push_back(soc.getRfa6() & 0xFF);
        toEncode.push_back((soc.getRfa6()>>8) & 0xFF);
        toEncode.push_back((soc.getRfa6()>>16) & 0xFF);
        toEncode.push_back((soc.getRfa6()>>24) & 0xFF);
    }
    toEncode.push_back(getRfa7() & 0xFF);
    toEncode.push_back((getRfa7()>>8) & 0xFF);
    toEncode.push_back((getRfa7()>>16) & 0xFF);
    toEncode.push_back((getRfa7()>>24) & 0xFF);
    
    return toEncode;
};