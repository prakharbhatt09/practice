#include<vector>
#include<cstdint>

using namespace std;

class Antenna{
    private:
    uint8_t AntennaHandle;
    uint8_t Rfa3;

    public:
    uint8_t getAntennaHandle(){return AntennaHandle;}
    uint8_t getRfa3(){return Rfa3;}

    void setAntennaHandle(uint8_t AntennaHandle_val){AntennaHandle = AntennaHandle_val;}
    void setRfa3(uint8_t Rfa3_val){Rfa3 = Rfa3_val;}
};