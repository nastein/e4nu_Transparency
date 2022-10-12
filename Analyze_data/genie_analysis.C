// SEARCH THROUGH THIS FILE TO FIND ALL THE 'CODE WARNING' AND 'CODE CAUTION' STATEMENTS BEFORE RUNNING THIS CODE.
//

// Authors: Afroditi Papadopoulou (apapadop), Graham Chambers-Wall (gchamber), Jacob Smith (smithja)
// Date	of Creation: N/A (you could ask Afroditi about this)

#define GENIE_ANALYSIS_C

#include "genie_analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <TProfile.h>
#include <TH1D.h>
#include <TMatrixD.h>
#include <TFile.h>
#include <TMath.h>
#include <exception>
#include <iostream>
#include <fstream>
#include <TLorentzVector.h>
#include <TVectorT.h>
#include <TRandom3.h>
#include <TF1.h>
#include <TH3.h>
#include <TGraph.h>

#include <vector>
#include <iomanip>
#include <sstream>
#include <iostream>

using namespace std;

// -----------------------------------------------------------------------------------------------------------------------------------------------

vector<double> CalculateCalKineVars(double ECal,TLorentzVector FSElectron) {

	vector<double> CalKineVars; CalKineVars.clear();

	TLorentzVector V4_beam_Cal(0,0,ECal,ECal);
	double nu_Cal = -(FSElectron-V4_beam_Cal).E();
	double Q2_Cal = -(FSElectron-V4_beam_Cal).Mag2();
	double x_bjk_Cal = Q2_Cal / (2*m_prot*nu_Cal);
	TVector3 V3_q_Cal = (V4_beam_Cal-FSElectron).Vect();
	double W_var_Cal = TMath::Sqrt((m_prot+nu_Cal)*(m_prot+nu_Cal)-V3_q_Cal*V3_q_Cal);

	CalKineVars.push_back(nu_Cal); // 0-th element: energy transfer using Ecal
	CalKineVars.push_back(Q2_Cal); // 1st element: Q2 using Ecal
	CalKineVars.push_back(x_bjk_Cal); // 2nd element: xB using Ecal
	CalKineVars.push_back(W_var_Cal); // 3rd element: invariant mass using Ecal

	return CalKineVars;

}

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Loading all the constants from Constant.h ( e_mass, m_prot, m_pimi, m_pipl, m_pion, m_neut = 0.939565,
// H3_bind_en, He4_bind_en, C12_bind_en, B_bind_en, He3_bind_en, D2_bind_en, Fe_bind_en, Mn_bind_en)

void genie_analysis::Loop() {

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();

	int NSectors = 6;

	const int NInt = 6; // All Interactions = 0, QE = 1, MEC = 2, RES = 3, DIS = 4, COH = 5

	// ---------------------------------------------------------------------------------------------------------------

	// Apply Cuts

	// Do we want to apply fiducials & the acceptance map weights
	// Do we want a truth level study ? if so, stop ditching sectors

	bool UseAllSectors = fAllSectors;
	bool ApplyFiducials = fFiducials;
	bool ApplyAccWeights = fAccWeights;
	bool ApplyReso = fReso;

	bool TruthLevel1p0piSignalStudy = fSignal;
	bool TruthLevel0piSignalStudy = false;

    bool UsePhiThetaBand = false;

    double PtMax = 0.2; // gchamber: max pt cut (1e1p spectrum)
	double Em_ub = 999999999;
	double theta_pq_cut = 20.;        

	std::cout << "UseAllSectors = " << UseAllSectors << "\n";
    std::cout << "ApplyFiducials = " << ApplyFiducials << "\n";
	std::cout << "ApplyAccWeights = " << ApplyAccWeights << "\n";
    std::cout << "ApplyReso = " << ApplyReso << "\n";
    std::cout << "TruthLevel study = " << TruthLevel1p0piSignalStudy << "\n";

	// ---------------------------------------------------------------------------------------------------------------

	// fchoice = 0 is for analysis of CLAS data while fchoice = 1 is for the analysis of GENIE simulation
	if (fchoice != 4 && fchoice != 3 && fchoice != 2 && fchoice != 1 && fchoice != 0) { // if the user has specified an invalid fchoice, let them know
		std::cout << "This parameter value is not implemented in genie_analysis::Loop(). It should be either 0 or 1. The given value is " << fchoice << std::endl;
		std::exit(0);
	}

	std::map<std::string,double> bind_en;
	std::map<std::string,double> target_mass;
	std::map<std::string,double> residual_target_mass;
	std::map<std::string,double> Ecal_offset; // that might not be necessary for simulation data

	target_name = ftarget; // std string for target name
	en_beam["1161"]=1.161;
	en_beam["2261"]=2.261;
	en_beam["4461"]=4.461; 

	en_beam_Ecal["1161"]=1.161;
	en_beam_Ecal["2261"]=2.261;
	en_beam_Ecal["4461"]=4.461;

	en_beam_Eqe["1161"]= 1.161;
	en_beam_Eqe["2261"]=2.261;
	en_beam_Eqe["4461"]=4.461;

	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntriesFast();
	//nentries = 100000000; // smithja: max for C-12 simulation to not crash
	nentries = 30000000;

	if (nentries < fChain->GetEntriesFast()) { 
		std::cout << "NENTRIES IS LESS THAN THE ACTUAL NUMBER OF EVENTS IN THIS FILE!!!" << "\n";
	}	
	if (nentries > fChain->GetEntriesFast()) {
		nentries = fChain->GetEntriesFast();
	}

	// Resolutions for Smearing for GENIE simulation data
	double reso_p = 0.01; // smearing for the proton
	double reso_e = 0.005; // smearing for the electrons
	double reso_pi = 0.007; //smearing for pions, executive decision by Larry (28.08.19)

	if (!ApplyReso) {  
		reso_p = 0.;
		reso_e = 0.;
		reso_pi = 0;
	}

	// Resolution defined above seems to be insufficient at 1.1 GeV -> tripled it for all particles
	if(fbeam_en == "1161") { reso_p = 3*reso_p; reso_e = 3*reso_e; reso_pi = 3*reso_pi; }

	double Wcut = 2; // cut for all beam energies < 2
	double Q2cut = 0; // cut for 1.1 GeV > 0.1, for 2.2 GeV > 0.4 and 4.4 GeV > 0.8

	const int n_slice = 3; // Stick to the 3 slices
	const double pperp_min[n_slice] = {0.,0.2,0.4};
	const double pperp_max[n_slice] = {0.2,0.4,10.};

	TVector3 V3_rotprot1, V3_rotprot2, V3_rotprot3, V3_rot_pi, V3_rotprot;

	TString E_acc_file;

	if (en_beam[fbeam_en] > 1. && en_beam[fbeam_en] < 2.) { // 1.1 GeV Configuration parameters and cuts
		E_acc_file = "1_161";
		Q2cut = 0.1;
	}

	if (en_beam[fbeam_en] > 2. && en_beam[fbeam_en] < 3.) { // 2.2 GeV Configuration parameters and cuts
		E_acc_file = "2_261";
		Q2cut = 0.4;
	}

	if (en_beam[fbeam_en] > 4. && en_beam[fbeam_en] < 5.) { // 4.4 GeV Configuration parameters and cuts
		E_acc_file = "4_461";
		Q2cut = 0.8;
	}

	// Further constants for binding energies and target masses

	Ecal_offset["3He"]  = 0.004;
	Ecal_offset["4He"]  = 0.005;
	Ecal_offset["C12"]  = 0.005;
	Ecal_offset["56Fe"] = 0.011;

	bind_en["3He"]  = He3_bind_en-D2_bind_en + Ecal_offset["3He"]; // the offset is used to shift the peak to be at 0
	bind_en["4He"]  = He4_bind_en-H3_bind_en + Ecal_offset["4He"];
	bind_en["C12"]  = C12_bind_en-B_bind_en	+ Ecal_offset["C12"];
	bind_en["56Fe"] = Fe_bind_en-Mn_bind_en	+ Ecal_offset["56Fe"];
	bind_en["CH2"]  = C12_bind_en-B_bind_en;

	target_mass["3He"]  = 2 * m_prot+m_neut-He3_bind_en;
	target_mass["4He"]  = 2 * m_prot+2*m_neut-He4_bind_en;
	target_mass["C12"]  = 6 * m_prot+6*m_neut-C12_bind_en;
	target_mass["56Fe"] = 26 * m_prot+30*m_neut-Fe_bind_en;
	target_mass["CH2"]  = 6 * m_prot+6*m_neut-C12_bind_en;

	residual_target_mass["3He"]  = m_prot+m_neut-D2_bind_en;
	residual_target_mass["4He"]  = m_prot+2*m_neut-H3_bind_en;
	residual_target_mass["C12"]  = 5*m_prot+6*m_neut-B_bind_en;
	residual_target_mass["56Fe"] = 25*m_prot+30*m_neut-Mn_bind_en;
	residual_target_mass["CH2"]  = 25*m_prot+30*m_neut-Mn_bind_en;

	// ----------------------------------------------------------------------------------------
	//NOAH :: Remove everything with E_tot in it (calorimetric reconstruction, do not need. 
	//Care about data driven background subtraction (funfction of p_p or p_e))

	TH2F *h2_N_pi_phot[20];

	gRandom = new TRandom3();
	gRandom->SetSeed(10);

	TLorentzVector V4_beam(0,0,en_beam[fbeam_en],en_beam[fbeam_en]);
	TLorentzVector V4_target(0,0,0,target_mass[ftarget]);

	// Acceptance Maps

	TString WhichMap = "e2a_maps";
	TFile* file_acceptance;
	TFile* file_acceptance_p;
	TFile* file_acceptance_pip;
	TFile* file_acceptance_pim;

	TString Target = "12C";
	if (ftarget.c_str() == "3He") { Target = "3He"; }
	if (ftarget.c_str() == "4He") { Target = "4He"; }

	if (fchoice > 0) { // Only need acceptance maps for GENIE simulation
		file_acceptance = TFile::Open(WhichMap+"/"+WhichMap+"_"+Target+"_E_"+E_acc_file+".root");
		file_acceptance_p = TFile::Open(WhichMap+"/"+WhichMap+"_"+Target+"_E_"+E_acc_file+"_p.root");
		file_acceptance_pip = TFile::Open(WhichMap+"/"+WhichMap+"_"+Target+"_E_"+E_acc_file+"_pip.root");
		file_acceptance_pim = TFile::Open(WhichMap+"/"+WhichMap+"_"+Target+"_E_"+E_acc_file+"_pim.root");
	}


	// ---------------------------------------------------------------------------------------------------------------

	double XSecScale = 1.;


	TFile *file_out;
	TString FileName = ""; 

 	t_Run->SetTitle((std::string(fchoice > 0 ? "Genie" : "Data") + "_" + (fchoice > 0 ? std::to_string(fchoice) : "")).c_str());
	t_target->SetTitle(ftarget.c_str());
	t_beam_en->SetVal(en_beam[fbeam_en]);
	//Save these options
    	my_options->Add(t_Run);
    	my_options->Add(t_target);
    	my_options->Add(t_beam_en);

	// Number of Entries
	t_nentries->SetVal(nentries);
        std::cout << "" << "\n";
	FileName = (fFileName+std::string(t_Run->GetTitle()) + "_" +std::string(t_target->GetTitle()) + "_" + std::to_string(t_beam_en->GetVal()) + ".root").c_str();
	file_out = new TFile( FileName, "Recreate");

	// Write out TList of run options see (https://root.cern/doc/master/classTCollection.html#a3992401270fb2383d6d6003b60d81146)
	my_options->Write("Run_Info", TObject::kSingleKey);

	std::cout << "el theta lb: " << t_thetaEl_lb->GetVal() << ", el theta ub: " << t_thetaEl_ub->GetVal() << "\n";
    std::cout << "prot theta lb: " << t_thetaProt_lb->GetVal() << ", prot theta ub: " << t_thetaProt_ub->GetVal() << "\n";
    std::cout << "Apply theta slice prot = " << fApplyThetaSliceProt << "\n";
	std::cout << "prot mom lb: " << t_ProtMom_lb->GetVal() << ",prot mom ub: " << t_ProtMom_ub->GetVal() << "\n";
    std::cout << "Apply mom slice prot = " << fApplyProtMomCut << "\n";
    std::cout << "Apply phi opening angle cut on electrons: " << fApplyPhiOpeningAngleEl << "\n";
    std::cout << "Apply phi opening angle cut on protons: " << fApplyPhiOpeningAngleProt << "\n";
        // ---------------------------------------------------------------------------------------------------------------
	//NOAH :: 
	fiducialcut->InitPiMinusFit( fbeam_en);

	//initialize Fiducial functions for EC limits
	fiducialcut->InitEClimits();
	std::cout << " Test InitEClimits Loop " << fiducialcut->up_lim1_ec->Eval(60) << std::endl;

	// Definition and initialization of Histograms

	TH1F *h1_el_theta = new TH1F("h1_el_theta","",200,0,180);
	TH1F *h1_hit_nuc = new TH1F("h1_hit_nuc","",2,1,3);
        TH1F *h1_hit_nuc_pass = new TH1F("h1_hit_nuc_pass","",2,1,3);
	//NOAH :: Above this (don't care)
	TH1F *h1_el_mom = new TH1F("h1_el_mom","",6000,0,6);
	TH1F *h1_electron_momentum = new TH1F("h1_electron_momentum","",6000,0,6); // gchamber: electron momentum for (e,e') sample
	TH1F *h1_el_mom_corr = new TH1F("h1_el_mom_corr","",100,0.,5.);
	TH1F *h1_el_mom_ratio = new TH1F("h1_el_mom_ratio","",50,0.97,1.01);
	TH1F *h1_prot_mom = new TH1F("h1_prot_mom","",400,0,4); 
	TH1F *h1_histoweight = new TH1F("h1_histoweight","",1000,-2,2); // gchamber: histograms of histoweigh*(proton array element) for 1e1p spectrum
	TH1F *h1_histoweight2 = new TH1F("h1_histoweight2","",1000,-2,2); // gchamber: histogram of (proton array element) for 1e1p spectrum
	TH2F *h2_el_prot_theta = new TH2F("h2_el_prot_theta","",360,0,360,360,0,360);
	TH2F *h2_prot_theta_phi = new TH2F("h2_prot_theta_phi","",720,-360,360,720,-360,360); // gchamber: proton angular distribution for 1e1p sample 
	TH1F *h1_el_prot_phi_diff = new TH1F("h1_el_prot_phi_diff","",720,-360,360); // gchamber: difference in e phi and p phi
	TH2F *h2_el_prot_phi = new TH2F("h2_el_prot_phi","",720,-360,360,720,-360,360);
	TH2F *h2_el_prot_mom = new TH2F("h2_el_prot_mom","",6000,0,6,6000,0,6);
	TH2F *h2_el_prot_theta_incl = new TH2F("h2_el_prot_theta_incl","",360,0,360,360,0,360);
	TH2F *h2_el_prot_phi_incl = new TH2F("h2_el_prot_phi_incl","",360,0,360,360,0,360);
	TH2F *h2_el_prot_mom_incl = new TH2F("h2_el_prot_mom_incl","",6000,0,6,6000,0,6);
	TH1F *h1_prot_theta = new TH1F("h1_prot_theta","",360,0,360); 
	TH1F *h1_prot_theta_noweight = new TH1F("h1_prot_theta_noweight","",360,0,360);  
	TH1F *h1_prot_costheta = new TH1F("h1_prot_costheta","",200,-1,1);  // gchamber: cos(theta) for proton
	TH1F *h1_prot_mom_ratio = new TH1F("h1_prot_mom_ratio","",50,0.97,1.2);
	TH1F *h1_prot_mom_nobackground = new TH1F("h1_prot_mom_nobackground","",400,0,4); // gchamber: same as h1_prot_mom but without histoweight
	TH1F *h1_prot_angle_nobackground = new TH1F("h1_prot_angle_nobackground","",360,0,360); // gchamber: same as h1_prot_angle but without histoweight
	//NOah :: Delete below this (if it doesn't include e or p momentum)
	//NOAH :: 13 instances of each of these plots 

	TH1F *h1_Electron_AccMapWeights = new TH1F("h1_Electron_AccMapWeights","",200,0.,2.);
	TH1F *h1_Proton_AccMapWeights = new TH1F("h1_Proton_AccMapWeights","",200,0.,2.);
	TH1F *h1_PiPlus_AccMapWeights = new TH1F("h1_PiPlus_AccMapWeights","",200,0.,2.);
	TH1F *h1_PiMinus_AccMapWeights = new TH1F("h1_PiMinus_AccMapWeights","",200,0.,2.);

	//NOAH :: Do not need E_QE plots or energy transfer plots
	TH1F *h1_InteractionBreakDown_InSector_Q2[NInt][NSectors]; // smithja: reconstructed Q2 separated according to the interaction component and sector
	TH1F *h1_InteractionBreakDown_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom[NInt][NSectors];
    TH1F *h1_InteractionBreakDown_Omega_NoQ4Weight_InSector_el_mom_noptcut[NInt][NSectors]; 
    TH1F *h1_InteractionBreakdown_Omega_NoQ4Weight_InSector_el_mom_ptcut[NInt][NSectors]; 
    TH1F *h1_InteractionBreakDown_Omega_NoQ4Weight_Insector_prot_mom[NInt][NSectors]; 
    TH1F *h1_InteractionBreakDown_Omega_NoQ4Weight_Insector_prot_mom_QE[NInt][NSectors];
	TH1F *h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[NInt][NSectors][2]; // smithja: same as h1_InteractionBreakDown_Omega_NoQ4Weight_Insector_prot_mom_QE
												//          separated accordinerg to FSI (in last index 0, resc_val > 1) or no FSI (in 
	TH1F *h1_InteractionBreakDown_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector[NInt][NSectors];
	TH1F *h1_EePrime_FullyInclusive_NoQ4Weight_Theta_Slice_InSector[NSectors];
	TH1F *h1_EePrime_FullyInclusive_NoQ4Weight_xBCut_Theta_Slice_InSector[NSectors];

	TH1F *h1_InteractionBreakDown_NoQ4Weight_InSector_el_theta[NInt][NSectors]; // smithja: electron theta quantity used in h2_Electron_Theta_Phi
	TH1F *h1_InteractionBreakDown_NoQ4Weight_InSector_prot_theta[NInt][NSectors]; // smithja: proton theta quantity used in h2_prot_theta_phi
	TH1F *h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[NInt][NSectors][2]; // smithja: same as h1_InteractionBreakDown_NoQ4Weight_InSector_prot_theta
                                                                                               //          separated according to FSI (in last index 0, resc_val > 1) or no 
                                                                                               //          FSI (in last index 1, resc_val = 1)

    TH1F *h1_InteractionBreakDown_InSector_Em[NInt][NSectors]; // Missing energy broken down into sectors and reaction mechanisms
    TH1F *h1_InteractionBreakDown_InSector_Pm[NInt][NSectors];
    TH2F *h2_InteractionBreakDown_InSector_EmPm[NInt][NSectors];
	TH1F *h1_InteractionBreakDown_ThetaPQ[NInt][NSectors]; 
	TH1F *h1_InteractionBreakDown_InSector_el_mom_Emcut[NInt][NSectors];

	TProfile *TProf_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector[NSectors];
	TProfile *TProf_Theta_FullyInclusive_NoQ4Weight_Theta_Slice_InSector[NSectors];

	TH3D* h3_Electron_Mom_Theta_Phi = new TH3D("h3_Electron_Mom_Theta_Phi",";P_{e'} [GeV/c];#theta_{e'} [deg];#phi_{e'} [deg]",450,0.,4.5,180,0,360,180,0,360);
	TH3D* h3_Proton_Mom_Theta_Phi = new TH3D("h3_Proton_Mom_Theta_Phi",";P_{p} [GeV/c];#theta_{p} [deg];#phi_{p} [deg]",450,0.,4.5,180,0,360,180,0,360);
	TH3D* h3_PiPlus_Mom_Theta_Phi = new TH3D("h3_PiPlus_Mom_Theta_Phi",";P_{#pi^{+}} [GeV/c];#theta_{#pi^{+}} [deg];#phi_{#pi^{+}} [deg]",450,0.,4.5,180,0,360,180,0,360);
	TH3D* h3_PiMinus_Mom_Theta_Phi = new TH3D("h3_PiMinus_Mom_Theta_Phi",";P_{#pi^{-}} [GeV/c];#theta_{#pi^{-}} [deg];#phi_{#pi^{-}} [deg]",450,0.,4.5,180,0,360,180,0,360);

	for (int WhichSector = 0; WhichSector < NSectors; WhichSector++) {

		for (int WhichInt = 0; WhichInt < NInt; WhichInt++) {
			double proton_upper_bound;
            double proton_lower_bound;
            double electron_lower_bound;
            double electron_upper_bound;

            if(en_beam[fbeam_en]>1. && en_beam[fbeam_en]<2.){
            	proton_lower_bound = 0.; proton_upper_bound = 6.;
            	electron_lower_bound = 0.; electron_upper_bound = 6.;
            }
            if(en_beam[fbeam_en]>2. && en_beam[fbeam_en]<3.){
            	proton_lower_bound = 0.; proton_upper_bound = 6.;
            	electron_lower_bound = 0.; electron_upper_bound = 6.;
            	
            }
            if(en_beam[fbeam_en]>4. && en_beam[fbeam_en]<5.){
            	proton_lower_bound = 0.; proton_upper_bound = 6.;
            	electron_lower_bound = 0.; electron_upper_bound = 6.;
            	
            }

			h1_InteractionBreakDown_InSector_Q2[WhichInt][WhichSector] = new TH1F("h1_Interaction"+TString(std::to_string(WhichInt))+"_InSector"+TString(std::to_string(WhichSector))+"_Q2", "", 6000, 0., 6.);
			h1_InteractionBreakDown_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector[WhichInt][WhichSector]  = new TH1F("h1_"+TString(std::to_string(WhichInt))+"_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_"+TString(std::to_string(WhichSector)), "", 6000, 0., 6.);
			h1_InteractionBreakDown_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom[WhichInt][WhichSector]  = new TH1F("h1_"+TString(std::to_string(WhichInt))+"_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__"+TString(std::to_string(WhichSector)), "", 6000, electron_lower_bound, electron_upper_bound); // gchamber: electron momentum breakdown for inclusive sample
            h1_InteractionBreakDown_Omega_NoQ4Weight_InSector_el_mom_noptcut[WhichInt][WhichSector]  = new TH1F("h1_"+TString(std::to_string(WhichInt))+"_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom_noptcut__"+TString(std::to_string(WhichSector)), "", 6000, electron_lower_bound, electron_upper_bound); // gchamber: electron momentum breakdown for 1e1p sample
            h1_InteractionBreakdown_Omega_NoQ4Weight_InSector_el_mom_ptcut[WhichInt][WhichSector]  = new TH1F("h1_"+TString(std::to_string(WhichInt))+"_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom_ptcut__"+TString(std::to_string(WhichSector)), "", 6000, electron_lower_bound, electron_upper_bound); // gchamber: electron momentum breakdown for 1e1p sample with ptcut (if turned on)

            h1_InteractionBreakDown_Omega_NoQ4Weight_Insector_prot_mom[WhichInt][WhichSector]  = new TH1F("h1_"+TString(std::to_string(WhichInt))+"_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom__"+TString(std::to_string(WhichSector)), "", 6000, proton_lower_bound, proton_upper_bound); // gchamber: proton momentum breakdown for every proton passing fiducial, other cuts (inclusive)
            h1_InteractionBreakDown_Omega_NoQ4Weight_Insector_prot_mom_QE[WhichInt][WhichSector]  = new TH1F("h1_"+TString(std::to_string(WhichInt))+"_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__"+TString(std::to_string(WhichSector)), "", 6000, proton_lower_bound, proton_upper_bound); // gchamber: proton momentum breakdown into different channels for 1e1p sample
			
			h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[WhichInt][WhichSector][0] = new TH1F("h1_InteractionEq"+TString(std::to_string(WhichInt))+"_NoQ4Weight_InSector"+TString(std::to_string(WhichSector))+"_FSI_prot_mom_QE", "", 6000, proton_lower_bound, proton_upper_bound);
			h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[WhichInt][WhichSector][1] = new TH1F("h1_InteractionEq"+TString(std::to_string(WhichInt))+"_NoQ4Weight_InSector"+TString(std::to_string(WhichSector))+"_noFSI_prot_mom_QE", "", 6000, proton_lower_bound, proton_upper_bound);			
			
			h1_InteractionBreakDown_NoQ4Weight_InSector_el_theta[WhichInt][WhichSector] = new TH1F("h1_InteractionEq"+TString(std::to_string(WhichInt))+"_NoQ4Weight_InSector"+TString(std::to_string(WhichSector))+"_el_theta", "", 180, 0, 180);
			h1_InteractionBreakDown_NoQ4Weight_InSector_prot_theta[WhichInt][WhichSector] = new TH1F("h1_InteractionEq"+TString(std::to_string(WhichInt))+"_NoQ4Weight_InSector"+TString(std::to_string(WhichSector))+"_prot_theta", "", 180, 0, 180);
			
			h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[WhichInt][WhichSector][0] = new TH1F("h1_InteractionEq"+TString(std::to_string(WhichInt))+"_NoQ4Weight_InSector"+TString(std::to_string(WhichSector))+"_FSI_prot_theta", "", 180, 0, 180);
            h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[WhichInt][WhichSector][1] = new TH1F("h1_InteractionEq"+TString(std::to_string(WhichInt))+"_NoQ4Weight_InSector"+TString(std::to_string(WhichSector))+"_noFSI_prot_theta", "", 180, 0, 180);
            
            h1_InteractionBreakDown_InSector_Em[WhichInt][WhichSector] = new TH1F("h1_Int_"+TString(std::to_string(WhichInt))+"_Sect_"+TString(std::to_string(WhichSector))+"_Em", "", 10,0,.4);//missing energy distribution
    		h1_InteractionBreakDown_InSector_Pm[WhichInt][WhichSector] = new TH1F("h1_Int_"+TString(std::to_string(WhichInt))+"_Sect_"+TString(std::to_string(WhichSector))+"_Pm","", 100,0,1.0);
    		h2_InteractionBreakDown_InSector_EmPm[WhichInt][WhichSector] = new TH2F("h2_Int_"+TString(std::to_string(WhichInt))+"_Sect_"+TString(std::to_string(WhichSector))+"_EmPm","", 10,0.,.4,100,0.,1.0);
    		h1_InteractionBreakDown_ThetaPQ[WhichInt][WhichSector] = new TH1F("h1_Int"+TString(std::to_string(WhichInt))+"_Sect_"+TString(std::to_string(WhichSector))+"_ThetaPQ", "", 90, 0, 180);

    		h1_InteractionBreakDown_InSector_el_mom_Emcut[WhichInt][WhichSector] = new TH1F("h1_Int"+TString(std::to_string(WhichInt))+"_Sect_"+TString(std::to_string(WhichSector))+"_el_mom_Emcut","", 80, electron_lower_bound, electron_upper_bound);

		}



		TProf_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector[WhichSector]  = new TProfile("TProf_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_"+TString(std::to_string(WhichSector)),"",6000,0.,6.);

		TProf_Theta_FullyInclusive_NoQ4Weight_Theta_Slice_InSector[WhichSector]  = new TProfile("TProf_Theta_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_"+TString(std::to_string(WhichSector)),"",300,t_thetaEl_lb->GetVal(),t_thetaEl_ub->GetVal());

		h1_EePrime_FullyInclusive_NoQ4Weight_Theta_Slice_InSector[WhichSector]  = new TH1F("h1_EePrime_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_"+TString(std::to_string(WhichSector)),"",6000,0.,6.);

		// ---------------------------------------------------------------------------------------------------------------

		h1_EePrime_FullyInclusive_NoQ4Weight_xBCut_Theta_Slice_InSector[WhichSector]  = new TH1F("h1_EePrime_FullyInclusive_NoQ4Weight_xBCut_Theta_Slice_InSector_"+TString(std::to_string(WhichSector)),"",6000,0.,6.);

	}

	// -------------------------------------------------------------------------------------------------------

	// Binning for energy reconstruction histograms && feeddown
	int n_bins;
	double *x_values;
	double *x_qe;

	if(en_beam[fbeam_en]>1. && en_beam[fbeam_en]<2.){
		n_bins=38;
		x_values=new double[n_bins+1]; x_qe=new double[n_bins+1];
		for (int i=0;i<=17;i++) { x_values[i]=0.4+i*0.04; x_qe[i] = (x_values[i] - en_beam[fbeam_en]) / en_beam[fbeam_en]; }
		for (int i=0;i<=20;i++) { x_values[i+18]=1.08+(i+1)*0.02; x_qe[i+18] = (x_values[i+18] - en_beam[fbeam_en]) / en_beam[fbeam_en]; }
	}

	if(en_beam[fbeam_en]>2. && en_beam[fbeam_en]<3.){
		n_bins=54;
		x_values=new double[n_bins+1]; x_qe=new double[n_bins+1];
		for (int i=0;i<=23;i++) { x_values[i]=i*0.09; x_qe[i] = (x_values[i] - en_beam[fbeam_en]) / en_beam[fbeam_en];}
		for (int i=0;i<=30;i++) { x_values[i+24]=2.07+(i+1)*0.03; x_qe[i+24] = (x_values[i+24] - en_beam[fbeam_en]) / en_beam[fbeam_en];}
	}

	if(en_beam[fbeam_en]>4. && en_beam[fbeam_en]<5.){
		n_bins=38;
		x_values=new double[n_bins+1]; x_qe=new double[n_bins+1];
		for (int i=0;i<=21;i++)	{ x_values[i]=i*0.2; x_qe[i] = (x_values[i] - en_beam[fbeam_en]) / en_beam[fbeam_en];}
		for (int i=0;i<=16;i++)	{ x_values[i+22]=4.2+(i+1)*0.05; x_qe[i+22] = (x_values[i+22] - en_beam[fbeam_en]) / en_beam[fbeam_en];}
	}


	// -------------------------------------------------------------------------------------------------------

	//Definitions of further Histograms
	//NOAH : Remove (E_rec, radiative corrections, etc. )
	TH1F *CosDeltaThetaElectronPhotonAboveThreshold=new TH1F("CosDeltaThetaElectronPhotonAboveThreshold","",100,-1.,1.);
	TH1F *CosDeltaPhiElectronPhotonAboveThreshold=new TH1F("CosDeltaPhiElectronPhotonAboveThreshold","",100,-1.,1.);

	TH1F *h1_theta0=new TH1F("h1_theta0","",300,0,180);

	TH2F *h2_N_prot_pi=new TH2F("h2_N_prot_pi","",10,0,5,10,0,5);
	TH2F *h2_N_prot_pi_phot=new TH2F("h2_N_prot_pi_phot","",10,0,5,10,0,5);
	TH2F *h2_N_prot_pi_phot_nonrad=new TH2F("h2_N_prot_pi_phot_nonrad","",20,0,10,20,0,10);
	TH2F *h2_el_theta_phi = new TH2F("h2_el_theta_phi","",200,0,360,200,0,180);
	TH1F *h1_el_mom_incl = new TH1F("h1_el_mom_incl","",100,0,2.6);	// gchamber: el momentum inclusive
	TH2F *h2_el_theta_phi_incl = new TH2F("h1_el_theta_incl","",360,0,360,360,0,360);
	
	TH2F *h2_Electron_Theta_Phi = new TH2F("h2_Electron_Theta_Phi", "", 360, 0, 360, 180, 0, 180); // smithja: electron theta vs. phi for exclusive case

	//NOAH: Monitoring plot (correlation plots between observables KEEP)
	// smithja:
	// These plots will be used to investigate correlations between proton
	// momentum and other variables of interest.
	TH2F *h2_prot_mom_el_phi = new TH2F("h2_prot_mom_el_phi", "", 360, 0, 360, 6000, 0, 6);
	TH2F *h2_prot_mom_el_theta = new TH2F("h2_prot_mom_el_theta", "", 720, 0, 180, 6000, 0, 6);
	TH2F *h2_prot_mom_el_mom = new TH2F("h2_prot_mom_el_mom", "", 6000, 0, 6, 6000, 0, 6);
	TH2F *h2_el_mom_theta_nocuts = new TH2F("h2_el_mom_theta_nocuts", "", 6000, 0, 6, 1800, 0, 180);
	TH2F *h2_el_mom_theta_nocuts_nosmear = new TH2F("h2_el_mom_theta_nocuts_nosmear", "", 6000, 0, 6, 1800, 0, 180);
	TH2F *h2_el_theta_phi_nocuts_nosmear = new TH2F("h2_el_theta_phi_nocuts_nosmear", "", 7200, -360, 360, 7200, -360, 360);
	TH2F *h2_prot_mom_phi = new TH2F("h2_prot_mom_phi", "", 360, 0, 360, 6000, 0, 6);
	TH2F *h2_prot_mom_theta = new TH2F("h2_prot_mom_theta", "", 720, 0, 180, 6000, 0, 6);
	// smithja: end plot section

	TH1F *h1_Electron_Momentum = new TH1F("h1_Electron_Momentum",";P_{e'} [GeV/c]",6000,0.,6);
	TH1F *h1_Proton_Momentum = new TH1F("h1_Proton_Momentum",";P_{p} [GeV/c]",6000,0.,6);
	TH1F *h1_Proton_Angle = new TH1F("h1_Proton_Angle","",360,0,360); // gchamber: hist for proton angle distribution (just for protons passing CLAS fiducials)
	TH1F *h1_Proton_Angle_noweight = new TH1F("h1_Proton_Angle_noweight","",360,0,360); 
	TH1F *h1_PiPlus_Momentum = new TH1F("h1_PiPlus_Momentum",";P_{#pi^{+}} [GeV/c]",6000,0.,6);
	TH1F *h1_PiMinus_Momentum = new TH1F("h1_PiMinus_Momentum",";P_{#pi^{-}} [GeV/c]",6000,0.,6);

	TH2F *h2_Electron_Theta_Momentum_FirstSector = new TH2F("h2_Electron_Theta_Momentum_FirstSector",";P_{e'} [GeV/c];#theta_{e'}",6000,0.,6,360,0,360);
	TH2F *h2_Electron_Theta_Momentum_SecondSector = new TH2F("h2_Electron_Theta_Momentum_SecondSector",";P_{e'} [GeV/c];#theta_{e'}",6000,0.,6,360,0,360);
	TH2F *h2_Electron_Theta_Momentum_ThirdSector = new TH2F("h2_Electron_Theta_Momentum_ThirdSector",";P_{e'} [GeV/c];#theta_{e'}",6000,0.,6,360,0,360);
	TH2F *h2_Electron_Theta_Momentum_FourthSector = new TH2F("h2_Electron_Theta_Momentum_FourthSector",";P_{e'} [GeV/c];#theta_{e'}",6000,0.,6,360,0,360);
	TH2F *h2_Electron_Theta_Momentum_FifthSector = new TH2F("h2_Electron_Theta_Momentum_FifthSector",";P_{e'} [GeV/c];#theta_{e'}",6000,0.,6,360,0,360);
	TH2F *h2_Electron_Theta_Momentum_SixthSector = new TH2F("h2_Electron_Theta_Momentum_SixthSector",";P_{e'} [GeV/c];#theta_{e'}",6000,0.,6,360,0,360);
	
	TH2F *h2_el_prot_theta_elSectors_protSectors[6][6];
	
	for (int elSector = 0; elSector < 6; elSector++) {for (int protSector = 0; protSector < 6; protSector++) {
		h2_el_prot_theta_elSectors_protSectors[elSector][protSector] = new TH2F("h2_el_prot_theta_elSector"+TString(std::to_string(elSector+1))+"_protSector"+TString(std::to_string(protSector+1)),"",360,0,360,360,0,360);
	}} 

	TH2F *h2_Proton_Theta_Phi = new TH2F("h2_Proton_Theta_Phi",";#phi_{p} [GeV/c];#theta_{p}",360,0.,360,360,0,360);

	TH2F *h2_Proton_Theta_Momentum_FirstSector = new TH2F("h2_Proton_Theta_Momentum_FirstSector",";P_{p} [GeV/c];#theta_{p}",6000,0.,6,360,0,360);
	TH2F *h2_Proton_Theta_Momentum_SecondSector = new TH2F("h2_Proton_Theta_Momentum_SecondSector",";P_{p} [GeV/c];#theta_{p}",6000,0.,6,360,0,360);
	TH2F *h2_Proton_Theta_Momentum_ThirdSector = new TH2F("h2_Proton_Theta_Momentum_ThirdSector",";P_{p} [GeV/c];#theta_{p}",6000,0.,6,360,0,360);
	TH2F *h2_Proton_Theta_Momentum_FourthSector = new TH2F("h2_Proton_Theta_Momentum_FourthSector",";P_{p} [GeV/c];#theta_{p}",6000,0.,6,360,0,360);
	TH2F *h2_Proton_Theta_Momentum_FifthSector = new TH2F("h2_Proton_Theta_Momentum_FifthSector",";P_{p} [GeV/c];#theta_{p}",6000,0.,6,360,0,360);
	TH2F *h2_Proton_Theta_Momentum_SixthSector = new TH2F("h2_Proton_Theta_Momentum_SixthSector",";P_{p} [GeV/c];#theta_{p}",6000,0.,6,360,0,360);

	//Noah :: Remove plots related to pions

	TH2F *h2_Electron_Theta_Momentum = new TH2F("h2_Electron_Theta_Momentum",";P_{e'} [GeV/c];#theta_{e'}",6000,0.,6,360,0,360);
	TH2F *h2_Proton_Theta_Momentum = new TH2F("h2_Proton_Theta_Momentum",";P_{p} [GeV/c];#theta_{p}",6000,0.,6,360,0,360);

	//NOAH:: REmove plots relate to photons

	TH2F *h2_el_CosTheta_E = new TH2F("h2_el_CosTheta_E",";cos(#theta_{e'});E_{e'} [GeV]",200,-1,1,600,0,6);
	TH2F *h2_el_mom_diff = new TH2F("h2_el_mom_diff","",500,0.,1.,500,-0.1,0.1);

	//Noah :: Remove these 
	TH2F *h2_el_pcorr_puncorr = new TH2F("h2_el_pcorr_puncorr","",100,0,1,100,0,3);
	TH2F *h2_pperp_W=new TH2F("h2_pperp_W","",200,0,3,200,0,2);


	// ---------------------------------------------------------------------------------------------------
	
	double MinTheta = 10, MaxTheta = 60; int ThetaSlices = 10;
	int ThetaStep = (MaxTheta - MinTheta) / ThetaSlices;
	double MinTheta2D = 15, MaxTheta2D = 60; int ThetaSlices2D = 3;	
	int ThetaStep2D = (MaxTheta2D - MinTheta2D) / ThetaSlices2D;
	
	// ---------------------------------------------------------------------------------------------------

	for(int h=0;h<20;h++){
		h2_N_pi_phot[h]=new TH2F(Form("h2_N_pi_phot_%d",h),"",10,0,5,10,0,5);
	}

	// Plots for interaction break down for GENIE samples
	TH1D* Q2_BreakDown[NInt];
	TH1D* Nu_BreakDown[NInt];
	TH1D* Pe_BreakDown[NInt];
		 

	for (int WhichInt = 0; WhichInt < NInt; WhichInt++) {
		Q2_BreakDown[WhichInt] = new TH1D(Form("Q2_Int_%d",WhichInt),";Q^{2} [GeV^{2}/c^{2}]",400,0,6);
		Nu_BreakDown[WhichInt] = new TH1D(Form("Nu_Int_%d",WhichInt),";Energy Transfer [GeV]",400,0,4);
		Pe_BreakDown[WhichInt] = new TH1D(Form("Pe_Int_%d",WhichInt),";P_{e} [GeV/c]",100,0.,5.);			
	}		  						  
	
	// Vector containing kinematic variables using Ecal
	vector<double> CalKineVars{};
	// Weight to fill the plots mentioned above
	//double LocalWeight;

	// Signal Event Counter -> 1e1p0pi events (everything lese is bkg)
	int SignalEvents = 0;
	int QESignalEvents = 0;
	int MECSignalEvents = 0;
	int RESSignalEvents = 0;
	int DISSignalEvents = 0;
	int OtherSignalEvents = 0;

	// ---------------------------------------------------------------------------------------------------------------

	// Get the number of events to run overall
	
//	int Nentries = TMath::Min(Ntfileentries,NtweightsEntries);

	// ---------------------------------------------------------------------------------------------------------------

	// Justification for the parameter fchoice
	// https://docs.google.com/presentation/d/1ghG08JfCYXRXh6O8hcXKrhJOFxkAs_9i5ZfoIkiiEHU/edit?usp=sharing
	//NOAH :: Need this (signal definition)
	TF1 *myElectronFit = new TF1("myElectronFit","[0]+[1]/x",0.,5.);

	if (en_beam[fbeam_en] == 1.161) { myElectronFit->SetParameters(17,7); }
	if (en_beam[fbeam_en] == 2.261) { myElectronFit->SetParameters(16,10.5); }
	if (en_beam[fbeam_en] == 4.461) { myElectronFit->SetParameters(13.5,15); }

	// ---------------------------------------------------------------------------------------------------------------

	// Keeping track of the energy

	// ---------------------------------------------------------------------------------------------------------------

	/** Beginning of Event Loop **/

	int TotalCounter = 0;
	int PassCounter06 = 0;
	int PassCounter05 = 0;
	int PassCounter04 = 0;
	int PassCounter04a = 0;
	int PassCounter03 = 0;
	int PassCounter02 = 0;
	int PassCounter01 = 0;
	int PassCounter0 = 0;
	int PassCounter1 = 0;
	int PassCounter2 = 0;
	int PassCounter3 = 0;
	int PassCounter4 = 0;

	int two_proton_same_sector = 0;
	int proton_pion_same_sector = 0;

	for( Long64_t jentry = 0; jentry < nentries; jentry++){
		
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		//Read Entry
		int nb = GetEntry(jentry);
		if (nb == 0) { std::cout <<"Event loop: 0 byte read for entry " << jentry << ". Indicate failure in reading the file" <<	std::endl;}

		if (jentry%10000 == 0) {std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/double(nentries)*100. << " %"<< std::endl;}

		/*
		if( jentry%200000 == 0 )
		{
			gDirectory->Write("hist_Files", TObject::kOverwrite);
			//cout<<jentry<<endl;
		}
                */

		TotalCounter ++;

		// ---------------------------------------------------------------------------------------------------------------

		std::string StoreEnergy = fbeam_en;
		if (UsePhiThetaBand) { StoreEnergy = ""; }

		// -------------------------------------------------------------------------------------------------------------------------

		// For GENIE samples, identify the interaction type

		int Interaction = -1;

		if (fchoice > 0) {
			if (qel) { Interaction = 1; }
			if (mec) { Interaction = 2; }
			if (res) { Interaction = 3; }
			if (dis) { Interaction = 4; }
		}
		else if (fchoice == 0) { Interaction = 0; } // smithja: added when I started running CLAS data on 10/29/2021

		//if (qel == false) continue;
		// ---------------------------------------------------------------------------------------------------------------

		// For GENIE samples, identify the value for resc
		
		int resc_val = -99; 

		if (fchoice > 0) {
			resc_val = resc[0]; // smithja: index always zero; resc looks to be single-element array in genie_analysis.h
		}

		//if (resc_val > 1) continue;
		
		// ---------------------------------------------------------------------------------------------------------------
		PassCounter06 ++;
		if(jentry == 0){ //first entry to initialize TorusCurrent, Fiducials and Subtraction classes

			//The TorusField has to be set before the Fiducialcut parameters are initialized
			if(en_beam[fbeam_en]>1. && en_beam[fbeam_en]<2. ) //1.1 GeV, we are not using the 1.1 GeV data with 1500 current field
			{
				 fTorusCurrent = 750;
			}
			else if( (en_beam[fbeam_en]>2. && en_beam[fbeam_en]<3.) || (en_beam[fbeam_en]>4. && en_beam[fbeam_en]<5.) ) //2.2 GeV	or 4.4 GeV
			{
				 fTorusCurrent = 2250;
			}
			else { std::cout << "genie_analysis::Loop(): fTorusCurrent could not be assigned" << std::endl;}

			fiducialcut->SetConstants(fTorusCurrent, target_name, en_beam);
			fiducialcut->SetFiducialCutParameters(fbeam_en);
			std::cout << " EventLoop: Finished setting up fiducial cut class " << std::endl;
//			rotation->InitSubtraction(fbeam_en, target_name, bind_en, N_tot, fiducialcut);
			rotation->InitSubtraction(StoreEnergy, target_name, bind_en, N_tot, fiducialcut);
			std::cout << " EventLoop: Finished setting up rotation initialize " << std::endl;
		}

		//Resets q vector to (0,0,0)
		rotation->ResetQVector();

		// -----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Counters for truth level studies

		int TrueElectronsAboveThreshold = 0;
		int TrueProtonsAboveThreshold = 0;
		int TrueChargedPionsAboveThreshold = 0;
		int TruePiPlusAboveThreshold = 0;
		int TruePiMinusAboveThreshold = 0;
		int TrueGammasAboveThreshold = 0;

		// -----------------------------------------------------------------------------------------------------------------------------------------------------------

		double SmearedPe;
		double SmearedEe;
		double e_acc_ratio = 1.;	//will be 1 for CLAS data

		// Outgoing e',	Uncorr and corrected are the same read from root file.
		//V4_el and V3_el will be changed by smearing for GENIE simulation data
		TLorentzVector V4_el(pxl,pyl,pzl,El);
		TLorentzVector V4_el_uncorr(pxl,pyl,pzl,El);
		TVector3 V3_el(pxl,pyl,pzl);
		
		double el_momentum = V3_el.Mag();
		double el_theta = V3_el.Theta();

		h2_el_mom_theta_nocuts_nosmear->Fill(el_momentum, el_theta*180./TMath::Pi());
		h2_el_theta_phi_nocuts_nosmear->Fill(el_theta*180./TMath::Pi(),V3_el.Phi()*180./TMath::Pi());
		// ----------------------------------------------------------------------------------------------------------------------	
		PassCounter05 ++;
		if (fchoice > 0) { //smearing, fiducials and acceptance ratio for GENIE simulation data

			//Smearing of Electron Vector from Simulation
			SmearedPe = gRandom->Gaus(pl,reso_e*pl);
			SmearedEe = sqrt( SmearedPe*SmearedPe + e_mass * e_mass );
			V3_el.SetXYZ(SmearedPe/pl * pxl,SmearedPe/pl * pyl,SmearedPe/pl * pzl);
			V4_el.SetPxPyPzE(V3_el.X(),V3_el.Y(),V3_el.Z(),SmearedEe);
			double phi_ElectronOut = V3_el.Phi(); //in Radians
			
			V3_el.SetPhi(phi_ElectronOut + TMath::Pi() ); // Vec.Phi() is between (-180,180), GENIE coordinate system flipped with respect to CLAS
			//Fiducial Cuts with the smeared values // moved it further down after W & Q2 cuts
//			if (ApplyFiducials)  { if (!EFiducialCut(fbeam_en,V3_el) ) continue;} // Electron theta & phi fiducial cuts
			
			phi_ElectronOut += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS
			
			el_momentum = V3_el.Mag(); //Momentum after smearing
			el_theta = V3_el.Theta(); //Angle after smearing

			// acceptance_c takes phi in radians and here unmodified by 30 degree.

			e_acc_ratio = acceptance_c(el_momentum, cos(el_theta), phi_ElectronOut, 11, file_acceptance, ApplyAccWeights);
			if ( fabs(e_acc_ratio) != e_acc_ratio ) { continue; }

			h2_el_mom_theta_nocuts->Fill(el_momentum, el_theta*180./TMath::Pi(), e_acc_ratio);
			// --------------------------------------------------------------------------------------------------

			// GENIE Systematic Uncertainties

//			tweights->GetEntry(jentry);
//			float* ArrayWeights = weights->GetArray();

////			double TuningWeight = ArrayWeights[0]; // - 1 sigma variation
////			double TuningWeight = ArrayWeights[1]; // 0 sigma variation
//			double TuningWeight = ArrayWeights[2]; // + 1 sigma variation	

//			e_acc_ratio = e_acc_ratio * TuningWeight;

			// --------------------------------------------------------------------------------------------------		

		}

		// ----------------------------------------------------------------------------------------------------------------------
		

		PassCounter04 ++;
		double theta_min = myElectronFit->Eval(el_momentum); // in deg
		if (el_theta*180./TMath::Pi() < theta_min) { continue; }
		PassCounter04a ++;
		if (fApplyThetaSliceEl) {  // hard coded range for now
			if ( el_theta*180./TMath::Pi() < t_thetaEl_lb->GetVal()) { continue; }
			if ( el_theta*180./TMath::Pi() > t_thetaEl_ub->GetVal()) { continue; }
		}
		// ----------------------------------------------------------------------------------------------------------------------
	
		// Explicit cuts on electron momentum
		PassCounter03 ++;
		if (fbeam_en=="1161" && (el_momentum < 0.4 || (el_momentum < t_elMom_lb->GetVal() && fApplyElMomCut == true))) { continue; }
		if (fbeam_en=="2261" && (el_momentum < 0.55 || (el_momentum < t_elMom_lb->GetVal() && fApplyElMomCut == true))) { continue; }
		if (fbeam_en=="4461" && (el_momentum < 1.1 || (el_momentum < t_elMom_lb->GetVal() && fApplyElMomCut == true))) { continue; }
		PassCounter02 ++;	
		//Definition as for data. It is also correct for GENIE simulation data since V3_el is rotated above by 180 degree in phi
		double el_phi_mod = V3_el.Phi()*TMath::RadToDeg()  + 30; //Add 30 degree for plotting and photon phi cut
		//if(el_phi_mod < 0) std::cout << "negative el_phi_mod = " << el_phi_mod << "\n";
		if(el_phi_mod<0)  el_phi_mod  = el_phi_mod+360; //Add 360 so that electron phi is between 0 and 360 degree
		//if(el_phi_mod < 30) std::cout << "el_phi_mod = " << el_phi_mod << "\n";

		if (fApplyPhiOpeningAngleEl) { if ( !(TMath::Abs(el_phi_mod - 30)  <= PhiOpeningAngleEl || TMath::Abs(el_phi_mod - 90)  <= PhiOpeningAngleEl || TMath::Abs(el_phi_mod - 150)  <= PhiOpeningAngleEl || TMath::Abs(el_phi_mod - 210)  <= PhiOpeningAngleEl || TMath::Abs(el_phi_mod - 270)  <= PhiOpeningAngleEl || TMath::Abs(el_phi_mod - 330)  <= PhiOpeningAngleEl ) ) { continue; } }

		int ElectronSector = el_phi_mod / 60.;

		PassCounter01 ++;	

		//if (fApplyPhiSliceEl_Sectors126) {if (ElectronSector == 2 || ElectronSector == 3 || ElectronSector == 4) continue;}

		//Calculated Mott Cross Section and Weights for Inclusive Histograms
		//Wght and e_acc_ratio is 1 for CLAS data
		//double Mott_cross_sec = ( pow(fine_struc_const,2.)*(cos(el_theta)+1))/(2*pow(El,2.)*pow((1-cos(el_theta)),2.));

		double reco_q3 = (V4_el-V4_beam).Rho();
		double reco_Q2 = -(V4_el-V4_beam).Mag2();
//		double Q4 = reco_Q2 * reco_Q2;
		double Q4 = 1.; // smithja: to eliminate Q4 dependence as part of re-doing Graham's Procedure 2 analysis, I
				//          have set Q4 to simply be 1. The only instances where Q4 pops up are when weighting
				//          some histograms, i.e. in the second argument of some Fill() statements. To put back in
				//          the Q4 dependence in these weights, simply comment out this instance of Q4 and uncomment
				//          the original one directly above.
//		double Mott_cross_sec = (1./Q4) * XSecScale;
		double Mott_cross_sec = 1; // smithja: this is the weight Dr. Betancourt said to do away with from Graham's analysis.
					   //          the object of setting this to 1 is to remove the Q4 dependence from the
					   //          Mott cross section. You can see that XSecScale is also part of the instance of
					   //          Mott_cross_sec directly above. However, when I received this script, XSecScale
					   //          was set to equal 1. While the above instance where Q4 = 1 technically does the
					   //          same thing as this line, I am changing Mott_cross_sec here in case some analysis
					   //          down the line wants to make use of XSecScale != 1.
		// ---------------------------------------------------------------------------------------------------------------------

		// ---------------------------------------------------------------------------------------------------------------------

		// Sanity check, especially for radiation
		if (wght < 0 || wght > 10) { std::cout << "Something is really wrong with your weights !!!" << std::endl; }

		double WeightIncl = wght*e_acc_ratio / Mott_cross_sec;

		PassCounter0 ++;
		// Securing ourselves against infinities
		if ( fabs(WeightIncl) != WeightIncl ) { continue; }

		//Calculation of Reconstructed Energy from ELectron only
		//using the same value of single nucleon separation E Ecal and Eqe
		double E_rec = (m_prot*bind_en[ftarget]+m_prot*V4_el.E())/(m_prot-V4_el.E()+V4_el.Rho()*cos(el_theta));
		double EQE_Reso = (E_rec - en_beam_Ecal[fbeam_en]) / en_beam_Ecal[fbeam_en]; 

		//Calculation of kinematic quantities (nu, Q2, x bjorken, q and W)
		double nu = -(V4_el-V4_beam).E();
		double x_bjk = reco_Q2/(2*m_prot*nu);

		// QE selection
		//if ( fabs(x_bjk - 1.) > 0.2) { continue; }

		// ---------------------------------------------------------------------------------------------------------------------
		TVector3 V3_q = (V4_beam-V4_el).Vect();
		TVector3 V3_rot_q = (V4_beam.Vect() - V3_el);
		double V3_q_theta_deg = V3_q.Theta() * 180. / TMath::Pi();
		double V3_q_phi_deg = V3_q.Phi() * 180. / TMath::Pi() + 30.; 
		if (V3_q_phi_deg > 360) { V3_q_phi_deg = V3_q_phi_deg - 360.; } 
		if (V3_q_phi_deg < 0) { V3_q_phi_deg = V3_q_phi_deg + 360.; }
		double W_var = TMath::Sqrt((m_prot+nu)*(m_prot+nu)-V3_q*V3_q);

		//converting theta to degrees
		el_theta = el_theta*TMath::RadToDeg();
		PassCounter1 ++;
		//Cuts on Q2 and W, only keep events with Q2 > Q2cut and W < Wcut
		if ( reco_Q2 < Q2cut || W_var > Wcut) continue;

		// ---------------------------------------------------------------------------------------------------------------------

		// apapadop Nov 4 2020: true electron counter for truth level studies
		TrueElectronsAboveThreshold++;
		
		if (fchoice > 0) { 			

			//Fiducial Cuts with the smeared values
			if (ApplyFiducials)  { if (!EFiducialCut(fbeam_en,V3_el) ) continue;} // Electron theta & phi fiducial cuts 
		}

		// ---------------------------------------------------------------------------------------------------------------------

		//Set q vector for the following rotations for the subtraction procedure
		rotation->SetQVector(V3_q);
//		rotation->PrintQVector();

		h2_el_theta_phi->Fill(el_phi_mod,el_theta,WeightIncl);

		if (el_phi_mod > 0 && el_phi_mod < 60) { h2_Electron_Theta_Momentum_FirstSector->Fill(V4_el.Rho(),V3_el.Theta()*180./TMath::Pi(),e_acc_ratio); } 
		if (el_phi_mod > 60 && el_phi_mod < 120) { h2_Electron_Theta_Momentum_SecondSector->Fill(V4_el.Rho(),V3_el.Theta()*180./TMath::Pi(),e_acc_ratio); } 
		if (el_phi_mod > 120 && el_phi_mod < 180) { h2_Electron_Theta_Momentum_ThirdSector->Fill(V4_el.Rho(),V3_el.Theta()*180./TMath::Pi(),e_acc_ratio); } 
		if (el_phi_mod > 180 && el_phi_mod < 240) { h2_Electron_Theta_Momentum_FourthSector->Fill(V4_el.Rho(),V3_el.Theta()*180./TMath::Pi(),e_acc_ratio); } 
		if (el_phi_mod > 240 && el_phi_mod < 300) { h2_Electron_Theta_Momentum_FifthSector->Fill(V4_el.Rho(),V3_el.Theta()*180./TMath::Pi(),e_acc_ratio); } 
		if (el_phi_mod > 300 && el_phi_mod < 360) { h2_Electron_Theta_Momentum_SixthSector->Fill(V4_el.Rho(),V3_el.Theta()*180./TMath::Pi(),e_acc_ratio); }

		// ---------------------------------------------------------------------------------------------------------------------

		// apapadop: Oct 8 2020: ditching bad sectors
		// Counting sectors from 0 to 5

		if (!UseAllSectors) { 
			if ( (ElectronSector == 2 || ElectronSector == 4) &&  fbeam_en == "1161") { continue; }
			if ( (ElectronSector == 2 || ElectronSector == 3 || ElectronSector == 4) &&  fbeam_en == "2261") { continue; }
		}

		// ---------------------------------------------------------------------------------------------------------------------
		PassCounter2 ++;
		// Fully inclusive plots & counters shown first below

		h1_Electron_AccMapWeights->Fill(e_acc_ratio);
		h1_Electron_Momentum->Fill(el_momentum,e_acc_ratio);


		if (el_theta >= t_thetaEl_lb->GetVal() && el_theta <= t_thetaEl_ub->GetVal()) { 

			if(hitnuc == 2212) h1_hit_nuc->Fill(1,WeightIncl);
                if(hitnuc == 2112) h1_hit_nuc->Fill(2,WeightIncl);
			if (Interaction > -1) { h1_InteractionBreakDown_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector[Interaction][ElectronSector]->Fill(nu,WeightIncl/Q4); }
			if (Interaction > -1) { if (!(TMath::Sqrt(TMath::Power(V3_el.X(),2) + TMath::Power(V3_el.Y(),2)) > PtMax && fApplyPtCut == true)) {
				h1_InteractionBreakDown_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl);
			}}

			h1_EePrime_FullyInclusive_NoQ4Weight_Theta_Slice_InSector[ElectronSector]->Fill(V4_el.E(),WeightIncl/Q4);

			TProf_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector[ElectronSector]->Fill(nu,nu);
			TProf_Theta_FullyInclusive_NoQ4Weight_Theta_Slice_InSector[ElectronSector]->Fill(el_theta,el_theta);

			if (fabs(x_bjk - 1.) < 0.2) {
				h1_EePrime_FullyInclusive_NoQ4Weight_xBCut_Theta_Slice_InSector[ElectronSector]->Fill(V4_el.E(),WeightIncl/Q4);
			}
		}
		h1_electron_momentum->Fill(el_momentum,WeightIncl);
		h1_el_mom->Fill(V4_el_uncorr.Rho(),WeightIncl);
		h1_el_mom_ratio->Fill(V4_el.Rho()/V4_el_uncorr.Rho(),WeightIncl);
		h2_el_pcorr_puncorr->Fill(V4_el.Rho(),V4_el.Rho()/V4_el_uncorr.Rho(),WeightIncl);
		h2_el_mom_diff->Fill(V4_el.Rho(),V4_el.Rho()-V4_el_uncorr.Rho(),WeightIncl);

		//Filling Histogram for electron kinematics
		//h3_Electron_Mom_Theta_Phi->Fill(V4_el.Rho(),el_theta,el_phi_mod,wght*e_acc_ratio);

		h1_el_theta->Fill(el_theta);

		int ThetaSlice = V4_el.Theta()*180./TMath::Pi() / ThetaStep;
		int ThetaSlice2D = V4_el.Theta()*180./TMath::Pi() / ThetaStep2D;
 
		//Now we are done with the selection of electrons. Next step is looking for other hadrons in the events

		//Index variables for hadrons (p and pions)
		int index_p[20]; //index for each proton
		int index_pi[20]; //index for each pion
		int ind_pi_phot[20]; //index for pions and photons
		int index_pipl[20]; //index for each pi plus
		int index_pimi[20]; //index for each pi minus
		int charge_pi[20]; //Charge for the pions and photons
		//Smeared Momentum and Energy values for GENIE (simulation) data
		double Smeared_Pp[20]; //smeared momentum values for protons
		double Smeared_Ep[20]; //smeared energy values for protons
		double Smeared_Ppi[20]; //smeared momentum values for pions
		double Smeared_Epi[20]; //smeared energy values for pions

		//Number of hadrons
		int num_p = 0;
		int num_pi = 0;
		int num_pi_phot = 0; //couting all pions and photons
		int num_phot = 0; //couting all photons
		int num_pimi = 0;
		int num_pipl = 0;
		int num_pi_phot_nonrad = 0; //counting all pions and non-radiation photons
		int num_phot_rad = 0; //counting radiation photons
		int num_phot_nonrad = 0;
		//Index and number variables for neutral particles
		int ec_index_n[20];
		int ec_num_n = 0;
		bool ec_radstat_n[20];

		//Array initialize to -1 or false
		for (int i = 0; i < 20; i++) {
			index_p[i] = -1;   index_pi[i] = -1;   index_pipl[i] = -1;   index_pimi[i] = -1;   ind_pi_phot[i] = -1;
			ec_index_n[i] = -1;   ec_radstat_n[i] = false;
			charge_pi[i] = -2; //default number should be not a possible real charge
			Smeared_Pp[i]  = 0; Smeared_Ep[i]  = 0;  //default 0 momentum and energy after smearing
			Smeared_Ppi[i] = 0; Smeared_Epi[i] = 0;  //default 0 momentum and energy after smearing
		}

		const double phot_rad_cut = 40;
		const double phot_e_phidiffcut = 30; //electron - photon phi difference cut

		// Creating vectors to store id of particles in the array
		vector <int> ProtonID; vector <int> PiPlusID; vector <int> PiMinusID; vector <int> PhotonID;
		ProtonID.clear(); PiPlusID.clear(); PiMinusID.clear();  PhotonID.clear();

		//Loop for Hadrons
		for (int i = 0; i < nf; i++) {

			// -----------------------------------------------------------------------------------------------------------------------------------------------

			//Start of proton selection

			if (pdgf[i] == 2212  && pf[i] > 0.3) {

				double ProtonWeight = 1.;
				double ProtonPhi_Deg = -999.;
				int ProtonSector = -1; // smithja: just documenting that I added this variable here
				double ProtonTheta_Deg = -999.;
				double ProtonCosTheta = -999.;
				double ProtonMag = -999.;

				if ( fchoice > 0 ) { //GENIE MC

					//Smearing of proton
					double temp_smear_P = gRandom->Gaus(pf[i],reso_p*pf[i]);
					double temp_smear_E = sqrt( temp_smear_P*temp_smear_P + m_prot * m_prot );

					TVector3 V3_prot_corr(temp_smear_P/pf[i] * pxf[i],temp_smear_P/pf[i] * pyf[i],temp_smear_P/pf[i] * pzf[i]);
					double phi_prot = V3_prot_corr.Phi();
					V3_prot_corr.SetPhi(phi_prot + TMath::Pi()); // Vec.Phi() is between (-180,180), // GENIE coordinate system flipped with respect to CLAS

					//ProtonPhi_Deg = V3_prot_corr.Phi() * 180. / TMath::Pi() + 30.; 
					ProtonPhi_Deg = V3_prot_corr.Phi() * 180. / TMath::Pi()  + 180. + 30.; 
					if (ProtonPhi_Deg > 360.) { ProtonPhi_Deg -= 360.; }
					if (ProtonPhi_Deg < 0.) { ProtonPhi_Deg += 360.; } 
					ProtonSector = int( ProtonPhi_Deg / 60);
					ProtonTheta_Deg = V3_prot_corr.Theta() * 180. / TMath::Pi();
					// apapadop Nov 4 2020: true proton counter for truth level studies above a min theta threshold (12 deg)
					if (PFiducialCutExtra(StoreEnergy, V3_prot_corr)) { TrueProtonsAboveThreshold++; }

//					if (ApplyFiducials) { if (!PFiducialCut(fbeam_en, V3_prot_corr) ) { continue; } } // Proton theta & phi fiducial cuts
					if (ApplyFiducials) { if (!PFiducialCut(StoreEnergy, V3_prot_corr) ) { continue; } } // Proton theta & phi fiducial cuts

					num_p = num_p + 1;
					index_p[num_p - 1] = i;
					ProtonID.push_back(i);
					Smeared_Pp[num_p - 1] = temp_smear_P;
					Smeared_Ep[num_p - 1] = temp_smear_E;

					phi_prot += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS
					ProtonCosTheta = V3_prot_corr.CosTheta(); 
					ProtonMag = V3_prot_corr.Mag(); 

					//acceptance_c takes phi in radians and here unmodified by 30 degree.
					ProtonWeight = wght*acceptance_c(ProtonMag,ProtonCosTheta, phi_prot, 2212,file_acceptance_p,ApplyAccWeights);
					if ( fabs(ProtonWeight) != ProtonWeight ) { continue; } 

				}
				else { // CLAS data does not need Fiducial Cut again

					num_p = num_p + 1;
					index_p[num_p - 1] = i;
					ProtonID.push_back(i);

					TVector3 V3_prot_corr(pxf[i+60],pyf[i+60],pzf[i+60]);

					//ProtonPhi_Deg = V3_prot_corr.Phi() * 180. / TMath::Pi() + 30.; 
					ProtonPhi_Deg = V3_prot_corr.Phi() * 180. / TMath::Pi() + 180. + 30.; 
					if (ProtonPhi_Deg > 360.) { ProtonPhi_Deg -= 360.; } 
                                        if (ProtonPhi_Deg < 0.) { ProtonPhi_Deg	+= 360.; }
					ProtonSector = int( ProtonPhi_Deg / 60);
					ProtonTheta_Deg = V3_prot_corr.Theta() * 180. / TMath::Pi(); 
					ProtonMag = V3_prot_corr.Mag(); 

				}

				// gchamber: below is cuts on proton angle (this is for every proton corresponding to an electron passing the cuts)
				if (fApplyThetaSliceProt) {

					if ( ProtonTheta_Deg < t_thetaProt_lb->GetVal()) { continue; }
					if ( ProtonTheta_Deg > t_thetaProt_ub->GetVal()) { continue; }

				}
			
				if (fApplyPhiOpeningAngleProt) { 
					if ( TMath::Abs(ProtonPhi_Deg - 30) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 90) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 150) > PhiOpeningAngleProt \
					    && TMath::Abs(ProtonPhi_Deg - 210) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 270) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 330) > PhiOpeningAngleProt ) { 
						continue; 
					} 
				}
				
				if (fApplyPhiSliceProt_Sectors && ProtonSector != (ElectronSector + 3)%6) { continue; }
				if (fApplyProtMomCut && (ProtonMag < t_ProtMom_lb->GetVal() || ProtonMag > t_ProtMom_ub->GetVal())) { continue; } 

				if (ProtonPhi_Deg > 0 && ProtonPhi_Deg < 60) { h2_Proton_Theta_Momentum_FirstSector->Fill(ProtonMag,ProtonTheta_Deg,ProtonWeight); } 
				if (ProtonPhi_Deg > 60 && ProtonPhi_Deg < 120) { h2_Proton_Theta_Momentum_SecondSector->Fill(ProtonMag,ProtonTheta_Deg,ProtonWeight); } 
				if (ProtonPhi_Deg > 120 && ProtonPhi_Deg < 180) { h2_Proton_Theta_Momentum_ThirdSector->Fill(ProtonMag,ProtonTheta_Deg,ProtonWeight); } 
				if (ProtonPhi_Deg > 180 && ProtonPhi_Deg < 240) { h2_Proton_Theta_Momentum_FourthSector->Fill(ProtonMag,ProtonTheta_Deg,ProtonWeight); } 
				if (ProtonPhi_Deg > 240 && ProtonPhi_Deg < 300) { h2_Proton_Theta_Momentum_FifthSector->Fill(ProtonMag,ProtonTheta_Deg,ProtonWeight); } 
				if (ProtonPhi_Deg > 300 && ProtonPhi_Deg < 360) { h2_Proton_Theta_Momentum_SixthSector->Fill(ProtonMag,ProtonTheta_Deg,ProtonWeight); }
		
				h2_Proton_Theta_Phi->Fill( ProtonPhi_Deg,ProtonTheta_Deg,ProtonWeight);
				h2_el_prot_theta_incl->Fill( el_theta,ProtonTheta_Deg,ProtonWeight*WeightIncl);
				h2_el_prot_phi_incl->Fill( el_phi_mod,ProtonPhi_Deg,ProtonWeight*WeightIncl);
				h2_el_prot_mom_incl->Fill( el_momentum,ProtonMag,ProtonWeight*WeightIncl);
				h1_Proton_AccMapWeights->Fill( ProtonWeight);
				h1_Proton_Momentum->Fill( ProtonMag, ProtonWeight);
				h1_Proton_Angle_noweight->Fill( ProtonTheta_Deg);
				h1_Proton_Angle->Fill( ProtonTheta_Deg, ProtonWeight);
				
				h2_el_prot_theta_elSectors_protSectors[ElectronSector][ProtonSector]->Fill(el_theta,ProtonTheta_Deg,ProtonWeight*WeightIncl);
				 
				if (Interaction > -1) {h1_InteractionBreakDown_Omega_NoQ4Weight_Insector_prot_mom[Interaction][ProtonSector]->Fill(ProtonMag,ProtonWeight);}
				//h3_Proton_Mom_Theta_Phi->Fill(ProtonMag,ProtonTheta_Deg,ProtonPhi_Deg,ProtonWeight);

			}

			// -------------------------------------------------------------------------------------------------------------------

			if (pdgf[i] == -211  && pf[i] > 0.15)  { //Pi minus

				double PiMinusWeight = 1.;
				double PiMinusPhi_Deg = -999.;
				double PiMinusTheta_Deg = -999.;
				double PiMinusCosTheta = -999.;
				double PiMinusMag = -999.;

				if ( fchoice > 0) { //GENIE data

					//Smearing of pi minus
					double temp_smear_P = gRandom->Gaus(pf[i],reso_pi*pf[i]);
					double temp_smear_E = sqrt( temp_smear_P*temp_smear_P + m_pion * m_pion );

					TVector3 V3_pi_corr(temp_smear_P/pf[i] * pxf[i],temp_smear_P/pf[i] * pyf[i],temp_smear_P/pf[i] * pzf[i]);
					double phi_pion = V3_pi_corr.Phi();
					V3_pi_corr.SetPhi(phi_pion + TMath::Pi()); // Vec.Phi() is between (-180,180)

					// apapadop Nov 4 2020: true charged pion counter for truth level studies above a min theta threshold 
					// given by a functional form A + B / P

					if (PimiFiducialCutExtra(StoreEnergy, V3_pi_corr)) { 

						TrueChargedPionsAboveThreshold++;
						TruePiMinusAboveThreshold++;

					}

					// Pi_phot_fid_united with +1 is for Piplus and Pi_phot_fid_united with -1 is for Piminus
//					if (ApplyFiducials) { if ( !Pi_phot_fid_united(fbeam_en, V3_pi_corr, -1) ) {  continue; } }
					if (ApplyFiducials) { if ( !Pi_phot_fid_united(StoreEnergy, V3_pi_corr, -1) ) {  continue; } }

					num_pimi = num_pimi + 1;
					num_pi = num_pi + 1;
					num_pi_phot = num_pi_phot + 1;
					num_pi_phot_nonrad = num_pi_phot_nonrad + 1;
					index_pimi[num_pi_phot - 1] = i;
					index_pi[num_pi_phot - 1] = i;
					ind_pi_phot[num_pi_phot - 1] = i;
					PiMinusID.push_back(i);
					charge_pi[num_pi_phot - 1] = -1;
					Smeared_Ppi[num_pi_phot - 1] = temp_smear_P;
					Smeared_Epi[num_pi_phot - 1] = temp_smear_E;

					phi_pion += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS
					PiMinusCosTheta = V3_pi_corr.CosTheta(); 
					PiMinusMag = V3_pi_corr.Mag(); 

					//acceptance_c takes phi in radians and here unmodified by 30 degree.
//					PiMinusWeight = wght * acceptance_c(PiMinusMag,PiMinusCosTheta, phi_pion, -211,file_acceptance,ApplyAccWeights);

					// UNTIL AXEL CREATES THE CORRECT PIMINUS MAP, WE SET THE PIMINUS ACCEPTANCE TO BE 1
//					PiMinusWeight = wght * acceptance_c(PiMinusMag,PiMinusCosTheta, phi_pion, -211,file_acceptance,false);
					PiMinusWeight = wght * acceptance_c(PiMinusMag,PiMinusCosTheta, phi_pion, -211,file_acceptance_pim,true);

					if ( fabs(PiMinusWeight) != PiMinusWeight ) { continue; }

					PiMinusPhi_Deg = V3_pi_corr.Phi() * 180. / TMath::Pi()  + 180. + 30.;
					if (PiMinusPhi_Deg > 360.) { PiMinusPhi_Deg -= 360.; } 
					PiMinusTheta_Deg = V3_pi_corr.Theta() * 180. / TMath::Pi();

				}
				else { // CLAS data does not need Fiducial Cut again
					num_pimi = num_pimi + 1;
					num_pi = num_pi + 1;
					num_pi_phot = num_pi_phot + 1;
					num_pi_phot_nonrad = num_pi_phot_nonrad + 1;
					index_pimi[num_pi_phot - 1] = i;
					index_pi[num_pi_phot - 1] = i;
					ind_pi_phot[num_pi_phot - 1] = i;
					PiMinusID.push_back(i);
					charge_pi[num_pi_phot - 1] = -1;

					TVector3 V3_pi_corr(pxf[i],pyf[i],pzf[i]);

					PiMinusPhi_Deg = V3_pi_corr.Phi() * 180. / TMath::Pi()  + 180. + 30.;
					if (PiMinusPhi_Deg > 360.) { PiMinusPhi_Deg -= 360.; }
					PiMinusTheta_Deg = V3_pi_corr.Theta() * 180. / TMath::Pi(); 
					PiMinusMag = V3_pi_corr.Mag(); 

				}

				h1_PiMinus_AccMapWeights->Fill(PiMinusWeight);
				h1_PiMinus_Momentum->Fill(PiMinusMag,PiMinusWeight);

				//h3_PiMinus_Mom_Theta_Phi->Fill(PiMinusMag,PiMinusTheta_Deg,PiMinusPhi_Deg,PiMinusWeight);

			}

			// -------------------------------------------------------------------------------------------------------------------

			if ( pdgf[i] == 211  && pf[i] > 0.15)  {

				double PiPlusWeight = 1.;
				double PiPlusPhi_Deg = -999.;
				double PiPlusTheta_Deg = -999.;
				double PiPlusCosTheta = -999.;
				double PiPlusMag = -999.;

				if ( fchoice > 0) { //GENIE data
					//Smearing of pi plus
					double temp_smear_P = gRandom->Gaus(pf[i],reso_pi*pf[i]);
					double temp_smear_E = sqrt( temp_smear_P*temp_smear_P + m_pion * m_pion );

					TVector3 V3_pi_corr(temp_smear_P/pf[i] * pxf[i],temp_smear_P/pf[i] * pyf[i],temp_smear_P/pf[i] * pzf[i]);
					double phi_pion = V3_pi_corr.Phi();
					V3_pi_corr.SetPhi(phi_pion + TMath::Pi()); // Vec.Phi() is between (-180,180)

					// apapadop Nov 4 2020: true charged pion counter for truth level studies with min theta threshold (12 deg)

					if (PiplFiducialCutExtra(StoreEnergy, V3_pi_corr)) { 

						TrueChargedPionsAboveThreshold++;
						TruePiPlusAboveThreshold++;

					}

					// Pi_phot_fid_united with +1 is for Piplus and Pi_phot_fid_united with -1 is for Piminus
//					if (ApplyFiducials) { if ( !Pi_phot_fid_united(fbeam_en, V3_pi_corr, 1) )     {  continue; } }
					if (ApplyFiducials) { if ( !Pi_phot_fid_united(StoreEnergy, V3_pi_corr, 1) )     {  continue; } }

					num_pipl = num_pipl + 1;
					num_pi  = num_pi + 1;
					num_pi_phot = num_pi_phot + 1;
					num_pi_phot_nonrad = num_pi_phot_nonrad + 1;
					index_pipl[num_pi_phot - 1] = i;
					index_pi[num_pi_phot - 1] = i;
					ind_pi_phot[num_pi_phot - 1] = i;
					PiPlusID.push_back(i);
					charge_pi[num_pi_phot - 1] = 1;
					Smeared_Ppi[num_pi_phot - 1] = temp_smear_P;
					Smeared_Epi[num_pi_phot - 1] = temp_smear_E;

					phi_pion += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS
					PiPlusCosTheta = V3_pi_corr.CosTheta(); 
					PiPlusMag = V3_pi_corr.Mag(); 

					// acceptance_c takes phi in radians and here unmodified by 30 degree.
					PiPlusWeight = wght * acceptance_c(PiPlusMag,PiPlusCosTheta, phi_pion, 211,file_acceptance_pip,ApplyAccWeights);
					if ( fabs(PiPlusWeight) != PiPlusWeight ) { continue; }

					PiPlusPhi_Deg = V3_pi_corr.Phi() * 180. / TMath::Pi()  + 180. + 30.;
					if (PiPlusPhi_Deg > 360.) { PiPlusPhi_Deg -= 360.; }
					PiPlusTheta_Deg = V3_pi_corr.Theta() * 180. / TMath::Pi();

				}
				else { //CLAS data does not need Fiducial Cut again
					num_pipl = num_pipl + 1;
					num_pi  = num_pi + 1;
					num_pi_phot = num_pi_phot + 1;
					num_pi_phot_nonrad = num_pi_phot_nonrad + 1;
					index_pipl[num_pi_phot - 1] = i;
					ind_pi_phot[num_pi_phot - 1] = i;
					ind_pi_phot[num_pi_phot - 1] = i;
					PiPlusID.push_back(i);
					charge_pi[num_pi_phot - 1] = 1;

					TVector3 V3_pi_corr(pxf[i],pyf[i],pzf[i]);

					PiPlusPhi_Deg = V3_pi_corr.Phi() * 180. / TMath::Pi()  + 180. + 30.;
					if (PiPlusPhi_Deg > 360.) { PiPlusPhi_Deg -= 360.; }
					PiPlusTheta_Deg = V3_pi_corr.Theta() * 180. / TMath::Pi(); 
					PiPlusMag = V3_pi_corr.Mag(); 

				}

				h1_PiPlus_AccMapWeights->Fill(PiPlusWeight);
				h1_PiPlus_Momentum->Fill(PiPlusMag,PiPlusWeight);

				//h3_PiPlus_Mom_Theta_Phi->Fill(PiPlusMag,PiPlusTheta_Deg,PiPlusPhi_Deg,PiPlusWeight);

			}

			// ---------------------------------------------------------------------------------------------------------------------------

			if (pdgf[i] == 22  && pf[i] > 0.3) {

				//Determine photon vector for the cut on radiation photon via angle with respect to the electron
				TVector3 V3_phot_angles(pxf[i],pyf[i],pzf[i]);
				if (fchoice > 0) { //GENIE data
					//no smearing of GENIE photons
					double phi_photon = V3_phot_angles.Phi();
					V3_phot_angles.SetPhi(phi_photon + TMath::Pi()); // Vec.Phi() is between (-180,180)

					// apapadop Nov 4 2020: true photon counter for truth level studies

					if (Phot_fidExtra(V3_phot_angles)) { 
	
						TrueGammasAboveThreshold++;

					}

					if (ApplyFiducials) { if ( !Pi_phot_fid_united(fbeam_en, V3_phot_angles, 0) )  { continue;} }

				}

				double neut_phi_mod = V3_phot_angles.Phi()*TMath::RadToDeg() + 30; //Add 30 degree
				if (neut_phi_mod < 0) neut_phi_mod = neut_phi_mod + 360;  //Neutral particle is between 0 and 360 degree

				ec_num_n = ec_num_n + 1;
				num_pi_phot = num_pi_phot + 1;
				ind_pi_phot[num_pi_phot - 1] = i;
				PhotonID.push_back(i);

				Smeared_Ppi[num_pi_phot - 1] = V3_phot_angles.Mag();
				Smeared_Epi[num_pi_phot - 1] = V3_phot_angles.Mag();

				CosDeltaThetaElectronPhotonAboveThreshold->Fill( cos( V3_phot_angles.Angle(V3_el) ) );
				CosDeltaPhiElectronPhotonAboveThreshold->Fill( cos( neut_phi_mod-el_phi_mod*TMath::Pi()/180. ) );

				 // within 40 degrees in theta and 30 degrees in phi. Electron phi has already added 30 degree and between 0 to 360

				 if(V3_phot_angles.Angle(V3_el)*TMath::RadToDeg() < phot_rad_cut && fabs(neut_phi_mod-el_phi_mod) < phot_e_phidiffcut ) {

					ec_radstat_n[num_pi_phot - 1] = true; // select radiation photons
					num_phot_rad = num_phot_rad + 1;

				 }

				 if(!ec_radstat_n[num_pi_phot - 1]) {

					num_phot_nonrad = num_phot_nonrad + 1;

					num_pi_phot_nonrad = num_pi_phot_nonrad + 1;
					charge_pi[num_pi_phot - 1] = 0;

					double GammaPhi_Deg = neut_phi_mod;
					double GammaTheta_Deg = V3_phot_angles.Theta()*TMath::RadToDeg();
					double GammaMag = V3_phot_angles.Mag();
					double GammaWeight = wght;

				 }

			}

		} // end of hadron loop

		// ----------------------------------------------------------------------------------------------------------------------------

		// Truth level studies
		// Requiring true level signal 1e 1p 0pi+/- 0 gammas
		// With smearing / fiducial cuts / acceptance maps

		if (TruthLevel1p0piSignalStudy || TruthLevel0piSignalStudy) {

			if (TrueElectronsAboveThreshold != 1) { continue; }
			if (TruthLevel1p0piSignalStudy) { if (TrueProtonsAboveThreshold != 1) { continue; } }
			if (TrueChargedPionsAboveThreshold != 0) { continue; }
//			if (TruePiPlusAboveThreshold != 0) { continue; }
//			if (TruePiMinusAboveThreshold != 0) { continue; }
			if (TrueGammasAboveThreshold != 0) { continue; }

		}

		// ----------------------------------------------------------------------------------------------------------------------------

		// apapadop: executive decision Dec 3
		// given that genie has much higher proton multiplicities than we observe in data
		// we ignore the num_p > 4 cases 

		//if (num_p > 4) { continue; }

		//Skip event if there is at least one radiation photon

		if (num_phot_rad > 0) {
			continue;
		}


		// -----------------------------------------------------------------------------------------------------------------------------

		// Filling Histograms with multiplicities

		h2_N_prot_pi->Fill(num_pi,num_p);
		h2_N_prot_pi_phot->Fill(num_pi+ec_num_n,num_p);
		h2_N_prot_pi_phot_nonrad->Fill(num_pi_phot_nonrad,num_p);
		h2_N_pi_phot[num_p]->Fill(ec_num_n,num_pi);

		// Events with exactly 2 protons

		if (num_p == 2) {

			//LorentzVectors for protons without momentum smearing or corrections
			TLorentzVector V4_prot_uncorr1(pxf[index_p[0]],pyf[index_p[0]],pzf[index_p[0]],TMath::Sqrt(m_prot*m_prot+pf[index_p[0]]*pf[index_p[0]]));
			TLorentzVector V4_prot_uncorr2(pxf[index_p[1]],pyf[index_p[1]],pzf[index_p[1]],TMath::Sqrt(m_prot*m_prot+pf[index_p[1]]*pf[index_p[1]]));
			//LorentzVectors for protons with momentum smearing or corrections
			TVector3 V3_prot_corr1;
			TVector3 V3_prot_corr2;

			double p_acc_ratio1 = 1; //will be 1 for CLAS data
			double p_acc_ratio2 = 1; //will be 1 for CLAS data

			if (fchoice == 0) { //CLAS data
				V3_prot_corr1.SetXYZ(pxf[index_p[0]+60],pyf[index_p[0]+60],pzf[index_p[0]+60]);
				V3_prot_corr2.SetXYZ(pxf[index_p[1]+60],pyf[index_p[1]+60],pzf[index_p[1]+60]);
			}

			if (fchoice > 0) { //GENIE data, fiducials are done in hadron loop

				V3_prot_corr1.SetXYZ(Smeared_Pp[0]/pf[index_p[0]] * pxf[index_p[0]],Smeared_Pp[0]/pf[index_p[0]] * pyf[index_p[0]],Smeared_Pp[0]/pf[index_p[0]] * pzf[index_p[0]]);
				double phi_prot1 = V3_prot_corr1.Phi();
				V3_prot_corr1.SetPhi(phi_prot1 + TMath::Pi()); // Vec.Phi() is between (-180,180), // GENIE coordinate system flipped with respect to CLAS
				phi_prot1 += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS

				double p_theta1 = V3_prot_corr1.Theta();
				double prot_mom_corr1 = V3_prot_corr1.Mag();
				//Proton 1 weight
				p_acc_ratio1 = acceptance_c(prot_mom_corr1, cos(p_theta1), phi_prot1, 2212,file_acceptance_p,ApplyAccWeights);
				if ( fabs(p_acc_ratio1) != p_acc_ratio1 ) { continue; }

				V3_prot_corr2.SetXYZ(Smeared_Pp[1]/pf[index_p[1]] * pxf[index_p[1]],Smeared_Pp[1]/pf[index_p[1]] * pyf[index_p[1]],Smeared_Pp[1]/pf[index_p[1]] * pzf[index_p[1]]);
				double phi_prot2 = V3_prot_corr2.Phi();
 				V3_prot_corr2.SetPhi(phi_prot2 + TMath::Pi()); // Vec.Phi() is between (-180,180) // GENIE coordinate system flipped with respect to CLAS
				phi_prot2 += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS

				double p_theta2 = V3_prot_corr2.Theta();
				double prot_mom_corr2 = V3_prot_corr2.Mag();
				//Proton 2 weight
				p_acc_ratio2 = acceptance_c(prot_mom_corr2, cos(p_theta2), phi_prot2, 2212,file_acceptance_p,ApplyAccWeights);
				if ( fabs(p_acc_ratio2) != p_acc_ratio2 ) { continue; }

			}

			//Total proton weight
			double weight_protons = p_acc_ratio1 * p_acc_ratio2;

			TVector3 V3_2prot_uncorr[2];
			V3_2prot_uncorr[0] = V4_prot_uncorr1.Vect();
			V3_2prot_uncorr[1] = V4_prot_uncorr2.Vect();

			TVector3 V3_2prot_corr[2];
			V3_2prot_corr[0] = V3_prot_corr1;
			V3_2prot_corr[1] = V3_prot_corr2;
			
			int proton_sectr[2];
			for(int f= 0; f < 2; f++) {
			double ProtonPhi_Deg1 = V3_2prot_corr[f].Phi() *180. / TMath::Pi() + 30;
                         if (ProtonPhi_Deg1 > 360.) { ProtonPhi_Deg1 -= 360.; }
                           if (ProtonPhi_Deg1 < 0.) { ProtonPhi_Deg1 += 360.; }
                           proton_sectr[f] = ProtonPhi_Deg1 / 60;
			}
			 bool same_sector_bool = false;
			if (proton_sectr[0] != proton_sectr[1]) {
                               two_proton_same_sector++;
                         }
	
			
			//---------------------------------- 2p 0pi->  1p0pi   ----------------------------------------------

			double E_tot_2p[2]={0};
			double p_perp_tot_2p[2]={0};
			double N_prot_both = 0;
			double P_N_2p[2]={0};

			rotation->prot2_rot_func( V3_2prot_corr, V3_2prot_uncorr, V4_el, E_tot_2p, p_perp_tot_2p, P_N_2p , &N_prot_both);

			if (num_pi_phot == 0 && N_prot_both != 0){

				double histoweight = weight_protons*e_acc_ratio*wght/Mott_cross_sec; //total weight from 2p acceptance , 1e acceptance, Mott, and GENIE weight

				for (int f = 0; f < num_p; f++) { // Looping through two protons
					
					h2_pperp_W->Fill(W_var,p_perp_tot_2p[f],-P_N_2p[f]*histoweight);
					h1_theta0->Fill((V4_beam.Vect()).Angle(V4_el.Vect()+V3_2prot_uncorr[f]) *TMath::RadToDeg(),-P_N_2p[f]*histoweight);

					double ProtonPhi_Deg = V3_2prot_corr[f].Phi() *180. / TMath::Pi() + 30;
					//double ProtonPhi_Deg = V3_2prot_corr[f].Phi() *180. / TMath::Pi() + 180 + 30; // smithja: commented out on 9/22/2021; 180-degree shift not needed here
					if (ProtonPhi_Deg > 360.) { ProtonPhi_Deg -= 360.; }
					if (ProtonPhi_Deg < 0.) { ProtonPhi_Deg += 360.; } 
					int ProtonSector = ProtonPhi_Deg / 60;
					double ProtonTheta_Deg = V3_2prot_corr[f].Theta() *180. / TMath::Pi();
					double ProtonMag = V3_2prot_corr[f].Mag();
					double ProtonTK = sqrt(ProtonMag*ProtonMag + m_prot*m_prot) - m_prot;
					double Em = (nu - ProtonTK);
					TVector3 pmiss_vec =  V3_rot_q - V3_2prot_corr[f];				
					double pmiss = pmiss_vec.Mag();
					double ThetaPQ = V3_rot_q.Angle(V3_2prot_corr[f]) * 180. / TMath::Pi();                              
	 
					if (Em > Em_ub)  {continue;}

					if(ThetaPQ > theta_pq_cut) { continue; }//Looking at ThetaPQ cut

					// gchamber: below are cuts on proton angles. These cuts are in each topology block	
					if (fApplyThetaSliceProt) {  // hard coded range for now
						if ( ProtonTheta_Deg < t_thetaProt_lb->GetVal()) { continue; }
						if ( ProtonTheta_Deg > t_thetaProt_ub->GetVal()) { continue; }
					}


			
        	        if (fApplyPhiOpeningAngleProt) {
                	        if ( TMath::Abs(ProtonPhi_Deg - 30) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 90) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 150) > PhiOpeningAngleProt \
                        	    && TMath::Abs(ProtonPhi_Deg - 210) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 270) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 330) > PhiOpeningAngleProt ) {
                                	continue; 
                        	}  
                	}

                    if (fApplyPhiSliceProt_Sectors && ProtonSector != (ElectronSector + 3)%6) { 
						same_sector_bool = false;
						continue; 
					} 
                    if (fApplyProtMomCut && (ProtonMag < t_ProtMom_lb->GetVal() || ProtonMag > t_ProtMom_ub->GetVal())) { continue; }


					h2_el_CosTheta_E->Fill(V3_el.CosTheta(),V4_el.E(),-P_N_2p[f]*histoweight);


					if (el_theta >= t_thetaEl_lb->GetVal() && el_theta <= t_thetaEl_ub->GetVal()) { // smithja: there looks to be continue statements above that already necessitate this condition
						if (p_perp_tot_2p[f] < PtMax && Interaction > -1) {h1_InteractionBreakdown_Omega_NoQ4Weight_InSector_el_mom_ptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4); }
                                                if (Interaction > -1) {
							h1_InteractionBreakDown_Omega_NoQ4Weight_InSector_el_mom_noptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4);
							h1_InteractionBreakDown_Omega_NoQ4Weight_Insector_prot_mom_QE[Interaction][ProtonSector]->Fill( ProtonMag, -P_N_2p[f]*histoweight); // smithja: might have to adjust ProtonSector
							if(hitnuc == 2212) h1_hit_nuc_pass->Fill(1,-P_N_2p[f]*histoweight);
							if(hitnuc == 2112) h1_hit_nuc_pass->Fill(2,-P_N_2p[f]*histoweight);

							h1_InteractionBreakDown_InSector_Em[Interaction][ProtonSector]->Fill(Em, -P_N_2p[f]*histoweight);
							h1_InteractionBreakDown_InSector_Pm[Interaction][ProtonSector]->Fill(pmiss, -P_N_2p[f]*histoweight);
							h2_InteractionBreakDown_InSector_EmPm[Interaction][ProtonSector]->Fill(Em,pmiss, -P_N_2p[f]*histoweight);
							h1_InteractionBreakDown_ThetaPQ[Interaction][ProtonSector]->Fill(ThetaPQ,-P_N_2p[f]*histoweight); 
							h1_InteractionBreakDown_InSector_el_mom_Emcut[Interaction][ProtonSector]->Fill(el_momentum,-P_N_2p[f]*histoweight);

                                                        if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][0]->Fill( ProtonMag, -P_N_2p[f]*histoweight); }
							if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][1]->Fill( ProtonMag, -P_N_2p[f]*histoweight); }
						}
					}
					
					h2_Electron_Theta_Phi->Fill( el_phi_mod, V3_el.Theta()*180./TMath::Pi(), -P_N_2p[f]*histoweight);
					h1_InteractionBreakDown_NoQ4Weight_InSector_el_theta[Interaction][ElectronSector]->Fill( V3_el.Theta()*180./TMath::Pi(), -P_N_2p[f]*histoweight);
                                        h1_InteractionBreakDown_NoQ4Weight_InSector_prot_theta[Interaction][ProtonSector]->Fill( ProtonTheta_Deg, -P_N_2p[f]*histoweight); // smithja: might have to adjust ProtonSector
					if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][0]->Fill( ProtonTheta_Deg, -P_N_2p[f]*histoweight); }
					if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][1]->Fill( ProtonTheta_Deg, -P_N_2p[f]*histoweight); }

					double prot_phi_plot = ProtonPhi_Deg; // smithja: alias ProtonPhi_Deg for plotting purposes in h2_prot_theta_phi
					if (prot_phi_plot < 0.) { prot_phi_plot += 360.; } // smithja: this statement puts the proton phi in the correct range for plotting; a similar statement making sure ProtonPhi_Deg is below 360
											   //          degrees is included towards the top of this code, so the only modification to prot_phi_plot needed is what's shown in this statement
					h2_prot_theta_phi->Fill( prot_phi_plot, ProtonTheta_Deg, -P_N_2p[f]*histoweight);	

					// smithja: These TH2s are used to investigate correlations between proton momtentum and other variables.
					h2_prot_mom_el_phi->Fill( el_phi_mod, ProtonMag, -P_N_2p[f]*histoweight); 
					h2_prot_mom_el_theta->Fill( V3_el.Theta()*180./TMath::Pi(),ProtonMag, -P_N_2p[f]*histoweight);
					h2_prot_mom_el_mom->Fill( el_momentum, ProtonMag, -P_N_2p[f]*histoweight); 
					h2_prot_mom_phi->Fill( prot_phi_plot, ProtonMag, -P_N_2p[f]*histoweight);
					h2_prot_mom_theta->Fill( ProtonTheta_Deg, ProtonMag, -P_N_2p[f]*histoweight);
					
					h1_el_mom_corr->Fill(V4_el.Rho(),-P_N_2p[f]*histoweight);
					// gchamber: for each topology block, h1_prot_mom can be weighted with -P_N_2p[f]*histoweight, 1/(-P_N_2p[f]*histoweight), or ProtonWeight (inclusive weight). Comment/uncomment the h1_prot_mom->Fill() lines below to choose (do this for all 13 blocks)
					//h1_prot_mom->Fill( ProtonMag, -P_N_2p[f]*histoweight);
					h1_histoweight->Fill(-P_N_2p[f]*histoweight);
					h1_histoweight2->Fill(-P_N_2p[f]);
					//if (-P_N_2p[f]*histoweight == 0) {h1_prot_mom->Fill( ProtonMag, -P_N_2p[f]*histoweight);}
					//if (-P_N_2p[f]*histoweight != 0) {h1_prot_mom->Fill( ProtonMag, 1/(-P_N_2p[f]*histoweight));}
					
					h1_el_prot_phi_diff->Fill(el_phi_mod-ProtonPhi_Deg,-P_N_2p[f]*histoweight);
					h2_el_prot_theta->Fill(el_theta,ProtonTheta_Deg,-P_N_2p[f]*histoweight);
					h2_el_prot_phi->Fill(el_phi_mod,ProtonPhi_Deg,-P_N_2p[f]*histoweight);
					h2_el_prot_mom->Fill(V4_el.Rho(), ProtonMag, -P_N_2p[f]*histoweight);

					h2_Electron_Theta_Momentum->Fill(V4_el.Rho(),V3_el.Theta()*180./TMath::Pi(),-P_N_2p[f]*histoweight);
					h2_Proton_Theta_Momentum->Fill( ProtonMag, V3_2prot_corr[f].Theta()*180./TMath::Pi(),-P_N_2p[f]*histoweight);
					h1_prot_theta->Fill(V3_2prot_corr[f].Theta()*180/TMath::Pi(),-P_N_2p[f]*histoweight);
					h1_prot_theta_noweight->Fill(V3_2prot_corr[f].Theta()*180/TMath::Pi());
					h1_prot_costheta->Fill(V3_2prot_corr[f].CosTheta(),-P_N_2p[f]*histoweight);
					
					double LocalWeight = -P_N_2p[f]*histoweight;

					// -----------------------------------------------------------------------------------------------
					// Reconstruct xB, W, Q2 using Ecal instead of Etrue

					CalKineVars = CalculateCalKineVars(E_tot_2p[f],V4_el);

					// Fill plots based on underlying interactions

					Q2_BreakDown[0]->Fill(reco_Q2,LocalWeight);
					Nu_BreakDown[0]->Fill(nu,LocalWeight);
					Pe_BreakDown[0]->Fill(V4_el.Rho(),LocalWeight);
					
			
					// ---------------------------------------------------------------------------------------------------------------------	

					double PTmiss = p_perp_tot_2p[f];
					double Ecal = E_tot_2p[f];	

					// ---------------------------------------------------------------------------------------------------------------------
						

					//h1_EePrime_InCosThetaEPrimeSlices[CosThetaEPrimeSlice]->Fill(V4_el.E(),LocalWeight);				

 					if (fchoice > 0) {

						Q2_BreakDown[Interaction]->Fill(reco_Q2,LocalWeight);
						Nu_BreakDown[Interaction]->Fill(nu,LocalWeight);
						Pe_BreakDown[Interaction]->Fill(V4_el.Rho(),LocalWeight);

					}

					// -----------------------------------------------------------------------------------------------


				} //looping through two protons

			}//no pion cut and N_prot_both!=0
			//---------------------------------- 2p 1pi   ----------------------------------------------
			//Const int can be placed somewhere up after if for 2 protons F.H. 05.09.19
			const int N_2prot=2;
			//Variable might/could be placed in a more local context F.H. 05.09.19
			double Ecal_2p1pi_to2p0pi[N_2prot]={0};
			double Ecal_2p1pi_to1p1pi[N_2prot]={0};
			double Ecal_2p1pi_to1p0pi[N_2prot]={0};
			double p_miss_perp_2p1pi_to2p0pi[N_2prot]={0};
			double p_miss_perp_2p1pi_to1p1pi[N_2prot]={0};
			double p_miss_perp_2p1pi_to1p0pi[N_2prot]={0};

			if (num_pi_phot == 1) {

				TVector3 V3_1pi_corr;
				double pion_acc_ratio = 1;

				if (fchoice == 0) { //CLAS data
					V3_1pi_corr.SetXYZ(pxf[ind_pi_phot[0]],pyf[ind_pi_phot[0]],pzf[ind_pi_phot[0]]);
				}

				if (fchoice > 0) { //GENIE data
					pion_acc_ratio = 0;//reset to 0 just to be save
					V3_1pi_corr.SetXYZ(Smeared_Ppi[0]/pf[ind_pi_phot[0]] * pxf[ind_pi_phot[0]],Smeared_Ppi[0]/pf[ind_pi_phot[0]] * pyf[ind_pi_phot[0]],Smeared_Ppi[0]/pf[ind_pi_phot[0]] * pzf[ind_pi_phot[0]]);

					double phi_pion = V3_1pi_corr.Phi();
					V3_1pi_corr.SetPhi(phi_pion + TMath::Pi()); // Vec.Phi() is between (-180,180)
					phi_pion += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS

					double pion_theta = V3_1pi_corr.Theta();
					double pion_mom_corr = V3_1pi_corr.Mag();

					if (charge_pi[0] == 1) { //acceptance for pi plus
						pion_acc_ratio = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, 211, file_acceptance_pip,ApplyAccWeights);
						if ( fabs(pion_acc_ratio) != pion_acc_ratio ) { continue; }
					}
					else if (charge_pi[0] == -1) {    //acceptance for pi minus. using electron acceptance map

						//pion_acc_ratio = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,ApplyAccWeights);

						// UNTIL AXEL CREATES THE CORRECT PIMINUS MAP, WE SET THE PIMINUS ACCEPTANCE TO BE 1
//						pion_acc_ratio = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,false);
						pion_acc_ratio = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance_pim,true);

						if ( fabs(pion_acc_ratio) != pion_acc_ratio ) { continue; }
					}
					else if (charge_pi[0] == 0) {    //acceptance for neutral, setting to 1 for now F.H. 09/24/19
						pion_acc_ratio = 1;
					}
					else { std::cout << "WARNING: 2proton and 1 Pion loop. pion_acc_ratio is still 0. Continue with next event " << std::endl;	continue; }
				}

				double P_2p1pito2p0pi[2] = {0};
				double P_2p1pito1p1pi[2] = {0};
				double P_2p1pito1p0pi[2] = {0};
				double Ptot = 0;

				rotation->prot2_pi1_rot_func(V3_2prot_corr,V3_2prot_uncorr,V3_1pi_corr, charge_pi[0], V4_el,Ecal_2p1pi_to2p0pi,p_miss_perp_2p1pi_to2p0pi,P_2p1pito2p0pi, P_2p1pito1p1pi, P_2p1pito1p0pi,&Ptot);

				double histoweight = pion_acc_ratio * weight_protons * e_acc_ratio * wght/Mott_cross_sec; 
				//Is this correct in the following loop? F.H. 09/01/19

				for (int z=0; z < N_2prot; z++){ //looping over two protons

					//---------------------------------- 2p 1pi ->2p 0pi ----------------------------------------------

					h2_pperp_W->Fill(W_var,p_miss_perp_2p1pi_to2p0pi[z],P_2p1pito2p0pi[z]*histoweight);
					h1_theta0->Fill((V4_beam.Vect()).Angle(V4_el.Vect()+V3_2prot_uncorr[z]) *TMath::RadToDeg(),P_2p1pito2p0pi[z]*histoweight);
		
					double ProtonPhi_Deg = V3_2prot_corr[z].Phi() *180. / TMath::Pi() + 30;
					//double ProtonPhi_Deg = V3_2prot_corr[z].Phi() *180. / TMath::Pi() + 180 + 30; // smithja: commented out on 9/22/2021; 180-degree shift not needed here
					if (ProtonPhi_Deg > 360.) { ProtonPhi_Deg -= 360.; } 
					if (ProtonPhi_Deg < 0.)	{ ProtonPhi_Deg	+= 360.; }
                                        int ProtonSector = ProtonPhi_Deg / 60;					
					double ProtonTheta_Deg = V3_2prot_corr[z].Theta() *180. / TMath::Pi();
					double ProtonMag = V3_2prot_corr[z].Mag();
					double ProtonTK = sqrt(ProtonMag*ProtonMag + m_prot*m_prot) - m_prot;
					double Em = (nu - ProtonTK);
					TVector3 pmiss_vec =  V3_rot_q - V3_2prot_corr[z];				
					double pmiss = pmiss_vec.Mag();
					double ThetaPQ = V3_rot_q.Angle(V3_2prot_corr[z]) * 180. / TMath::Pi();		
                    
                    if (Em > Em_ub)  {continue;}

					if(ThetaPQ > theta_pq_cut) { continue; }//Looking at ThetaPQ cut
					
					if (fApplyThetaSliceProt) {  // hard coded range for now
						if ( ProtonTheta_Deg < t_thetaProt_lb->GetVal()) { continue; }
						if ( ProtonTheta_Deg > t_thetaProt_ub->GetVal()) { continue; }
					}
			
	            	if (fApplyPhiOpeningAngleProt) {
	                    	if ( TMath::Abs(ProtonPhi_Deg - 30) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 90) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 150) > PhiOpeningAngleProt \
	                    	    && TMath::Abs(ProtonPhi_Deg - 210) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 270) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 330) > PhiOpeningAngleProt ) {
	            	                continue; 
	    	                }  
	                }

                    if (fApplyPhiSliceProt_Sectors && ProtonSector != (ElectronSector + 3)%6) { continue; } 
                    if (fApplyProtMomCut && (ProtonMag < t_ProtMom_lb->GetVal() || ProtonMag > t_ProtMom_ub->GetVal())) { continue; }

	
					h2_el_CosTheta_E->Fill(V3_el.CosTheta(),V4_el.E(),P_2p1pito2p0pi[z]*histoweight);


					if (el_theta >= t_thetaEl_lb->GetVal() && el_theta <= t_thetaEl_ub->GetVal()) { // smithja: there looks to be continue statements above that already necessitate this condition
						if (p_miss_perp_2p1pi_to2p0pi[z] < PtMax && Interaction > -1) {h1_InteractionBreakdown_Omega_NoQ4Weight_InSector_el_mom_ptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4); }
                                                if (Interaction > -1) {
							h1_InteractionBreakDown_Omega_NoQ4Weight_InSector_el_mom_noptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4);
							h1_InteractionBreakDown_Omega_NoQ4Weight_Insector_prot_mom_QE[Interaction][ProtonSector]->Fill( ProtonMag, P_2p1pito2p0pi[z]*histoweight);

								if(hitnuc == 2212) h1_hit_nuc_pass->Fill(1,P_2p1pito2p0pi[z]*histoweight);
	                            if(hitnuc == 2112) h1_hit_nuc_pass->Fill(2,P_2p1pito2p0pi[z]*histoweight);

							h1_InteractionBreakDown_InSector_Em[Interaction][ProtonSector]->Fill(Em, P_2p1pito2p0pi[z]*histoweight);
							h1_InteractionBreakDown_InSector_Pm[Interaction][ProtonSector]->Fill(pmiss, P_2p1pito2p0pi[z]*histoweight);
							h2_InteractionBreakDown_InSector_EmPm[Interaction][ProtonSector]->Fill(Em,pmiss, P_2p1pito2p0pi[z]*histoweight);
							h1_InteractionBreakDown_ThetaPQ[Interaction][ProtonSector]->Fill(ThetaPQ,P_2p1pito2p0pi[z]*histoweight); 
							h1_InteractionBreakDown_InSector_el_mom_Emcut[Interaction][ProtonSector]->Fill(el_momentum,P_2p1pito2p0pi[z]*histoweight);

							if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][0]->Fill( ProtonMag, P_2p1pito2p0pi[z]*histoweight); }
                                                        if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][1]->Fill( ProtonMag, P_2p1pito2p0pi[z]*histoweight); }
						}
					}

					h2_Electron_Theta_Phi->Fill( el_phi_mod, V3_el.Theta()*180./TMath::Pi(), P_2p1pito2p0pi[z]*histoweight);
                                        h1_InteractionBreakDown_NoQ4Weight_InSector_el_theta[Interaction][ElectronSector]->Fill( V3_el.Theta()*180./TMath::Pi(), P_2p1pito2p0pi[z]*histoweight);
                                        h1_InteractionBreakDown_NoQ4Weight_InSector_prot_theta[Interaction][ProtonSector]->Fill( ProtonTheta_Deg, P_2p1pito2p0pi[z]*histoweight); // smithja: might have to adjust ProtonSector
					if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][0]->Fill( ProtonTheta_Deg, P_2p1pito2p0pi[z]*histoweight); }
                                        if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][1]->Fill( ProtonTheta_Deg, P_2p1pito2p0pi[z]*histoweight); }

					double prot_phi_plot = ProtonPhi_Deg; // smithja: alias	ProtonPhi_Deg for plotting purposes in h2_prot_theta_phi
                                        if (prot_phi_plot < 0.)	{ prot_phi_plot += 360.; } // smithja: this statement puts the proton phi in the correct range for plotting; a similar statement making	sure ProtonPhi_Deg is below 360
                                                                                           //          degrees is included towards the top of this code, so the only modification to prot_phi_plot needed is what's shown in this statement
					h2_prot_theta_phi->Fill( prot_phi_plot, ProtonTheta_Deg, P_2p1pito2p0pi[z]*histoweight);	
					PassCounter3 ++;

                                        // smithja: These TH2s are used to investigate correlations between proton momtentum and other variables.
                                        h2_prot_mom_el_phi->Fill( el_phi_mod, ProtonMag, P_2p1pito2p0pi[z]*histoweight);
                                        h2_prot_mom_el_theta->Fill( V3_el.Theta()*180./TMath::Pi(), ProtonMag, P_2p1pito2p0pi[z]*histoweight);
                                        h2_prot_mom_el_mom->Fill( el_momentum, ProtonMag, P_2p1pito2p0pi[z]*histoweight);
                                        h2_prot_mom_phi->Fill( prot_phi_plot, ProtonMag, P_2p1pito2p0pi[z]*histoweight);
                                        h2_prot_mom_theta->Fill( ProtonTheta_Deg, ProtonMag, P_2p1pito2p0pi[z]*histoweight);			
	
					h1_el_mom_corr->Fill(V4_el.Rho(),P_2p1pito2p0pi[z]*histoweight);
					//h1_prot_mom->Fill( ProtonMag, P_2p1pito2p0pi[z]*histoweight);
					h1_histoweight->Fill(P_2p1pito2p0pi[z]*histoweight);
					h1_histoweight2->Fill(P_2p1pito2p0pi[z]);
					//if (P_2p1pito2p0pi[z]*histoweight == 0) {h1_prot_mom->Fill( ProtonMag, P_2p1pito2p0pi[z]*histoweight);}
					//if (P_2p1pito2p0pi[z]*histoweight != 0) {h1_prot_mom->Fill( ProtonMag, 1/(P_2p1pito2p0pi[z]*histoweight));}

					h1_el_prot_phi_diff->Fill(el_phi_mod-ProtonPhi_Deg,P_2p1pito2p0pi[z]*histoweight);
					h2_el_prot_theta->Fill(el_theta,ProtonTheta_Deg,P_2p1pito2p0pi[z]*histoweight);
					h2_el_prot_phi->Fill(el_phi_mod,ProtonPhi_Deg,P_2p1pito2p0pi[z]*histoweight);
					h2_el_prot_mom->Fill(V4_el.Rho(), ProtonMag, P_2p1pito2p0pi[z]*histoweight);

					double LocalWeight = P_2p1pito2p0pi[z]*histoweight;

					h2_Electron_Theta_Momentum->Fill(V4_el.Rho(),V3_el.Theta()*180./TMath::Pi(),P_2p1pito2p0pi[z]*histoweight);
					h2_Proton_Theta_Momentum->Fill( ProtonMag, V3_2prot_corr[z].Theta()*180./TMath::Pi(),P_2p1pito2p0pi[z]*histoweight);
					h1_prot_theta->Fill(V3_2prot_corr[z].Theta()*180./TMath::Pi(),P_2p1pito2p0pi[z]*histoweight);
					h1_prot_theta_noweight->Fill(V3_2prot_corr[z].Theta()*180./TMath::Pi());
					h1_prot_costheta->Fill(V3_2prot_corr[z].CosTheta(),P_2p1pito2p0pi[z]*histoweight);

					// -----------------------------------------------------------------------------------------------
					// Reconstruct xB, W, Q2 using Ecal instead of Etrue

					CalKineVars = CalculateCalKineVars(Ecal_2p1pi_to2p0pi[z],V4_el);

					// Fill plots based on underlying interactions

					Q2_BreakDown[0]->Fill(reco_Q2,LocalWeight);
					Nu_BreakDown[0]->Fill(nu,LocalWeight);
					Pe_BreakDown[0]->Fill(V4_el.Rho(),LocalWeight);

					// ---------------------------------------------------------------------------------------------------------------------	

					double PTmiss = p_miss_perp_2p1pi_to2p0pi[z];
					double Ecal = Ecal_2p1pi_to2p0pi[z];

					// ---------------------------------------------------------------------------------------------------------------------				 								

					//h1_EePrime_InCosThetaEPrimeSlices[CosThetaEPrimeSlice]->Fill(V4_el.E(),LocalWeight);				
				

 					if (fchoice > 0) {

						Q2_BreakDown[Interaction]->Fill(reco_Q2,LocalWeight);
						Nu_BreakDown[Interaction]->Fill(nu,LocalWeight);
						Pe_BreakDown[Interaction]->Fill(V4_el.Rho(),LocalWeight);			

					}

					// -----------------------------------------------------------------------------------------------


					//---------------------------------- 2p 1pi ->1p 1pi   ----------------------------------------------
					
					h2_pperp_W->Fill(W_var,p_perp_tot_2p[z],P_2p1pito1p1pi[z]*histoweight);
					h1_theta0->Fill((V4_beam.Vect()).Angle(V4_el.Vect()+V3_2prot_uncorr[z])*TMath::RadToDeg(),P_2p1pito1p1pi[z]*histoweight);

					
					h2_el_CosTheta_E->Fill(V3_el.CosTheta(),V4_el.E(),P_2p1pito1p1pi[z]*histoweight);


					if (el_theta >= t_thetaEl_lb->GetVal() && el_theta <= t_thetaEl_ub->GetVal()) { // smithja: there looks to be continue statements above that already necessitate this condition
						if (p_perp_tot_2p[z] < PtMax && Interaction > -1) {h1_InteractionBreakdown_Omega_NoQ4Weight_InSector_el_mom_ptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4); }
                                                if (Interaction > -1) {
							h1_InteractionBreakDown_Omega_NoQ4Weight_InSector_el_mom_noptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4);
							h1_InteractionBreakDown_Omega_NoQ4Weight_Insector_prot_mom_QE[Interaction][ProtonSector]->Fill( ProtonMag, P_2p1pito1p1pi[z]*histoweight);
                            					if(hitnuc == 2212) h1_hit_nuc_pass->Fill(1,P_2p1pito1p1pi[z]*histoweight);
	                                                        if(hitnuc == 2112) h1_hit_nuc_pass->Fill(2,P_2p1pito1p1pi[z]*histoweight);

							h1_InteractionBreakDown_InSector_Em[Interaction][ProtonSector]->Fill(Em, P_2p1pito1p1pi[z]*histoweight);
							h1_InteractionBreakDown_InSector_Pm[Interaction][ProtonSector]->Fill(pmiss, P_2p1pito1p1pi[z]*histoweight);
							h2_InteractionBreakDown_InSector_EmPm[Interaction][ProtonSector]->Fill(Em,pmiss, P_2p1pito1p1pi[z]*histoweight);
							h1_InteractionBreakDown_ThetaPQ[Interaction][ProtonSector]->Fill(ThetaPQ,P_2p1pito1p1pi[z]*histoweight); 
							h1_InteractionBreakDown_InSector_el_mom_Emcut[Interaction][ProtonSector]->Fill(el_momentum,P_2p1pito1p1pi[z]*histoweight);

                                                        if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][0]->Fill( ProtonMag, P_2p1pito1p1pi[z]*histoweight); }
                                                        if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][1]->Fill( ProtonMag, P_2p1pito1p1pi[z]*histoweight); }
						}
					}

					h2_Electron_Theta_Phi->Fill( el_phi_mod, V3_el.Theta()*180./TMath::Pi(), P_2p1pito1p1pi[z]*histoweight);
                                        h1_InteractionBreakDown_NoQ4Weight_InSector_el_theta[Interaction][ElectronSector]->Fill( V3_el.Theta()*180./TMath::Pi(), P_2p1pito1p1pi[z]*histoweight);
                                        h1_InteractionBreakDown_NoQ4Weight_InSector_prot_theta[Interaction][ProtonSector]->Fill( ProtonTheta_Deg, P_2p1pito1p1pi[z]*histoweight); // smithja: might have to adjust ProtonSector
					if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][0]->Fill( ProtonTheta_Deg, P_2p1pito1p1pi[z]*histoweight); }
                                        if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][1]->Fill( ProtonTheta_Deg, P_2p1pito1p1pi[z]*histoweight); }

					prot_phi_plot = ProtonPhi_Deg; // smithja: alias ProtonPhi_Deg for plotting purposes in h2_prot_theta_phi; NB: redeclaring as a double here gives an error
                                        if (prot_phi_plot < 0.)	{ prot_phi_plot += 360.; } // smithja: this statement puts the proton phi in the correct range for plotting; a similar statement making	sure ProtonPhi_Deg is below 360
                                                                                           //          degrees is included towards the top of this code, so the only modification to prot_phi_plot needed is what's shown in this statement
					h2_prot_theta_phi->Fill( prot_phi_plot, ProtonTheta_Deg, P_2p1pito1p1pi[z]*histoweight);
					PassCounter3 ++;
					
                                        // smithja: These TH2s are used to investigate correlations between proton momtentum and other variables.
					h2_prot_mom_el_phi->Fill( el_phi_mod, ProtonMag, P_2p1pito1p1pi[z]*histoweight);
                                        h2_prot_mom_el_theta->Fill( V3_el.Theta()*180./TMath::Pi(), ProtonMag, P_2p1pito1p1pi[z]*histoweight);
                                        h2_prot_mom_el_mom->Fill( el_momentum, ProtonMag, P_2p1pito1p1pi[z]*histoweight);
                                        h2_prot_mom_phi->Fill( prot_phi_plot, ProtonMag, P_2p1pito1p1pi[z]*histoweight);
                                        h2_prot_mom_theta->Fill( ProtonTheta_Deg, ProtonMag, P_2p1pito1p1pi[z]*histoweight);

					h1_el_mom_corr->Fill(V4_el.Rho(),P_2p1pito1p1pi[z]*histoweight);
					//h1_prot_mom->Fill( ProtonMag, P_2p1pito1p1pi[z]*histoweight);
					h1_histoweight->Fill(P_2p1pito1p1pi[z]*histoweight);
					h1_histoweight2->Fill(P_2p1pito1p1pi[z]);
					//if (P_2p1pito1p1pi[z]*histoweight == 0) {h1_prot_mom->Fill( ProtonMag, P_2p1pito1p1pi[z]*histoweight);}
					//if (P_2p1pito1p1pi[z]*histoweight != 0) {h1_prot_mom->Fill( ProtonMag, 1/(P_2p1pito1p1pi[z]*histoweight));}
					h1_el_prot_phi_diff->Fill(el_phi_mod-ProtonPhi_Deg,P_2p1pito1p1pi[z]*histoweight);
					h2_el_prot_theta->Fill(el_theta,ProtonTheta_Deg,P_2p1pito1p1pi[z]*histoweight);
					h2_el_prot_phi->Fill(el_phi_mod,ProtonPhi_Deg,P_2p1pito1p1pi[z]*histoweight);
					h2_el_prot_mom->Fill(V4_el.Rho(), ProtonMag, P_2p1pito1p1pi[z]*histoweight);

					LocalWeight = P_2p1pito1p1pi[z]*histoweight;

					h2_Electron_Theta_Momentum->Fill(V4_el.Rho(),V3_el.Theta()*180./TMath::Pi(),P_2p1pito1p1pi[z]*histoweight);
					h2_Proton_Theta_Momentum->Fill( ProtonMag, V3_2prot_corr[z].Theta()*180./TMath::Pi(),P_2p1pito1p1pi[z]*histoweight);
					h1_prot_theta->Fill(V3_2prot_corr[z].Theta()*180./TMath::Pi(),P_2p1pito1p1pi[z]*histoweight);
					h1_prot_theta_noweight->Fill(V3_2prot_corr[z].Theta()*180./TMath::Pi());
					h1_prot_costheta->Fill(V3_2prot_corr[z].CosTheta(),P_2p1pito1p1pi[z]*histoweight);


					// -----------------------------------------------------------------------------------------------
					// Reconstruct xB, W, Q2 using Ecal instead of Etrue

					CalKineVars = CalculateCalKineVars(E_tot_2p[z],V4_el);

					// Fill plots based on underlying interactions

					Q2_BreakDown[0]->Fill(reco_Q2,LocalWeight);
					Nu_BreakDown[0]->Fill(nu,LocalWeight);
					Pe_BreakDown[0]->Fill(V4_el.Rho(),LocalWeight);	

					// ---------------------------------------------------------------------------------------------------------------------	

					// ---------------------------------------------------------------------------------------------------------------------

					//h1_EePrime_InCosThetaEPrimeSlices[CosThetaEPrimeSlice]->Fill(V4_el.E(),LocalWeight);							

 					if (fchoice > 0) {

						Q2_BreakDown[Interaction]->Fill(reco_Q2,LocalWeight);
						Nu_BreakDown[Interaction]->Fill(nu,LocalWeight);
						Pe_BreakDown[Interaction]->Fill(V4_el.Rho(),LocalWeight);
					}

					// -----------------------------------------------------------------------------------------------

					//---------------------------------- 2p 1pi ->1p 0pi   ----------------------------------------------

					h2_pperp_W->Fill(W_var,p_perp_tot_2p[z],-P_2p1pito1p0pi[z]*histoweight);
					h1_theta0->Fill((V4_beam.Vect()).Angle(V4_el.Vect()+V3_2prot_uncorr[z])*TMath::RadToDeg(),-P_2p1pito1p0pi[z]*histoweight);
					
					h2_el_CosTheta_E->Fill(V3_el.CosTheta(),V4_el.E(),-P_2p1pito1p0pi[z]*histoweight);


					if (el_theta >= t_thetaEl_lb->GetVal() && el_theta <= t_thetaEl_ub->GetVal()) { // smithja: there looks to be continue statements above that already necessitate this condition
						if (p_perp_tot_2p[z] < PtMax && Interaction > -1) {h1_InteractionBreakdown_Omega_NoQ4Weight_InSector_el_mom_ptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4); } 
                                                if (Interaction > -1) {
							h1_InteractionBreakDown_Omega_NoQ4Weight_InSector_el_mom_noptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4);
							h1_InteractionBreakDown_Omega_NoQ4Weight_Insector_prot_mom_QE[Interaction][ProtonSector]->Fill( ProtonMag, -P_2p1pito1p0pi[z]*histoweight);                      
								if(hitnuc == 2212) h1_hit_nuc_pass->Fill(1, -P_2p1pito1p0pi[z]*histoweight);
	                                                        if(hitnuc == 2112) h1_hit_nuc_pass->Fill(2, -P_2p1pito1p0pi[z]*histoweight);
							
							h1_InteractionBreakDown_InSector_Em[Interaction][ProtonSector]->Fill(Em, -P_2p1pito1p0pi[z]*histoweight);
							h1_InteractionBreakDown_InSector_Pm[Interaction][ProtonSector]->Fill(pmiss, -P_2p1pito1p0pi[z]*histoweight);
							h2_InteractionBreakDown_InSector_EmPm[Interaction][ProtonSector]->Fill(Em,pmiss, -P_2p1pito1p0pi[z]*histoweight);
							h1_InteractionBreakDown_ThetaPQ[Interaction][ProtonSector]->Fill(ThetaPQ,-P_2p1pito1p0pi[z]*histoweight);
							h1_InteractionBreakDown_InSector_el_mom_Emcut[Interaction][ProtonSector]->Fill(el_momentum,-P_2p1pito1p0pi[z]*histoweight);

                                                        if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][0]->Fill( ProtonMag, -P_2p1pito1p0pi[z]*histoweight); }
                                                        if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][1]->Fill( ProtonMag, -P_2p1pito1p0pi[z]*histoweight); }
						}
					}

					h2_Electron_Theta_Phi->Fill( el_phi_mod, V3_el.Theta()*180./TMath::Pi(), -P_2p1pito1p0pi[z]*histoweight);
                                        h1_InteractionBreakDown_NoQ4Weight_InSector_el_theta[Interaction][ElectronSector]->Fill( V3_el.Theta()*180./TMath::Pi(), -P_2p1pito1p0pi[z]*histoweight);
					h1_InteractionBreakDown_NoQ4Weight_InSector_prot_theta[Interaction][ProtonSector]->Fill( ProtonTheta_Deg, -P_2p1pito1p0pi[z]*histoweight); // smithja: might have to adjust ProtonSector
					if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][0]->Fill( ProtonTheta_Deg, -P_2p1pito1p0pi[z]*histoweight); }
                                        if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][1]->Fill( ProtonTheta_Deg, -P_2p1pito1p0pi[z]*histoweight); }

                                        prot_phi_plot = ProtonPhi_Deg; // smithja: alias ProtonPhi_Deg for plotting purposes in h2_prot_theta_phi; NB: redeclaration here causes an error
                                        if (prot_phi_plot < 0.)	{ prot_phi_plot += 360.; } // smithja: this statement puts the proton phi in the correct range for plotting; a similar statement making	sure ProtonPhi_Deg is below 360
                                                                                           //          degrees is included towards the top of this code, so the only modification to prot_phi_plot needed is what's shown in this statement
					h2_prot_theta_phi->Fill( prot_phi_plot, ProtonTheta_Deg, -P_2p1pito1p0pi[z]*histoweight);	
					PassCounter3 ++;
					
                                        // smithja: These TH2s are used to investigate correlations between proton momtentum and other variables.
                                        h2_prot_mom_el_phi->Fill( el_phi_mod, ProtonMag, -P_2p1pito1p0pi[z]*histoweight);
                                        h2_prot_mom_el_theta->Fill( V3_el.Theta()*180./TMath::Pi(), ProtonMag, -P_2p1pito1p0pi[z]*histoweight);
                                        h2_prot_mom_el_mom->Fill( el_momentum, ProtonMag, -P_2p1pito1p0pi[z]*histoweight);
                                        h2_prot_mom_phi->Fill( prot_phi_plot, ProtonMag, -P_2p1pito1p0pi[z]*histoweight);
                                        h2_prot_mom_theta->Fill( ProtonTheta_Deg, ProtonMag, -P_2p1pito1p0pi[z]*histoweight);

					h1_el_mom_corr->Fill(V4_el.Rho(),-P_2p1pito1p0pi[z]*histoweight);
					//h1_prot_mom->Fill( ProtonMag, -P_2p1pito1p0pi[z]*histoweight);
					h1_histoweight->Fill(-P_2p1pito1p0pi[z]*histoweight);
					h1_histoweight2->Fill(-P_2p1pito1p0pi[z]);
					//if (-P_2p1pito1p0pi[z]*histoweight == 0) {h1_prot_mom->Fill( ProtonMag, -P_2p1pito1p0pi[z]*histoweight);}
					//if (-P_2p1pito1p0pi[z]*histoweight != 0) {h1_prot_mom->Fill( ProtonMag, 1/(-P_2p1pito1p0pi[z]*histoweight));}

					h1_el_prot_phi_diff->Fill(el_phi_mod-ProtonPhi_Deg,-P_2p1pito1p0pi[z]*histoweight);
					h2_el_prot_theta->Fill(el_theta,ProtonTheta_Deg,-P_2p1pito1p0pi[z]*histoweight);
					h2_el_prot_phi->Fill(el_phi_mod,ProtonPhi_Deg,-P_2p1pito1p0pi[z]*histoweight);
					h2_el_prot_mom->Fill(V4_el.Rho(), ProtonMag, -P_2p1pito1p0pi[z]*histoweight);

					LocalWeight = -P_2p1pito1p0pi[z]*histoweight;

					h2_Electron_Theta_Momentum->Fill(V4_el.Rho(),V3_el.Theta()*180./TMath::Pi(),-P_2p1pito1p0pi[z]*histoweight);
					h2_Proton_Theta_Momentum->Fill( ProtonMag, V3_2prot_corr[z].Theta()*180./TMath::Pi(),-P_2p1pito1p0pi[z]*histoweight);
					h1_prot_theta->Fill(V3_2prot_corr[z].Theta()*180./TMath::Pi(),-P_2p1pito1p0pi[z]*histoweight);
					h1_prot_theta_noweight->Fill(V3_2prot_corr[z].Theta()*180./TMath::Pi());
					h1_prot_costheta->Fill(V3_2prot_corr[z].CosTheta(),-P_2p1pito1p0pi[z]*histoweight);
					

					// -----------------------------------------------------------------------------------------------
					// Reconstruct xB, W, Q2 using Ecal instead of Etrue

					CalKineVars = CalculateCalKineVars(E_tot_2p[z],V4_el);

					// Fill plots based on underlying interactions

					Q2_BreakDown[0]->Fill(reco_Q2,LocalWeight);
					Nu_BreakDown[0]->Fill(nu,LocalWeight);
					Pe_BreakDown[0]->Fill(V4_el.Rho(),LocalWeight);	

					// ---------------------------------------------------------------------------------------------------------------------	

					// ---------------------------------------------------------------------------------------------------------------------

					//h1_EePrime_InCosThetaEPrimeSlices[CosThetaEPrimeSlice]->Fill(V4_el.E(),LocalWeight);						

 					if (fchoice > 0) {

						Q2_BreakDown[Interaction]->Fill(reco_Q2,LocalWeight);
						Nu_BreakDown[Interaction]->Fill(nu,LocalWeight);
						Pe_BreakDown[Interaction]->Fill(V4_el.Rho(),LocalWeight);

					}

					// -----------------------------------------------------------------------------------------------


				}//filling the histograms for 2protons

			}//1pi requirement

			//---------------------------------- 2p 2pi ----------------------------------------------

			const int N_2pi=2;
			double Ecal_2p2pi[N_2prot];
			double p_miss_perp_2p2pi[N_2prot];
			double Ptot_2p[2]={0};

			if (num_pi_phot == 2) {

				TVector3 V3_2pi_corr[N_2pi];
				double pion_acc_ratio[N_2pi] = {1};

				for (int i = 0; i < num_pi_phot; i++) {

					if (fchoice == 0) { //CLAS data
						V3_2pi_corr[i].SetXYZ(pxf[ind_pi_phot[i]],pyf[ind_pi_phot[i]],pzf[ind_pi_phot[i]]);
						pion_acc_ratio[i] = 1; //Acceptance 1 for CLAS data
					}

					if (fchoice > 0) { //GENIE data
						pion_acc_ratio[i] = 0; //reset to 0 just to be same
						V3_2pi_corr[i].SetXYZ(Smeared_Ppi[i]/pf[ind_pi_phot[i]] * pxf[ind_pi_phot[i]],Smeared_Ppi[i]/pf[ind_pi_phot[i]] * pyf[ind_pi_phot[i]],
								Smeared_Ppi[i]/pf[ind_pi_phot[i]] * pzf[ind_pi_phot[i]]);
						double phi_pion = V3_2pi_corr[i].Phi();
						V3_2pi_corr[i].SetPhi(phi_pion + TMath::Pi() ); // Vec.Phi() is between (-180,180)
						phi_pion += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS

						double pion_theta = V3_2pi_corr[i].Theta();
						double pion_mom_corr = V3_2pi_corr[i].Mag();

						if (charge_pi[i] == 1) { //acceptance for pi plus
							pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, 211, file_acceptance_pip,ApplyAccWeights);
							if ( fabs(pion_acc_ratio[i]) != pion_acc_ratio[i] ) { continue; }
						}
						else if (charge_pi[i] == -1) {		//acceptance for pi minus. using electron acceptance map

							//pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,ApplyAccWeights);
							
							// UNTIL AXEL CREATES THE CORRECT PIMINUS MAP, WE SET THE PIMINUS ACCEPTANCE TO BE 1
//							pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,false);
							pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance_pim,true);


							if ( fabs(pion_acc_ratio[i]) != pion_acc_ratio[i] ) { continue; }
						}
						else if (charge_pi[i] == 0) {		//acceptance for photon set to 1 for now F.H. 09/24/19
							pion_acc_ratio[i] = 1;
						}
						else { std::cout << "WARNING: 2proton and 2 Pion loop. pion_acc_ratio is still 0. Continue with next event " << std::endl;	continue;
						}
					}

				}

				rotation->prot2_pi2_rot_func(V3_2prot_corr,V3_2prot_uncorr,V3_2pi_corr,charge_pi, V4_el, Ecal_2p2pi,p_miss_perp_2p2pi,Ptot_2p);

				double weight_pions = pion_acc_ratio[0] * pion_acc_ratio[1];
				double histoweight = weight_pions * weight_protons * e_acc_ratio * wght/Mott_cross_sec; 
				//Is this correct in the following loop? F.H. 09/01/19


				for(int z = 0; z < N_2prot; z++){ //looping over two protons

					//---------------------------------- 2p 2pi ->1p 0pi   ----------------------------------------------

					h2_pperp_W->Fill(W_var,p_perp_tot_2p[z],Ptot_2p[z]*histoweight);
					h1_theta0->Fill((V4_beam.Vect()).Angle(V4_el.Vect()+V3_2prot_uncorr[z])*TMath::RadToDeg(),Ptot_2p[z]*histoweight);


					double ProtonPhi_Deg = V3_2prot_corr[z].Phi() *180. / TMath::Pi() + 30;
					//double ProtonPhi_Deg = V3_2prot_corr[z].Phi() *180. / TMath::Pi() + 180 + 30; // smithja: commented out on 9/22/2021; 180-degree shift not needed here
					if (ProtonPhi_Deg > 360.) { ProtonPhi_Deg -= 360.; } 
                                        if (ProtonPhi_Deg < 0.) { ProtonPhi_Deg += 360.; }
                                        int ProtonSector = ProtonPhi_Deg / 60;
					double ProtonTheta_Deg = V3_2prot_corr[z].Theta() *180. / TMath::Pi();
					double ProtonMag = V3_2prot_corr[z].Mag();
					double ProtonTK = sqrt(ProtonMag*ProtonMag + m_prot*m_prot) - m_prot;
					double Em = (nu - ProtonTK);
					TVector3 pmiss_vec =  V3_rot_q - V3_2prot_corr[z];				
					double pmiss = pmiss_vec.Mag();
					double ThetaPQ = V3_rot_q.Angle(V3_2prot_corr[z]) * 180. / TMath::Pi();						
                    
                    if (Em > Em_ub)  {continue;}

					if(ThetaPQ > theta_pq_cut) { continue; }//Looking at ThetaPQ cut

					if (fApplyThetaSliceProt) {  // hard coded range for now
						if ( ProtonTheta_Deg < t_thetaProt_lb->GetVal()) { continue; }
						if ( ProtonTheta_Deg > t_thetaProt_ub->GetVal()) { continue; }
					}

        	        if (fApplyPhiOpeningAngleProt) {
                	        if ( TMath::Abs(ProtonPhi_Deg - 30) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 90) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 150) > PhiOpeningAngleProt \
                        	    && TMath::Abs(ProtonPhi_Deg - 210) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 270) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 330) > PhiOpeningAngleProt ) {
                                	continue; 
                       		}  
                	}

                	if (fApplyPhiSliceProt_Sectors && ProtonSector != (ElectronSector + 3)%6) { continue; } 
                    if (fApplyProtMomCut && (ProtonMag < t_ProtMom_lb->GetVal() || ProtonMag > t_ProtMom_ub->GetVal())) { continue; }

					h2_el_CosTheta_E->Fill(V3_el.CosTheta(),V4_el.E(),Ptot_2p[z]*histoweight);


					if (el_theta >= t_thetaEl_lb->GetVal() && el_theta <= t_thetaEl_ub->GetVal()) { // smithja: there looks to be continue statements above that already necessitate this condition
						if (p_perp_tot_2p[z] < PtMax && Interaction > -1) {h1_InteractionBreakdown_Omega_NoQ4Weight_InSector_el_mom_ptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4); }
                                                if (Interaction > -1) {
							h1_InteractionBreakDown_Omega_NoQ4Weight_InSector_el_mom_noptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4);
							h1_InteractionBreakDown_Omega_NoQ4Weight_Insector_prot_mom_QE[Interaction][ProtonSector]->Fill( ProtonMag, Ptot_2p[z]*histoweight);

                            h1_InteractionBreakDown_InSector_Em[Interaction][ProtonSector]->Fill(Em, Ptot_2p[z]*histoweight);
							h1_InteractionBreakDown_InSector_Pm[Interaction][ProtonSector]->Fill(pmiss, Ptot_2p[z]*histoweight);
							h2_InteractionBreakDown_InSector_EmPm[Interaction][ProtonSector]->Fill(Em,pmiss, Ptot_2p[z]*histoweight);
							h1_InteractionBreakDown_ThetaPQ[Interaction][ProtonSector]->Fill(ThetaPQ, Ptot_2p[z]*histoweight);
							h1_InteractionBreakDown_InSector_el_mom_Emcut[Interaction][ProtonSector]->Fill(el_momentum,Ptot_2p[z]*histoweight);

								if(hitnuc == 2212) h1_hit_nuc_pass->Fill(1,Ptot_2p[z]*histoweight);
	                                                        if(hitnuc == 2112) h1_hit_nuc_pass->Fill(2,Ptot_2p[z]*histoweight);

                                                        if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][0]->Fill( ProtonMag, Ptot_2p[z]*histoweight); }
                                                        if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][1]->Fill( ProtonMag, Ptot_2p[z]*histoweight); }
						}
					}

					h2_Electron_Theta_Phi->Fill( el_phi_mod, V3_el.Theta()*180./TMath::Pi(), Ptot_2p[z]*histoweight);
                                        h1_InteractionBreakDown_NoQ4Weight_InSector_el_theta[Interaction][ElectronSector]->Fill( V3_el.Theta()*180./TMath::Pi(), Ptot_2p[z]*histoweight);
					h1_InteractionBreakDown_NoQ4Weight_InSector_prot_theta[Interaction][ProtonSector]->Fill( ProtonTheta_Deg, Ptot_2p[z]*histoweight); // smithja: might have to adjust ProtonSector
					if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][0]->Fill( ProtonTheta_Deg, Ptot_2p[z]*histoweight); }
                                        if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][1]->Fill( ProtonTheta_Deg, Ptot_2p[z]*histoweight); }

                                        double prot_phi_plot = ProtonPhi_Deg; // smithja: alias	ProtonPhi_Deg for plotting purposes in h2_prot_theta_phi
                                        if (prot_phi_plot < 0.)	{ prot_phi_plot += 360.; } // smithja: this statement puts the proton phi in the correct range for plotting; a similar statement making	sure ProtonPhi_Deg is below 360
                                                                                           //          degrees is included towards the top of this code, so the only modification to prot_phi_plot needed is what's shown in this statement
					h2_prot_theta_phi->Fill( prot_phi_plot, ProtonTheta_Deg, Ptot_2p[z]*histoweight);						
					PassCounter3 ++;
					
                                        // smithja: These TH2s are used to investigate correlations between proton momtentum and other variables.
                                        h2_prot_mom_el_phi->Fill( el_phi_mod, ProtonMag, Ptot_2p[z]*histoweight);
                                        h2_prot_mom_el_theta->Fill( V3_el.Theta()*180./TMath::Pi(), ProtonMag, Ptot_2p[z]*histoweight);
                                        h2_prot_mom_el_mom->Fill( el_momentum, ProtonMag, Ptot_2p[z]*histoweight);
                                        h2_prot_mom_phi->Fill( prot_phi_plot, ProtonMag, Ptot_2p[z]*histoweight);
                                        h2_prot_mom_theta->Fill( ProtonTheta_Deg, ProtonMag, Ptot_2p[z]*histoweight);

					h1_el_mom_corr->Fill(V4_el.Rho(),Ptot_2p[z]*histoweight);
					//h1_prot_mom->Fill( ProtonMag, Ptot_2p[z]*histoweight);
					h1_histoweight->Fill(Ptot_2p[z]*histoweight);
					h1_histoweight2->Fill(Ptot_2p[z]);
					//if (Ptot_2p[z]*histoweight == 0) {h1_prot_mom->Fill( ProtonMag, Ptot_2p[z]*histoweight);}
					//if (Ptot_2p[z]*histoweight != 0) {h1_prot_mom->Fill( ProtonMag, 1/(Ptot_2p[z]*histoweight));}
				
					h1_el_prot_phi_diff->Fill(el_phi_mod-ProtonPhi_Deg,Ptot_2p[z]*histoweight);
					h2_el_prot_theta->Fill(el_theta,ProtonTheta_Deg,Ptot_2p[z]*histoweight);
					h2_el_prot_phi->Fill(el_phi_mod,ProtonPhi_Deg,Ptot_2p[z]*histoweight);
					h2_el_prot_mom->Fill(V4_el.Rho(), ProtonMag, Ptot_2p[z]*histoweight);

					double LocalWeight = Ptot_2p[z]*histoweight;

					h2_Electron_Theta_Momentum->Fill(V4_el.Rho(),V3_el.Theta()*180./TMath::Pi(),Ptot_2p[z]*histoweight);
					h2_Proton_Theta_Momentum->Fill( ProtonMag, V3_2prot_corr[z].Theta()*180./TMath::Pi(),Ptot_2p[z]*histoweight);
					h1_prot_theta->Fill(V3_2prot_corr[z].Theta()*180./TMath::Pi(),Ptot_2p[z]*histoweight);
					h1_prot_theta_noweight->Fill(V3_2prot_corr[z].Theta()*180./TMath::Pi());
					h1_prot_costheta->Fill(V3_2prot_corr[z].CosTheta(),Ptot_2p[z]*histoweight);


					// -----------------------------------------------------------------------------------------------
					// Reconstruct xB, W, Q2 using Ecal instead of Etrue

					CalKineVars = CalculateCalKineVars(E_tot_2p[z],V4_el);
					LocalWeight = Ptot_2p[z]*histoweight;

					// Fill plots based on underlying interactions

					Q2_BreakDown[0]->Fill(reco_Q2,LocalWeight);
					Nu_BreakDown[0]->Fill(nu,LocalWeight);
					Pe_BreakDown[0]->Fill(V4_el.Rho(),LocalWeight);	

					// ---------------------------------------------------------------------------------------------------------------------	

					double PTmiss = p_perp_tot_2p[z];
					double Ecal = E_tot_2p[z];

					double EcalReso = (Ecal-en_beam_Ecal[fbeam_en])/en_beam_Ecal[fbeam_en];

					// ---------------------------------------------------------------------------------------------------------------------

					//h1_EePrime_InCosThetaEPrimeSlices[CosThetaEPrimeSlice]->Fill(V4_el.E(),LocalWeight);							

 					if (fchoice > 0) {

						Q2_BreakDown[Interaction]->Fill(reco_Q2,LocalWeight);
						Nu_BreakDown[Interaction]->Fill(nu,LocalWeight);
						Pe_BreakDown[Interaction]->Fill(V4_el.Rho(),LocalWeight);
					}

					// -----------------------------------------------------------------------------------------------


				} //Filling the histogram for two protons

			}//2pi requirement

		} // End of the 2-proton case

		// -------------------------------------------------------------------------------------------------------------------------------------

		// Events with exactly 3 protons

		if(num_p == 3) {

			const int N_3p = 3;
			TLorentzVector V4_p_uncorr[N_3p], V4_p_corr[N_3p],V4_prot_el[N_3p];
			TVector3 V3_prot_uncorr[N_3p],V3_prot_corr[N_3p],V3_3p_rot[N_3p];
			double E_cal[N_3p],p_miss_perp[N_3p],P_3pto1p[N_3p];
			double N_p1[N_3p]={0};
			double N_p_three=0;
			double E_cal_3pto1p[3]={0};
			double p_miss_perp_3pto1p[3]={0};
			int N_comb = 3;
			const int N_2p = 2;
			double E_cal_3pto2p[3][N_2p]={0};
			double p_miss_perp_3pto2p[3][N_2p]={0};
			double P_3pto2p[3][N_2p]={0};
			TVector3 V3_2p_rot[N_2p], V3_prot_el[N_3p][N_2p];
			double p_acc_ratio[N_3p] = {1};

			for(int i = 0; i < N_3p; i++) {

				N_p1[i] = 0;

				V4_p_uncorr[i].SetPxPyPzE(pxf[index_p[i]],pyf[index_p[i]],pzf[index_p[i]],TMath::Sqrt(m_prot*m_prot+pf[index_p[i]]*pf[index_p[i]]));
				V3_prot_uncorr[i] = V4_p_uncorr[i].Vect();

				if (fchoice == 0) { //CLAS data

					V3_prot_corr[i].SetXYZ(pxf[index_p[i]+60], pyf[index_p[i]+60], pzf[index_p[i]+60]);
					V4_p_corr[i].SetPxPyPzE(pxf[index_p[i]+60], pyf[index_p[i]+60], pzf[index_p[i]+60],TMath::Sqrt(m_prot*m_prot+pf[index_p[i]+60]*pf[index_p[i]+60]));
					p_acc_ratio[i] = 1; //Acceptance is 1 for CLAS datafile
				}

				if (fchoice > 0) { //GENIE data

					p_acc_ratio[i] = 0; //Reset just to be sure
					V3_prot_corr[i].SetXYZ(Smeared_Pp[i]/pf[index_p[i]] * pxf[index_p[i]],Smeared_Pp[i]/pf[index_p[i]] * pyf[index_p[i]],
						Smeared_Pp[i]/pf[index_p[i]] * pzf[index_p[i]]);
					V4_p_corr[i].SetPxPyPzE(Smeared_Pp[i]/pf[index_p[i]] * pxf[index_p[i]],Smeared_Pp[i]/pf[index_p[i]] * pyf[index_p[i]],
						Smeared_Pp[i]/pf[index_p[i]] * pzf[index_p[i]],Smeared_Ep[i]);

					double phi_prot = V3_el.Phi(); //in Radians
					V3_prot_corr[i].SetPhi(phi_prot + TMath::Pi() ); // Vec.Phi() is between (-180,180)
					phi_prot += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS

					double p_theta = V3_prot_corr[i].Theta();
					double prot_mom_corr = V3_prot_corr[i].Mag();
					//Proton acceptance weight
					p_acc_ratio[i] = acceptance_c(prot_mom_corr, cos(p_theta), phi_prot, 2212,file_acceptance_p,ApplyAccWeights);
					if ( fabs(p_acc_ratio[i]) != p_acc_ratio[i] ) { continue; }
				}

				V4_prot_el[i] = V4_p_corr[i] + V4_el;
				E_cal[i] = V4_el.E()+ V4_p_corr[i].E() - m_prot + bind_en[ftarget];
				p_miss_perp[i] = TMath::Sqrt(V4_prot_el[i].Px()*V4_prot_el[i].Px() + V4_prot_el[i].Py()*V4_prot_el[i].Py());

			} //end loop over N_3p

			V3_prot_el[0][0]=V4_el.Vect()+V3_prot_uncorr[0];
			V3_prot_el[0][1]=V4_el.Vect()+V3_prot_uncorr[1];
			V3_prot_el[1][0]=V4_el.Vect()+V3_prot_uncorr[0];
			V3_prot_el[1][1]=V4_el.Vect()+V3_prot_uncorr[2];
			V3_prot_el[2][0]=V4_el.Vect()+V3_prot_uncorr[1];
			V3_prot_el[2][1]=V4_el.Vect()+V3_prot_uncorr[2];


			rotation->prot3_rot_func( V3_prot_corr,V3_prot_uncorr,V4_el,E_cal_3pto2p,p_miss_perp_3pto2p, P_3pto2p,N_p1, E_cal_3pto1p,p_miss_perp_3pto1p,&N_p_three);

			//acceptance weight for all three protons ( = 1 for CLAS data)

			double weight_protons =	p_acc_ratio[0] * p_acc_ratio[1] * p_acc_ratio[2];

			if (num_pi_phot == 0 && N_p_three != 0){

				//histoweight is 1/Mott_cross_sec for CLAS data
				double histoweight = weight_protons * e_acc_ratio * wght/Mott_cross_sec; 
				//Weight for 3protons, 1 electron, GENIE weight and Mott cross section

				for(int count = 0; count < N_comb; count++) { // Loop over number of combinations

					for(int j = 0; j < N_2p; j++) { // Loop over two protons

						//-----------------------------------------  3p to 2p->1p  ------------------------------

						h2_pperp_W->Fill(W_var,p_miss_perp_3pto2p[count][j],P_3pto2p[count][j]*histoweight);
						h1_theta0->Fill((V4_beam.Vect()).Angle(V3_prot_el[count][j])*TMath::RadToDeg(),P_3pto2p[count][j]*histoweight);

						double ProtonPhi_Deg = V3_prot_corr[j].Phi() *180. / TMath::Pi() + 30;
						//double ProtonPhi_Deg = V3_prot_corr[j].Phi() *180. / TMath::Pi() + 180 + 30; // smithja: commented out on 9/22/2021; 180-degree shift not needed here
						if (ProtonPhi_Deg > 360.) { ProtonPhi_Deg -= 360.; } 
        	                                if (ProtonPhi_Deg < 0.) { ProtonPhi_Deg += 360.; }
	                                        int ProtonSector = ProtonPhi_Deg / 60;
						double ProtonTheta_Deg = V3_prot_corr[j].Theta() *180. / TMath::Pi();
						double ProtonMag = V3_prot_corr[j].Mag();
						double ProtonTK = sqrt(ProtonMag*ProtonMag + m_prot*m_prot) - m_prot;
						double Em = (nu - ProtonTK);
						TVector3 pmiss_vec =  V3_rot_q - V3_prot_corr[j];				
						double pmiss = pmiss_vec.Mag();
						double ThetaPQ = V3_rot_q.Angle(V3_prot_corr[j]) * 180. / TMath::Pi();
                    	
                    	if (Em > Em_ub)  {continue;}

						if(ThetaPQ > theta_pq_cut) { continue; }//Looking at ThetaPQ cut
						
						if (fApplyThetaSliceProt) {  // hard coded range for now
							if ( ProtonTheta_Deg < t_thetaProt_lb->GetVal()) { continue; }
							if ( ProtonTheta_Deg > t_thetaProt_ub->GetVal()) { continue; }
						}
			
                    	if (fApplyPhiOpeningAngleProt) {
                            	if ( TMath::Abs(ProtonPhi_Deg - 30) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 90) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 150) > PhiOpeningAngleProt \
                    	            && TMath::Abs(ProtonPhi_Deg - 210) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 270) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 330) > PhiOpeningAngleProt ) {
            	                        continue;
    	                        }
                        }

                        if (fApplyPhiSliceProt_Sectors && ProtonSector != (ElectronSector + 3)%6) { continue; }
                        if (fApplyProtMomCut && (ProtonMag < t_ProtMom_lb->GetVal() || ProtonMag > t_ProtMom_ub->GetVal())) { continue; }

						h2_el_CosTheta_E->Fill(V3_el.CosTheta(),V4_el.E(),P_3pto2p[count][j]*histoweight);


						if (el_theta >= t_thetaEl_lb->GetVal() && el_theta <= t_thetaEl_ub->GetVal()) { // smithja: there looks to be continue statements above that already necessitate this condition
							if (p_miss_perp_3pto2p[count][j] < PtMax && Interaction > -1) {h1_InteractionBreakdown_Omega_NoQ4Weight_InSector_el_mom_ptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4); }
                                                	if (Interaction > -1) {
								h1_InteractionBreakDown_Omega_NoQ4Weight_InSector_el_mom_noptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4);
								h1_InteractionBreakDown_Omega_NoQ4Weight_Insector_prot_mom_QE[Interaction][ProtonSector]->Fill( ProtonMag, P_3pto2p[count][j]*histoweight);
	                            					if(hitnuc == 2212) h1_hit_nuc_pass->Fill(1,P_3pto2p[count][j]*histoweight);
	                                                        if(hitnuc == 2112) h1_hit_nuc_pass->Fill(2,P_3pto2p[count][j]*histoweight);

								h1_InteractionBreakDown_InSector_Em[Interaction][ProtonSector]->Fill(Em, P_3pto2p[count][j]*histoweight);
								h1_InteractionBreakDown_InSector_Pm[Interaction][ProtonSector]->Fill(pmiss, P_3pto2p[count][j]*histoweight);
								h2_InteractionBreakDown_InSector_EmPm[Interaction][ProtonSector]->Fill(Em,pmiss, P_3pto2p[count][j]*histoweight);
								h1_InteractionBreakDown_ThetaPQ[Interaction][ProtonSector]->Fill(ThetaPQ, P_3pto2p[count][j]*histoweight);
							h1_InteractionBreakDown_InSector_el_mom_Emcut[Interaction][ProtonSector]->Fill(el_momentum,P_3pto2p[count][j]*histoweight);

	                                                        if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][0]->Fill( ProtonMag, P_3pto2p[count][j]*histoweight); }
        	                                                if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][1]->Fill( ProtonMag, P_3pto2p[count][j]*histoweight); }
							}
						}

						h2_Electron_Theta_Phi->Fill( el_phi_mod, V3_el.Theta()*180./TMath::Pi(), P_3pto2p[count][j]*histoweight);
	                                        h1_InteractionBreakDown_NoQ4Weight_InSector_el_theta[Interaction][ElectronSector]->Fill( V3_el.Theta()*180./TMath::Pi(), P_3pto2p[count][j]*histoweight);
						h1_InteractionBreakDown_NoQ4Weight_InSector_prot_theta[Interaction][ProtonSector]->Fill( ProtonTheta_Deg, P_3pto2p[count][j]*histoweight); // smithja: might have to adjust ProtonSector
						if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][0]->Fill( ProtonTheta_Deg, P_3pto2p[count][j]*histoweight); }
                                        	if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][1]->Fill( ProtonTheta_Deg, P_3pto2p[count][j]*histoweight); }

                                        	double prot_phi_plot = ProtonPhi_Deg; // smithja: alias	ProtonPhi_Deg for plotting purposes in h2_prot_theta_phi
        	                                if (prot_phi_plot < 0.)	{ prot_phi_plot += 360.; } // smithja: this statement puts the proton phi in the correct range for plotting; a similar statement making	sure ProtonPhi_Deg is below 360
                                                                                           //          degrees is included towards the top of this code, so the only modification to prot_phi_plot needed is what's shown in this statement
						h2_prot_theta_phi->Fill( prot_phi_plot, ProtonTheta_Deg, P_3pto2p[count][j]*histoweight);							
						PassCounter3 ++;
					
	                                        // smithja: These TH2s are used to investigate correlations between proton momtentum and other variables.
        	                                h2_prot_mom_el_phi->Fill( el_phi_mod, ProtonMag, P_3pto2p[count][j]*histoweight);
                	                        h2_prot_mom_el_theta->Fill( V3_el.Theta()*180./TMath::Pi(), ProtonMag, P_3pto2p[count][j]*histoweight);
                        	                h2_prot_mom_el_mom->Fill( el_momentum, ProtonMag, P_3pto2p[count][j]*histoweight);
                                	        h2_prot_mom_phi->Fill( prot_phi_plot, ProtonMag, P_3pto2p[count][j]*histoweight);
                                        	h2_prot_mom_theta->Fill( ProtonTheta_Deg, ProtonMag, P_3pto2p[count][j]*histoweight);
	
						h1_el_mom_corr->Fill(V4_el.Rho(),P_3pto2p[count][j]*histoweight);
						//h1_prot_mom->Fill( ProtonMag, P_3pto2p[count][j]*histoweight);
						h1_histoweight->Fill(P_3pto2p[count][j]*histoweight);
						h1_histoweight2->Fill(P_3pto2p[count][j]);
						//if (P_3pto2p[count][j]*histoweight == 0) {h1_prot_mom->Fill( ProtonMag, P_3pto2p[count][j]*histoweight);}
						//if (P_3pto2p[count][j]*histoweight != 0) {h1_prot_mom->Fill( ProtonMag, 1/(P_3pto2p[count][j]*histoweight));}

						h1_el_prot_phi_diff->Fill(el_phi_mod-ProtonPhi_Deg,P_3pto2p[count][j]*histoweight);
						h2_el_prot_theta->Fill(el_theta,ProtonTheta_Deg,P_3pto2p[count][j]*histoweight);
						h2_el_prot_phi->Fill(el_phi_mod,ProtonPhi_Deg,P_3pto2p[count][j]*histoweight);
						h2_el_prot_mom->Fill(V4_el.Rho(), ProtonMag, P_3pto2p[count][j]*histoweight);

						double LocalWeight = P_3pto2p[count][j]*histoweight;

						h2_Electron_Theta_Momentum->Fill(V4_el.Rho(),V3_el.Theta()*180./TMath::Pi(),P_3pto2p[count][j]*histoweight);
						h2_Proton_Theta_Momentum->Fill( ProtonMag, V3_prot_corr[j].Theta()*180./TMath::Pi(),P_3pto2p[count][j]*histoweight);
						h1_prot_theta->Fill(V3_prot_corr[j].Theta()*180./TMath::Pi(),P_3pto2p[count][j]*histoweight);
						h1_prot_theta_noweight->Fill(V3_prot_corr[j].Theta()*180./TMath::Pi());
						h1_prot_costheta->Fill(V3_prot_corr[j].CosTheta(),P_3pto2p[count][j]*histoweight);

						// -----------------------------------------------------------------------------------------------
						// Reconstruct xB, W, Q2 using Ecal instead of Etrue

						CalKineVars = CalculateCalKineVars(E_cal_3pto2p[count][j],V4_el);

						// Fill plots based on underlying interactions

						Q2_BreakDown[0]->Fill(reco_Q2,LocalWeight);
						Nu_BreakDown[0]->Fill(nu,LocalWeight);
						Pe_BreakDown[0]->Fill(V4_el.Rho(),LocalWeight);

						// ---------------------------------------------------------------------------------------------------------------------	

						double PTmiss = p_miss_perp_3pto2p[count][j];
						double Ecal = E_cal_3pto2p[count][j];

						double EcalReso = (Ecal-en_beam_Ecal[fbeam_en])/en_beam_Ecal[fbeam_en];

						// ---------------------------------------------------------------------------------------------------------------------

						//h1_EePrime_InCosThetaEPrimeSlices[CosThetaEPrimeSlice]->Fill(V4_el.E(),LocalWeight);						

	 					if (fchoice > 0) {

							Q2_BreakDown[Interaction]->Fill(reco_Q2,LocalWeight);
							Nu_BreakDown[Interaction]->Fill(nu,LocalWeight);
							Pe_BreakDown[Interaction]->Fill(V4_el.Rho(),LocalWeight);

						}

						// -----------------------------------------------------------------------------------------------

					} //end loop over protons

				} //end loop over combination N_comb

				//-----------------------------------------  3p to 1p  ------------------------------------------

				for(int j = 0; j < N_3p; j++)    {

					P_3pto1p[j]= N_p1[j] / N_p_three;

					h2_pperp_W->Fill(W_var,p_miss_perp[j],-P_3pto1p[j]*histoweight);
					h1_theta0->Fill((V4_beam.Vect()).Angle(V4_el.Vect()+V3_prot_uncorr[j])*TMath::RadToDeg(),-P_3pto1p[j]*histoweight);


					double ProtonPhi_Deg = V3_prot_corr[j].Phi() *180. / TMath::Pi() + 30;
					//double ProtonPhi_Deg = V3_prot_corr[j].Phi() *180. / TMath::Pi() + 180 + 30; // smithja: commented out on 9/22/2021; 180-degree shift not needed here
					if (ProtonPhi_Deg > 360.) { ProtonPhi_Deg -= 360.; } 
                                        if (ProtonPhi_Deg < 0.) { ProtonPhi_Deg += 360.; }
                                        int ProtonSector = ProtonPhi_Deg / 60;
					double ProtonTheta_Deg = V3_prot_corr[j].Theta() *180. / TMath::Pi();
					double ProtonMag = V3_prot_corr[j].Mag();
					double ProtonTK = sqrt(ProtonMag*ProtonMag + m_prot*m_prot) - m_prot;
					double Em = (nu - ProtonTK);
					TVector3 pmiss_vec =  V3_rot_q - V3_prot_corr[j];				
					double pmiss = pmiss_vec.Mag();
					double ThetaPQ = V3_rot_q.Angle(V3_prot_corr[j]) * 180. / TMath::Pi();

                    if (Em > Em_ub)  {continue;}

					if(ThetaPQ > theta_pq_cut) { continue; }//Looking at ThetaPQ cut

					if (fApplyThetaSliceProt) {  // hard coded range for now
						if ( ProtonTheta_Deg < t_thetaProt_lb->GetVal()) { continue; }
						if ( ProtonTheta_Deg > t_thetaProt_ub->GetVal()) { continue; }
					}
			
                    if (fApplyPhiOpeningAngleProt) {
                            if ( TMath::Abs(ProtonPhi_Deg - 30) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 90) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 150) > PhiOpeningAngleProt \
                                && TMath::Abs(ProtonPhi_Deg - 210) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 270) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 330) > PhiOpeningAngleProt ) {
                                    continue;
                            }
                    }

                    if (fApplyPhiSliceProt_Sectors && ProtonSector != (ElectronSector + 3)%6) { continue; }
                    if (fApplyProtMomCut && (ProtonMag < t_ProtMom_lb->GetVal() || ProtonMag > t_ProtMom_ub->GetVal())) { continue; }

					h2_el_CosTheta_E->Fill(V3_el.CosTheta(),V4_el.E(),-P_3pto1p[j]*histoweight);


					if (el_theta >= t_thetaEl_lb->GetVal() && el_theta <= t_thetaEl_ub->GetVal()) { // smithja: there looks to be continue statements above that already necessitate this condition
						if (p_miss_perp[j] < PtMax && Interaction > -1) {h1_InteractionBreakdown_Omega_NoQ4Weight_InSector_el_mom_ptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4); }
                                                if (Interaction > -1) {
							h1_InteractionBreakDown_Omega_NoQ4Weight_InSector_el_mom_noptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4);
							h1_InteractionBreakDown_Omega_NoQ4Weight_Insector_prot_mom_QE[Interaction][ProtonSector]->Fill( ProtonMag, -P_3pto1p[j]*histoweight);

                            h1_InteractionBreakDown_InSector_Em[Interaction][ProtonSector]->Fill(Em, -P_3pto1p[j]*histoweight);
								h1_InteractionBreakDown_InSector_Pm[Interaction][ProtonSector]->Fill(pmiss, -P_3pto1p[j]*histoweight);
								h2_InteractionBreakDown_InSector_EmPm[Interaction][ProtonSector]->Fill(Em,pmiss, -P_3pto1p[j]*histoweight);
								h1_InteractionBreakDown_ThetaPQ[Interaction][ProtonSector]->Fill(ThetaPQ, -P_3pto1p[j]*histoweight);
							h1_InteractionBreakDown_InSector_el_mom_Emcut[Interaction][ProtonSector]->Fill(el_momentum,-P_3pto1p[j]*histoweight);

                                                		if(hitnuc == 2212) h1_hit_nuc_pass->Fill(1,-P_3pto1p[j]*histoweight);
	                                                        if(hitnuc == 2112) h1_hit_nuc_pass->Fill(2,-P_3pto1p[j]*histoweight);

						        if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][0]->Fill( ProtonMag, -P_3pto1p[j]*histoweight); }
                                                        if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][1]->Fill( ProtonMag, -P_3pto1p[j]*histoweight); }
						}
					}

					h2_Electron_Theta_Phi->Fill( el_phi_mod, V3_el.Theta()*180./TMath::Pi(), -P_3pto1p[j]*histoweight);
                                        h1_InteractionBreakDown_NoQ4Weight_InSector_el_theta[Interaction][ElectronSector]->Fill( V3_el.Theta()*180./TMath::Pi(), -P_3pto1p[j]*histoweight);
					h1_InteractionBreakDown_NoQ4Weight_InSector_prot_theta[Interaction][ProtonSector]->Fill( ProtonTheta_Deg, -P_3pto1p[j]*histoweight); // smithja: might have to adjust ProtonSector
					if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][0]->Fill( ProtonTheta_Deg, -P_3pto1p[j]*histoweight); }
                                        if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][1]->Fill( ProtonTheta_Deg, -P_3pto1p[j]*histoweight); }

                                        double prot_phi_plot = ProtonPhi_Deg; // smithja: alias	ProtonPhi_Deg for plotting purposes in h2_prot_theta_phi
                                        if (prot_phi_plot < 0.)	{ prot_phi_plot += 360.; } // smithja: this statement puts the proton phi in the correct range for plotting; a similar statement making	sure ProtonPhi_Deg is below 360
                                                                                           //          degrees is included towards the top of this code, so the only modification to prot_phi_plot needed is what's shown in this statement
					h2_prot_theta_phi->Fill( prot_phi_plot, ProtonTheta_Deg, -P_3pto1p[j]*histoweight);						
					PassCounter3 ++;
					
                                        // smithja: These TH2s are used to investigate correlations between proton momtentum and other variables.
                                        h2_prot_mom_el_phi->Fill( el_phi_mod, ProtonMag, -P_3pto1p[j]*histoweight);
                                        h2_prot_mom_el_theta->Fill( V3_el.Theta()*180./TMath::Pi(), ProtonMag, -P_3pto1p[j]*histoweight);
                                        h2_prot_mom_el_mom->Fill( el_momentum, ProtonMag, -P_3pto1p[j]*histoweight);
                                        h2_prot_mom_phi->Fill( prot_phi_plot, ProtonMag, -P_3pto1p[j]*histoweight);
                                        h2_prot_mom_theta->Fill( ProtonTheta_Deg, ProtonMag, -P_3pto1p[j]*histoweight);

					h1_el_mom_corr->Fill(V4_el.Rho(),-P_3pto1p[j]*histoweight);
					//h1_prot_mom->Fill( ProtonMag, -P_3pto1p[j]*histoweight);
					h1_histoweight->Fill(-P_3pto1p[j]*histoweight);
					h1_histoweight2->Fill(-P_3pto1p[j]);
					//if (-P_3pto1p[j]*histoweight == 0) {h1_prot_mom->Fill( ProtonMag, -P_3pto1p[j]*histoweight);}
					//if (-P_3pto1p[j]*histoweight != 0) {h1_prot_mom->Fill( ProtonMag, 1/(-P_3pto1p[j]*histoweight));}

					h1_el_prot_phi_diff->Fill(el_phi_mod-ProtonPhi_Deg,-P_3pto1p[j]*histoweight);
					h2_el_prot_theta->Fill(el_theta,ProtonTheta_Deg,-P_3pto1p[j]*histoweight);
					h2_el_prot_phi->Fill(el_phi_mod,ProtonPhi_Deg,-P_3pto1p[j]*histoweight);
					h2_el_prot_mom->Fill(V4_el.Rho(), ProtonMag, -P_3pto1p[j]*histoweight);

					double LocalWeight = -P_3pto1p[j]*histoweight;

					h2_Electron_Theta_Momentum->Fill(V4_el.Rho(),V3_el.Theta()*180./TMath::Pi(),-P_3pto1p[j]*histoweight);
					h2_Proton_Theta_Momentum->Fill( ProtonMag, V3_prot_corr[j].Theta()*180./TMath::Pi(),-P_3pto1p[j]*histoweight);
					h1_prot_theta->Fill(V3_prot_corr[j].Theta()*180./TMath::Pi(),-P_3pto1p[j]*histoweight);
					h1_prot_theta_noweight->Fill(V3_prot_corr[j].Theta()*180./TMath::Pi());
					h1_prot_costheta->Fill(V3_prot_corr[j].CosTheta(),-P_3pto1p[j]*histoweight);

					// -----------------------------------------------------------------------------------------------
					// Reconstruct xB, W, Q2 using Ecal instead of Etrue

					CalKineVars = CalculateCalKineVars(E_cal[j],V4_el);

					// Fill plots based on underlying interactions

					Q2_BreakDown[0]->Fill(reco_Q2,LocalWeight);
					Nu_BreakDown[0]->Fill(nu,LocalWeight);
					Pe_BreakDown[0]->Fill(V4_el.Rho(),LocalWeight);	

					// ---------------------------------------------------------------------------------------------------------------------	

					double PTmiss = p_miss_perp[j];
					double Ecal = E_cal[j];

					double EcalReso = (Ecal-en_beam_Ecal[fbeam_en])/en_beam_Ecal[fbeam_en];

					// ---------------------------------------------------------------------------------------------------------------------

					//h1_EePrime_InCosThetaEPrimeSlices[CosThetaEPrimeSlice]->Fill(V4_el.E(),LocalWeight);								

	 				if (fchoice > 0) {

						Q2_BreakDown[Interaction]->Fill(reco_Q2,LocalWeight);
						Nu_BreakDown[Interaction]->Fill(nu,LocalWeight);
						Pe_BreakDown[Interaction]->Fill(V4_el.Rho(),LocalWeight);
					}

					// -----------------------------------------------------------------------------------------------

				} //end loop over N_3p

			} // end if num_pi_phot==0 && N_p_three!=0, no pions

			//----------------------------------3p 1pi ----------------------------------------------------------

			if (num_pi_phot==1) {

				double P_tot_3p[N_3p]={0};
				double Ecal_3p1pi[N_3p]={0};
				double p_miss_perp_3p1pi[N_3p]={0};
				TVector3 V3_pi_corr;
				double pion_acc_ratio = 1;

				if (fchoice == 0) { //CLAS data
					V3_pi_corr.SetXYZ(pxf[ind_pi_phot[0]],pyf[ind_pi_phot[0]],pzf[ind_pi_phot[0]]);
					pion_acc_ratio = 1; //Acceptance is 1 for CLAS datafile
				}

				if (fchoice > 0){ //GENIE data

					pion_acc_ratio = 0; //Reset to 0 just to be sure
					V3_pi_corr.SetXYZ(Smeared_Ppi[0]/pf[ind_pi_phot[0]] * pxf[ind_pi_phot[0]],Smeared_Ppi[0]/pf[ind_pi_phot[0]] * pyf[ind_pi_phot[0]],
							Smeared_Ppi[0]/pf[ind_pi_phot[0]] * pzf[ind_pi_phot[0]]);

					double phi_pion = V3_pi_corr.Phi(); //in Radians
					V3_pi_corr.SetPhi(phi_pion + TMath::Pi() ); // Vec.Phi() is between (-180,180)
					phi_pion += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS

					double pion_theta = V3_pi_corr.Theta();
					double pion_mom_corr = V3_pi_corr.Mag();

					if (charge_pi[0] == 1) { //acceptance for pi plus
						pion_acc_ratio = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, 211, file_acceptance_pip,ApplyAccWeights);
						if ( fabs(pion_acc_ratio) != pion_acc_ratio ) { continue; }
					}
					else if (charge_pi[0] == -1) {		//acceptance for pi minus. using electron acceptance map

//						pion_acc_ratio = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,ApplyAccWeights);

						// UNTIL AXEL CREATES THE CORRECT PIMINUS MAP, WE SET THE PIMINUS ACCEPTANCE TO BE 1
//						pion_acc_ratio = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,false);
						pion_acc_ratio = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance_pim,true);

						if ( fabs(pion_acc_ratio) != pion_acc_ratio ) { continue; }
					}
					else if (charge_pi[0] == 0) {		//acceptance for photon/pi0 is 1 for now F.H. 09/24/19
						 pion_acc_ratio = 1;
					}
					else { std::cout << "WARNING: 3proton and 1 Pion loop. pion_acc_ratio is still 0. Continue with next event " << std::endl;	continue; }

				}

				rotation->prot3_pi1_rot_func(V3_prot_corr,V3_prot_uncorr, V3_pi_corr, charge_pi[0] , V4_el,	Ecal_3p1pi,p_miss_perp_3p1pi, P_tot_3p);

				//for CLAS data is histoweight = 1/Mott_cross_sec
				double histoweight = pion_acc_ratio * weight_protons * e_acc_ratio * wght/Mott_cross_sec; 
				//Weight for 3protons, 1 pion, 1 electron, GENIE weight and Mott cross section

				for(int j = 0; j < N_3p; j++) { //loop over 3 protons

					h2_pperp_W->Fill(W_var,p_miss_perp[j],P_tot_3p[j]*histoweight);
					h1_theta0->Fill((V4_beam.Vect()).Angle(V4_el.Vect()+V3_prot_uncorr[j])*TMath::RadToDeg(),P_tot_3p[j]*histoweight);


					double ProtonPhi_Deg = V3_prot_corr[j].Phi() *180. / TMath::Pi() + 30;
					//double ProtonPhi_Deg = V3_prot_corr[j].Phi() *180. / TMath::Pi() + 180 + 30; // smithja: commented out on 9/22/2021; 180-degree shift not needed here
					if (ProtonPhi_Deg > 360.) { ProtonPhi_Deg -= 360.; } 
                                        if (ProtonPhi_Deg < 0.) { ProtonPhi_Deg += 360.; }
                                        int ProtonSector = ProtonPhi_Deg / 60;
					double ProtonTheta_Deg = V3_prot_corr[j].Theta() *180. / TMath::Pi();
					double ProtonMag = V3_prot_corr[j].Mag();
					double ProtonTK = sqrt(ProtonMag*ProtonMag + m_prot*m_prot) - m_prot;
					double Em = (nu - ProtonTK);
					TVector3 pmiss_vec =  V3_rot_q - V3_prot_corr[j];				
					double pmiss = pmiss_vec.Mag();
					double ThetaPQ = V3_rot_q.Angle(V3_prot_corr[j]) * 180. / TMath::Pi();				
	
                    if (Em > Em_ub)  {continue;}

					if(ThetaPQ > theta_pq_cut) { continue; }//Looking at ThetaPQ cut
					
					if (fApplyThetaSliceProt) {  // hard coded range for now
						if ( ProtonTheta_Deg < t_thetaProt_lb->GetVal()) { continue; }
						if ( ProtonTheta_Deg > t_thetaProt_ub->GetVal()) { continue; }
					}
			
                    if (fApplyPhiOpeningAngleProt) {
                            if ( TMath::Abs(ProtonPhi_Deg - 30) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 90) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 150) > PhiOpeningAngleProt \
                                && TMath::Abs(ProtonPhi_Deg - 210) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 270) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 330) > PhiOpeningAngleProt ) {
                                    continue;
                            }
                    }

                    if (fApplyPhiSliceProt_Sectors && ProtonSector != (ElectronSector + 3)%6) { continue; }
                    if (fApplyProtMomCut && (ProtonMag < t_ProtMom_lb->GetVal() || ProtonMag > t_ProtMom_ub->GetVal())) { continue; }

					h2_el_CosTheta_E->Fill(V3_el.CosTheta(),V4_el.E(),P_tot_3p[j]*histoweight);


					if (el_theta >= t_thetaEl_lb->GetVal() && el_theta <= t_thetaEl_ub->GetVal()) { // smithja: there looks to be continue statements above that already necessitate this condition
						if (p_miss_perp[j] < PtMax && Interaction > -1) {h1_InteractionBreakdown_Omega_NoQ4Weight_InSector_el_mom_ptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4); }
                                                if (Interaction > -1) {
							h1_InteractionBreakDown_Omega_NoQ4Weight_InSector_el_mom_noptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4);
							h1_InteractionBreakDown_Omega_NoQ4Weight_Insector_prot_mom_QE[Interaction][ProtonSector]->Fill( ProtonMag, P_tot_3p[j]*histoweight);

                            h1_InteractionBreakDown_InSector_Em[Interaction][ProtonSector]->Fill(Em, P_tot_3p[j]*histoweight);
								h1_InteractionBreakDown_InSector_Pm[Interaction][ProtonSector]->Fill(pmiss, P_tot_3p[j]*histoweight);
								h2_InteractionBreakDown_InSector_EmPm[Interaction][ProtonSector]->Fill(Em,pmiss, P_tot_3p[j]*histoweight);
								h1_InteractionBreakDown_ThetaPQ[Interaction][ProtonSector]->Fill(ThetaPQ, P_tot_3p[j]*histoweight);
							h1_InteractionBreakDown_InSector_el_mom_Emcut[Interaction][ProtonSector]->Fill(el_momentum,P_tot_3p[j]*histoweight);

								if(hitnuc == 2212) h1_hit_nuc_pass->Fill(1,P_tot_3p[j]*histoweight);
	                                                        if(hitnuc == 2112) h1_hit_nuc_pass->Fill(2,P_tot_3p[j]*histoweight);

                                                        if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][0]->Fill( ProtonMag, P_tot_3p[j]*histoweight); }
                                                        if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][1]->Fill( ProtonMag, P_tot_3p[j]*histoweight); }
						}
					}

					h2_Electron_Theta_Phi->Fill( el_phi_mod, V3_el.Theta()*180./TMath::Pi(), P_tot_3p[j]*histoweight);
                                        h1_InteractionBreakDown_NoQ4Weight_InSector_el_theta[Interaction][ElectronSector]->Fill( V3_el.Theta()*180./TMath::Pi(), P_tot_3p[j]*histoweight);
					h1_InteractionBreakDown_NoQ4Weight_InSector_prot_theta[Interaction][ProtonSector]->Fill( ProtonTheta_Deg, P_tot_3p[j]*histoweight); // smithja: might have to adjust ProtonSector
					if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][0]->Fill( ProtonTheta_Deg, P_tot_3p[j]*histoweight); }
                                        if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][1]->Fill( ProtonTheta_Deg, P_tot_3p[j]*histoweight); }

                                        double prot_phi_plot = ProtonPhi_Deg; // smithja: alias	ProtonPhi_Deg for plotting purposes in h2_prot_theta_phi
                                        if (prot_phi_plot < 0.)	{ prot_phi_plot += 360.; } // smithja: this statement puts the proton phi in the correct range for plotting; a similar statement making	sure ProtonPhi_Deg is below 360
                                                                                           //          degrees is included towards the top of this code, so the only modification to prot_phi_plot needed is what's shown in this statement
					h2_prot_theta_phi->Fill( prot_phi_plot, ProtonTheta_Deg, P_tot_3p[j]*histoweight);						
					PassCounter3 ++;
					
                                        // smithja: These TH2s are used to investigate correlations between proton momtentum and other variables.
                                        h2_prot_mom_el_phi->Fill( el_phi_mod, ProtonMag, P_tot_3p[j]*histoweight);
                                        h2_prot_mom_el_theta->Fill( V3_el.Theta()*180./TMath::Pi(), ProtonMag, P_tot_3p[j]*histoweight);
                                        h2_prot_mom_el_mom->Fill( el_momentum, ProtonMag, P_tot_3p[j]*histoweight);
                                        h2_prot_mom_phi->Fill( prot_phi_plot, ProtonMag, P_tot_3p[j]*histoweight);
                                        h2_prot_mom_theta->Fill( ProtonTheta_Deg, ProtonMag, P_tot_3p[j]*histoweight);

					h1_el_mom_corr->Fill(V4_el.Rho(),P_tot_3p[j]*histoweight);
					//h1_prot_mom->Fill( ProtonMag, P_tot_3p[j]*histoweight);
					h1_histoweight->Fill(P_tot_3p[j]*histoweight);
					h1_histoweight2->Fill(P_tot_3p[j]);
					//if (P_tot_3p[j]*histoweight == 0) {h1_prot_mom->Fill( ProtonMag, P_tot_3p[j]*histoweight);}
					//if (P_tot_3p[j]*histoweight != 0) {h1_prot_mom->Fill( ProtonMag, 1/(P_tot_3p[j]*histoweight));}

					h1_el_prot_phi_diff->Fill(el_phi_mod-ProtonPhi_Deg,P_tot_3p[j]*histoweight);
					h2_el_prot_theta->Fill(el_theta,ProtonTheta_Deg,P_tot_3p[j]*histoweight);
					h2_el_prot_phi->Fill(el_phi_mod,ProtonPhi_Deg,P_tot_3p[j]*histoweight);
					h2_el_prot_mom->Fill(V4_el.Rho(), ProtonMag, P_tot_3p[j]*histoweight);

					double LocalWeight = P_tot_3p[j]*histoweight;

					h2_Electron_Theta_Momentum->Fill(V4_el.Rho(),V3_el.Theta()*180./TMath::Pi(),P_tot_3p[j]*histoweight);
					h2_Proton_Theta_Momentum->Fill( ProtonMag, V3_prot_corr[j].Theta()*180./TMath::Pi(),P_tot_3p[j]*histoweight);
					h1_prot_theta->Fill(V3_prot_corr[j].Theta()*180./TMath::Pi(),P_tot_3p[j]*histoweight);
					h1_prot_theta_noweight->Fill(V3_prot_corr[j].Theta()*180./TMath::Pi());
					h1_prot_costheta->Fill(V3_prot_corr[j].CosTheta(),P_tot_3p[j]*histoweight);

					// -----------------------------------------------------------------------------------------------
					// Reconstruct xB, W, Q2 using Ecal instead of Etrue

					CalKineVars = CalculateCalKineVars(E_cal[j],V4_el);

					// Fill plots based on underlying interactions

					Q2_BreakDown[0]->Fill(reco_Q2,LocalWeight);
					Nu_BreakDown[0]->Fill(nu,LocalWeight);
					Pe_BreakDown[0]->Fill(V4_el.Rho(),LocalWeight);

					// ---------------------------------------------------------------------------------------------------------------------	

					double PTmiss = p_miss_perp[j];
					double Ecal = E_cal[j];

					double EcalReso = (Ecal-en_beam_Ecal[fbeam_en])/en_beam_Ecal[fbeam_en];

					// ---------------------------------------------------------------------------------------------------------------------

					//h1_EePrime_InCosThetaEPrimeSlices[CosThetaEPrimeSlice]->Fill(V4_el.E(),LocalWeight);							

	 				if (fchoice > 0) {

						Q2_BreakDown[Interaction]->Fill(reco_Q2,LocalWeight);
						Nu_BreakDown[Interaction]->Fill(nu,LocalWeight);
						Pe_BreakDown[Interaction]->Fill(V4_el.Rho(),LocalWeight);

					}

					// -----------------------------------------------------------------------------------------------


				} //end loop over N_3p

			} // 1 pi requirement ends

		} //end of 3-proton case

		// -------------------------------------------------------------------------------------------------------------------------------------

		// NOAH:: Deleted 4proton rotation case because it was commented out as "Massively messed up"
		// We are not looking for 4 Proton and 1 Pion events!

		// ---------------------------------------------------------------------------------------------------------------------------------------

		//No Protons here, Next 150 lines are for the inclusive events

		h1_el_mom_incl->Fill(V4_el.Rho(),WeightIncl);
		h2_el_theta_phi_incl->Fill(V4_el.Theta()*180./TMath::Pi(),V4_el.Phi(),WeightIncl);


		//----------------------------- e- ,1pi  -----------------------------------------

		if (num_pi_phot == 1) {

			TVector3 V3_pi_corr;
			double P_undet=0;
			double pion_acc_ratio = 1;

			if (fchoice == 0) { //CLAS data
				V3_pi_corr.SetXYZ(pxf[ind_pi_phot[0]], pyf[ind_pi_phot[0]], pzf[ind_pi_phot[0]]);
				pion_acc_ratio = 1; //acceptance is 1 for CLAS data
			}

			if (fchoice > 0) { //GENIE data
				pion_acc_ratio = 0; //reset just to be sure
				V3_pi_corr.SetXYZ(Smeared_Ppi[0]/pf[ind_pi_phot[0]] * pxf[ind_pi_phot[0]],Smeared_Ppi[0]/pf[ind_pi_phot[0]] * pyf[ind_pi_phot[0]],
						Smeared_Ppi[0]/pf[ind_pi_phot[0]] * pzf[ind_pi_phot[0]]);
				double phi_pion = V3_pi_corr.Phi(); //in Radians
				V3_pi_corr.SetPhi(phi_pion + TMath::Pi() ); // Vec.Phi() is between (-180,180)
				phi_pion += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS

				double pion_theta = V3_pi_corr.Theta();
				double pion_mom_corr = V3_pi_corr.Mag();

				if (charge_pi[0] == 1) { //acceptance for pi plus
					pion_acc_ratio = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, 211, file_acceptance_pip,ApplyAccWeights);
					if ( fabs(pion_acc_ratio) != pion_acc_ratio ) { continue; }
				}
				else if (charge_pi[0] == -1) {	 //acceptance for pi minus. using electron acceptance map

					//pion_acc_ratio = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,ApplyAccWeights);

					// UNTIL AXEL CREATES THE CORRECT PIMINUS MAP, WE SET THE PIMINUS ACCEPTANCE TO BE 1
//					pion_acc_ratio = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,false);
					pion_acc_ratio = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance_pim,true);

					if ( fabs(pion_acc_ratio) != pion_acc_ratio ) { continue; }
				}
				else if (charge_pi[0] == 0) {	 //acceptance for photon/pi0 is 1 for now F.H. 09/24/19
					pion_acc_ratio = 1;
				}
				else { std::cout << "WARNING: 1 Pion Events. pion_acc_ratio is still 0. Continue with next event " << std::endl;  continue; }

			}

			rotation->pi1_rot_func( V3_pi_corr, charge_pi[0], &P_undet);

			//histoweight is 1/Mott_cross_sec for CLAS data
			double histoweight = pion_acc_ratio * WeightIncl;


		}

		//----------------------------- e- ,2pi  -----------------------------------------

		if(num_pi_phot == 2) {

			const int N_2pi = 2;
			TVector3 V3_2pi_corr[N_2pi];
			double P_1pi[N_2pi] = {0};
			double P_0pi = 0;
			double pion_acc_ratio[N_2pi] = {1};

			for (int i = 0; i < num_pi_phot; i++) {

				if (fchoice == 0) { //CLAS data
					V3_2pi_corr[i].SetXYZ( pxf[ind_pi_phot[i]], pyf[ind_pi_phot[i]], pzf[ind_pi_phot[i]]);
					pion_acc_ratio[i] = 1; //Acceptance is 1 for CLAS data
				}

				if (fchoice > 0) { //GENIE data
					pion_acc_ratio[i] = 0; //Reset just to be secure
					V3_2pi_corr[i].SetXYZ(Smeared_Ppi[i]/pf[ind_pi_phot[i]] * pxf[ind_pi_phot[i]],Smeared_Ppi[i]/pf[ind_pi_phot[i]] * pyf[ind_pi_phot[i]],
							Smeared_Ppi[i]/pf[ind_pi_phot[i]] * pzf[ind_pi_phot[i]]);
					double phi_pion = V3_2pi_corr[i].Phi(); //in Radians
					V3_2pi_corr[i].SetPhi(phi_pion + TMath::Pi() ); // Vec.Phi() is between (-180,180)
					phi_pion += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS

					double pion_theta = V3_2pi_corr[i].Theta();
					double pion_mom_corr = V3_2pi_corr[i].Mag();

					if (charge_pi[i] == 1) { //acceptance for pi plus
						pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, 211, file_acceptance_pip,ApplyAccWeights);
						if ( fabs(pion_acc_ratio[i]) != pion_acc_ratio[i] ) { continue; }
					}
					else if (charge_pi[i] == -1) {	//acceptance for pi minus. using electron acceptance map

//						pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,ApplyAccWeights);

						// UNTIL AXEL CREATES THE CORRECT PIMINUS MAP, WE SET THE PIMINUS ACCEPTANCE TO BE 1
//						pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,false);
						pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance_pim,true);

						if ( fabs(pion_acc_ratio[i]) != pion_acc_ratio[i] ) { continue; }
					}
					else if (charge_pi[i] == 0) {	//acceptance for photon/pi0 is 1 for now F.H. 09/24/19
						pion_acc_ratio[i] = 1;
					}
					else { std::cout << "WARNING: 2 Pion Events. pion_acc_ratio is still 0. Continue with next event " << std::endl;	continue; }
				}

			} //end loop over num_pi_phot

			rotation->pi2_rot_func(V3_2pi_corr, charge_pi, &P_0pi,P_1pi);
			//weight_pions is 1 for CLAS data
			double weight_pions = pion_acc_ratio[0] * pion_acc_ratio[1];
			//histoweight is 1/Mott_cross_sec for CLAS data
			double histoweight = weight_pions * e_acc_ratio * wght/Mott_cross_sec;

			//----------------------------- e- ,2pi->0pi (-) -----------------------------------------


			//----------------------------- e- ,2pi->1pi->0pi (+)  -----------------------------------------



		} //end if for two pion events

		//----------------------------- e- ,3pi  -----------------------------------------

		if(num_pi_phot == 3){

			const int N_3pi=3;
			const int N_2pi=2;
			TVector3 V3_3pi_corr[N_3pi];
			double P_0pi = 0;
			double P_1pi[N_3pi]={0};
			double P_320pi[N_3pi]={0};
			double P_3210pi[N_3pi][N_2pi]={0};
			double pion_acc_ratio[N_3pi] = {1};

			for (int i = 0; i < num_pi_phot; i++) {

				if (fchoice == 0) { //CLAS data

					V3_3pi_corr[i].SetXYZ( pxf[ind_pi_phot[i]], pyf[ind_pi_phot[i]], pzf[ind_pi_phot[i]]);
					pion_acc_ratio[i] = 1; //Acceptance is 1 for CLAS data
				}

				if (fchoice > 0) { //GENIE data

					pion_acc_ratio[i] = 0; //Reset just to be sure
					V3_3pi_corr[i].SetXYZ(Smeared_Ppi[i]/pf[ind_pi_phot[i]] * pxf[ind_pi_phot[i]],Smeared_Ppi[i]/pf[ind_pi_phot[i]] * pyf[ind_pi_phot[i]],
								Smeared_Ppi[i]/pf[ind_pi_phot[i]] * pzf[ind_pi_phot[i]]);
					double phi_pion = V3_3pi_corr[i].Phi(); //in Radians
					V3_3pi_corr[i].SetPhi(phi_pion + TMath::Pi() ); // Vec.Phi() is between (-180,180)
					phi_pion += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS

					double pion_theta = V3_3pi_corr[i].Theta();
					double pion_mom_corr = V3_3pi_corr[i].Mag();

					if (charge_pi[i] == 1) { //acceptance for pi plus
						pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, 211, file_acceptance_pip,ApplyAccWeights);
						if ( fabs(pion_acc_ratio[i]) != pion_acc_ratio[i] ) { continue; }
					}
					else if (charge_pi[i] == -1) {	//acceptance for pi minus. using electron acceptance map

						//pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,ApplyAccWeights);

						// UNTIL AXEL CREATES THE CORRECT PIMINUS MAP, WE SET THE PIMINUS ACCEPTANCE TO BE 1
//						pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,false);
						pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance_pim,true);

						if ( fabs(pion_acc_ratio[i]) != pion_acc_ratio[i] ) { continue; }
					}
					else if (charge_pi[i] == 0) {	//acceptance for photon/pi0 is 1 for now F.H. 09/24/19
						pion_acc_ratio[i] = 1;
					}
					else { std::cout << "WARNING: 3 Pion Events. pion_acc_ratio is still 0. Continue with next event " << std::endl;  continue; }

				}

			} //end loop over num_pi_phot

			rotation->pi3_rot_func( V3_3pi_corr, charge_pi, &P_0pi, P_1pi, P_320pi,P_3210pi);
			//weight_pions is 1 for CLAS data
			double weight_pions = pion_acc_ratio[0] * pion_acc_ratio[1] * pion_acc_ratio[2];
			//histoweight is 1/Mott_cross_sec for CLAS data
			double histoweight = weight_pions * e_acc_ratio * wght/Mott_cross_sec;

			//---------------------------3pi->0pi----------------------------------------------


		}//end of 3pi requirement

		//----------------------------- e- ,4pi  -----------------------------------------

		if(num_pi_phot == 4){

			const int N_4pi=4;
			TVector3 V3_4pi_corr[N_4pi];
			double P_0pi=0;
			double P_410pi=0;
			double P_420pi=0;
			double P_4210pi=0;
			double P_430pi=0;
			double P_4310pi=0;
			double P_4320pi=0;
			double P_43210pi=0;
			double pion_acc_ratio[N_4pi] = {1};

			for (int i = 0; i < num_pi_phot; i++) {

				if (fchoice == 0) { //CLAS data
					V3_4pi_corr[i].SetXYZ( pxf[ind_pi_phot[i]], pyf[ind_pi_phot[i]], pzf[ind_pi_phot[i]]);
					pion_acc_ratio[i] = 1; //Acceptance is 1 for CLAS data
				}

				if (fchoice > 0) { //GENIE data

						pion_acc_ratio[i] = 0; //Reset just to be sure
						V3_4pi_corr[i].SetXYZ(Smeared_Ppi[i]/pf[ind_pi_phot[i]] * pxf[ind_pi_phot[i]],Smeared_Ppi[i]/pf[ind_pi_phot[i]] * pyf[ind_pi_phot[i]],
									Smeared_Ppi[i]/pf[ind_pi_phot[i]] * pzf[ind_pi_phot[i]]);
						// apapadop
						double phi_pion = V3_4pi_corr[i].Phi(); //in Radians
						V3_4pi_corr[i].SetPhi(phi_pion + TMath::Pi() ); // Vec.Phi() is between (-180,180)
						phi_pion += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS

						double pion_theta = V3_4pi_corr[i].Theta();
						double pion_mom_corr = V3_4pi_corr[i].Mag();

						if (charge_pi[i] == 1) { //acceptance for pi plus
							pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, 211, file_acceptance_pip,ApplyAccWeights);
							if ( fabs(pion_acc_ratio[i]) != pion_acc_ratio[i] ) { continue; }
						}
						else if (charge_pi[i] == -1) {    //acceptance for pi minus. using electron acceptance map

							//pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,ApplyAccWeights);

							// UNTIL AXEL CREATES THE CORRECT PIMINUS MAP, WE SET THE PIMINUS ACCEPTANCE TO BE 1
//							pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,false);
							pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance_pim,true);

							if ( fabs(pion_acc_ratio[i]) != pion_acc_ratio[i] ) { continue; }
						}
						else if (charge_pi[i] == 0) {    //acceptance for photon/pi0 is 1 for now F.H. 09/24/19
							pion_acc_ratio[i] = 1;
						}
						else { std::cout << "WARNING: 4 Pion Events. pion_acc_ratio is still 0. Continue with next event " << std::endl;  continue; }
				}

			} //end loop over num_pi_phot

			rotation->pi4_rot_func(V3_4pi_corr, charge_pi, &P_0pi,&P_410pi,&P_420pi,&P_4210pi,&P_430pi,&P_4310pi,&P_4320pi,&P_43210pi);

			//weight_pions is 1 for CLAS data
			double weight_pions = pion_acc_ratio[0] * pion_acc_ratio[1] * pion_acc_ratio[2] * pion_acc_ratio[3];
			//histoweight is 1/Mott_cross_sec for CLAS data
			double histoweight = weight_pions * e_acc_ratio * wght/Mott_cross_sec;

			//---------------------------4pi->0pi----------------------------------------------


		}//end of 4 pi/photon requirement

		//------------------------------------------requiring there to be a proton -------------------------------------

		//Events with exactly one proton

		if( num_p == 1) {

			//Vector for proton without momentum smearing
			TLorentzVector V4_prot_uncorr(pxf[index_p[0]],pyf[index_p[0]],pzf[index_p[0]],TMath::Sqrt(m_prot*m_prot+pf[index_p[0]]*pf[index_p[0]]));
			TVector3 V3_prot_uncorr = V4_prot_uncorr.Vect();

			//Vector for proton with momentum smearing or correction (energy loss)
			TVector3 V3_prot_corr;
			TLorentzVector V4_prot_corr;

			double p_acc_ratio = 1; //acceptance is 1 for CLAS data

			if (fchoice == 0) { //CLAS data
				V3_prot_corr.SetXYZ(pxf[index_p[0]+60], pyf[index_p[0]+60], pzf[index_p[0]+60]);
				V4_prot_corr.SetPxPyPzE(pxf[index_p[0]+60], pyf[index_p[0]+60], pzf[index_p[0]+60],TMath::Sqrt(m_prot*m_prot+pf[index_p[0]+60]*pf[index_p[0]+60]));
			}
			if (fchoice > 0) { //GENIE data
				p_acc_ratio = 0; //Reset just to be sure
				//Fiducial cuts are done in the hadron loop
				//Vector for proton with momentum smearing
				V3_prot_corr.SetXYZ(Smeared_Pp[0]/pf[index_p[0]] * pxf[index_p[0]],Smeared_Pp[0]/pf[index_p[0]] * pyf[index_p[0]],Smeared_Pp[0]/pf[index_p[0]] * pzf[index_p[0]]);
				V4_prot_corr.SetPxPyPzE(Smeared_Pp[0]/pf[index_p[0]] * pxf[index_p[0]],Smeared_Pp[0]/pf[index_p[0]] * pyf[index_p[0]],
							Smeared_Pp[0]/pf[index_p[0]] * pzf[index_p[0]],Smeared_Ep[0]);

				double phi_prot = V3_prot_corr.Phi(); //in Radians
				V3_prot_corr.SetPhi(phi_prot + TMath::Pi() ); // Vec.Phi() is between (-180,180)
				phi_prot += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS

				//Proton kinematic variables
				double p_theta = V3_prot_corr.Theta();
				double prot_mom_corr = V3_prot_corr.Mag();
				//Proton weight
				p_acc_ratio = acceptance_c(prot_mom_corr, cos(p_theta), phi_prot, 2212,file_acceptance_p,ApplyAccWeights);
				if ( fabs(p_acc_ratio) != p_acc_ratio ) { continue; }

			}

			TLorentzVector V4_prot_el_tot = V4_prot_corr + V4_el;

			double p_perp_tot = TMath::Sqrt(V4_prot_el_tot.Px()*V4_prot_el_tot.Px() + V4_prot_el_tot.Py()*V4_prot_el_tot.Py());
			double E_tot = V4_el.E() + V4_prot_corr.E() - m_prot + bind_en[ftarget];

			//These Histograms are events with 1 electron and  1 proton and multiple pions
			//histoweight_inc is 1/Mott_cross_sec for CLAS data
			double histoweight_inc = p_acc_ratio * e_acc_ratio * wght/Mott_cross_sec;
			double histoweight_NoMott = p_acc_ratio * e_acc_ratio * wght;

			//---------------------------------- 1p 0pi   ----------------------------------------------
			//NOAH :: Main QE plots live here (everything else bkgd)
			// Main Plots
			if(num_pi_phot == 0){
				double ECalReso = (E_tot-en_beam_Ecal[fbeam_en])/en_beam_Ecal[fbeam_en];
				double EQEReso = (E_rec-en_beam_Eqe[fbeam_en])/en_beam_Eqe[fbeam_en];

				SignalEvents++;
				// std::cout << "SignalEvents: " << SignalEvents << std::endl; // smithja: used to track the number of events in the 1e1p0pi case 

				if (Interaction == 1) { QESignalEvents++; }
				else if (Interaction == 2) { MECSignalEvents++; }
				else if (Interaction == 3) { RESSignalEvents++; }
				else if (Interaction == 4) { DISSignalEvents++; }
				else { OtherSignalEvents++; }

				//histoweight is 1/Mott_cross_sec for CLAS data
				double histoweight = p_acc_ratio * e_acc_ratio * wght/Mott_cross_sec;

				h2_pperp_W->Fill(W_var,p_perp_tot,histoweight);
				h1_theta0->Fill((V4_beam.Vect()).Angle(V4_prot_el_tot.Vect()) *TMath::RadToDeg(),histoweight);

				double ProtonPhi_Deg = V3_prot_corr.Phi() *180. / TMath::Pi() + 30;
				//double ProtonPhi_Deg = V3_prot_corr.Phi() *180. / TMath::Pi() + 180 + 30; // smithja: commented out on 9/22/2021; 180-degree shift not needed here
				if (ProtonPhi_Deg > 360.) { ProtonPhi_Deg -= 360.; } 
                                if (ProtonPhi_Deg < 0.) { ProtonPhi_Deg += 360.; }
                                int ProtonSector = ProtonPhi_Deg / 60;
				double ProtonTheta_Deg = V3_prot_corr.Theta() *180. / TMath::Pi();
				double ProtonMag = V3_prot_corr.Mag();
				double ProtonTK = sqrt(ProtonMag*ProtonMag + m_prot*m_prot) - m_prot;
				
				double Em = (nu - ProtonTK);
				TVector3 pmiss_vec =  V3_rot_q - V3_prot_corr;				
				double pmiss = pmiss_vec.Mag();
				double ThetaPQ = V3_rot_q.Angle(V3_prot_corr) * 180. / TMath::Pi();
                		
                if (Em > Em_ub)  {continue;}

				if(ThetaPQ > theta_pq_cut) { continue; }//Looking at ThetaPQ cut
						
				if (fApplyThetaSliceProt) {  // hard coded range for now
					if ( ProtonTheta_Deg < t_thetaProt_lb->GetVal()) { continue; }
					if ( ProtonTheta_Deg > t_thetaProt_ub->GetVal()) { continue; }
				}

                if (fApplyPhiOpeningAngleProt) {
                        if ( TMath::Abs(ProtonPhi_Deg - 30) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 90) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 150) > PhiOpeningAngleProt \
                            && TMath::Abs(ProtonPhi_Deg - 210) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 270) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 330) > PhiOpeningAngleProt ) {
                                continue;
                        }
                }

                if (fApplyPhiSliceProt_Sectors && ProtonSector != (ElectronSector + 3)%6) { continue; }
                if (fApplyProtMomCut && (ProtonMag < t_ProtMom_lb->GetVal() || ProtonMag > t_ProtMom_ub->GetVal())) { continue; }

				h2_el_CosTheta_E->Fill(V3_el.CosTheta(),V4_el.E(),histoweight);


				if (el_theta >= t_thetaEl_lb->GetVal() && el_theta <= t_thetaEl_ub->GetVal()) { // smithja: there looks to be continue statements above that already necessitate this condition
					if (p_perp_tot < PtMax && Interaction > -1) {h1_InteractionBreakdown_Omega_NoQ4Weight_InSector_el_mom_ptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4); }
					if (Interaction > -1) {
						h1_InteractionBreakDown_Omega_NoQ4Weight_InSector_el_mom_noptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4);
						h1_InteractionBreakDown_Omega_NoQ4Weight_Insector_prot_mom_QE[Interaction][ProtonSector]->Fill( ProtonMag, histoweight);

                        h1_InteractionBreakDown_InSector_Em[Interaction][ProtonSector]->Fill(Em, histoweight);
								h1_InteractionBreakDown_InSector_Pm[Interaction][ProtonSector]->Fill(pmiss, histoweight);
								h2_InteractionBreakDown_InSector_EmPm[Interaction][ProtonSector]->Fill(Em,pmiss, histoweight);
								h1_InteractionBreakDown_ThetaPQ[Interaction][ProtonSector]->Fill(ThetaPQ, histoweight);
							h1_InteractionBreakDown_InSector_el_mom_Emcut[Interaction][ProtonSector]->Fill(el_momentum,histoweight);

                                        		if(hitnuc == 2212) h1_hit_nuc_pass->Fill(1,histoweight);
	                                                        if(hitnuc == 2112) h1_hit_nuc_pass->Fill(2,histoweight);

					        if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][0]->Fill( ProtonMag, histoweight); }
                                                if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][1]->Fill( ProtonMag, histoweight); }
					}
				}

				h2_Electron_Theta_Phi->Fill( el_phi_mod, V3_el.Theta()*180./TMath::Pi(), histoweight);
                                h1_InteractionBreakDown_NoQ4Weight_InSector_el_theta[Interaction][ElectronSector]->Fill( V3_el.Theta()*180./TMath::Pi(), histoweight);
				h1_InteractionBreakDown_NoQ4Weight_InSector_prot_theta[Interaction][ProtonSector]->Fill( ProtonTheta_Deg, histoweight);
				if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][0]->Fill( ProtonTheta_Deg, histoweight); }
                                if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][1]->Fill( ProtonTheta_Deg, histoweight); }

                                double prot_phi_plot = ProtonPhi_Deg; // smithja: alias	ProtonPhi_Deg for plotting purposes in h2_prot_theta_phi
                                if (prot_phi_plot < 0.)	{ prot_phi_plot += 360.; } // smithja: this statement puts the proton phi in the correct range for plotting; a similar statement making	sure ProtonPhi_Deg is below 360
                                                                                   //          degrees is included towards the top of this code, so the only modification to prot_phi_plot needed is what's shown in this statement
				h2_prot_theta_phi->Fill( prot_phi_plot, ProtonTheta_Deg, histoweight);					
				PassCounter3 ++;

                                // smithja: These TH2s are used to investigate correlations between proton momtentum and other variables.
                                h2_prot_mom_el_phi->Fill( el_phi_mod, ProtonMag, histoweight);
                                h2_prot_mom_el_theta->Fill( V3_el.Theta()*180./TMath::Pi(), ProtonMag, histoweight);
                                h2_prot_mom_el_mom->Fill( el_momentum, ProtonMag, histoweight);
                                h2_prot_mom_phi->Fill( prot_phi_plot, ProtonMag, histoweight);
                                h2_prot_mom_theta->Fill( ProtonTheta_Deg, ProtonMag, histoweight);

				h1_el_mom_corr->Fill(V4_el.Rho(),histoweight);
				//h1_prot_mom->Fill( ProtonMag, histoweight);
				h1_histoweight->Fill(histoweight);
				h1_histoweight2->Fill(1);
				//if (histoweight == 0) {h1_prot_mom->Fill( ProtonMag, histoweight);}
				//if (histoweight != 0) {h1_prot_mom->Fill( ProtonMag, 1/(histoweight));}
				h1_el_prot_phi_diff->Fill(el_phi_mod-ProtonPhi_Deg,histoweight);
				h2_el_prot_theta->Fill(el_theta,ProtonTheta_Deg,histoweight);
				
				//h2_el_prot_phi->Fill(el_phi_mod,ProtonPhi_Deg,histoweight);
				h2_el_prot_phi->Fill(el_phi_mod,prot_phi_plot,histoweight);				
				h2_el_prot_mom->Fill(V4_el.Rho(), ProtonMag, histoweight);

				//h1_prot_mom_nobackground->Fill( ProtonMag, histoweight);
				h1_prot_angle_nobackground->Fill(V3_prot_corr.Theta()*180./TMath::Pi(),histoweight);
				double LocalWeight = histoweight;

				h2_Electron_Theta_Momentum->Fill(V4_el.Rho(),V3_el.Theta()*180./TMath::Pi(),histoweight);
				h2_Proton_Theta_Momentum->Fill( ProtonMag, V3_prot_corr.Theta()*180./TMath::Pi(),histoweight);
				h1_prot_theta->Fill(V3_prot_corr.Theta()*180./TMath::Pi(),histoweight);
				h1_prot_theta_noweight->Fill(V3_prot_corr.Theta()*180./TMath::Pi());
				h1_prot_costheta->Fill(V3_prot_corr.CosTheta(),histoweight);

				// -----------------------------------------------------------------------------------------------

				// Unweighted plots for number of events

				// -----------------------------------------------------------------------------------------------
				// Reconstruct xB, W, Q2 using Ecal instead of Etrue

				CalKineVars = CalculateCalKineVars(E_tot,V4_el);

				// Fill plots based on underlying interactions

				Q2_BreakDown[0]->Fill(reco_Q2,LocalWeight);
				Nu_BreakDown[0]->Fill(nu,LocalWeight);
				Pe_BreakDown[0]->Fill(V4_el.Rho(),LocalWeight);

				// ---------------------------------------------------------------------------------------------------------------------

				double PTmiss = p_perp_tot;
				double Ecal = E_tot;

				double EcalReso = (Ecal-en_beam_Ecal[fbeam_en])/en_beam_Ecal[fbeam_en];

				// ---------------------------------------------------------------------------------------------------------------------	

				//h1_EePrime_InCosThetaEPrimeSlices[CosThetaEPrimeSlice]->Fill(V4_el.E(),LocalWeight);								

				if (fchoice > 0) {

					Q2_BreakDown[Interaction]->Fill(reco_Q2,LocalWeight);
					Nu_BreakDown[Interaction]->Fill(nu,LocalWeight);
					Pe_BreakDown[Interaction]->Fill(V4_el.Rho(),LocalWeight);

				}

				// -----------------------------------------------------------------------------------------------


			} //num pi=0

			//---------------------------------- 1p 1pi   ----------------------------------------------

			if(num_pi_phot == 1){

				double N_piphot_det;
				double N_piphot_undet;
				TVector3 V3_pi_corr;
				double pion_acc_ratio = 1;

				if (fchoice == 0) { //CLAS data

					pion_acc_ratio = 1; //Acceptance is 1 for CLAS data
					V3_pi_corr.SetXYZ(pxf[ind_pi_phot[0]], pyf[ind_pi_phot[0]], pzf[ind_pi_phot[0]]);
				}

				if (fchoice > 0) { //GENIE data

					pion_acc_ratio = 1; //Reset to 0 just to be sure
					V3_pi_corr.SetXYZ(Smeared_Ppi[0]/pf[ind_pi_phot[0]] * pxf[ind_pi_phot[0]],Smeared_Ppi[0]/pf[ind_pi_phot[0]] * pyf[ind_pi_phot[0]],
							Smeared_Ppi[0]/pf[ind_pi_phot[0]] * pzf[ind_pi_phot[0]]);
					double phi_pion = V3_pi_corr.Phi(); //in Radians
					V3_pi_corr.SetPhi(phi_pion + TMath::Pi() ); // Vec.Phi() is between (-180,180)
					phi_pion += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS

					double pion_theta = V3_pi_corr.Theta();
					double pion_mom_corr = V3_pi_corr.Mag();

					if (charge_pi[0] == 1) { //acceptance for pi plus
					
						pion_acc_ratio = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, 211, file_acceptance_pip,ApplyAccWeights);
						if ( fabs(pion_acc_ratio) != pion_acc_ratio ) { continue; }
					}
					else if (charge_pi[0] == -1) { //acceptance for pi minus. using electron acceptance map

						//pion_acc_ratio = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,ApplyAccWeights);

						// UNTIL AXEL CREATES THE CORRECT PIMINUS MAP, WE SET THE PIMINUS ACCEPTANCE TO BE 1
//						pion_acc_ratio = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,false);
						pion_acc_ratio = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance_pim,true);

						if ( fabs(pion_acc_ratio) != pion_acc_ratio ) { continue; }
					}
					else if (charge_pi[0] == 0) { //acceptance for photon/pi0 is 1 for now F.H. 09/24/19
						pion_acc_ratio = 1;
					}
					else { std::cout << "WARNING: 1 Pion Events. pion_acc_ratio is still 0. Continue with next event " << std::endl;  continue; }

				}
				int _sectr[2];
                        	//for(int f= 0; f < 2; f++) {V3_prot_corr
                        		double ProtonPhi_Deg1 = V3_prot_corr.Phi() *180. / TMath::Pi() + 30;
                         		if (ProtonPhi_Deg1 > 360.) { ProtonPhi_Deg1 -= 360.; }
                           		if (ProtonPhi_Deg1 < 0.) { ProtonPhi_Deg1 += 360.; }
                           		_sectr[0] = ProtonPhi_Deg1 / 60;
					double PiPhi_Deg1 = V3_pi_corr.Phi() *180./TMath::Pi() + 30;
					if (PiPhi_Deg1 > 360. ) {PiPhi_Deg1 -= 360.; }
					if (PiPhi_Deg1 < 0. ) { PiPhi_Deg1 += 360.;  }
					_sectr[1] = PiPhi_Deg1 / 60;
					//std::cout << "Proton sec = " << _sectr[0] << "\n";
					//std::cout << "Pi sec = " << _sectr[1] << "\n";
                        	//}
                         	bool same_sector_bool = false;
                        	if (_sectr[0] != _sectr[1]) {
                               		proton_pion_same_sector++;
                         	}


				rotation->prot1_pi1_rot_func(V3_prot_uncorr,V3_pi_corr, charge_pi[0], &N_piphot_det,&N_piphot_undet);

				//histoweight is 1/Mott_cross_sec for CLAS data
				double histoweight = pion_acc_ratio * p_acc_ratio * e_acc_ratio * wght/Mott_cross_sec; 
				// 1 proton, 1 Pion, 1 electron acceptance, GENIE weight and Mott

				if (N_piphot_det != 0) {

					h2_pperp_W->Fill(W_var,p_perp_tot,-(N_piphot_undet/N_piphot_det)*histoweight);
					h1_theta0->Fill((V4_beam.Vect()).Angle(V4_el.Vect()+V3_prot_uncorr)*TMath::RadToDeg(),-(N_piphot_undet/N_piphot_det)*histoweight);

					double ProtonPhi_Deg = V3_prot_corr.Phi() *180. / TMath::Pi() + 30;
					//double ProtonPhi_Deg = V3_prot_corr.Phi() *180. / TMath::Pi() + 180 + 30; // smithja:	commented out on 9/22/2021; 180-degree shift not needed	here
					if (ProtonPhi_Deg > 360.) { ProtonPhi_Deg -= 360.; } 
                                        if (ProtonPhi_Deg < 0.) { ProtonPhi_Deg += 360.; }
                                        int ProtonSector = ProtonPhi_Deg / 60;
					double ProtonTheta_Deg = V3_prot_corr.Theta() *180. / TMath::Pi();
					double ProtonMag = V3_prot_corr.Mag();
					double ProtonTK = sqrt(ProtonMag*ProtonMag + m_prot*m_prot) - m_prot;
					double Em = (nu - ProtonTK);
					TVector3 pmiss_vec =  V3_rot_q - V3_prot_corr;				
					double pmiss = pmiss_vec.Mag();
					double ThetaPQ = V3_rot_q.Angle(V3_prot_corr) * 180. / TMath::Pi();
				
                    if (Em > Em_ub)  {continue;}

					if(ThetaPQ > theta_pq_cut) { continue; }//Looking at ThetaPQ cut
					
					if (fApplyThetaSliceProt) {  // hard coded range for now
						if ( ProtonTheta_Deg < t_thetaProt_lb->GetVal()) { continue; }
						if ( ProtonTheta_Deg > t_thetaProt_ub->GetVal()) { continue; }
					}
			
                    if (fApplyPhiOpeningAngleProt) {
                            if ( TMath::Abs(ProtonPhi_Deg - 30) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 90) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 150) > PhiOpeningAngleProt \
                                && TMath::Abs(ProtonPhi_Deg - 210) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 270) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 330) > PhiOpeningAngleProt ) {
                                    continue;
                            }
                    }

                    if (fApplyPhiSliceProt_Sectors && ProtonSector != (ElectronSector + 3)%6) { continue; }
                	if (fApplyProtMomCut && (ProtonMag < t_ProtMom_lb->GetVal() || ProtonMag > t_ProtMom_ub->GetVal())) { continue; }

					h2_el_CosTheta_E->Fill(V3_el.CosTheta(),V4_el.E(),-(N_piphot_undet/N_piphot_det)*histoweight);


					if (el_theta >= t_thetaEl_lb->GetVal() && el_theta <= t_thetaEl_ub->GetVal()) { // smithja: there looks to be continue statements above that already necessitate this condition
						if (p_perp_tot < PtMax && Interaction > -1) {h1_InteractionBreakdown_Omega_NoQ4Weight_InSector_el_mom_ptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4); } 
                                                if (Interaction > -1) {
							h1_InteractionBreakDown_Omega_NoQ4Weight_InSector_el_mom_noptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4);
							h1_InteractionBreakDown_Omega_NoQ4Weight_Insector_prot_mom_QE[Interaction][ProtonSector]->Fill( ProtonMag, -(N_piphot_undet/N_piphot_det)*histoweight);

								if(hitnuc == 2212) h1_hit_nuc_pass->Fill(1,-(N_piphot_undet/N_piphot_det)*histoweight);
	                                                        if(hitnuc == 2112) h1_hit_nuc_pass->Fill(2,-(N_piphot_undet/N_piphot_det)*histoweight);

							h1_InteractionBreakDown_InSector_Em[Interaction][ProtonSector]->Fill(Em, -(N_piphot_undet/N_piphot_det)*histoweight);
								h1_InteractionBreakDown_InSector_Pm[Interaction][ProtonSector]->Fill(pmiss,  -(N_piphot_undet/N_piphot_det)*histoweight);
								h2_InteractionBreakDown_InSector_EmPm[Interaction][ProtonSector]->Fill(Em,pmiss,  -(N_piphot_undet/N_piphot_det)*histoweight);
								h1_InteractionBreakDown_ThetaPQ[Interaction][ProtonSector]->Fill(ThetaPQ,  -(N_piphot_undet/N_piphot_det)*histoweight);
							h1_InteractionBreakDown_InSector_el_mom_Emcut[Interaction][ProtonSector]->Fill(el_momentum, -(N_piphot_undet/N_piphot_det)*histoweight);

                                                        if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][0]->Fill( ProtonMag, -(N_piphot_undet/N_piphot_det)*histoweight); }
                                                        if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][1]->Fill( ProtonMag, -(N_piphot_undet/N_piphot_det)*histoweight); }
						}
					}

					h2_Electron_Theta_Phi->Fill( el_phi_mod, V3_el.Theta()*180./TMath::Pi(), -(N_piphot_undet/N_piphot_det)*histoweight);
                                        h1_InteractionBreakDown_NoQ4Weight_InSector_el_theta[Interaction][ElectronSector]->Fill( V3_el.Theta()*180./TMath::Pi(), -(N_piphot_undet/N_piphot_det)*histoweight);
					h1_InteractionBreakDown_NoQ4Weight_InSector_prot_theta[Interaction][ProtonSector]->Fill( ProtonTheta_Deg, -(N_piphot_undet/N_piphot_det)*histoweight); // smithja: might have to adjust ProtonSector
					if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][0]->Fill( ProtonTheta_Deg, -(N_piphot_undet/N_piphot_det)*histoweight); }
                                        if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][1]->Fill( ProtonTheta_Deg, -(N_piphot_undet/N_piphot_det)*histoweight); }

                                        double prot_phi_plot = ProtonPhi_Deg; // smithja: alias	ProtonPhi_Deg for plotting purposes in h2_prot_theta_phi
                                        if (prot_phi_plot < 0.)	{ prot_phi_plot += 360.; } // smithja: this statement puts the proton phi in the correct range for plotting; a similar statement making	sure ProtonPhi_Deg is below 360
                                                                                           //          degrees is included towards the top of this code, so the only modification to prot_phi_plot needed is what's shown in this statement
					h2_prot_theta_phi->Fill( prot_phi_plot, ProtonTheta_Deg, -(N_piphot_undet/N_piphot_det)*histoweight);						
					PassCounter3 ++;
					
                                        // smithja: These TH2s are used to investigate correlations between proton momtentum and other variables.
                                        h2_prot_mom_el_phi->Fill( el_phi_mod, ProtonMag, -(N_piphot_undet/N_piphot_det)*histoweight);
                                        h2_prot_mom_el_theta->Fill( V3_el.Theta()*180./TMath::Pi(), ProtonMag, -(N_piphot_undet/N_piphot_det)*histoweight);
                                        h2_prot_mom_el_mom->Fill( el_momentum, ProtonMag, -(N_piphot_undet/N_piphot_det)*histoweight);
                                        h2_prot_mom_phi->Fill( prot_phi_plot, ProtonMag, -(N_piphot_undet/N_piphot_det)*histoweight);
                                        h2_prot_mom_theta->Fill( ProtonTheta_Deg, ProtonMag, -(N_piphot_undet/N_piphot_det)*histoweight);

					h1_el_mom_corr->Fill(V4_el.Rho(),-(N_piphot_undet/N_piphot_det)*histoweight);
					//h1_prot_mom->Fill( ProtonMag, -(N_piphot_undet/N_piphot_det)*histoweight);
					h1_histoweight->Fill(-(N_piphot_undet/N_piphot_det)*histoweight);
					h1_histoweight2->Fill(-(N_piphot_undet/N_piphot_det));
					//if (-(N_piphot_undet/N_piphot_det)*histoweight == 0) {h1_prot_mom->Fill( ProtonMag, -(N_piphot_undet/N_piphot_det)*histoweight);}
					//if (-(N_piphot_undet/N_piphot_det)*histoweight != 0) {h1_prot_mom->Fill( ProtonMag, 1/(-(N_piphot_undet/N_piphot_det)*histoweight));}

					h1_el_prot_phi_diff->Fill(el_phi_mod-ProtonPhi_Deg,-(N_piphot_undet/N_piphot_det)*histoweight);
					h2_el_prot_theta->Fill(el_theta,ProtonTheta_Deg,-(N_piphot_undet/N_piphot_det)*histoweight);
					h2_el_prot_phi->Fill(el_phi_mod,ProtonPhi_Deg,-(N_piphot_undet/N_piphot_det)*histoweight);
					h2_el_prot_mom->Fill(V4_el.Rho(), ProtonMag, -(N_piphot_undet/N_piphot_det)*histoweight);

					double LocalWeight = -(N_piphot_undet/N_piphot_det)*histoweight;

					h2_Electron_Theta_Momentum->Fill(V4_el.Rho(),V3_el.Theta()*180./TMath::Pi(),-(N_piphot_undet/N_piphot_det)*histoweight);
					h2_Proton_Theta_Momentum->Fill( ProtonMag, V3_prot_corr.Theta()*180./TMath::Pi(),-(N_piphot_undet/N_piphot_det)*histoweight);
					h1_prot_theta->Fill(V3_prot_corr.Theta()*180./TMath::Pi(),-(N_piphot_undet/N_piphot_det)*histoweight);
					h1_prot_theta_noweight->Fill(V3_prot_corr.Theta()*180./TMath::Pi());
					h1_prot_costheta->Fill(V3_prot_corr.CosTheta(),-(N_piphot_undet/N_piphot_det)*histoweight);


					// -----------------------------------------------------------------------------------------------
					// apapadop: Reconstruct xB, W, Q2 using Ecal instead of Etrue

					CalKineVars = CalculateCalKineVars(E_tot,V4_el);

					// Fill plots based on underlying interactions

					Q2_BreakDown[0]->Fill(reco_Q2,LocalWeight);
					Nu_BreakDown[0]->Fill(nu,LocalWeight);
					Pe_BreakDown[0]->Fill(V4_el.Rho(),LocalWeight);

					// ---------------------------------------------------------------------------------------------------------------------

					double PTmiss = p_perp_tot;
					double Ecal = E_tot;

					double EcalReso = (Ecal-en_beam_Ecal[fbeam_en])/en_beam_Ecal[fbeam_en];

					// ---------------------------------------------------------------------------------------------------------------------

					//h1_EePrime_InCosThetaEPrimeSlices[CosThetaEPrimeSlice]->Fill(V4_el.E(),LocalWeight);							

					if (fchoice > 0) {

						Q2_BreakDown[Interaction]->Fill(reco_Q2,LocalWeight);
						Nu_BreakDown[Interaction]->Fill(nu,LocalWeight);
						Pe_BreakDown[Interaction]->Fill(V4_el.Rho(),LocalWeight);

					}

					// -----------------------------------------------------------------------------------------------


				} //end of N_piphot_det!=0

			 }//end of 1p 1pi requirement

			//---------------------------------- 1p 2pi   ----------------------------------------------

			if(num_pi_phot == 2) {

				const int N_2pi=2;
				TVector3 V3_2pi_corr[N_2pi],V3_2pi_rot[N_2pi],V3_p_rot;
				double P_1p0pi=0;
				double P_1p1pi[N_2pi]={1};

				double pion_acc_ratio[N_2pi] = {0};

				for (int i = 0; i < num_pi_phot; i++) {

					if (fchoice == 0) { //CLAS data
						V3_2pi_corr[i].SetXYZ( pxf[ind_pi_phot[i]], pyf[ind_pi_phot[i]], pzf[ind_pi_phot[i]]);
						pion_acc_ratio[i] = 1; //Acceptance is 1 for CLAS data
					}

					if (fchoice > 0) { //GENIE data

						V3_2pi_corr[i].SetXYZ(Smeared_Ppi[i]/pf[ind_pi_phot[i]] * pxf[ind_pi_phot[i]],Smeared_Ppi[i]/pf[ind_pi_phot[i]] * pyf[ind_pi_phot[i]],
									Smeared_Ppi[i]/pf[ind_pi_phot[i]] * pzf[ind_pi_phot[i]]);
						double phi_pion = V3_2pi_corr[i].Phi(); //in Radians
						V3_2pi_corr[i].SetPhi(phi_pion + TMath::Pi() ); // Vec.Phi() is between (-180,180)
						phi_pion += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS

						double pion_theta = V3_2pi_corr[i].Theta();
						double pion_mom_corr = V3_2pi_corr[i].Mag();

						if (charge_pi[i] == 1) { //acceptance for pi plus
							 pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, 211, file_acceptance_pip,ApplyAccWeights);
							  if ( fabs(pion_acc_ratio[i]) != pion_acc_ratio[i] ) { continue; }
						}
						else if (charge_pi[i] == -1) {	//acceptance for pi minus. using electron acceptance map

							//pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,ApplyAccWeights);

							// UNTIL AXEL CREATES THE CORRECT PIMINUS MAP, WE SET THE PIMINUS ACCEPTANCE TO BE 1
//							pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,false);
							pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance_pim,true);

							if ( fabs(pion_acc_ratio[i]) != pion_acc_ratio[i] ) { continue; }
						}
						else if (charge_pi[i] == 0) {	//acceptance for photon/pi0 is 1 for now F.H. 09/24/19
							 pion_acc_ratio[i] = 1;
						}
						else { std::cout << "WARNING: 1 Proton 2 Pion Events. pion_acc_ratio is still 0. Continue with next event " << std::endl;  continue; }
					}

				} //end loop over num_pi_phot

				rotation->prot1_pi2_rot_func(V3_prot_uncorr,V3_2pi_corr,charge_pi,&P_1p0pi,P_1p1pi);
				//weight_pions is 1 for CLAS data
				double weight_pions = pion_acc_ratio[0] * pion_acc_ratio[1];
				//histoweight is 1/Mott_cross_sec for CLAS data
				double histoweight = weight_pions * p_acc_ratio * e_acc_ratio * wght/Mott_cross_sec; 
				//1proton, 2 Pion, 1 electron acceptance, GENIE weight and Mott
				//---------------------------------- 1p 2pi->1p1pi   ----------------------------------------------

				for(int z = 0; z < N_2pi; z++){  //to consider 2 diff. 1pi states

					h2_pperp_W->Fill(W_var,p_perp_tot,P_1p1pi[z]*histoweight);
					h1_theta0->Fill((V4_beam.Vect()).Angle(V4_el.Vect()+V3_prot_uncorr)*TMath::RadToDeg(),P_1p1pi[z]*histoweight);

					double ProtonPhi_Deg = V3_prot_corr.Phi() *180. / TMath::Pi() + 30;
					//double ProtonPhi_Deg = V3_prot_corr.Phi() *180. / TMath::Pi() + 180 + 30; // smithja:	commented out on 9/22/2021; 180-degree shift not needed	here
					if (ProtonPhi_Deg > 360.) { ProtonPhi_Deg -= 360.; } 
                                        if (ProtonPhi_Deg < 0.) { ProtonPhi_Deg += 360.; }
                                        int ProtonSector = ProtonPhi_Deg / 60;
					double ProtonTheta_Deg = V3_prot_corr.Theta() *180. / TMath::Pi();
					double ProtonMag = V3_prot_corr.Mag();
					double ProtonTK = sqrt(ProtonMag*ProtonMag + m_prot*m_prot) - m_prot;
					double Em = (nu - ProtonTK);
					TVector3 pmiss_vec =  V3_rot_q - V3_prot_corr;				
					double pmiss = pmiss_vec.Mag();
					double ThetaPQ = V3_rot_q.Angle(V3_prot_corr) * 180. / TMath::Pi();                                 
       
					if (Em > Em_ub)  {continue;}

					if(ThetaPQ > theta_pq_cut) { continue; }//Looking at ThetaPQ cut
				
					if (fApplyThetaSliceProt) {  // hard coded range for now
						if ( ProtonTheta_Deg < t_thetaProt_lb->GetVal()) { continue; }
						if ( ProtonTheta_Deg > t_thetaProt_ub->GetVal()) { continue; }
					}
			
                    if (fApplyPhiOpeningAngleProt) {
                            if ( TMath::Abs(ProtonPhi_Deg - 30) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 90) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 150) > PhiOpeningAngleProt \
                                && TMath::Abs(ProtonPhi_Deg - 210) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 270) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 330) > PhiOpeningAngleProt ) {
                                    continue;
                            }
                    }

                    if (fApplyPhiSliceProt_Sectors && ProtonSector != (ElectronSector + 3)%6) { continue; }
                    if (fApplyProtMomCut && (ProtonMag < t_ProtMom_lb->GetVal() || ProtonMag > t_ProtMom_ub->GetVal())) { continue; }

					h2_el_CosTheta_E->Fill(V3_el.CosTheta(),V4_el.E(),P_1p1pi[z]*histoweight);


					if (el_theta >= t_thetaEl_lb->GetVal() && el_theta <= t_thetaEl_ub->GetVal()) { // smithja: there looks to be continue statements above that already necessitate this condition
						if (p_perp_tot < PtMax && Interaction > -1) {h1_InteractionBreakdown_Omega_NoQ4Weight_InSector_el_mom_ptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4); } 
                                                if (Interaction > -1) {
							h1_InteractionBreakDown_Omega_NoQ4Weight_InSector_el_mom_noptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4);
							h1_InteractionBreakDown_Omega_NoQ4Weight_Insector_prot_mom_QE[Interaction][ProtonSector]->Fill( ProtonMag, P_1p1pi[z]*histoweight);

							h1_InteractionBreakDown_InSector_Em[Interaction][ProtonSector]->Fill(Em, P_1p1pi[z]*histoweight);
								h1_InteractionBreakDown_InSector_Pm[Interaction][ProtonSector]->Fill(pmiss, P_1p1pi[z]*histoweight);
								h2_InteractionBreakDown_InSector_EmPm[Interaction][ProtonSector]->Fill(Em,pmiss, P_1p1pi[z]*histoweight);
								h1_InteractionBreakDown_ThetaPQ[Interaction][ProtonSector]->Fill(ThetaPQ, P_1p1pi[z]*histoweight);
							h1_InteractionBreakDown_InSector_el_mom_Emcut[Interaction][ProtonSector]->Fill(el_momentum, P_1p1pi[z]*histoweight);

                                                		if(hitnuc == 2212) h1_hit_nuc_pass->Fill(1,P_1p1pi[z]*histoweight);
	                                                        if(hitnuc == 2112) h1_hit_nuc_pass->Fill(2,P_1p1pi[z]*histoweight);

						        if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][0]->Fill( ProtonMag, P_1p1pi[z]*histoweight); }
                                                        if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][1]->Fill( ProtonMag, P_1p1pi[z]*histoweight); }
						}
					}

					h2_Electron_Theta_Phi->Fill( el_phi_mod, V3_el.Theta()*180./TMath::Pi(), P_1p1pi[z]*histoweight);
                                        h1_InteractionBreakDown_NoQ4Weight_InSector_el_theta[Interaction][ElectronSector]->Fill( V3_el.Theta()*180./TMath::Pi(), P_1p1pi[z]*histoweight);
					h1_InteractionBreakDown_NoQ4Weight_InSector_prot_theta[Interaction][ProtonSector]->Fill( ProtonTheta_Deg, P_1p1pi[z]*histoweight); // smithja: might have to adjust ProtonSector
					if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][0]->Fill( ProtonTheta_Deg, P_1p1pi[z]*histoweight); }
                                        if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][1]->Fill( ProtonTheta_Deg, P_1p1pi[z]*histoweight); }

                                        double prot_phi_plot = ProtonPhi_Deg; // smithja: alias	ProtonPhi_Deg for plotting purposes in h2_prot_theta_phi
                                        if (prot_phi_plot < 0.)	{ prot_phi_plot += 360.; } // smithja: this statement puts the proton phi in the correct range for plotting; a similar statement making	sure ProtonPhi_Deg is below 360
                                                                                           //          degrees is included towards the top of this code, so the only modification to prot_phi_plot needed is what's shown in this statement
					h2_prot_theta_phi->Fill( prot_phi_plot, ProtonTheta_Deg, P_1p1pi[z]*histoweight);						
					PassCounter3 ++;
					
                                        // smithja: These TH2s are used to investigate correlations between proton momtentum and other variables.
                                        h2_prot_mom_el_phi->Fill( el_phi_mod, ProtonMag, P_1p1pi[z]*histoweight);
                                        h2_prot_mom_el_theta->Fill( V3_el.Theta()*180./TMath::Pi(), ProtonMag, P_1p1pi[z]*histoweight);
                                        h2_prot_mom_el_mom->Fill( el_momentum, ProtonMag, P_1p1pi[z]*histoweight);
                                        h2_prot_mom_phi->Fill( prot_phi_plot, ProtonMag, P_1p1pi[z]*histoweight);
                                        h2_prot_mom_theta->Fill( ProtonTheta_Deg, ProtonMag, P_1p1pi[z]*histoweight);

					h1_el_mom_corr->Fill(V4_el.Rho(),P_1p1pi[z]*histoweight);
					//h1_prot_mom->Fill( ProtonMag, P_1p1pi[z]*histoweight);
					h1_histoweight->Fill(P_1p1pi[z]*histoweight);
					h1_histoweight2->Fill(P_1p1pi[z]);
					//if (P_1p1pi[z]*histoweight == 0) {h1_prot_mom->Fill( ProtonMag, P_1p1pi[z]*histoweight);}
					//if (P_1p1pi[z]*histoweight != 0) {h1_prot_mom->Fill( ProtonMag, 1/(P_1p1pi[z]*histoweight));}

					h1_el_prot_phi_diff->Fill(el_phi_mod-ProtonPhi_Deg,P_1p1pi[z]*histoweight);
					h2_el_prot_theta->Fill(el_theta,ProtonTheta_Deg,P_1p1pi[z]*histoweight);
					h2_el_prot_phi->Fill(el_phi_mod,ProtonPhi_Deg,P_1p1pi[z]*histoweight);
					h2_el_prot_mom->Fill(V4_el.Rho(), ProtonMag, P_1p1pi[z]*histoweight);

					double LocalWeight = P_1p1pi[z]*histoweight;

					h2_Electron_Theta_Momentum->Fill(V4_el.Rho(),V3_el.Theta()*180./TMath::Pi(),P_1p1pi[z]*histoweight);
					h2_Proton_Theta_Momentum->Fill( ProtonMag, V3_prot_corr.Theta()*180./TMath::Pi(),P_1p1pi[z]*histoweight);
					h1_prot_theta->Fill(V3_prot_corr.Theta()*180./TMath::Pi(),P_1p1pi[z]*histoweight);
					h1_prot_theta_noweight->Fill(V3_prot_corr.Theta()*180./TMath::Pi());
					h1_prot_costheta->Fill(V3_prot_corr.CosTheta(),P_1p1pi[z]*histoweight);


					// -----------------------------------------------------------------------------------------------
					// apapadop: Reconstruct xB, W, Q2 using Ecal instead of Etrue

					CalKineVars = CalculateCalKineVars(E_tot,V4_el);

					// Fill plots based on underlying interactions

					Q2_BreakDown[0]->Fill(reco_Q2,LocalWeight);
					Nu_BreakDown[0]->Fill(nu,LocalWeight);
					Pe_BreakDown[0]->Fill(V4_el.Rho(),LocalWeight);

					// ---------------------------------------------------------------------------------------------------------------------

					double PTmiss = p_perp_tot;
					double Ecal = E_tot;

					double EcalReso = (Ecal-en_beam_Ecal[fbeam_en])/en_beam_Ecal[fbeam_en];

					// ---------------------------------------------------------------------------------------------------------------------	

					//h1_EePrime_InCosThetaEPrimeSlices[CosThetaEPrimeSlice]->Fill(V4_el.E(),LocalWeight);						

					if (fchoice > 0) {

						Q2_BreakDown[Interaction]->Fill(reco_Q2,LocalWeight);
						Nu_BreakDown[Interaction]->Fill(nu,LocalWeight);
						Pe_BreakDown[Interaction]->Fill(V4_el.Rho(),LocalWeight);

					}

					// -----------------------------------------------------------------------------------------------

				} //end loop over N_2pi

				//---------------------------------- 1p 2pi->1p0pi   ----------------------------------------------

				h2_pperp_W->Fill(W_var,p_perp_tot,-P_1p0pi*histoweight);
				h1_theta0->Fill((V4_beam.Vect()).Angle(V4_el.Vect()+V3_prot_uncorr)*TMath::RadToDeg(),-P_1p0pi*histoweight);

				double ProtonPhi_Deg = V3_prot_corr.Phi() *180. / TMath::Pi() + 30;
				//double ProtonPhi_Deg = V3_prot_corr.Phi() *180. / TMath::Pi() + 180 + 30; // smithja:	commented out on 9/22/2021; 180-degree shift not needed	here
				if (ProtonPhi_Deg > 360.) { ProtonPhi_Deg -= 360.; } 
                                if (ProtonPhi_Deg < 0.) { ProtonPhi_Deg += 360.; }
                                int ProtonSector = ProtonPhi_Deg / 60;
				double ProtonTheta_Deg = V3_prot_corr.Theta() *180. / TMath::Pi();
				double ProtonMag = V3_prot_corr.Mag();
				double ProtonTK = sqrt(ProtonMag*ProtonMag + m_prot*m_prot) - m_prot;
				double Em = (nu - ProtonTK);
				TVector3 pmiss_vec =  V3_rot_q - V3_prot_corr;				
				double pmiss = pmiss_vec.Mag();
				double ThetaPQ = V3_rot_q.Angle(V3_prot_corr) * 180. / TMath::Pi();
	
                if (Em > Em_ub)  {continue;}

				if(ThetaPQ > theta_pq_cut) { continue; }//Looking at ThetaPQ cut
				
				if (fApplyThetaSliceProt) {  // hard coded range for now
					if ( ProtonTheta_Deg < t_thetaProt_lb->GetVal()) { continue; }
					if ( ProtonTheta_Deg > t_thetaProt_ub->GetVal()) { continue; }
				}

                if (fApplyPhiOpeningAngleProt) {
                        if ( TMath::Abs(ProtonPhi_Deg - 30) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 90) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 150) > PhiOpeningAngleProt \
                            && TMath::Abs(ProtonPhi_Deg - 210) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 270) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 330) > PhiOpeningAngleProt ) {
                                continue;
                        }
                }

                if (fApplyPhiSliceProt_Sectors && ProtonSector != (ElectronSector + 3)%6) { continue; }
                if (fApplyProtMomCut && (ProtonMag < t_ProtMom_lb->GetVal() || ProtonMag > t_ProtMom_ub->GetVal())) { continue; }

				h2_el_CosTheta_E->Fill(V3_el.CosTheta(),V4_el.E(),-P_1p0pi*histoweight);


				if (el_theta >= t_thetaEl_lb->GetVal() && el_theta <= t_thetaEl_ub->GetVal()) { // smithja: there looks to be continue statements above that already necessitate this condition
					if (p_perp_tot < PtMax && Interaction > -1) {h1_InteractionBreakdown_Omega_NoQ4Weight_InSector_el_mom_ptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4); }
                                        if (Interaction > -1) {
						h1_InteractionBreakDown_Omega_NoQ4Weight_InSector_el_mom_noptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4);
						h1_InteractionBreakDown_Omega_NoQ4Weight_Insector_prot_mom_QE[Interaction][ProtonSector]->Fill( ProtonMag, -P_1p0pi*histoweight);
                       					if(hitnuc == 2212) h1_hit_nuc_pass->Fill(1,-P_1p0pi*histoweight);
	                                                        if(hitnuc == 2112) h1_hit_nuc_pass->Fill(2,-P_1p0pi*histoweight);

						h1_InteractionBreakDown_InSector_Em[Interaction][ProtonSector]->Fill(Em, -P_1p0pi*histoweight);
								h1_InteractionBreakDown_InSector_Pm[Interaction][ProtonSector]->Fill(pmiss, -P_1p0pi*histoweight);
								h2_InteractionBreakDown_InSector_EmPm[Interaction][ProtonSector]->Fill(Em,pmiss, -P_1p0pi*histoweight);
								h1_InteractionBreakDown_ThetaPQ[Interaction][ProtonSector]->Fill(ThetaPQ, -P_1p0pi*histoweight);
							h1_InteractionBreakDown_InSector_el_mom_Emcut[Interaction][ProtonSector]->Fill(el_momentum, -P_1p0pi*histoweight);

                                                if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][0]->Fill( ProtonMag, -P_1p0pi*histoweight); }
                                                if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][1]->Fill( ProtonMag, -P_1p0pi*histoweight); }
					}
				}

				h2_Electron_Theta_Phi->Fill( el_phi_mod, V3_el.Theta()*180./TMath::Pi(), -P_1p0pi*histoweight);
                                h1_InteractionBreakDown_NoQ4Weight_InSector_el_theta[Interaction][ElectronSector]->Fill( V3_el.Theta()*180./TMath::Pi(), -P_1p0pi*histoweight);
				h1_InteractionBreakDown_NoQ4Weight_InSector_prot_theta[Interaction][ProtonSector]->Fill( ProtonTheta_Deg, -P_1p0pi*histoweight); // smithja: might have to adjust ProtonSector
				if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][0]->Fill( ProtonTheta_Deg, -P_1p0pi*histoweight); }
                                if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][1]->Fill( ProtonTheta_Deg, -P_1p0pi*histoweight); }

                                double prot_phi_plot = ProtonPhi_Deg; // smithja: alias	ProtonPhi_Deg for plotting purposes in h2_prot_theta_phi
                                if (prot_phi_plot < 0.)	{ prot_phi_plot += 360.; } // smithja: this statement puts the proton phi in the correct range for plotting; a similar statement making	sure ProtonPhi_Deg is below 360
                                                                                   //          degrees is included towards the top of this code, so the only modification to prot_phi_plot needed is what's shown in this statement
				h2_prot_theta_phi->Fill( prot_phi_plot, ProtonTheta_Deg, -P_1p0pi*histoweight);					
				PassCounter3 ++;
				
                                // smithja: These TH2s are used to investigate correlations between proton momtentum and other variables.
                                h2_prot_mom_el_phi->Fill( el_phi_mod, ProtonMag, -P_1p0pi*histoweight);
                                h2_prot_mom_el_theta->Fill( V3_el.Theta()*180./TMath::Pi(), ProtonMag, -P_1p0pi*histoweight);
                                h2_prot_mom_el_mom->Fill( el_momentum, ProtonMag, -P_1p0pi*histoweight);
                                h2_prot_mom_phi->Fill( prot_phi_plot, ProtonMag, -P_1p0pi*histoweight);
                                h2_prot_mom_theta->Fill( ProtonTheta_Deg, ProtonMag, -P_1p0pi*histoweight);

				h1_el_mom_corr->Fill(V4_el.Rho(),-P_1p0pi*histoweight);
				//h1_prot_mom->Fill( ProtonMag, -P_1p0pi*histoweight);
				h1_histoweight->Fill(-P_1p0pi*histoweight);
				h1_histoweight2->Fill(-P_1p0pi);
				//if (-P_1p0pi*histoweight == 0) {h1_prot_mom->Fill( ProtonMag, -P_1p0pi*histoweight);}
				//if (-P_1p0pi*histoweight != 0) {h1_prot_mom->Fill( ProtonMag, 1/(-P_1p0pi*histoweight));}

				h1_el_prot_phi_diff->Fill(el_phi_mod-ProtonPhi_Deg,-P_1p0pi*histoweight);
				h2_el_prot_theta->Fill(el_theta,ProtonTheta_Deg,-P_1p0pi*histoweight);
				h2_el_prot_phi->Fill(el_phi_mod,ProtonPhi_Deg,-P_1p0pi*histoweight);
				h2_el_prot_mom->Fill(V4_el.Rho(), ProtonMag, -P_1p0pi*histoweight);

				double LocalWeight = -P_1p0pi*histoweight;

				h2_Electron_Theta_Momentum->Fill(V4_el.Rho(),V3_el.Theta()*180./TMath::Pi(),-P_1p0pi*histoweight);
				h2_Proton_Theta_Momentum->Fill( ProtonMag, V3_prot_corr.Theta()*180./TMath::Pi(),-P_1p0pi*histoweight);
				h1_prot_theta->Fill(V3_prot_corr.Theta()*180./TMath::Pi(),-P_1p0pi*histoweight);
				h1_prot_theta_noweight->Fill(V3_prot_corr.Theta()*180./TMath::Pi());
				h1_prot_costheta->Fill(V3_prot_corr.CosTheta(),-P_1p0pi*histoweight);
				

				// -----------------------------------------------------------------------------------------------
				// apapadop: Reconstruct xB, W, Q2 using Ecal instead of Etrue

				CalKineVars = CalculateCalKineVars(E_tot,V4_el);

				// Fill plots based on underlying interactions

				Q2_BreakDown[0]->Fill(reco_Q2,LocalWeight);
				Nu_BreakDown[0]->Fill(nu,LocalWeight);
				Pe_BreakDown[0]->Fill(V4_el.Rho(),LocalWeight);

				// ---------------------------------------------------------------------------------------------------------------------

				double PTmiss = p_perp_tot;
				double Ecal = E_tot;

				double EcalReso = (Ecal-en_beam_Ecal[fbeam_en])/en_beam_Ecal[fbeam_en];

				// ---------------------------------------------------------------------------------------------------------------------	

				//h1_EePrime_InCosThetaEPrimeSlices[CosThetaEPrimeSlice]->Fill(V4_el.E(),LocalWeight);								

				if (fchoice > 0) {

					Q2_BreakDown[Interaction]->Fill(reco_Q2,LocalWeight);
					Nu_BreakDown[Interaction]->Fill(nu,LocalWeight);
					Pe_BreakDown[Interaction]->Fill(V4_el.Rho(),LocalWeight);

				}

				// -----------------------------------------------------------------------------------------------


			}//1p 2pi statetment ends

			//---------------------------------- 1p 3pi   ----------------------------------------------

			if(num_pi_phot == 3){

				const int N_3pi=3;
				TVector3 V3_3pi_corr[N_3pi],V3_3pi_rot[N_3pi],V3_p_rot;
				double P_1p3pi = 0;
				double pion_acc_ratio[N_3pi] = {1};

				for (int i = 0; i < num_pi_phot; i++) {

					if (fchoice == 0) { //CLAS data
						V3_3pi_corr[i].SetXYZ( pxf[ind_pi_phot[i]], pyf[ind_pi_phot[i]], pzf[ind_pi_phot[i]]);
						pion_acc_ratio[i] = 1; //Acceptance is 1 for CLAS data
					}

					if (fchoice > 0) { //GENIE data
						pion_acc_ratio[i] = 0; //Reset to 0 just to be sure
						V3_3pi_corr[i].SetXYZ(Smeared_Ppi[i]/pf[ind_pi_phot[i]] * pxf[ind_pi_phot[i]],Smeared_Pp[i]/pf[ind_pi_phot[i]] * pyf[ind_pi_phot[i]],
									Smeared_Pp[i]/pf[ind_pi_phot[i]] * pzf[ind_pi_phot[i]]);
						double phi_pion = V3_3pi_corr[i].Phi(); //in Radians
						V3_3pi_corr[i].SetPhi(phi_pion + TMath::Pi() ); // Vec.Phi() is between (-180,180)
						phi_pion += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS

						double pion_theta = V3_3pi_corr[i].Theta();
						double pion_mom_corr = V3_3pi_corr[i].Mag();

						if (charge_pi[i] == 1) { //acceptance for pi plus
							pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, 211, file_acceptance_pip,ApplyAccWeights);
							if ( fabs(pion_acc_ratio[i]) != pion_acc_ratio[i] ) { continue; }
						}
						else if (charge_pi[i] == -1) {	//acceptance for pi minus. using electron acceptance map

//							pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,ApplyAccWeights);

							// UNTIL AXEL CREATES THE CORRECT PIMINUS MAP, WE SET THE PIMINUS ACCEPTANCE TO BE 1
//							pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance,false);
							pion_acc_ratio[i] = acceptance_c(pion_mom_corr, cos(pion_theta), phi_pion, -211, file_acceptance_pim,true);

							if ( fabs(pion_acc_ratio[i]) != pion_acc_ratio[i] ) { continue; }
						}
						else if (charge_pi[i] == 0) {	//acceptance for photon/pi0 is 1 for now F.H. 09/24/19
							pion_acc_ratio[i] = 1;
						}
						else { std::cout << "WARNING: 3 Pion Events. pion_acc_ratio is still 0. Continue with next event " << std::endl;  continue; }
					}

				} //end loop over num_pi_phot

				rotation->prot1_pi3_rot_func(V3_prot_uncorr, V3_3pi_corr, charge_pi, &P_1p3pi);
		 		//weight_pions is 1 for CLAS data
				double weight_pions = pion_acc_ratio[0] * pion_acc_ratio[1] * pion_acc_ratio[2];
				//histoweight is 1/Mott_cross_sec for CLAS data
				double histoweight = weight_pions * p_acc_ratio * e_acc_ratio * wght/Mott_cross_sec; 
				//1proton, 3 Pion, 1 electron acceptance, GENIE weight and Mott

				//---------------------------------- 1p 3pi->1p 0pi  total ?? F.H. 08/13/19 check logic here compared to 1p 2pi case ----------------------------

				h2_pperp_W->Fill(W_var,p_perp_tot,P_1p3pi*histoweight);
				h1_theta0->Fill((V4_beam.Vect()).Angle(V4_el.Vect()+V3_prot_uncorr)*TMath::RadToDeg(),P_1p3pi*histoweight);

				
				double ProtonPhi_Deg = V3_prot_corr.Phi() *180. / TMath::Pi() + 30;
				//double ProtonPhi_Deg = V3_prot_corr.Phi() *180. / TMath::Pi() + 180 + 30; // smithja:	commented out on 9/22/2021; 180-degree shift not needed	here
				if (ProtonPhi_Deg > 360.) { ProtonPhi_Deg -= 360.; } 
                                if (ProtonPhi_Deg < 0.) { ProtonPhi_Deg += 360.; }
                                int ProtonSector = ProtonPhi_Deg / 60;
				double ProtonTheta_Deg = V3_prot_corr.Theta() *180. / TMath::Pi();
				double ProtonMag = V3_prot_corr.Mag();
				double ProtonTK = sqrt(ProtonMag*ProtonMag + m_prot*m_prot) - m_prot;
				double Em = (nu - ProtonTK);
				TVector3 pmiss_vec =  V3_rot_q - V3_prot_corr;				
				double pmiss = pmiss_vec.Mag();
				double ThetaPQ = V3_rot_q.Angle(V3_prot_corr) * 180. / TMath::Pi();
					
                if (Em > Em_ub)  {continue;}

				if(ThetaPQ > theta_pq_cut) { continue; }//Looking at ThetaPQ cut
				
				if (fApplyThetaSliceProt) {  // hard coded range for now
					if ( ProtonTheta_Deg < t_thetaProt_lb->GetVal()) { continue; }
					if ( ProtonTheta_Deg > t_thetaProt_ub->GetVal()) { continue; }
				}
			
                if (fApplyPhiOpeningAngleProt) {
                        if ( TMath::Abs(ProtonPhi_Deg - 30) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 90) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 150) > PhiOpeningAngleProt \
                            && TMath::Abs(ProtonPhi_Deg - 210) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 270) > PhiOpeningAngleProt && TMath::Abs(ProtonPhi_Deg - 330) > PhiOpeningAngleProt ) {
                                continue;
                        }
                }

                if (fApplyPhiSliceProt_Sectors && ProtonSector != (ElectronSector + 3)%6) { continue; }
				if (fApplyProtMomCut && (ProtonMag < t_ProtMom_lb->GetVal() || ProtonMag > t_ProtMom_ub->GetVal())) { continue; }

				h2_el_CosTheta_E->Fill(V3_el.CosTheta(),V4_el.E(),P_1p3pi*histoweight);

				if (el_theta >= t_thetaEl_lb->GetVal() && el_theta <= t_thetaEl_ub->GetVal()) { // smithja: there looks to be continue statements above that already necessitate this condition
					if (p_perp_tot < PtMax && Interaction > -1) {h1_InteractionBreakdown_Omega_NoQ4Weight_InSector_el_mom_ptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4); }
                                        if (Interaction > -1) {
						h1_InteractionBreakDown_Omega_NoQ4Weight_InSector_el_mom_noptcut[Interaction][ElectronSector]->Fill(el_momentum,WeightIncl/Q4);
						h1_InteractionBreakDown_Omega_NoQ4Weight_Insector_prot_mom_QE[Interaction][ProtonSector]->Fill( ProtonMag, P_1p3pi*histoweight);

                        h1_InteractionBreakDown_InSector_Em[Interaction][ProtonSector]->Fill(Em, P_1p3pi*histoweight);
								h1_InteractionBreakDown_InSector_Pm[Interaction][ProtonSector]->Fill(pmiss, P_1p3pi*histoweight);
								h2_InteractionBreakDown_InSector_EmPm[Interaction][ProtonSector]->Fill(Em,pmiss, P_1p3pi*histoweight);
								h1_InteractionBreakDown_ThetaPQ[Interaction][ProtonSector]->Fill(ThetaPQ, P_1p3pi*histoweight);
							h1_InteractionBreakDown_InSector_el_mom_Emcut[Interaction][ProtonSector]->Fill(el_momentum, P_1p3pi*histoweight);

                                        		if(hitnuc == 2212) h1_hit_nuc_pass->Fill(1,P_1p3pi*histoweight);
	                                                        if(hitnuc == 2112) h1_hit_nuc_pass->Fill(2,P_1p3pi*histoweight);
					        if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][0]->Fill( ProtonMag, P_1p3pi*histoweight); }
                                                if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_mom_QE[Interaction][ProtonSector][1]->Fill( ProtonMag, P_1p3pi*histoweight); }
					}
				}

				h2_Electron_Theta_Phi->Fill( el_phi_mod, V3_el.Theta()*180./TMath::Pi(), P_1p3pi*histoweight);
                                h1_InteractionBreakDown_NoQ4Weight_InSector_el_theta[Interaction][ElectronSector]->Fill( V3_el.Theta()*180./TMath::Pi(), P_1p3pi*histoweight);
				h1_InteractionBreakDown_NoQ4Weight_InSector_prot_theta[Interaction][ProtonSector]->Fill( ProtonTheta_Deg, P_1p3pi*histoweight); // smithja: might have to adjust ProtonSector
				if (resc_val > 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][0]->Fill( ProtonTheta_Deg, P_1p3pi*histoweight); }
                                if (resc_val == 1) { h1_InteractionBreakDown_NoQ4Weight_InSector_isFSI_prot_theta[Interaction][ProtonSector][1]->Fill( ProtonTheta_Deg, P_1p3pi*histoweight); }

                                double prot_phi_plot = ProtonPhi_Deg; // smithja: alias	ProtonPhi_Deg for plotting purposes in h2_prot_theta_phi
                                if (prot_phi_plot < 0.)	{ prot_phi_plot += 360.; } // smithja: this statement puts the proton phi in the correct range for plotting; a similar statement making	sure ProtonPhi_Deg is below 360
                                                                                   //          degrees is included towards the top of this code, so the only modification to prot_phi_plot needed is what's shown in this statement
				h2_prot_theta_phi->Fill( prot_phi_plot, ProtonTheta_Deg, P_1p3pi*histoweight);					
				PassCounter3 ++;
				
                                // smithja: These TH2s are used to investigate correlations between proton momtentum and other variables.
                                h2_prot_mom_el_phi->Fill( el_phi_mod, ProtonMag, P_1p3pi*histoweight);
                                h2_prot_mom_el_theta->Fill( V3_el.Theta()*180./TMath::Pi(), ProtonMag, P_1p3pi*histoweight);
                                h2_prot_mom_el_mom->Fill( el_momentum, ProtonMag, P_1p3pi*histoweight);
                                h2_prot_mom_phi->Fill( prot_phi_plot, ProtonMag, P_1p3pi*histoweight);
                                h2_prot_mom_theta->Fill( ProtonTheta_Deg, ProtonMag, P_1p3pi*histoweight);

				h1_el_mom_corr->Fill(V4_el.Rho(),P_1p3pi*histoweight);
				//h1_prot_mom->Fill( ProtonMag, P_1p3pi*histoweight);
				h1_histoweight->Fill(P_1p3pi*histoweight);
				h1_histoweight2->Fill(P_1p3pi);
				//if (P_1p3pi*histoweight == 0) {h1_prot_mom->Fill( ProtonMag, P_1p3pi*histoweight);}
				//if (P_1p3pi*histoweight != 0) {h1_prot_mom->Fill( ProtonMag, 1/(P_1p3pi*histoweight));}

				h1_el_prot_phi_diff->Fill(el_phi_mod-ProtonPhi_Deg,P_1p3pi*histoweight);
				h2_el_prot_theta->Fill(el_theta,ProtonTheta_Deg,P_1p3pi*histoweight);
				h2_el_prot_phi->Fill(el_phi_mod,ProtonPhi_Deg,P_1p3pi*histoweight);
				h2_el_prot_phi->Fill(V4_el.Rho(), ProtonMag, P_1p3pi*histoweight);

				double LocalWeight = P_1p3pi*histoweight;

				h2_Electron_Theta_Momentum->Fill(V4_el.Rho(),V3_el.Theta()*180./TMath::Pi(),P_1p3pi*histoweight);
				h2_Proton_Theta_Momentum->Fill( ProtonMag, V3_prot_corr.Theta()*180./TMath::Pi(),P_1p3pi*histoweight);
				h1_prot_theta->Fill(V3_prot_corr.Theta()*180./TMath::Pi(),P_1p3pi*histoweight);
				h1_prot_theta_noweight->Fill(V3_prot_corr.Theta()*180./TMath::Pi());
				h1_prot_costheta->Fill(V3_prot_corr.CosTheta(),P_1p3pi*histoweight);


				// -----------------------------------------------------------------------------------------------
				// apapadop: Reconstruct xB, W, Q2 using Ecal instead of Etrue

				CalKineVars = CalculateCalKineVars(E_tot,V4_el);

				// Fill plots based on underlying interactions

				Q2_BreakDown[0]->Fill(reco_Q2,LocalWeight);
				Nu_BreakDown[0]->Fill(nu,LocalWeight);
				Pe_BreakDown[0]->Fill(V4_el.Rho(),LocalWeight);

				// ---------------------------------------------------------------------------------------------------------------------

				double PTmiss = p_perp_tot;
				double Ecal = E_tot;

				double EcalReso = (Ecal-en_beam_Ecal[fbeam_en])/en_beam_Ecal[fbeam_en];

				// ---------------------------------------------------------------------------------------------------------------------	

				//h1_EePrime_InCosThetaEPrimeSlices[CosThetaEPrimeSlice]->Fill(V4_el.E(),LocalWeight);								

				if (fchoice > 0) {

					Q2_BreakDown[Interaction]->Fill(reco_Q2,LocalWeight);
					Nu_BreakDown[Interaction]->Fill(nu,LocalWeight);
					Pe_BreakDown[Interaction]->Fill(V4_el.Rho(),LocalWeight);	

				}

				// -----------------------------------------------------------------------------------------------

		
			}//end of 1p 3pi requirement

		} // End of 1-proton case

	} //end of event loop (jentry)

	gStyle->SetOptFit(1);

	//------------------------------------fractional energy reconstruction plots --------------------------------------

	gDirectory->Write("hist_Files", TObject::kOverwrite);
	// skim_tree->AutoSave();

	// --------------------------------------------------------------------------------------------------------

	std::cout << std::endl << "-----------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl << "# Processed Events = " << TotalCounter << std::endl;
	std::cout << std::endl << "1e1p0pi Signal # Events = " << SignalEvents << std::endl;
	std::cout << std::endl << "Passing Rate = " << int(double(SignalEvents) / double(TotalCounter)*100.) << " \%"<< std::endl << std::endl;

	std::cout << std::endl << "PassCounter06 = " << PassCounter06 << std::endl;
	std::cout << std::endl << "PassCounter05 = " << PassCounter05 << std::endl;
	std::cout << std::endl << "PassCounter04 = " << PassCounter04 << std::endl;
	std::cout << std::endl << "PassCounter04a = " << PassCounter04a << std::endl;
	std::cout << std::endl << "PassCounter03 = " << PassCounter03 << std::endl;
	std::cout << std::endl << "PassCounter02 = " << PassCounter02 << std::endl;
	std::cout << std::endl << "PassCounter01 = " << PassCounter01 << std::endl;
	std::cout << std::endl << "PassCounter0 = " << PassCounter0 << std::endl;
	std::cout << std::endl << "PassCounter1 = " << PassCounter1 << std::endl;
	std::cout << std::endl << "PassCounter2 = " << PassCounter2 << std::endl;
	std::cout << std::endl << "PassCounter3 = " << PassCounter3 << std::endl;
	if (fchoice > 0) {

		std::cout << std::endl << "QE Fractional Contribution = " << int(double(QESignalEvents) / double(SignalEvents)*100.) << " \%" << std::endl;
		std::cout << std::endl << "MEC Fractional Contribution = " << int(double(MECSignalEvents) / double(SignalEvents)*100.) << " \%" << std::endl;
		std::cout << std::endl << "RES Fractional Contribution = " << int(double(RESSignalEvents) / double(SignalEvents)*100.) << " \%" << std::endl;
		std::cout << std::endl << "DIS Fractional Contribution = " << int(double(DISSignalEvents) / double(SignalEvents)*100.) << " \%" << std::endl;
		std::cout << std::endl << "-----------------------------------------------------------------------------------------------------" << std::endl;

	}
	std::cout << "Number of 2 protons events in same sector = " << two_proton_same_sector << "\n";
	std::cout << "Number of 1 proton 1 pion events in same sectr = " << proton_pion_same_sector << "\n";
	std::cout << "File " << FileName << " created" << std::endl << std::endl;

} // End of program

//End Loop function

// -------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------

double genie_analysis::acceptance_c(double p, double cost, double phi, int particle_id,TFile* file_acceptance, bool ApplyAccWeights) {

	if (ApplyAccWeights) {

		//Redefinition of the phi angle
		//because the acceptance maps are defined between (-30,330)

		// Check that phi is between (0,360)

		//int redef = -30;
		int redef = 0;

		TH3D * acc;
		TH3D * gen;

		acc = (TH3D*)file_acceptance->Get("Accepted Particles");
		gen = (TH3D*)file_acceptance->Get("Generated Particles");

		//map 330 till 360 to [-30:0] for the acceptance map histogram
		if(phi > (2*TMath::Pi() - TMath::Pi()/6.) ) { phi -= 2*TMath::Pi(); }
		//Find number of generated events

		double pbin_gen = gen->GetXaxis()->FindBin(p);
		double tbin_gen = gen->GetYaxis()->FindBin(cost);
		double phibin_gen = gen->GetZaxis()->FindBin(phi*180/TMath::Pi()+redef);
		double num_gen = gen->GetBinContent(pbin_gen, tbin_gen, phibin_gen);

		//Find number of accepted events

		double pbin_acc = acc->GetXaxis()->FindBin(p);
		double tbin_acc = acc->GetYaxis()->FindBin(cost);
		double phibin_acc = acc->GetZaxis()->FindBin(phi*180/TMath::Pi()+redef);
		double num_acc = acc->GetBinContent(pbin_acc, tbin_acc, phibin_acc);

		double acc_ratio = (double)num_acc / (double)num_gen;
		double acc_err = (double)sqrt(acc_ratio*(1-acc_ratio)) / (double)num_gen;


		return acc_ratio;

	}

	else { return 1.; }

}

