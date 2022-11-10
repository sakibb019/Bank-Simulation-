#! /bin/bash

mkdir targets
cd targets || exit
cmake -G "Unix Makefiles" ..
make bankSimulationTest
./bankSimulationTest
