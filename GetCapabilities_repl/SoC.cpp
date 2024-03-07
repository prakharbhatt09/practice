#include<vector>
#include<cstdint>
#include"SoC.hpp"

void SoC::addTunerPathInstance(TunerPath &pathObject){
    tunerPathsVector.push_back(pathObject);
};