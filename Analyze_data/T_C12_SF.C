#include "myFunctions.cpp"
#include "noah_constants_C12_SF.h"

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

void T_C12_SF(bool make_plots = false) {
        gStyle->SetOptStat(0);

        data_1161[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/C12/Excl_Range2_Data__C12_1.161000.root";
        data_1161[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/C12/Excl_Range3_Data__C12_1.161000.root";
        data_2261[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/C12/Excl_Range1_Data__C12_2.261000.root";
        data_2261[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/C12/Excl_Range2_Data__C12_2.261000.root";
        data_2261[2] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/C12/Excl_Range3_Data__C12_2.261000.root";
        data_4461[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/C12/Excl_Range1_Data__C12_4.461000.root";

        susa_1161[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Excl_Range2_Genie_1_C12_1.161000.root";
        susa_1161[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Excl_Range3_Genie_1_C12_1.161000.root";
        susa_2261[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Excl_Range1_Genie_1_C12_2.261000.root";
        susa_2261[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Excl_Range2_Genie_1_C12_2.261000.root";
        susa_2261[2] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Excl_Range3_Genie_1_C12_2.261000.root";
        susa_4461[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Excl_Range1_Genie_1_C12_4.461000.root";

        g_1161[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Excl_Range2_Genie_2_C12_1.161000.root";
        g_1161[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Excl_Range3_Genie_2_C12_1.161000.root";
        g_2261[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Excl_Range1_Genie_2_C12_2.261000.root";
        g_2261[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Excl_Range2_Genie_2_C12_2.261000.root";
        g_2261[2] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Excl_Range3_Genie_2_C12_2.261000.root";
        g_4461[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Excl_Range1_Genie_2_C12_4.461000.root";

        susa_1161_truereco[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Excl_Range2_Genie_1_C12_1.161000.root";
        susa_1161_truereco[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Excl_Range3_Genie_1_C12_1.161000.root";
        susa_2261_truereco[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Excl_Range1_Genie_1_C12_2.261000.root";
        susa_2261_truereco[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Excl_Range2_Genie_1_C12_2.261000.root";
        susa_2261_truereco[2] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Excl_Range3_Genie_1_C12_2.261000.root";
        susa_4461_truereco[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Excl_Range1_Genie_1_C12_4.461000.root";

        susa_1161_true[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Excl_Range2_Genie_1_C12_1.161000.root";
        susa_1161_true[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Excl_Range3_Genie_1_C12_1.161000.root";
        susa_2261_true[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Excl_Range1_Genie_1_C12_2.261000.root";
        susa_2261_true[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Excl_Range2_Genie_1_C12_2.261000.root";
        susa_2261_true[2] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Excl_Range3_Genie_1_C12_2.261000.root";
        susa_4461_true[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Excl_Range1_Genie_1_C12_4.461000.root";

        g_1161_truereco[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Excl_Range2_Genie_2_C12_1.161000.root";
        g_1161_truereco[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Excl_Range3_Genie_2_C12_1.161000.root";
        g_2261_truereco[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Excl_Range1_Genie_2_C12_2.261000.root";
        g_2261_truereco[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Excl_Range2_Genie_2_C12_2.261000.root";
        g_2261_truereco[2] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Excl_Range3_Genie_2_C12_2.261000.root";
        g_4461_truereco[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Excl_Range1_Genie_2_C12_4.461000.root";

        g_1161_true[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Excl_Range2_Genie_2_C12_1.161000.root";
        g_1161_true[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Excl_Range3_Genie_2_C12_1.161000.root";
        g_2261_true[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Excl_Range1_Genie_2_C12_2.261000.root";
        g_2261_true[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Excl_Range2_Genie_2_C12_2.261000.root";
        g_2261_true[2] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Excl_Range3_Genie_2_C12_2.261000.root";
        g_4461_true[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Excl_Range1_Genie_2_C12_4.461000.root";

        susa_1161_truereco_rad[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Excl_Range2_Genie_3_C12_1.161000.root";
        susa_1161_truereco_rad[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Excl_Range3_Genie_3_C12_1.161000.root";
        susa_2261_truereco_rad[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Excl_Range1_Genie_3_C12_2.261000.root";
        susa_2261_truereco_rad[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Excl_Range2_Genie_3_C12_2.261000.root";
        susa_2261_truereco_rad[2] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Excl_Range3_Genie_3_C12_2.261000.root";
        susa_4461_truereco_rad[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Excl_Range1_Genie_3_C12_4.461000.root";


        std::string sf_1161[2];
        std::string sf_2261[3];
        std::string sf_1161_true[2];
        std::string sf_1161_truereco[2];
        std::string sf_2261_true[3];
        std::string sf_2261_truereco[3];
        sf_1161[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SF/Excl_Range2_Genie_2_C12_1.161000.root";
        sf_1161[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SF/Excl_Range3_Genie_2_C12_1.161000.root";

        sf_2261[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SF/Excl_Range1_Genie_2_C12_2.261000.root";
        sf_2261[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SF/Excl_Range2_Genie_2_C12_2.261000.root";
        sf_2261[2] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SF/Excl_Range3_Genie_2_C12_2.261000.root";
        //std::string sf_4461[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SF/Excl_Range1_Genie_2_C12_4.461000.root";

        sf_1161_true[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SF/Excl_Range2_Genie_2_C12_1.161000.root";
        sf_1161_true[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SF/Excl_Range3_Genie_2_C12_1.161000.root";
        sf_2261_true[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SF/Excl_Range1_Genie_2_C12_2.261000.root";
        sf_2261_true[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SF/Excl_Range2_Genie_2_C12_2.261000.root";
        sf_2261_true[2] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SF/Excl_Range3_Genie_2_C12_2.261000.root";
        //std::string sf_4461_true[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Truth/Corr_Sectors/SF/Excl_Range1_Genie_2_C12_4.461000.root";

        sf_1161_truereco[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SF/Excl_Range2_Genie_2_C12_1.161000.root";
        sf_1161_truereco[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SF/Excl_Range3_Genie_2_C12_1.161000.root";
        sf_2261_truereco[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SF/Excl_Range1_Genie_2_C12_2.261000.root";
        sf_2261_truereco[1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SF/Excl_Range2_Genie_2_C12_2.261000.root";
        sf_2261_truereco[2] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SF/Excl_Range3_Genie_2_C12_2.261000.root";
        //std::string sf_4461_truereco[0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Truth_Reco/Corr_Sectors/SF/Excl_Range1_Genie_2_C12_4.461000.root";

	std::string first_en[2] = {"1.161 Excl Range 2","1.161 Excl Range 3"};
	std::string second_en[3] = {"2.261 Excl Range 1","2.261 Excl Range 2", "2.261 Excl Range 3"};
	std::string third_en[1] = {"4.461 Excl Range 1"}; 

        int sectors[3] = {2,3,4};

        int num_1161_sec = 3;
        int num_2261_sec = 3;
        int num_4461_sec = 3;

// --------------------- Getting radiative correction histograms from MC ----------------
        TH1D* SuSA_1161_true_reco_rad[2][6];
        TH1D* SuSA_2261_true_reco_rad[3][6];
        TH1D* SuSA_4461_true_reco_rad[1][6];

        for(const int &s : sectors) {
                for(int r = 0; r < 2; r++) {
                        SuSA_1161_true_reco_rad[r][s] = (TH1D*)SumProtSectorsAndInts(susa_1161_truereco_rad[r], s, false);
                        
                        UniversalE4vFunction(SuSA_1161_true_reco_rad[r][s], FSIModelsToLabels["SuSav2_RadCorr_LFGM_Truth_WithFidAcc_UpdatedSchwinger"], "12C", "1_161", TString::Format("susa_1161_mom_truereco_rad"));
        
                }
        


                for(int r = 0; r < 3; r++) {
                        SuSA_2261_true_reco_rad[r][s] = (TH1D*)SumProtSectorsAndInts(susa_2261_truereco_rad[r], s, false);
                        
                        UniversalE4vFunction(SuSA_2261_true_reco_rad[r][s],  FSIModelsToLabels["SuSav2_RadCorr_LFGM_Truth_WithFidAcc_UpdatedSchwinger"], "12C", "2_261", TString::Format("susa_2261_mom_truereco_rad"));
                }
                
        

               
                for(int r = 0; r < 1; r++) {
                        SuSA_4461_true_reco_rad[r][s] = (TH1D*)SumProtSectorsAndInts(susa_4461_truereco_rad[r], s, false);
                        
                        
                        UniversalE4vFunction(SuSA_4461_true_reco_rad[r][s],  FSIModelsToLabels["SuSav2_RadCorr_LFGM_Truth_WithFidAcc_UpdatedSchwinger"], "12C", "4_461", TString::Format("susa_4461_mom_truereco_rad"));
                }
                
        }

// --------------------- Getting acceptance correction histograms from MC ---------------
        
        //[NRanges][Exclusive = 0, Inclsuive = 1]     
        TH1D* SuSA_1161_true[2][6];
        TH1D* SuSA_1161_true_reco[2][6];
        TH1D* G_1161_true[2][6];
        TH1D* G_1161_true_reco[2][6];
        TH1D* SF_1161_true[2][6];
        TH1D* SF_1161_true_reco[2][6];

        TH1D* SuSA_2261_true[3][6];
        TH1D* SuSA_2261_true_reco[3][6];
        TH1D* G_2261_true[3][6];
        TH1D* G_2261_true_reco[3][6];
        TH1D* SF_2261_true[3][6];
        TH1D* SF_2261_true_reco[3][6];

        TH1D* SuSA_4461_true[1][6];
        TH1D* SuSA_4461_true_reco[1][6];
        TH1D* G_4461_true[1][6];
        TH1D* G_4461_true_reco[1][6];
        TH1D* SF_4461_true[1][6];
        TH1D* SF_4461_true_reco[1][6];


        for(const int &s : sectors) {
                //1.161 GeV
                for(int r = 0; r < 2; r++) {
                        SuSA_1161_true[r][s] = (TH1D*)SumProtSectorsAndInts(susa_1161_true[r], s, false);
                        SuSA_1161_true_reco[r][s] = (TH1D*)SumProtSectorsAndInts(susa_1161_truereco[r], s, false);
                        G_1161_true[r][s] = (TH1D*)SumProtSectorsAndInts(g_1161_true[r], s, false);
                        G_1161_true_reco[r][s] = (TH1D*)SumProtSectorsAndInts(g_1161_truereco[r], s, false);
                        SF_1161_true[r][s] = (TH1D*)SumProtSectorsAndInts(sf_1161_true[r], s, false);
                        SF_1161_true_reco[r][s] = (TH1D*)SumProtSectorsAndInts(sf_1161_truereco[r], s, false);
                        
                        UniversalE4vFunction(SuSA_1161_true[r][s],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "12C","1_161", TString::Format("susa_1161_mom_true_%i%i",r,s));
                        UniversalE4vFunction(G_1161_true[r][s],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "12C","1_161", TString::Format("g_1161_mom_true_%i%i",r,s));
                        UniversalE4vFunction(SF_1161_true[r][s],  "SF", "12C","1_161", TString::Format("sf_1161_mom_true_%i%i",r,s));
                        UniversalE4vFunction(SuSA_1161_true_reco[r][s],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","1_161", TString::Format("susa_1161_mom_truereco_%i%i",r,s));
                        UniversalE4vFunction(G_1161_true_reco[r][s],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","1_161", TString::Format("g_1161_mom_truereco_%i%i",r,s));
                        UniversalE4vFunction(SF_1161_true_reco[r][s],  "SF", "12C","1_161", TString::Format("sf_1161_mom_truereco_%i%i",r,s));
                }
                
        
                // 2.261 GeV
                for(int r = 0; r < 3; r++) {
                        
                        SuSA_2261_true[r][s] = (TH1D*)SumProtSectorsAndInts(susa_2261_true[r], s, false);
                        SuSA_2261_true_reco[r][s] = (TH1D*)SumProtSectorsAndInts(susa_2261_truereco[r], s, false);
                        G_2261_true[r][s] = (TH1D*)SumProtSectorsAndInts(g_2261_true[r], s, false);
                        G_2261_true_reco[r][s] = (TH1D*)SumProtSectorsAndInts(g_2261_truereco[r], s, false);
                        SF_2261_true[r][s] = (TH1D*)SumProtSectorsAndInts(sf_2261_true[r], s, false);
                        SF_2261_true_reco[r][s] = (TH1D*)SumProtSectorsAndInts(sf_2261_truereco[r], s, false);
                
                        
                        UniversalE4vFunction(SuSA_2261_true[r][s],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "12C","2_261", TString::Format("susa_2261_mom_%i%i",r,s));
                        UniversalE4vFunction(G_2261_true[r][s],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "12C","2_261", TString::Format("g_2261_mom_%i%i",r,s));
                        UniversalE4vFunction(SF_2261_true[r][s],  "SF", "12C","2_261", TString::Format("sf_2261_mom_true_%i%i",r,s));
                        UniversalE4vFunction(SuSA_2261_true_reco[r][s],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","2_261", TString::Format("susa_2261_mom_truereco_%i%i",r,s));
                        UniversalE4vFunction(G_2261_true_reco[r][s],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","2_261", TString::Format("g_2261_mom_truereco_%i%i",r,s));
                        UniversalE4vFunction(SF_2261_true_reco[r][s],  "SF", "12C","2_261", TString::Format("sf_2261_mom_truereco_%i%i",r,s));
                }
                   
        /*
        // 4.461 GeV
                for(int r = 0; r < 1; r++) {
                        SuSA_4461_true[r][s] = (TH1D*)SumProtSectorsAndInts(susa_4461_true[r], s, false);
                        SuSA_4461_true_reco[r][s] = (TH1D*)SumProtSectorsAndInts(susa_4461_truereco[r], s, false);
                        G_4461_true[r][s] = (TH1D*)SumProtSectorsAndInts(g_4461_true[r], s, false);
                        G_4461_true_reco[r][s] = (TH1D*)SumProtSectorsAndInts(g_4461_truereco[r], s, false);
                        SF_4461_true[r][s] = (TH1D*)SumProtSectorsAndInts(sf_4461_true[r], s, false);
                        SF_4461_true_reco[r][s] = (TH1D*)SumProtSectorsAndInts(sf_4461_truereco[r], s, false);
                
                        
                        UniversalE4vFunction(SuSA_4461_true[r][s],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "12C","4_461", TString::Format("susa_4461_mom_%i%i",r,s));
                        UniversalE4vFunction(G_4461_true[r][s],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "12C","4_461", TString::Format("g_4461_mom_%i%i",r,s));
                        UniversalE4vFunction(SF_4461_true[r][s],  "SF", "12C","1_161", TString::Format("sf_4461_mom_true_%i%i%i",r,p,s));
                        UniversalE4vFunction(SuSA_4461_true_reco[r][s],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","4_461", TString::Format("susa_4461_mom_truereco_%i%i",r,s));
                        UniversalE4vFunction(G_4461_true_reco[r][s],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","4_461", TString::Format("g_4461_mom_truereco_%i%i",r,s));
                        UniversalE4vFunction(SF_4461_true_reco[r][s],  "SF", "12C","1_161", TString::Format("sf_4461_mom_truereco_%i%i%i",r,p,s));
                }
        */        
        }
        


// --------------------- Getting MC exclusive and inclusive measurements and mec/neutron corrections ----------------

        //[NRanges][Exclusive = 0, Inclsuive = 1]     
        TH1D* SuSA_1161[2][6];     
        TH1D* SF_1161[2][6];
        double mec_corr_1161[2][6];
        double neutron_corr_1161_G18[2];
        double neutron_corr_1161_SF[2];
        double neutron_corr_1161_susa[2];

        // Get the exclusive and inclusive SuSA predictions as well as MEC corrections
        // neutron corrections to apply to data from G18
        // neutron corrections to apply to MEC from SuSA
        // 1.161 GeV
                for(int r = 0; r < 2; r++) {
                        std::cout << "Neutron and MEC corrections for " << first_en[r] << "\n";
                        
                        neutron_corr_1161_susa[r] = get_Neutron_corr(susa_1161[r], false);
                        neutron_corr_1161_G18[r] = get_Neutron_corr(g_1161[r], false);
                        neutron_corr_1161_SF[r] = get_Neutron_corr(sf_1161[r], false);
                
                        
                        std::cout << "G18 N: " << neutron_corr_1161_G18[r] << "\n";
                        std::cout << "SF N: " << neutron_corr_1161_SF[r] << "\n";
                        std::cout << "SuSA N: " <<  neutron_corr_1161_susa[r] << "\n";
                        for(const int &s : sectors) {
                                
                                SuSA_1161[r][s] = (TH1D*)SumProtSectorsAndInts(susa_1161[r], s, false);
                                SF_1161[r][s] = (TH1D*)SumProtSectorsAndInts(sf_1161[r], s, false);
                                mec_corr_1161[r][s] = get_MEC_corr(susa_1161[r], s, false);
                                
                                std::cout << "sector " << s << "\n";
                                std::cout << "MEC: " << mec_corr_1161[r][s] << "\n";
                                UniversalE4vFunction(SuSA_1161[r][s], FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","1_161", TString::Format("susa_1161_mom_reco_%i%i",r,s));
                                UniversalE4vFunction(SF_1161[r][s], "SF", "12C","1_161", TString::Format("sf_1161_mom_reco_%i%i",r,s));
                        }
                }
        
        std::cout << "\n";

        TH1D* SuSA_2261[3][6];    
        TH1D* SF_2261[2][6];
        double mec_corr_2261[3][6];
        double neutron_corr_2261_G18[3];
        double neutron_corr_2261_susa[3];
        double neutron_corr_2261_SF[3];
        // 2.261 GeV
                for(int r = 0; r < 3; r++) {
                        std::cout<< "Neutron and MEC corrections for " << second_en[r] << "\n"; 
                        
                                neutron_corr_2261_susa[r] = get_Neutron_corr(susa_2261[r], false);
                                neutron_corr_2261_G18[r] = get_Neutron_corr(g_2261[r], false);
                                neutron_corr_2261_SF[r] = get_Neutron_corr(sf_2261[r], false);
                        
                        
                        std::cout << "G18 N: " << neutron_corr_2261_G18[r] << "\n";
                        std::cout << "SF N: " << neutron_corr_2261_SF[r] << "\n";
                        std::cout << "SuSA N: " << neutron_corr_2261_susa[r] << "\n";
                        for(const int &s : sectors) {
                                        SuSA_2261[r][s] = (TH1D*)SumProtSectorsAndInts(susa_2261[r], s, false);
                                        SF_2261[r][s] = (TH1D*)SumProtSectorsAndInts(sf_2261[r], s, false);
                                        mec_corr_2261[r][s] = get_MEC_corr(susa_2261[r], s, false);
                                        
                                
                                
                                std::cout << "sector " << s << "\n";
                                std::cout << "MEC: " << mec_corr_2261[r][s] << "\n";
                                UniversalE4vFunction(SuSA_2261[r][s], FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","2_261", TString::Format("susa_2261_mom_reco_%i%i",r,s));
                                UniversalE4vFunction(SF_2261[r][s], "SF", "12C","2_261", TString::Format("sf_2261_mom_reco_%i%i",r,s));
                        }
                }
        
        std::cout << "\n";
        /*
        TH1D* SuSA_4461[1][6];
        TH1D* SF_4461[1][6];
        double mec_corr_4461[1][6];
        double neutron_corr_4461_G18[1];
        double neutron_corr_4461_susa[1];
        // 4.461 GeV
                for(int r = 0; r < 1; r++) {
                       // std::cout << "Neutron and MEC corrections for "<< third_en[r] << "\n";
                       
                                neutron_corr_4461_susa[r] = get_Neutron_corr(susa_4461[r], false);
                                neutron_corr_4461_G18[r] = get_Neutron_corr(g_4461[r], false);
                        
                        
                        std::cout << "G18 N: " << neutron_corr_4461_G18[r] << "\n";
                        std::cout << "SuSA N: " << neutron_corr_4461_susa[r] << "\n";
                        for(const int &s : sectors) {
                                        SuSA_4461[r][s] = (TH1D*)SumProtSectorsAndInts(susa_4461[r], s, false);
                                        //SF_4461[r][s] = (TH1D*)SumProtSectorsAndInts(sf_4461[r], s, false);
                                        mec_corr_4461[r][s] = get_MEC_corr(susa_4461[r], s, false);   
                                
                                
                                std::cout << "sector " << s << "\n";
                                std::cout << "MEC: " << mec_corr_4461[r][s] << "\n";
                                UniversalE4vFunction(SuSA_4461[r][s], FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","4_461", TString::Format("susa_4461_mom_reco_%i%i",r,s));
                                //UniversalE4vFunction(SF_4461[r][s], FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","4_461", TString::Format("sf_4461_mom_reco_%i%i",r,s));
                        }
                }
                */
        
        std::cout << "\n";
        

// --------------------- Getting Data exclusive and inclusive measurements ----------------

        // Here we will also scale the data
        TH1D* Data_1161[2][6];
        TH1D* Data_2261[3][6];
        TH1D* Data_4461[1][6];

        for( const int &s : sectors) {
                        Data_1161[0][s] = (TH1D*)SumProtSectorsAndInts(data_1161[0], s, true);
                        Data_1161[1][s] = (TH1D*)SumProtSectorsAndInts(data_1161[1], s, true);
                        Data_2261[0][s] = (TH1D*)SumProtSectorsAndInts(data_2261[0], s, true);
                        Data_2261[1][s] = (TH1D*)SumProtSectorsAndInts(data_2261[1], s, true);
                        Data_2261[2][s] = (TH1D*)SumProtSectorsAndInts(data_2261[2], s, true);
                        //Data_4461[0][s] = (TH1D*)SumProtSectorsAndInts(data_4461[0], s, true);
                
                
                UniversalE4vFunction(Data_1161[0][s], "Pinned Data", "12C", "1_161", TString::Format("data_1161_mom_0%i",s));
                UniversalE4vFunction(Data_1161[1][s], "Pinned Data", "12C", "1_161", TString::Format("data_1161_mom_1%i",s));
                UniversalE4vFunction(Data_2261[0][s], "Pinned Data", "12C", "2_261", TString::Format("data_2261_mom_0%i",s));
                UniversalE4vFunction(Data_2261[1][s], "Pinned Data", "12C", "2_261", TString::Format("data_2261_mom_1%i",s));
                UniversalE4vFunction(Data_2261[2][s], "Pinned Data", "12C", "2_261", TString::Format("data_2261_mom_2%i",s));
                //UniversalE4vFunction(Data_4461[0][s], "Pinned Data", "12C", "4_461", TString::Format("data_4461_mom_0%i",s));
        }
        

// ---------------- Acceptance correct all histograms ---------------------
        TCanvas *ca = new TCanvas("","",800,800);
	if(make_plots) {
		
		ca->SaveAs("C12_true_vs_truereco.pdf(");
        	ca->SaveAs("C12_truerecorad_vs_truereco.pdf(");
        	ca->SaveAs("C12_Acceptance_Ratios.pdf(");
		ca->SaveAs("C12_Rad_Ratios.pdf(");
	}
        
        
        for(const int &s : sectors) {
                //1161
                
                        for(int r = 0; r < 2; r++) {
        		        Data_1161[r][s]->SetTitle(TString::Format("Data1161_%s%i",first_en[r].c_str(),s));
                                Data_1161[r][s] = (TH1D*)AcceptanceCorrect(Data_1161[r][s], SuSA_1161_true[r][s], SuSA_1161_true_reco[r][s], SuSA_1161_true_reco_rad[r][s], make_plots, true, false);
                        }   
                                  
                
        

                //2261
                        for(int r = 0; r < 3; r++) {
        		        Data_2261[r][s]->SetTitle(TString::Format("Data2261_%s%i",second_en[r].c_str(),s));
                                Data_2261[r][s] = (TH1D*)AcceptanceCorrect(Data_2261[r][s], SuSA_2261_true[r][s], SuSA_2261_true_reco[r][s], SuSA_2261_true_reco_rad[r][s], make_plots, true, false);
                        }
                

                //4461
                        /*
                        for(int r = 0; r < 1; r++) {
        		        Data_4461[r][s]->SetTitle(TString::Format("Data4461_%s%i",third_en[r].c_str(),s));
                                Data_4461[r][s] = (TH1D*)AcceptanceCorrect(Data_4461[r][s], SF_4461_true[r][s], SF_4461_true_reco[r][s], SuSA_4461_true_reco_rad[r][s], make_plots, true, false);
                        }
                        */
                
        }
        
        
	if(make_plots) {
        	ca->SaveAs("C12_true_vs_truereco.pdf)");
        	ca->SaveAs("C12_truerecorad_vs_truereco.pdf)");
        	ca->SaveAs("C12_Acceptance_Ratios.pdf)");
		ca->SaveAs("C12_Rad_Ratios.pdf)");
	}


// ---------------- Get average proton momentum for data and MC ------------------------
        
        double data_avg_prot_mom_1161[2][6];
        double data_avg_prot_mom_2261[3][6];
        double data_avg_prot_mom_4461[1][6];

        double SF_avg_prot_mom_1161[2][6];
        double SF_avg_prot_mom_2261[3][6];
        double SF_avg_prot_mom_4461[1][6];

        //std::cout << "Avg proton momentum for data and MC " << "\n";
        for(const int &s : sectors) {
                printit("Sector", s);
                data_avg_prot_mom_1161[0][s] = weighted_average(Data_1161[0][s]); 
                data_avg_prot_mom_1161[1][s] = weighted_average(Data_1161[1][s]);
                data_avg_prot_mom_2261[0][s] = weighted_average(Data_2261[0][s]); 
                data_avg_prot_mom_2261[1][s] = weighted_average(Data_2261[1][s]); 
                data_avg_prot_mom_2261[2][s] = weighted_average(Data_2261[2][s]);
                //data_avg_prot_mom_4461[0][s] = weighted_average(Data_4461[0][s]); 

                
                SF_avg_prot_mom_1161[0][s] = weighted_average(SF_1161[0][s]); 
                SF_avg_prot_mom_1161[1][s] = weighted_average(SF_1161[1][s]);
                SF_avg_prot_mom_2261[0][s] = weighted_average(SF_2261[0][s]); 
                SF_avg_prot_mom_2261[1][s] = weighted_average(SF_2261[1][s]); 
                SF_avg_prot_mom_2261[2][s] = weighted_average(SF_2261[2][s]);
                //SF_avg_prot_mom_4461[0][s] = weighted_average(SF_4461[0][s]); 


                printit("data 1161 range 2", data_avg_prot_mom_1161[0][s]);
                printit("SF 1161 range 2", SF_avg_prot_mom_1161[0][s]);
                printit("data 1161 range 3", data_avg_prot_mom_1161[1][s]);
                printit("SF 1161 range 3", SF_avg_prot_mom_1161[1][s]);
                printit("data 2261 range 1", data_avg_prot_mom_2261[0][s]);
                printit("SF 2261 range 1", SF_avg_prot_mom_2261[0][s]);
                printit("data 2261 range 2", data_avg_prot_mom_2261[1][s]);
                printit("SF 2261 range 2", SF_avg_prot_mom_2261[1][s]);
                printit("data 2261 range 3", data_avg_prot_mom_2261[2][s]);
                printit("SF 2261 range 3", SF_avg_prot_mom_2261[2][s]);
                //printit("data 4461 range 1", data_avg_prot_mom_4461[0][s]); 
                //printit("SuSA 4461 range 1", SuSA_avg_prot_mom_4461[0][s]);
        }

// -------------- Add systematic uncertainties ---------------------------

        for(const int &s : sectors) {
                //1161
                for(int r = 0; r < 2; r++) {
                        ApplySystUnc(Data_1161[r][s],"1_161"); 
                }
                
        
                //2261
                for(int r = 0; r < 3; r++) {
                        ApplySystUnc(Data_2261[r][s],"2_261");
                }
                

                //4461
                //for(int r = 0; r < 1; r++) {
                //       ApplySystUnc(Data_4461[r][s],"4_461"); 
                //}
                
        }

// -------------- Correct for MEC and neutron contamination --------------
        //Correct Data by (1-(MECfrac))*(G18_prot/(G18_prot + G18_neut))
        //Correct MC by (1-(MECfrac))*(SuSA_prot/(SuSA_prot + SuSA_neut))
        /*
        for(const int &s : sectors) {
                //1161
                for(int p = 0; p < 2; p++) {
                        for(int r = 0; r < 2; r++) {
                                Data_1161[r][s]->Scale((1. - mec_corr_1161[r][s]));
                                SuSA_1161[r][s]->Scale((1. - mec_corr_1161[r][s]));
        			if(p == 1) {	
        				SuSA_1161[r][s]->Scale(neutron_corr_1161_susa[r]);
        				Data_1161[r][s]->Scale(neutron_corr_1161_G18[r]);
        			}
                        }
                }
        
                //2261
                for(int p = 0; p < 2; p++) {
                        for(int r = 0; r < 3; r++) {
                                Data_2261[r][s]->Scale((1. - mec_corr_2261[r][s]));
                                SuSA_2261[r][s]->Scale((1. - mec_corr_2261[r][s]));
                 		if(p == 1) {    
                                        SuSA_2261[r][s]->Scale(neutron_corr_2261_susa[r]);
                                        Data_2261[r][s]->Scale(neutron_corr_2261_G18[r]);
                                }
                        }
	        }

                //4461
                for(int p = 0; p < 2; p++) {
                        for(int r = 0; r < 1; r++) {
                                Data_4461[r][s]->Scale((1. - mec_corr_4461[r][s]));
                                SuSA_4461[r][s]->Scale((1. - mec_corr_4461[r][s]));
        			if(p == 1) {    
                                        SuSA_4461[r][s]->Scale(neutron_corr_4461_susa[r]);
                                        Data_4461[r][s]->Scale(neutron_corr_4461_G18[r]);
                                }
                        }
                }
        }*/

//Combine histograms to get overall average proton momentum
        TH1D* Data_comb_1161[2];
        TH1D* Data_comb_2261[3];
        TH1D* Data_comb_4461[1];
        TH1D* SF_comb_1161[2];
        TH1D* SF_comb_2261[3];
        TH1D* SF_comb_4461[1];
        
        for(const int &s : sectors ){
                
                for(int r = 0; r < 2; r++ ) {
                        std::cout << "s = " << s << "\n";
                        if(s == 2) {

                        std::cout << "s = " << s << "\n";
                                Data_comb_1161[r] = (TH1D*)( (Data_1161[r][s])->Clone() );
                                SF_comb_1161[r] = (TH1D*)( (SF_1161[r][s])->Clone() );
                        }
                        if(s != 2) {

                        std::cout << "s = " << s << "\n";
                                Data_comb_1161[r]->Add( Data_1161[r][s] );
                                SF_comb_1161[r]->Add( SF_1161[r][s] );
                        }

                }
             
                for(int r = 0; r < 3; r++) {
                        if(s == 2) {
                                Data_comb_2261[r] = (TH1D*)( Data_2261[r][s]->Clone() );
                                SF_comb_2261[r] = (TH1D*)( SF_2261[r][s]->Clone() );

                        }
                        if(s != 2) {
                                Data_comb_2261[r]->Add( Data_2261[r][s] );
                                SF_comb_2261[r]->Add( SF_2261[r][s] );
                        }

                }
                
                /*
                for(int r = 0; r < 1; r++) {
                        if(s == 2) {
                                Data_comb_4461[r] = (TH1D*)( Data_4461[r][s]->Clone() );
                                SF_comb_4461[r] = (TH1D*)( SF_4461[r][s]->Clone() );
                        }
                        if(s != 2) {
                                Data_comb_4461[r]->Add( Data_4461[r][s] );
                                SF_comb_4461[r]->Add( SF_4461[r][s] );
                        }
                }*/
                
        }


        // ---------------- Make plots of reconstructed momentum distributions for acc corrected data/MC ------------

        if(make_plots) { 
        TCanvas* reco_dist_canvas = new TCanvas("","",1000,800);   
          
                TLegend *leg1161[2];
                
                reco_dist_canvas->SaveAs("C12_reco_dist.pdf(");
                for(int r = 0; r< 2; r++ ) {
                        SF_comb_1161[r]->Draw("e hist");
                        Data_comb_1161[r]->Draw("e same");
                        SF_comb_1161[r]->SetTitle("SF C12");
                        Data_comb_1161[r]->SetTitle("Data C12");
                        Data_comb_1161[r]->SetMarkerColor(kBlack);
                        Data_comb_1161[r]->SetMarkerStyle(20);
                        SF_comb_1161[r]->GetYaxis()->SetTitle("Absolute Yield");
                        SF_comb_1161[r]->GetXaxis()->SetTitle("Momentum (GeV)");
                        leg1161[r] = new TLegend(0.7,0.75,0.89,0.89);
                        leg1161[r]->AddEntry(Data_comb_1161[r]);
                        leg1161[r]->AddEntry(SF_comb_1161[r]);
                        leg1161[r]->Draw();
                        SF_comb_1161[r]->SetTitle(TString::Format("SF C12 %s", first_en[r].c_str()));
                        reco_dist_canvas->SaveAs("C12_reco_dist.pdf");
                }


                TLegend *leg2261[3];
                for(int r = 0; r< 3; r++ ) {
                        SF_comb_2261[r]->Draw("e hist");
                        Data_comb_2261[r]->Draw("e same");
                        SF_comb_2261[r]->SetTitle("SF C12");
                        Data_comb_2261[r]->SetTitle("Data C12");
                        Data_comb_2261[r]->SetMarkerColor(kBlack);
                        Data_comb_2261[r]->SetMarkerStyle(20);
                        SF_comb_2261[r]->GetYaxis()->SetTitle("Absolute Yield");
                        SF_comb_2261[r]->GetXaxis()->SetTitle("Momentum (GeV)");
                        leg2261[r] = new TLegend(0.7,0.75,0.89,0.89);
                        leg2261[r]->AddEntry(Data_comb_2261[r]);
                        leg2261[r]->AddEntry(SF_comb_2261[r]);
                        leg2261[r]->Draw();
                        SF_comb_2261[r]->SetTitle(TString::Format("SF C12 %s", second_en[r].c_str()));
                        reco_dist_canvas->SaveAs("C12_reco_dist.pdf");
                }
                

                        /*
                TLegend *leg4461[1];
                        for(int r = 0; r< 1; r++ ) {
                                SF_comb_4461[r]->Draw("e hist");
                                Data_comb_4461[r]->Draw("e same");
                                SF_comb_4461[r]->SetTitle("SF C12");
                                Data_comb_4461[r]->SetTitle("Data C12");
                                Data_comb_4461[r]->SetMarkerColor(kBlack);
                                Data_comb_4461[r]->SetMarkerStyle(20);
                                SF_comb_4461[r]->GetYaxis()->SetTitle("Absolute Yield");
                                SF_comb_4461[r]->GetXaxis()->SetTitle("Momentum (GeV)");
                                leg4461[r] = new TLegend(0.7,0.75,0.89,0.89);
                                leg4461[r]->AddEntry(Data_comb_4461[r]);
                                leg4461[r]->AddEntry(SF_comb_4461[r]);
                                leg4461[r]->Draw();
                                SF_comb_4461[r]->SetTitle(TString::Format("SF C12 %s", third_en[r].c_str()));
                                reco_dist_canvas->SaveAs("C12_reco_dist.pdf");
                        }*/
                
                reco_dist_canvas->SaveAs("C12_reco_dist.pdf)");

        }


        double data_comb_int_1161[2];
        double data_comb_int_2261[3];
        double data_comb_int_4461[1];
        double data_comb_int_1161_err[2];
        double data_comb_int_2261_err[3];
        double data_comb_int_4461_err[1];

        double SF_comb_int_1161[2];
        double SF_comb_int_2261[3];
        double SF_comb_int_4461[1];
        double SF_comb_int_1161_err[2];
        double SF_comb_int_2261_err[3];
        double SF_comb_int_4461_err[1];

        std::cout << "Data and SF combined yields" << "\n";
        
        for(int r = 0; r < 2; r++) {
                data_comb_int_1161[r] = Data_comb_1161[r]->IntegralAndError(1, Data_comb_1161[r]->GetNbinsX(), data_comb_int_1161_err[r],"width");
                SF_comb_int_1161[r] = SF_comb_1161[r]->IntegralAndError(1, SF_comb_1161[r]->GetNbinsX(), SF_comb_int_1161_err[r],"width");
                        std::cout << "Data " << first_en[r] << " = " << data_comb_int_1161[r] << "\n";
                        std::cout << "SF " << first_en[r] << " = " << SF_comb_int_1161[r] << "\n";
                        std::cout << "\n"; 
        }
        for(int r = 0; r < 3; r++) {
                data_comb_int_2261[r] = Data_comb_2261[r]->IntegralAndError(1, Data_comb_2261[r]->GetNbinsX(), data_comb_int_2261_err[r],"width");
                SF_comb_int_2261[r] = SF_comb_2261[r]->IntegralAndError(1, SF_comb_2261[r]->GetNbinsX(), SF_comb_int_2261_err[r],"width");
                        std::cout << "Data " << second_en[r] << " = " << data_comb_int_2261[r] << "\n";
                        std::cout << "SF " << second_en[r] << " = " << SF_comb_int_2261[r] << "\n";
                        std::cout << "\n"; 
        }/*
        for(int r = 0; r < 1; r++) {
                data_comb_int_4461[r] = Data_comb_4461[r]->IntegralAndError(1, Data_comb_4461[r]->GetNbinsX(), data_comb_int_4461_err[r],"width");
                SF_comb_int_4461[r] = SF_comb_4461[r]->IntegralAndError(1, SF_comb_4461[r]->GetNbinsX(), SF_comb_int_4461_err[r],"width");
                        std::cout << "Data " << third_en[r] << " = " << data_comb_int_4461[r] << "\n";
                        std::cout << "SF " << third_en[r] << " = " << SF_comb_int_4461[r] << "\n";
                        std::cout << "\n";               
        }*/
        
        printit("here1",NULL);

        double data_comb_avg_prot_mom_1161[2];
        double data_comb_avg_prot_mom_2261[3];
        double data_comb_avg_prot_mom_4461[1];

        double SF_comb_avg_prot_mom_1161[2];
        double SF_comb_avg_prot_mom_2261[3];
        double SF_comb_avg_prot_mom_4461[1];

        data_comb_avg_prot_mom_1161[0] = weighted_average(Data_comb_1161[0]); 
        data_comb_avg_prot_mom_1161[1] = weighted_average(Data_comb_1161[1]);
        data_comb_avg_prot_mom_2261[0] = weighted_average(Data_comb_2261[0]); 
        data_comb_avg_prot_mom_2261[1] = weighted_average(Data_comb_2261[1]); 
        data_comb_avg_prot_mom_2261[2] = weighted_average(Data_comb_2261[2]);
        //data_comb_avg_prot_mom_4461[0] = weighted_average(Data_comb_4461[0]); 

        SF_comb_avg_prot_mom_1161[0] = weighted_average(SF_comb_1161[0]); 
        SF_comb_avg_prot_mom_1161[1] = weighted_average(SF_comb_1161[1]);
        SF_comb_avg_prot_mom_2261[0] = weighted_average(SF_comb_2261[0]); 
        SF_comb_avg_prot_mom_2261[1] = weighted_average(SF_comb_2261[1]); 
        SF_comb_avg_prot_mom_2261[2] = weighted_average(SF_comb_2261[2]);
        //SF_comb_avg_prot_mom_4461[0] = weighted_average(SF_comb_4461[0]); 

        

        printit("here2",NULL);

// -------------- Integrate histograms -----------------

        double data_int_1161[2][6];
        double data_int_2261[3][6];
        //double data_int_4461[1][6];
        double data_int_1161_err[2][6];
        double data_int_2261_err[3][6];
        //double data_int_4461_err[1][6];

        double SF_int_1161[2][6];
        double SF_int_2261[3][6];
        //double SF_int_4461[1][6];
        double SF_int_1161_err[2][6];
        double SF_int_2261_err[3][6];
        //double SF_int_4461_err[1][6];

        //std::cout << "Yields for Data and MC" << "\n";
        for( const int &s : sectors) {
        //std::cout << "Sector " << s << "\n";
                 //1161
                
                for(int r = 0; r < 2; r++) {
                		data_int_1161[r][s] = Data_1161[r][s]->IntegralAndError(1, Data_1161[r][s]->GetNbinsX(), data_int_1161_err[r][s],"width");
                                SF_int_1161[r][s] = SF_1161[r][s]->IntegralAndError(1, SF_1161[r][s]->GetNbinsX(), SF_int_1161_err[r][s],"width");
                		//std::cout << "Data " << first_en[r] << " = " << data_int_1161[r][s] << "\n";
                		//std::cout << "SF " << first_en[r] << " = " << SF_int_1161[r][s] << "\n";
                		//std::cout << "\n"; 
                        
                }

                //2261
                for(int r = 0; r < 3; r++) {
                                data_int_2261[r][s] = Data_2261[r][s]->IntegralAndError(1, Data_2261[r][s]->GetNbinsX(), data_int_2261_err[r][s],"width");
                                SF_int_2261[r][s] = SF_2261[r][s]->IntegralAndError(1, SF_2261[r][s]->GetNbinsX(), SF_int_2261_err[r][s],"width");
                                //std::cout << "Data " << second_en[r] << " = " << data_int_2261[r][s] << "\n";
                                //std::cout << "SF " << second_en[r] << " = " << SF_int_2261[r][s] << "\n";
                                //std::cout << "\n";
                        
                }

                //4461
                /*
                for(int r = 0; r < 1; r++) {
                                data_int_4461[r][s] = Data_4461[r][s]->IntegralAndError(1, Data_4461[r][s]->GetNbinsX(), data_int_4461_err[r][s],"width");
                                SF_int_4461[r][s] = SF_4461[r][s]->IntegralAndError(1, SF_4461[r][s]->GetNbinsX(), SF_int_4461_err[r][s],"width");
                                //std::cout << "Data " << third_en[r] << " = " << data_int_4461[r][s] << "\n";
                                //std::cout << "SF " << third_en[r] << " = " << SF_int_4461[r][s] << "\n";
                                //std::cout << "\n"; 
                        
                }*/
        }

        printit("here3",NULL);
// ----------- Take Ratios to obtain transparencies and errors --------------
        //Remember that a proton in sector i corresponds to an electron in sector (i-3)

        // Sector by sector data transparencies
        double data_T_1161[2][6];
        double data_T_2261[3][6];
        //double data_T_4461[1][6];
        double data_T_1161_err[2][6];
        double data_T_2261_err[3][6];
        //double data_T_4461_err[1][6];

        // Spread in data transparencies
        double data_spread_T_1161[2];
        double data_spread_T_2261[3];
        //double data_spread_T_4461[1];
        double data_spread_T_1161_err[2];
        double data_spread_T_2261_err[3];
        //double data_spread_T_4461_err[1];

        // Data combined transparencies
        double data_comb_T_1161[2];
        double data_comb_T_2261[3];
        //double data_comb_T_4461[1];
        double data_comb_T_1161_err[2];
        double data_comb_T_2261_err[3];
        //double data_comb_T_4461_err[1];

       

        for(const int &s : sectors) {
                data_T_1161[0][s] = data_int_1161[0][s]/SF_int_1161[0][s];
                data_T_1161[1][s] = data_int_1161[1][s]/SF_int_1161[1][s];
                data_T_2261[0][s] = data_int_2261[0][s]/SF_int_2261[0][s];
                data_T_2261[1][s] = data_int_2261[1][s]/SF_int_2261[1][s];
                data_T_2261[2][s] = data_int_2261[2][s]/SF_int_2261[2][s];
                //data_T_4461[0][s] = data_int_4461[0][s]/SF_int_4461[0][s];

                data_T_1161_err[0][s] = get_ratio_error(data_int_1161[0][s],SF_int_1161[0][s], data_int_1161_err[0][s], SF_int_2261_err[0][s]);
                data_T_1161_err[1][s] = get_ratio_error(data_int_1161[1][s],SF_int_1161[1][s], data_int_1161_err[1][s], SF_int_2261_err[1][s]);
                data_T_2261_err[0][s] = get_ratio_error(data_int_2261[0][s],SF_int_2261[0][s], data_int_2261_err[0][s], SF_int_2261_err[0][s]);
                data_T_2261_err[1][s] = get_ratio_error(data_int_2261[1][s],SF_int_2261[1][s], data_int_2261_err[1][s], SF_int_2261_err[1][s]);
                data_T_2261_err[2][s] = get_ratio_error(data_int_2261[2][s],SF_int_2261[2][s], data_int_2261_err[2][s], SF_int_2261_err[2][s]);
                //data_T_4461_err[0][s] = get_ratio_error(data_int_4461[0][s],SF_int_4461[0][s]);
        }

        for(const int &s : sectors) {
                //Compute spread of transparencies 
                if(s != 3) {
                        data_spread_T_1161[0] += diff_squared(data_T_1161[0][3],data_T_1161[0][s]);
                        data_spread_T_1161[1] += diff_squared(data_T_1161[1][3],data_T_1161[1][s]);
                        data_spread_T_2261[0] += diff_squared(data_T_2261[0][3],data_T_2261[0][s]);
                        data_spread_T_2261[1] += diff_squared(data_T_2261[1][3],data_T_2261[1][s]);
                        data_spread_T_2261[2] += diff_squared(data_T_2261[2][3],data_T_2261[2][s]);
                        //data_spread_T_4461[0] += diff_squared(data_T_4461[0][3],data_T_4461[0][s]);
                }
        }

        printit("here4",NULL);
        // Take sqrt of sector uncertainties and then add them to overall uncertainty 
        data_spread_T_1161[0] = sqrt(data_spread_T_1161[0]/num_1161_sec);
        data_spread_T_1161[1] = sqrt(data_spread_T_1161[1]/num_1161_sec);
        data_spread_T_2261[0] = sqrt(data_spread_T_2261[0]/num_2261_sec);
        data_spread_T_2261[1] = sqrt(data_spread_T_2261[1]/num_2261_sec);
        data_spread_T_2261[2] = sqrt(data_spread_T_2261[2]/num_2261_sec);
        //data_spread_T_4461[0] = sqrt(data_spread_T_4461[0]/num_4461_sec);

        //Get combined transparencies and errors
        data_comb_T_1161[0] = data_comb_int_1161[0]/SF_comb_int_1161[0];
        data_comb_T_1161[1] = data_comb_int_1161[1]/SF_comb_int_1161[1];
        data_comb_T_2261[0] = data_comb_int_2261[0]/SF_comb_int_2261[0];
        data_comb_T_2261[1] = data_comb_int_2261[1]/SF_comb_int_2261[1];
        data_comb_T_2261[2] = data_comb_int_2261[2]/SF_comb_int_2261[2];
        //data_comb_T_4461[0] = data_comb_int_4461[0]/SF_comb_int_4461[0];

        data_comb_T_1161_err[0] = get_ratio_error(data_comb_int_1161[0],SF_comb_int_1161[0],data_comb_int_1161_err[0],SF_comb_int_1161_err[0]);
        data_comb_T_1161_err[1] = get_ratio_error(data_comb_int_1161[1],SF_comb_int_1161[1],data_comb_int_1161_err[1],SF_comb_int_1161_err[1]);
        data_comb_T_2261_err[0] = get_ratio_error(data_comb_int_2261[0],SF_comb_int_2261[0],data_comb_int_2261_err[0],SF_comb_int_2261_err[0]);
        data_comb_T_2261_err[1] = get_ratio_error(data_comb_int_2261[1],SF_comb_int_2261[1],data_comb_int_2261_err[1],SF_comb_int_2261_err[1]);
        data_comb_T_2261_err[2] = get_ratio_error(data_comb_int_2261[2],SF_comb_int_2261[2],data_comb_int_2261_err[2],SF_comb_int_2261_err[2]);
        //data_comb_T_4461_err[0] = get_ratio_error(data_comb_int_4461[0],SF_comb_int_4461[0],data_comb_int_4461_err[0],SF_comb_int_4461_err[0]);
// ---------------------------------------------------------------------

        printit("here5",NULL);
        double ypoints[6][5]; 
        double ypoint_errs[6][5]; 
        double xpoints[6][5]; 
        double xpoint_errs[6][5]; 

        double comb_ypoints[5]; 
        double comb_ypoint_errs[5]; 
        double comb_xpoints[5]; 
        double comb_xpoint_errs[5]; 


        for(const int &s : sectors) {
                ypoints[s][0] = data_T_1161[0][s];
                ypoints[s][1] = data_T_1161[1][s];
                ypoints[s][2] = data_T_2261[0][s];
                ypoints[s][3] = data_T_2261[1][s];
                ypoints[s][4] = data_T_2261[2][s];
                //ypoints[s][5] = data_T_4461[0][s];

                ypoint_errs[s][0] = data_T_1161_err[0][s];
                ypoint_errs[s][1] = data_T_1161_err[1][s];
                ypoint_errs[s][2] = data_T_2261_err[0][s];
                ypoint_errs[s][3] = data_T_2261_err[1][s];
                ypoint_errs[s][4] = data_T_2261_err[2][s];
                //ypoint_errs[s][5] = data_T_4461_err[0][s];

                xpoints[s][0] = data_avg_prot_mom_1161[0][s];
                xpoints[s][1] = data_avg_prot_mom_1161[1][s];
                xpoints[s][2] = data_avg_prot_mom_2261[0][s];
                xpoints[s][3] = data_avg_prot_mom_2261[1][s];
                xpoints[s][4] = data_avg_prot_mom_2261[2][s];
                //xpoints[s][5] = data_avg_prot_mom_4461[0][s];

                

                for(int i = 0; i < 5; i++){
                        xpoint_errs[s][i] = 0.0;
                }
        }

        printit("here6",NULL);
        comb_ypoints[0] = data_comb_T_1161[0];
        comb_ypoints[1] = data_comb_T_1161[1];
        comb_ypoints[2] = data_comb_T_2261[0];
        comb_ypoints[3] = data_comb_T_2261[1];
        comb_ypoints[4] = data_comb_T_2261[2];
        //comb_ypoints[5] = data_comb_T_4461[0];

        printit("here7",NULL);
        comb_ypoint_errs[0] = sqrt(pow(data_comb_T_1161_err[0],2) + pow(data_spread_T_1161[0],2));
        comb_ypoint_errs[1] = sqrt(pow(data_comb_T_1161_err[1],2) + pow(data_spread_T_1161[1],2));
        comb_ypoint_errs[2] = sqrt(pow(data_comb_T_2261_err[0],2) + pow(data_spread_T_2261[0],2));
        comb_ypoint_errs[3] = sqrt(pow(data_comb_T_2261_err[1],2) + pow(data_spread_T_2261[1],2));
        comb_ypoint_errs[4] = sqrt(pow(data_comb_T_2261_err[2],2) + pow(data_spread_T_2261[2],2));
        //comb_ypoint_errs[5] = sqrt(pow(data_comb_T_4461_err[0],2) + pow(data_spread_T_4461[0],2));

        comb_xpoints[0] = data_comb_avg_prot_mom_1161[0];
        comb_xpoints[1] = data_comb_avg_prot_mom_1161[1];
        comb_xpoints[2] = data_comb_avg_prot_mom_2261[0];
        comb_xpoints[3] = data_comb_avg_prot_mom_2261[1];
        comb_xpoints[4] = data_comb_avg_prot_mom_2261[2];
        //comb_xpoints[5] = data_comb_avg_prot_mom_4461[0];

        for(int i = 0; i < 5; i++){
                comb_xpoint_errs[i] = 0.0;
        }

        
        printit("here8",NULL);
        TCanvas* c_data;
        c_data = new TCanvas(TString::Format("Data transparency by sector"), TString::Format("Data transparency by sector"), 800, 600);

        TGraphErrors *data_t[6];
        for(const int &s : sectors){
                data_t[s] = new TGraphErrors(5, xpoints[s], ypoints[s], xpoint_errs[s], ypoint_errs[s]);
                data_t[s]->SetTitle(TString::Format("Sector %i",s));
                data_t[s]->GetXaxis()->SetTitle("Proton Momentum (GeV)");
                data_t[s]->GetYaxis()->SetTitle("Transparency");
                data_t[s]->SetMarkerStyle(kFullCircle);
                data_t[s]->SetMarkerColor(3+s);
                data_t[s]->SetLineColor(3+s);
                //data_t[s]->GetYaxis()->SetRangeUser(0.1,1.0);
        }
        TGraphErrors *data_comb_t = new TGraphErrors(5, comb_xpoints, comb_ypoints, comb_xpoint_errs, comb_ypoint_errs);
        data_comb_t->SetTitle("All Sectors");
        data_comb_t->SetMarkerStyle(kFullCircle);
        data_comb_t->SetMarkerColor(12);
        
        data_t[2]->Draw("AP");
        data_t[3]->Draw("P");
        data_t[4]->Draw("P");
        data_comb_t->Draw("P");

        c_data->BuildLegend();


        printit("here9",NULL);
        double dutta_C_P[4] = {.35,.7,.97,1.8};
        double dutta_C_T[4] = {.61,.60,.57,.58};        
        double dutta_C_T_err[4] = {0.0,0.0,0.0,0.0};
        double dutta_C_P_err[4] = {0.0,0.0,0.0,0.0};
        for(int i = 0; i < 4; i++) {dutta_C_T_err[i] = dutta_C_T[i]*.05;}
        TGraphErrors* dutta_C = new TGraphErrors(4,dutta_C_P,dutta_C_T, dutta_C_P_err, dutta_C_T_err);
        dutta_C->SetMarkerColor(kBlack);
        dutta_C->SetLineColor(kBlack);
        dutta_C->SetMarkerSize(2);
        dutta_C->SetMarkerStyle(33);
        dutta_C->SetTitle("Dutta 03");
        

        TCanvas* c_combined;
        c_combined = new TCanvas("Combined", "Combined", 800, 600);
        data_comb_t->SetLineColor(kBlue);
        data_comb_t->SetMarkerStyle(kFullCircle);
        data_comb_t->SetMarkerColor(kBlue);
        data_comb_t->SetMarkerSize(2);
        data_comb_t->SetTitle("CLAS Data");
        data_comb_t->Draw("AP");
        dutta_C->Draw("P");

        c_combined->BuildLegend();

        //TFile *final = TFile::Open("T_C12_sectors.root", "RECREATE");
        //c_data->Write("data");
        //c_susa->Write("SuSA");
        //final->Close();    
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

        if(protons == 0.0 || (neutrons + protons) == 0.0) return 0;
        else return protons/(neutrons + protons);

}

double get_MEC_corr(TString file, int sector, bool incl) {   
        TFile *input = TFile::Open( TString( file ) );

        TH1D* mom_Int[4];
        TH1D* total;

        if( incl == true ) {
                for(int i = 0; i < 4; i++) {
                        mom_Int[i] = (TH1D*)input->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", i+1, (sector) ));
                }
                
        }

        if( incl == false ) {
                for(int i = 0; i < 4; i++) {
                        mom_Int[i] = (TH1D*)input->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", i+1, sector));
                }
        }

        total = (TH1D*) mom_Int[0]->Clone();
        total->Add(mom_Int[1]); total->Add(mom_Int[2]); total->Add(mom_Int[3]);

        double mec_int = mom_Int[1]->Integral();
        double total_int = total->Integral();
        if (mec_int == 0.0 || total_int == 0.0) return 0;

        return mec_int/total_int;
}

TH1D* SumElecSectorsAndInts(TString file, int sector, bool isData) {
        TFile *input = TFile::Open( TString( file ) );

        TH1D* el_mom;
        TH1D* el_mom_Int[6];
        TH1D* el_mom_d;

        if ( isData == false ) { 
                        for (int i = 0; i < 4; i++) { // for all the interactions

                                // extract the histrograms
                                el_mom_Int[i] = (TH1D*)input->Get( TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", i+1, (sector) ));
                                if( i == 0 ) el_mom = (TH1D*)( el_mom_Int[i]->Clone() );
                                else el_mom->Add(el_mom_Int[i]);
                        }
        }

        if ( isData == true ) {
                el_mom_d = (TH1D*)input->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", (sector) ));
                el_mom = (TH1D*) ( el_mom_d->Clone() );
        }

        el_mom->Rebin( 40 );
        return el_mom;
}

TH1D* SumProtSectorsAndInts(TString file, int sector, bool isData) {
        TFile *input = TFile::Open( TString( file ) );

        TH1D* h1_prot_momentum;
        TH1D* h1_prot_momentum_d;
        TH1D* h1_prot_mom_InteractionBreakDown_inSector[4];

        if ( isData == false ) {
                for (int i = 0; i < 4; i++) { // for all the interactions

                        // extract the histrograms
                        h1_prot_mom_InteractionBreakDown_inSector[i] = (TH1D*)input->Get( TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", i+1, sector) );
                        if(i == 0) h1_prot_momentum = (TH1D*)( h1_prot_mom_InteractionBreakDown_inSector[i]->Clone() );
                        else h1_prot_momentum->Add( h1_prot_mom_InteractionBreakDown_inSector[i] );
                }
        }

        if ( isData == true ) {
               
                h1_prot_momentum_d = (TH1D*)input->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", sector));
                h1_prot_momentum = (TH1D*)( h1_prot_momentum_d->Clone() );
        }

        h1_prot_momentum->Rebin( 40 );
        return h1_prot_momentum;
}

TH1D* AcceptanceCorrect(TH1D* hist, TH1D* susa_true, TH1D* susa_truereco, TH1D* susa_truereco_rad, bool make_plots, bool data, bool inclusive) {

        //Make sure we have a non empty histogram
        if(hist->GetEntries() == 0.0) return hist;
        
        TH1D::SetDefaultSumw2();

        TH1D* OverallClone = (TH1D*)hist->Clone();

        TH1D* susa_correction = (TH1D*)susa_true->Clone();
        susa_correction->Divide(susa_truereco);

        TH1D* Average = (TH1D*)(susa_correction->Clone());

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
		tPlotCanvas->BuildLegend();
		tPlotCanvas->SaveAs("C12_true_vs_truereco.pdf");


        	TString trCanvasName = TString::Format("radrec_vs_noradreco_%s",hist->GetTitle());
        	TCanvas* trPlotCanvas = new TCanvas(trCanvasName,trCanvasName,205,34,1024,768);
        	susa_truereco->GetYaxis()->SetTitle("Scaled number of events");
		susa_truereco->GetXaxis()->SetTitle("Momentum (GeV)");
        	susa_truereco->Draw("e hist");
        	susa_truereco->SetLineColor(kBlack);
        	susa_truereco_rad->SetLineColor(kGreen);
		susa_truereco_rad->SetTitle(TString::Format("Reco Rad %s",hist->GetTitle()));
        	susa_truereco_rad->Draw("e hist same");
		trPlotCanvas->BuildLegend();
        	trPlotCanvas->SaveAs("C12_truerecorad_vs_truereco.pdf");
	}
	
        int NBins = OverallClone->GetXaxis()->GetNbins();
        double AccCorrTolerance = 10;

        for (int WhichBin = 0; WhichBin < NBins; WhichBin++) {
                double AccCorr = 0.;
                double RadCorr = 0.;

                double NewBinContent = 0.;
                double NewBinError = 0.;

                AccCorr = Average->GetBinContent(WhichBin + 1);
                RadCorr = RadCorrection->GetBinContent(WhichBin + 1);

                if(RadCorr <= 0.) RadCorr = 1.;
		if(AccCorr <= 0.) AccCorr = 1.;
                if(!data) RadCorr = 1.;
                AccCorr = 1.;
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
	  PlotCanvas->SaveAs("C12_Acceptance_Ratios.pdf");

	  TString RadCanvasName = TString::Format("RadCorrCanvas_%s",hist->GetTitle());
	  TCanvas* RadPlotCanvas = new TCanvas(RadCanvasName,RadCanvasName,205,34,1024,768);
	  RadCorrection->GetYaxis()->SetTitle("Radiative Correction");
	  RadCorrection->GetXaxis()->SetTitle("Momentum (GeV)");
	  RadCorrection->SetTitle(TString::Format("%s", hist->GetTitle()));
	  RadCorrection->Draw("e hist");
	  RadPlotCanvas->SaveAs("C12_Rad_Ratios.pdf");
	}

        return OverallClone;
}

double get_ratio_error(double num, double denom, double num_err, double denom_err) {
        return (num/denom)*sqrt(pow(num_err/num,2) + pow(denom_err/denom,2));
}

void printit(std::string s, double x) {
        std::cout << s << " = " << x << "\n";
}

double diff_squared(double x, double y) {
        if (isnan(x) || isnan(y) || x == 0.0 || y == 0.0) return 0.;
        //std::cout << (x-y)*(x-y) << "\n";
        return (x - y)*(x - y); 
}






