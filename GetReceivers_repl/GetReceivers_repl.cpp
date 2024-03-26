#include<vector>
#include<cstdint>
#include "GetReceivers_repl.hpp"
#include "Receiver.hpp"
#include "Antenna.hpp"

void GetReceivers_repl::addReceiverInstance(I_Receiver &ReceiverObject) {
    receiversVector.push_back(&ReceiverObject);
};

void GetReceivers_repl::decode(const vector<uint8_t> &toDecode){
    setMessageType(toDecode.at(0)>>7);
    setCookie(toDecode.at(0) & 0x3F);
    setReplyStatus(toDecode.at(3));
    setRfa1(toDecode.at(4)>>4);
    setNrOfReceivers(toDecode.at(4) & 0x0F);
    int index = 4;

        for(uint8_t i=0; i<getNrOfReceivers(); i++){
            Receiver rec;
            rec.setReceiverHandle(toDecode.at(++index));
            int FetchAtIndex_1 = ++index;
            rec.setPHY_ID(toDecode.at(FetchAtIndex_1)>>4);
            rec.setCTRL_ID(toDecode.at(FetchAtIndex_1) & 0x0F);
            int FetchAtIndex_2 = ++index;
            rec.setBroadcastStandard(toDecode.at(FetchAtIndex_2)>>4);
            rec.setReceiverMode(toDecode.at(FetchAtIndex_2) & 0x0F);
            rec.setReceiverState(toDecode.at(++index));
            int FetchAtIndex_3 = ++index;
            rec.setRfa2(toDecode.at(FetchAtIndex_3)>>2);
            rec.setNrOfAntennaHandles(toDecode.at(FetchAtIndex_3) & 0x03);

                for(uint8_t j=0; j<rec.getNrOfAntennaHandles(); j++){
                    Antenna antenna;
                    antenna.setAntennaHandle(toDecode.at(++index));
                    antenna.setRfa3(toDecode.at(++index));
                    rec.addAntennaHandleInstance(antenna);
                }
            rec.setRfa4((toDecode.at(++index)<<24)|(toDecode.at(++index)<<16)|(toDecode.at(++index)<<8)|(toDecode.at(++index)));
            addReceiverInstance(rec);
        }
    setRfa5((toDecode.at(++index)<<24)|(toDecode.at(++index)<<16)|(toDecode.at(++index)<<8)|(toDecode.at(++index)));
};