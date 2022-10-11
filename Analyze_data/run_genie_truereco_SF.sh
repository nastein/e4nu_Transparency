#!/bin/bash

AllSectors=0
Fiducials=1
AccWeights=1
Reso=1
Signal=1

#./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/SF/Incl_Range2_ C12 1161 2 100 1 1 28 31 1.0 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
#./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/SF/Incl_Range3_ C12 1161 2 100 1 1 37 40 0.95 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
#./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/SF/Excl_Range2_ C12 1161 2 100 1 1 28 31 1.0 1 0 40 95 $AllSectors $Fiducials $AccWeights $Reso $Signal
#./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/SF/Excl_Range3_ C12 1161 2 100 1 1 37 40 0.95 1 0 45 80 $AllSectors $Fiducials $AccWeights $Reso $Signal

./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/SF/Incl_Range1_ C12 2261 2 100 1 1 21 23 1.95 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/SF/Incl_Range2_ C12 2261 2 100 1 1 28 31 1.75 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/SF/Incl_Range3_ C12 2261 2 100 1 1 37 40 1.5 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/SF/Excl_Range1_ C12 2261 2 100 1 1 21 23 1.95 1 0 45 80 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/SF/Excl_Range2_ C12 2261 2 100 1 1 28 31 1.75 1 0 40 70 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/SF/Excl_Range3_ C12 2261 2 100 1 1 37 40 1.5 1 0 30 55 $AllSectors $Fiducials $AccWeights $Reso $Signal

