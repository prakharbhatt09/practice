#include<vector>
#include<cstdint>
#include "Antenna.hpp"

uint8_t Antenna::getAntennaHandle(){
    return AntennaHandle;
};

uint8_t Antenna::getRfa3(){
    return Rfa3;
};

void Antenna::setAntennaHandle(uint8_t AntennaHandle_val){
    AntennaHandle = AntennaHandle_val;
};
void Antenna::setRfa3(uint8_t Rfa3_val){
    Rfa3 = Rfa3_val;
};