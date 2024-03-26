#ifndef ANTENNA_H
#define ANTENNA_H

#include<vector>
#include<cstdint>

using namespace std;

class I_Antenna{
    public:
    virtual uint8_t getAntennaHandle() = 0;

    virtual ~I_Antenna(){};
};

class Antenna : public I_Antenna{
    private:
    uint8_t AntennaHandle;
    uint8_t Rfa3;

    public:
    uint8_t getAntennaHandle() override;
    uint8_t getRfa3();

    void setAntennaHandle(uint8_t AntennaHandle_val);
    void setRfa3(uint8_t Rfa3_val);
};
#endif