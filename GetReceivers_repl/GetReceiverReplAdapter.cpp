#include <vector>
#include <cstdint>
#include "GetReceiverReplAdapter.hpp"

void MsgReplAdapter :: addReceiverInstance(I_Receiver *ReceiverObject) {
    msg->addReceiverInstance(ReceiverObject); //redirects to add rec inst. method
};

void MsgReplAdapter::decode(const vector<uint8_t> &toDecode) {
    msg->decode(toDecode);
};

void ReceiverAdapter :: addAntennaHandleInstance(I_Antenna *AntennaHandleObject) {
    rec->addAntennaHandleInstance(AntennaHandleObject); //redirects to add antenna handle inst. method
};  

void AntennaAdapter::setAntennaHandle(uint8_t AntennaHandle_val){
    AntennaHandle = AntennaHandle_val;
}

uint8_t AntennaAdapter::getAntennaHandle(){
    return AntennaHandle;
}

void MockAntenna::setAntennaHandle(uint8_t AntennaHandle_val){
    AntennaHandle = AntennaHandle_val;
}

uint8_t MockAntenna::getAntennaHandle(){
    return AntennaHandle;
}

void MockReceiver::addAntennaHandleInstance(I_Antenna *AntennaHandleObject){
    AntennaHandlesVectorMock.push_back(AntennaHandleObject);
}

void MockMessage::addReceiverInstance(I_Receiver *ReceiverObject){
        receiversVectorMock.push_back(ReceiverObject);
};