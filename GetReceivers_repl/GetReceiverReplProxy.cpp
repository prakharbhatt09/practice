#include <vector>
#include <cstdint>
#include "GetReceiverReplProxy.hpp"

void MsgReplProxy :: addReceiverInstance(I_Receiver &ReceiverObject) {
    msg->addReceiverInstance(ReceiverObject); //redirects to add rec inst. method
};

void MsgReplProxy::decode(const vector<uint8_t> &toDecode) {
    msg->decode(toDecode);
};

void ReceiverProxy :: addAntennaHandleInstance(I_Antenna &AntennaHandleObject) {
    rec->addAntennaHandleInstance(AntennaHandleObject); //redirects to add antenna handle inst. method
};  

uint8_t AntennaProxy::getAntennaHandle(){
    return AntennaHandle;
};