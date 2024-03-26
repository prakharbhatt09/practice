#ifndef GETRECEIVERREPLADAPTER_H
#define GETRECEIVERREPLADAPTER_H
#include <vector>
#include <cstdint>
#include "GetReceivers_repl.hpp"
#include "Receiver.hpp"
#include "Antenna.hpp"

using namespace std;

class AntennaProxy : public I_Antenna{
    private:
    I_Antenna *ant;
    uint8_t AntennaHandle;

    public:
    AntennaProxy(I_Antenna *antenna) : ant(antenna){};

    uint8_t getAntennaHandle() override;

    ~AntennaProxy(){
        delete ant;
    };
};

class ReceiverProxy : public I_Receiver{
    private:
    I_Receiver *rec;

    public:
    ReceiverProxy(I_Receiver *receiver) : rec(receiver){};

    void addAntennaHandleInstance(I_Antenna &AntennaHandleObject) override;

    ~ReceiverProxy(){
        delete rec;
    };
};

class MsgReplProxy : public I_GetReceiversRepl{
    private:
    I_GetReceiversRepl *msg;

    public:
    MsgReplProxy(I_GetReceiversRepl* message) : msg(message){};

    void decode(const vector<uint8_t> &toDecode) override;

    void addReceiverInstance(I_Receiver &ReceiverObject) override;

    ~MsgReplProxy(){
        delete msg;
    };
};
#endif