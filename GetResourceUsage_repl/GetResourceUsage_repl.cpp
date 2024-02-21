#include "GetResourceUsage_repl.hpp"

using namespace std;

GetResourceUsage_repl message1;

vector<uint8_t> GetResourceUsage_repl::encode(){
    vector<uint8_t> toEncode;
    toEncode.push_back(getCookie());
    toEncode.push_back((Opcode>>8) & 0xFF);
    toEncode.push_back(Opcode & 0xFF);
    toEncode.push_back(getReplyStatus());
    toEncode.push_back((getRfa()<<4)|(getNrOfSoCs() & 0x0F)); 

    for (uint8_t i=0; i<getNrOfSoCs(); i++) {
        auto &soc = socs.at(i);

        toEncode.push_back((soc.getRfa1() << 4) | (soc.getSoC_ID() & 0x0F));
        toEncode.push_back(soc.getNrOfTunerPaths());    

        for(uint8_t j=0; j<soc.getNrOfTunerPaths(); j++){
            auto &tunerPath = soc.tunerPaths.at(j);

            toEncode.push_back(tunerPath.getAntennaHandle());
            toEncode.push_back(tunerPath.getActive()<<1|(tunerPath.getRfa2()<<3)|(tunerPath.getActiveNBTs() & 0x0F));
            toEncode.push_back((tunerPath.getAntennaPort()<<4)|(tunerPath.getRfa3() & 0x0F));

            for(uint8_t k=0; k<tunerPath.getActiveNBTs(); k++){
                auto &nbt = tunerPath.nbts.at(k);

                toEncode.push_back(nbt.getNBT_ix());
                toEncode.push_back(nbt.getAssigned_DFE_ix());
                toEncode.push_back(nbt.getRfa4()>>8);
                toEncode.push_back(nbt.getRfa4() & 0xFF);
            }
        }
        toEncode.push_back(soc.getNrOfDFEs());
        for(uint8_t m=0; m<soc.getNrOfDFEs();){
            auto &dfe = soc.dfes.at(m);

            toEncode.push_back(dfe.getNrOfAssignedReceivers());

            for(uint8_t n=0; n<dfe.getNrOfAssignedReceivers(); n++){
                auto &receiver = dfe.AssignedReceivers.at(n);

                toEncode.push_back(receiver.getReceiverHandle());
                toEncode.push_back((receiver.getBroadcastStandard()<<4)|(receiver.getMode() & 0x0F));
                toEncode.push_back(receiver.getRfa5()>>8);
                toEncode.push_back(receiver.getRfa5() & 0xFF);

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
};