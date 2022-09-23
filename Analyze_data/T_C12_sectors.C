#include "myFunctions.cpp"
#include "noah_constants_C12.h"


double weighted_average(TH1D* h1) {
        double num_sum = 0.0;
        double den_sum = 0.0;
        for (int i = 0; i < h1->GetNbinsX(); i++) {
                if (h1->GetBinContent(i) == 0) continue;
                num_sum += h1->GetBinCenter(i)*h1->GetBinContent(i);
                den_sum += h1->GetBinContent(i);
        }

        if(isnan(num_sum/den_sum)) return 0.;
        //std::cout << "Weighted average = " << num_sum/den_sum << "\n";
        return num_sum/den_sum;
}

void T_C12_sectors(bool make_plots = false) {
        gStyle->SetOptStat(0);

        data_1161[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/C12/Excl_Range2_Data__C12_1.161000.root";
        data_1161[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/C12/Incl_Range2_Data__C12_1.161000.root";
        data_1161[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/C12/Excl_Range3_Data__C12_1.161000.root";
        data_1161[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/C12/Incl_Range3_Data__C12_1.161000.root";
        data_2261[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/C12/Excl_Range1_Data__C12_2.261000.root";
        data_2261[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/C12/Incl_Range1_Data__C12_2.261000.root";
        data_2261[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/C12/Excl_Range2_Data__C12_2.261000.root";
        data_2261[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/C12/Incl_Range2_Data__C12_2.261000.root";
        data_2261[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/C12/Excl_Range3_Data__C12_2.261000.root";
        data_2261[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/C12/Incl_Range3_Data__C12_2.261000.root";
        data_4461[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/C12/Excl_Range1_Data__C12_4.461000.root";
        data_4461[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample/C12/Incl_Range1_Data__C12_4.461000.root";

        susa_1161[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Excl_Range2_Genie_1_C12_1.161000.root";
        susa_1161[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Incl_Range2_Genie_1_C12_1.161000.root";
        susa_1161[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Excl_Range3_Genie_1_C12_1.161000.root";
        susa_1161[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Incl_Range3_Genie_1_C12_1.161000.root";
        susa_2261[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Excl_Range1_Genie_1_C12_2.261000.root";
        susa_2261[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Incl_Range1_Genie_1_C12_2.261000.root";
        susa_2261[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Excl_Range2_Genie_1_C12_2.261000.root";
        susa_2261[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Incl_Range2_Genie_1_C12_2.261000.root";
        susa_2261[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Excl_Range3_Genie_1_C12_2.261000.root";
        susa_2261[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Incl_Range3_Genie_1_C12_2.261000.root";
        susa_4461[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Excl_Range1_Genie_1_C12_4.461000.root";
        susa_4461[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/SuSAv2/Incl_Range1_Genie_1_C12_4.461000.root";

        g_1161[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Excl_Range2_Genie_2_C12_1.161000.root";
        g_1161[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Incl_Range2_Genie_2_C12_1.161000.root";
        g_1161[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Excl_Range3_Genie_2_C12_1.161000.root";
        g_1161[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Incl_Range3_Genie_2_C12_1.161000.root";
        g_2261[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Excl_Range1_Genie_2_C12_2.261000.root";
        g_2261[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Incl_Range1_Genie_2_C12_2.261000.root";
        g_2261[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Excl_Range2_Genie_2_C12_2.261000.root";
        g_2261[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Incl_Range2_Genie_2_C12_2.261000.root";
        g_2261[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Excl_Range3_Genie_2_C12_2.261000.root";
        g_2261[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Incl_Range3_Genie_2_C12_2.261000.root";
        g_4461[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Excl_Range1_Genie_2_C12_4.461000.root";
        g_4461[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Corr_Sectors/G18/Incl_Range1_Genie_2_C12_4.461000.root";

        susa_1161_truereco[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Excl_Range2_Genie_1_C12_1.161000.root";
        susa_1161_truereco[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Incl_Range2_Genie_1_C12_1.161000.root";
        susa_1161_truereco[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Excl_Range3_Genie_1_C12_1.161000.root";
        susa_1161_truereco[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Incl_Range3_Genie_1_C12_1.161000.root";
        susa_2261_truereco[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Excl_Range1_Genie_1_C12_2.261000.root";
        susa_2261_truereco[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Incl_Range1_Genie_1_C12_2.261000.root";
        susa_2261_truereco[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Excl_Range2_Genie_1_C12_2.261000.root";
        susa_2261_truereco[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Incl_Range2_Genie_1_C12_2.261000.root";
        susa_2261_truereco[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Excl_Range3_Genie_1_C12_2.261000.root";
        susa_2261_truereco[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Incl_Range3_Genie_1_C12_2.261000.root";
        susa_4461_truereco[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Excl_Range1_Genie_1_C12_4.461000.root";
        susa_4461_truereco[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/SuSA/Incl_Range1_Genie_1_C12_4.461000.root";

        susa_1161_true[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Excl_Range2_Genie_1_C12_1.161000.root";
        susa_1161_true[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Incl_Range2_Genie_1_C12_1.161000.root";
        susa_1161_true[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Excl_Range3_Genie_1_C12_1.161000.root";
        susa_1161_true[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Incl_Range3_Genie_1_C12_1.161000.root";
        susa_2261_true[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Excl_Range1_Genie_1_C12_2.261000.root";
        susa_2261_true[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Incl_Range1_Genie_1_C12_2.261000.root";
        susa_2261_true[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Excl_Range2_Genie_1_C12_2.261000.root";
        susa_2261_true[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Incl_Range2_Genie_1_C12_2.261000.root";
        susa_2261_true[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Excl_Range3_Genie_1_C12_2.261000.root";
        susa_2261_true[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Incl_Range3_Genie_1_C12_2.261000.root";
        susa_4461_true[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Excl_Range1_Genie_1_C12_4.461000.root";
        susa_4461_true[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/SuSA/Incl_Range1_Genie_1_C12_4.461000.root";

        g_1161_truereco[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Excl_Range2_Genie_2_C12_1.161000.root";
        g_1161_truereco[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Incl_Range2_Genie_2_C12_1.161000.root";
        g_1161_truereco[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Excl_Range3_Genie_2_C12_1.161000.root";
        g_1161_truereco[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Incl_Range3_Genie_2_C12_1.161000.root";
        g_2261_truereco[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Excl_Range1_Genie_2_C12_2.261000.root";
        g_2261_truereco[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Incl_Range1_Genie_2_C12_2.261000.root";
        g_2261_truereco[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Excl_Range2_Genie_2_C12_2.261000.root";
        g_2261_truereco[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Incl_Range2_Genie_2_C12_2.261000.root";
        g_2261_truereco[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Excl_Range3_Genie_2_C12_2.261000.root";
        g_2261_truereco[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Incl_Range3_Genie_2_C12_2.261000.root";
        g_4461_truereco[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Excl_Range1_Genie_2_C12_4.461000.root";
        g_4461_truereco[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth_Reco/G18/Incl_Range1_Genie_2_C12_4.461000.root";

        g_1161_true[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Excl_Range2_Genie_2_C12_1.161000.root";
        g_1161_true[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Incl_Range2_Genie_2_C12_1.161000.root";
        g_1161_true[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Excl_Range3_Genie_2_C12_1.161000.root";
        g_1161_true[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Incl_Range3_Genie_2_C12_1.161000.root";
        g_2261_true[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Excl_Range1_Genie_2_C12_2.261000.root";
        g_2261_true[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Incl_Range1_Genie_2_C12_2.261000.root";
        g_2261_true[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Excl_Range2_Genie_2_C12_2.261000.root";
        g_2261_true[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Incl_Range2_Genie_2_C12_2.261000.root";
        g_2261_true[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Excl_Range3_Genie_2_C12_2.261000.root";
        g_2261_true[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Incl_Range3_Genie_2_C12_2.261000.root";
        g_4461_true[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Excl_Range1_Genie_2_C12_4.461000.root";
        g_4461_true[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Truth/G18/Incl_Range1_Genie_2_C12_4.461000.root";

        susa_1161_truereco_rad[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Excl_Range2_Genie_3_C12_1.161000.root";
        susa_1161_truereco_rad[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Incl_Range2_Genie_3_C12_1.161000.root";
        susa_1161_truereco_rad[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Excl_Range3_Genie_3_C12_1.161000.root";
        susa_1161_truereco_rad[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Incl_Range3_Genie_3_C12_1.161000.root";
        susa_2261_truereco_rad[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Excl_Range1_Genie_3_C12_2.261000.root";
        susa_2261_truereco_rad[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Incl_Range1_Genie_3_C12_2.261000.root";
        susa_2261_truereco_rad[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Excl_Range2_Genie_3_C12_2.261000.root";
        susa_2261_truereco_rad[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Incl_Range2_Genie_3_C12_2.261000.root";
        susa_2261_truereco_rad[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Excl_Range3_Genie_3_C12_2.261000.root";
        susa_2261_truereco_rad[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Incl_Range3_Genie_3_C12_2.261000.root";
        susa_4461_truereco_rad[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Excl_Range1_Genie_3_C12_4.461000.root";
        susa_4461_truereco_rad[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/Corr_Sectors/Rad_Truth_Reco/Incl_Range1_Genie_3_C12_4.461000.root";

        std::string first_en[2][2] = {{"1.161 Excl Range 2","1.161 Incl Range 2"},{"1.161 Excl Range 3","1.161 Incl Range 3"}};
        std::string second_en[3][2] = {{"2.261 Excl Range 1", "2.261 Incl Range 1"},{"2.261 Excl Range 2", "2.261 Incl Range 2"},{ "2.261 Excl Range 3", "2.261 Incl Range 3"}};
        std::string third_en[1][2] = {{"4.461 Excl Range 1","4.461 Incl Range 1"}}; 

        int sectors[3] = {2,3,4};

        int num_1161_sec = 4;
        int num_2261_sec = 3;
        int num_4461_sec = 3;

// --------------------- Getting radiative correction histograms from MC ----------------
        TH1D* SuSA_1161_true_reco_rad[2][2][6];
        TH1D* SuSA_2261_true_reco_rad[3][2][6];
        TH1D* SuSA_4461_true_reco_rad[1][2][6];

        for(int s : sectors) {
                for(int p = 0; p < 2; p++) {
                        if(p == 1) s = (s+3)%6;

                        for(int r = 0; r < 2; r++) {
                                if(p==0) { // Exclusive
                                        SuSA_1161_true_reco_rad[r][p][s] = (TH1D*)SumProtSectorsAndInts(susa_1161_truereco_rad[r][p], s, false);
                                }
                                if(p==1) { // Inclusive
                                        SuSA_1161_true_reco_rad[r][p][s] = (TH1D*)SumElecSectorsAndInts(susa_1161_truereco_rad[r][p], s, false);
                                }
                                UniversalE4vFunction(SuSA_1161_true_reco_rad[r][p][s], FSIModelsToLabels["SuSav2_RadCorr_LFGM_Truth_WithFidAcc_UpdatedSchwinger"], "12C", "1_161", TString::Format("susa_1161_mom_truereco_rad"));
                
                        }

                        for(int r = 0; r < 3; r++) {
                                if(p==0) { // Exclusive
                                        SuSA_2261_true_reco_rad[r][p][s] = (TH1D*)SumProtSectorsAndInts(susa_2261_truereco_rad[r][p], s, false);
                                }
                                if(p==1) { // Inclusive
                                        SuSA_2261_true_reco_rad[r][p][s] = (TH1D*)SumElecSectorsAndInts(susa_2261_truereco_rad[r][p], s, false);
                                }
                                UniversalE4vFunction(SuSA_2261_true_reco_rad[r][p][s],  FSIModelsToLabels["SuSav2_RadCorr_LFGM_Truth_WithFidAcc_UpdatedSchwinger"], "12C", "2_261", TString::Format("susa_2261_mom_truereco_rad"));
                        }
                
                        for(int r = 0; r < 1; r++) {
                                if(p==0) { // Exclusive
                                        SuSA_4461_true_reco_rad[r][p][s] = (TH1D*)SumProtSectorsAndInts(susa_4461_truereco_rad[r][p], s, false);
                                }
                                if(p==1) { // Inclusive
                                        SuSA_4461_true_reco_rad[r][p][s] = (TH1D*)SumElecSectorsAndInts(susa_4461_truereco_rad[r][p], s, false);
                                }
                                UniversalE4vFunction(SuSA_4461_true_reco_rad[r][p][s],  FSIModelsToLabels["SuSav2_RadCorr_LFGM_Truth_WithFidAcc_UpdatedSchwinger"], "12C", "4_461", TString::Format("susa_4461_mom_truereco_rad"));
                        }
                }
        }

// --------------------- Getting acceptance correction histograms from MC ---------------
        
        //[NRanges][Exclusive = 0, Inclsuive = 1] 
        TH1D* SuSA_1161_true[2][2][6];
        TH1D* SuSA_1161_true_reco[2][2][6];
        TH1D* G_1161_true[2][2][6];
        TH1D* G_1161_true_reco[2][2][6];

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

                        // 1.161 GeV
                        for(int r = 0; r < 2; r++) {
                                if(p==0) { // Exclusive
                                        SuSA_1161_true[r][p][s] = (TH1D*)SumProtSectorsAndInts(susa_1161_true[r][p], s, false);
                                        SuSA_1161_true_reco[r][p][s] = (TH1D*)SumProtSectorsAndInts(susa_1161_truereco[r][p], s, false);
                                        G_1161_true[r][p][s] = (TH1D*)SumProtSectorsAndInts(g_1161_true[r][p], s, false);
                                        G_1161_true_reco[r][p][s] = (TH1D*)SumProtSectorsAndInts(g_1161_truereco[r][p], s, false);
                                }
                                if(p==1) { // Inclusive
                                        SuSA_1161_true[r][p][s] = (TH1D*)SumElecSectorsAndInts(susa_1161_true[r][p], s, false);
                                        SuSA_1161_true_reco[r][p][s] = (TH1D*)SumElecSectorsAndInts(susa_1161_truereco[r][p], s, false);
                                        G_1161_true[r][p][s] = (TH1D*)SumElecSectorsAndInts(g_1161_true[r][p], s, false);
                                        G_1161_true_reco[r][p][s] = (TH1D*)SumElecSectorsAndInts(g_1161_truereco[r][p], s, false);
                                }
                                UniversalE4vFunction(SuSA_1161_true[r][p][s],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "12C","1_161", TString::Format("susa_1161_mom_true_%i%i%i",r,p,s));
                                UniversalE4vFunction(G_1161_true[r][p][s],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "12C","1_161", TString::Format("g_1161_mom_true_%i%i%i",r,p,s));
                                UniversalE4vFunction(SuSA_1161_true_reco[r][p][s],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","1_161", TString::Format("susa_1161_mom_truereco_%i%i%i",r,p,s));
                                UniversalE4vFunction(G_1161_true_reco[r][p][s],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","1_161", TString::Format("g_1161_mom_truereco_%i%i%i",r,p,s));
                        }

                        // 2.261 GeV
                        for(int r = 0; r < 3; r++) {
                                if(p==0) { // Exclusive
                                        SuSA_2261_true[r][p][s] = (TH1D*)SumProtSectorsAndInts(susa_2261_true[r][p], s, false);
                                        SuSA_2261_true_reco[r][p][s] = (TH1D*)SumProtSectorsAndInts(susa_2261_truereco[r][p], s, false);
                                        G_2261_true[r][p][s] = (TH1D*)SumProtSectorsAndInts(g_2261_true[r][p], s, false);
                                        G_2261_true_reco[r][p][s] = (TH1D*)SumProtSectorsAndInts(g_2261_truereco[r][p], s, false);
                                }
                                if(p==1) { // Inclusive
                                        SuSA_2261_true[r][p][s] = (TH1D*)SumElecSectorsAndInts(susa_2261_true[r][p], s, false);
                                        SuSA_2261_true_reco[r][p][s] = (TH1D*)SumElecSectorsAndInts(susa_2261_truereco[r][p], s, false);
                                        G_2261_true[r][p][s] = (TH1D*)SumElecSectorsAndInts(g_2261_true[r][p], s, false);
                                        G_2261_true_reco[r][p][s] = (TH1D*)SumElecSectorsAndInts(g_2261_truereco[r][p], s, false);
                                }
                                UniversalE4vFunction(SuSA_2261_true[r][p][s],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "12C","2_261", TString::Format("susa_2261_mom_%i%i%i",r,p,s));
                                UniversalE4vFunction(G_2261_true[r][p][s],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "12C","2_261", TString::Format("g_2261_mom_%i%i%i",r,p,s));
                                UniversalE4vFunction(SuSA_2261_true_reco[r][p][s],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","2_261", TString::Format("susa_2261_mom_truereco_%i%i%i",r,p,s));
                                UniversalE4vFunction(G_2261_true_reco[r][p][s],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","2_261", TString::Format("g_2261_mom_truereco_%i%i%i",r,p,s));
                        }   
        
                        // 4.461 GeV
                        for(int r = 0; r < 1; r++) {
                                if(p==0) { // Exclusive
                                        SuSA_4461_true[r][p][s] = (TH1D*)SumProtSectorsAndInts(susa_4461_true[r][p], s, false);
                                        SuSA_4461_true_reco[r][p][s] = (TH1D*)SumProtSectorsAndInts(susa_4461_truereco[r][p], s, false);
                                        G_4461_true[r][p][s] = (TH1D*)SumProtSectorsAndInts(g_4461_true[r][p], s, false);
                                        G_4461_true_reco[r][p][s] = (TH1D*)SumProtSectorsAndInts(g_4461_truereco[r][p], s, false);
                                }
                                if(p==1) { // Inclusive
                                        SuSA_4461_true[r][p][s] = (TH1D*)SumElecSectorsAndInts(susa_4461_true[r][p], s, false);
                                        SuSA_4461_true_reco[r][p][s] = (TH1D*)SumElecSectorsAndInts(susa_4461_truereco[r][p], s, false);
                                        G_4461_true[r][p][s] = (TH1D*)SumElecSectorsAndInts(g_4461_true[r][p], s, false);
                                        G_4461_true_reco[r][p][s] = (TH1D*)SumElecSectorsAndInts(g_4461_truereco[r][p], s, false);
                                }
                                UniversalE4vFunction(SuSA_4461_true[r][p][s],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "12C","4_461", TString::Format("susa_4461_mom_%i%i%i",r,p,s));
                                UniversalE4vFunction(G_4461_true[r][p][s],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "12C","4_461", TString::Format("g_4461_mom_%i%i%i",r,p,s));
                                UniversalE4vFunction(SuSA_4461_true_reco[r][p][s],  FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","4_461", TString::Format("susa_4461_mom_truereco_%i%i%i",r,p,s));
                                UniversalE4vFunction(G_4461_true_reco[r][p][s],  FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","4_461", TString::Format("g_4461_mom_truereco_%i%i%i",r,p,s));
                        }
                }
        }


// --------------------- Getting MC exclusive and inclusive measurements and mec/neutron corrections ----------------

        //[NRanges][Exclusive = 0, Inclsuive = 1]     
        
        // Get the exclusive and inclusive SuSA predictions as well as MEC corrections
        // neutron corrections to apply to data from G18
        // neutron corrections to apply to MEC from SuSA

        TH1D* SuSA_1161[2][2][6];
        TH1D* G_1161[2][2][6];
        double mec_corr_1161[2][2][6];
        double mec_corr_G_1161[2][2][6];
        double neutron_corr_1161_G18[2][2];
        double neutron_corr_1161_susa[2][2];

        TH1D* SuSA_2261[3][2][6];
        TH1D* G_2261[3][2][6];
        double mec_corr_2261[3][2][6];
        double mec_corr_G_2261[3][2][6];
        double neutron_corr_2261_G18[3][2];
        double neutron_corr_2261_susa[3][2];

        TH1D* SuSA_4461[1][2][6];
        TH1D* G_4461[1][2][6];
        double mec_corr_4461[1][2][6];
        double mec_corr_G_4461[1][2][6];
        double neutron_corr_4461_G18[1][2];
        double neutron_corr_4461_susa[1][2];


        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 2; r++) {
                        //std::cout << "Neutron and MEC corrections for " << first_en[r][p] << "\n";
                        if( p == 0 ) {
                                neutron_corr_1161_susa[r][p] = get_Neutron_corr(susa_1161[r][p], false);
                                neutron_corr_1161_G18[r][p] = get_Neutron_corr(g_1161[r][p], false);
                        }
                        if( p == 1 ) {
                                neutron_corr_1161_susa[r][p] = get_Neutron_corr(susa_1161[r][p], true);
                                neutron_corr_1161_G18[r][p] = get_Neutron_corr(g_1161[r][p], true); 
                        }
                        std::cout << "G18 N: " << neutron_corr_1161_G18[r][p] << "\n";
                        std::cout << "SuSA N: " <<  neutron_corr_1161_susa[r][p] << "\n";
                        for(int s: sectors) {
                                if(p==0) { // Exclusive
                                        SuSA_1161[r][p][s] = (TH1D*)SumProtSectorsAndInts(susa_1161[r][p], s, false);
                                        G_1161[r][p][s] = (TH1D*)SumProtSectorsAndInts(g_1161[r][p], s, false);
                                        mec_corr_1161[r][p][s] = get_MEC_corr(susa_1161[r][p], s, false);
                                        mec_corr_G_1161[r][p][s] = get_MEC_corr(g_1161[r][p], s, false);
                                }
                                if(p==1) { // Inclusive
                                        s = (s+3)%6;
                                        SuSA_1161[r][p][s] = (TH1D*)SumElecSectorsAndInts(susa_1161[r][p], s, false);
                                        G_1161[r][p][s] = (TH1D*)SumElecSectorsAndInts(g_1161[r][p], s, false);
                                        mec_corr_1161[r][p][s] = get_MEC_corr(susa_1161[r][p], s, true);
                                        mec_corr_G_1161[r][p][s] = get_MEC_corr(g_1161[r][p], s, true);
                                }
                                std::cout << "sector " << s << "\n";
                                std::cout << "MEC: " << mec_corr_1161[r][p][s] << "\n";
                                UniversalE4vFunction(SuSA_1161[r][p][s], FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","1_161", TString::Format("susa_1161_mom_reco_%i%i%i",r,p,s));
                                UniversalE4vFunction(G_1161[r][p][s], FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","1_161", TString::Format("g_1161_mom_reco_%i%i%i",r,p,s));
                        }
                }

                for(int r = 0; r < 3; r++) {
                        std::cout<< "Neutron and MEC corrections for " << second_en[r][p] << "\n"; 
                        if(p == 0) {
                                neutron_corr_2261_susa[r][p] = get_Neutron_corr(susa_2261[r][p], false);
                                neutron_corr_2261_G18[r][p] = get_Neutron_corr(g_2261[r][p], false);
                        }
                        if(p == 1) {
                                neutron_corr_2261_susa[r][p] = get_Neutron_corr(susa_2261[r][p], true);
                                neutron_corr_2261_G18[r][p] = get_Neutron_corr(g_2261[r][p], true); 
                        }
                        std::cout << "G18 N: " << neutron_corr_2261_G18[r][p] << "\n";
                        std::cout << "SuSA N: " << neutron_corr_2261_susa[r][p] << "\n";
                        for(int s : sectors) {
                                if(p==0) { // Exclusive
                                        SuSA_2261[r][p][s] = (TH1D*)SumProtSectorsAndInts(susa_2261[r][p], s, false);
                                        G_2261[r][p][s] = (TH1D*)SumProtSectorsAndInts(g_2261[r][p], s, false);
                                        mec_corr_2261[r][p][s] = get_MEC_corr(susa_2261[r][p], s, false);
                                        mec_corr_G_2261[r][p][s] = get_MEC_corr(g_2261[r][p], s, false);
                                        
                                }
                                if(p==1) { // Inclusive
                                        s = (s+3)%6;
                                        SuSA_2261[r][p][s] = (TH1D*)SumElecSectorsAndInts(susa_2261[r][p], s, false);
                                        G_2261[r][p][s] = (TH1D*)SumElecSectorsAndInts(g_2261[r][p], s, false);
                                        mec_corr_2261[r][p][s] = get_MEC_corr(susa_2261[r][p], s, true);
                                        mec_corr_G_2261[r][p][s] = get_MEC_corr(g_2261[r][p], s, true);
                                        }
                                std::cout << "sector " << s << "\n";
                                std::cout << "SuSA MEC: " << mec_corr_2261[r][p][s] << "\n";
                                std::cout << "G18 MEC:  " << mec_corr_G_2261[r][p][s] << "\n";
                                UniversalE4vFunction(SuSA_2261[r][p][s], FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","2_261", TString::Format("susa_2261_mom_reco_%i%i%i",r,p,s));
                                UniversalE4vFunction(G_2261[r][p][s], FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","2_261", TString::Format("g_2261_mom_reco_%i%i%i",r,p,s));
                        }
                }
        

                // 4.461 GeV
                for(int r = 0; r < 1; r++) {
                        std::cout << "Neutron and MEC corrections for "<< third_en[r][p] << "\n";
                        if( p == 0 ) {
                                neutron_corr_4461_susa[r][p] = get_Neutron_corr(susa_4461[r][p], false);
                                neutron_corr_4461_G18[r][p] = get_Neutron_corr(g_4461[r][p], false);
                        }
                        if( p == 1 ) {
                                neutron_corr_4461_susa[r][p] = get_Neutron_corr(susa_4461[r][p], true);
                                neutron_corr_4461_G18[r][p] = get_Neutron_corr(g_4461[r][p], true); 
                        }
                       std::cout << "G18 N:  " << neutron_corr_4461_G18[r][p] << "\n";
                       std::cout << "SuSA N: " << neutron_corr_4461_susa[r][p] << "\n";
                        for(int s : sectors) {
                                if(p==0) { // Exclusive
                                        SuSA_4461[r][p][s] = (TH1D*)SumProtSectorsAndInts(susa_4461[r][p], s, false);
                                        G_4461[r][p][s] = (TH1D*)SumProtSectorsAndInts(g_4461[r][p], s, false);
                                        mec_corr_4461[r][p][s] = get_MEC_corr(susa_4461[r][p], s, false); 
                                        mec_corr_G_4461[r][p][s] = get_MEC_corr(g_4461[r][p], s, false);  
                                }
                                if(p==1) { // Inclusive

                                        s = (s+3)%6;
                                        SuSA_4461[r][p][s] = (TH1D*)SumElecSectorsAndInts(susa_4461[r][p], s, false);
                                        G_4461[r][p][s] = (TH1D*)SumElecSectorsAndInts(g_4461[r][p], s, false);
                                        mec_corr_4461[r][p][s] = get_MEC_corr(susa_4461[r][p], s, true); 
                                        mec_corr_G_4461[r][p][s] = get_MEC_corr(g_4461[r][p], s, true);   
                                }
                                std::cout << "sector " << s << "\n";
                                std::cout << "SuSA MEC: " << mec_corr_4461[r][p][s] << "\n";
                                std::cout << "G18 MEC:  " << mec_corr_G_4461[r][p][s] << "\n";
                                UniversalE4vFunction(SuSA_4461[r][p][s], FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","4_461", TString::Format("susa_4461_mom_reco_%i%i%i",r,p,s));
                                UniversalE4vFunction(G_4461[r][p][s], FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C","4_461", TString::Format("g_4461_mom_reco_%i%i%i",r,p,s));                                          
                        }
                }
        }
        std::cout << "\n";
        

// --------------------- Getting Data exclusive and inclusive measurements ----------------

        // Here we will also scale the data
        TH1D* Data_1161[2][2][6];
        TH1D* Data_2261[3][2][6];
        TH1D* Data_4461[1][2][6];

        for(int p = 0; p < 2; p++) {
                for(int s : sectors) {
                        if(p == 0) { // Exclusive
                                Data_1161[0][p][s] = (TH1D*)SumProtSectorsAndInts(data_1161[0][p], s, true);
                                Data_1161[1][p][s] = (TH1D*)SumProtSectorsAndInts(data_1161[1][p], s, true);
                                Data_2261[0][p][s] = (TH1D*)SumProtSectorsAndInts(data_2261[0][p], s, true);
                                Data_2261[1][p][s] = (TH1D*)SumProtSectorsAndInts(data_2261[1][p], s, true);
                                Data_2261[2][p][s] = (TH1D*)SumProtSectorsAndInts(data_2261[2][p], s, true);
                                Data_4461[0][p][s] = (TH1D*)SumProtSectorsAndInts(data_4461[0][p], s, true);
                        }
                        if(p == 1) { // Inclusive
                                s = (s+3)%6;
                                Data_1161[0][p][s] = (TH1D*)SumElecSectorsAndInts(data_1161[0][p], s, true);
                                Data_1161[1][p][s] = (TH1D*)SumElecSectorsAndInts(data_1161[1][p], s, true);
                                Data_2261[0][p][s] = (TH1D*)SumElecSectorsAndInts(data_2261[0][p], s, true);
                                Data_2261[1][p][s] = (TH1D*)SumElecSectorsAndInts(data_2261[1][p], s, true);
                                Data_2261[2][p][s] = (TH1D*)SumElecSectorsAndInts(data_2261[2][p], s, true);
                                Data_4461[0][p][s] = (TH1D*)SumElecSectorsAndInts(data_4461[0][p], s, true);
                        }
                        UniversalE4vFunction(Data_1161[0][p][s], "Pinned Data", "12C", "1_161", TString::Format("data %s %i",first_en[0][p].c_str(),s));
                        UniversalE4vFunction(Data_1161[1][p][s], "Pinned Data", "12C", "1_161", TString::Format("data %s %i",first_en[1][p].c_str(),s));
                        UniversalE4vFunction(Data_2261[0][p][s], "Pinned Data", "12C", "2_261", TString::Format("data %s %i",second_en[0][p].c_str(),s));
                        UniversalE4vFunction(Data_2261[1][p][s], "Pinned Data", "12C", "2_261", TString::Format("data %s %i",second_en[1][p].c_str(),s));
                        UniversalE4vFunction(Data_2261[2][p][s], "Pinned Data", "12C", "2_261", TString::Format("data %s %i",second_en[2][p].c_str(),s));
                        UniversalE4vFunction(Data_4461[0][p][s], "Pinned Data", "12C", "4_461", TString::Format("data %s %i",third_en[0][p].c_str(),s));
                }
        }

// ---------------- Acceptance correct all histograms ---------------------
        TCanvas *ca = new TCanvas("corrections can"," corrections can",800,800);
        if(make_plots) {
                
                ca->SaveAs("C12_true_vs_truereco.pdf(");
                ca->SaveAs("C12_truerecorad_vs_truereco.pdf(");
                ca->SaveAs("C12_Acceptance_Ratios.pdf(");
                ca->SaveAs("C12_Rad_Ratios.pdf(");
        }
        
        
        for(int p = 0; p < 2; p++) {
                for(int s : sectors) {
                        if(p == 1) s = (s+3)%6;

                        //1161
                        for(int r = 0; r < 2; r++) {
                                SuSA_1161[r][p][s]->SetTitle(TString::Format("SuSA %s Sector %i",first_en[r][p].c_str(),s));
                                G_1161[r][p][s]->SetTitle(TString::Format("G18 %s Sector %i",first_en[r][p].c_str(),s));

                                Data_1161[r][p][s] = (TH1D*)AcceptanceCorrect(Data_1161[r][p][s], SuSA_1161_true[r][p][s], SuSA_1161_true_reco[r][p][s], G_1161_true[r][p][s], G_1161_true_reco[r][p][s], SuSA_1161_true_reco_rad[r][p][s], false, "data");
                                SuSA_1161[r][p][s] = (TH1D*)AcceptanceCorrect(SuSA_1161[r][p][s], SuSA_1161_true[r][p][s], SuSA_1161_true_reco[r][p][s], G_1161_true[r][p][s], G_1161_true_reco[r][p][s], SuSA_1161_true_reco_rad[r][p][s], make_plots, "SuSA");
                                G_1161[r][p][s] = (TH1D*)AcceptanceCorrect(G_1161[r][p][s], SuSA_1161_true[r][p][s], SuSA_1161_true_reco[r][p][s], G_1161_true[r][p][s], G_1161_true_reco[r][p][s], SuSA_1161_true_reco_rad[r][p][s], make_plots, "G");
                        } 

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
                ca->SaveAs("C12_true_vs_truereco.pdf)");
                ca->SaveAs("C12_truerecorad_vs_truereco.pdf)");
                ca->SaveAs("C12_Acceptance_Ratios.pdf)");
                ca->SaveAs("C12_Rad_Ratios.pdf)");
        }


// ---------------- Get average proton momentum for data and MC ------------------------

        double data_avg_prot_mom_1161[2][6];
        double data_avg_prot_mom_2261[3][6];
        double data_avg_prot_mom_4461[1][6];

        double SuSA_avg_prot_mom_1161[2][6];
        double SuSA_avg_prot_mom_2261[3][6];
        double SuSA_avg_prot_mom_4461[1][6];

        double G_avg_prot_mom_1161[2][6];
        double G_avg_prot_mom_2261[3][6];
        double G_avg_prot_mom_4461[1][6];

        for(int s : sectors) {
                data_avg_prot_mom_1161[0][s] = weighted_average(Data_1161[0][0][s]); 
                data_avg_prot_mom_1161[1][s] = weighted_average(Data_1161[1][0][s]);
                data_avg_prot_mom_2261[0][s] = weighted_average(Data_2261[0][0][s]); 
                data_avg_prot_mom_2261[1][s] = weighted_average(Data_2261[1][0][s]); 
                data_avg_prot_mom_2261[2][s] = weighted_average(Data_2261[2][0][s]);
                data_avg_prot_mom_4461[0][s] = weighted_average(Data_4461[0][0][s]); 

                SuSA_avg_prot_mom_1161[0][s] = weighted_average(SuSA_1161[0][0][s]); 
                SuSA_avg_prot_mom_1161[1][s] = weighted_average(SuSA_1161[1][0][s]);
                SuSA_avg_prot_mom_2261[0][s] = weighted_average(SuSA_2261[0][0][s]); 
                SuSA_avg_prot_mom_2261[1][s] = weighted_average(SuSA_2261[1][0][s]); 
                SuSA_avg_prot_mom_2261[2][s] = weighted_average(SuSA_2261[2][0][s]);
                SuSA_avg_prot_mom_4461[0][s] = weighted_average(SuSA_4461[0][0][s]); 

                G_avg_prot_mom_1161[0][s] = weighted_average(G_1161[0][0][s]); 
                G_avg_prot_mom_1161[1][s] = weighted_average(G_1161[1][0][s]);
                G_avg_prot_mom_2261[0][s] = weighted_average(G_2261[0][0][s]); 
                G_avg_prot_mom_2261[1][s] = weighted_average(G_2261[1][0][s]); 
                G_avg_prot_mom_2261[2][s] = weighted_average(G_2261[2][0][s]);
                G_avg_prot_mom_4461[0][s] = weighted_average(G_4461[0][0][s]); 
        }

// -------------- Add systematic uncertainties ---------------------------

        
        for(int p = 0; p < 2; p++) {
                for(int s : sectors) {
                        if(p == 1) s = (s+3)%6;

                        //1161
                        for(int r = 0; r < 2; r++) {
                                ApplySystUnc(Data_1161[r][p][s],"1_161"); 
                                ApplySystUnc(SuSA_1161[r][p][s],"1_161");
                                ApplySystUnc(G_1161[r][p][s],"1_161");
                        }

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

                        //1161
                        for(int r = 0; r < 2; r++) {
                                Data_1161[r][p][s]->Scale((1. - mec_corr_1161[r][p][s]));
                                SuSA_1161[r][p][s]->Scale((1. - mec_corr_1161[r][p][s]));
                                G_1161[r][p][s]->Scale((1. - mec_corr_G_1161[r][p][s]));
                                if(p == 1) {    
                                        SuSA_1161[r][p][s]->Scale(neutron_corr_1161_susa[r][p]);
                                        Data_1161[r][p][s]->Scale(neutron_corr_1161_G18[r][p]);
                                        G_1161[r][p][s]->Scale(neutron_corr_1161_G18[r][p]);
                                }
                        }

                        //2261
                        for(int r = 0; r < 3; r++) {
                                Data_2261[r][p][s]->Scale((1. - mec_corr_2261[r][p][s]));
                                SuSA_2261[r][p][s]->Scale((1. - mec_corr_2261[r][p][s]));
                                G_2261[r][p][s]->Scale((1. - mec_corr_G_2261[r][p][s]));
                                if(p == 1) {    
                                        SuSA_2261[r][p][s]->Scale(neutron_corr_2261_susa[r][p]);
                                        Data_2261[r][p][s]->Scale(neutron_corr_2261_G18[r][p]);
                                        G_2261[r][p][s]->Scale(neutron_corr_2261_G18[r][p]);
                                }
                        }
                

                        //4461
                        for(int r = 0; r < 1; r++) {
                                Data_4461[r][p][s]->Scale((1. - mec_corr_4461[r][p][s]));
                                SuSA_4461[r][p][s]->Scale((1. - mec_corr_4461[r][p][s]));
                                G_4461[r][p][s]->Scale((1. - mec_corr_G_4461[r][p][s]));
                                if(p == 1) {    
                                        SuSA_4461[r][p][s]->Scale(neutron_corr_4461_susa[r][p]);
                                        Data_4461[r][p][s]->Scale(neutron_corr_4461_G18[r][p]);
                                        G_4461[r][p][s]->Scale(neutron_corr_4461_G18[r][p]);
                                }
                        }
                }
        }


//Combine histograms to get overall average proton momentum
        TH1D* Data_comb_1161[2][2];
        TH1D* Data_comb_2261[3][2];
        TH1D* Data_comb_4461[1][2];
        TH1D* SuSA_comb_1161[2][2];
        TH1D* SuSA_comb_2261[3][2];
        TH1D* SuSA_comb_4461[1][2];
        TH1D* G_comb_1161[2][2];
        TH1D* G_comb_2261[3][2];
        TH1D* G_comb_4461[1][2];
        
        for(int p = 0; p < 2; p++ ) {

                for(int r = 0; r < 2; r++) {
                        for(int s: sectors) {
                                if(p ==1) s = (s+3)%6;

                                if((p == 0 && s == 2) || (p == 1 && s == 5)) {
                                        Data_comb_1161[r][p] = (TH1D*)( Data_1161[r][p][s]->Clone() );
                                        SuSA_comb_1161[r][p] = (TH1D*)( SuSA_1161[r][p][s]->Clone() );
                                        G_comb_1161[r][p] = (TH1D*)(G_1161[r][p][s]->Clone() );

                                }
                                if((p == 0 && s != 2) || (p == 1 && s != 5)) {
                                        Data_comb_1161[r][p]->Add( Data_1161[r][p][s] );
                                        SuSA_comb_1161[r][p]->Add( SuSA_1161[r][p][s] );
                                        G_comb_1161[r][p]->Add( G_1161[r][p][s] );
                                }


                        }
                }

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
                reco_dist_canvas->SaveAs("C12_reco_dist.pdf(");

                TLegend *leg1161[2][2][6];
                TLegend *leg2261[3][2][6];
                TLegend *leg4461[1][2][6];

                for(int s : sectors) {
                        for(int p = 0; p < 2; p++) {
                                if(p == 1) s = (s+3)%6;


                                for(int r = 0; r< 2; r++ ) {
                                        leg1161[r][p][s] = new TLegend(0.7,0.75,0.89,0.89);
                                        SuSA_1161[r][p][s]->Draw("e hist");
                                        Data_1161[r][p][s]->Draw("e same");
                                        SuSA_1161[r][p][s]->SetTitle("SuSA_v2 C12");
                                        Data_1161[r][p][s]->SetTitle("Data C12");
                                        G_1161[r][p][s]->Draw("e same");
                                        G_1161[r][p][s]->SetTitle("G18 C12");
                                        G_1161[r][p][s]->SetLineColor(kRed);
                                        leg1161[r][p][s]->AddEntry(G_1161[r][p][s]);
                                        Data_1161[r][p][s]->SetMarkerColor(kBlack);
                                        Data_1161[r][p][s]->SetMarkerStyle(20);
                                        SuSA_1161[r][p][s]->GetYaxis()->SetTitle("Absolute Number of Events ");
                                        SuSA_1161[r][p][s]->GetXaxis()->SetTitle("Momentum (GeV)");
                                        leg1161[r][p][s]->AddEntry(Data_1161[r][p][s]);
                                        leg1161[r][p][s]->AddEntry(SuSA_1161[r][p][s]);
                                        leg1161[r][p][s]->Draw();
                                        SuSA_1161[r][p][s]->SetTitle(TString::Format("SuSA_v2 C12 %s Sector %i", first_en[r][p].c_str(), s));
                                        reco_dist_canvas->SaveAs("C12_reco_dist.pdf");
                                }

                                for(int r = 0; r< 3; r++ ) {
                                        leg2261[r][p][s] = new TLegend(0.7,0.75,0.89,0.89);
                                        SuSA_2261[r][p][s]->Draw("e hist");
                                        Data_2261[r][p][s]->Draw("e same");
                                        SuSA_2261[r][p][s]->SetTitle("SuSA_v2 C12");
                                        Data_2261[r][p][s]->SetTitle("Data C12");
                                        G_2261[r][p][s]->Draw("e same");
                                        G_2261[r][p][s]->SetTitle("G18 C12");
                                        G_2261[r][p][s]->SetLineColor(kRed);
                                        leg2261[r][p][s]->AddEntry(G_2261[r][p][s]);
                                        Data_2261[r][p][s]->SetMarkerColor(kBlack);
                                        Data_2261[r][p][s]->SetMarkerStyle(20);
                                        SuSA_2261[r][p][s]->GetYaxis()->SetTitle("Absolute Number of Events ");
                                        SuSA_2261[r][p][s]->GetXaxis()->SetTitle("Momentum (GeV)");
                                        leg2261[r][p][s]->AddEntry(Data_2261[r][p][s]);
                                        leg2261[r][p][s]->AddEntry(SuSA_2261[r][p][s]);
                                        leg2261[r][p][s]->Draw();
                                        SuSA_2261[r][p][s]->SetTitle(TString::Format("SuSA_v2 C12 %s Sector %i", second_en[r][p].c_str(), s));
                                        reco_dist_canvas->SaveAs("C12_reco_dist.pdf");
                                }


                                for(int r = 0; r < 1; r++ ) {
                                        leg4461[r][p][s] = new TLegend(0.7,0.75,0.89,0.89);
                                        SuSA_4461[r][p][s]->Draw("e hist");
                                        Data_4461[r][p][s]->Draw("e same");
                                        SuSA_4461[r][p][s]->SetTitle("SuSA_v2 C12");
                                        Data_4461[r][p][s]->SetTitle("Data C12");
                                        G_4461[r][p][s]->Draw("e same");
                                        G_4461[r][p][s]->SetTitle("G18 C12");
                                        G_4461[r][p][s]->SetLineColor(kRed);
                                        leg4461[r][p][s]->AddEntry(G_2261[r][p][s]);
                                        Data_4461[r][p][s]->SetMarkerColor(kBlack);
                                        Data_4461[r][p][s]->SetMarkerStyle(20);
                                        SuSA_4461[r][p][s]->GetYaxis()->SetTitle("Absolute Number of Events");
                                        SuSA_4461[r][p][s]->GetXaxis()->SetTitle("Momentum (GeV)");
                                        leg4461[r][p][s]->AddEntry(Data_2261[r][p][s]);
                                        leg4461[r][p][s]->AddEntry(SuSA_2261[r][p][s]);
                                        leg4461[r][p][s]->Draw();
                                        SuSA_4461[r][p][s]->SetTitle(TString::Format("SuSA_v2 C12 %s Sector %i", third_en[r][p].c_str(), s));
                                        reco_dist_canvas->SaveAs("C12_reco_dist.pdf");
                                }
                        }
                }
                reco_dist_canvas->SaveAs("C12_reco_dist.pdf)");
        }


        double data_comb_int_1161[2][2];
        double data_comb_int_2261[3][2];
        double data_comb_int_4461[1][2];
        double data_comb_int_1161_err[2][2];
        double data_comb_int_2261_err[3][2];
        double data_comb_int_4461_err[1][2];


        double SuSA_comb_int_1161[2][2];
        double SuSA_comb_int_2261[3][2];
        double SuSA_comb_int_4461[1][2];
        double SuSA_comb_int_1161_err[2][2];
        double SuSA_comb_int_2261_err[3][2];
        double SuSA_comb_int_4461_err[1][2];

        double G_comb_int_1161[2][2];
        double G_comb_int_2261[3][2];
        double G_comb_int_4461[1][2];
        double G_comb_int_1161_err[2][2];
        double G_comb_int_2261_err[3][2];
        double G_comb_int_4461_err[1][2];

        std::cout << "Combined Yields for Data and MC" << "\n";

        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 2; r++) {
                        data_comb_int_1161[r][p] = Data_comb_1161[r][p]->IntegralAndError(1, Data_comb_1161[r][p]->GetNbinsX(), data_comb_int_1161_err[r][p],"width");
                        SuSA_comb_int_1161[r][p] = SuSA_comb_1161[r][p]->IntegralAndError(1, SuSA_comb_1161[r][p]->GetNbinsX(), SuSA_comb_int_1161_err[r][p],"width");
                        G_comb_int_1161[r][p] = G_comb_1161[r][p]->IntegralAndError(1, G_comb_1161[r][p]->GetNbinsX(), G_comb_int_1161_err[r][p],"width");
                                std::cout << "Data " << first_en[r][p] << " = " << data_comb_int_1161[r][p] << " p/m " << data_comb_int_1161_err[r][p] << "\n";
                                std::cout << "SuSA " << first_en[r][p] << " = " << SuSA_comb_int_1161[r][p] << " p/m " << SuSA_comb_int_1161_err[r][p] << "\n";
                                std::cout << "G    " << first_en[r][p] << " = " << G_comb_int_1161[r][p] << " p/m " << G_comb_int_1161_err[r][p] << "\n";
                }
                for(int r = 0; r < 3; r++) {
                        data_comb_int_2261[r][p] = Data_comb_2261[r][p]->IntegralAndError(1, Data_comb_2261[r][p]->GetNbinsX(), data_comb_int_2261_err[r][p],"width");
                        SuSA_comb_int_2261[r][p] = SuSA_comb_2261[r][p]->IntegralAndError(1, SuSA_comb_2261[r][p]->GetNbinsX(), SuSA_comb_int_2261_err[r][p],"width");
                        G_comb_int_2261[r][p] = G_comb_2261[r][p]->IntegralAndError(1, G_comb_2261[r][p]->GetNbinsX(), G_comb_int_2261_err[r][p],"width");
                                std::cout << "Data " << second_en[r][p] << " = " << data_comb_int_2261[r][p] << " p/m " << data_comb_int_2261_err[r][p] <<  "\n";
                                std::cout << "SuSA " << second_en[r][p] << " = " << SuSA_comb_int_2261[r][p] << " p/m " << SuSA_comb_int_2261_err[r][p] << "\n";
                                std::cout << "G    " << second_en[r][p] << " = " << G_comb_int_2261[r][p] << " p/m " << G_comb_int_2261_err[r][p] << "\n";
                }
                for(int r = 0; r < 1; r++) {
                        data_comb_int_4461[r][p] = Data_comb_4461[r][p]->IntegralAndError(1, Data_comb_4461[r][p]->GetNbinsX(), data_comb_int_4461_err[r][p],"width");
                        SuSA_comb_int_4461[r][p] = SuSA_comb_4461[r][p]->IntegralAndError(1, SuSA_comb_4461[r][p]->GetNbinsX(), SuSA_comb_int_4461_err[r][p],"width");
                        G_comb_int_4461[r][p] = G_comb_4461[r][p]->IntegralAndError(1, G_comb_4461[r][p]->GetNbinsX(), G_comb_int_4461_err[r][p],"width");
                                std::cout << "Data " << third_en[r][p] << " = " << data_comb_int_4461[r][p] << " p/m " << data_comb_int_4461_err[r][p] << "\n";
                                std::cout << "SuSA " << third_en[r][p] << " = " << SuSA_comb_int_4461[r][p] << " p/m " << SuSA_comb_int_4461_err[r][p] << "\n"; 
                                std::cout << "G    " << third_en[r][p] << " = " << G_comb_int_4461[r][p] << " p/m " << G_comb_int_4461_err[r][p] << "\n";         
                }
        }

        double data_comb_avg_prot_mom_1161[2];
        double data_comb_avg_prot_mom_2261[3];
        double data_comb_avg_prot_mom_4461[1];

        double SuSA_comb_avg_prot_mom_1161[2];
        double SuSA_comb_avg_prot_mom_2261[3];
        double SuSA_comb_avg_prot_mom_4461[1];

        double G_comb_avg_prot_mom_1161[2];
        double G_comb_avg_prot_mom_2261[3];
        double G_comb_avg_prot_mom_4461[1];

        data_comb_avg_prot_mom_1161[0] = weighted_average(Data_comb_1161[0][0]); 
        data_comb_avg_prot_mom_1161[1] = weighted_average(Data_comb_1161[1][0]);
        data_comb_avg_prot_mom_2261[0] = weighted_average(Data_comb_2261[0][0]); 
        data_comb_avg_prot_mom_2261[1] = weighted_average(Data_comb_2261[1][0]); 
        data_comb_avg_prot_mom_2261[2] = weighted_average(Data_comb_2261[2][0]);
        data_comb_avg_prot_mom_4461[0] = weighted_average(Data_comb_4461[0][0]); 

        SuSA_comb_avg_prot_mom_1161[0] = weighted_average(SuSA_comb_1161[0][0]); 
        SuSA_comb_avg_prot_mom_1161[1] = weighted_average(SuSA_comb_1161[1][0]);
        SuSA_comb_avg_prot_mom_2261[0] = weighted_average(SuSA_comb_2261[0][0]); 
        SuSA_comb_avg_prot_mom_2261[1] = weighted_average(SuSA_comb_2261[1][0]); 
        SuSA_comb_avg_prot_mom_2261[2] = weighted_average(SuSA_comb_2261[2][0]);
        SuSA_comb_avg_prot_mom_4461[0] = weighted_average(SuSA_comb_4461[0][0]); 

        G_comb_avg_prot_mom_1161[0] = weighted_average(G_comb_1161[0][0]); 
        G_comb_avg_prot_mom_1161[1] = weighted_average(G_comb_1161[1][0]);
        G_comb_avg_prot_mom_2261[0] = weighted_average(G_comb_2261[0][0]); 
        G_comb_avg_prot_mom_2261[1] = weighted_average(G_comb_2261[1][0]); 
        G_comb_avg_prot_mom_2261[2] = weighted_average(G_comb_2261[2][0]);
        G_comb_avg_prot_mom_4461[0] = weighted_average(G_comb_4461[0][0]); 

        


// -------------- Integrate sector by sector histograms -----------------


        double data_int_1161[2][2][6];
        double data_int_2261[3][2][6];
        double data_int_4461[1][2][6];
        double data_int_1161_err[2][2][6];
        double data_int_2261_err[3][2][6];
        double data_int_4461_err[1][2][6];

        double SuSA_int_1161[2][2][6];
        double SuSA_int_2261[3][2][6];
        double SuSA_int_4461[1][2][6];
        double SuSA_int_1161_err[2][2][6];
        double SuSA_int_2261_err[3][2][6];
        double SuSA_int_4461_err[1][2][6];

        double G_int_1161[2][2][6];
        double G_int_2261[3][2][6];
        double G_int_4461[1][2][6];
        double G_int_1161_err[2][2][6];
        double G_int_2261_err[3][2][6];
        double G_int_4461_err[1][2][6];

        std::cout << "Sector by Sector Yields for Data and MC" << "\n";
        
        for(int s : sectors) {
                for(int p = 0; p < 2; p++) {
                        if(p == 1) s = (s+3)%6;
                        std::cout << "Sector " << s << "\n";

                        //1161
                        for(int r = 0; r < 2; r++) {
                                data_int_1161[r][p][s] = Data_1161[r][p][s]->IntegralAndError(1, Data_1161[r][p][s]->GetNbinsX(), data_int_1161_err[r][p][s],"width");
                                SuSA_int_1161[r][p][s] = SuSA_1161[r][p][s]->IntegralAndError(1, SuSA_1161[r][p][s]->GetNbinsX(), SuSA_int_1161_err[r][p][s],"width");
                                G_int_1161[r][p][s] = G_1161[r][p][s]->IntegralAndError(1, G_1161[r][p][s]->GetNbinsX(), G_int_1161_err[r][p][s],"width");
                                std::cout << "Data " << first_en[r][p] << " = " << data_int_1161[r][p][s] << " p/m " << data_int_1161_err[r][p][s] << "\n";
                                std::cout << "SuSA " << first_en[r][p] << " = " << SuSA_int_1161[r][p][s] << " p/m " << SuSA_int_1161_err[r][p][s]  << "\n";
                                std::cout << "G    " << first_en[r][p] << " = " << G_int_1161[r][p][s] << " p/m " << G_int_1161_err[r][p][s]  << "\n";
                        }
 
                        //2261
                        for(int r = 0; r < 3; r++) {
                                data_int_2261[r][p][s] = Data_2261[r][p][s]->IntegralAndError(1, Data_2261[r][p][s]->GetNbinsX(), data_int_2261_err[r][p][s],"width");
                                SuSA_int_2261[r][p][s] = SuSA_2261[r][p][s]->IntegralAndError(1, SuSA_2261[r][p][s]->GetNbinsX(), SuSA_int_2261_err[r][p][s],"width");
                                G_int_2261[r][p][s] = G_2261[r][p][s]->IntegralAndError(1, G_2261[r][p][s]->GetNbinsX(), G_int_2261_err[r][p][s],"width");
                                std::cout << "Data " << second_en[r][p] << " = " << data_int_2261[r][p][s] << " p/m " << data_int_2261_err[r][p][s] << "\n";
                                std::cout << "SuSA " << second_en[r][p] << " = " << SuSA_int_2261[r][p][s] << " p/m " << SuSA_int_2261_err[r][p][s]  << "\n";
                                std::cout << "G    " << second_en[r][p] << " = " << G_int_2261[r][p][s] << " p/m " << G_int_2261_err[r][p][s]  << "\n";
                        }

                        //4461
                        for(int r = 0; r < 1; r++) {
                                data_int_4461[r][p][s] = Data_4461[r][p][s]->IntegralAndError(1, Data_4461[r][p][s]->GetNbinsX(), data_int_4461_err[r][p][s],"width");
                                SuSA_int_4461[r][p][s] = SuSA_4461[r][p][s]->IntegralAndError(1, SuSA_4461[r][p][s]->GetNbinsX(), SuSA_int_4461_err[r][p][s],"width");
                                G_int_4461[r][p][s] = G_4461[r][p][s]->IntegralAndError(1, G_4461[r][p][s]->GetNbinsX(), G_int_4461_err[r][p][s],"width");
                                std::cout << "Data " << third_en[r][p] << " = " << data_int_4461[r][p][s] << " p/m " << data_int_4461_err[r][p][s]  << "\n";
                                std::cout << "SuSA " << third_en[r][p] << " = " << SuSA_int_4461[r][p][s] << " p/m " << SuSA_int_4461_err[r][p][s]  << "\n";
                                std::cout << "G    " << third_en[r][p] << " = " << G_int_4461[r][p][s] << " p/m " << G_int_4461_err[r][p][s]  << "\n";
                        }
                }
        }

// ----------- Take Ratios to obtain transparencies and errors --------------
        //Remember that a proton in sector i corresponds to an electron in sector (i-3)

        // Sector by sector data transparencies
        double data_T_1161[2][6];
        double data_T_2261[3][6];
        double data_T_4461[1][6];
        double data_T_1161_err[2][6];
        double data_T_2261_err[3][6];
        double data_T_4461_err[1][6];

        // Spread in data transparencies
        double data_spread_T_1161[2];
        double data_spread_T_2261[3];
        double data_spread_T_4461[1];
        double data_spread_T_1161_err[2];
        double data_spread_T_2261_err[3];
        double data_spread_T_4461_err[1];

        // Sector by sector susa transparencies
        double SuSA_T_1161[2][6];
        double SuSA_T_2261[3][6];
        double SuSA_T_4461[1][6];
        double SuSA_T_1161_err[2][6];
        double SuSA_T_2261_err[3][6];
        double SuSA_T_4461_err[1][6];

        // Spread in susa transparencies
        double SuSA_spread_T_1161[2];
        double SuSA_spread_T_2261[3];
        double SuSA_spread_T_4461[1];
        double SuSA_spread_T_1161_err[2];
        double SuSA_spread_T_2261_err[3];
        double SuSA_spread_T_4461_err[1];

        // Sector by sector G18 transparencies
        double G_T_1161[2][6];
        double G_T_2261[3][6];
        double G_T_4461[1][6];
        double G_T_1161_err[2][6];
        double G_T_2261_err[3][6];
        double G_T_4461_err[1][6];

        // Spread in G18 transparencies
        double G_spread_T_1161[2];
        double G_spread_T_2261[3];
        double G_spread_T_4461[1];
        double G_spread_T_1161_err[2];
        double G_spread_T_2261_err[3];
        double G_spread_T_4461_err[1];

        // Data combined transparencies
        double data_comb_T_1161[2];
        double data_comb_T_2261[3];
        double data_comb_T_4461[1];
        double data_comb_T_1161_err[2];
        double data_comb_T_2261_err[3];
        double data_comb_T_4461_err[1];

        // SuSA combined transparencies
        double SuSA_comb_T_1161[2];
        double SuSA_comb_T_2261[3];
        double SuSA_comb_T_4461[1];
        double SuSA_comb_T_1161_err[2];
        double SuSA_comb_T_2261_err[3];
        double SuSA_comb_T_4461_err[1];

        // G18 combined transparencies
        double G_comb_T_1161[2];
        double G_comb_T_2261[3];
        double G_comb_T_4461[1];
        double G_comb_T_1161_err[2];
        double G_comb_T_2261_err[3];
        double G_comb_T_4461_err[1];

        // Compute transparencies and errors by sector
        for(int s : sectors) {
                data_T_1161[0][s] = myratio(data_int_1161[0][0][s],data_int_1161[0][1][(s+3)%6]);
                data_T_1161[1][s] = myratio(data_int_1161[1][0][s],data_int_1161[1][1][(s+3)%6]);
                data_T_2261[0][s] = myratio(data_int_2261[0][0][s],data_int_2261[0][1][(s+3)%6]);
                data_T_2261[1][s] = myratio(data_int_2261[1][0][s],data_int_2261[1][1][(s+3)%6]);
                data_T_2261[2][s] = myratio(data_int_2261[2][0][s],data_int_2261[2][1][(s+3)%6]);
                data_T_4461[0][s] = myratio(data_int_4461[0][0][s],data_int_4461[0][1][(s+3)%6]);

                data_T_1161_err[0][s] = get_ratio_error(data_int_1161[0][0][s],data_int_1161[0][1][(s+3)%6]);
                data_T_1161_err[1][s] = get_ratio_error(data_int_1161[1][0][s],data_int_1161[1][1][(s+3)%6]);
                data_T_2261_err[0][s] = get_ratio_error(data_int_2261[0][0][s],data_int_2261[0][1][(s+3)%6]);
                data_T_2261_err[1][s] = get_ratio_error(data_int_2261[1][0][s],data_int_2261[1][1][(s+3)%6]);
                data_T_2261_err[2][s] = get_ratio_error(data_int_2261[2][0][s],data_int_2261[2][1][(s+3)%6]);
                data_T_4461_err[0][s] = get_ratio_error(data_int_4461[0][0][s],data_int_4461[0][1][(s+3)%6]);

                SuSA_T_1161[0][s] = myratio(SuSA_int_1161[0][0][s],SuSA_int_1161[0][1][(s+3)%6]);
                SuSA_T_1161[1][s] = myratio(SuSA_int_1161[1][0][s],SuSA_int_1161[1][1][(s+3)%6]);
                SuSA_T_2261[0][s] = myratio(SuSA_int_2261[0][0][s],SuSA_int_2261[0][1][(s+3)%6]);
                SuSA_T_2261[1][s] = myratio(SuSA_int_2261[1][0][s],SuSA_int_2261[1][1][(s+3)%6]);
                SuSA_T_2261[2][s] = myratio(SuSA_int_2261[2][0][s],SuSA_int_2261[2][1][(s+3)%6]);
                SuSA_T_4461[0][s] = myratio(SuSA_int_4461[0][0][s],SuSA_int_4461[0][1][(s+3)%6]);
                
                SuSA_T_1161_err[0][s] = get_ratio_error(SuSA_int_1161[0][0][s],SuSA_int_1161[0][1][(s+3)%6]);
                SuSA_T_1161_err[1][s] = get_ratio_error(SuSA_int_1161[1][0][s],SuSA_int_1161[1][1][(s+3)%6]);
                SuSA_T_2261_err[0][s] = get_ratio_error(SuSA_int_2261[0][0][s],SuSA_int_2261[0][1][(s+3)%6]);
                SuSA_T_2261_err[1][s] = get_ratio_error(SuSA_int_2261[1][0][s],SuSA_int_2261[1][1][(s+3)%6]);
                SuSA_T_2261_err[2][s] = get_ratio_error(SuSA_int_2261[2][0][s],SuSA_int_2261[2][1][(s+3)%6]);
                SuSA_T_4461_err[0][s] = get_ratio_error(SuSA_int_4461[0][0][s],SuSA_int_4461[0][1][(s+3)%6]);

                G_T_1161[0][s] = myratio(G_int_1161[0][0][s],G_int_1161[0][1][(s+3)%6]);
                G_T_1161[1][s] = myratio(G_int_1161[1][0][s],G_int_1161[1][1][(s+3)%6]);
                G_T_2261[0][s] = myratio(G_int_2261[0][0][s],G_int_2261[0][1][(s+3)%6]);
                G_T_2261[1][s] = myratio(G_int_2261[1][0][s],G_int_2261[1][1][(s+3)%6]);
                G_T_2261[2][s] = myratio(G_int_2261[2][0][s],G_int_2261[2][1][(s+3)%6]);
                G_T_4461[0][s] = myratio(G_int_4461[0][0][s],G_int_4461[0][1][(s+3)%6]);

                G_T_1161_err[0][s] = get_ratio_error(G_int_1161[0][0][s],G_int_1161[0][1][(s+3)%6]);
                G_T_1161_err[1][s] = get_ratio_error(G_int_1161[1][0][s],G_int_1161[1][1][(s+3)%6]);
                G_T_2261_err[0][s] = get_ratio_error(G_int_2261[0][0][s],G_int_2261[0][1][(s+3)%6]);
                G_T_2261_err[1][s] = get_ratio_error(G_int_2261[1][0][s],G_int_2261[1][1][(s+3)%6]);
                G_T_2261_err[2][s] = get_ratio_error(G_int_2261[2][0][s],G_int_2261[2][1][(s+3)%6]);
                G_T_4461_err[0][s] = get_ratio_error(G_int_4461[0][0][s],G_int_4461[0][1][(s+3)%6]);
        }


        //Compute spread of transparencies
        for(int s : sectors) { 
                if(s != 3) {
                        data_spread_T_1161[0] += diff_squared(data_T_1161[0][3],data_T_1161[0][s]);
                        data_spread_T_1161[1] += diff_squared(data_T_1161[1][3],data_T_1161[1][s]);
                        data_spread_T_2261[0] += diff_squared(data_T_2261[0][3],data_T_2261[0][s]);
                        data_spread_T_2261[1] += diff_squared(data_T_2261[1][3],data_T_2261[1][s]);
                        data_spread_T_2261[2] += diff_squared(data_T_2261[2][3],data_T_2261[2][s]);
                        data_spread_T_4461[0] += diff_squared(data_T_4461[0][3],data_T_4461[0][s]);

                        SuSA_spread_T_1161[0] += diff_squared(SuSA_T_1161[0][3],SuSA_T_1161[0][s]);
                        SuSA_spread_T_1161[1] += diff_squared(SuSA_T_1161[1][3],SuSA_T_1161[1][s]);
                        SuSA_spread_T_2261[0] += diff_squared(SuSA_T_2261[0][3],SuSA_T_2261[0][s]);
                        SuSA_spread_T_2261[1] += diff_squared(SuSA_T_2261[1][3],SuSA_T_2261[1][s]);
                        SuSA_spread_T_2261[2] += diff_squared(SuSA_T_2261[2][3],SuSA_T_2261[2][s]);
                        SuSA_spread_T_4461[0] += diff_squared(SuSA_T_4461[0][3],SuSA_T_4461[0][s]);

                        G_spread_T_1161[0] += diff_squared(G_T_1161[0][3],G_T_1161[0][s]);
                        G_spread_T_1161[1] += diff_squared(G_T_1161[1][3],G_T_1161[1][s]);
                        G_spread_T_2261[0] += diff_squared(G_T_2261[0][3],G_T_2261[0][s]);
                        G_spread_T_2261[1] += diff_squared(G_T_2261[1][3],G_T_2261[1][s]);
                        G_spread_T_2261[2] += diff_squared(G_T_2261[2][3],G_T_2261[2][s]);
                        G_spread_T_4461[0] += diff_squared(G_T_4461[0][3],G_T_4461[0][s]);
                }
        }

        // Take sqrt of sector by sector uncertainty and then add them to overall uncertainty 
        data_spread_T_1161[0] = sqrt(data_spread_T_1161[0]/num_1161_sec);
        data_spread_T_1161[1] = sqrt(data_spread_T_1161[1]/num_1161_sec);
        data_spread_T_2261[0] = sqrt(data_spread_T_2261[0]/num_2261_sec);
        data_spread_T_2261[1] = sqrt(data_spread_T_2261[1]/num_2261_sec);
        data_spread_T_2261[2] = sqrt(data_spread_T_2261[2]/num_2261_sec);
        data_spread_T_4461[0] = sqrt(data_spread_T_4461[0]/num_4461_sec);

        SuSA_spread_T_1161[0] = sqrt(SuSA_spread_T_1161[0]/num_1161_sec);
        SuSA_spread_T_1161[1] = sqrt(SuSA_spread_T_1161[1]/num_1161_sec);
        SuSA_spread_T_2261[0] = sqrt(SuSA_spread_T_2261[0]/num_2261_sec);
        SuSA_spread_T_2261[1] = sqrt(SuSA_spread_T_2261[1]/num_2261_sec);
        SuSA_spread_T_2261[2] = sqrt(SuSA_spread_T_2261[2]/num_2261_sec);
        SuSA_spread_T_4461[0] = sqrt(SuSA_spread_T_4461[0]/num_4461_sec);

        G_spread_T_1161[0] = sqrt(G_spread_T_1161[0]/num_1161_sec);
        G_spread_T_1161[1] = sqrt(G_spread_T_1161[1]/num_1161_sec);
        G_spread_T_2261[0] = sqrt(G_spread_T_2261[0]/num_2261_sec);
        G_spread_T_2261[1] = sqrt(G_spread_T_2261[1]/num_2261_sec);
        G_spread_T_2261[2] = sqrt(G_spread_T_2261[2]/num_2261_sec);
        G_spread_T_4461[0] = sqrt(G_spread_T_4461[0]/num_4461_sec);

        //Get combined transparencies and errors
        data_comb_T_1161[0] = myratio(data_comb_int_1161[0][0],data_comb_int_1161[0][1]);
        data_comb_T_1161[1] = myratio(data_comb_int_1161[1][0],data_comb_int_1161[1][1]);
        data_comb_T_2261[0] = myratio(data_comb_int_2261[0][0],data_comb_int_2261[0][1]);
        data_comb_T_2261[1] = myratio(data_comb_int_2261[1][0],data_comb_int_2261[1][1]);
        data_comb_T_2261[2] = myratio(data_comb_int_2261[2][0],data_comb_int_2261[2][1]);
        data_comb_T_4461[0] = myratio(data_comb_int_4461[0][0],data_comb_int_4461[0][1]);

        data_comb_T_1161_err[0] = get_ratio_error(data_comb_int_1161[0][0],data_comb_int_1161[0][1]);
        data_comb_T_1161_err[1] = get_ratio_error(data_comb_int_1161[1][0],data_comb_int_1161[1][1]);
        data_comb_T_2261_err[0] = get_ratio_error(data_comb_int_2261[0][0],data_comb_int_2261[0][1]);
        data_comb_T_2261_err[1] = get_ratio_error(data_comb_int_2261[1][0],data_comb_int_2261[1][1]);
        data_comb_T_2261_err[2] = get_ratio_error(data_comb_int_2261[2][0],data_comb_int_2261[2][1]);
        data_comb_T_4461_err[0] = get_ratio_error(data_comb_int_4461[0][0],data_comb_int_4461[0][1]);

        SuSA_comb_T_1161[0] = myratio(SuSA_comb_int_1161[0][0],SuSA_comb_int_1161[0][1]);
        SuSA_comb_T_1161[1] = myratio(SuSA_comb_int_1161[1][0],SuSA_comb_int_1161[1][1]);
        SuSA_comb_T_2261[0] = myratio(SuSA_comb_int_2261[0][0],SuSA_comb_int_2261[0][1]);
        SuSA_comb_T_2261[1] = myratio(SuSA_comb_int_2261[1][0],SuSA_comb_int_2261[1][1]);
        SuSA_comb_T_2261[2] = myratio(SuSA_comb_int_2261[2][0],SuSA_comb_int_2261[2][1]);
        SuSA_comb_T_4461[0] = myratio(SuSA_comb_int_4461[0][0],SuSA_comb_int_4461[0][1]);

        SuSA_comb_T_1161_err[0] = get_ratio_error(SuSA_comb_int_1161[0][0],SuSA_comb_int_1161[0][1]);
        SuSA_comb_T_1161_err[1] = get_ratio_error(SuSA_comb_int_1161[1][0],SuSA_comb_int_1161[1][1]);
        SuSA_comb_T_2261_err[0] = get_ratio_error(SuSA_comb_int_2261[0][0],SuSA_comb_int_2261[0][1]);
        SuSA_comb_T_2261_err[1] = get_ratio_error(SuSA_comb_int_2261[1][0],SuSA_comb_int_2261[1][1]);
        SuSA_comb_T_2261_err[2] = get_ratio_error(SuSA_comb_int_2261[2][0],SuSA_comb_int_2261[2][1]);
        SuSA_comb_T_4461_err[0] = get_ratio_error(SuSA_comb_int_4461[0][0],SuSA_comb_int_4461[0][1]);

        G_comb_T_1161[0] = myratio(G_comb_int_1161[0][0],G_comb_int_1161[0][1]);
        G_comb_T_1161[1] = myratio(G_comb_int_1161[1][0],G_comb_int_1161[1][1]);
        G_comb_T_2261[0] = myratio(G_comb_int_2261[0][0],G_comb_int_2261[0][1]);
        G_comb_T_2261[1] = myratio(G_comb_int_2261[1][0],G_comb_int_2261[1][1]);
        G_comb_T_2261[2] = myratio(G_comb_int_2261[2][0],G_comb_int_2261[2][1]);
        G_comb_T_4461[0] = myratio(G_comb_int_4461[0][0],G_comb_int_4461[0][1]);

        G_comb_T_1161_err[0] = get_ratio_error(G_comb_int_1161[0][0],G_comb_int_1161[0][1]);
        G_comb_T_1161_err[1] = get_ratio_error(G_comb_int_1161[1][0],G_comb_int_1161[1][1]);
        G_comb_T_2261_err[0] = get_ratio_error(G_comb_int_2261[0][0],G_comb_int_2261[0][1]);
        G_comb_T_2261_err[1] = get_ratio_error(G_comb_int_2261[1][0],G_comb_int_2261[1][1]);
        G_comb_T_2261_err[2] = get_ratio_error(G_comb_int_2261[2][0],G_comb_int_2261[2][1]);
        G_comb_T_4461_err[0] = get_ratio_error(G_comb_int_4461[0][0],G_comb_int_4461[0][1]);


// ---------------------------------------------------------------------

        double ypoints[6][6]; 
        double ypoint_errs[6][6]; 
        double xpoints[6][6]; 
        double xpoint_errs[6][6]; 

        double mc_ypoints[6][6];
        double mc_ypoint_errs[6][6];
        double mc_xpoints[6][6]; 
        double mc_xpoint_errs[6][6];

        double G_mc_ypoints[6][6];
        double G_mc_ypoint_errs[6][6];
        double G_mc_xpoints[6][6]; 

        // Add all the transparencies by sectors to arrays
        for(int s : sectors) {
                
                ypoints[s][0] = data_T_1161[0][s];
                ypoints[s][1] = data_T_1161[1][s];
                ypoints[s][2] = data_T_2261[0][s];
                ypoints[s][3] = data_T_2261[1][s];
                ypoints[s][4] = data_T_2261[2][s];
                ypoints[s][5] = data_T_4461[0][s];
                
                ypoint_errs[s][0] = data_T_1161_err[0][s];
                ypoint_errs[s][1] = data_T_1161_err[1][s];
                ypoint_errs[s][2] = data_T_2261_err[0][s];
                ypoint_errs[s][3] = data_T_2261_err[1][s];
                ypoint_errs[s][4] = data_T_2261_err[2][s];
                ypoint_errs[s][5] = data_T_4461_err[0][s];
                
                xpoints[s][0] = data_avg_prot_mom_1161[0][s];
                xpoints[s][1] = data_avg_prot_mom_1161[1][s];
                xpoints[s][2] = data_avg_prot_mom_2261[0][s];
                xpoints[s][3] = data_avg_prot_mom_2261[1][s];
                xpoints[s][4] = data_avg_prot_mom_2261[2][s];
                xpoints[s][5] = data_avg_prot_mom_4461[0][s];
                
                mc_ypoints[s][0] = SuSA_T_1161[0][s];
                mc_ypoints[s][1] = SuSA_T_1161[1][s];
                mc_ypoints[s][2] = SuSA_T_2261[0][s];
                mc_ypoints[s][3] = SuSA_T_2261[1][s];
                mc_ypoints[s][4] = SuSA_T_2261[2][s];
                mc_ypoints[s][5] = SuSA_T_4461[0][s];

                mc_ypoint_errs[s][0] = SuSA_T_1161_err[0][s];
                mc_ypoint_errs[s][1] = SuSA_T_1161_err[1][s];
                mc_ypoint_errs[s][2] = SuSA_T_2261_err[0][s];
                mc_ypoint_errs[s][3] = SuSA_T_2261_err[1][s];
                mc_ypoint_errs[s][4] = SuSA_T_2261_err[2][s];
                mc_ypoint_errs[s][5] = SuSA_T_4461_err[0][s];

                G_mc_ypoints[s][0] = G_T_1161[0][s];
                G_mc_ypoints[s][1] = G_T_1161[1][s];
                G_mc_ypoints[s][2] = G_T_2261[0][s];
                G_mc_ypoints[s][3] = G_T_2261[1][s];
                G_mc_ypoints[s][4] = G_T_2261[2][s];
                G_mc_ypoints[s][5] = G_T_4461[0][s];

                G_mc_ypoint_errs[s][0] = G_T_1161_err[0][s];
                G_mc_ypoint_errs[s][1] = G_T_1161_err[1][s];
                G_mc_ypoint_errs[s][2] = G_T_2261_err[0][s];
                G_mc_ypoint_errs[s][3] = G_T_2261_err[1][s];
                G_mc_ypoint_errs[s][4] = G_T_2261_err[2][s];
                G_mc_ypoint_errs[s][5] = G_T_4461_err[0][s];

                mc_xpoints[s][0] = SuSA_avg_prot_mom_1161[0][s];
                mc_xpoints[s][1] = SuSA_avg_prot_mom_1161[1][s];
                mc_xpoints[s][2] = SuSA_avg_prot_mom_2261[0][s];
                mc_xpoints[s][3] = SuSA_avg_prot_mom_2261[1][s];
                mc_xpoints[s][4] = SuSA_avg_prot_mom_2261[2][s];
                mc_xpoints[s][5] = SuSA_avg_prot_mom_4461[0][s];

                G_mc_xpoints[s][0] = G_avg_prot_mom_1161[0][s];
                G_mc_xpoints[s][1] = G_avg_prot_mom_1161[1][s];
                G_mc_xpoints[s][2] = G_avg_prot_mom_2261[0][s];
                G_mc_xpoints[s][3] = G_avg_prot_mom_2261[1][s];
                G_mc_xpoints[s][4] = G_avg_prot_mom_2261[2][s];
                G_mc_xpoints[s][5] = G_avg_prot_mom_4461[0][s];

                for(int i = 0; i < 6; i++) {
                        xpoint_errs[s][i] = 0.0;
                        mc_xpoint_errs[s][i] = 0.0;
                }
        }

        double comb_ypoints[6] = {data_comb_T_1161[0], data_comb_T_1161[1], data_comb_T_2261[0], data_comb_T_2261[1], data_comb_T_2261[2], data_comb_T_4461[0]};

        double comb_ypoint_errs[6];
        comb_ypoint_errs[0] = sqrt(pow(data_comb_T_1161_err[0],2) + pow(data_spread_T_1161[0],2));
        comb_ypoint_errs[1] = sqrt(pow(data_comb_T_1161_err[1],2) + pow(data_spread_T_1161[1],2));
        comb_ypoint_errs[2] = sqrt(pow(data_comb_T_2261_err[0],2) + pow(data_spread_T_2261[0],2));
        comb_ypoint_errs[3] = sqrt(pow(data_comb_T_2261_err[1],2) + pow(data_spread_T_2261[1],2));
        comb_ypoint_errs[4] = sqrt(pow(data_comb_T_2261_err[2],2) + pow(data_spread_T_2261[2],2));
        comb_ypoint_errs[5] = sqrt(pow(data_comb_T_4461_err[0],2) + pow(data_spread_T_4461[0],2));

        double comb_xpoints[6] = {data_comb_avg_prot_mom_1161[0], data_comb_avg_prot_mom_1161[1], data_comb_avg_prot_mom_2261[0], data_comb_avg_prot_mom_2261[1], data_comb_avg_prot_mom_2261[2], data_comb_avg_prot_mom_4461[0]};

        double comb_mc_ypoints[6] = {SuSA_comb_T_1161[0], SuSA_comb_T_1161[1], SuSA_comb_T_2261[0], SuSA_comb_T_2261[1], SuSA_comb_T_2261[2], SuSA_comb_T_4461[0]};

        double comb_mc_ypoint_errs[6];
        comb_mc_ypoint_errs[0] = sqrt(pow(SuSA_comb_T_1161_err[0],2) + pow(SuSA_spread_T_1161[0],2));
        comb_mc_ypoint_errs[1] = sqrt(pow(SuSA_comb_T_1161_err[1],2) + pow(SuSA_spread_T_1161[1],2));
        comb_mc_ypoint_errs[2] = sqrt(pow(SuSA_comb_T_2261_err[0],2) + pow(SuSA_spread_T_2261[0],2));
        comb_mc_ypoint_errs[3] = sqrt(pow(SuSA_comb_T_2261_err[1],2) + pow(SuSA_spread_T_2261[1],2));
        comb_mc_ypoint_errs[4] = sqrt(pow(SuSA_comb_T_2261_err[2],2) + pow(SuSA_spread_T_2261[2],2));
        comb_mc_ypoint_errs[5] = sqrt(pow(SuSA_comb_T_4461_err[0],2) + pow(SuSA_spread_T_4461[0],2));

        double comb_mc_xpoints[6] = {SuSA_comb_avg_prot_mom_1161[0],SuSA_comb_avg_prot_mom_1161[1],SuSA_comb_avg_prot_mom_2261[0], SuSA_comb_avg_prot_mom_2261[1], SuSA_comb_avg_prot_mom_2261[2], SuSA_comb_avg_prot_mom_4461[0]};

        double G_comb_mc_ypoints[6] = {G_comb_T_1161[0], G_comb_T_1161[1], G_comb_T_2261[0], G_comb_T_2261[1], G_comb_T_2261[2], G_comb_T_4461[0]};

        double G_comb_mc_ypoint_errs[6];
        G_comb_mc_ypoint_errs[0] = sqrt(pow(G_comb_T_2261_err[0],2) + pow(G_spread_T_2261[0],2));
        G_comb_mc_ypoint_errs[1] = sqrt(pow(G_comb_T_2261_err[1],2) + pow(G_spread_T_2261[1],2));
        G_comb_mc_ypoint_errs[2] = sqrt(pow(G_comb_T_2261_err[0],2) + pow(G_spread_T_2261[0],2));
        G_comb_mc_ypoint_errs[3] = sqrt(pow(G_comb_T_2261_err[1],2) + pow(G_spread_T_2261[1],2));
        G_comb_mc_ypoint_errs[4] = sqrt(pow(G_comb_T_2261_err[2],2) + pow(G_spread_T_2261[2],2));
        G_comb_mc_ypoint_errs[5] = sqrt(pow(G_comb_T_4461_err[0],2) + pow(G_spread_T_4461[0],2));

        double G_comb_mc_xpoints[6] = {G_comb_avg_prot_mom_1161[0], G_comb_avg_prot_mom_1161[1],G_comb_avg_prot_mom_2261[0], G_comb_avg_prot_mom_2261[1], G_comb_avg_prot_mom_2261[2], G_comb_avg_prot_mom_4461[0]};

        double comb_xpoint_errs[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
        double comb_mc_xpoint_errs[6] = {0.0,0.0,0.0,0.0,0.0,0.0};

        std::map<int,int> color_options = {{2,2},{3,4},{4,6}};
        
        TCanvas* c_data;
        c_data = new TCanvas(TString::Format("Data transparency by sector"), TString::Format("Data transparency by sector"), 800, 600);

        TGraphErrors *data_t[6];
        TGraphErrors *data_comb_t;
        data_comb_t = new TGraphErrors(6, comb_xpoints, comb_ypoints, comb_xpoint_errs, comb_ypoint_errs);
        data_comb_t->SetTitle("All Sectors");
        data_comb_t->SetMarkerStyle(kFullCircle);
        data_comb_t->GetXaxis()->SetTitle("Proton Momentum (GeV)");
        data_comb_t->GetYaxis()->SetTitle("Transparency");
        data_comb_t->SetMarkerColor(12);
        data_comb_t->Draw("AP");
        
        for(int s : sectors){

                data_t[s] = new TGraphErrors(6, xpoints[s], ypoints[s], xpoint_errs[s], ypoint_errs[s]);
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
        susa_comb_t = new TGraphErrors(6, comb_mc_xpoints, comb_mc_ypoints, comb_mc_xpoint_errs, comb_mc_ypoint_errs);
        susa_comb_t->SetTitle("All Sectors");
        susa_comb_t->SetMarkerStyle(kFullCircle);
        susa_comb_t->GetXaxis()->SetTitle("Proton Momentum (GeV)");
        susa_comb_t->GetYaxis()->SetTitle("Transparency");
        susa_comb_t->SetMarkerColor(12);
        susa_comb_t->Draw("AP");

        for(int s : sectors){
                susa_t[s] = new TGraphErrors(6, mc_xpoints[s], mc_ypoints[s], mc_xpoint_errs[s], mc_ypoint_errs[s]);
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
        G_comb_t = new TGraphErrors(6, G_comb_mc_xpoints, G_comb_mc_ypoints, comb_mc_xpoint_errs, G_comb_mc_ypoint_errs);
        G_comb_t->SetTitle("All Sectors");
        G_comb_t->SetMarkerStyle(kFullCircle);
        G_comb_t->GetXaxis()->SetTitle("Proton Momentum (GeV)");
        G_comb_t->GetYaxis()->SetTitle("Transparency");
        G_comb_t->SetMarkerColor(12);
        G_comb_t->Draw("AP");

        for(int s : sectors){

                G_t[s] = new TGraphErrors(6, G_mc_xpoints[s], G_mc_ypoints[s], mc_xpoint_errs[s], G_mc_ypoint_errs[s]);
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

        c_comb->SaveAs("T_C12.pdf");


 /*       TFile *final = TFile::Open("T_C12_sectors.root", "RECREATE");
        c_data->Write("data");
        c_susa->Write("SuSA");
        c_
        final->Close();  */  
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

        if((neutrons + protons) == 0.0) return 0;
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

        double mec_int = mom_Int[1]->Integral("width");
        double total_int = total->Integral("width");
        if (total_int == 0.0) return 0;

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

        el_mom->Rebin( 80 );
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

        h1_prot_momentum->Rebin( 80 );
        return h1_prot_momentum;
}

TH1D* AcceptanceCorrect(TH1D* hist, TH1D* susa_true, TH1D* susa_truereco, TH1D* G_true, TH1D* G_truereco, TH1D* susa_truereco_rad, bool make_plots, std::string type) {

        //Make sure we have a non empty histogram
        if(hist->GetEntries() == 0.0) return hist;
        
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
                if(type == "SuSA") {
                        susa_true->GetYaxis()->SetTitle("Scaled number of events");
                        susa_true->GetXaxis()->SetTitle("Momentum (GeV)");
                        susa_true->SetTitle(TString::Format("True %s",hist->GetTitle()));
                        susa_truereco->SetTitle(TString::Format("Reco %s",hist->GetTitle()));
                        susa_true->SetLineColor(kRed);
                        susa_true->Draw("e hist");
                        susa_truereco->Draw("e hist same");
                }
                if(type == "G") {
                        G_true->GetYaxis()->SetTitle("Scaled number of events");
                        G_true->GetXaxis()->SetTitle("Momentum (GeV)");
                        G_true->SetTitle(TString::Format("True %s",hist->GetTitle()));
                        G_truereco->SetTitle(TString::Format("Reco %s",hist->GetTitle()));
                        G_true->SetLineColor(kRed);
                        G_true->Draw("e hist");
                        G_truereco->Draw("e hist same"); 
                }
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
        double AccCorrTolerance = 5;

        for (int WhichBin = 0; WhichBin < NBins; WhichBin++) {
                double AccCorr = 0.;
                double RadCorr = 0.;

                double NewBinContent = 0.;
                double NewBinError = 0.;

                if(type == "G") AccCorr = G_correction->GetBinContent(WhichBin + 1);
                else if(type == "SuSA") AccCorr = susa_correction->GetBinContent(WhichBin + 1);
                else AccCorr = Average->GetBinContent(WhichBin + 1);

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
                if(type != "data") RadCorr = 1.;

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

        TH1D* Spread = (TH1D*)susa_correction->Clone();
        Spread->Add(G_correction, -1);
        Spread->Divide(Average);
        //Spread->Scale(1./TMath::Sqrt(12.));

        int NBinsSpread = Spread->GetXaxis()->GetNbins();

        for (int WhichBin = 0; WhichBin < NBinsSpread; WhichBin++) {

                double BinContent = Spread->GetBinContent(WhichBin+1);
                if (BinContent < 0) { Spread->SetBinContent(WhichBin+1,-BinContent); }

        }

        if(type == "data") {
                for (int WhichBin = 0; WhichBin < NBinsSpread; WhichBin++) {

                        double SpreadBinContent = Spread->GetBinContent(WhichBin+1);
                        double XSecBinError = OverallClone->GetBinError(WhichBin+1);
                        double XSecBinEntry = OverallClone->GetBinContent(WhichBin+1);
                        double AccCorrError = SpreadBinContent * XSecBinEntry;
                        double NewXSecBinError = TMath::Sqrt( TMath::Power(XSecBinError,2.) + TMath::Power(AccCorrError,2.) );
                        if(NewXSecBinError < XSecBinError) {
                                std::cout << "Something wrong, errors should increase!" << "\n";
                                std::cout << "Previous bin error: " << XSecBinError << "\n";
                                std::cout << "Updated bin error: " << NewXSecBinError << "\n";
                        }
                        OverallClone->SetBinError(WhichBin+1,NewXSecBinError);

                }
        }
        

        return OverallClone;
}

double get_ratio_error(double num, double denom) {
        // Binomial errors for transparency ratio
        if (denom == 0. || isnan(num) || isnan(denom)) {
                std::cout << "Is this happening?" << "\n";
                return 0.;
        }
        double p = num/denom;
        double q = 1. - p;
        //std::cout << sqrt(denom * p * q) << "\n";
        return sqrt(denom * p * q);
}

void printit(std::string s, double x) {
        std::cout << s << " = " << x << "\n";
}

double diff_squared(double x, double y) {
        if (isnan(x) || isnan(y) || x == 0.0 || y == 0.0) return 0.;
        //std::cout << (x-y)*(x-y) << "\n";
        return (x - y)*(x - y); 
}

double myratio(double x, double y) {
        if(y == 0. || isnan(x) || isnan(y)) return 0.;
        if (x > y) {
                std::cout << "Something is wrong!" << "\n";
                std::cout << "Ratio = " << x/y << "\n";
        }
        return x/y;
}



