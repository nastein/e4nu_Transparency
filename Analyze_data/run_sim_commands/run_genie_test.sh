#!/bin/bash

AllSectors=1
Fiducials=1
AccWeights=1
Reso=1
Signal=1

./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/LookForHoles_ C12 1161 1 100 0 1 0 180 9999 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/LookForHoles_ C12 4461 1 100 0 1 0 180 9999 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/LookForHoles_ C12 2261 1 100 0 1 0 180 9999 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal



