#include<vector>
#include<cstdint>
#include "Receiver.hpp"

void Receiver::addAntennaHandleInstance(Antenna &AntennaHandleObject){
    AntennaHandlesVector.push_back(AntennaHandleObject);
};