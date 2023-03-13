#include "myFunctions.h"
#include "T_C12_sectors.h"
#include "transfunctions.h"


void T_C12_newsectors_true(bool make_plots = false) {
        gStyle->SetOptStat(0);
        gStyle->SetOptTitle(0);

        data_1161[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/C12/Excl_Range2_Data__C12_1.161000.root";
        data_1161[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/C12/Incl_Range2_Data__C12_1.161000.root";
        data_1161[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/C12/Excl_Range3_Data__C12_1.161000.root";
        data_1161[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/C12/Incl_Range3_Data__C12_1.161000.root";
        data_2261[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/C12/Excl_Range1_Data__C12_2.261000.root";
        data_2261[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/C12/Incl_Range1_Data__C12_2.261000.root";
        data_2261[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/C12/Excl_Range2_Data__C12_2.261000.root";
        data_2261[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/C12/Incl_Range2_Data__C12_2.261000.root";
        data_2261[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/C12/Excl_Range3_Data__C12_2.261000.root";
        data_2261[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/C12/Incl_Range3_Data__C12_2.261000.root";
        data_2261[3][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/C12/Excl_Range1_Data__C12_4.461000.root";
        data_2261[3][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/C12/Incl_Range1_Data__C12_4.461000.root";

        susa_1161[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SuSAv2/Excl_Range2_Genie_1_C12_1.161000.root";
        susa_1161[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SuSAv2/Incl_Range2_Genie_1_C12_1.161000.root";
        susa_1161[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SuSAv2/Excl_Range3_Genie_1_C12_1.161000.root";
        susa_1161[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SuSAv2/Incl_Range3_Genie_1_C12_1.161000.root";
        susa_2261[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SuSAv2/Excl_Range1_Genie_1_C12_2.261000.root";
        susa_2261[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SuSAv2/Incl_Range1_Genie_1_C12_2.261000.root";
        susa_2261[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SuSAv2/Excl_Range2_Genie_1_C12_2.261000.root";
        susa_2261[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SuSAv2/Incl_Range2_Genie_1_C12_2.261000.root";
        susa_2261[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SuSAv2/Excl_Range3_Genie_1_C12_2.261000.root";
        susa_2261[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SuSAv2/Incl_Range3_Genie_1_C12_2.261000.root";
        susa_2261[3][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SuSAv2/Excl_Range1_Genie_1_C12_4.461000.root";
        susa_2261[3][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SuSAv2/Incl_Range1_Genie_1_C12_4.461000.root";

        g_1161[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/G18/Excl_Range2_Genie_2_C12_1.161000.root";
        g_1161[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/G18/Incl_Range2_Genie_2_C12_1.161000.root";
        g_1161[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/G18/Excl_Range3_Genie_2_C12_1.161000.root";
        g_1161[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/G18/Incl_Range3_Genie_2_C12_1.161000.root";
        g_2261[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/G18/Excl_Range1_Genie_2_C12_2.261000.root";
        g_2261[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/G18/Incl_Range1_Genie_2_C12_2.261000.root";
        g_2261[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/G18/Excl_Range2_Genie_2_C12_2.261000.root";
        g_2261[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/G18/Incl_Range2_Genie_2_C12_2.261000.root";
        g_2261[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/G18/Excl_Range3_Genie_2_C12_2.261000.root";
        g_2261[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/G18/Incl_Range3_Genie_2_C12_2.261000.root";
        g_2261[3][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/G18/Excl_Range1_Genie_2_C12_4.461000.root";
        g_2261[3][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/G18/Incl_Range1_Genie_2_C12_4.461000.root";

        susa_1161_truereco[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/SuSA/Big_Excl_Range2_Genie_1_C12_1.161000.root";
        susa_1161_truereco[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/SuSA/Big_Incl_Range2_Genie_1_C12_1.161000.root";
        susa_1161_truereco[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/SuSA/Big_Excl_Range3_Genie_1_C12_1.161000.root";
        susa_1161_truereco[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/SuSA/Big_Incl_Range3_Genie_1_C12_1.161000.root";
        susa_2261_truereco[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/SuSA/Big_Excl_Range1_Genie_1_C12_2.261000.root";
        susa_2261_truereco[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/SuSA/Big_Incl_Range1_Genie_1_C12_2.261000.root";
        susa_2261_truereco[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/SuSA/Big_Excl_Range2_Genie_1_C12_2.261000.root";
        susa_2261_truereco[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/SuSA/Big_Incl_Range2_Genie_1_C12_2.261000.root";
        susa_2261_truereco[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/SuSA/Big_Excl_Range3_Genie_1_C12_2.261000.root";
        susa_2261_truereco[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/SuSA/Big_Incl_Range3_Genie_1_C12_2.261000.root";
        susa_2261_truereco[3][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/SuSA/Big_Excl_Range1_Genie_1_C12_4.461000.root";
        susa_2261_truereco[3][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/SuSA/Big_Incl_Range1_Genie_1_C12_4.461000.root";

        susa_1161_true[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/SuSA/Big_Excl_Range2_Genie_1_C12_1.161000.root";
        susa_1161_true[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/SuSA/Big_Incl_Range2_Genie_1_C12_1.161000.root";
        susa_1161_true[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/SuSA/Big_Excl_Range3_Genie_1_C12_1.161000.root";
        susa_1161_true[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/SuSA/Big_Incl_Range3_Genie_1_C12_1.161000.root";
        susa_2261_true[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/SuSA/Big_Excl_Range1_Genie_1_C12_2.261000.root";
        susa_2261_true[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/SuSA/Big_Incl_Range1_Genie_1_C12_2.261000.root";
        susa_2261_true[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/SuSA/Big_Excl_Range2_Genie_1_C12_2.261000.root";
        susa_2261_true[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/SuSA/Big_Incl_Range2_Genie_1_C12_2.261000.root";
        susa_2261_true[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/SuSA/Big_Excl_Range3_Genie_1_C12_2.261000.root";
        susa_2261_true[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/SuSA/Big_Incl_Range3_Genie_1_C12_2.261000.root";
        susa_2261_true[3][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/SuSA/Big_Excl_Range1_Genie_1_C12_4.461000.root";
        susa_2261_true[3][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/SuSA/Big_Incl_Range1_Genie_1_C12_4.461000.root";

        g_1161_truereco[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/G18/Big_Excl_Range2_Genie_2_C12_1.161000.root";
        g_1161_truereco[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/G18/Big_Incl_Range2_Genie_2_C12_1.161000.root";
        g_1161_truereco[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/G18/Big_Excl_Range3_Genie_2_C12_1.161000.root";
        g_1161_truereco[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/G18/Big_Incl_Range3_Genie_2_C12_1.161000.root";
        g_2261_truereco[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/G18/Big_Excl_Range1_Genie_2_C12_2.261000.root";
        g_2261_truereco[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/G18/Big_Incl_Range1_Genie_2_C12_2.261000.root";
        g_2261_truereco[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/G18/Big_Excl_Range2_Genie_2_C12_2.261000.root";
        g_2261_truereco[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/G18/Big_Incl_Range2_Genie_2_C12_2.261000.root";
        g_2261_truereco[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/G18/Big_Excl_Range3_Genie_2_C12_2.261000.root";
        g_2261_truereco[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/G18/Big_Incl_Range3_Genie_2_C12_2.261000.root";
        g_2261_truereco[3][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/G18/Big_Excl_Range1_Genie_2_C12_4.461000.root";
        g_2261_truereco[3][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/G18/Big_Incl_Range1_Genie_2_C12_4.461000.root";

        g_1161_true[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/G18/Big_Excl_Range2_Genie_2_C12_1.161000.root";
        g_1161_true[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/G18/Big_Incl_Range2_Genie_2_C12_1.161000.root";
        g_1161_true[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/G18/Big_Excl_Range3_Genie_2_C12_1.161000.root";
        g_1161_true[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/G18/Big_Incl_Range3_Genie_2_C12_1.161000.root";
        g_2261_true[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/G18/Big_Excl_Range1_Genie_2_C12_2.261000.root";
        g_2261_true[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/G18/Big_Incl_Range1_Genie_2_C12_2.261000.root";
        g_2261_true[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/G18/Big_Excl_Range2_Genie_2_C12_2.261000.root";
        g_2261_true[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/G18/Big_Incl_Range2_Genie_2_C12_2.261000.root";
        g_2261_true[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/G18/Big_Excl_Range3_Genie_2_C12_2.261000.root";
        g_2261_true[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/G18/Big_Incl_Range3_Genie_2_C12_2.261000.root";
        g_2261_true[3][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/G18/Big_Excl_Range1_Genie_2_C12_4.461000.root";
        g_2261_true[3][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/G18/Big_Incl_Range1_Genie_2_C12_4.461000.root";

        susa_1161_truereco_rad[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Rad_Truth_Reco/Big_Excl_Range2_Genie_3_C12_1.161000.root";
        susa_1161_truereco_rad[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Rad_Truth_Reco/Big_Incl_Range2_Genie_3_C12_1.161000.root";
        susa_1161_truereco_rad[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Rad_Truth_Reco/Big_Excl_Range3_Genie_3_C12_1.161000.root";
        susa_1161_truereco_rad[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Rad_Truth_Reco/Big_Incl_Range3_Genie_3_C12_1.161000.root";
        susa_2261_truereco_rad[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Rad_Truth_Reco/Big_Excl_Range1_Genie_3_C12_2.261000.root";
        susa_2261_truereco_rad[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Rad_Truth_Reco/Big_Incl_Range1_Genie_3_C12_2.261000.root";
        susa_2261_truereco_rad[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Rad_Truth_Reco/Big_Excl_Range2_Genie_3_C12_2.261000.root";
        susa_2261_truereco_rad[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Rad_Truth_Reco/Big_Incl_Range2_Genie_3_C12_2.261000.root";
        susa_2261_truereco_rad[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Rad_Truth_Reco/Big_Excl_Range3_Genie_3_C12_2.261000.root";
        susa_2261_truereco_rad[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Rad_Truth_Reco/Big_Incl_Range3_Genie_3_C12_2.261000.root";
        susa_2261_truereco_rad[3][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Rad_Truth_Reco/Big_Excl_Range1_Genie_3_C12_4.461000.root";
        susa_2261_truereco_rad[3][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Rad_Truth_Reco/Big_Incl_Range1_Genie_3_C12_4.461000.root";

        std::string sf_2261_true[3][2];
        std::string sf_2261_truereco[3][2];
        std::string sf_2261[3][2];

        sf_2261[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SF/Excl_Range1_Genie_2_C12_2.261000.root";
        sf_2261[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SF/Incl_Range1_Genie_2_C12_2.261000.root";
        sf_2261[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SF/Excl_Range2_Genie_2_C12_2.261000.root";
        sf_2261[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SF/Incl_Range2_Genie_2_C12_2.261000.root";
        sf_2261[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SF/Excl_Range3_Genie_2_C12_2.261000.root";
        sf_2261[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SF/Incl_Range3_Genie_2_C12_2.261000.root";

        sf_2261_true[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/SF/Excl_Range1_Genie_2_C12_2.261000.root";
        sf_2261_true[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/SF/Excl_Range2_Genie_2_C12_2.261000.root";
        sf_2261_true[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/SF/Excl_Range3_Genie_2_C12_2.261000.root";
        sf_2261_true[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/SF/Incl_Range1_Genie_2_C12_2.261000.root";
        sf_2261_true[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/SF/Incl_Range2_Genie_2_C12_2.261000.root";
        sf_2261_true[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/SF/Incl_Range3_Genie_2_C12_2.261000.root";

        sf_2261_truereco[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/SF/Excl_Range1_Genie_2_C12_2.261000.root";
        sf_2261_truereco[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/SF/Excl_Range2_Genie_2_C12_2.261000.root";
        sf_2261_truereco[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/SF/Excl_Range3_Genie_2_C12_2.261000.root";
        sf_2261_truereco[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/SF/Incl_Range1_Genie_2_C12_2.261000.root";
        sf_2261_truereco[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/SF/Incl_Range2_Genie_2_C12_2.261000.root";
        sf_2261_truereco[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/SF/Incl_Range3_Genie_2_C12_2.261000.root";

        std::string second_en[4][2] = {{"2.261_Excl_Range_1", "2.261_Incl_Range_1"},{"2.261_Excl_Range_2", "2.261_Incl_Range_2"},{ "2.261_Excl_Range_3", "2.261_Incl_Range_3"}, {"4.461_Excl_Range_4", "4.461_Incl_Range_4"}};std::string third_en[1][2] = {{"4.461 Excl Range 1","4.461 Incl Range 1"}}; 

        std::string energies[4] = {"2_261", "2_261", "2_261", "4_461"};

        std::vector<int> r1_sec{2,3,4};
        std::vector<int> r2_sec{0,2,3,4,5};
        std::vector<int> r3_sec{0,2,5};
        std::vector<int> r4_sec{1,2,3};

        std::vector<int> first_sector{2,0,0,1};

        std::map<int,std::vector<int>> sectors;
        sectors[0] = r1_sec;
        sectors[1] = r2_sec;
        sectors[2] = r3_sec;
        sectors[3] = r4_sec;

        std::map<std::string,double> energy_val;
        energy_val["1_161"] = 1.161;
        energy_val["2_261"] = 2.261;
        energy_val["4_461"] = 4.461;

// --------------------- Getting radiative correction histograms from MC ----------------
        TH1D* SuSA_2261_true_reco_rad[4][2][6];

        for(int r = 0; r < 4; r++) {
                for(int p = 0; p < 2; p++) {
                        for(int s : sectors[r]) {
                                if(p == 1) s = (s+3)%6;

                                if(p==0) { // Exclusive
                                        SuSA_2261_true_reco_rad[r][p][s] = (TH1D*)SumProtInts(susa_2261_truereco_rad[r][p], s, false);
                                }
                                if(p==1) { // Inclusive
                                        SuSA_2261_true_reco_rad[r][p][s] = (TH1D*)SumElecInts(susa_2261_truereco_rad[r][p], s, false);
                                }
                                UniversalE4vFunction(SuSA_2261_true_reco_rad[r][p][s],  FSIModelsToLabels["SuSav2_RadCorr_LFGM_Truth_WithFidAcc_UpdatedSchwinger"], "12C", TString::Format("%s", energies[r].c_str()), TString::Format("SuSA 2.261 GeV Rad_%i%i%i",r,p,s+1),r);
                        
                        }
                }
        }

// --------------------- Getting acceptance correction histograms from MC ---------------
        
        //[NRanges][Exclusive = 0, Inclsuive = 1] 

        TH1D* SuSA_2261_true[4][2][6];
        TH1D* SuSA_2261_true_reco[4][2][6];
        TH1D* SF_2261_true[3][2][6];
        TH1D* SF_2261_true_reco[3][2][6];
        TH1D* G_2261_true[4][2][6];
        TH1D* G_2261_true_reco[4][2][6];


        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 4; r++) {
                        for(int s : sectors[r]) {
                                if(p == 1) s = (s+3)%6;

                                if(p==0) { // Exclusive
                                        SuSA_2261_true[r][p][s] = (TH1D*)SumProtInts(susa_2261_true[r][p], s, false);
                                        SuSA_2261_true_reco[r][p][s] = (TH1D*)SumProtInts(susa_2261_truereco[r][p], s, false);
                                        G_2261_true[r][p][s] = (TH1D*)SumProtInts(g_2261_true[r][p], s, false);
                                        G_2261_true_reco[r][p][s] = (TH1D*)SumProtInts(g_2261_truereco[r][p], s, false);
                                        
                                        if(r != 3) {
                                                SF_2261_true[r][p][s] = (TH1D*)SumProtInts(sf_2261_true[r][p], s, false);
                                                SF_2261_true_reco[r][p][s] = (TH1D*)SumProtInts(sf_2261_truereco[r][p], s, false);
                                        }
                                        
                                }
                                if(p==1) { // Inclusive
                                        SuSA_2261_true[r][p][s] = (TH1D*)SumElecInts(susa_2261_true[r][p], s, false);
                                        SuSA_2261_true_reco[r][p][s] = (TH1D*)SumElecInts(susa_2261_truereco[r][p], s, false);
                                        G_2261_true[r][p][s] = (TH1D*)SumElecInts(g_2261_true[r][p], s, false);
                                        G_2261_true_reco[r][p][s] = (TH1D*)SumElecInts(g_2261_truereco[r][p], s, false); 
                                                                           
                                        if(r != 3) {
                                                SF_2261_true[r][p][s] = (TH1D*)SumElecInts(sf_2261_true[r][p], s, false);
                                                SF_2261_true_reco[r][p][s] = (TH1D*)SumElecInts(sf_2261_truereco[r][p], s, false);
                                        }
                                        
                                }
                                
                                UniversalE4vFunction(SuSA_2261_true[r][p][s], FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "12C",TString::Format("%s", energies[r].c_str()), TString::Format("susa_2261_mom_%i%i%i",r,p,s+1),r);
                                UniversalE4vFunction(SuSA_2261_true_reco[r][p][s], FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C",TString::Format("%s", energies[r].c_str()), TString::Format("susa_reco_2261_mom_%i%i%i",r,p,s+1),r);
                                
                                UniversalE4vFunction(G_2261_true[r][p][s], FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithoutFidAcc"], "12C",TString::Format("%s", energies[r].c_str()), TString::Format("g_2261_mom_%i%i%i",r,p,s+1),r);
                                UniversalE4vFunction(G_2261_true_reco[r][p][s], FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C",TString::Format("%s", energies[r].c_str()), TString::Format("g_reco_2261_mom_%i%i%i",r,p,s+1),r);
                                
                                if(r!=3){
                                        UniversalE4vFunction(SF_2261_true[r][p][s], "SF", "12C",TString::Format("%s", energies[r].c_str()), TString::Format("SF_2261_mom_%i%i%i",r,p,s+1),r);
                                        UniversalE4vFunction(SF_2261_true_reco[r][p][s], "SF", "12C",TString::Format("%s", energies[r].c_str()), TString::Format("SF_reco_2261_mom_%i%i%i",r,p,s+1),r);
                                }
                                
                        }
                }
        }
        

// --------------------- Getting MC exclusive and inclusive measurements and mec/neutron corrections ----------------

        //[NRanges][Exclusive = 0, Inclsuive = 1]     
        
        // Get the exclusive and inclusive SuSA predictions as well as MEC corrections
        // neutron corrections to apply to data from G18
        // neutron corrections to apply to MEC from SuSA


        double MEC_uncertainty = .25;

        TH1D* SuSA_2261[4][2][6];
        TH1D* SF_2261[3][2][6];
        TH1D* G_2261[4][2][6];
        double mec_corr_2261[4][2][6][3];
        double mec_corr_G_2261[4][2][6];
        double mec_corr_tot_2261[4][2];
        double mec_corr_tot_G_2261[4][2];
        double neutron_corr_2261_G18[4][2];
        double neutron_corr_2261_susa[4][2];
        double neutron_corr_2261_sf[3][2];

        double mec_corr_2261_true[4][2][6];
        double mec_corr_2261_G_true[4][2][6];


        for(int p = 0; p < 2; p++) {

                for(int r = 0; r < 4; r++) {
                        //std::cout<< "Neutron and MEC corrections for " << second_en[r][p] << "\n"; 
                        if(p == 0) {
                                neutron_corr_2261_susa[r][p] = get_Neutron_corr(susa_2261[r][p], false);
                                neutron_corr_2261_G18[r][p] = get_Neutron_corr(g_2261[r][p], false);
                                if(r!=3) {
                                        neutron_corr_2261_sf[r][p] = get_Neutron_corr(sf_2261[r][p], false);
                                }
                                mec_corr_tot_2261[r][p] = get_MEC_corr_overall(susa_2261[r][p], false);
                                mec_corr_tot_G_2261[r][p] = get_MEC_corr_overall(g_2261[r][p], false);
                        }
                        if(p == 1) {
                                neutron_corr_2261_susa[r][p] = get_Neutron_corr(susa_2261[r][p], true);
                                neutron_corr_2261_G18[r][p] = get_Neutron_corr(g_2261[r][p], true); 
                                if(r!=3) {
                                        neutron_corr_2261_sf[r][p] = get_Neutron_corr(sf_2261[r][p], true);
                                }
                                mec_corr_tot_2261[r][p] = get_MEC_corr_overall(susa_2261[r][p], true);
                                mec_corr_tot_G_2261[r][p] = get_MEC_corr_overall(g_2261[r][p], true);
                        }
                        //std::cout << "G18 N: " << neutron_corr_2261_G18[r][p] << ", MEC: " << mec_corr_tot_G_2261[r][p] << "\n";
                        //std::cout << "SuSA N: " << neutron_corr_2261_susa[r][p] << ", MEC: " << mec_corr_tot_2261[r][p] << "\n";
                        //if(r!=3)std::cout << "SF N: " << neutron_corr_2261_sf[r][p] << "\n";
                
                        for(int s : sectors[r]) {
                                if(p==1) s = (s+3)%6;
                                if(p==0) { // Exclusive
                                        SuSA_2261[r][p][s] = (TH1D*)SumProtInts(susa_2261[r][p], s, false);
                                        if(r!=3){
                                                SF_2261[r][p][s] = (TH1D*)SumProtInts(sf_2261[r][p], s, false);
                                        }
                                        G_2261[r][p][s] = (TH1D*)SumProtInts(g_2261[r][p], s, false);
                                        mec_corr_2261[r][p][s][1] = get_MEC_corr(susa_2261[r][p], s, false);
                                        mec_corr_G_2261[r][p][s] = get_MEC_corr(g_2261[r][p], s, false);

                                        mec_corr_2261_true[r][p][s] = get_MEC_corr(susa_2261_true[r][p], s, false);
                                        mec_corr_2261_G_true[r][p][s] = get_MEC_corr(g_2261_true[r][p], s, false);
                                        std::cout << "Mec truth correction = " << mec_corr_2261_true[r][p][s] << "\n";
                                        
                                        mec_corr_2261[r][p][s][0] = (1 - MEC_uncertainty)*mec_corr_2261[r][p][s][1];
                                        mec_corr_2261[r][p][s][2] = (1 + MEC_uncertainty)*mec_corr_2261[r][p][s][1]; 
                                        
                                        
                                }
                                if(p==1) { // Inclusive
                                        SuSA_2261[r][p][s] = (TH1D*)SumElecInts(susa_2261[r][p], s, false);                                        
                                        if(r!=3){
                                                SF_2261[r][p][s] = (TH1D*)SumElecInts(sf_2261[r][p], s, false);
                                        }
                                        G_2261[r][p][s] = (TH1D*)SumElecInts(g_2261[r][p], s, false);
                                        mec_corr_2261[r][p][s][1] = get_MEC_corr(susa_2261[r][p], s, true);
                                        mec_corr_G_2261[r][p][s] = get_MEC_corr(g_2261[r][p], s, true);


                                        mec_corr_2261_true[r][p][s] = get_MEC_corr(susa_2261_true[r][p], s, true);
                                        mec_corr_2261_G_true[r][p][s] = get_MEC_corr(g_2261_true[r][p], s, true);
                                        
                                        std::cout << "Mec truth correction = " << mec_corr_2261_true[r][p][s] << "\n";

                                        mec_corr_2261[r][p][s][0] = (1 - MEC_uncertainty)*mec_corr_2261[r][p][s][1];
                                        mec_corr_2261[r][p][s][2] = (1 + MEC_uncertainty)*mec_corr_2261[r][p][s][1];
                                }
                                
                                if(r!=3) {
                                        //std::cout << "SF integral before = " << SF_2261[r][p][s]->Integral(1, SF_2261[r][p][s]->GetNbinsX(), "width") << "\n";
                                        //Absolutely normalize SF sample for ratio with Data
                                        UniversalE4vFunction(SF_2261[r][p][s], "SF", "12C", TString::Format("%s",energies[r].c_str()), TString::Format("SF_%s_mom_reco_%i%i%i",energies[r].c_str(),r,p,s+1),r);
                                        //std::cout << "SF integral after = " << SF_2261[r][p][s]->Integral(1, SF_2261[r][p][s]->GetNbinsX(), "width") << "\n";
                                }
                        }
                }
        }
        

// --------------------- Getting Data exclusive and inclusive measurements ----------------

        // Here we will also scale the data
        TH1D* Data_2261[4][2][6];
        TH1D* Data_SF_2261[4][2][6];

        for(int r = 0; r < 4; r++) {
                for(int p = 0; p < 2; p++) {
                        for(int s : sectors[r]) {

                                if(p ==1) s=(s+3)%6;
                                if(p == 0) { // Exclusive
                                        Data_2261[r][p][s] = (TH1D*)SumProtInts(data_2261[r][p], s, true);
                                        Data_SF_2261[r][p][s] = (TH1D*)SumProtInts(data_2261[r][p], s, true);
                                }
                                if(p == 1) { // Inclusive

                                        Data_2261[r][p][s] = (TH1D*)SumElecInts(data_2261[r][p], s, true);
                                        Data_SF_2261[r][p][s] = (TH1D*)SumElecInts(data_2261[r][p], s, true);
                                }
                                
                                //std::cout << "Data SF integral before = " << Data_SF_2261[r][p][s]->Integral(1, Data_SF_2261[r][p][s]->GetNbinsX(), "width") << "\n";
                                //std::cout << "Data integral before = " << Data_2261[r][p][s]->Integral(1, Data_2261[r][p][s]->GetNbinsX(), "width") << "\n";
                                UniversalE4vFunction(Data_SF_2261[r][p][s], "Pinned Data", "12C", TString::Format("%s",energies[r].c_str()), TString::Format("Data_SF_%s_mom_reco_%i%i%i",energies[r].c_str(),r,p,s+1),r);
                                //std::cout << "Data SF integral after = " << Data_SF_2261[r][p][s]->Integral(1, Data_SF_2261[r][p][s]->GetNbinsX(), "width") << "\n";
                                //std::cout << "Data SF integral after = " << Data_2261[r][p][s]->Integral(1, Data_2261[r][p][s]->GetNbinsX(), "width") << "\n";

                        }
                }
        }

// ---------------- Acceptance correct all histograms ---------------------
        /*
        TCanvas *ca = new TCanvas("corrections can"," corrections can",800,800);
        if(make_plots) {
                
                ca->SaveAs("12C_true_vs_truereco.pdf(");
                ca->SaveAs("12C_truerecorad_vs_truereco.pdf(");
                ca->SaveAs("12C_Acceptance_Ratios.pdf(");
                ca->SaveAs("12C_Rad_Ratios.pdf(");
        }
        */
        
        
        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 4; r++) {

                        //2261
                        for(int s : sectors[r])  {

                                if(p == 1) s = (s+3)%6;
                                SuSA_2261[r][p][s]->SetTitle(TString::Format("%s_Sector_%i",second_en[r][p].c_str(),s+1));
                                G_2261[r][p][s]->SetTitle(TString::Format("%s_Sector_%i",second_en[r][p].c_str(),s+1));
                                Data_2261[r][p][s]->SetTitle(TString::Format("%s_Sector_%i",second_en[r][p].c_str(),s+1));
                                Data_SF_2261[r][p][s]->SetTitle(TString::Format("SF_%s_Sector_%i",second_en[r][p].c_str(),s+1));
                                
                                if(r != 3) {
                                        SF_2261[r][p][s]->SetTitle(TString::Format("%s_Sector_%i",second_en[r][p].c_str(),s+1));
                                        SF_2261[r][p][s] = (TH1D*)AcceptanceCorrect(SF_2261[r][p][s], SuSA_2261_true[r][p][s], SuSA_2261_true_reco[r][p][s], G_2261_true[r][p][s], G_2261_true_reco[r][p][s], SuSA_2261_true_reco_rad[r][p][s], false, "SF", "12C", SF_2261_true[r][p][s], SF_2261_true_reco[r][p][s]);
                                }

                                Data_SF_2261[r][p][s] = (TH1D*)AcceptanceCorrect(Data_SF_2261[r][p][s], SuSA_2261_true[r][p][s], SuSA_2261_true_reco[r][p][s], G_2261_true[r][p][s], G_2261_true_reco[r][p][s], SuSA_2261_true_reco_rad[r][p][s], false, "data", "12C");
                                Data_2261[r][p][s] = (TH1D*)AcceptanceCorrect(Data_2261[r][p][s], SuSA_2261_true[r][p][s], SuSA_2261_true_reco[r][p][s], G_2261_true[r][p][s], G_2261_true_reco[r][p][s], SuSA_2261_true_reco_rad[r][p][s], false, "data", "12C");
                                SuSA_2261[r][p][s] = (TH1D*)AcceptanceCorrect(SuSA_2261[r][p][s], SuSA_2261_true[r][p][s], SuSA_2261_true_reco[r][p][s], G_2261_true[r][p][s], G_2261_true_reco[r][p][s], SuSA_2261_true_reco_rad[r][p][s], make_plots, "SuSA", "12C");
                                G_2261[r][p][s] = (TH1D*)AcceptanceCorrect(G_2261[r][p][s], SuSA_2261_true[r][p][s], SuSA_2261_true_reco[r][p][s], G_2261_true[r][p][s], G_2261_true_reco[r][p][s], SuSA_2261_true_reco_rad[r][p][s], false, "G", "12C");
                        }
                }
        }
        
        
        
        /*
        if(make_plots) {
                ca->SaveAs("12C_true_vs_truereco.pdf)");
                ca->SaveAs("12C_truerecorad_vs_truereco.pdf)");
                ca->SaveAs("12C_Acceptance_Ratios.pdf)");
                ca->SaveAs("12C_Rad_Ratios.pdf)");
        }*/

// ---------------- Get average proton momentum for data and MC ------------------------

        double data_avg_prot_mom_1161[2][6];
        double data_avg_prot_mom_2261[4][6];

        double SuSA_avg_prot_mom_1161[2][6];
        double SuSA_avg_prot_mom_2261[4][6];

        double SF_avg_prot_mom_2261[3][6];

        double G_avg_prot_mom_1161[2][6];
        double G_avg_prot_mom_2261[4][6];

        for(int r = 0; r < 4; r++) {
                for(int s : sectors[r]) {
                        data_avg_prot_mom_2261[r][s] = weighted_average(Data_2261[r][0][s]); 
                        SuSA_avg_prot_mom_2261[r][s] = weighted_average(SuSA_2261_true[r][0][s]); 
                        if(r!=3){
                                SF_avg_prot_mom_2261[r][s] = weighted_average(SF_2261[r][0][s]);
                        }
                        G_avg_prot_mom_2261[r][s] = weighted_average(G_2261_true[r][0][s]); 
                }
        }

// -------------- Add systematic uncertainties ---------------------------

        
        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 4; r++) {

                        //2261
                        for(int s : sectors[r]) {
                                if(p == 1) s = (s+3)%6;
                                ApplySystUnc(Data_2261[r][p][s],TString::Format("%s",energies[r].c_str())); 
                                ApplySystUnc(Data_SF_2261[r][p][s],TString::Format("%s",energies[r].c_str()));
                        }
                }
        }

// -------------- Correct for MEC and neutron contamination --------------
        //Correct Data by (1-(MECfrac))*(G18_prot/(G18_prot + G18_neut))
        //Correct MC by (1-(MECfrac))*(SuSA_prot/(SuSA_prot + SuSA_neut))


        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 4; r++) {

                        //2261
                        for(int s : sectors[r]) {
                                if(p == 1) s = (s+3)%6;

                                ApplyMECcorr(*Data_2261[r][p][s], mec_corr_2261[r][p][s]);
                                ApplyMECcorr(*Data_SF_2261[r][p][s], mec_corr_2261[r][p][s]);

                                SuSA_2261_true[r][p][s]->Scale((1. - mec_corr_2261_true[r][p][s]));
                                G_2261_true[r][p][s]->Scale((1. - mec_corr_2261_G_true [r][p][s]));
                                
                                if(p == 1) {  
                                        SuSA_2261_true[r][p][s]->Scale(neutron_corr_2261_susa[r][p]);
                                        Data_2261[r][p][s]->Scale(neutron_corr_2261_G18[r][p]);
                                        G_2261_true[r][p][s]->Scale(neutron_corr_2261_G18[r][p]);
                                        Data_SF_2261[r][p][s]->Scale(neutron_corr_2261_G18[r][p]);
                                        if(r!=3){ 
                                                SF_2261[r][p][s]->Scale(neutron_corr_2261_sf[r][p]);
                                                
                                        }
                                }
                        }
                }
        }

//Combine histograms to get overall average proton momentum
        TH1D* Data_comb_2261[4][2];
        TH1D* Data_SF_comb_2261[4][2];
        TH1D* SuSA_comb_1161[2][2];
        TH1D* SuSA_comb_2261[4][2];
        TH1D* SF_comb_2261[3][2];
        TH1D* G_comb_1161[2][2];
        TH1D* G_comb_2261[4][2];
        
        for(int p = 0; p < 2; p++ ) {

                for(int r = 0; r < 4; r++) {
                        //Make fake histograms so we can add all of the sectors up, probably a better way to do this
                        Data_comb_2261[r][p] = new TH1D(TString::Format("data %s",second_en[r][p].c_str()),TString::Format("data %s",second_en[r][p].c_str()),150, 0., 6.);
                        Data_SF_comb_2261[r][p] = new TH1D(TString::Format("Data SF %s",second_en[r][p].c_str()),TString::Format("Data SF %s",second_en[r][p].c_str()),150, 0., 6.);
                        
                        SuSA_comb_2261[r][p] = new TH1D(TString::Format("SuSA %s",second_en[r][p].c_str()),TString::Format("SuSA %s",second_en[r][p].c_str()),150, 0., 6.);
                        G_comb_2261[r][p] = new TH1D(TString::Format("G %s",second_en[r][p].c_str()),TString::Format("G %s",second_en[r][p].c_str()),150, 0., 6.);
                        
                        
                        if(r!=3) {
                                SF_comb_2261[r][p] = new TH1D(TString::Format("SF %s",second_en[r][p].c_str()),TString::Format("SF %s",second_en[r][p].c_str()),150, 0., 6.);
                        }
                        for(int s : sectors[r] ){
                                if(p == 1) s = (s+3)%6;

                                Data_comb_2261[r][p]->Add( Data_2261[r][p][s] );
                                SuSA_comb_2261[r][p]->Add( SuSA_2261_true[r][p][s] );
                                G_comb_2261[r][p]->Add( G_2261_true[r][p][s] );
                                Data_SF_comb_2261[r][p]->Add(Data_SF_2261[r][p][s]);
                                if(r!=3) {
                                        SF_comb_2261[r][p]->Add( SF_2261[r][p][s] );          
                                }
                        }
                }       
        }

        double data_comb_int_2261[4][2];
        double data_comb_int_2261_err[4][2];

        double data_SF_comb_int_2261[3][2];
        double data_SF_comb_int_2261_err[3][2];

        double SuSA_comb_int_2261[4][2];
        double SuSA_comb_int_2261_err[4][2];

        double SF_comb_int_2261[3][2];
        double SF_comb_int_2261_err[3][2];

        double G_comb_int_2261[4][2];
        double G_comb_int_2261_err[4][2];

        for(int p = 0; p < 2; p++) {
                /*
                for(int r = 0; r < 2; r++) {
                        data_comb_int_1161[r][p] = Data_comb_1161[r][p]->IntegralAndError(1, Data_comb_1161[r][p]->GetNbinsX(), data_comb_int_1161_err[r][p],"width");
                        SuSA_comb_int_1161[r][p] = SuSA_comb_1161[r][p]->IntegralAndError(1, SuSA_comb_1161[r][p]->GetNbinsX(), SuSA_comb_int_1161_err[r][p],"width");
                        G_comb_int_1161[r][p] = G_comb_1161[r][p]->IntegralAndError(1, G_comb_1161[r][p]->GetNbinsX(), G_comb_int_1161_err[r][p],"width");
                                std::cout << "Data " << first_en[r][p] << " = " << data_comb_int_1161[r][p] << " p/m " << data_comb_int_1161_err[r][p] << "\n";
                                std::cout << "SuSA " << first_en[r][p] << " = " << SuSA_comb_int_1161[r][p] << " p/m " << SuSA_comb_int_1161_err[r][p] << "\n";
                                std::cout << "G    " << first_en[r][p] << " = " << G_comb_int_1161[r][p] << " p/m " << G_comb_int_1161_err[r][p] << "\n";
                }
                */
                for(int r = 0; r < 4; r++) {
                        SuSA_comb_int_2261[r][p] = SuSA_comb_2261[r][p]->IntegralAndError(1, SuSA_comb_2261[r][p]->GetNbinsX(), SuSA_comb_int_2261_err[r][p],"width");
                        G_comb_int_2261[r][p] = G_comb_2261[r][p]->IntegralAndError(1, G_comb_2261[r][p]->GetNbinsX(), G_comb_int_2261_err[r][p],"width");
                        data_comb_int_2261[r][p] = Data_comb_2261[r][p]->IntegralAndError(1, Data_comb_2261[r][p]->GetNbinsX(), data_comb_int_2261_err[r][p],"width"); 
                        

                        if(r!=3) {
                                SF_comb_int_2261[r][p] = SF_comb_2261[r][p]->IntegralAndError(1, SF_comb_2261[r][p]->GetNbinsX(), SF_comb_int_2261_err[r][p],"width");
                                
                                data_SF_comb_int_2261[r][p] = Data_SF_comb_2261[r][p]->IntegralAndError(1, Data_SF_comb_2261[r][p]->GetNbinsX(), data_SF_comb_int_2261_err[r][p],"width");
                                
                        }                
                }
        }

        double data_comb_avg_prot_mom_1161[2];
        double data_comb_avg_prot_mom_2261[4];

        double SuSA_comb_avg_prot_mom_1161[2];
        double SuSA_comb_avg_prot_mom_2261[4];

        double SF_comb_avg_prot_mom_2261[3];

        double G_comb_avg_prot_mom_1161[2];
        double G_comb_avg_prot_mom_2261[4];

        //data_comb_avg_prot_mom_1161[0] = weighted_average(Data_comb_1161[0][0]); 
        //data_comb_avg_prot_mom_1161[1] = weighted_average(Data_comb_1161[1][0]);
        data_comb_avg_prot_mom_2261[0] = weighted_average(Data_comb_2261[0][0]); 
        data_comb_avg_prot_mom_2261[1] = weighted_average(Data_comb_2261[1][0]); 
        data_comb_avg_prot_mom_2261[2] = weighted_average(Data_comb_2261[2][0]);
        data_comb_avg_prot_mom_2261[3] = weighted_average(Data_comb_2261[3][0]); 

        //SuSA_comb_avg_prot_mom_1161[0] = weighted_average(SuSA_comb_1161[0][0]); 
        //SuSA_comb_avg_prot_mom_1161[1] = weighted_average(SuSA_comb_1161[1][0]);
        SuSA_comb_avg_prot_mom_2261[0] = weighted_average(SuSA_comb_2261[0][0]); 
        SuSA_comb_avg_prot_mom_2261[1] = weighted_average(SuSA_comb_2261[1][0]); 
        SuSA_comb_avg_prot_mom_2261[2] = weighted_average(SuSA_comb_2261[2][0]);
        SuSA_comb_avg_prot_mom_2261[3] = weighted_average(SuSA_comb_2261[3][0]); 


        SF_comb_avg_prot_mom_2261[0] = weighted_average(SF_comb_2261[0][0]); 
        SF_comb_avg_prot_mom_2261[1] = weighted_average(SF_comb_2261[1][0]); 
        SF_comb_avg_prot_mom_2261[2] = weighted_average(SF_comb_2261[2][0]);
        
        //G_comb_avg_prot_mom_1161[0] = weighted_average(G_comb_1161[0][0]); 
        //G_comb_avg_prot_mom_1161[1] = weighted_average(G_comb_1161[1][0]);
        G_comb_avg_prot_mom_2261[0] = weighted_average(G_comb_2261[0][0]); 
        G_comb_avg_prot_mom_2261[1] = weighted_average(G_comb_2261[1][0]); 
        G_comb_avg_prot_mom_2261[2] = weighted_average(G_comb_2261[2][0]);
        G_comb_avg_prot_mom_2261[3] = weighted_average(G_comb_2261[3][0]); 

        


// -------------- Integrate sector by sector histograms -----------------


        double data_int_2261[4][2][6];
        double data_int_2261_err[4][2][6];

        double SuSA_int_2261[4][2][6];
        double SuSA_int_2261_err[4][2][6];

        double SF_int_2261[3][2][6];
        double SF_int_2261_err[3][2][6];

        double data_SF_int_2261[3][2][6];
        double data_SF_int_2261_err[3][2][6];

        double G_int_2261[4][2][6];
        double G_int_2261_err[4][2][6];
        
        for(int r = 0; r < 4; r++) {
                for(int p = 0; p < 2; p++) {
 
                        //2261
                        for(int s : sectors[r]) {
                                if(p == 1) s = (s+3)%6;
                                data_int_2261[r][p][s] = Data_2261[r][p][s]->IntegralAndError(1, Data_2261[r][p][s]->GetNbinsX(), data_int_2261_err[r][p][s],"width");
                                SuSA_int_2261[r][p][s] = SuSA_2261_true[r][p][s]->IntegralAndError(1, SuSA_2261_true[r][p][s]->GetNbinsX(), SuSA_int_2261_err[r][p][s],"width");
                                G_int_2261[r][p][s] = G_2261_true[r][p][s]->IntegralAndError(1, G_2261_true[r][p][s]->GetNbinsX(), G_int_2261_err[r][p][s],"width");
                                
                                if(r!=3) {
                                        data_SF_int_2261[r][p][s] = Data_SF_2261[r][p][s]->IntegralAndError(1, Data_SF_2261[r][p][s]->GetNbinsX(), data_SF_int_2261_err[r][p][s],"width");
                                        SF_int_2261[r][p][s] = SF_2261[r][p][s]->IntegralAndError(1, SF_2261[r][p][s]->GetNbinsX(), SF_int_2261_err[r][p][s],"width");
                                }
                        }
                }
        }


// ----------- Take Ratios to obtain transparencies and errors --------------
        //Remember that a proton in sector i corresponds to an electron in sector (i+3%6)

        // Sector by sector data transparencies
        double data_T_1161[2][6];
        double data_T_2261[4][6];
        double data_T_1161_err[2][6];
        double data_T_2261_err[4][6];


        double SF_T_2261[3][6];
        double SF_T_2261_err[3][6];

        double SF_spread_T_2261[3];

        // Spread in data transparencies
        double data_spread_T_1161[2];
        double data_spread_T_2261[4];
        double data_spread_T_1161_err[2];
        double data_spread_T_2261_err[4];

        // Sector by sector susa transparencies
        double SuSA_T_1161[2][6];
        double SuSA_T_2261[4][6];
        double SuSA_T_1161_err[2][6];
        double SuSA_T_2261_err[4][6];

        // Spread in susa transparencies
        double SuSA_spread_T_1161[2];
        double SuSA_spread_T_2261[4];
        double SuSA_spread_T_1161_err[2];
        double SuSA_spread_T_2261_err[4];

        // Sector by sector G18 transparencies
        double G_T_1161[2][6];
        double G_T_2261[4][6];
        double G_T_1161_err[2][6];
        double G_T_2261_err[4][6];

        // Spread in G18 transparencies
        double G_spread_T_1161[2];
        double G_spread_T_2261[4];
        double G_spread_T_1161_err[2];
        double G_spread_T_2261_err[4];

        // Data combined transparencies
        double data_comb_T_1161[2];
        double data_comb_T_2261[4];
        double data_comb_T_1161_err[2];
        double data_comb_T_2261_err[4];

        double SF_comb_T_2261[3];
        double SF_comb_T_2261_err[3];

        // SuSA combined transparencies
        double SuSA_comb_T_1161[2];
        double SuSA_comb_T_2261[4];
        double SuSA_comb_T_1161_err[2];
        double SuSA_comb_T_2261_err[4];

        // G18 combined transparencies
        double G_comb_T_1161[2];
        double G_comb_T_2261[4];
        double G_comb_T_1161_err[2];
        double G_comb_T_2261_err[4];

        int sf_p = 1;

        // Compute transparencies and errors by sector
        for(int r = 0; r < 4; r++) {
                for(int s : sectors[r]) {
                        data_T_2261[r][s] = myratio(data_int_2261[r][0][s],data_int_2261[r][1][(s+3)%6]);

                        data_T_2261_err[r][s] = get_ratio_error(data_int_2261[r][0][s],data_int_2261[r][1][(s+3)%6]);

                        if(r!=3){
                                int d = s;
                                if(sf_p == 1) d = (s+3)%6;
                                SF_T_2261[r][s] = myratio(data_SF_int_2261[r][0][s], SF_int_2261[r][sf_p][d]);
                                SF_T_2261_err[r][s] = get_ratio_error_ind(data_SF_int_2261[r][0][s], data_SF_int_2261_err[r][0][s], SF_int_2261[r][sf_p][d],SF_int_2261_err[r][sf_p][d]);
                                }

                        SuSA_T_2261[r][s] = myratio(SuSA_int_2261[r][0][s],SuSA_int_2261[r][1][(s+3)%6]);
                        
                        SuSA_T_2261_err[r][s] = get_ratio_error(SuSA_int_2261[r][0][s],SuSA_int_2261[r][1][(s+3)%6]);

                        G_T_2261[r][s] = myratio(G_int_2261[r][0][s],G_int_2261[r][1][(s+3)%6]);

                        G_T_2261_err[r][s] = get_ratio_error(G_int_2261[r][0][s],G_int_2261[r][1][(s+3)%6]);
                }

                data_spread_T_2261[r] = weighted_var(data_T_2261[r], data_T_2261_err[r], sectors[r]);
                SuSA_spread_T_2261[r] = weighted_var(SuSA_T_2261[r], SuSA_T_2261_err[r], sectors[r]);
                G_spread_T_2261[r] = weighted_var(G_T_2261[r], G_T_2261_err[r], sectors[r]);
                if(r!=3) SF_spread_T_2261[r] = weighted_var(SF_T_2261[r], SF_T_2261_err[r], sectors[r]);
        }

        // Take sqrt of sector by sector uncertainty and then add them to overall uncertainty 
        //data_spread_T_1161[0] = sqrt(data_spread_T_1161[0]/num_1161_sec);
        //data_spread_T_1161[1] = sqrt(data_spread_T_1161[1]/num_1161_sec);
        for(int r = 0; r < 4; r++) {
                //data_spread_T_2261[r] = sqrt(data_spread_T_2261[r]/sectors[r].size());

                //SuSA_spread_T_1161[0] = sqrt(SuSA_spread_T_1161[0]/num_1161_sec);
                //SuSA_spread_T_1161[1] = sqrt(SuSA_spread_T_1161[1]/num_1161_sec);
                //SuSA_spread_T_2261[r] = sqrt(SuSA_spread_T_2261[r]/sectors[r].size());

                //G_spread_T_1161[0] = sqrt(G_spread_T_1161[0]/num_1161_sec);
                //G_spread_T_1161[1] = sqrt(G_spread_T_1161[1]/num_1161_sec);
                //G_spread_T_2261[r] = sqrt(G_spread_T_2261[r]/sectors[r].size());

                //Get combined transparencies and errors
                //data_comb_T_1161[0] = myratio(data_comb_int_1161[0][0],data_comb_int_1161[0][1]);
                //data_comb_T_1161[1] = myratio(data_comb_int_1161[1][0],data_comb_int_1161[1][1]);
                data_comb_T_2261[r] = myratio(data_comb_int_2261[r][0],data_comb_int_2261[r][1]);

                //data_comb_T_1161_err[0] = get_ratio_error(data_comb_int_1161[0][0],data_comb_int_1161[0][1]);
                //data_comb_T_1161_err[1] = get_ratio_error(data_comb_int_1161[1][0],data_comb_int_1161[1][1]);
                data_comb_T_2261_err[r] = get_ratio_error(data_comb_int_2261[r][0],data_comb_int_2261[r][1]);

                
                if(r!=3){
                        SF_comb_T_2261[r] = myratio(data_SF_comb_int_2261[r][0], SF_comb_int_2261[r][sf_p]);
                        SF_comb_T_2261_err[r] = get_ratio_error_ind(data_SF_comb_int_2261[r][0], data_SF_comb_int_2261_err[r][0], SF_comb_int_2261[r][sf_p], SF_comb_int_2261_err[r][sf_p]);
                }

                //SuSA_comb_T_1161[0] = myratio(SuSA_comb_int_1161[0][0],SuSA_comb_int_1161[0][1]);
                //SuSA_comb_T_1161[1] = myratio(SuSA_comb_int_1161[1][0],SuSA_comb_int_1161[1][1]);
                SuSA_comb_T_2261[r] = myratio(SuSA_comb_int_2261[r][0],SuSA_comb_int_2261[r][1]);

                //SuSA_comb_T_1161_err[0] = get_ratio_error(SuSA_comb_int_1161[0][0],SuSA_comb_int_1161[0][1]);
                //SuSA_comb_T_1161_err[1] = get_ratio_error(SuSA_comb_int_1161[1][0],SuSA_comb_int_1161[1][1]);
                SuSA_comb_T_2261_err[r] = get_ratio_error(SuSA_comb_int_2261[r][0],SuSA_comb_int_2261[r][1]);

                //G_comb_T_1161[0] = myratio(G_comb_int_1161[0][0],G_comb_int_1161[0][1]);
                //G_comb_T_1161[1] = myratio(G_comb_int_1161[1][0],G_comb_int_1161[1][1]);
                G_comb_T_2261[r] = myratio(G_comb_int_2261[r][0],G_comb_int_2261[r][1]);

                //G_comb_T_1161_err[0] = get_ratio_error(G_comb_int_1161[0][0],G_comb_int_1161[0][1]);
               // G_comb_T_1161_err[1] = get_ratio_error(G_comb_int_1161[1][0],G_comb_int_1161[1][1]);
                G_comb_T_2261_err[r] = get_ratio_error(G_comb_int_2261[r][0],G_comb_int_2261[r][1]);
        }


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

        double SF_mc_ypoints[6][3];
        double SF_mc_ypoint_errs[6][3];
        double SF_mc_xpoints[6][3]; 
        double SF_mc_xpoint_errs[6][3];

        // Add all the transparencies by sectors to arrays
        for(int r = 0; r < 4; r++) {
                for(int s : sectors[r]) {
                
                        //ypoints[s][0] = data_T_1161[0][s];
                        //ypoints[s][1] = data_T_1161[1][s];
                        ypoints[s][r] = data_T_2261[r][s];
                        //std::cout << "sector: " << s+1 << " range: " << r << ": " << ypoints[s][r] << "\n";
                        
                        //ypoint_errs[s][0] = data_T_1161_err[0][s];
                        //ypoint_errs[s][1] = data_T_1161_err[1][s];
                        ypoint_errs[s][r] = data_T_2261_err[r][s];
                        
                        //xpoints[s][0] = data_avg_prot_mom_1161[0][s];
                        //xpoints[s][1] = data_avg_prot_mom_1161[1][s];
                        xpoints[s][r] = data_avg_prot_mom_2261[r][s];

                        //std::cout << "Prot mom sector: " << s+1 << " range: " << r << ": " << xpoints[s][r] << "\n";
                        
                        //mc_ypoints[s][0] = SuSA_T_1161[0][s];
                        //mc_ypoints[s][1] = SuSA_T_1161[1][s];
                        mc_ypoints[s][r] = SuSA_T_2261[r][s];

                        //mc_ypoint_errs[s][0] = SuSA_T_1161_err[0][s];
                        //mc_ypoint_errs[s][1] = SuSA_T_1161_err[1][s];
                        mc_ypoint_errs[s][r] = SuSA_T_2261_err[r][s];

                        //G_mc_ypoints[s][0] = G_T_1161[0][s];
                        //G_mc_ypoints[s][1] = G_T_1161[1][s];
                        G_mc_ypoints[s][r] = G_T_2261[r][s];

                        //G_mc_ypoint_errs[s][0] = G_T_1161_err[0][s];
                        //G_mc_ypoint_errs[s][1] = G_T_1161_err[1][s];
                        G_mc_ypoint_errs[s][r] = G_T_2261_err[r][s];

                        if(r!=3) {
                                SF_mc_ypoints[s][r] = SF_T_2261[r][s];
                                SF_mc_ypoint_errs[s][r] = SF_T_2261_err[r][s];
                                SF_mc_xpoint_errs[s][r] = 0.0;
                                SF_mc_xpoints[s][r] = data_avg_prot_mom_2261[r][s];
                        }

                        //mc_xpoints[s][0] = SuSA_avg_prot_mom_1161[0][s];
                        //mc_xpoints[s][1] = SuSA_avg_prot_mom_1161[1][s];
                        mc_xpoints[s][r] = SuSA_avg_prot_mom_2261[r][s];

                        //G_mc_xpoints[s][0] = G_avg_prot_mom_1161[0][s];
                        //G_mc_xpoints[s][1] = G_avg_prot_mom_1161[1][s];
                        G_mc_xpoints[s][r] = G_avg_prot_mom_2261[r][s];



                        xpoint_errs[s][r] = 0.0;
                        mc_xpoint_errs[s][r] = 0.0;
                }
        }

        double comb_ypoints[4] = {data_comb_T_2261[0], data_comb_T_2261[1], data_comb_T_2261[2], data_comb_T_2261[3]};

        //double comb_ypoint_errs[6];
        double comb_ypoint_errs[4];
        //comb_ypoint_errs[0] = sqrt(pow(data_comb_T_1161_err[0],2) + pow(data_spread_T_1161[0],2));
        //comb_ypoint_errs[1] = sqrt(pow(data_comb_T_1161_err[1],2) + pow(data_spread_T_1161[1],2));
        comb_ypoint_errs[0] = sqrt(pow(data_comb_T_2261_err[0],2) + pow(data_spread_T_2261[0],2));
        comb_ypoint_errs[1] = sqrt(pow(data_comb_T_2261_err[1],2) + pow(data_spread_T_2261[1],2));
        comb_ypoint_errs[2] = sqrt(pow(data_comb_T_2261_err[2],2) + pow(data_spread_T_2261[2],2));
        comb_ypoint_errs[3] = sqrt(pow(data_comb_T_2261_err[3],2) + pow(data_spread_T_2261[3],2));

        double comb_xpoints[4] = {data_comb_avg_prot_mom_2261[0], data_comb_avg_prot_mom_2261[1], data_comb_avg_prot_mom_2261[2], data_comb_avg_prot_mom_2261[3]};


        double comb_mc_ypoints[4] = {SuSA_comb_T_2261[0], SuSA_comb_T_2261[1], SuSA_comb_T_2261[2], SuSA_comb_T_2261[3]};

        //double comb_mc_ypoint_errs[6];
        double comb_mc_ypoint_errs[4];
        //comb_mc_ypoint_errs[0] = sqrt(pow(SuSA_comb_T_1161_err[0],2) + pow(SuSA_spread_T_1161[0],2));
        //comb_mc_ypoint_errs[1] = sqrt(pow(SuSA_comb_T_1161_err[1],2) + pow(SuSA_spread_T_1161[1],2));
        comb_mc_ypoint_errs[0] = SuSA_comb_T_2261_err[0];
        comb_mc_ypoint_errs[1] = SuSA_comb_T_2261_err[1];
        comb_mc_ypoint_errs[2] = SuSA_comb_T_2261_err[2];
        comb_mc_ypoint_errs[3] = SuSA_comb_T_2261_err[3];

        double comb_mc_xpoints[4] = {SuSA_comb_avg_prot_mom_2261[0], SuSA_comb_avg_prot_mom_2261[1], SuSA_comb_avg_prot_mom_2261[2], SuSA_comb_avg_prot_mom_2261[3]};

        //double G_comb_mc_ypoints[6] = {G_comb_T_1161[0], G_comb_T_1161[1], G_comb_T_2261[0], G_comb_T_2261[1], G_comb_T_2261[2], G_comb_T_4461[0]};
        double G_comb_mc_ypoints[4] = {G_comb_T_2261[0], G_comb_T_2261[1], G_comb_T_2261[2], G_comb_T_2261[3]};

        //double G_comb_mc_ypoint_errs[6];
        double G_comb_mc_ypoint_errs[4];
        //G_comb_mc_ypoint_errs[0] = sqrt(pow(G_comb_T_2261_err[0],2) + pow(G_spread_T_2261[0],2));
        //G_comb_mc_ypoint_errs[1] = sqrt(pow(G_comb_T_2261_err[1],2) + pow(G_spread_T_2261[1],2));
        G_comb_mc_ypoint_errs[0] = G_comb_T_2261_err[0];
        G_comb_mc_ypoint_errs[1] = G_comb_T_2261_err[1];
        G_comb_mc_ypoint_errs[2] = G_comb_T_2261_err[2];
        G_comb_mc_ypoint_errs[3] = G_comb_T_2261_err[3];

        double G_comb_mc_xpoints[4] = {G_comb_avg_prot_mom_2261[0], G_comb_avg_prot_mom_2261[1], G_comb_avg_prot_mom_2261[2], G_comb_avg_prot_mom_2261[3]};

        //Adding SF
        double SF_comb_mc_ypoints[3] = {SF_comb_T_2261[0], SF_comb_T_2261[1], SF_comb_T_2261[2]};
        double SF_comb_mc_ypoint_errs[3];
        SF_comb_mc_ypoint_errs[0] = sqrt(pow(SF_comb_T_2261_err[0],2) + pow(SF_spread_T_2261[0],2));
        SF_comb_mc_ypoint_errs[1] = sqrt(pow(SF_comb_T_2261_err[1],2) + pow(SF_spread_T_2261[1],2));
        SF_comb_mc_ypoint_errs[2] = sqrt(pow(SF_comb_T_2261_err[2],2) + pow(SF_spread_T_2261[2],2));

        //double G_comb_mc_xpoints[6] = {G_comb_avg_prot_mom_1161[0], G_comb_avg_prot_mom_1161[1],G_comb_avg_prot_mom_2261[0], G_comb_avg_prot_mom_2261[1], G_comb_avg_prot_mom_2261[2], G_comb_avg_prot_mom_4461[0]};
        double SF_comb_mc_xpoints[3] = {data_comb_avg_prot_mom_2261[0], data_comb_avg_prot_mom_2261[1], data_comb_avg_prot_mom_2261[2]};

        //double comb_xpoint_errs[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
        //double comb_mc_xpoint_errs[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
        double comb_xpoint_errs[4] = {0.0,0.0,0.0,0.0};
        double comb_mc_xpoint_errs[4] = {0.0,0.0,0.0,0.0};
        double comb_SF_mc_xpoint_errs[3] = {0.0,0.0,0.0};

        
        TCanvas* c_data;
        c_data = new TCanvas(TString::Format("Data transparency by sector"), TString::Format("Data transparency by sector"), 1200, 1000);
        c_data->SetLeftMargin( 0.2);
        c_data->SetBottomMargin( 0.2);
        c_data->SetRightMargin(0.2);
        c_data->Update();

        TGraphErrors *data_t[6];
        TGraphErrors *data_comb_t;
        //data_comb_t = new TGraphErrors(6, comb_xpoints, comb_ypoints, comb_xpoint_errs, comb_ypoint_errs);
        data_comb_t = new TGraphErrors(4, comb_xpoints, comb_ypoints, comb_xpoint_errs, comb_ypoint_errs);
        PrettyGraph(data_comb_t);
        data_comb_t->SetTitle("Data: All Sectors");
        data_comb_t->GetXaxis()->SetTitle("Proton Momentum (GeV)");
        data_comb_t->GetYaxis()->SetTitle("Transparency");
        data_comb_t->GetYaxis()->SetRangeUser(0,1.0);
        data_comb_t->GetXaxis()->SetRangeUser(0,2.0);
        data_comb_t->SetMarkerColor(12);
        data_comb_t->Draw("AP");
        
        for(int s = 0; s < 6; s++){

                data_t[s] = new TGraphErrors(4, xpoints[s], ypoints[s], xpoint_errs[s], ypoint_errs[s]);
                //data_t[s] = new TGraphErrors(4, xpoints[s], ypoints[s], xpoint_errs[s], ypoint_errs[s]);
                data_t[s]->SetTitle(TString::Format("Sector %i",s+1));
                data_t[s]->GetXaxis()->SetTitle("Proton Momentum (GeV)");
                data_t[s]->GetYaxis()->SetTitle("Transparency");
                data_t[s]->SetMarkerColor(SectorColors[s]);
                PrettyGraph(data_t[s]);
                //if(s == 0) data_t[s]->Draw("AP");
                data_t[s]->Draw("P");
        }
        

        TLegend* dLegend = c_data->BuildLegend(.82,.65,.99,.85);
        dLegend->SetBorderSize(0);

        if(make_plots) c_data->SaveAs("12C/T_12C_Data.pdf");
        
        /*
        TCanvas* sf_data;
        sf_data = new TCanvas(TString::Format("SF transparency by sector"), TString::Format("SF transparency by sector"), 850, 850);
        sf_data->SetLeftMargin( 0.2);
        sf_data->SetBottomMargin( 0.2);
        sf_data->Update();

        TGraphErrors *sf_t[6];
        TGraphErrors *sf_comb_t;
        //data_comb_t = new TGraphErrors(6, comb_xpoints, comb_ypoints, comb_xpoint_errs, comb_ypoint_errs);
        sf_comb_t = new TGraphErrors(3, SF_comb_mc_xpoints, SF_comb_mc_ypoints, comb_SF_mc_xpoint_errs, SF_comb_mc_ypoint_errs);
        PrettyGraph(sf_comb_t);
        sf_comb_t->SetTitle("SF Data: All Sectors");
        sf_comb_t->GetXaxis()->SetTitle("Proton Momentum (GeV)");
        sf_comb_t->GetYaxis()->SetTitle("Transparency");
        sf_comb_t->GetYaxis()->SetRangeUser(0,1.0);
        sf_comb_t->GetXaxis()->SetRangeUser(0,2.0);
        sf_comb_t->SetMarkerColor(12);
        sf_comb_t->Draw("AP");
        
        for(int s = 0; s < 6; s++){

                sf_t[s] = new TGraphErrors(3, SF_mc_xpoints[s], SF_mc_ypoints[s], SF_mc_xpoint_errs[s], SF_mc_ypoint_errs[s]);
                //data_t[s] = new TGraphErrors(4, xpoints[s], ypoints[s], xpoint_errs[s], ypoint_errs[s]);
                sf_t[s]->SetTitle(TString::Format("Sector %i",s+1));
                sf_t[s]->GetXaxis()->SetTitle("Proton Momentum (GeV)");
                sf_t[s]->GetYaxis()->SetTitle("Transparency");
                sf_t[s]->SetMarkerColor(SectorColors[s]);
                PrettyGraph(sf_t[s]);
                //if(s == 0) data_t[s]->Draw("AP");
                sf_t[s]->Draw("P");
        }
        

        TLegend* sfLegend = sf_data->BuildLegend(.65,.65,.85,.85);
        sfLegend->SetBorderSize(0);
        */
        
        
        TCanvas* c_susa;
        c_susa = new TCanvas(TString::Format("SuSA transparency by sector"), TString::Format("SuSA transparency by sector"), 1200, 1000);
        c_susa->SetLeftMargin( 0.2);
        c_susa->SetBottomMargin( 0.2);
        c_susa->SetRightMargin(0.2);
        c_susa->Update();

        TGraphErrors *susa_t[6];
        TGraphErrors *susa_comb_t;
        //susa_comb_t = new TGraphErrors(6, comb_mc_xpoints, comb_mc_ypoints, comb_mc_xpoint_errs, comb_mc_ypoint_errs);
        susa_comb_t = new TGraphErrors(4, comb_mc_xpoints, comb_mc_ypoints, comb_mc_xpoint_errs, comb_mc_ypoint_errs);
        PrettyGraph(susa_comb_t);
        susa_comb_t->SetTitle("SuSAv2: All Sectors");
        susa_comb_t->GetXaxis()->SetTitle("Proton Momentum (GeV)");
        susa_comb_t->GetYaxis()->SetTitle("Transparency");
        susa_comb_t->GetYaxis()->SetRangeUser(0,1.0);
        susa_comb_t->SetMarkerColor(12);
        susa_comb_t->Draw("AP");

        for(int s = 0; s < 6; s++){
                //susa_t[s] = new TGraphErrors(6, mc_xpoints[s], mc_ypoints[s], mc_xpoint_errs[s], mc_ypoint_errs[s]);
                susa_t[s] = new TGraphErrors(4, mc_xpoints[s], mc_ypoints[s], mc_xpoint_errs[s], mc_ypoint_errs[s]);
                susa_t[s]->SetTitle(TString::Format("Sector %i",s+1));
                susa_t[s]->GetXaxis()->SetTitle("Proton Momentum (GeV)");
                susa_t[s]->GetYaxis()->SetTitle("Transparency");
                PrettyGraph(susa_t[s]);
                susa_t[s]->SetMarkerColor(SectorColors[s]);
                susa_t[s]->Draw("P");
        }

        TLegend* sLegend = c_susa->BuildLegend(.82,.65,.99,.85);
        sLegend->SetBorderSize(0);

        if(make_plots)c_susa->SaveAs("12C/T_12C_SuSA.pdf");


        TCanvas* c_g;
        c_g = new TCanvas(TString::Format("G18 transparency by sector"), TString::Format("G18 transparency by sector"), 1200, 1000);
        c_g->SetLeftMargin( 0.2);
        c_g->SetBottomMargin( 0.2);
        c_g->SetRightMargin(0.2);
        c_g->Update();

        TGraphErrors *G_t[6];
        TGraphErrors *G_comb_t;
        //G_comb_t = new TGraphErrors(6, G_comb_mc_xpoints, G_comb_mc_ypoints, comb_mc_xpoint_errs, G_comb_mc_ypoint_errs);
        G_comb_t = new TGraphErrors(4, G_comb_mc_xpoints, G_comb_mc_ypoints, comb_mc_xpoint_errs, G_comb_mc_ypoint_errs);
        PrettyGraph(G_comb_t);
        G_comb_t->SetTitle("G18: All Sectors");
        G_comb_t->GetXaxis()->SetTitle("Proton Momentum (GeV)");
        G_comb_t->GetYaxis()->SetTitle("Transparency");
        G_comb_t->SetMarkerColor(12);
        G_comb_t->GetYaxis()->SetRangeUser(0,1.0);
        G_comb_t->Draw("AP");

        for(int s = 0; s < 6; s++){

                //G_t[s] = new TGraphErrors(6, G_mc_xpoints[s], G_mc_ypoints[s], mc_xpoint_errs[s], G_mc_ypoint_errs[s]);
                G_t[s] = new TGraphErrors(4, G_mc_xpoints[s], G_mc_ypoints[s], mc_xpoint_errs[s], G_mc_ypoint_errs[s]);
                G_t[s]->SetTitle(TString::Format("Sector %i",s+1));
                G_t[s]->GetXaxis()->SetTitle("Proton Momentum (GeV)");
                G_t[s]->GetYaxis()->SetTitle("Transparency");
                G_t[s]->SetMarkerColor(SectorColors[s]);
                PrettyGraph(G_t[s]);
                G_t[s]->Draw("P");
        }
        
        TLegend* gLegend = c_g->BuildLegend(.82,.65,.99,.85);
        gLegend->SetBorderSize(0);

        if(make_plots)c_g->SaveAs("12C/T_12C_G18.pdf");

        TCanvas *c_comb;
        c_comb = new TCanvas(TString::Format("all transparency by sector"), TString::Format("all transparency by sector"), 1200, 1000);
        c_comb->SetLeftMargin( 0.2);
        c_comb->SetBottomMargin( 0.2);
        c_comb->SetRightMargin( 0.2);

        TGraphErrors *G18_trans = (TGraphErrors*)(G_comb_t->Clone());
        TGraphErrors *SuSA_trans = (TGraphErrors*)(susa_comb_t->Clone());
        TGraphErrors *Data_trans = (TGraphErrors*)(data_comb_t->Clone());
        //TGraphErrors *SF_trans = (TGraphErrors*)(sf_comb_t->Clone());
        G18_trans->SetTitle("G18");
        G18_trans->SetMarkerColor(2);
        SuSA_trans->SetTitle("SuSA v2");
        SuSA_trans->SetMarkerColor(4);
        Data_trans->SetTitle("CLAS Data");
        Data_trans->SetMarkerColor(kBlack);
        G18_trans->SetTitle("G18");
        //SF_trans->SetMarkerColor(8);
        //SF_trans->SetTitle("SF");
        G18_trans->Draw("AP");

        SuSA_trans->Draw("P");
        Data_trans->Draw("P");
        //SF_trans->Draw("P");

        TLegend* combLegend = c_comb->BuildLegend(.82,.65,.99,.85);
        combLegend->SetBorderSize(0);

        if(make_plots)c_comb->SaveAs("12C/T_12C_combined.pdf");


        TFile *final = TFile::Open("T_C12_sectors.root", "RECREATE");
        G18_trans->Write("G_C12");
        SuSA_trans->Write("SuSA_C12");
        Data_trans->Write("data_C12");
        final->Close();  
                // ---------------- Make plots of reconstructed momentum distributions for acc corrected data/MC ------------

        if(make_plots) {
                TCanvas* reco_dist_canvas = new TCanvas("reco can","reco can",1200,1000);

                reco_dist_canvas->SetLeftMargin( 0.2);
                reco_dist_canvas->SetBottomMargin( 0.2);
                reco_dist_canvas->SetRightMargin( 0.2);

                //reco_dist_canvas->SaveAs("12C_reco_dist.pdf(");

                //TLegend *leg2261[4][2][6];
                TLegend *leg2261[4][2];

                for(int r = 0; r < 4; r++) {

                        int firstsector = first_sector[r];
                        bool changed_first_sector = false;

                        for(int p = 0; p < 2; p++) {
                                leg2261[r][p] = new TLegend(.82,.65,.99,.85);
                                leg2261[r][p]->SetBorderSize(0);

                                for(int s : sectors[r]) {
                                        if(p == 1) {
                                                s = (s+3)%6; 
                                                if(!changed_first_sector) {
                                                        firstsector = (firstsector+3)%6;
                                                        changed_first_sector = true;
                                                }
                                        }

                                        UniversalE4vFunction(Data_2261[r][p][s], "Pinned Data", "12C", TString::Format("%s",energies[r].c_str()), TString::Format("Data_%s_mom_reco_%i%i%i",energies[r].c_str(),r,p,s+1),r);
                                        PrettyDoubleXSecPlot(Data_2261[r][p][s], p, energy_val[energies[r]], r, true);
                                        //if(s!=firstsector) Data_2261[r][p][s]->Divide(Data_2261[r][p][firstsector]);
                                        Data_2261[r][p][s]->SetMarkerColor(SectorColors[s]);
                                        Data_2261[r][p][s]->SetMarkerStyle(20);
                                        if(s == firstsector) {
                                                TH1D* copy = (TH1D*)(Data_2261[r][p][s]->Clone());
                                                //copy->Divide(Data_2261[r][p][s]);
                                                copy->Draw("e p ");
                                                copy->GetYaxis()->SetRangeUser(0,1.5*copy->GetMaximum());
                                                //copy->GetYaxis()->SetTitle(TString::Format("Ratio to Sector %i", firstsector+1));
                                        }
                                        else Data_2261[r][p][s]->Draw("e p same ");

                                        leg2261[r][p]->AddEntry(Data_2261[r][p][s], TString::Format("Sector %i", s+1));

                                        /*
                                        leg2261[r][p][s] = new TLegend(.82,.65,.99,.85);
                                        leg2261[r][p][s]->SetBorderSize(0);

                                        UniversalE4vFunction(SuSA_2261[r][p][s], FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C", TString::Format("%s",energies[r].c_str()), TString::Format("SuSA_%s_mom_reco_%i%i%i",energies[r].c_str(),r,p,s+1),r);
                                        UniversalE4vFunction(G_2261[r][p][s], FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM"], "12C", TString::Format("%s",energies[r].c_str()), TString::Format("G18_%s_mom_reco_%i%i%i",energies[r].c_str(),r,p,s+1),r);
                                        UniversalE4vFunction(Data_2261[r][p][s], "Pinned Data", "12C", TString::Format("%s",energies[r].c_str()), TString::Format("Data_%s_mom_reco_%i%i%i",energies[r].c_str(),r,p,s+1),r);

                                        PrettyDoubleXSecPlot(SuSA_2261[r][p][s], p, energy_val[energies[r]], r, true);
                                        PrettyDoubleXSecPlot(Data_2261[r][p][s], p, energy_val[energies[r]], r, true);
                                        PrettyDoubleXSecPlot(G_2261[r][p][s], p, energy_val[energies[r]], r, true);
                                        if(r!=3) PrettyDoubleXSecPlot(SF_2261[r][p][s], p, energy_val[energies[r]], r, true);


                                        SuSA_2261[r][p][s]->Draw("e hist");
                                        Data_2261[r][p][s]->Draw("e same");
                                        SuSA_2261[r][p][s]->SetTitle("SuSA_v2 C");
                                        Data_2261[r][p][s]->SetTitle("Data C");
                                        G_2261[r][p][s]->Draw("e hist same");
                                        G_2261[r][p][s]->SetTitle("G18 C12");

                                        /*
                                        if(r!=3) {
                                                SF_2261[r][p][s]->Draw("e hist same");
                                                SF_2261[r][p][s]->SetTitle("SF C");
                                                SF_2261[r][p][s]->SetLineColor(kGreen);
                                        }
                                        */

                                        //findmaxhist(SuSA_2261[r][p][s], Data_2261[r][p][s], G_2261[r][p][s]);
                                        /*
                                        G_2261[r][p][s]->SetLineColor(kRed);
                                        leg2261[r][p][s]->AddEntry(G_2261[r][p][s]);
                                        Data_2261[r][p][s]->SetMarkerColor(kBlack);
                                        Data_2261[r][p][s]->SetMarkerStyle(20);
                                        leg2261[r][p][s]->AddEntry(Data_2261[r][p][s]);
                                        leg2261[r][p][s]->AddEntry(SuSA_2261[r][p][s]);
                                        //if(r!=3)leg2261[r][p][s]->AddEntry(SF_2261[r][p][s]);
                                        leg2261[r][p][s]->Draw();
                                        SuSA_2261[r][p][s]->SetTitle(TString::Format("SuSA_v2 C %s Sector %i", second_en[r][p].c_str(), s+1));
                                        reco_dist_canvas->SaveAs(TString::Format("12C/12C_%s_Sector_%i_xsec.pdf", second_en[r][p].c_str(), s+1));
                                        */
                                }
                                leg2261[r][p]->Draw();
                                reco_dist_canvas->SaveAs(TString::Format("12C/12C_%s_sector_xsec.pdf", second_en[r][p].c_str()));
                        }
                }
                //reco_dist_canvas->SaveAs("12C_reco_dist.pdf)");

                TCanvas* total_reco_dist_canvas = new TCanvas("total reco can","total reco can",1200,1000);

                total_reco_dist_canvas->SetLeftMargin( 0.2);
                total_reco_dist_canvas->SetBottomMargin( 0.2);
                total_reco_dist_canvas->SetRightMargin( 0.2);
                //total_reco_dist_canvas->SaveAs("12C_total_reco_dist.pdf(");


                TLegend *tot_leg2261[4][2];

                for(int r = 0; r < 4; r++) {
                        for (int p = 0; p < 2; p ++) {
                                tot_leg2261[r][p] = new TLegend(.82,.65,.99,.85);
                                tot_leg2261[r][p]->SetBorderSize(0);

                                
                                PrettyDoubleXSecPlot(SuSA_comb_2261[r][p], p, energy_val[energies[r]], r, true);
                                PrettyDoubleXSecPlot(Data_comb_2261[r][p], p, energy_val[energies[r]], r, true);
                                PrettyDoubleXSecPlot(G_comb_2261[r][p], p, energy_val[energies[r]], r, true);
                                if(r!=3)PrettyDoubleXSecPlot(SF_comb_2261[r][p], p, energy_val[energies[r]], r, true);

                                UniversalE4vFunction(SuSA_comb_2261[r][p], FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"], "12C", TString::Format("%s",energies[r].c_str()), TString::Format("SuSA_%s_mom_reco_%i%i",energies[r].c_str(),r,p),r);
                                UniversalE4vFunction(G_comb_2261[r][p], FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM"], "12C", TString::Format("%s",energies[r].c_str()), TString::Format("G18_%s_mom_reco_%i%i",energies[r].c_str(),r,p),r);
                                UniversalE4vFunction(Data_comb_2261[r][p], "Pinned Data", "12C", TString::Format("%s",energies[r].c_str()), TString::Format("Data_%s_mom_reco_%i%i",energies[r].c_str(),r,p),r);


                                SuSA_comb_2261[r][p]->Draw("e hist");
                                G_comb_2261[r][p]->Draw("e hist same");
                                SuSA_comb_2261[r][p]->SetTitle("SuSA_v2 C");
                                G_comb_2261[r][p]->SetTitle("G18 C");

                                /*
                                if(r!=3) {
                                        SF_comb_2261[r][p]->Draw("e hist same");
                                        SF_comb_2261[r][p]->SetTitle("SF C");
                                        SF_comb_2261[r][p]->SetLineColor(kGreen);
                                }
                                */

                                Data_comb_2261[r][p]->Draw("e same");
                                Data_comb_2261[r][p]->SetTitle("Data C");
                                Data_comb_2261[r][p]->SetMarkerColor(kBlack);
                                Data_comb_2261[r][p]->SetMarkerStyle(20);

                                findmaxhist(SuSA_comb_2261[r][p], Data_comb_2261[r][p], G_comb_2261[r][p]);
                                
                                G_comb_2261[r][p]->SetLineColor(kRed);

                                tot_leg2261[r][p]->AddEntry(G_comb_2261[r][p]);
                                tot_leg2261[r][p]->AddEntry(Data_comb_2261[r][p]);
                                tot_leg2261[r][p]->AddEntry(SuSA_comb_2261[r][p]);
                                //if(r!=3)tot_leg2261[r][p]->AddEntry(SF_comb_2261[r][p]);
                                tot_leg2261[r][p]->Draw();
                                
                                SuSA_comb_2261[r][p]->SetTitle(TString::Format("SuSA_v2 C %s", second_en[r][p].c_str()));
                                total_reco_dist_canvas->SaveAs(TString::Format("12C/12C_%s_xsec.pdf", second_en[r][p].c_str()));
                        }
                }
                //total_reco_dist_canvas->SaveAs("12C_total_reco_dist.pdf)");
        }

}




