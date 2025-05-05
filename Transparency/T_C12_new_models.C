#include "myFunctions.h"
#include "T_C12_sectors.h"
#include "transfunctions.h"


void T_C12_new_models(bool make_plots = false) {
        gStyle->SetOptStat(0);
        gStyle->SetOptTitle(0);

        TH1D::SetDefaultSumw2();

       

        susa_2261[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hA_LFG_range1_Genie_1_C12_2.261000.root";
        susa_2261[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hA_LFG_range1_Genie_1_C12_2.261000.root";
        susa_2261[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hA_LFG_range2_Genie_1_C12_2.261000.root";
        susa_2261[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hA_LFG_range2_Genie_1_C12_2.261000.root";
        susa_2261[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hA_LFG_range3_Genie_1_C12_2.261000.root";
        susa_2261[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hA_LFG_range3_Genie_1_C12_2.261000.root";
        susa_2261[3][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hA_LFG_range1_Genie_1_C12_4.461000.root";
        susa_2261[3][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hA_LFG_range1_Genie_1_C12_4.461000.root";

        std::string susa_2261_CFG[4][2];

        susa_2261_CFG[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hA_CFG_range1_Genie_1_C12_2.261000.root";
        susa_2261_CFG[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hA_CFG_range1_Genie_1_C12_2.261000.root";
        susa_2261_CFG[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hA_CFG_range2_Genie_1_C12_2.261000.root";
        susa_2261_CFG[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hA_CFG_range2_Genie_1_C12_2.261000.root";
        susa_2261_CFG[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hA_CFG_range3_Genie_1_C12_2.261000.root";
        susa_2261_CFG[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hA_CFG_range3_Genie_1_C12_2.261000.root";
        susa_2261_CFG[3][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hA_CFG_range1_Genie_1_C12_4.461000.root";
        susa_2261_CFG[3][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hA_CFG_range1_Genie_1_C12_4.461000.root";


        std::string susa_2261_LFG_hN[4][2];

        susa_2261_LFG_hN[0][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hN_LFG_range1_Genie_1_C12_2.261000.root";
        susa_2261_LFG_hN[0][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hN_LFG_range1_Genie_1_C12_2.261000.root";
        susa_2261_LFG_hN[1][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hN_LFG_range2_Genie_1_C12_2.261000.root";
        susa_2261_LFG_hN[1][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hN_LFG_range2_Genie_1_C12_2.261000.root";
        susa_2261_LFG_hN[2][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hN_LFG_range3_Genie_1_C12_2.261000.root";
        susa_2261_LFG_hN[2][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hN_LFG_range3_Genie_1_C12_2.261000.root";
        susa_2261_LFG_hN[3][0] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hN_LFG_range1_Genie_1_C12_4.461000.root";
        susa_2261_LFG_hN[3][1] = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Alternate_models/SuSAv2_hN_LFG_range1_Genie_1_C12_4.461000.root";
       
        std::string second_en[4][2] = {{"2.261_Excl_Range_1", "2.261_Incl_Range_1"},{"2.261_Excl_Range_2", "2.261_Incl_Range_2"},{ "2.261_Excl_Range_3", "2.261_Incl_Range_3"}, {"4.461_Excl_Range_4", "4.461_Incl_Range_4"}};std::string third_en[1][2] = {{"4.461 Excl Range 1","4.461 Incl Range 1"}}; 

        std::string energies[4] = {"2_261", "2_261", "2_261", "4_461"};
        double prot_mom_cuts[4] = {.5,.75,1.1,1.4};
        //double prot_mom_cuts [4] = {0., 0., 0., 0.};
        double offset = -0.00;

        for(int i = 0; i < 4; i++) {
                prot_mom_cuts[i] += offset;
        }

        /*
        std::vector<int> r1_sec{2,3,4};
        std::vector<int> r2_sec{0,2,3,4,5};
        std::vector<int> r3_sec{0,2,5};
        std::vector<int> r4_sec{2,3};
        */


        std::vector<int> r1_sec{0,1,2,3,4,5};
        std::vector<int> r2_sec{0,1,2,3,4,5};
        std::vector<int> r3_sec{0,1,2,3,4,5};
        std::vector<int> r4_sec{0,1,2,3,4,5};

        std::vector<int> first_sector{2,0,0,1};

        std::vector<double> prot_upper_bound{1.2,1.4,1.7,2.0};

        std::map<int,std::vector<int>> sectors;
        sectors[0] = r1_sec;
        sectors[1] = r2_sec;
        sectors[2] = r3_sec;
        sectors[3] = r4_sec;

        std::map<std::string,double> energy_val;
        energy_val["1_161"] = 1.161;
        energy_val["2_261"] = 2.261;
        energy_val["4_461"] = 4.461;



// --------------------- Getting MC exclusive and inclusive measurements and mec/neutron corrections ----------------

        //[NRanges][Exclusive = 0, Inclsuive = 1]     
        
        // Get the exclusive and inclusive SuSA predictions as well as MEC corrections
        // neutron corrections to apply to data from G18
        // neutron corrections to apply to MEC from SuSA



        TH1D* SuSA_2261[4][2][6];
        TH1D* SuSA_2261_CFG[4][2][6];
        TH1D* SuSA_2261_LFG_hN[4][2][6];

        double mec_corr_2261[4][2][6][3];
        double mec_corr_tot_2261[4][2];

        double mec_corr_2261_CFG[4][2][6][3];
        double mec_corr_tot_2261_CFG[4][2];

        double mec_corr_2261_LFG_hN[4][2][6][3];
        double mec_corr_tot_2261_LFG_hN[4][2];

        double neutron_corr_2261_susa[4][2];
        double neutron_corr_2261_susa_CFG[4][2];
        double neutron_corr_2261_susa_LFG_hN[4][2];


        for(int p = 0; p < 2; p++) {

                for(int r = 0; r < 4; r++) {
                        std::cout<< "MEC corrections for " << second_en[r][p] << "\n"; 
                        if(p == 0) {
                                neutron_corr_2261_susa[r][p] = get_Neutron_corr(susa_2261[r][p], false);
                                neutron_corr_2261_susa_CFG[r][p] = get_Neutron_corr(susa_2261_CFG[r][p], false);
                                neutron_corr_2261_susa_LFG_hN[r][p] = get_Neutron_corr(susa_2261_LFG_hN[r][p], false);
                                mec_corr_tot_2261[r][p] = get_MEC_corr_overall(susa_2261[r][p], false, prot_mom_cuts[r]);
                                mec_corr_tot_2261_CFG[r][p] = get_MEC_corr_overall(susa_2261_CFG[r][p], false, prot_mom_cuts[r]);
                                mec_corr_tot_2261_LFG_hN[r][p] = get_MEC_corr_overall(susa_2261_LFG_hN[r][p], false, prot_mom_cuts[r]);
                        }
                        if(p == 1) {
                                neutron_corr_2261_susa[r][p] = get_Neutron_corr(susa_2261[r][p], true);
                                neutron_corr_2261_susa_CFG[r][p] = get_Neutron_corr(susa_2261_CFG[r][p], true);
                                neutron_corr_2261_susa_LFG_hN[r][p] = get_Neutron_corr(susa_2261_LFG_hN[r][p], true);
                                mec_corr_tot_2261[r][p] = get_MEC_corr_overall(susa_2261[r][p], true, prot_mom_cuts[r]);
                                mec_corr_tot_2261_CFG[r][p] = get_MEC_corr_overall(susa_2261_CFG[r][p], true, prot_mom_cuts[r]);
                                mec_corr_tot_2261_LFG_hN[r][p] = get_MEC_corr_overall(susa_2261_LFG_hN[r][p], true, prot_mom_cuts[r]);
                        }
                        std::cout << mec_corr_tot_2261[r][p] << "\n";
                        std::cout << mec_corr_tot_2261_CFG[r][p] << "\n";
                        std::cout << mec_corr_tot_2261_LFG_hN[r][p] << "\n";
                        //if(r!=3)std::cout << "SF N: " << neutron_corr_2261_sf[r][p] << "\n";
                
                        for(int s : sectors[r]) {
                                if(p==1) s = (s+3)%6;
                                if(p==0) { // Exclusive
                                        SuSA_2261[r][p][s] = (TH1D*)SumProtInts(susa_2261[r][p], s, false, prot_mom_cuts[r]);
                                        SuSA_2261_CFG[r][p][s] = (TH1D*)SumProtInts(susa_2261_CFG[r][p], s, false, prot_mom_cuts[r]);
                                        SuSA_2261_LFG_hN[r][p][s] = (TH1D*)SumProtInts(susa_2261_LFG_hN[r][p], s, false, prot_mom_cuts[r]);
                                        mec_corr_2261[r][p][s][1] = get_MEC_corr(susa_2261[r][p], s, false, prot_mom_cuts[r]);
                                        mec_corr_2261_CFG[r][p][s][1] = get_MEC_corr(susa_2261_CFG[r][p], s, false, prot_mom_cuts[r]);
                                        mec_corr_2261_LFG_hN[r][p][s][1] = get_MEC_corr(susa_2261_LFG_hN[r][p], s, false, prot_mom_cuts[r]);
                                        
                                        
                                }
                                if(p==1) { // Inclusive
                                        SuSA_2261[r][p][s] = (TH1D*)SumElecInts(susa_2261[r][p], s, false); 
                                        SuSA_2261_CFG[r][p][s] = (TH1D*)SumElecInts(susa_2261_CFG[r][p], s, false); 
                                        SuSA_2261_LFG_hN[r][p][s] = (TH1D*)SumElecInts(susa_2261_LFG_hN[r][p], s, false); 
                                        mec_corr_2261[r][p][s][1] = get_MEC_corr(susa_2261[r][p], s, true); 
                                        mec_corr_2261_CFG[r][p][s][1] = get_MEC_corr(susa_2261_CFG[r][p], s, true);
                                        mec_corr_2261_LFG_hN[r][p][s][1] = get_MEC_corr(susa_2261_LFG_hN[r][p], s, true);


                                }
                                
                        }
                }
        }
        


// ---------------- Get average proton momentum for data and MC ------------------------

        double SuSA_avg_prot_mom_2261[4][6];
        double SuSA_avg_prot_mom_2261_CFG[4][6];
        double SuSA_avg_prot_mom_2261_LFG_hN[4][6];


        for(int r = 0; r < 4; r++) {
                for(int s : sectors[r]) { 
                        SuSA_avg_prot_mom_2261[r][s] = weighted_average(SuSA_2261[r][0][s]);
                        SuSA_avg_prot_mom_2261_CFG[r][s] = weighted_average(SuSA_2261_CFG[r][0][s]);
                        SuSA_avg_prot_mom_2261_LFG_hN[r][s] = weighted_average(SuSA_2261_LFG_hN[r][0][s]); 
                }
        }

// -------------- Correct for MEC and neutron contamination --------------
        //Correct Data by (1-(MECfrac))*(G18_prot/(G18_prot + G18_neut))
        //Correct MC by (1-(MECfrac))*(SuSA_prot/(SuSA_prot + SuSA_neut))

        double neutron_corr_2261_G18[4][2] = {{0.759,0.759},{0.720,0.720},{0.685,0.685},{0.697,0.697}};


        for(int p = 0; p < 2; p++) {
                for(int r = 0; r < 4; r++) {

                        //2261
                        for(int s : sectors[r]) {
                                if(p == 1) s = (s+3)%6;

                                SuSA_2261[r][p][s]->Scale((1. - mec_corr_2261[r][p][s][1]));
                                SuSA_2261_CFG[r][p][s]->Scale((1. - mec_corr_2261_CFG[r][p][s][1])); 
                                SuSA_2261_LFG_hN[r][p][s]->Scale((1. - mec_corr_2261_LFG_hN[r][p][s][1]));                             

                                if(p == 1) {  
                                        SuSA_2261[r][p][s]->Scale(neutron_corr_2261_G18[r][p]);
                                        SuSA_2261_CFG[r][p][s]->Scale(neutron_corr_2261_G18[r][p]);
                                        SuSA_2261_LFG_hN[r][p][s]->Scale(neutron_corr_2261_G18[r][p]);
                                }

				if(p == 0) {
					std::cout << "Applying neutron correction " << neutron_corr_2261_G18[r][1] << "/" << neutron_corr_2261_susa[r][1] << " = " << neutron_corr_2261_G18[r][1]/neutron_corr_2261_susa[r][1] << "\n";
					SuSA_2261[r][p][s]->Scale(neutron_corr_2261_G18[r][1]/neutron_corr_2261_susa[r][1]);
                                        std::cout << "Applying neutron correction CFG " << neutron_corr_2261_G18[r][1] << "/" << neutron_corr_2261_susa_CFG[r][1] << " = " << neutron_corr_2261_G18[r][1]/neutron_corr_2261_susa_CFG[r][1] << "\n";
                                        SuSA_2261_CFG[r][p][s]->Scale(neutron_corr_2261_G18[r][1]/neutron_corr_2261_susa_CFG[r][1]);
                                        std::cout << "Applying neutron correction LFG hN " << neutron_corr_2261_G18[r][1] << "/" << neutron_corr_2261_susa_LFG_hN[r][1] << " = " << neutron_corr_2261_G18[r][1]/neutron_corr_2261_susa_LFG_hN[r][1] << "\n";
                                        SuSA_2261_LFG_hN[r][p][s]->Scale(neutron_corr_2261_G18[r][1]/neutron_corr_2261_susa_LFG_hN[r][1]);
				}


                        }
                }
        }

//Combine histograms to get overall average proton momentum
        TH1D* SuSA_comb_2261[4][2];
        TH1D* SuSA_comb_2261_CFG[4][2];
        TH1D* SuSA_comb_2261_LFG_hN[4][2];
        
        for(int p = 0; p < 2; p++ ) {

                for(int r = 0; r < 4; r++) {
                        //Make fake histograms so we can add all of the sectors up, probably a better way to do this
                        SuSA_comb_2261[r][p] = new TH1D(TString::Format("SuSA %s",second_en[r][p].c_str()),TString::Format("SuSA %s",second_en[r][p].c_str()),150, 0., 6.);
                        SuSA_comb_2261_CFG[r][p] = new TH1D(TString::Format("SuSA CFG %s",second_en[r][p].c_str()),TString::Format("SuSA CFG %s",second_en[r][p].c_str()),150, 0., 6.);
                        SuSA_comb_2261_LFG_hN[r][p] = new TH1D(TString::Format("SuSA LFG hN %s",second_en[r][p].c_str()),TString::Format("SuSA LFG hN %s",second_en[r][p].c_str()),150, 0., 6.);
                        
                        
                        for(int s : sectors[r] ){
                                if(p == 1) s = (s+3)%6;
                                SuSA_comb_2261[r][p]->Add( SuSA_2261[r][p][s] );
                                SuSA_comb_2261_CFG[r][p]->Add( SuSA_2261_CFG[r][p][s] );
                                SuSA_comb_2261_LFG_hN[r][p]->Add( SuSA_2261_LFG_hN[r][p][s] );
                        }
                }       
        }

        double SuSA_comb_int_2261[4][2];
        double SuSA_comb_int_2261_err[4][2];
        double SuSA_comb_int_2261_CFG[4][2];
        double SuSA_comb_int_2261_err_CFG[4][2];
        double SuSA_comb_int_2261_LFG_hN[4][2];
        double SuSA_comb_int_2261_err_LFG_hN[4][2];


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
                        SuSA_comb_int_2261_CFG[r][p] = SuSA_comb_2261_CFG[r][p]->IntegralAndError(1, SuSA_comb_2261_CFG[r][p]->GetNbinsX(), SuSA_comb_int_2261_err_CFG[r][p],"width");
                        SuSA_comb_int_2261_LFG_hN[r][p] = SuSA_comb_2261_LFG_hN[r][p]->IntegralAndError(1, SuSA_comb_2261_LFG_hN[r][p]->GetNbinsX(), SuSA_comb_int_2261_err_LFG_hN[r][p],"width");
                       

                                
                }
        }

        double SuSA_comb_avg_prot_mom_2261[4];
        double SuSA_comb_avg_prot_mom_2261_CFG[4];
        double SuSA_comb_avg_prot_mom_2261_LFG_hN[4];

        SuSA_comb_avg_prot_mom_2261[0] = weighted_average(SuSA_comb_2261[0][0]); 
        SuSA_comb_avg_prot_mom_2261[1] = weighted_average(SuSA_comb_2261[1][0]); 
        SuSA_comb_avg_prot_mom_2261[2] = weighted_average(SuSA_comb_2261[2][0]);
        SuSA_comb_avg_prot_mom_2261[3] = weighted_average(SuSA_comb_2261[3][0]); 


        SuSA_comb_avg_prot_mom_2261_CFG[0] = weighted_average(SuSA_comb_2261_CFG[0][0]); 
        SuSA_comb_avg_prot_mom_2261_CFG[1] = weighted_average(SuSA_comb_2261_CFG[1][0]); 
        SuSA_comb_avg_prot_mom_2261_CFG[2] = weighted_average(SuSA_comb_2261_CFG[2][0]);
        SuSA_comb_avg_prot_mom_2261_CFG[3] = weighted_average(SuSA_comb_2261_CFG[3][0]); 



        SuSA_comb_avg_prot_mom_2261_LFG_hN[0] = weighted_average(SuSA_comb_2261_LFG_hN[0][0]); 
        SuSA_comb_avg_prot_mom_2261_LFG_hN[1] = weighted_average(SuSA_comb_2261_LFG_hN[1][0]); 
        SuSA_comb_avg_prot_mom_2261_LFG_hN[2] = weighted_average(SuSA_comb_2261_LFG_hN[2][0]);
        SuSA_comb_avg_prot_mom_2261_LFG_hN[3] = weighted_average(SuSA_comb_2261_LFG_hN[3][0]); 


        


// -------------- Integrate sector by sector histograms -----------------


        double SuSA_int_2261[4][2][6];
        double SuSA_int_2261_err[4][2][6];

        double SuSA_int_2261_CFG[4][2][6];
        double SuSA_int_2261_err_CFG[4][2][6];

        double SuSA_int_2261_LFG_hN[4][2][6];
        double SuSA_int_2261_err_LFG_hN[4][2][6];

        
        for(int r = 0; r < 4; r++) {
                for(int p = 0; p < 2; p++) {
 
                        //2261
                        for(int s : sectors[r]) {
                                if(p == 1) s = (s+3)%6;
                                SuSA_int_2261[r][p][s] = SuSA_2261[r][p][s]->IntegralAndError(1, SuSA_2261[r][p][s]->GetNbinsX(), SuSA_int_2261_err[r][p][s],"width");
                                SuSA_int_2261_CFG[r][p][s] = SuSA_2261_CFG[r][p][s]->IntegralAndError(1, SuSA_2261_CFG[r][p][s]->GetNbinsX(), SuSA_int_2261_err_CFG[r][p][s],"width");
                                SuSA_int_2261_LFG_hN[r][p][s] = SuSA_2261_LFG_hN[r][p][s]->IntegralAndError(1, SuSA_2261_LFG_hN[r][p][s]->GetNbinsX(), SuSA_int_2261_err_LFG_hN[r][p][s],"width");
                        }
                }
        }


// ----------- Take Ratios to obtain transparencies and errors --------------
        //Remember that a proton in sector i corresponds to an electron in sector (i+3%6)

        // Sector by sector data transparencies
       
        // Sector by sector susa transparencies
        double SuSA_T_2261[4][6];
        double SuSA_T_2261_err[4][6];

        double SuSA_T_2261_CFG[4][6];
        double SuSA_T_2261_err_CFG[4][6];


        double SuSA_T_2261_LFG_hN[4][6];
        double SuSA_T_2261_err_LFG_hN[4][6];

        // Spread in susa transparencies
        double SuSA_spread_T_2261[4];
        double SuSA_spread_T_2261_err[4];
        double SuSA_spread_T_2261_CFG[4];
        double SuSA_spread_T_2261_err_CFG[4];
        double SuSA_spread_T_2261_LFG_hN[4];
        double SuSA_spread_T_2261_err_LFG_hN[4];

        // SuSA combined transparencies
        double SuSA_comb_T_2261[4];
        double SuSA_comb_T_2261_err[4];
        double SuSA_comb_T_2261_CFG[4];
        double SuSA_comb_T_2261_err_CFG[4];
        double SuSA_comb_T_2261_LFG_hN[4];
        double SuSA_comb_T_2261_err_LFG_hN[4];


        int sf_p = 1;

        // Compute transparencies and errors by sector
        for(int r = 0; r < 4; r++) {
                for(int s : sectors[r]) {
                       
                        SuSA_T_2261[r][s] = myratio(SuSA_int_2261[r][0][s],SuSA_int_2261[r][1][(s+3)%6]);
                        
                        SuSA_T_2261_err[r][s] = get_ratio_error(SuSA_int_2261[r][0][s],SuSA_int_2261[r][1][(s+3)%6],SuSA_int_2261_err[r][0][s],SuSA_int_2261_err[r][1][(s+3)%6]);


                        SuSA_T_2261_CFG[r][s] = myratio(SuSA_int_2261_CFG[r][0][s],SuSA_int_2261_CFG[r][1][(s+3)%6]);
                        
                        SuSA_T_2261_err_CFG[r][s] = get_ratio_error(SuSA_int_2261_CFG[r][0][s],SuSA_int_2261_CFG[r][1][(s+3)%6],SuSA_int_2261_err_CFG[r][0][s],SuSA_int_2261_err_CFG[r][1][(s+3)%6]);

                        SuSA_T_2261_LFG_hN[r][s] = myratio(SuSA_int_2261_LFG_hN[r][0][s],SuSA_int_2261_LFG_hN[r][1][(s+3)%6]);
                        
                        SuSA_T_2261_err_LFG_hN[r][s] = get_ratio_error(SuSA_int_2261_LFG_hN[r][0][s],SuSA_int_2261_LFG_hN[r][1][(s+3)%6],SuSA_int_2261_err_LFG_hN[r][0][s],SuSA_int_2261_err_LFG_hN[r][1][(s+3)%6]);

                        
                }

                SuSA_spread_T_2261[r] = weighted_var(SuSA_T_2261[r], SuSA_T_2261_err[r], sectors[r]);
                SuSA_spread_T_2261_CFG[r] = weighted_var(SuSA_T_2261_CFG[r], SuSA_T_2261_err_CFG[r], sectors[r]);
                SuSA_spread_T_2261_LFG_hN[r] = weighted_var(SuSA_T_2261_LFG_hN[r], SuSA_T_2261_err_LFG_hN[r], sectors[r]);
        }

        for(int r = 0; r < 4; r++) {
                
                SuSA_comb_T_2261[r] = myratio(SuSA_comb_int_2261[r][0],SuSA_comb_int_2261[r][1]);
                SuSA_comb_T_2261_err[r] = get_ratio_error(SuSA_comb_int_2261[r][0],SuSA_comb_int_2261[r][1], SuSA_comb_int_2261_err[r][0],SuSA_comb_int_2261_err[r][1]);


                SuSA_comb_T_2261_CFG[r] = myratio(SuSA_comb_int_2261_CFG[r][0],SuSA_comb_int_2261_CFG[r][1]);
                SuSA_comb_T_2261_err_CFG[r] = get_ratio_error(SuSA_comb_int_2261_CFG[r][0],SuSA_comb_int_2261_CFG[r][1], SuSA_comb_int_2261_err_CFG[r][0],SuSA_comb_int_2261_err_CFG[r][1]);


                SuSA_comb_T_2261_LFG_hN[r] = myratio(SuSA_comb_int_2261_LFG_hN[r][0],SuSA_comb_int_2261_LFG_hN[r][1]);
                SuSA_comb_T_2261_err_CFG[r] = get_ratio_error(SuSA_comb_int_2261_LFG_hN[r][0],SuSA_comb_int_2261_LFG_hN[r][1], SuSA_comb_int_2261_err_LFG_hN[r][0],SuSA_comb_int_2261_err_LFG_hN[r][1]);

        }


// ---------------------------------------------------------------------

        double mc_ypoints[6][4];
        double mc_ypoint_errs[6][4];
        double mc_xpoints[6][4]; 
        double mc_xpoint_errs[6][4];


        double mc_ypoints_CFG[6][4];
        double mc_ypoint_errs_CFG[6][4];
        double mc_xpoints_CFG[6][4]; 
        double mc_xpoint_errs_CFG[6][4];


        double mc_ypoints_LFG_hN[6][4];
        double mc_ypoint_errs_LFG_hN[6][4];
        double mc_xpoints_LFG_hN[6][4]; 
        double mc_xpoint_errs_LFG_hN[6][4];

        // Add all the transparencies by sectors to arrays
        for(int r = 0; r < 4; r++) {
                for(int s : sectors[r]) {
                        
                        mc_ypoints[s][r] = SuSA_T_2261[r][s];
                        mc_ypoint_errs[s][r] = SuSA_T_2261_err[r][s];
                        mc_xpoints[s][r] = SuSA_avg_prot_mom_2261[r][s];
                        mc_xpoint_errs[s][r] = 0.0;


                        mc_ypoints_CFG[s][r] = SuSA_T_2261_CFG[r][s];
                        mc_ypoint_errs_CFG[s][r] = SuSA_T_2261_err_CFG[r][s];
                        mc_xpoints_CFG[s][r] = SuSA_avg_prot_mom_2261_CFG[r][s];
                        mc_xpoint_errs_CFG[s][r] = 0.0;

                        mc_ypoints_LFG_hN[s][r] = SuSA_T_2261_LFG_hN[r][s];
                        mc_ypoint_errs_LFG_hN[s][r] = SuSA_T_2261_err_LFG_hN[r][s];
                        mc_xpoints_LFG_hN[s][r] = SuSA_avg_prot_mom_2261_LFG_hN[r][s];
                        mc_xpoint_errs_LFG_hN[s][r] = 0.0;
                }
        }


        double comb_mc_ypoints[4] = {SuSA_comb_T_2261[0], SuSA_comb_T_2261[1], SuSA_comb_T_2261[2], SuSA_comb_T_2261[3]};

        double comb_mc_ypoints_CFG[4] = {SuSA_comb_T_2261_CFG[0], SuSA_comb_T_2261_CFG[1], SuSA_comb_T_2261_CFG[2], SuSA_comb_T_2261_CFG[3]};

        double comb_mc_ypoints_LFG_hN[4] = {SuSA_comb_T_2261_LFG_hN[0], SuSA_comb_T_2261_LFG_hN[1], SuSA_comb_T_2261_LFG_hN[2], SuSA_comb_T_2261_LFG_hN[3]};

        double comb_mc_ypoint_errs[4];
        double comb_mc_ypoint_errs_CFG[4];
        double comb_mc_ypoint_errs_LFG_hN[4];

        comb_mc_ypoint_errs[0] = SuSA_comb_T_2261_err[0];
        comb_mc_ypoint_errs[1] = SuSA_comb_T_2261_err[1];
        comb_mc_ypoint_errs[2] = SuSA_comb_T_2261_err[2];
        comb_mc_ypoint_errs[3] = SuSA_comb_T_2261_err[3];

        comb_mc_ypoint_errs_CFG[0] = SuSA_comb_T_2261_err_CFG[0];
        comb_mc_ypoint_errs_CFG[1] = SuSA_comb_T_2261_err_CFG[1];
        comb_mc_ypoint_errs_CFG[2] = SuSA_comb_T_2261_err_CFG[2];
        comb_mc_ypoint_errs_CFG[3] = SuSA_comb_T_2261_err_CFG[3];

        comb_mc_ypoint_errs_LFG_hN[0] = SuSA_comb_T_2261_err_LFG_hN[0];
        comb_mc_ypoint_errs_LFG_hN[1] = SuSA_comb_T_2261_err_LFG_hN[1];
        comb_mc_ypoint_errs_LFG_hN[2] = SuSA_comb_T_2261_err_LFG_hN[2];
        comb_mc_ypoint_errs_LFG_hN[3] = SuSA_comb_T_2261_err_LFG_hN[3];

        double comb_mc_xpoints[4] = {SuSA_comb_avg_prot_mom_2261[0], SuSA_comb_avg_prot_mom_2261[1], SuSA_comb_avg_prot_mom_2261[2], SuSA_comb_avg_prot_mom_2261[3]};


        double comb_mc_xpoints_CFG[4] = {SuSA_comb_avg_prot_mom_2261_CFG[0], SuSA_comb_avg_prot_mom_2261_CFG[1], SuSA_comb_avg_prot_mom_2261_CFG[2], SuSA_comb_avg_prot_mom_2261_CFG[3]};

        double comb_mc_xpoints_LFG_hN[4] = {SuSA_comb_avg_prot_mom_2261_LFG_hN[0], SuSA_comb_avg_prot_mom_2261_LFG_hN[1], SuSA_comb_avg_prot_mom_2261_LFG_hN[2], SuSA_comb_avg_prot_mom_2261_LFG_hN[3]};

        double comb_mc_xpoint_errs[4] = {0.0,0.0,0.0,0.0};

        
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

        c_susa->SaveAs("T_12C_SuSA_LFG_HA.pdf");


        TCanvas* c_susa_CFG;
        c_susa_CFG = new TCanvas(TString::Format("SuSA CFG transparency by sector"), TString::Format("SuSA CFG transparency by sector"), 1200, 1000);
        c_susa_CFG->SetLeftMargin( 0.2);
        c_susa_CFG->SetBottomMargin( 0.2);
        c_susa_CFG->SetRightMargin(0.2);
        c_susa_CFG->Update();

        TGraphErrors *susa_t_CFG[6];
        TGraphErrors *susa_comb_t_CFG;
        //susa_comb_t = new TGraphErrors(6, comb_mc_xpoints, comb_mc_ypoints, comb_mc_xpoint_errs, comb_mc_ypoint_errs);
        susa_comb_t_CFG = new TGraphErrors(4, comb_mc_xpoints_CFG, comb_mc_ypoints_CFG, comb_mc_xpoint_errs, comb_mc_ypoint_errs_CFG);
        PrettyGraph(susa_comb_t_CFG);
        susa_comb_t_CFG->SetTitle("SuSAv2 CFG: All Sectors");
        susa_comb_t_CFG->GetXaxis()->SetTitle("Proton Momentum (GeV)");
        susa_comb_t_CFG->GetYaxis()->SetTitle("Transparency");
        susa_comb_t_CFG->GetYaxis()->SetRangeUser(0,1.0);
        susa_comb_t_CFG->SetMarkerColor(12);
        susa_comb_t_CFG->Draw("AP");

        for(int s = 0; s < 6; s++){
                //susa_t[s] = new TGraphErrors(6, mc_xpoints[s], mc_ypoints[s], mc_xpoint_errs[s], mc_ypoint_errs[s]);
                susa_t_CFG[s] = new TGraphErrors(4, mc_xpoints_CFG[s], mc_ypoints_CFG[s], mc_xpoint_errs[s], mc_ypoint_errs_CFG[s]);
                susa_t_CFG[s]->SetTitle(TString::Format("Sector %i",s+1));
                susa_t_CFG[s]->GetXaxis()->SetTitle("Proton Momentum (GeV)");
                susa_t_CFG[s]->GetYaxis()->SetTitle("Transparency");
                PrettyGraph(susa_t_CFG[s]);
                susa_t_CFG[s]->SetMarkerColor(SectorColors[s]);
                susa_t_CFG[s]->Draw("P");
        }

        TLegend* sLegend_CFG = c_susa->BuildLegend(.82,.65,.99,.85);
        sLegend_CFG->SetBorderSize(0);

        c_susa->SaveAs("T_12C_SuSA_CFG_HA.pdf");

        TCanvas* c_susa_LFG_hN;
        c_susa_LFG_hN = new TCanvas(TString::Format("SuSA LFG hN transparency by sector"), TString::Format("SuSA LFG hN transparency by sector"), 1200, 1000);
        c_susa_LFG_hN->SetLeftMargin( 0.2);
        c_susa_LFG_hN->SetBottomMargin( 0.2);
        c_susa_LFG_hN->SetRightMargin(0.2);
        c_susa_LFG_hN->Update();

        TGraphErrors *susa_t_LFG_hN[6];
        TGraphErrors *susa_comb_t_LFG_hN;
        //susa_comb_t = new TGraphErrors(6, comb_mc_xpoints, comb_mc_ypoints, comb_mc_xpoint_errs, comb_mc_ypoint_errs);
        susa_comb_t_LFG_hN = new TGraphErrors(4, comb_mc_xpoints_LFG_hN, comb_mc_ypoints_LFG_hN, comb_mc_xpoint_errs, comb_mc_ypoint_errs_LFG_hN);
        PrettyGraph(susa_comb_t_LFG_hN);
        susa_comb_t_LFG_hN->SetTitle("SuSAv2 LFG hN: All Sectors");
        susa_comb_t_LFG_hN->GetXaxis()->SetTitle("Proton Momentum (GeV)");
        susa_comb_t_LFG_hN->GetYaxis()->SetTitle("Transparency");
        susa_comb_t_LFG_hN->GetYaxis()->SetRangeUser(0,1.0);
        susa_comb_t_LFG_hN->SetMarkerColor(12);
        susa_comb_t_LFG_hN->Draw("AP");

        for(int s = 0; s < 6; s++){
                //susa_t[s] = new TGraphErrors(6, mc_xpoints[s], mc_ypoints[s], mc_xpoint_errs[s], mc_ypoint_errs[s]);
                susa_t_LFG_hN[s] = new TGraphErrors(4, mc_xpoints_LFG_hN[s], mc_ypoints_LFG_hN[s], mc_xpoint_errs[s], mc_ypoint_errs_LFG_hN[s]);
                susa_t_LFG_hN[s]->SetTitle(TString::Format("Sector %i",s+1));
                susa_t_LFG_hN[s]->GetXaxis()->SetTitle("Proton Momentum (GeV)");
                susa_t_LFG_hN[s]->GetYaxis()->SetTitle("Transparency");
                PrettyGraph(susa_t_LFG_hN[s]);
                susa_t_LFG_hN[s]->SetMarkerColor(SectorColors[s]);
                susa_t_LFG_hN[s]->Draw("P");
        }

        TLegend* sLegend_LFG_hN = c_susa->BuildLegend(.82,.65,.99,.85);
        sLegend_LFG_hN->SetBorderSize(0);

        c_susa->SaveAs("T_12C_SuSA_LFG_HN.pdf");


        TCanvas *c_comb;
        c_comb = new TCanvas(TString::Format("all transparency by sector"), TString::Format("all transparency by sector"), 1200, 1000);
        c_comb->SetLeftMargin( 0.2);
        c_comb->SetBottomMargin( 0.2);
        c_comb->SetRightMargin( 0.2);

        TGraphErrors *SuSA_trans = (TGraphErrors*)(susa_comb_t->Clone());
        TGraphErrors *SuSA_trans_CFG = (TGraphErrors*)(susa_comb_t_CFG->Clone());
        TGraphErrors *SuSA_trans_LFG_hN = (TGraphErrors*)(susa_comb_t_LFG_hN->Clone());

        SuSA_trans->SetTitle("SuSAv2 LFG HA");
	SuSA_trans->SetName("SuSAv2 LFG HA");
        SuSA_trans->SetMarkerColor(4);

        SuSA_trans_CFG->SetTitle("SuSAv2 CFG HA");
	SuSA_trans_CFG->SetName("SuSAv2 CFG HA");
        SuSA_trans_CFG->SetMarkerColor(3);

        SuSA_trans_LFG_hN->SetTitle("SuSAv2 LFG HN");
	SuSA_trans_LFG_hN->SetName("SuSAv2 LFG HN");
        SuSA_trans_LFG_hN->SetMarkerColor(2);
        
        SuSA_trans->Draw("AP");
        SuSA_trans_CFG->Draw("P");
        SuSA_trans_LFG_hN->Draw("P");
        
        TLegend* combLegend = c_comb->BuildLegend(.82,.65,.99,.85);
        combLegend->SetBorderSize(0);

        c_comb->SaveAs("T_12C_CFG_LFG_comp.pdf");

	TFile *file = TFile::Open("T_C12_Alternate_models.root", "RECREATE");
	SuSA_trans->Write();
	SuSA_trans_CFG->Write();
	SuSA_trans_LFG_hN->Write();
	file->Close();
	delete file;
	


        TCanvas *c_proton[4];
        for(int r = 0; r < 4; r++) {

                c_proton[r] = new TCanvas(TString::Format("prot mom range %d",r+1), TString::Format("prot mom range %d",r+1), 1000, 800);

                c_proton[r]->SetLeftMargin( 0.2);
                c_proton[r]->SetBottomMargin( 0.2);
                c_proton[r]->SetRightMargin( 0.2);

                SuSA_comb_2261[r][0]->SetLineColor(kBlue);
                SuSA_comb_2261_CFG[r][0]->SetLineColor(kGreen);
                SuSA_comb_2261_LFG_hN[r][0]->SetLineColor(kRed);

                if(r < 3)  {
                        SuSA_comb_2261[r][0]->Scale(1./(17.6e6));
                        SuSA_comb_2261_CFG[r][0]->Scale(1./(80800000));
                        SuSA_comb_2261_LFG_hN[r][0]->Scale(1./(16.8e6));
                }
                else {
                        SuSA_comb_2261[r][0]->Scale(1./(16.8e6));
                        SuSA_comb_2261_CFG[r][0]->Scale(1./(84800000));
                        SuSA_comb_2261_LFG_hN[r][0]->Scale(1./(15.2e6));
                }

                double Energy = r < 3? 2.261 : 4.461;


                double max = SuSA_comb_2261[r][0]->GetMaximum();
                if(SuSA_comb_2261_CFG[r][0]->GetMaximum() > max) max = SuSA_comb_2261_CFG[r][0]->GetMaximum();
                if(SuSA_comb_2261_LFG_hN[r][0]->GetMaximum() > max) max = SuSA_comb_2261_LFG_hN[r][0]->GetMaximum();


                PrettyDoubleXSecPlot(SuSA_comb_2261[r][0], 0, Energy, 1, false);
                PrettyDoubleXSecPlot(SuSA_comb_2261_CFG[r][0], 0, Energy, 1, false);
                PrettyDoubleXSecPlot(SuSA_comb_2261_LFG_hN[r][0], 0, Energy, 1, false);


                SuSA_comb_2261[r][0]->GetYaxis()->SetRangeUser(0.,1.2*max);
                SuSA_comb_2261[r][0]->Draw("HIST");
                SuSA_comb_2261_CFG[r][0]->Draw("HIST SAME");
                SuSA_comb_2261_LFG_hN[r][0]->Draw("HIST SAME");

                c_proton[r]->BuildLegend();
		c_proton[r]->SaveAs(TString::Format("Prot_mom_range_%d_model_comp.png",r+1));
        }

        TCanvas *c_elect[4];
        for(int r = 0; r < 4; r++) {

                c_elect[r] = new TCanvas(TString::Format("elect mom range %d",r+1), TString::Format("elect mom range %d",r+1), 1000, 800);


                c_elect[r]->SetLeftMargin( 0.2);
                c_elect[r]->SetBottomMargin( 0.2);
                c_elect[r]->SetRightMargin( 0.2);

                SuSA_comb_2261[r][1]->SetLineColor(kBlue);
                SuSA_comb_2261_CFG[r][1]->SetLineColor(kGreen);
                SuSA_comb_2261_LFG_hN[r][1]->SetLineColor(kRed);

                if(r < 3)  {
                        SuSA_comb_2261[r][1]->Scale(1./(17.6e6));
                        SuSA_comb_2261_CFG[r][1]->Scale(1./80800000);
                        SuSA_comb_2261_LFG_hN[r][1]->Scale(1./(16.8e6));
                }
                else {
                        SuSA_comb_2261[r][1]->Scale(1./(16.8e6));
                        SuSA_comb_2261_CFG[r][1]->Scale(1./(84800000));
                        SuSA_comb_2261_LFG_hN[r][1]->Scale(1./(15.2e6));
                }

                double max = SuSA_comb_2261[r][1]->GetMaximum();
                if(SuSA_comb_2261_CFG[r][1]->GetMaximum() > max) max = SuSA_comb_2261_CFG[r][1]->GetMaximum();
                if(SuSA_comb_2261_LFG_hN[r][1]->GetMaximum ()> max) max = SuSA_comb_2261_LFG_hN[r][1]->GetMaximum();


                double Energy = r < 3? 2.261 : 4.461;

                PrettyDoubleXSecPlot(SuSA_comb_2261[r][1], 1, Energy, 1, false);
                PrettyDoubleXSecPlot(SuSA_comb_2261_CFG[r][1], 1, Energy, 1, false);
                PrettyDoubleXSecPlot(SuSA_comb_2261_LFG_hN[r][1], 1, Energy, 1, false);

                SuSA_comb_2261[r][1]->GetYaxis()->SetRangeUser(0.,1.2*max);
                SuSA_comb_2261[r][1]->Draw("HIST");
                SuSA_comb_2261_CFG[r][1]->Draw("HIST SAME");
                SuSA_comb_2261_LFG_hN[r][1]->Draw("HIST SAME");


                c_elect[r]->BuildLegend();
		c_elect[r]->SaveAs(TString::Format("Elec_mom_range_%d_model_comp.png",r+1));
        }


        //TFile *final = TFile::Open("T_C12_sectors.root", "RECREATE");
        //G18_trans->Write("G_C12");
        //SuSA_trans->Write("SuSA_C12");
        //Data_trans->Write("data_C12");
        //final->Close();  
                // ---------------- Make plots of reconstructed momentum distributions for acc corrected data/MC ------------
}




