#!/bin/bash

AllSectors=0
Fiducials=1
AccWeights=1
Reso=1
Signal=0

./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Incl_Range2_ C12 1161 1 100 1 1 28 31 1.0 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Incl_Range3_ C12 1161 1 100 1 1 37 40 0.95 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Incl_Range1_ C12 4461 1 100 1 1 21 23 3.4 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Excl_Range2_ C12 1161 1 100 1 1 28 31 1.0 1 0 40 95 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Excl_Range3_ C12 1161 1 100 1 1 37 40 0.95 1 0 45 80 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Excl_Range1_ C12 4461 1 100 1 1 21 23 3.4 1 0 35 50 $AllSectors $Fiducials $AccWeights $Reso $Signal

./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Incl_Range1_ C12 2261 1 100 1 1 21 23 1.95 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Incl_Range2_ C12 2261 1 100 1 1 28 31 1.75 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Incl_Range3_ C12 2261 1 100 1 1 37 40 1.5 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Excl_Range1_ C12 2261 1 100 1 1 21 23 1.95 1 0 45 80 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Excl_Range2_ C12 2261 1 100 1 1 28 31 1.75 1 0 40 70 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Excl_Range3_ C12 2261 1 100 1 1 37 40 1.5 1 0 30 55 $AllSectors $Fiducials $AccWeights $Reso $Signal

./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Incl_Range1_ 4He 2261 1 100 1 1 21 23 1.85 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Incl_Range2_ 4He 2261 1 100 1 1 28 31 1.75 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Incl_Range3_ 4He 2261 1 100 1 1 37 40 1.5 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Incl_Range1_ 4He 4461 1 100 1 1 21 23 3.4 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Excl_Range1_ 4He 2261 1 100 1 1 21 23 1.85 1 0 35 80 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Excl_Range2_ 4He 2261 1 100 1 1 28 31 1.75 1 0 35 70 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Excl_Range3_ 4He 2261 1 100 1 1 37 40 1.5 1 0 30 55 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Excl_Range1_ 4He 4461 1 100 1 1 21 23 3.4 1 0 40 55 $AllSectors $Fiducials $AccWeights $Reso $Signal

./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Excl_Range1_ 56Fe 2261 1 100 1 1 21 23 1.95 1 0 40 80 $AllSectors $Fiducials $AccWeights $Reso $Signal 
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Excl_Range2_ 56Fe 2261 1 100 1 1 28 31 1.75 1 0 40 70 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Excl_Range3_ 56Fe 2261 1 100 1 1 37 40 1.5 1 0 30 55 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Excl_Range1_ 56Fe 4461 1 100 1 1 21 23 3.35 1 0 35 55 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Incl_Range1_ 56Fe 2261 1 100 1 1 21 23 1.95 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Incl_Range2_ 56Fe 2261 1 100 1 1 28 31 1.75 0 0 0 100 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Incl_Range3_ 56Fe 2261 1 100 1 1 37 40 1.5 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Incl_Range1_ 56Fe 4461 1 100 1 1 21 23 3.35 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal


