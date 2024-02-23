#include <iostream>
#include <vector>
#include "GetResourceUsage_repl.hpp"
#include "SoC.hpp"
#include "TunerPath.hpp"
#include "NBT.hpp"
#include "DFE.hpp"
#include "Receiver.hpp"

using namespace std;

void SoC::addDFEInstance(DFE &DFEObject){
    dfes.push_back(DFEObject);
};

void SoC::addtunerPathInstance(TunerPath &tunerPathObject){
    tunerPaths.push_back(tunerPathObject);
};