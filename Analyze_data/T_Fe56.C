#include "myFunctions.cpp"
#include "noah_constants_Fe56.h"

double weighted_average(TH1D* h1) {
        double num_sum = 0.0;
        double den_sum = 0.0;
        for (int i = 0; i < h1->GetNbinsX(); i++) {
                if (h1->GetBinContent(i) == 0) continue;
                num_sum += h1->GetBinCenter(i)*h1->GetBinContent(i);
                den_sum += h1->GetBinContent(i);
        }

        return num_sum/den_sum;
}

void T_Fe56(bool make_plots = false) {
        gStyle->SetOptStat(0);

        data_2261[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/Fe56/Excl_Range1_Data__56Fe_2.261000.root";
        data_2261[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/Fe56/Incl_Range1_Data__56Fe_2.261000.root";
        data_2261[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/Fe56/Excl_Range2_Data__56Fe_2.261000.root";
        data_2261[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/Fe56/Incl_Range2_Data__56Fe_2.261000.root";
        data_2261[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/Fe56/Excl_Range3_Data__56Fe_2.261000.root";
        data_2261[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/Fe56/Incl_Range3_Data__56Fe_2.261000.root";
        data_4461[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/Fe56/Excl_Range1_Data__56Fe_4.461000.root";
        data_4461[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/Fe56/Incl_Range1_Data__56Fe_4.461000.root";

        susa_2261[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Excl_Range1_Genie_1_56Fe_2.261000.root";
        susa_2261[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Incl_Range1_Genie_1_56Fe_2.261000.root";
        susa_2261[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Excl_Range2_Genie_1_56Fe_2.261000.root";
        susa_2261[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Incl_Range2_Genie_1_56Fe_2.261000.root";
        susa_2261[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Excl_Range3_Genie_1_56Fe_2.261000.root";
        susa_2261[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Incl_Range3_Genie_1_56Fe_2.261000.root";
        susa_4461[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Excl_Range1_Genie_1_56Fe_4.461000.root";
        susa_4461[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Incl_Range1_Genie_1_56Fe_4.461000.root";

        g_2261[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Excl_Range1_Genie_2_56Fe_2.261000.root";
        g_2261[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Incl_Range1_Genie_2_56Fe_2.261000.root";
        g_2261[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Excl_Range2_Genie_2_56Fe_2.261000.root";
        g_2261[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Incl_Range2_Genie_2_56Fe_2.261000.root";
        g_2261[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Excl_Range3_Genie_2_56Fe_2.261000.root";
        g_2261[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Incl_Range3_Genie_2_56Fe_2.261000.root";
        g_4461[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Excl_Range1_Genie_2_56Fe_4.461000.root";
        g_4461[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Incl_Range1_Genie_2_56Fe_4.461000.root";

        susa_2261_truereco[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Excl_Range1_Genie_1_56Fe_2.261000.root";
        susa_2261_truereco[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Incl_Range1_Genie_1_56Fe_2.261000.root";
        susa_2261_truereco[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Excl_Range2_Genie_1_56Fe_2.261000.root";
        susa_2261_truereco[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Incl_Range2_Genie_1_56Fe_2.261000.root";
        susa_2261_truereco[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Excl_Range3_Genie_1_56Fe_2.261000.root";
        susa_2261_truereco[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Incl_Range3_Genie_1_56Fe_2.261000.root";
        susa_4461_truereco[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Excl_Range1_Genie_1_56Fe_4.461000.root";
        susa_4461_truereco[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Incl_Range1_Genie_1_56Fe_4.461000.root";

        susa_2261_true[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Excl_Range1_Genie_1_56Fe_2.261000.root";
        susa_2261_true[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Incl_Range1_Genie_1_56Fe_2.261000.root";
        susa_2261_true[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Excl_Range2_Genie_1_56Fe_2.261000.root";
        susa_2261_true[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Incl_Range2_Genie_1_56Fe_2.261000.root";
        susa_2261_true[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Excl_Range3_Genie_1_56Fe_2.261000.root";
        susa_2261_true[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Incl_Range3_Genie_1_56Fe_2.261000.root";
        susa_4461_true[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Excl_Range1_Genie_1_56Fe_4.461000.root";
        susa_4461_true[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Incl_Range1_Genie_1_56Fe_4.461000.root";

        g_2261_truereco[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Excl_Range1_Genie_2_56Fe_2.261000.root";
        g_2261_truereco[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Incl_Range1_Genie_2_56Fe_2.261000.root";
        g_2261_truereco[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Excl_Range2_Genie_2_56Fe_2.261000.root";
        g_2261_truereco[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Incl_Range2_Genie_2_56Fe_2.261000.root";
        g_2261_truereco[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Excl_Range3_Genie_2_56Fe_2.261000.root";
        g_2261_truereco[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Incl_Range3_Genie_2_56Fe_2.261000.root";
        g_4461_truereco[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Excl_Range1_Genie_2_56Fe_4.461000.root";
        g_4461_truereco[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Incl_Range1_Genie_2_56Fe_4.461000.root";

        g_2261_true[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Excl_Range1_Genie_2_56Fe_2.261000.root";
        g_2261_true[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Incl_Range1_Genie_2_56Fe_2.261000.root";
        g_2261_true[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Excl_Range2_Genie_2_56Fe_2.261000.root";
        g_2261_true[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Incl_Range2_Genie_2_56Fe_2.261000.root";
        g_2261_true[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Excl_Range3_Genie_2_56Fe_2.261000.root";
        g_2261_true[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Incl_Range3_Genie_2_56Fe_2.261000.root";
        g_4461_true[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Excl_Range1_Genie_2_56Fe_4.461000.root";
        g_4461_true[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Incl_Range1_Genie_2_56Fe_4.461000.root";

        susa_2261_truereco_rad[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Excl_Range1_Genie_3_56Fe_2.261000.root";
        susa_2261_truereco_rad[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Incl_Range1_Genie_3_56Fe_2.261000.root";
        susa_2261_truereco_rad[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Excl_Range2_Genie_3_56Fe_2.261000.root";
        susa_2261_truereco_rad[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Incl_Range2_Genie_3_56Fe_2.261000.root";
        susa_2261_truereco_rad[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Excl_Range3_Genie_3_56Fe_2.261000.root";
        susa_2261_truereco_rad[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Incl_Range3_Genie_3_56Fe_2.261000.root";
        susa_4461_truereco_rad[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Excl_Range1_Genie_3_56Fe_4.461000.root";
        susa_4461_truereco_rad[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Incl_Range1_Genie_3_56Fe_4.461000.root";

       std::string second_en[3][2] = {{"2.261 Excl Range 1", "2.261 Incl Range 1"},{"2.261 Excl Range 2", "2.261 Incl Range 2"},{ "2.261 Excl Range 3", "2.261 Incl Range 3"}};
        std::string third_en[1][2] = {{"4.461 Excl Range 1","4.461 Incl Range 1"}};  

// --------------------- Getting radiative correction histograms from MC ----------------
        TH1D* SuSA_2261_true_reco_rad[3][2];
        TH1D* SuSA_4461_true_reco_rad[1][2];


        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 3; r++) {
                        if(p==0) { // Exclusive
                                SuSA_2261_true_reco_rad[r][p] = (TH1D*)SumProtSectorsAndInts(susa_2261_truereco_rad[r][p], false);
                        }
                        if(p==1) { // Inclusive
                                SuSA_2261_true_reco_rad[r][p] = (TH1D*)SumElecSectorsAndInts(susa_2261_truereco_rad[r][p], false);
                        }
                        UniversalE4vFunction(SuSA_2261_true_reco_rad[r][p],  FSIModelsToLabels["SuSav2_RadCorr_LFGM_Truth_WithFidAcc_UpdatedSchwinger"], "56Fe", "2_261", TString::Format("susa_2261_mom_truereco_rad"));
                }
        }

        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 1; r++) {
                        if(p==0) { // Exclusive
                                SuSA_4461_true_reco_rad[r][p] = (TH1D*)SumProtSectorsAndInts(susa_4461_truereco_rad[r][p], false);
                        }
                        if(p==1) { // Inclusive
                                SuSA_4461_true_reco_rad[r][p] = (TH1D*)SumElecSectorsAndInts(susa_4461_truereco_rad[r][p], false);
                        }
                        UniversalE4vFunction(SuSA_4461_true_reco_rad[r][p],  FSIModelsToLabels["SuSav2_RadCorr_LFGM_Truth_WithFidAcc_UpdatedSchwinger"], "56Fe", "4_461", TString::Format("susa_4461_mom_truereco_rad"));
                }
        }

// --------------------- Getting acceptance correction histograms from MC ---------------

        //[NRanges][Exclusive = 0, Inclsuive = 1]     
     
        TH1D* SuSA_2261_true[3][2];
        TH1D* SuSA_2261_true_reco[3][2];
        TH1D* G_2261_true[3][2];
        TH1D* G_2261_true_reco[3][2];
        // 2.261 GeV
        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 3; r++) {
                        if(p==0) { // Exclusive
                                SuSA_2261_true[r][p] = (TH1D*)SumProtSectorsAndInts(susa_2261_true[r][p], false);
                                SuSA_2261_true_reco[r][p] = (TH1D*)SumProtSectorsAndInts(susa_2261_truereco[r][p], false);
                                G_2261_true[r][p] = (TH1D*)SumProtSectorsAndInts(g_2261_true[r][p], false);
                                G_2261_true_reco[r][p] = (TH1D*)SumProtSectorsAndInts(g_2261_truereco[r][p], false);
                        }
                        if(p==1) { // Inclusive
                                SuSA_2261_true[r][p] = (TH1D*)SumElecSectorsAndInts(susa_2261_true[r][p], false);
                                SuSA_2261_true_reco[r][p] = (TH1D*)SumElecSectorsAndInts(susa_2261_truereco[r][p], false);
                                G_2261_true[r][p] = (TH1D*)SumElecSectorsAndInts(g_2261_true[r][p], false);
                                G_2261_true_reco[r][p] = (TH1D*)SumElecSectorsAndInts(g_2261_truereco[r][p], false);
                        }
                        UniversalE4vFunction(SuSA_2261_true[r][p],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "56Fe","2_261", TString::Format("susa_2261_mom_%i%i",r,p));
                        UniversalE4vFunction(G_2261_true[r][p],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "56Fe","2_261", TString::Format("g_2261_mom_%i%i",r,p));
                        UniversalE4vFunction(SuSA_2261_true_reco[r][p],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "56Fe","2_261", TString::Format("susa_2261_mom_truereco_%i%i",r,p));
                        UniversalE4vFunction(G_2261_true_reco[r][p],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithFidAcc"], "56Fe","2_261", TString::Format("g_2261_mom_truereco_%i%i",r,p));
                }
        }     

        TH1D* SuSA_4461_true[1][2];
        TH1D* SuSA_4461_true_reco[1][2];
        TH1D* G_4461_true[1][2];
        TH1D* G_4461_true_reco[1][2];
        // 4.461 GeV
        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 1; r++) {
                        if(p==0) { // Exclusive
                                SuSA_4461_true[r][p] = (TH1D*)SumProtSectorsAndInts(susa_4461_true[r][p], false);
                                SuSA_4461_true_reco[r][p] = (TH1D*)SumProtSectorsAndInts(susa_4461_truereco[r][p], false);
                                G_4461_true[r][p] = (TH1D*)SumProtSectorsAndInts(g_4461_true[r][p], false);
                                G_4461_true_reco[r][p] = (TH1D*)SumProtSectorsAndInts(g_4461_truereco[r][p], false);
                        }
                        if(p==1) { // Inclusive
                                SuSA_4461_true[r][p] = (TH1D*)SumElecSectorsAndInts(susa_4461_true[r][p], false);
                                SuSA_4461_true_reco[r][p] = (TH1D*)SumElecSectorsAndInts(susa_4461_truereco[r][p], false);
                                G_4461_true[r][p] = (TH1D*)SumElecSectorsAndInts(g_4461_true[r][p], false);
                                G_4461_true_reco[r][p] = (TH1D*)SumElecSectorsAndInts(g_4461_truereco[r][p], false);
                        }
                        UniversalE4vFunction(SuSA_4461_true[r][p],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "56Fe","4_461", TString::Format("susa_4461_mom_%i%i",r,p));
                        UniversalE4vFunction(G_4461_true[r][p],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "56Fe","4_461", TString::Format("g_4461_mom_%i%i",r,p));
                        UniversalE4vFunction(SuSA_4461_true_reco[r][p],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "56Fe","4_461", TString::Format("susa_4461_mom_truereco_%i%i",r,p));
                        UniversalE4vFunction(G_4461_true_reco[r][p],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithFidAcc"], "56Fe","4_461", TString::Format("g_4461_mom_truereco_%i%i",r,p));
                }
        }


// --------------------- Getting MC exclusive and inclusive measurements and mec/neutron corrections ----------------
        
        //[NRanges][Exclusive = 0, Inclsuive = 1]     
        TH1D* SuSA_2261[3][2];
        double mec_corr_2261[3][2];
        double neutron_corr_2261_G18[3][2];
        double neutron_corr_2261_susa[3][2];
        // 2.261 GeV
        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 3; r++) {
                        if(p==0) { // Exclusive
                                SuSA_2261[r][p] = (TH1D*)SumProtSectorsAndInts(susa_2261[r][p], false);
                                mec_corr_2261[r][p] = get_MEC_corr(susa_2261[r][p], false);
                                neutron_corr_2261_susa[r][p] = get_Neutron_corr(susa_2261[r][p], false);
                                neutron_corr_2261_G18[r][p] = get_Neutron_corr(g_2261[r][p], false);
                        }
                        if(p==1) { // Inclusive
                                SuSA_2261[r][p] = (TH1D*)SumElecSectorsAndInts(susa_2261[r][p], false);
                                mec_corr_2261[r][p] = get_MEC_corr(susa_2261[r][p], true);
                                neutron_corr_2261_susa[r][p]=get_Neutron_corr(susa_2261[r][p], true);
                                neutron_corr_2261_G18[r][p] = get_Neutron_corr(g_2261[r][p], true); 
                        }
                        UniversalE4vFunction(SuSA_2261[r][p], FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "56Fe","2_261", TString::Format("susa_2261_mom_reco_%i%i",r,p));
                }
        }

        std::cout << "MEC and neutron correction for 2.261 GeV" << "\n";
        for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 2; j++) {
                        std::cout << second_en[i][j] << "\n"; 
                        std::cout << "MEC:  " << mec_corr_2261[i][j] << "\n";
                        std::cout << "G18 N: " << neutron_corr_2261_G18[i][j] << "\n";
                        std::cout << "SuSA N: " << neutron_corr_2261_susa[i][j] << "\n";
                        std::cout << "\n"; 
               }
        }

        TH1D* SuSA_4461[1][2];
        double mec_corr_4461[1][2];
        double neutron_corr_4461_G18[1][2];
        double neutron_corr_4461_susa[1][2];
        // 4.461 GeV
        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 1; r++) {
                        if(p==0) { // Exclusive
                                SuSA_4461[r][p] = (TH1D*)SumProtSectorsAndInts(susa_4461[r][p], false);
                                mec_corr_4461[r][p] = get_MEC_corr(susa_4461[r][p], false);
                                neutron_corr_4461_susa[r][p] = get_Neutron_corr(susa_4461[r][p], false);
                                neutron_corr_4461_G18[r][p] = get_Neutron_corr(g_4461[r][p], false);
                        }
                        if(p==1) { // Inclusive
                                SuSA_4461[r][p] = (TH1D*)SumElecSectorsAndInts(susa_4461[r][p], false);
                                mec_corr_4461[r][p] = get_MEC_corr(susa_4461[r][p], true);
                                neutron_corr_4461_susa[r][p]=get_Neutron_corr(susa_4461[r][p], true);
                                neutron_corr_4461_G18[r][p] = get_Neutron_corr(g_4461[r][p], true); 
                        }
                        UniversalE4vFunction(SuSA_4461[r][p], FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "56Fe","4_461", TString::Format("susa_4461_mom_reco_%i%i",r,p));
                }
        }

        std::cout << "MEC and neutron correction for 4.461 GeV" << "\n";
        for(int i = 0; i < 1; i++) {
                for(int j = 0; j < 2; j++) {
                        std::cout << third_en[i][j] << "\n";
                        std::cout << "MEC: " << mec_corr_4461[i][j] << "\n";
                        std::cout << "G18 N: " << neutron_corr_4461_G18[i][j] << "\n";
                        std::cout << "SuSA N: " << neutron_corr_4461_susa[i][j] << "\n";
                        std::cout << "\n"; 
               }
        }


// --------------------- Getting Data exclusive and inclusive measurements ----------------

        // Here we will also scale the data
        TH1D* Data_2261[3][2];
        TH1D* Data_4461[1][2];

        for(int p = 0; p < 2; p++) {
                if(p == 0) { // Exclusive
                        Data_2261[0][p] = (TH1D*)SumProtSectorsAndInts(data_2261[0][p], true);
                        Data_2261[1][p] = (TH1D*)SumProtSectorsAndInts(data_2261[1][p], true);
                        Data_2261[2][p] = (TH1D*)SumProtSectorsAndInts(data_2261[2][p], true);
                        Data_4461[0][p] = (TH1D*)SumProtSectorsAndInts(data_4461[0][p], true);
                }
                if(p == 1) { // Inclusive
                        Data_2261[0][p] = (TH1D*)SumElecSectorsAndInts(data_2261[0][p], true);
                        Data_2261[1][p] = (TH1D*)SumElecSectorsAndInts(data_2261[1][p], true);
                        Data_2261[2][p] = (TH1D*)SumElecSectorsAndInts(data_2261[2][p], true);
                        Data_4461[0][p] = (TH1D*)SumElecSectorsAndInts(data_4461[0][p], true);
                }
                UniversalE4vFunction(Data_2261[0][p], "Pinned Data", "56Fe", "2_261", TString::Format("data_2261_mom_0%i",p));
                UniversalE4vFunction(Data_2261[1][p], "Pinned Data", "56Fe", "2_261", TString::Format("data_2261_mom_1%i",p));
                UniversalE4vFunction(Data_2261[2][p], "Pinned Data", "56Fe", "2_261", TString::Format("data_2261_mom_2%i",p));
                UniversalE4vFunction(Data_4461[0][p], "Pinned Data", "56Fe", "4_461", TString::Format("data_4461_mom_0%i",p));
        }


// ---------------- Acceptance correct all histograms ---------------------
        TCanvas *ca = new TCanvas("","",800,800);
        if(make_plots) {  
                ca->SaveAs("Fe56_true_vs_truereco.pdf(");
                ca->SaveAs("Fe56_truerecorad_vs_truereco.pdf(");
                ca->SaveAs("Fe56_Acceptance_Ratios.pdf(");
                ca->SaveAs("Fe56_Rad_Ratios.pdf(");
        }

        //2261
        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 3; r++) {
                        SuSA_2261[r][p]->SetTitle(TString::Format("SuSA2261_%s",second_en[r][p].c_str()));
                        Data_2261[r][p] = (TH1D*)AcceptanceCorrect(Data_2261[r][p], SuSA_2261_true[r][p], SuSA_2261_true_reco[r][p], G_2261_true[r][p], G_2261_true_reco[r][p], SuSA_2261_true_reco_rad[r][p], false);
                        SuSA_2261[r][p] = (TH1D*)AcceptanceCorrect(SuSA_2261[r][p], SuSA_2261_true[r][p], SuSA_2261_true_reco[r][p], G_2261_true[r][p], G_2261_true_reco[r][p], SuSA_2261_true_reco_rad[r][p], make_plots, false);
                }
        }

        //4461
        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 1; r++) {
                        SuSA_4461[r][p]->SetTitle(TString::Format("SuSA4461_%s",third_en[r][p].c_str()));
                        Data_4461[r][p] = (TH1D*)AcceptanceCorrect(Data_4461[r][p], SuSA_4461_true[r][p], SuSA_4461_true_reco[r][p], G_4461_true[r][p], G_4461_true_reco[r][p], SuSA_4461_true_reco_rad[r][p], false);
                        SuSA_4461[r][p] = (TH1D*)AcceptanceCorrect(SuSA_4461[r][p], SuSA_4461_true[r][p], SuSA_4461_true_reco[r][p], G_4461_true[r][p], G_4461_true_reco[r][p], SuSA_4461_true_reco_rad[r][p], make_plots, false);
                }
        }
        
        if(make_plots) {
                ca->SaveAs("Fe56_true_vs_truereco.pdf)");
                ca->SaveAs("Fe56_truerecorad_vs_truereco.pdf)");
                ca->SaveAs("Fe56_Acceptance_Ratios.pdf)");
                ca->SaveAs("Fe56_Rad_Ratios.pdf)");
        }

// ---------------- Get average proton momentum for data and MC ------------------------
        
        double data_avg_prot_mom_2261[3];
        double data_avg_prot_mom_4461[1];

        double SuSA_avg_prot_mom_2261[3];
        double SuSA_avg_prot_mom_4461[1];

        data_avg_prot_mom_2261[0] = weighted_average(Data_2261[0][0]); 
        data_avg_prot_mom_2261[1] = weighted_average(Data_2261[1][0]); 
        data_avg_prot_mom_2261[2] = weighted_average(Data_2261[2][0]);
        data_avg_prot_mom_4461[0] = weighted_average(Data_4461[0][0]); 

        SuSA_avg_prot_mom_2261[0] = weighted_average(SuSA_2261[0][0]); 
        SuSA_avg_prot_mom_2261[1] = weighted_average(SuSA_2261[1][0]); 
        SuSA_avg_prot_mom_2261[2] = weighted_average(SuSA_2261[2][0]);
        SuSA_avg_prot_mom_4461[0] = weighted_average(SuSA_4461[0][0]); 

// -------------- Add systematic uncertainties ---------------------------

        //2261
        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 3; r++) {
                        ApplySystUnc(Data_2261[r][p],"2_261"); 
                        ApplySystUnc(SuSA_2261[r][p],"2_261");
                }
        }

        //4461
        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 1; r++) {
                        ApplySystUnc(Data_4461[r][p],"4_461"); 
                        ApplySystUnc(SuSA_4461[r][p],"4_461");
                }
        }

// -------------- Correct for MEC and neutron contamination --------------
        //Correct Data by (1-(MECfrac))*(G18_prot/(G18_prot + G18_neut))
        //Correct MC by (1-(MECfrac))*(SuSA_prot/(SuSA_prot + SuSA_neut))

        //2261
        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 3; r++) {
                        Data_2261[r][p]->Scale((1. - mec_corr_2261[r][p]));
                        SuSA_2261[r][p]->Scale((1. - mec_corr_2261[r][p]));
                        if(p == 1) {    
                                SuSA_2261[r][p]->Scale(neutron_corr_2261_susa[r][p]);
                                Data_2261[r][p]->Scale(neutron_corr_2261_G18[r][p]);
                        }
                }
        }

        //4461
        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 1; r++) {
                        Data_4461[r][p]->Scale((1. - mec_corr_4461[r][p]));
                        SuSA_4461[r][p]->Scale((1. - mec_corr_4461[r][p]));
                        if(p == 1) {    
                                SuSA_4461[r][p]->Scale(neutron_corr_4461_susa[r][p]);
                                Data_4461[r][p]->Scale(neutron_corr_4461_G18[r][p]);
                        }
                }
        }

// ---------------- Make plots of reconstructed momentum distributions for acc corrected data/MC ------------
        if(make_plots) {
                TCanvas* reco_dist_canvas = new TCanvas("","",1000,800);
                reco_dist_canvas->SaveAs("Fe56_reco_dist.pdf(");

                for(int p = 0; p < 2; p++) {
                        for(int r = 0; r< 3; r++ ) {
                                SuSA_2261[r][p]->Draw("e hist");
                                Data_2261[r][p]->Draw("e same");
                                SuSA_2261[r][p]->SetTitle("SuSA_v2 Fe56");
                                Data_2261[r][p]->SetTitle("Data Fe56");
                                Data_2261[r][p]->SetMarkerColor(kBlack);
                                Data_2261[r][p]->SetMarkerStyle(20);
                                SuSA_2261[r][p]->GetYaxis()->SetTitle("Absolute Number of Events ");
                                SuSA_2261[r][p]->GetXaxis()->SetTitle("Momentum (GeV)");
                                reco_dist_canvas->BuildLegend();
                                SuSA_2261[r][p]->SetTitle(TString::Format("SuSA_v2 Fe56 %s", second_en[r][p].c_str()));
                                reco_dist_canvas->SaveAs("Fe56_reco_dist.pdf");
                        }
                }


                for(int p = 0; p < 2; p++) {
                        for(int r = 0; r< 1; r++ ) {
                                SuSA_4461[r][p]->Draw("e hist");
                                Data_4461[r][p]->Draw("e same");
                                SuSA_4461[r][p]->SetTitle("SuSA_v2 Fe56");
                                Data_4461[r][p]->SetTitle("Data Fe56");
                                Data_4461[r][p]->SetMarkerColor(kBlack);
                                Data_4461[r][p]->SetMarkerStyle(20);
                                SuSA_4461[r][p]->GetYaxis()->SetTitle("Absolute Number of Events");
                                SuSA_4461[r][p]->GetXaxis()->SetTitle("Momentum (GeV)");
                                reco_dist_canvas->BuildLegend();
                                SuSA_4461[r][p]->SetTitle(TString::Format("SuSA_v2 Fe56 %s", third_en[r][p].c_str()));
                                reco_dist_canvas->SaveAs("Fe56_reco_dist.pdf");
                        }
                }
                reco_dist_canvas->SaveAs("Fe56_reco_dist.pdf)");

        }        
// -------------- Integrate histograms -----------------

        double data_int_2261[3][2];
        double data_int_4461[1][2];
        double data_int_2261_err[3][2];
        double data_int_4461_err[1][2];

        double SuSA_int_2261[3][2];
        double SuSA_int_4461[1][2];
        double SuSA_int_2261_err[3][2];
        double SuSA_int_4461_err[1][2];

        //2261
        for(int r = 0; r < 3; r++) {
                for(int p = 0; p < 2; p++) {
                        data_int_2261[r][p] = Data_2261[r][p]->IntegralAndError(1, Data_2261[r][p]->GetNbinsX(), data_int_2261_err[r][p],"width");
                        SuSA_int_2261[r][p] = SuSA_2261[r][p]->IntegralAndError(1, SuSA_2261[r][p]->GetNbinsX(), SuSA_int_2261_err[r][p],"width");
                        std::cout << "Data " << second_en[r][p] << " = " << data_int_2261[r][p] << "\n";
                        std::cout << "SuSA " << second_en[r][p] << " = " << SuSA_int_2261[r][p] << "\n";
                        std::cout << "\n";
                }
        }

        //4461
        for(int r = 0; r < 1; r++) {
                for(int p = 0; p < 2; p++) {
                        data_int_4461[r][p] = Data_4461[r][p]->IntegralAndError(1, Data_4461[r][p]->GetNbinsX(), data_int_4461_err[r][p],"width");
                        SuSA_int_4461[r][p] = SuSA_4461[r][p]->IntegralAndError(1, SuSA_4461[r][p]->GetNbinsX(), SuSA_int_4461_err[r][p],"width");
                        std::cout << "Data " << third_en[r][p] << " = " << data_int_4461[r][p] << "\n";
                        std::cout << "SuSA " << third_en[r][p] << " = " << SuSA_int_4461[r][p] << "\n";
                        std::cout << "\n";
                }
        }

// ----------- Take Ratios to obtain transparencies and errors --------------
        double data_T_2261[3];
        double data_T_4461[1];
        double data_T_2261_err[3];
        double data_T_4461_err[1];

        data_T_2261[0] = data_int_2261[0][0]/data_int_2261[0][1];
        data_T_2261[1] = data_int_2261[1][0]/data_int_2261[1][1];
        data_T_2261[2] = data_int_2261[2][0]/data_int_2261[2][1];
        data_T_4461[0] = data_int_4461[0][0]/data_int_4461[0][1];

        data_T_2261_err[0] = get_ratio_error(data_int_2261[0][0],data_int_2261[0][1],data_int_2261_err[0][0],data_int_2261_err[0][1]);
        data_T_2261_err[1] = get_ratio_error(data_int_2261[1][0],data_int_2261[1][1],data_int_2261_err[1][0],data_int_2261_err[1][1]);
        data_T_2261_err[2] = get_ratio_error(data_int_2261[2][0],data_int_2261[2][1],data_int_2261_err[2][0],data_int_2261_err[2][1]);
        data_T_4461_err[0] = get_ratio_error(data_int_4461[0][0],data_int_4461[0][1],data_int_4461_err[0][0],data_int_4461_err[0][1]);


        double SuSA_T_2261[3];
        double SuSA_T_4461[1];
        double SuSA_T_2261_err[3];
        double SuSA_T_4461_err[1];

        SuSA_T_2261[0] = SuSA_int_2261[0][0]/SuSA_int_2261[0][1];
        SuSA_T_2261[1] = SuSA_int_2261[1][0]/SuSA_int_2261[1][1];
        SuSA_T_2261[2] = SuSA_int_2261[2][0]/SuSA_int_2261[2][1];
        SuSA_T_4461[0] = SuSA_int_4461[0][0]/SuSA_int_4461[0][1];

        SuSA_T_2261_err[0] = get_ratio_error(SuSA_int_2261[0][0],SuSA_int_2261[0][1],SuSA_int_2261_err[0][0],SuSA_int_2261_err[0][1]);
        SuSA_T_2261_err[1] = get_ratio_error(SuSA_int_2261[1][0],SuSA_int_2261[1][1],SuSA_int_2261_err[1][0],SuSA_int_2261_err[1][1]);
        SuSA_T_2261_err[2] = get_ratio_error(SuSA_int_2261[2][0],SuSA_int_2261[2][1],SuSA_int_2261_err[2][0],SuSA_int_2261_err[2][1]);
        SuSA_T_4461_err[0] = get_ratio_error(SuSA_int_4461[0][0],SuSA_int_4461[0][1],SuSA_int_4461_err[0][0],SuSA_int_4461_err[0][1]);

// ---------------------------------------------------------------------


        TCanvas* c;
        c = new TCanvas(TString::Format("c"), TString::Format("c"), 800, 600);

        double ypoints[4] = {data_T_2261[0], data_T_2261[1], data_T_2261[2], data_T_4461[0]};
        double ypoint_errs[4] = {data_T_2261_err[0], data_T_2261_err[1], data_T_2261_err[2], data_T_4461_err[0]};
        double xpoints[4] = {data_avg_prot_mom_2261[0],data_avg_prot_mom_2261[1],data_avg_prot_mom_2261[2],data_avg_prot_mom_4461[0]};
        double xpoint_errs[4] = {0.,0.,0.,0.};

        TGraphErrors *data_t = new TGraphErrors(4, xpoints, ypoints, xpoint_errs, ypoint_errs);
        data_t->SetTitle("Data Fe56");
        data_t->GetXaxis()->SetTitle("Proton Momentum (GeV)");
        data_t->GetYaxis()->SetTitle("Transparency");
        data_t->SetMarkerStyle(kFullCircle);
        data_t->SetMarkerColor(3);
        data_t->GetYaxis()->SetRangeUser(0.1,1.0);
        data_t->Draw("AP");

        
        double mc_ypoints[4] = { SuSA_T_2261[0], SuSA_T_2261[1], SuSA_T_2261[2], SuSA_T_4461[0]};
        double mc_ypoint_errs[4] = { SuSA_T_2261_err[0], SuSA_T_2261_err[1], SuSA_T_2261_err[2], SuSA_T_4461_err[0]};
        double mc_xpoints[4] = {SuSA_avg_prot_mom_2261[0],SuSA_avg_prot_mom_2261[1],SuSA_avg_prot_mom_2261[2],SuSA_avg_prot_mom_4461[0]};
        double mc_xpoint_errs[4] = {0.,0.,0.,0.};

        TGraphErrors *SuSA_t = new TGraphErrors(4, mc_xpoints, mc_ypoints, mc_xpoint_errs, mc_ypoint_errs);
        SuSA_t->SetMarkerStyle(kFullCircle);
        SuSA_t->SetMarkerColor(4);
        SuSA_t->GetYaxis()->SetRangeUser(0.1,1.0);
        SuSA_t->SetTitle("SuSA_v2 Fe56");
        SuSA_t->Draw("P");
        
        c->BuildLegend();
        c->SaveAs("T_Fe56.pdf");

        TFile *final = TFile::Open("T_Fe56.root", "RECREATE");
        data_t->Write("data");
        SuSA_t->Write("SuSA");
        final->Close();
}

double get_Neutron_corr(TString file, bool incl) {

        TFile *F = TFile::Open( TString( file ) );
        TH1D* hit_nuc;
        
        if (incl == true) {
                hit_nuc = (TH1D*)F->Get("h1_hit_nuc");
        }

        if (incl == false) {
                hit_nuc = (TH1D*)F->Get("h1_hit_nuc_pass");
        }

        double protons = hit_nuc->GetBinContent(1);
        double neutrons = hit_nuc->GetBinContent(2);

        return protons/(neutrons + protons);

}

double get_MEC_corr(TString file, bool incl) {   
        TFile *input = TFile::Open( TString( file ) );

        TH1D* mom_int[4];
        TH1D* mom_Int_Sec[6][4];
        TH1D* total;

        if(incl == true) {
                for(int j = 0; j < 4; j++) {
                        for(int i = 0; i < 6; i++) {
                                mom_Int_Sec[i][j] = (TH1D*)input->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", j+1, i));
                                if(i == 0) mom_int[j] = (TH1D*)(mom_Int_Sec[i][j]->Clone());
                                else mom_int[j]->Add(mom_Int_Sec[i][j]);
                        }
                }
        }

        if(incl == false) {
                for(int j = 0; j < 4; j++) {
                        for(int i = 0; i < 6; i++) {
                                mom_Int_Sec[i][j] = (TH1D*)input->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", j+1, i));
                                if(i == 0) mom_int[j] = (TH1D*)(mom_Int_Sec[i][j]->Clone());
                                else mom_int[j]->Add(mom_Int_Sec[i][j]);
                        }
                }
        }

        total = (TH1D*) mom_int[0]->Clone();
        total->Add(mom_int[1]); total->Add(mom_int[2]); total->Add(mom_int[3]); 

        double mec_int = mom_int[1]->Integral();
        double total_int = total->Integral();
        return mec_int/total_int;
}

TH1D* SumElecSectorsAndInts(TString file, bool isData) {
        TFile *input = TFile::Open( TString( file ) );

        TH1D* el_mom;
        TH1D* el_mom_d[6];
        TH1D* el_mom_Int_Sec[6][4];

        if (isData == false) {
                for (int i = 0; i < 6; i++) { // for all the sectors
                        for (int j = 0; j < 4; j++) { // for all the interactions

                                // extract the histrograms
                                el_mom_Int_Sec[i][j] = (TH1D*)input->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", j+1, i));
                                if(i == 0 && j == 0) el_mom = (TH1D*)(el_mom_Int_Sec[i][j]->Clone());
                                else el_mom->Add(el_mom_Int_Sec[i][j]);
                        }
                }
        }

        if (isData == true) {
                for (int i = 0; i < 6; i++) { // for all the sectors
                         el_mom_d[i] = (TH1D*)input->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", i));
                        if(i == 0) el_mom = (TH1D*)(el_mom_d[i]->Clone());
                        else el_mom->Add(el_mom_d[i]);
            }
        }

        el_mom->Rebin( 60 );
        return el_mom;
}

TH1D* SumProtSectorsAndInts(TString file, bool isData) {
        TFile *input = TFile::Open( TString( file ) );

        TH1D* h1_prot_momentum;
        TH1D* h1_prot_momentum_d[6];
        TH1D* h1_prot_mom_InteractionBreakDown_inSector[6][4];

        if (isData == false) {
                for (int i = 0; i < 6; i++) { // for all the sectors
                        for (int j = 0; j < 4; j++) { // for all the interactions

                                // extract the histrograms
                                h1_prot_mom_InteractionBreakDown_inSector[i][j] = (TH1D*)input->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", j+1, i));
                                if(i == 0 && j == 0) h1_prot_momentum = (TH1D*)(h1_prot_mom_InteractionBreakDown_inSector[i][j]->Clone());
                                else h1_prot_momentum->Add(h1_prot_mom_InteractionBreakDown_inSector[i][j]);
                        }
                }
        }

        if (isData == true) {
                for (int i = 0; i < 6; i++) { // for all the sectors
                         h1_prot_momentum_d[i] = (TH1D*)input->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", i));
                        if(i == 0) h1_prot_momentum = (TH1D*)(h1_prot_momentum_d[i]->Clone());
                        else h1_prot_momentum->Add(h1_prot_momentum_d[i]);
                }
        }

        h1_prot_momentum->Rebin( 60 );
        return h1_prot_momentum;
}

TH1D* AcceptanceCorrect(TH1D* hist, TH1D* susa_true, TH1D* susa_truereco, TH1D* G_true, TH1D* G_truereco, TH1D* susa_truereco_rad, bool make_plots, bool data) {
        
        TH1D::SetDefaultSumw2();

        TH1D* OverallClone = (TH1D*)hist->Clone();

        TH1D* susa_correction = (TH1D*)susa_true->Clone();
        TH1D* G_correction = (TH1D*)G_true->Clone();

        susa_correction->Divide(susa_truereco);
        G_correction->Divide(G_truereco);

        TH1D* Average = (TH1D*)(susa_correction->Clone());
        Average->Add(G_correction);
        Average->Scale(0.5);

        TH1D* RadCorrection = (TH1D*)susa_truereco->Clone();
        RadCorrection->Divide(susa_truereco_rad);

        if(make_plots) {
                TString tCanvasName = TString::Format("true_vs_reco_%s",hist->GetTitle());
                TCanvas* tPlotCanvas = new TCanvas(tCanvasName,tCanvasName,205,34,1024,768);
                susa_true->GetYaxis()->SetTitle("Scaled number of events");
                susa_true->GetXaxis()->SetTitle("Momentum (GeV)");
                susa_true->SetTitle(TString::Format("True %s",hist->GetTitle()));
                susa_truereco->SetTitle(TString::Format("Reco %s",hist->GetTitle()));
                susa_true->SetLineColor(kRed);
                susa_true->Draw("e hist");
                susa_truereco->Draw("e hist same");
                tPlotCanvas->SetLogy();
                tPlotCanvas->BuildLegend();
                tPlotCanvas->SaveAs("Fe56_true_vs_truereco.pdf");


                TString trCanvasName = TString::Format("radrec_vs_noradreco_%s",hist->GetTitle());
                TCanvas* trPlotCanvas = new TCanvas(trCanvasName,trCanvasName,205,34,1024,768);
                susa_truereco->GetYaxis()->SetTitle("Scaled number of events");
                susa_truereco->GetXaxis()->SetTitle("Momentum (GeV)");
                susa_truereco->Draw("e hist");
                susa_truereco->SetLineColor(kBlack);
                susa_truereco_rad->SetLineColor(kGreen);
                susa_truereco_rad->SetTitle(TString::Format("Reco Rad %s",hist->GetTitle()));
                susa_truereco_rad->Draw("e hist same");
                trPlotCanvas->SetLogy();
                trPlotCanvas->BuildLegend();
                trPlotCanvas->SaveAs("Fe56_truerecorad_vs_truereco.pdf");
        }
        
        int NBins = OverallClone->GetXaxis()->GetNbins();
        double AccCorrTolerance = 5;

        for (int WhichBin = 0; WhichBin < NBins; WhichBin++) {
                double AccCorr = 0.;
                double RadCorr = 0.;

                double NewBinContent = 0.;
                double NewBinError = 0.;

                AccCorr = Average->GetBinContent(WhichBin + 1);
                if (AccCorr < 0 || AccCorr > AccCorrTolerance) {
                        double CorrectionSuSav2Bin = susa_correction->GetBinContent(WhichBin + 1);
                        double CorrectionG2018Bin = G_correction->GetBinContent(WhichBin + 1);

                        if (CorrectionSuSav2Bin > 0 && CorrectionSuSav2Bin < AccCorrTolerance) { AccCorr = CorrectionSuSav2Bin; }
                        else if (CorrectionG2018Bin > 0 && CorrectionG2018Bin < AccCorrTolerance) { AccCorr = CorrectionG2018Bin; }
                        else { AccCorr = 0.; }

                }
                
                
                RadCorr = RadCorrection->GetBinContent(WhichBin + 1);
                if(RadCorr <= 0.) RadCorr = 1.;
                if(AccCorr <= 0.) AccCorr = 1.;
                if(!data) RadCorr = 1.;
                NewBinContent = hist->GetBinContent(WhichBin + 1) * AccCorr * RadCorr;
                NewBinError = hist->GetBinError(WhichBin + 1) * AccCorr * RadCorr;

                OverallClone->SetBinContent(WhichBin + 1, NewBinContent);
                OverallClone->SetBinError(WhichBin + 1, NewBinError);
        }

        if(make_plots) {
          TString CanvasName = TString::Format("AccCorrCanvas_%s",hist->GetTitle());
          TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
          Average->GetYaxis()->SetTitle("Detector Acceptance Correction");
          Average->GetXaxis()->SetTitle("Momentum (GeV)");
          Average->Draw("e hist");
          Average->SetTitle(TString::Format("%s",hist->GetTitle()));
          PlotCanvas->SaveAs("Fe56_Acceptance_Ratios.pdf");

          TString RadCanvasName = TString::Format("RadCorrCanvas_%s",hist->GetTitle());
          TCanvas* RadPlotCanvas = new TCanvas(RadCanvasName,RadCanvasName,205,34,1024,768);
          RadCorrection->GetYaxis()->SetTitle("Radiative Correction");
          RadCorrection->GetXaxis()->SetTitle("Momentum (GeV)");
          RadCorrection->SetTitle(TString::Format("%s", hist->GetTitle()));
          RadCorrection->Draw("e hist");
          RadPlotCanvas->SaveAs("Fe56_Rad_Ratios.pdf");
        }

        TH1D* Spread = (TH1D*)susa_correction->Clone();
        Spread->Add(G_correction, -1);
        Spread->Divide(Average);
        Spread->Scale(1./TMath::Sqrt(12.));

        int NBinsSpread = Spread->GetXaxis()->GetNbins();

        for (int WhichBin = 0; WhichBin < NBinsSpread; WhichBin++) {

                double BinContent = Spread->GetBinContent(WhichBin+1);
                if (BinContent < 0) { Spread->SetBinContent(WhichBin+1,-BinContent); }

        }

        for (int WhichBin = 0; WhichBin < NBinsSpread; WhichBin++) {

                double SpreadBinContent = Spread->GetBinContent(WhichBin+1);
                double XSecBinError = OverallClone->GetBinError(WhichBin+1);
                double XSecBinEntry = OverallClone->GetBinContent(WhichBin+1);
                double AccCorrError = SpreadBinContent * XSecBinEntry;
                double NewXSecBinError = TMath::Sqrt( TMath::Power(XSecBinError,2.) + TMath::Power(AccCorrError,2.) );
                OverallClone->SetBinError(WhichBin+1,NewXSecBinError);

        }

        return OverallClone;
}

double get_ratio_error(double num, double denom, double num_err, double denom_err) {
        return (1./denom)*TMath::Power(TMath::Power(num_err,2.) - TMath::Power(num*denom_err/denom,2.), 0.5);
}






