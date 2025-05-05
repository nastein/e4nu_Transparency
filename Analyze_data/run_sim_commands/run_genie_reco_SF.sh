#!/bin/bash

AllSectors=1
Fiducials=1
AccWeights=1
Reso=1
Signal=0

./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/SF/Excl_Range1 C12 2261 1 100 1 1 21 23 1.95 1 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
#./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/SF/Excl_Range1 C12 2261 1 100 1 1 28 31 1.75 1 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
#./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/SF/Excl_Range1 C12 2261 1 100 1 1 37 40 1.5 1 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal

