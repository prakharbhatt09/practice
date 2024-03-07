#include<vector>
#include<cstdint>
#include"Standard.hpp"
#include"SoC.hpp"

using namespace std;

class GetCapabilities_repl{

    private:
    uint8_t MessageType;
    uint8_t Cookie;
    const uint16_t Opcode{0x0102};
    uint8_t ReplyStatus;
    uint8_t NrOfStandards;
    uint8_t NrOfSoCs;
    uint32_t Rfa;
    
    vector<Standard> standardsVector;
    vector<SoC> socsVector;
    
    public:
    uint8_t getMessageType(){return MessageType;}
    uint8_t getCookie(){return Cookie;}
    uint8_t getReplyStatus(){return ReplyStatus;}
    uint8_t getNrOfStandards(){return NrOfStandards;}
    uint8_t getNrOfSoCs(){return NrOfSoCs;}
    uint8_t getRfa(){return Rfa;}
    vector<Standard> getstandardsVector(){return standardsVector;}
    vector<SoC> getsocsVector(){return socsVector;}
    
    void setMessageType(uint8_t MessageType_val){MessageType = MessageType_val;}
    void setCookie(uint8_t cookie_val){Cookie = cookie_val;}
    void setReplyStatus(uint8_t replyStatus_val){ReplyStatus = replyStatus_val;}
    void setNrOfStandards(uint8_t standards_val){NrOfStandards = standards_val;}
    void setNrOfSoCs(uint8_t socs_val){NrOfSoCs = socs_val;}
    void setRfa(uint8_t Rfa_val){Rfa = Rfa_val;}
    
    void addStandardInstance(Standard &standardObject);

    void addSoCInstance(SoC &socObject);

    void decode(const vector<uint8_t> &toDecode);
};