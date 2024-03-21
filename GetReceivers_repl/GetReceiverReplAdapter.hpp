#ifndef GETRECEIVERREPLADAPTER_H
#define GETRECEIVERREPLADAPTER_H
#include <vector>
#include <cstdint>
#include "GetReceivers_repl.hpp"
#include "Receiver.hpp"
#include "Antenna.hpp"

using namespace std;

class I_Antenna{
    public:
    virtual void setAntennaHandle(uint8_t AntennaHandle_val) = 0;
    virtual uint8_t getAntennaHandle() = 0;

    virtual ~I_Antenna(){};
};

class AntennaAdapter : public I_Antenna{
    private:
    I_Antenna *ant;
    uint8_t AntennaHandle;

    public:
    AntennaAdapter(I_Antenna *antenna) : ant(antenna){};

    void setAntennaHandle(uint8_t AntennaHandle_val) override;

    uint8_t getAntennaHandle() override;

    ~AntennaAdapter(){
        delete ant;
    };
};

class MockAntenna : public I_Antenna{
    public:
    MockAntenna(){};
    uint8_t AntennaHandle;
    void setAntennaHandle(uint8_t AntennaHandle_val) override;
    uint8_t getAntennaHandle() override;

    ~MockAntenna(){};
};

class I_Receiver{
    public:
    virtual void addAntennaHandleInstance(I_Antenna *AntennaHandleObject) = 0;

    virtual ~I_Receiver(){};
};

class ReceiverAdapter : public I_Receiver{
    private:
    I_Receiver *rec;

    public:
    ReceiverAdapter(I_Receiver *receiver) : rec(receiver){};

    void addAntennaHandleInstance(I_Antenna *AntennaHandleObject) override;

    ~ReceiverAdapter(){
        delete rec;
    };
};

class MockReceiver : public I_Receiver{
    private:
    vector<I_Antenna*> AntennaHandlesVectorMock;
    public:
    MockReceiver(){};

    void addAntennaHandleInstance(I_Antenna *AntennaHandleObject) override;

    ~MockReceiver(){};
};

class I_GetReceiversRepl{
    public:
    virtual void decode(const vector<uint8_t> &toDecode) = 0;

    virtual void addReceiverInstance(I_Receiver *ReceiverObject) = 0;

    virtual ~I_GetReceiversRepl(){};
};

class MsgReplAdapter : public I_GetReceiversRepl{
    private:
    I_GetReceiversRepl *msg;

    public:
    MsgReplAdapter(I_GetReceiversRepl* message) : msg(message){};

    void decode(const vector<uint8_t> &toDecode) override;

    void addReceiverInstance(I_Receiver *ReceiverObject) override;

    ~MsgReplAdapter(){
        delete msg;
    };
};

class MockMessage : public I_GetReceiversRepl{
    private:
    vector<I_Receiver*> receiversVectorMock;
    public:

    MockMessage(){};

    void decode(const vector<uint8_t> &toDecode){};

    void addReceiverInstance(I_Receiver *ReceiverObject) override;

    ~MockMessage(){};
};
#endif