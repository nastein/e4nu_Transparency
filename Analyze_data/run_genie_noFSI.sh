#!/bin/bash

AllSectors=1
Fiducials=0
AccWeights=0
Reso=0
Signal=1

#./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/SF/Excl_Range1_ C12 2261 1 100 1 1 21 23 1.95 1 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Analyze_data/G18_noFSI_truereco_ C12 2261 2 100 1 1 28 31 1.75 1 0 0 180 1 1 1 1 1
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Analyze_data/G18_noFSI_reco_ C12 2261 2 100 1 1 28 31 1.75 1 0 0 180 1 1 1 1 0
./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Analyze_data/G18_noFSI_true_ C12 2261 2 100 1 1 28 31 1.75 1 0 0 180 1 0 0 0 1
#./genie_analysis /genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/ProtMom_Cut/Excl_Range3_ C12 2261 1 100 1 1 37 40 1.5 1 0 0 180 $AllSectors $Fiducials $AccWeights $Reso $Signal
