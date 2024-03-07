#include<vector>
#include<cstdint>
#include"GetCapabilities_repl.hpp"

void GetCapabilities_repl::addStandardInstance(Standard &standardObject){
    standardsVector.push_back(standardObject);
};

void GetCapabilities_repl::addSoCInstance(SoC &socObject){
    socsVector.push_back(socObject);
}

void GetCapabilities_repl::decode(const vector<uint8_t> &toDecode){
    
    setMessageType(toDecode.at(0)>>7);
    setCookie(toDecode.at(0) & 0x3F);
    setReplyStatus(toDecode.at(3));
    setNrOfStandards(toDecode.at(4)>>4);
    setNrOfSoCs(toDecode.at(4) &0x0F);

    int index = 4;

        for(uint8_t i=0; i<getNrOfStandards(); i++){
            Standard standardObject;
                index++;
                standardObject.setRfa1((toDecode.at(index))>>4);
                standardObject.setbroadcastStandard((toDecode.at(index)) & 0x0F);
                standardObject.setcreatableReceiverCount(toDecode.at(++index));
                standardObject.setconfigurableReceiverCount(toDecode.at(++index));
                standardObject.setdualAntennaReceiverCount(toDecode.at(++index));
                int FetchAtIndex_1 = ++index;
                standardObject.setRfa2((toDecode.at(FetchAtIndex_1)>>4));
                standardObject.setsharedByBroadcastStandard((toDecode.at(FetchAtIndex_1)) & 0x0F);
                standardObject.setRfa3(toDecode.at(++index));
                addStandardInstance(standardObject);
        }

        for(uint8_t j=0; j<getNrOfSoCs(); j++){
            SoC soc;
                int FetchAtIndex_2 = ++index;
                soc.setRfa4((toDecode.at(FetchAtIndex_2))>>4);
                soc.setSOC_ID((toDecode.at(FetchAtIndex_2)) & 0x0F);
                soc.setSoC_Type(toDecode.at(++index));
                soc.setNrOfTunerPaths(toDecode.at(++index));

                for(uint8_t k=0; k<soc.getNrOfTunerPaths(); k++){
                    TunerPath path;
                        int FetchAtIndex_3 = ++index;

                        path.setCanReceiveAM(((toDecode.at(FetchAtIndex_3))>>7) & 0x01);
                        path.setCanReceiveFM(((toDecode.at(FetchAtIndex_3))>>6) & 0x01);
                        path.setCanReceiveDAB(((toDecode.at(FetchAtIndex_3))>>5) & 0x01);

                        int FetchAtIndex_4 = ++index;
                        int FetchAtIndex_5 = ++index;
                        int FetchAtIndex_6 = ++index;

                        path.setRfa5(((toDecode.at(FetchAtIndex_3) & 0x1F) << 23)|(toDecode.at(FetchAtIndex_4)<<15)|(toDecode.at(FetchAtIndex_5)<<7)|(toDecode.at(FetchAtIndex_6)<<1));
                        path.setProvidedAsExternal(toDecode.at(FetchAtIndex_6) & 0x01);
                        soc.addTunerPathInstance(path);
                }
                soc.setNrOfNBTs(toDecode.at(++index));
                soc.setNrOfDFEs(toDecode.at(++index));
                int FetchAtIndex_7 = ++index;
                soc.setCanDemodulateAM((toDecode.at(FetchAtIndex_7)>>7) & 0x01);
                soc.setCanDemodulateFM((toDecode.at(FetchAtIndex_7)>>6) & 0x01);
                soc.setCanDecodeHD((toDecode.at(FetchAtIndex_7)>>5) & 0x01);
                soc.setCanDecodeDAB((toDecode.at(FetchAtIndex_7)>>4) & 0x01);
                soc.setCanDecodeDRM((toDecode.at(FetchAtIndex_7)>>3) & 0x01);
                soc.setCanDecodeCDR((toDecode.at(FetchAtIndex_7)>>2) & 0x01);
                soc.setRfa6(((toDecode.at(FetchAtIndex_7) & 0x02)<<8)|(toDecode.at(++index)));
                addSoCInstance(soc);
        }
        setRfa((toDecode.at(++index)<<24)|(toDecode.at(++index)<<16)|(toDecode.at(++index)<<8)|(toDecode.at(++index)));
};