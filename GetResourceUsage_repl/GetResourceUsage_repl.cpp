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
            toEncode.push_back((tunerPath.getActive()<<7)|(tunerPath.getActiveNBTs() & 0x0F));//8 check?
            toEncode.push_back((tunerPath.getAntennaPort()<<4)|(tunerPath.getRfa3()));//9
                                                            
            for(uint8_t k=0; k<tunerPath.getActiveNBTs(); k++){
                auto &nbt = tunerPath.nbts.at(k);
                toEncode.push_back(nbt.getNBT_ix());//10
                toEncode.push_back(nbt.getAssigned_DFE_ix());//11
                toEncode.push_back(nbt.getRfa4()>>8 & 0xFF);//12
                toEncode.push_back(nbt.getRfa4() & 0xFF);//13

                }
        }
            toEncode.push_back(soc.getNrOfDFEs());//14
            for(uint8_t m=0; m<soc.getNrOfDFEs(); m++){
                auto &dfe = soc.dfes.at(m);
                toEncode.push_back(dfe.getNrOfAssignedReceivers());//15

                for(uint8_t n=0; n<dfe.getNrOfAssignedReceivers(); n++){
                    auto &rec = dfe.AssignedReceivers.at(n);
                    toEncode.push_back(rec.getReceiverHandle());//16
                    toEncode.push_back((rec.getBroadcastStandard()<<4)|(rec.getMode() & 0x0F));//17
                    toEncode.push_back(rec.getRfa5()>>8 & 0xFF);//18
                    toEncode.push_back(rec.getRfa5() & 0xFF);//19
                }
            }
        toEncode.push_back(soc.getRfa6() & 0xFF);//20,21,22,23
        toEncode.push_back((soc.getRfa6()>>8) & 0xFF);
        toEncode.push_back((soc.getRfa6()>>16) & 0xFF);
        toEncode.push_back((soc.getRfa6()>>24) & 0xFF);
    }
    toEncode.push_back(getRfa7() & 0xFF);//24,25,26,27
    toEncode.push_back((getRfa7()>>8) & 0xFF);
    toEncode.push_back((getRfa7()>>16) & 0xFF);
    toEncode.push_back((getRfa7()>>24) & 0xFF);
    
    return toEncode;
};

void GetResourceUsage_repl::decode(const vector<uint8_t>& toDecode){
    
    setCookie((toDecode.at(0)) & 0x0F);
    setReplyStatus(toDecode.at(3));
    setRfa((toDecode.at(4)) >> 4);
    setNrOfSoCs(toDecode.at(4) & 0x0F);
    int index = 5;
    
    for(uint8_t i=0; i<NrOfSoCs; i++){
        SoC soc;
        soc.setRfa1((toDecode.at(index))>>4);//5
        soc.setSoC_ID((toDecode.at(index) & 0x0F));//5
        soc.setNrOfTunerPaths(toDecode.at(index++));//6

        for(uint8_t j=0; j<soc.getNrOfTunerPaths(); j++){
            TunerPath path;
            path.setAntennaHandle(toDecode.at(index++));//7
            int extractAtIndex_1 = index++;
            path.setActive(toDecode.at(extractAtIndex_1)>>1);//8,check?
            path.setRfa2(toDecode.at(extractAtIndex_1)>>3);//8
            path.setActiveNBTs((toDecode.at(extractAtIndex_1)>>4));//8
            int extractAtIndex_2 = index++;
            path.setAntennaPort(toDecode.at(extractAtIndex_2)>>4);//9
            path.setRfa3((toDecode.at(extractAtIndex_2)>>4) & 0x0F);//9

            for(uint8_t k=0; k<path.getActiveNBTs(); k++){
                NBT nbt;
                nbt.setNBT_ix(toDecode.at(index++));//10
                nbt.setAssigned_DFE_ix(toDecode.at(index++));//11
                nbt.setRfa4(((toDecode.at(index++)<<8) & 0xFF)|((toDecode.at(index++) & 0xFF)));//12,13
                path.addNBTInstance(nbt);
            }
            soc.addtunerPathInstance(path);
        }
        soc.setNrOfDFEs(toDecode.at(index++));//14
        for(uint8_t x=0; x<soc.getNrOfDFEs(); x++){
            DFE dfe;
            dfe.setNrOfAssignedReceivers(toDecode.at(index++));//15

            for(uint8_t y=0; y<dfe.getNrOfAssignedReceivers(); y++){
                Receiver rec;
                rec.setReceiverHandle(toDecode.at(index++));//16
                int extractAtIndex_3 = index++;
                rec.setBroadcastStandard((toDecode.at(extractAtIndex_3))>>4);//17
                rec.setMode((toDecode.at(extractAtIndex_3)) & 0x0F);//17
                rec.setRfa5(((toDecode.at(index++)<<8) & 0xFF)|(toDecode.at(index++) & 0xFF));//18,19
                dfe.addReceiverInstance(rec);
            }
            soc.addDFEInstance(dfe);
        }
        soc.setRfa6((toDecode.at(index++)<<24)|(toDecode.at(index++)<<16)|(toDecode.at(index++)<<8)|(toDecode.at(index++)));//20,21,22,23
        addsocInstance(soc);
    }
    setRfa7((toDecode.at(index++)<<24)|(toDecode.at(index++)<<16)|(toDecode.at(index++)<<8)|(toDecode.at(index++)));//24,25,26,27
};