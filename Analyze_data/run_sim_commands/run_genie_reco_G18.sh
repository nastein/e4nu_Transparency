#!/bin/bash

AllSectors=1
Fiducials=1
AccWeights=1
Reso=1
Signal=0

./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/G18/Excl_Range1_ C12 2261 2 100 1 1 21 23 1.95 1 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/G18/Excl_Range2_ C12 2261 2 100 1 1 28 31 1.75 1 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/G18/Excl_Range3_ C12 2261 2 100 1 1 37 40 1.5 1 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/G18/Excl_Range1_ C12 4461 2 100 1 1 21 23 3.4 1 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal

./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/G18/Excl_Range1_ 4He 2261 2 100 1 1 21 23 1.85 1 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/G18/Excl_Range2_ 4He 2261 2 100 1 1 28 31 1.75 1 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/G18/Excl_Range3_ 4He 2261 2 100 1 1 37 40 1.5 1 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/G18/Excl_Range1_ 4He 4461 2 100 1 1 21 23 3.4 1 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal

./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/G18/Excl_Range1_ 56Fe 2261 2 100 1 1 21 23 1.95 1 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/G18/Excl_Range2_ 56Fe 2261 2 100 1 1 28 31 1.75 1 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/G18/Excl_Range3_ 56Fe 2261 2 100 1 1 37 40 1.5 1 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal


