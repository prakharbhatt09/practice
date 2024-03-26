#include<vector>
#include<cstdint>
#include "Receiver.hpp"

void Receiver::addAntennaHandleInstance(I_Antenna &AntennaHandleObject){
    AntennaHandlesVector.push_back(&AntennaHandleObject);
};