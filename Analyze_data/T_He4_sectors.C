#include "myFunctions.cpp"
#include "T_He4_sectors.h"
#include "transfunctions.h"

void T_He4_sectors(bool make_plots = false) {
        gStyle->SetOptStat(0);

        data_2261[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample3/He4/Excl_Range1_Data__4He_2.261000.root";
        data_2261[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample3/He4/Incl_Range1_Data__4He_2.261000.root";
        data_2261[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample3/He4/Excl_Range2_Data__4He_2.261000.root";
        data_2261[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample3/He4/Incl_Range2_Data__4He_2.261000.root";
        data_2261[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample3/He4/Excl_Range3_Data__4He_2.261000.root";
        data_2261[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample3/He4/Incl_Range3_Data__4He_2.261000.root";
        data_4461[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample3/He4/Excl_Range1_Data__4He_4.461000.root";
        data_4461[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample3/He4/Incl_Range1_Data__4He_4.461000.root";

        susa_2261[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Excl_Range1_Genie_1_4He_2.261000.root";
        susa_2261[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Incl_Range1_Genie_1_4He_2.261000.root";
        susa_2261[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Excl_Range2_Genie_1_4He_2.261000.root";
        susa_2261[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Incl_Range2_Genie_1_4He_2.261000.root";
        susa_2261[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Excl_Range3_Genie_1_4He_2.261000.root";
        susa_2261[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Incl_Range3_Genie_1_4He_2.261000.root";
        susa_4461[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Excl_Range1_Genie_1_4He_4.461000.root";
        susa_4461[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/SuSAv2/Incl_Range1_Genie_1_4He_4.461000.root";

        g_2261[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/G18/Excl_Range1_Genie_2_4He_2.261000.root";
        g_2261[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/G18/Incl_Range1_Genie_2_4He_2.261000.root";
        g_2261[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/G18/Excl_Range2_Genie_2_4He_2.261000.root";
        g_2261[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/G18/Incl_Range2_Genie_2_4He_2.261000.root";
        g_2261[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/G18/Excl_Range3_Genie_2_4He_2.261000.root";
        g_2261[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/G18/Incl_Range3_Genie_2_4He_2.261000.root";
        g_4461[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/G18/Excl_Range1_Genie_2_4He_4.461000.root";
        g_4461[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/G18/Incl_Range1_Genie_2_4He_4.461000.root";

        susa_2261_truereco[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/SuSA/Excl_Range1_Genie_1_4He_2.261000.root";
        susa_2261_truereco[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/SuSA/Incl_Range1_Genie_1_4He_2.261000.root";
        susa_2261_truereco[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/SuSA/Excl_Range2_Genie_1_4He_2.261000.root";
        susa_2261_truereco[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/SuSA/Incl_Range2_Genie_1_4He_2.261000.root";
        susa_2261_truereco[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/SuSA/Excl_Range3_Genie_1_4He_2.261000.root";
        susa_2261_truereco[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/SuSA/Incl_Range3_Genie_1_4He_2.261000.root";
        susa_4461_truereco[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/SuSA/Excl_Range1_Genie_1_4He_4.461000.root";
        susa_4461_truereco[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/SuSA/Incl_Range1_Genie_1_4He_4.461000.root";

        susa_2261_true[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth/SuSA/Excl_Range1_Genie_1_4He_2.261000.root";
        susa_2261_true[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth/SuSA/Incl_Range1_Genie_1_4He_2.261000.root";
        susa_2261_true[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth/SuSA/Excl_Range2_Genie_1_4He_2.261000.root";
        susa_2261_true[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth/SuSA/Incl_Range2_Genie_1_4He_2.261000.root";
        susa_2261_true[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth/SuSA/Excl_Range3_Genie_1_4He_2.261000.root";
        susa_2261_true[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth/SuSA/Incl_Range3_Genie_1_4He_2.261000.root";
        susa_4461_true[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth/SuSA/Excl_Range1_Genie_1_4He_4.461000.root";
        susa_4461_true[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth/SuSA/Incl_Range1_Genie_1_4He_4.461000.root";

        g_2261_truereco[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/G18/Excl_Range1_Genie_2_4He_2.261000.root";
        g_2261_truereco[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/G18/Incl_Range1_Genie_2_4He_2.261000.root";
        g_2261_truereco[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/G18/Excl_Range2_Genie_2_4He_2.261000.root";
        g_2261_truereco[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/G18/Incl_Range2_Genie_2_4He_2.261000.root";
        g_2261_truereco[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/G18/Excl_Range3_Genie_2_4He_2.261000.root";
        g_2261_truereco[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/G18/Incl_Range3_Genie_2_4He_2.261000.root";
        g_4461_truereco[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/G18/Excl_Range1_Genie_2_4He_4.461000.root";
        g_4461_truereco[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth_Reco/G18/Incl_Range1_Genie_2_4He_4.461000.root";

        g_2261_true[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth/G18/Excl_Range1_Genie_2_4He_2.261000.root";
        g_2261_true[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth/G18/Incl_Range1_Genie_2_4He_2.261000.root";
        g_2261_true[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth/G18/Excl_Range2_Genie_2_4He_2.261000.root";
        g_2261_true[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth/G18/Incl_Range2_Genie_2_4He_2.261000.root";
        g_2261_true[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth/G18/Excl_Range3_Genie_2_4He_2.261000.root";
        g_2261_true[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth/G18/Incl_Range3_Genie_2_4He_2.261000.root";
        g_4461_true[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth/G18/Excl_Range1_Genie_2_4He_4.461000.root";
        g_4461_true[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Truth/G18/Incl_Range1_Genie_2_4He_4.461000.root";

        susa_2261_truereco_rad[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Rad_Truth_Reco/Excl_Range1_Genie_3_4He_2.261000.root";
        susa_2261_truereco_rad[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Rad_Truth_Reco/Incl_Range1_Genie_3_4He_2.261000.root";
        susa_2261_truereco_rad[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Rad_Truth_Reco/Excl_Range2_Genie_3_4He_2.261000.root";
        susa_2261_truereco_rad[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Rad_Truth_Reco/Incl_Range2_Genie_3_4He_2.261000.root";
        susa_2261_truereco_rad[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Rad_Truth_Reco/Excl_Range3_Genie_3_4He_2.261000.root";
        susa_2261_truereco_rad[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Rad_Truth_Reco/Incl_Range3_Genie_3_4He_2.261000.root";
        susa_4461_truereco_rad[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Rad_Truth_Reco/Excl_Range1_Genie_3_4He_4.461000.root";
        susa_4461_truereco_rad[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Third_Try/Rad_Truth_Reco/Incl_Range1_Genie_3_4He_4.461000.root";

        std::string second_en[3][2] = {{"2.261 Excl Range 1", "2.261 Incl Range 1"},{"2.261 Excl Range 2", "2.261 Incl Range 2"},{ "2.261 Excl Range 3", "2.261 Incl Range 3"}};
        std::string third_en[1][2] = {{"4.461 Excl Range 1","4.461 Incl Range 1"}}; 

        int sectors[3] = {2,3,4};

        int num_2261_sec = 3;
        int num_4461_sec = 3;


        
// --------------------- Getting radiative correction histograms from MC ----------------
        TH1D* SuSA_2261_true_reco_rad[3][2][6];
        TH1D* SuSA_4461_true_reco_rad[1][2][6];

        for(int s : sectors) {
                for(int p = 0; p < 2; p++) {
                        if(p == 1) s = (s+3)%6;

                        for(int r = 0; r < 3; r++) {
                                if(p==0) { // Exclusive
                                        SuSA_2261_true_reco_rad[r][p][s] = (TH1D*)SumProtInts(susa_2261_truereco_rad[r][p], s, false);
                                }
                                if(p==1) { // Inclusive
                                        SuSA_2261_true_reco_rad[r][p][s] = (TH1D*)SumElecInts(susa_2261_truereco_rad[r][p], s, false);
                                }
                                UniversalE4vFunction(SuSA_2261_true_reco_rad[r][p][s],  FSIModelsToLabels["SuSav2_RadCorr_LFGM_Truth_WithFidAcc_UpdatedSchwinger"], "4He", "2_261", TString::Format("susa_2261_mom_truereco_rad"));
                        }
                
                        for(int r = 0; r < 1; r++) {
                                if(p==0) { // Exclusive
                                        SuSA_4461_true_reco_rad[r][p][s] = (TH1D*)SumProtInts(susa_4461_truereco_rad[r][p], s, false);
                                }
                                if(p==1) { // Inclusive
                                        SuSA_4461_true_reco_rad[r][p][s] = (TH1D*)SumElecInts(susa_4461_truereco_rad[r][p], s, false);
                                }
                                UniversalE4vFunction(SuSA_4461_true_reco_rad[r][p][s],  FSIModelsToLabels["SuSav2_RadCorr_LFGM_Truth_WithFidAcc_UpdatedSchwinger"], "4He", "4_461", TString::Format("susa_4461_mom_truereco_rad"));
                        }
                }
        }

// --------------------- Getting acceptance correction histograms from MC ---------------
        
        //[NRanges][Exclusive = 0, Inclsuive = 1]     
        TH1D* SuSA_2261_true[3][2][6];
        TH1D* SuSA_2261_true_reco[3][2][6];
        TH1D* G_2261_true[3][2][6];
        TH1D* G_2261_true_reco[3][2][6];

        TH1D* SuSA_4461_true[1][2][6];
        TH1D* SuSA_4461_true_reco[1][2][6];
        TH1D* G_4461_true[1][2][6];
        TH1D* G_4461_true_reco[1][2][6];


        for(int p = 0; p < 2; p++) {
                for(int s : sectors) {
                        if(p == 1) s = (s+3)%6;
                        // 2.261 GeV
                        for(int r = 0; r < 3; r++) {
                                if(p==0) { // Exclusive
                                        SuSA_2261_true[r][p][s] = (TH1D*)SumProtInts(susa_2261_true[r][p], s, false);
                                        SuSA_2261_true_reco[r][p][s] = (TH1D*)SumProtInts(susa_2261_truereco[r][p], s, false);
                                        G_2261_true[r][p][s] = (TH1D*)SumProtInts(g_2261_true[r][p], s, false);
                                        G_2261_true_reco[r][p][s] = (TH1D*)SumProtInts(g_2261_truereco[r][p], s, false);
                                }
                                if(p==1) { // Inclusive
                                        SuSA_2261_true[r][p][s] = (TH1D*)SumElecInts(susa_2261_true[r][p], s, false);
                                        SuSA_2261_true_reco[r][p][s] = (TH1D*)SumElecInts(susa_2261_truereco[r][p], s, false);
                                        G_2261_true[r][p][s] = (TH1D*)SumElecInts(g_2261_true[r][p], s, false);
                                        G_2261_true_reco[r][p][s] = (TH1D*)SumElecInts(g_2261_truereco[r][p], s, false);
                                }
                                UniversalE4vFunction(SuSA_2261_true[r][p][s],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "4He","2_261", TString::Format("susa_2261_mom_%i%i%i",r,p,s));
                                UniversalE4vFunction(G_2261_true[r][p][s],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "4He","2_261", TString::Format("g_2261_mom_%i%i%i",r,p,s));
                                UniversalE4vFunction(SuSA_2261_true_reco[r][p][s],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "4He","2_261", TString::Format("susa_2261_mom_truereco_%i%i%i",r,p,s));
                                UniversalE4vFunction(G_2261_true_reco[r][p][s],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithFidAcc"], "4He","2_261", TString::Format("g_2261_mom_truereco_%i%i%i",r,p,s));
                        }   
        
                        // 4.461 GeV
                        for(int r = 0; r < 1; r++) {
                                if(p==0) { // Exclusive
                                        SuSA_4461_true[r][p][s] = (TH1D*)SumProtInts(susa_4461_true[r][p], s, false);
                                        SuSA_4461_true_reco[r][p][s] = (TH1D*)SumProtInts(susa_4461_truereco[r][p], s, false);
                                        G_4461_true[r][p][s] = (TH1D*)SumProtInts(g_4461_true[r][p], s, false);
                                        G_4461_true_reco[r][p][s] = (TH1D*)SumProtInts(g_4461_truereco[r][p], s, false);
                                }
                                if(p==1) { // Inclusive
                                        SuSA_4461_true[r][p][s] = (TH1D*)SumElecInts(susa_4461_true[r][p], s, false);
                                        SuSA_4461_true_reco[r][p][s] = (TH1D*)SumElecInts(susa_4461_truereco[r][p], s, false);
                                        G_4461_true[r][p][s] = (TH1D*)SumElecInts(g_4461_true[r][p], s, false);
                                        G_4461_true_reco[r][p][s] = (TH1D*)SumElecInts(g_4461_truereco[r][p], s, false);
                                }
                                UniversalE4vFunction(SuSA_4461_true[r][p][s],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "4He","4_461", TString::Format("susa_4461_mom_%i%i%i",r,p,s));
                                UniversalE4vFunction(G_4461_true[r][p][s],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "4He","4_461", TString::Format("g_4461_mom_%i%i%i",r,p,s));
                                UniversalE4vFunction(SuSA_4461_true_reco[r][p][s],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "4He","4_461", TString::Format("susa_4461_mom_truereco_%i%i%i",r,p,s));
                                UniversalE4vFunction(G_4461_true_reco[r][p][s],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithFidAcc"], "4He","4_461", TString::Format("g_4461_mom_truereco_%i%i%i",r,p,s));
                        }
                }
        }


// --------------------- Getting MC exclusive and inclusive measurements and mec/neutron corrections ----------------

        //[NRanges][Exclusive = 0, Inclsuive = 1]     
        
        // Get the exclusive and inclusive SuSA predictions as well as MEC corrections
        // neutron corrections to apply to data from G18
        // neutron corrections to apply to MEC from SuSA
        // 1.161 GeV
        TH1D* SuSA_2261[3][2][6];
        TH1D* G_2261[3][2][6];
        double mec_corr_2261[3][2][6];
        double mec_corr_G_2261[3][2][6];
        double mec_corr_tot_2261[3][2];
        double mec_corr_tot_G_2261[3][2];
        double neutron_corr_2261_G18[3][2];
        double neutron_corr_2261_susa[3][2];

        TH1D* SuSA_4461[1][2][6];
        TH1D* G_4461[1][2][6];
        double mec_corr_4461[1][2][6];
        double mec_corr_G_4461[1][2][6];
        double mec_corr_tot_4461[1][2];
        double mec_corr_tot_G_4461[1][2];
        double neutron_corr_4461_G18[1][2];
        double neutron_corr_4461_susa[1][2];


        // 2.261 GeV
        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 3; r++) {
                        std::cout<< "Neutron and MEC corrections for " << second_en[r][p] << "\n"; 
                        if(p == 0) {
                                neutron_corr_2261_susa[r][p] = get_Neutron_corr(susa_2261[r][p], false);
                                neutron_corr_2261_G18[r][p] = get_Neutron_corr(g_2261[r][p], false);
                                mec_corr_tot_2261[r][p] = get_MEC_corr_overall(susa_2261[r][p], false);
                                mec_corr_tot_G_2261[r][p] = get_MEC_corr_overall(g_2261[r][p], false);
                        }
                        if(p == 1) {
                                neutron_corr_2261_susa[r][p] = get_Neutron_corr(susa_2261[r][p], true);
                                neutron_corr_2261_G18[r][p] = get_Neutron_corr(g_2261[r][p], true); 
                                mec_corr_tot_2261[r][p] = get_MEC_corr_overall(susa_2261[r][p], true);
                                mec_corr_tot_G_2261[r][p] = get_MEC_corr_overall(g_2261[r][p], true);
                        }
                        std::cout << "G18 N: " << neutron_corr_2261_G18[r][p] << ", MEC: " << mec_corr_tot_G_2261[r][p] << "\n";
                        std::cout << "SuSA N: " << neutron_corr_2261_susa[r][p] << ", MEC: " << mec_corr_tot_2261[r][p] << "\n";
                        for(int s : sectors) {
                                if(p==0) { // Exclusive
                                        SuSA_2261[r][p][s] = (TH1D*)SumProtInts(susa_2261[r][p], s, false);
                                        G_2261[r][p][s] = (TH1D*)SumProtInts(g_2261[r][p], s, false);
                                        mec_corr_2261[r][p][s] = get_MEC_corr(susa_2261[r][p], s, false);
                                        mec_corr_G_2261[r][p][s] = get_MEC_corr(g_2261[r][p], s, false);
                                        
                                }
                                if(p==1) { // Inclusive
                                        s = (s+3)%6;
                                        SuSA_2261[r][p][s] = (TH1D*)SumElecInts(susa_2261[r][p], s, false);
                                        G_2261[r][p][s] = (TH1D*)SumElecInts(g_2261[r][p], s, false);
                                        mec_corr_2261[r][p][s] = get_MEC_corr(susa_2261[r][p], s, true);
                                        mec_corr_G_2261[r][p][s] = get_MEC_corr(g_2261[r][p], s, true);
                                        }
                                ///std::cout << "sector " << s << "\n";
                                //std::cout << "SuSA MEC: " << mec_corr_2261[r][p][s] << "\n";
                                //std::cout << "G18 MEC:  " << mec_corr_G_2261[r][p][s] << "\n";
                                UniversalE4vFunction(SuSA_2261[r][p][s], FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "4He","2_261", TString::Format("susa_2261_mom_reco_%i%i%i",r,p,s));
                                UniversalE4vFunction(G_2261[r][p][s], FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithFidAcc"], "4He","2_261", TString::Format("g_2261_mom_reco_%i%i%i",r,p,s));
                        }
                }
        

                // 4.461 GeV
                for(int r = 0; r < 1; r++) {
                        std::cout << "Neutron and MEC corrections for "<< third_en[r][p] << "\n";
                        if( p == 0 ) {
                                neutron_corr_4461_susa[r][p] = get_Neutron_corr(susa_4461[r][p], false);
                                neutron_corr_4461_G18[r][p] = get_Neutron_corr(g_4461[r][p], false);
                                mec_corr_tot_4461[r][p] = get_MEC_corr_overall(susa_4461[r][p], false);
                                mec_corr_tot_G_4461[r][p] = get_MEC_corr_overall(g_4461[r][p], false);
                        }
                        if( p == 1 ) {
                                neutron_corr_4461_susa[r][p] = get_Neutron_corr(susa_4461[r][p], true);
                                neutron_corr_4461_G18[r][p] = get_Neutron_corr(g_4461[r][p], true); 
                                mec_corr_tot_4461[r][p] = get_MEC_corr_overall(susa_4461[r][p], true);
                                mec_corr_tot_G_4461[r][p] = get_MEC_corr_overall(g_4461[r][p], true);
                        }
                        std::cout << "G18 N: " << neutron_corr_4461_G18[r][p] << ", MEC: " << mec_corr_tot_G_4461[r][p] << "\n";
                        std::cout << "SuSA N: " << neutron_corr_4461_susa[r][p] << ", MEC: " << mec_corr_tot_4461[r][p] << "\n";
                        for(int s : sectors) {
                                if(p==0) { // Exclusive
                                        SuSA_4461[r][p][s] = (TH1D*)SumProtInts(susa_4461[r][p], s, false);
                                        G_4461[r][p][s] = (TH1D*)SumProtInts(g_4461[r][p], s, false);
                                        mec_corr_4461[r][p][s] = get_MEC_corr(susa_4461[r][p], s, false); 
                                        mec_corr_G_4461[r][p][s] = get_MEC_corr(g_4461[r][p], s, false);  
                                }
                                if(p==1) { // Inclusive

                                        s = (s+3)%6;
                                        SuSA_4461[r][p][s] = (TH1D*)SumElecInts(susa_4461[r][p], s, false);
                                        G_4461[r][p][s] = (TH1D*)SumElecInts(g_4461[r][p], s, false);
                                        mec_corr_4461[r][p][s] = get_MEC_corr(susa_4461[r][p], s, true); 
                                        mec_corr_G_4461[r][p][s] = get_MEC_corr(g_4461[r][p], s, true);   
                                }
                                //std::cout << "sector " << s << "\n";
                                //std::cout << "SuSA MEC: " << mec_corr_4461[r][p][s] << "\n";
                                //std::cout << "G18 MEC:  " << mec_corr_G_4461[r][p][s] << "\n";
                                UniversalE4vFunction(SuSA_4461[r][p][s], FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "4He","4_461", TString::Format("susa_4461_mom_reco_%i%i%i",r,p,s));
                                UniversalE4vFunction(G_4461[r][p][s], FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithFidAcc"], "4He","4_461", TString::Format("g_4461_mom_reco_%i%i%i",r,p,s));                                          
                        }
                }
        }
        std::cout << "\n";
        

// --------------------- Getting Data exclusive and inclusive measurements ----------------

        // Here we will also scale the data
        TH1D* Data_2261[3][2][6];
        TH1D* Data_4461[1][2][6];

        for(int p = 0; p < 2; p++) {
                for(int s : sectors) {
                        if(p == 0) { // Exclusive
                                Data_2261[0][p][s] = (TH1D*)SumProtInts(data_2261[0][p], s, true);
                                Data_2261[1][p][s] = (TH1D*)SumProtInts(data_2261[1][p], s, true);
                                Data_2261[2][p][s] = (TH1D*)SumProtInts(data_2261[2][p], s, true);
                                Data_4461[0][p][s] = (TH1D*)SumProtInts(data_4461[0][p], s, true);
                        }
                        if(p == 1) { // Inclusive
                                s = (s+3)%6;
                                Data_2261[0][p][s] = (TH1D*)SumElecInts(data_2261[0][p], s, true);
                                Data_2261[1][p][s] = (TH1D*)SumElecInts(data_2261[1][p], s, true);
                                Data_2261[2][p][s] = (TH1D*)SumElecInts(data_2261[2][p], s, true);
                                Data_4461[0][p][s] = (TH1D*)SumElecInts(data_4461[0][p], s, true);
                        }
                        UniversalE4vFunction(Data_2261[0][p][s], "Pinned Data", "4He", "2_261", TString::Format("data %s %i",second_en[0][p].c_str(),s));
                        UniversalE4vFunction(Data_2261[1][p][s], "Pinned Data", "4He", "2_261", TString::Format("data %s %i",second_en[1][p].c_str(),s));
                        UniversalE4vFunction(Data_2261[2][p][s], "Pinned Data", "4He", "2_261", TString::Format("data %s %i",second_en[2][p].c_str(),s));
                        UniversalE4vFunction(Data_4461[0][p][s], "Pinned Data", "4He", "4_461", TString::Format("data %s %i",third_en[0][p].c_str(),s));
                }
        }

// ---------------- Acceptance correct all histograms ---------------------
        TCanvas *ca = new TCanvas("corrections can"," corrections can",800,800);
        if(make_plots) {
                
                ca->SaveAs("He4_true_vs_truereco.pdf(");
                ca->SaveAs("He4_truerecorad_vs_truereco.pdf(");
                ca->SaveAs("He4_Acceptance_Ratios.pdf(");
                ca->SaveAs("He4_Rad_Ratios.pdf(");
        }
        
        
        for(int p = 0; p < 2; p++) {
                for(int s : sectors) {
                        if(p == 1) s = (s+3)%6;
                        //2261
                        for(int r = 0; r < 3; r++) {
                                SuSA_2261[r][p][s]->SetTitle(TString::Format("SuSA %s Sector %i",second_en[r][p].c_str(),s));
                                G_2261[r][p][s]->SetTitle(TString::Format("G18 %s Sector %i",second_en[r][p].c_str(),s));

                                Data_2261[r][p][s] = (TH1D*)AcceptanceCorrect(Data_2261[r][p][s], SuSA_2261_true[r][p][s], SuSA_2261_true_reco[r][p][s], G_2261_true[r][p][s], G_2261_true_reco[r][p][s], SuSA_2261_true_reco_rad[r][p][s], false, "data");
                                SuSA_2261[r][p][s] = (TH1D*)AcceptanceCorrect(SuSA_2261[r][p][s], SuSA_2261_true[r][p][s], SuSA_2261_true_reco[r][p][s], G_2261_true[r][p][s], G_2261_true_reco[r][p][s], SuSA_2261_true_reco_rad[r][p][s], make_plots, "SuSA");
                                G_2261[r][p][s] = (TH1D*)AcceptanceCorrect(G_2261[r][p][s], SuSA_2261_true[r][p][s], SuSA_2261_true_reco[r][p][s], G_2261_true[r][p][s], G_2261_true_reco[r][p][s], SuSA_2261_true_reco_rad[r][p][s], make_plots, "G");
                        }
                

                        //4461
                        for(int r = 0; r < 1; r++) {
                                SuSA_4461[r][p][s]->SetTitle(TString::Format("SuSA %s Sector %i",third_en[r][p].c_str(),s));
                                G_4461[r][p][s]->SetTitle(TString::Format("G18 %s Sector %i",third_en[r][p].c_str(),s));

                                Data_4461[r][p][s] = (TH1D*)AcceptanceCorrect(Data_4461[r][p][s], SuSA_4461_true[r][p][s], SuSA_4461_true_reco[r][p][s], G_4461_true[r][p][s], G_4461_true_reco[r][p][s], SuSA_4461_true_reco_rad[r][p][s], false, "data");
                                SuSA_4461[r][p][s] = (TH1D*)AcceptanceCorrect(SuSA_4461[r][p][s], SuSA_4461_true[r][p][s], SuSA_4461_true_reco[r][p][s], G_4461_true[r][p][s], G_4461_true_reco[r][p][s], SuSA_4461_true_reco_rad[r][p][s], make_plots, "SuSA");
                                G_4461[r][p][s] = (TH1D*)AcceptanceCorrect(G_4461[r][p][s], SuSA_4461_true[r][p][s], SuSA_4461_true_reco[r][p][s], G_4461_true[r][p][s], G_4461_true_reco[r][p][s], SuSA_4461_true_reco_rad[r][p][s], make_plots, "G");
                        }
                }
        }
        
        
        if(make_plots) {
                ca->SaveAs("He4_true_vs_truereco.pdf)");
                ca->SaveAs("He4_truerecorad_vs_truereco.pdf)");
                ca->SaveAs("He4_Acceptance_Ratios.pdf)");
                ca->SaveAs("He4_Rad_Ratios.pdf)");
        }


// ---------------- Get average proton momentum for data and MC ------------------------
        
        double data_avg_prot_mom_2261[3][6];
        double data_avg_prot_mom_4461[1][6];

        double SuSA_avg_prot_mom_2261[3][6];
        double SuSA_avg_prot_mom_4461[1][6];

        double G_avg_prot_mom_2261[3][6];
        double G_avg_prot_mom_4461[1][6];

        for(int s : sectors) {
                data_avg_prot_mom_2261[0][s] = weighted_average(Data_2261[0][0][s]); 
                data_avg_prot_mom_2261[1][s] = weighted_average(Data_2261[1][0][s]); 
                data_avg_prot_mom_2261[2][s] = weighted_average(Data_2261[2][0][s]);
                data_avg_prot_mom_4461[0][s] = weighted_average(Data_4461[0][0][s]); 

                SuSA_avg_prot_mom_2261[0][s] = weighted_average(SuSA_2261[0][0][s]); 
                SuSA_avg_prot_mom_2261[1][s] = weighted_average(SuSA_2261[1][0][s]); 
                SuSA_avg_prot_mom_2261[2][s] = weighted_average(SuSA_2261[2][0][s]);
                SuSA_avg_prot_mom_4461[0][s] = weighted_average(SuSA_4461[0][0][s]); 

                G_avg_prot_mom_2261[0][s] = weighted_average(G_2261[0][0][s]); 
                G_avg_prot_mom_2261[1][s] = weighted_average(G_2261[1][0][s]); 
                G_avg_prot_mom_2261[2][s] = weighted_average(G_2261[2][0][s]);
                G_avg_prot_mom_4461[0][s] = weighted_average(G_4461[0][0][s]); 
        }

// -------------- Add systematic uncertainties ---------------------------

        
        for(int p = 0; p < 2; p++) {
                for(int s : sectors) {
                        if(p == 1) s = (s+3)%6;
                        //2261
                        for(int r = 0; r < 3; r++) {
                                ApplySystUnc(Data_2261[r][p][s],"2_261"); 
                                ApplySystUnc(SuSA_2261[r][p][s],"2_261");
                                ApplySystUnc(G_2261[r][p][s],"2_261");
                        }

                        //4461
                        for(int r = 0; r < 1; r++) {
                                ApplySystUnc(Data_4461[r][p][s],"4_461"); 
                                ApplySystUnc(SuSA_4461[r][p][s],"4_461");
                                ApplySystUnc(G_4461[r][p][s],"4_461");
                        }
                }
        }

// -------------- Correct for MEC and neutron contamination --------------
        //Correct Data by (1-(MECfrac))*(G18_prot/(G18_prot + G18_neut))
        //Correct MC by (1-(MECfrac))*(SuSA_prot/(SuSA_prot + SuSA_neut))


        for(int p = 0; p < 2; p++) {
                for(int s : sectors) {
                        if(p == 1) s = (s+3)%6;
                        //2261
                        for(int r = 0; r < 3; r++) {
                                //Data_2261[r][p][s]->Scale((1. - mec_corr_2261[r][p][s]));
                                //SuSA_2261[r][p][s]->Scale((1. - mec_corr_2261[r][p][s]));
                                //G_2261[r][p][s]->Scale((1. - mec_corr_G_2261[r][p][s]));
                                if(p == 1) {    
                                        SuSA_2261[r][p][s]->Scale(neutron_corr_2261_susa[r][p]);
                                        Data_2261[r][p][s]->Scale(neutron_corr_2261_G18[r][p]);
                                        G_2261[r][p][s]->Scale(neutron_corr_2261_G18[r][p]);
                                }
                        }
                

                        //4461
                        for(int r = 0; r < 1; r++) {
                                //Data_4461[r][p][s]->Scale((1. - mec_corr_4461[r][p][s]));
                                //SuSA_4461[r][p][s]->Scale((1. - mec_corr_4461[r][p][s]));
                                //G_4461[r][p][s]->Scale((1. - mec_corr_G_4461[r][p][s]));
                                if(p == 1) {    
                                        SuSA_4461[r][p][s]->Scale(neutron_corr_4461_susa[r][p]);
                                        Data_4461[r][p][s]->Scale(neutron_corr_4461_G18[r][p]);
                                        G_4461[r][p][s]->Scale(neutron_corr_4461_G18[r][p]);
                                }
                        }
                }
        }


//Combine histograms to get overall average proton momentum
        TH1D* Data_comb_2261[3][2];
        TH1D* Data_comb_4461[1][2];
        TH1D* SuSA_comb_2261[3][2];
        TH1D* SuSA_comb_4461[1][2];
        TH1D* G_comb_2261[3][2];
        TH1D* G_comb_4461[1][2];
        
        for(int p = 0; p < 2; p++ ) {
                for(int r = 0; r < 3; r++) {
                        for(int s : sectors ){
                                if(p == 1) s = (s+3)%6;

                                if((p == 0 && s == 2) || (p == 1 && s == 5)) {
                                        Data_comb_2261[r][p] = (TH1D*)( Data_2261[r][p][s]->Clone() );
                                        SuSA_comb_2261[r][p] = (TH1D*)( SuSA_2261[r][p][s]->Clone() );
                                        G_comb_2261[r][p] = (TH1D*)(G_2261[r][p][s]->Clone() );

                                }
                                if((p == 0 && s != 2) || (p == 1 && s != 5)) {
                                        Data_comb_2261[r][p]->Add( Data_2261[r][p][s] );
                                        SuSA_comb_2261[r][p]->Add( SuSA_2261[r][p][s] );
                                        G_comb_2261[r][p]->Add( G_2261[r][p][s] );
                                }

                        }
                }       
                
                for(int r = 0; r < 1; r++) {
                        for(int s : sectors ) {
                                if(p == 1) s = (s+3)%6;

                                if((p == 0 && s == 2) || (p == 1 && s == 5)) {
                                        Data_comb_4461[r][p] = (TH1D*)( Data_4461[r][p][s]->Clone() );
                                        SuSA_comb_4461[r][p] = (TH1D*)( SuSA_4461[r][p][s]->Clone() );
                                        G_comb_4461[r][p] = (TH1D*)( G_4461[r][p][s]->Clone() );
                                }
                                if((p == 0 && s != 2) || (p == 1 && s != 5)) {
                                        Data_comb_4461[r][p]->Add( Data_4461[r][p][s] );
                                        SuSA_comb_4461[r][p]->Add( SuSA_4461[r][p][s] );
                                        G_comb_4461[r][p]->Add( G_4461[r][p][s] );
                                }
                        }
                        
                }
        }

        // ---------------- Make plots of reconstructed momentum distributions for acc corrected data/MC ------------

        if(make_plots) {
                TCanvas* reco_dist_canvas = new TCanvas("reco can","reco can",1000,800);
                reco_dist_canvas->SaveAs("He4_reco_dist.pdf(");

                TLegend *leg2261[3][2][6];
                TLegend *leg4461[1][2][6];

                for(int s : sectors) {
                        for(int p = 0; p < 2; p++) {
                                if(p == 1) s = (s+3)%6;
                                for(int r = 0; r< 3; r++ ) {
                                        leg2261[r][p][s] = new TLegend(0.7,0.75,0.89,0.89);
                                        SuSA_2261[r][p][s]->Draw("e hist");
                                        Data_2261[r][p][s]->Draw("e same");
                                        SuSA_2261[r][p][s]->SetTitle("SuSA_v2 He4");
                                        Data_2261[r][p][s]->SetTitle("Data He4");
                                        G_2261[r][p][s]->Draw("e same");
                                        G_2261[r][p][s]->SetTitle("G18 He4");
                                        G_2261[r][p][s]->SetLineColor(kRed);
                                        leg2261[r][p][s]->AddEntry(G_2261[r][p][s]);
                                        Data_2261[r][p][s]->SetMarkerColor(kBlack);
                                        Data_2261[r][p][s]->SetMarkerStyle(20);
                                        SuSA_2261[r][p][s]->GetYaxis()->SetTitle("Absolute Number of Events ");
                                        SuSA_2261[r][p][s]->GetXaxis()->SetTitle("Momentum (GeV)");
                                        leg2261[r][p][s]->AddEntry(Data_2261[r][p][s]);
                                        leg2261[r][p][s]->AddEntry(SuSA_2261[r][p][s]);
                                        leg2261[r][p][s]->Draw();
                                        SuSA_2261[r][p][s]->SetTitle(TString::Format("SuSA_v2 He4 %s Sector %i", second_en[r][p].c_str(), s));
                                        reco_dist_canvas->SaveAs("He4_reco_dist.pdf");
                                }


                                for(int r = 0; r < 1; r++ ) {
                                        leg4461[r][p][s] = new TLegend(0.7,0.75,0.89,0.89);
                                        SuSA_4461[r][p][s]->Draw("e hist");
                                        Data_4461[r][p][s]->Draw("e same");
                                        SuSA_4461[r][p][s]->SetTitle("SuSA_v2 He4");
                                        Data_4461[r][p][s]->SetTitle("Data He4");
                                        G_4461[r][p][s]->Draw("e same");
                                        G_4461[r][p][s]->SetTitle("G18 He4");
                                        G_4461[r][p][s]->SetLineColor(kRed);
                                        leg4461[r][p][s]->AddEntry(G_2261[r][p][s]);
                                        Data_4461[r][p][s]->SetMarkerColor(kBlack);
                                        Data_4461[r][p][s]->SetMarkerStyle(20);
                                        SuSA_4461[r][p][s]->GetYaxis()->SetTitle("Absolute Number of Events");
                                        SuSA_4461[r][p][s]->GetXaxis()->SetTitle("Momentum (GeV)");
                                        leg4461[r][p][s]->AddEntry(Data_2261[r][p][s]);
                                        leg4461[r][p][s]->AddEntry(SuSA_2261[r][p][s]);
                                        leg4461[r][p][s]->Draw();
                                        SuSA_4461[r][p][s]->SetTitle(TString::Format("SuSA_v2 He4 %s Sector %i", third_en[r][p].c_str(), s));
                                        reco_dist_canvas->SaveAs("He4_reco_dist.pdf");
                                }
                        }
                }
                reco_dist_canvas->SaveAs("He4_reco_dist.pdf)");
        }


        double data_comb_int_2261[3][2];
        double data_comb_int_4461[1][2];
        double data_comb_int_2261_err[3][2];
        double data_comb_int_4461_err[1][2];

        double SuSA_comb_int_2261[3][2];
        double SuSA_comb_int_4461[1][2];
        double SuSA_comb_int_2261_err[3][2];
        double SuSA_comb_int_4461_err[1][2];

        double G_comb_int_2261[3][2];
        double G_comb_int_4461[1][2];
        double G_comb_int_2261_err[3][2];
        double G_comb_int_4461_err[1][2];

        std::cout << "Combined Yields for Data and MC" << "\n";

        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 3; r++) {
                        data_comb_int_2261[r][p] = Data_comb_2261[r][p]->IntegralAndError(1, Data_comb_2261[r][p]->GetNbinsX(), data_comb_int_2261_err[r][p],"width");
                        SuSA_comb_int_2261[r][p] = SuSA_comb_2261[r][p]->IntegralAndError(1, SuSA_comb_2261[r][p]->GetNbinsX(), SuSA_comb_int_2261_err[r][p],"width");
                        G_comb_int_2261[r][p] = G_comb_2261[r][p]->IntegralAndError(1, G_comb_2261[r][p]->GetNbinsX(), G_comb_int_2261_err[r][p],"width");
                                //std::cout << "Data " << second_en[r][p] << " = " << data_comb_int_2261[r][p] << " p/m " << data_comb_int_2261_err[r][p] <<  "\n";
                                //std::cout << "SuSA " << second_en[r][p] << " = " << SuSA_comb_int_2261[r][p] << " p/m " << SuSA_comb_int_2261_err[r][p] << "\n";
                                //std::cout << "G    " << second_en[r][p] << " = " << G_comb_int_2261[r][p] << " p/m " << G_comb_int_2261_err[r][p] << "\n";
                }
                for(int r = 0; r < 1; r++) {
                        data_comb_int_4461[r][p] = Data_comb_4461[r][p]->IntegralAndError(1, Data_comb_4461[r][p]->GetNbinsX(), data_comb_int_4461_err[r][p],"width");
                        SuSA_comb_int_4461[r][p] = SuSA_comb_4461[r][p]->IntegralAndError(1, SuSA_comb_4461[r][p]->GetNbinsX(), SuSA_comb_int_4461_err[r][p],"width");
                        G_comb_int_4461[r][p] = G_comb_4461[r][p]->IntegralAndError(1, G_comb_4461[r][p]->GetNbinsX(), G_comb_int_4461_err[r][p],"width");
                                //std::cout << "Data " << third_en[r][p] << " = " << data_comb_int_4461[r][p] << " p/m " << data_comb_int_4461_err[r][p] << "\n";
                                //std::cout << "SuSA " << third_en[r][p] << " = " << SuSA_comb_int_4461[r][p] << " p/m " << SuSA_comb_int_4461_err[r][p] << "\n"; 
                                //std::cout << "G    " << third_en[r][p] << " = " << G_comb_int_4461[r][p] << " p/m " << G_comb_int_4461_err[r][p] << "\n";         
                }
        }

        double data_comb_avg_prot_mom_2261[3];
        double data_comb_avg_prot_mom_4461[1];

        double SuSA_comb_avg_prot_mom_2261[3];
        double SuSA_comb_avg_prot_mom_4461[1];

        double G_comb_avg_prot_mom_2261[3];
        double G_comb_avg_prot_mom_4461[1];

        data_comb_avg_prot_mom_2261[0] = weighted_average(Data_comb_2261[0][0]); 
        data_comb_avg_prot_mom_2261[1] = weighted_average(Data_comb_2261[1][0]); 
        data_comb_avg_prot_mom_2261[2] = weighted_average(Data_comb_2261[2][0]);
        data_comb_avg_prot_mom_4461[0] = weighted_average(Data_comb_4461[0][0]); 

        SuSA_comb_avg_prot_mom_2261[0] = weighted_average(SuSA_comb_2261[0][0]); 
        SuSA_comb_avg_prot_mom_2261[1] = weighted_average(SuSA_comb_2261[1][0]); 
        SuSA_comb_avg_prot_mom_2261[2] = weighted_average(SuSA_comb_2261[2][0]);
        SuSA_comb_avg_prot_mom_4461[0] = weighted_average(SuSA_comb_4461[0][0]); 

        G_comb_avg_prot_mom_2261[0] = weighted_average(G_comb_2261[0][0]); 
        G_comb_avg_prot_mom_2261[1] = weighted_average(G_comb_2261[1][0]); 
        G_comb_avg_prot_mom_2261[2] = weighted_average(G_comb_2261[2][0]);
        G_comb_avg_prot_mom_4461[0] = weighted_average(G_comb_4461[0][0]); 

        


// -------------- Integrate sector by sector histograms -----------------

        double data_int_2261[3][2][6];
        double data_int_4461[1][2][6];
        double data_int_2261_err[3][2][6];
        double data_int_4461_err[1][2][6];

        double SuSA_int_2261[3][2][6];
        double SuSA_int_4461[1][2][6];
        double SuSA_int_2261_err[3][2][6];
        double SuSA_int_4461_err[1][2][6];

        double G_int_2261[3][2][6];
        double G_int_4461[1][2][6];
        double G_int_2261_err[3][2][6];
        double G_int_4461_err[1][2][6];

        std::cout << "Sector by Sector Yields for Data and MC" << "\n";
        
        for(int s : sectors) {
                for(int p = 0; p < 2; p++) {
                        if(p == 1) s = (s+3)%6;
                        std::cout << "Sector " << s << "\n";
 
                        //2261
                        for(int r = 0; r < 3; r++) {
                                data_int_2261[r][p][s] = Data_2261[r][p][s]->IntegralAndError(1, Data_2261[r][p][s]->GetNbinsX(), data_int_2261_err[r][p][s],"width");
                                SuSA_int_2261[r][p][s] = SuSA_2261[r][p][s]->IntegralAndError(1, SuSA_2261[r][p][s]->GetNbinsX(), SuSA_int_2261_err[r][p][s],"width");
                                G_int_2261[r][p][s] = G_2261[r][p][s]->IntegralAndError(1, G_2261[r][p][s]->GetNbinsX(), G_int_2261_err[r][p][s],"width");
                                //std::cout << "Data " << second_en[r][p] << " = " << data_int_2261[r][p][s] << " p/m " << data_int_2261_err[r][p][s] << "\n";
                                //std::cout << "SuSA " << second_en[r][p] << " = " << SuSA_int_2261[r][p][s] << " p/m " << SuSA_int_2261_err[r][p][s]  << "\n";
                                //std::cout << "G    " << second_en[r][p] << " = " << G_int_2261[r][p][s] << " p/m " << G_int_2261_err[r][p][s]  << "\n";
                        }

                        //4461
                        for(int r = 0; r < 1; r++) {
                                data_int_4461[r][p][s] = Data_4461[r][p][s]->IntegralAndError(1, Data_4461[r][p][s]->GetNbinsX(), data_int_4461_err[r][p][s],"width");
                                SuSA_int_4461[r][p][s] = SuSA_4461[r][p][s]->IntegralAndError(1, SuSA_4461[r][p][s]->GetNbinsX(), SuSA_int_4461_err[r][p][s],"width");
                                G_int_4461[r][p][s] = G_4461[r][p][s]->IntegralAndError(1, G_4461[r][p][s]->GetNbinsX(), G_int_4461_err[r][p][s],"width");
                                //std::cout << "Data " << third_en[r][p] << " = " << data_int_4461[r][p][s] << " p/m " << data_int_4461_err[r][p][s]  << "\n";
                                //std::cout << "SuSA " << third_en[r][p] << " = " << SuSA_int_4461[r][p][s] << " p/m " << SuSA_int_4461_err[r][p][s]  << "\n";
                                //std::cout << "G    " << third_en[r][p] << " = " << G_int_4461[r][p][s] << " p/m " << G_int_4461_err[r][p][s]  << "\n";
                        }
                }
        }

// ----------- Take Ratios to obtain transparencies and errors --------------
        //Remember that a proton in sector i corresponds to an electron in sector (i-3)

        // Sector by sector data transparencies
        double data_T_2261[3][6];
        double data_T_4461[1][6];
        double data_T_2261_err[3][6];
        double data_T_4461_err[1][6];

        // Spread in data transparencies
        double data_spread_T_2261[3];
        double data_spread_T_4461[1];
        double data_spread_T_2261_err[3];
        double data_spread_T_4461_err[1];

        // Sector by sector susa transparencies
        double SuSA_T_2261[3][6];
        double SuSA_T_4461[1][6];
        double SuSA_T_2261_err[3][6];
        double SuSA_T_4461_err[1][6];

        // Spread in susa transparencies
        double SuSA_spread_T_2261[3];
        double SuSA_spread_T_4461[1];
        double SuSA_spread_T_2261_err[3];
        double SuSA_spread_T_4461_err[1];

        // Sector by sector G18 transparencies
        double G_T_2261[3][6];
        double G_T_4461[1][6];
        double G_T_2261_err[3][6];
        double G_T_4461_err[1][6];

        // Spread in G18 transparencies
        double G_spread_T_2261[3];
        double G_spread_T_4461[1];
        double G_spread_T_2261_err[3];
        double G_spread_T_4461_err[1];

        // Data combined transparencies
        double data_comb_T_2261[3];
        double data_comb_T_4461[1];
        double data_comb_T_2261_err[3];
        double data_comb_T_4461_err[1];

        // SuSA combined transparencies
        double SuSA_comb_T_2261[3];
        double SuSA_comb_T_4461[1];
        double SuSA_comb_T_2261_err[3];
        double SuSA_comb_T_4461_err[1];

        // G18 combined transparencies
        double G_comb_T_2261[3];
        double G_comb_T_4461[1];
        double G_comb_T_2261_err[3];
        double G_comb_T_4461_err[1];

        // Compute transparencies and errors by sector
        for(int s : sectors) {
                data_T_2261[0][s] = myratio(data_int_2261[0][0][s],data_int_2261[0][1][(s+3)%6]);
                data_T_2261[1][s] = myratio(data_int_2261[1][0][s],data_int_2261[1][1][(s+3)%6]);
                data_T_2261[2][s] = myratio(data_int_2261[2][0][s],data_int_2261[2][1][(s+3)%6]);
                data_T_4461[0][s] = myratio(data_int_4461[0][0][s],data_int_4461[0][1][(s+3)%6]);

                data_T_2261_err[0][s] = get_ratio_error(data_int_2261[0][0][s],data_int_2261[0][1][(s+3)%6]);
                data_T_2261_err[1][s] = get_ratio_error(data_int_2261[1][0][s],data_int_2261[1][1][(s+3)%6]);
                data_T_2261_err[2][s] = get_ratio_error(data_int_2261[2][0][s],data_int_2261[2][1][(s+3)%6]);
                data_T_4461_err[0][s] = get_ratio_error(data_int_4461[0][0][s],data_int_4461[0][1][(s+3)%6]);

                SuSA_T_2261[0][s] = myratio(SuSA_int_2261[0][0][s],SuSA_int_2261[0][1][(s+3)%6]);
                SuSA_T_2261[1][s] = myratio(SuSA_int_2261[1][0][s],SuSA_int_2261[1][1][(s+3)%6]);
                SuSA_T_2261[2][s] = myratio(SuSA_int_2261[2][0][s],SuSA_int_2261[2][1][(s+3)%6]);
                SuSA_T_4461[0][s] = myratio(SuSA_int_4461[0][0][s],SuSA_int_4461[0][1][(s+3)%6]);

                SuSA_T_2261_err[0][s] = get_ratio_error(SuSA_int_2261[0][0][s],SuSA_int_2261[0][1][(s+3)%6]);
                SuSA_T_2261_err[1][s] = get_ratio_error(SuSA_int_2261[1][0][s],SuSA_int_2261[1][1][(s+3)%6]);
                SuSA_T_2261_err[2][s] = get_ratio_error(SuSA_int_2261[2][0][s],SuSA_int_2261[2][1][(s+3)%6]);
                SuSA_T_4461_err[0][s] = get_ratio_error(SuSA_int_4461[0][0][s],SuSA_int_4461[0][1][(s+3)%6]);

                G_T_2261[0][s] = myratio(G_int_2261[0][0][s],G_int_2261[0][1][(s+3)%6]);
                G_T_2261[1][s] = myratio(G_int_2261[1][0][s],G_int_2261[1][1][(s+3)%6]);
                G_T_2261[2][s] = myratio(G_int_2261[2][0][s],G_int_2261[2][1][(s+3)%6]);
                G_T_4461[0][s] = myratio(G_int_4461[0][0][s],G_int_4461[0][1][(s+3)%6]);

                G_T_2261_err[0][s] = get_ratio_error(G_int_2261[0][0][s],G_int_2261[0][1][(s+3)%6]);
                G_T_2261_err[1][s] = get_ratio_error(G_int_2261[1][0][s],G_int_2261[1][1][(s+3)%6]);
                G_T_2261_err[2][s] = get_ratio_error(G_int_2261[2][0][s],G_int_2261[2][1][(s+3)%6]);
                G_T_4461_err[0][s] = get_ratio_error(G_int_4461[0][0][s],G_int_4461[0][1][(s+3)%6]);
        }


        //Compute spread of transparencies
        for(int s : sectors) { 
                if(s != 3) {
                        data_spread_T_2261[0] += diff_squared(data_T_2261[0][3],data_T_2261[0][s]);
                        data_spread_T_2261[1] += diff_squared(data_T_2261[1][3],data_T_2261[1][s]);
                        data_spread_T_2261[2] += diff_squared(data_T_2261[2][3],data_T_2261[2][s]);
                        data_spread_T_4461[0] += diff_squared(data_T_4461[0][3],data_T_4461[0][s]);

                        SuSA_spread_T_2261[0] += diff_squared(SuSA_T_2261[0][3],SuSA_T_2261[0][s]);
                        SuSA_spread_T_2261[1] += diff_squared(SuSA_T_2261[1][3],SuSA_T_2261[1][s]);
                        SuSA_spread_T_2261[2] += diff_squared(SuSA_T_2261[2][3],SuSA_T_2261[2][s]);
                        SuSA_spread_T_4461[0] += diff_squared(SuSA_T_4461[0][3],SuSA_T_4461[0][s]);

                        G_spread_T_2261[0] += diff_squared(G_T_2261[0][3],G_T_2261[0][s]);
                        G_spread_T_2261[1] += diff_squared(G_T_2261[1][3],G_T_2261[1][s]);
                        G_spread_T_2261[2] += diff_squared(G_T_2261[2][3],G_T_2261[2][s]);
                        G_spread_T_4461[0] += diff_squared(G_T_4461[0][3],G_T_4461[0][s]);
                }
        }

        // Take sqrt of sector by sector uncertainty and then add them to overall uncertainty 
        data_spread_T_2261[0] = sqrt(data_spread_T_2261[0]/num_2261_sec);
        data_spread_T_2261[1] = sqrt(data_spread_T_2261[1]/num_2261_sec);
        data_spread_T_2261[2] = sqrt(data_spread_T_2261[2]/num_2261_sec);
        data_spread_T_4461[0] = sqrt(data_spread_T_4461[0]/num_4461_sec);
        std::cout << "Data spread 2261 range 1 = " << data_spread_T_2261[0] << "\n";
        std::cout << "Data spread 2261 range 2 = " << data_spread_T_2261[1] << "\n";
        std::cout << "Data spread 2261 range 3 = " << data_spread_T_2261[2] << "\n";
        std::cout << "Data spread 4461 range 1 = " << data_spread_T_4461[0] << "\n";

        SuSA_spread_T_2261[0] = sqrt(SuSA_spread_T_2261[0]/num_2261_sec);
        SuSA_spread_T_2261[1] = sqrt(SuSA_spread_T_2261[1]/num_2261_sec);
        SuSA_spread_T_2261[2] = sqrt(SuSA_spread_T_2261[2]/num_2261_sec);
        SuSA_spread_T_4461[0] = sqrt(SuSA_spread_T_4461[0]/num_4461_sec);
        std::cout << "susa spread 2261 range 1 = " << SuSA_spread_T_2261[0] << "\n";
        std::cout << "susa spread 2261 range 2 = " << SuSA_spread_T_2261[1] << "\n";
        std::cout << "susa spread 2261 range 3 = " << SuSA_spread_T_2261[2] << "\n";
        std::cout << "susa spread 4461 range 1 = " << SuSA_spread_T_4461[0] << "\n";

        G_spread_T_2261[0] = sqrt(G_spread_T_2261[0]/num_2261_sec);
        G_spread_T_2261[1] = sqrt(G_spread_T_2261[1]/num_2261_sec);
        G_spread_T_2261[2] = sqrt(G_spread_T_2261[2]/num_2261_sec);
        G_spread_T_4461[0] = sqrt(G_spread_T_4461[0]/num_4461_sec);
        std::cout << "G spread 2261 range 1 = " << G_spread_T_2261[0] << "\n";
        std::cout << "G spread 2261 range 2 = " << G_spread_T_2261[1] << "\n";
        std::cout << "G spread 2261 range 3 = " << G_spread_T_2261[2] << "\n";
        std::cout << "G spread 4461 range 1 = " << G_spread_T_4461[0] << "\n";

        //Get combined transparencies and errors
        data_comb_T_2261[0] = myratio(data_comb_int_2261[0][0],data_comb_int_2261[0][1]);
        data_comb_T_2261[1] = myratio(data_comb_int_2261[1][0],data_comb_int_2261[1][1]);
        data_comb_T_2261[2] = myratio(data_comb_int_2261[2][0],data_comb_int_2261[2][1]);
        data_comb_T_4461[0] = myratio(data_comb_int_4461[0][0],data_comb_int_4461[0][1]);

        data_comb_T_2261_err[0] = get_ratio_error(data_comb_int_2261[0][0],data_comb_int_2261[0][1]);
        data_comb_T_2261_err[1] = get_ratio_error(data_comb_int_2261[1][0],data_comb_int_2261[1][1]);
        data_comb_T_2261_err[2] = get_ratio_error(data_comb_int_2261[2][0],data_comb_int_2261[2][1]);
        data_comb_T_4461_err[0] = get_ratio_error(data_comb_int_4461[0][0],data_comb_int_4461[0][1]);

        SuSA_comb_T_2261[0] = myratio(SuSA_comb_int_2261[0][0],SuSA_comb_int_2261[0][1]);
        SuSA_comb_T_2261[1] = myratio(SuSA_comb_int_2261[1][0],SuSA_comb_int_2261[1][1]);
        SuSA_comb_T_2261[2] = myratio(SuSA_comb_int_2261[2][0],SuSA_comb_int_2261[2][1]);
        SuSA_comb_T_4461[0] = myratio(SuSA_comb_int_4461[0][0],SuSA_comb_int_4461[0][1]);

        SuSA_comb_T_2261_err[0] = get_ratio_error(SuSA_comb_int_2261[0][0],SuSA_comb_int_2261[0][1]);
        SuSA_comb_T_2261_err[1] = get_ratio_error(SuSA_comb_int_2261[1][0],SuSA_comb_int_2261[1][1]);
        SuSA_comb_T_2261_err[2] = get_ratio_error(SuSA_comb_int_2261[2][0],SuSA_comb_int_2261[2][1]);
        SuSA_comb_T_4461_err[0] = get_ratio_error(SuSA_comb_int_4461[0][0],SuSA_comb_int_4461[0][1]);

        G_comb_T_2261[0] = myratio(G_comb_int_2261[0][0],G_comb_int_2261[0][1]);
        G_comb_T_2261[1] = myratio(G_comb_int_2261[1][0],G_comb_int_2261[1][1]);
        G_comb_T_2261[2] = myratio(G_comb_int_2261[2][0],G_comb_int_2261[2][1]);
        G_comb_T_4461[0] = myratio(G_comb_int_4461[0][0],G_comb_int_4461[0][1]);

        G_comb_T_2261_err[0] = get_ratio_error(G_comb_int_2261[0][0],G_comb_int_2261[0][1]);
        G_comb_T_2261_err[1] = get_ratio_error(G_comb_int_2261[1][0],G_comb_int_2261[1][1]);
        G_comb_T_2261_err[2] = get_ratio_error(G_comb_int_2261[2][0],G_comb_int_2261[2][1]);
        G_comb_T_4461_err[0] = get_ratio_error(G_comb_int_4461[0][0],G_comb_int_4461[0][1]);


// ---------------------------------------------------------------------

        double ypoints[6][4]; 
        double ypoint_errs[6][4]; 
        double xpoints[6][4]; 
        double xpoint_errs[6][4]; 

        double mc_ypoints[6][4];
        double mc_ypoint_errs[6][4];
        double mc_xpoints[6][4]; 
        double mc_xpoint_errs[6][4];

        double G_mc_ypoints[6][4];
        double G_mc_ypoint_errs[6][4];
        double G_mc_xpoints[6][4]; 

        // Add all the transparencies by sectors to arrays
        for(int s : sectors) {
                
                ypoints[s][0] = data_T_2261[0][s];
                ypoints[s][1] = data_T_2261[1][s];
                ypoints[s][2] = data_T_2261[2][s];
                ypoints[s][3] = data_T_4461[0][s];
                
                ypoint_errs[s][0] = data_T_2261_err[0][s];
                ypoint_errs[s][1] = data_T_2261_err[1][s];
                ypoint_errs[s][2] = data_T_2261_err[2][s];
                ypoint_errs[s][3] = data_T_4461_err[0][s];
                
                xpoints[s][0] = data_avg_prot_mom_2261[0][s];
                xpoints[s][1] = data_avg_prot_mom_2261[1][s];
                xpoints[s][2] = data_avg_prot_mom_2261[2][s];
                xpoints[s][3] = data_avg_prot_mom_4461[0][s];
                
                mc_ypoints[s][0] = SuSA_T_2261[0][s];
                mc_ypoints[s][1] = SuSA_T_2261[1][s];
                mc_ypoints[s][2] = SuSA_T_2261[2][s];
                mc_ypoints[s][3] = SuSA_T_4461[0][s];

                mc_ypoint_errs[s][0] = SuSA_T_2261_err[0][s];
                mc_ypoint_errs[s][1] = SuSA_T_2261_err[1][s];
                mc_ypoint_errs[s][2] = SuSA_T_2261_err[2][s];
                mc_ypoint_errs[s][3] = SuSA_T_4461_err[0][s];

                G_mc_ypoints[s][0] = G_T_2261[0][s];
                G_mc_ypoints[s][1] = G_T_2261[1][s];
                G_mc_ypoints[s][2] = G_T_2261[2][s];
                G_mc_ypoints[s][3] = G_T_4461[0][s];

                G_mc_ypoint_errs[s][0] = G_T_2261_err[0][s];
                G_mc_ypoint_errs[s][1] = G_T_2261_err[1][s];
                G_mc_ypoint_errs[s][2] = G_T_2261_err[2][s];
                G_mc_ypoint_errs[s][3] = G_T_4461_err[0][s];

                mc_xpoints[s][0] = SuSA_avg_prot_mom_2261[0][s];
                mc_xpoints[s][1] = SuSA_avg_prot_mom_2261[1][s];
                mc_xpoints[s][2] = SuSA_avg_prot_mom_2261[2][s];
                mc_xpoints[s][3] = SuSA_avg_prot_mom_4461[0][s];

                G_mc_xpoints[s][0] = SuSA_avg_prot_mom_2261[0][s];
                G_mc_xpoints[s][1] = SuSA_avg_prot_mom_2261[1][s];
                G_mc_xpoints[s][2] = SuSA_avg_prot_mom_2261[2][s];
                G_mc_xpoints[s][3] = SuSA_avg_prot_mom_4461[0][s];

                for(int i = 0; i < 4; i++) {
                        xpoint_errs[s][i] = 0.0;
                        mc_xpoint_errs[s][i] = 0.0;
                }
        }

        double comb_ypoints[4] = {data_comb_T_2261[0], data_comb_T_2261[1], data_comb_T_2261[2], data_comb_T_4461[0]};

        double comb_ypoint_errs[4];
        comb_ypoint_errs[0] = sqrt(pow(data_comb_T_2261_err[0],2) + pow(data_spread_T_2261[0],2));
        comb_ypoint_errs[1] = sqrt(pow(data_comb_T_2261_err[1],2) + pow(data_spread_T_2261[1],2));
        comb_ypoint_errs[2] = sqrt(pow(data_comb_T_2261_err[2],2) + pow(data_spread_T_2261[2],2));
        comb_ypoint_errs[3] = sqrt(pow(data_comb_T_4461_err[0],2) + pow(data_spread_T_4461[0],2));

        double comb_xpoints[4] = {data_comb_avg_prot_mom_2261[0], data_comb_avg_prot_mom_2261[1], data_comb_avg_prot_mom_2261[2], data_comb_avg_prot_mom_4461[0]};

        double comb_mc_ypoints[4] = {SuSA_comb_T_2261[0], SuSA_comb_T_2261[1], SuSA_comb_T_2261[2], SuSA_comb_T_4461[0]};

        double comb_mc_ypoint_errs[4];
        comb_mc_ypoint_errs[0] = sqrt(pow(SuSA_comb_T_2261_err[0],2) + pow(SuSA_spread_T_2261[0],2));
        comb_mc_ypoint_errs[1] = sqrt(pow(SuSA_comb_T_2261_err[1],2) + pow(SuSA_spread_T_2261[1],2));
        comb_mc_ypoint_errs[2] = sqrt(pow(SuSA_comb_T_2261_err[2],2) + pow(SuSA_spread_T_2261[2],2));
        comb_mc_ypoint_errs[3] = sqrt(pow(SuSA_comb_T_4461_err[0],2) + pow(SuSA_spread_T_4461[0],2));

        double comb_mc_xpoints[4] = {SuSA_comb_avg_prot_mom_2261[0], SuSA_comb_avg_prot_mom_2261[1], SuSA_comb_avg_prot_mom_2261[2], SuSA_comb_avg_prot_mom_4461[0]};

        double G_comb_mc_ypoints[4] = {G_comb_T_2261[0], G_comb_T_2261[1], G_comb_T_2261[2], G_comb_T_4461[0]};

        double G_comb_mc_ypoint_errs[4];
        G_comb_mc_ypoint_errs[0] = sqrt(pow(G_comb_T_2261_err[0],2) + pow(G_spread_T_2261[0],2));
        G_comb_mc_ypoint_errs[1] = sqrt(pow(G_comb_T_2261_err[1],2) + pow(G_spread_T_2261[1],2));
        G_comb_mc_ypoint_errs[2] = sqrt(pow(G_comb_T_2261_err[2],2) + pow(G_spread_T_2261[2],2));
        G_comb_mc_ypoint_errs[3] = sqrt(pow(G_comb_T_4461_err[0],2) + pow(G_spread_T_4461[0],2));

        double G_comb_mc_xpoints[4] = {G_comb_avg_prot_mom_2261[0], G_comb_avg_prot_mom_2261[1], G_comb_avg_prot_mom_2261[2], G_comb_avg_prot_mom_4461[0]};

        double comb_xpoint_errs[4] = {0.0,0.0,0.0,0.0};
        double comb_mc_xpoint_errs[4] = {0.0,0.0,0.0,0.0};

        std::map<int,int> color_options = {{2,2},{3,4},{4,6}};
        
        TCanvas* c_data;
        c_data = new TCanvas(TString::Format("Data transparency by sector"), TString::Format("Data transparency by sector"), 800, 600);

        TGraphErrors *data_t[6];
        TGraphErrors *data_comb_t;
        data_comb_t = new TGraphErrors(4, comb_xpoints, comb_ypoints, comb_xpoint_errs, comb_ypoint_errs);
        data_comb_t->SetTitle("All Sectors");
        data_comb_t->SetMarkerStyle(kFullCircle);
        data_comb_t->GetXaxis()->SetTitle("Proton Momentum (GeV)");
        data_comb_t->GetYaxis()->SetTitle("Transparency");
        data_comb_t->GetYaxis()->SetRangeUser(0,1.2);
	data_comb_t->SetMarkerColor(12);
        data_comb_t->Draw("AP");
        
        for(int s : sectors){

                data_t[s] = new TGraphErrors(4, xpoints[s], ypoints[s], xpoint_errs[s], ypoint_errs[s]);
                data_t[s]->SetTitle(TString::Format("Sector %i",s));
                data_t[s]->GetXaxis()->SetTitle("Proton Momentum (GeV)");
                data_t[s]->GetYaxis()->SetTitle("Transparency");
                data_t[s]->SetMarkerStyle(kFullCircle);
                data_t[s]->SetMarkerColor(color_options[s]);
                data_t[s]->Draw("P");
        }
        

        c_data->BuildLegend();
        
        TCanvas* c_susa;
        c_susa = new TCanvas(TString::Format("SuSA transparency by sector"), TString::Format("SuSA transparency by sector"), 800, 600);

        TGraphErrors *susa_t[6];
        TGraphErrors *susa_comb_t;
        susa_comb_t = new TGraphErrors(4, comb_mc_xpoints, comb_mc_ypoints, comb_mc_xpoint_errs, comb_mc_ypoint_errs);
        susa_comb_t->SetTitle("All Sectors");
        susa_comb_t->SetMarkerStyle(kFullCircle);
        susa_comb_t->GetXaxis()->SetTitle("Proton Momentum (GeV)");
        susa_comb_t->GetYaxis()->SetTitle("Transparency");
        susa_comb_t->GetYaxis()->SetRangeUser(0,1.2);
	susa_comb_t->SetMarkerColor(12);
        susa_comb_t->Draw("AP");

        for(int s : sectors){
                susa_t[s] = new TGraphErrors(4, mc_xpoints[s], mc_ypoints[s], mc_xpoint_errs[s], mc_ypoint_errs[s]);
                susa_t[s]->SetTitle(TString::Format("Sector %i",s));
                susa_t[s]->GetXaxis()->SetTitle("Proton Momentum (GeV)");
                susa_t[s]->GetYaxis()->SetTitle("Transparency");
                susa_t[s]->SetMarkerStyle(kFullCircle);
                susa_t[s]->SetMarkerColor(color_options[s]);
                susa_t[s]->Draw("P");
        }

        c_susa->BuildLegend();


        TCanvas* c_g;
        c_g = new TCanvas(TString::Format("G18 transparency by sector"), TString::Format("G18 transparency by sector"), 800, 600);

        TGraphErrors *G_t[6];
        TGraphErrors *G_comb_t;
        G_comb_t = new TGraphErrors(4, G_comb_mc_xpoints, G_comb_mc_ypoints, comb_mc_xpoint_errs, G_comb_mc_ypoint_errs);
        G_comb_t->SetTitle("All Sectors");
        G_comb_t->SetMarkerStyle(kFullCircle);
        G_comb_t->GetXaxis()->SetTitle("Proton Momentum (GeV)");
        G_comb_t->GetYaxis()->SetTitle("Transparency");
        G_comb_t->GetYaxis()->SetRangeUser(0,1.2);
	G_comb_t->SetMarkerColor(12);
        G_comb_t->Draw("AP");

        for(int s : sectors){

                G_t[s] = new TGraphErrors(4, G_mc_xpoints[s], G_mc_ypoints[s], mc_xpoint_errs[s], G_mc_ypoint_errs[s]);
                G_t[s]->SetTitle(TString::Format("Sector %i",s));
                G_t[s]->GetXaxis()->SetTitle("Proton Momentum (GeV)");
                G_t[s]->GetYaxis()->SetTitle("Transparency");
                G_t[s]->SetMarkerStyle(kFullCircle);
                G_t[s]->SetMarkerColor(color_options[s]);
                G_t[s]->Draw("P");
        }
        
        c_g->BuildLegend();

        TCanvas *c_comb;
        c_comb = new TCanvas(TString::Format("all transparency by sector"), TString::Format("all transparency by sector"), 800, 600);
        TGraphErrors *G18_trans = (TGraphErrors*)(G_comb_t->Clone());
        TGraphErrors *SuSA_trans = (TGraphErrors*)(susa_comb_t->Clone());
        TGraphErrors *Data_trans = (TGraphErrors*)(data_comb_t->Clone());
        G18_trans->SetTitle("G18");
        G18_trans->SetMarkerColor(2);
        SuSA_trans->SetTitle("SuSA v2");
        SuSA_trans->SetMarkerColor(4);
        Data_trans->SetTitle("CLAS Data");
        Data_trans->SetMarkerColor(6);
        G18_trans->Draw("AP");
        SuSA_trans->Draw("P");
        Data_trans->Draw("P");

        c_comb->BuildLegend();


       TFile *final = TFile::Open("T_He4_sectors.root", "RECREATE");
        Data_trans->Write("data_He4");
        G18_trans->Write("G_He4");
        SuSA_trans->Write("SuSA_He4");
        //c_susa->Write("SuSA");
        //c_
        final->Close();  
}

