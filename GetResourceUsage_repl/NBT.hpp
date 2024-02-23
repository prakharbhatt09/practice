#ifndef NBT_H
#define NBT_H

#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

class NBT{
    private:
    uint8_t NBT_ix;
    uint8_t Assigned_DFE_ix;
    uint16_t Rfa4;

    public:
    NBT();
    NBT(uint8_t NBT_ix_val, uint8_t Assigned_DFE_ix_val, uint8_t Rfa4_val)
        :NBT_ix{NBT_ix_val}, Assigned_DFE_ix{Assigned_DFE_ix_val}, Rfa4{Rfa4_val}{
        }

    uint8_t getNBT_ix(){return NBT_ix;}
    uint8_t getAssigned_DFE_ix(){return Assigned_DFE_ix;}
    uint8_t getRfa4(){return Rfa4;}

    void setNBT_ix(uint8_t p){NBT_ix = p;}
    void setAssigned_DFE_ix(uint8_t q){Assigned_DFE_ix = q;}
    void setRfa4(uint8_t r){Rfa4 = r;}

};
#endif