#include<vector>
#include<cstdint>

using namespace std;

class Standard{

private:
uint8_t Rfa1;
uint8_t broadcastStandard;
uint8_t creatableReceiverCount;
uint8_t configurableReceiverCount;
uint8_t dualAntennaReceiverCount;
uint8_t Rfa2;
uint8_t sharedByBroadcastStandard;
uint8_t Rfa3;

public:
uint8_t getrfa1(){return Rfa1;}
uint8_t getbroadcastStandard(){return broadcastStandard;}
uint8_t getcreatableReceiverCount(){return creatableReceiverCount;}
uint8_t getconfigurableReceiverCount(){return configurableReceiverCount;}
uint8_t getdualAntennaReceiverCount(){return dualAntennaReceiverCount;}
uint8_t getRfa2(){return Rfa2;}
uint8_t getsharedByBroadcastStandard(){return sharedByBroadcastStandard;}
uint8_t getRfa3(){return Rfa3;}

void setRfa1(uint8_t rfa1_val){Rfa1 = rfa1_val;}
void setbroadcastStandard(uint8_t bs_val){broadcastStandard = bs_val;}
void setcreatableReceiverCount(uint8_t cRC_val){creatableReceiverCount = cRC_val;}
void setconfigurableReceiverCount(uint8_t configRC_val){configurableReceiverCount = configRC_val;}
void setdualAntennaReceiverCount(uint8_t dualAntRC_val){dualAntennaReceiverCount = dualAntRC_val;}
void setRfa2(uint8_t Rfa2_val){Rfa2 = Rfa2_val;}
void setsharedByBroadcastStandard(uint8_t sharedBS_val){sharedByBroadcastStandard = sharedBS_val;}
void setRfa3(uint8_t Rfa3_val){Rfa3 = Rfa3_val;}

};