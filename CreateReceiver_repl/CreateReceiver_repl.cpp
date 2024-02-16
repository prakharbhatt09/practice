#include "CreateReceiver_repl.hpp"

using namespace std;

CreateReceiver_repl::CreateReceiver_repl(){}

    vector<uint8_t> CreateReceiver_repl::encode(){
    vector<uint8_t> toEncode;

    toEncode.push_back(getCookie()); //0
    toEncode.push_back((Opcode >> 8) & 0xFF);
    toEncode.push_back(Opcode & 0xFF);
    toEncode.push_back(getReplyStatus()); //3
    toEncode.push_back(getReceiverHandle());//4
    toEncode.push_back((getRfa() >> 24) & 0xFF);
    toEncode.push_back((getRfa() >> 16) & 0xFF);
    toEncode.push_back((getRfa() >> 8) & 0xFF);
    toEncode.push_back(getRfa() & 0xFF);

    return toEncode;
};

void CreateReceiver_repl::decode(const std::vector<uint8_t>& toDecode){
    Cookie = (toDecode.at(0));
    ReplyStatus = (toDecode.at(3));
    ReceiverHandle = (toDecode.at(4));
    Rfa = ((toDecode.at(5) << 24) & 0xFF);
    Rfa = ((toDecode.at(6) << 16) & 0xFF);
    Rfa = ((toDecode.at(7) << 8) & 0xFF);
    Rfa = (toDecode.at(8) & 0xFF);
};