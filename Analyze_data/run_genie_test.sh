#!/bin/bash

AllSectors=1
Fiducials=1
AccWeights=1
Reso=1
Signal=0

#./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/All_Angles_ C12 2261 1 100 0 1 0 180 0 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/xy_emomcut_ C12 2261 1 100 0 1 21 23 1.95 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/xy_emomcut_ C12 2261 1 100 0 1 28 31 1.75 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/xy_emomcut_ C12 2261 1 100 0 1 37 40 1.5 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/xy_emomcut_ C12 4461 1 100 0 1 21 23 3.4 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
#./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/ThetaPQ_Range3_ C12 2261 1 100 0 1 37 40 1.5 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
#./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/ThetaPQ_Range1_ C12 4461 1 100 0 1 21 23 3.4 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal

#./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/ThetaPQ_Range1_ 4He 2261 1 100 0 1 21 23 1.85 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
#./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/ThetaPQ_Range2_ 4He 2261 1 100 0 1 28 31 1.75 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
#./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/ThetaPQ_Range3_ 4He 2261 1 100 0 1 37 40 1.5 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
#./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/ThetaPQ_Range1_ 4He 4461 1 100 0 1 21 23 3.4 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal

#./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/ThetaPQ_Range1_ 56Fe 2261 1 100 0 1 21 23 1.95 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
#./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/ThetaPQ_Range2_ 56Fe 2261 1 100 0 1 28 31 1.75 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
#./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/ThetaPQ_Range3_ 56Fe 2261 1 100 0 1 37 40 1.5 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
#./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/All_Angles_ 56Fe 4461 1 100 0 1 0 180 0 0 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal


