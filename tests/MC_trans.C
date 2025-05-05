#define Analysis_cxx
#include "Analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TH2D.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <TGraph.h>
using namespace std;

bool pass_elec_cut(double pl, double theta_l);
bool pass_prot_cut(double pp, double theta_p);

void AnalysisInclusive() {
   Analysis t;
   t.Analyze();
}

void Analysis::Analyze() {

   const std::vector<int> Colors{kBlue+1,kRed-3,kGreen+1,kOrange+1};
   //Total cross sections for each genie simulation 
   double sigma_SF = 3.64031e+07 * 1e-38; // cm^2
   double num_events_SF = 4200000;

   double sigma_susa = 2.1024e+08 * 1e-38; // cm^2
   double num_events_susa = 5e6;//19800000;

   double sigma_G18 = 1.;
   double num_events_G18 = 5e6;

   gStyle->SetOptStat(0);
   gStyle->SetErrorX(0);
   gStyle->SetOptTitle(0);

   std::vector<TH1D*> LFG_hA_2GeV;
   std::vector<TH1D*> LFG_hN_2GeV;
   std::vector<TH1D*> CFG_hA_2GeV;

   double sf_prot_frac = 0;
   double G18_prot_frac = 0;

   //Creating all of gennie histograms
   //sf_hists_2GeV = Loop("/pnfs/genie/scratch/users/nsteinbe/eGENIE_grid/e4v/2261/C12_SF_hN/EmQ2_04-routine_validation_01-eScattering/e4v_2261_hN_SF.gst.root", sigma_SF, num_events_SF, sf_prot_frac); 
   LFG_hA_2GeV = Loop("/pnfs/genie/persistent/users/jtenavid/e4nu_files/GENIE_Files/2024Generation/GEM21_11a_Dipole_LFG_Q2_04_2GeV_eCarbon.gst.root", sigma_G18, num_events_G18, G18_prot_frac); 

   LFG_hN_2GeV = Loop("/pnfs/genie/persistent/users/jtenavid/e4nu_files/GENIE_Files/2024Generation/GEM21_11b_Dipole_LFG_Q2_04_2GeV_eCarbon.gst.root", sigma_G18, num_events_G18, G18_prot_frac);

   CFG_hA_2GeV = Loop("/pnfs/genie/persistent/users/jtenavid/e4nu_files/GENIE_Files/2024Generation/GEM21_11a_Dipole_CFG_Q2_04_2GeV_eCarbon.gst.root", sigma_G18, num_events_G18, G18_prot_frac);

   //G18_hists_1GeV = Loop("/pnfs/genie/persistent/users/apapadop/e4v_G2018/Exclusive/electrons/C12_1161GeV/apapadop_G2018_C12_1161GeV_master.root", sigma_G18, num_events_G18, G18_prot_frac);

   //sf_hists_1GeV = Loop("/pnfs/genie/scratch/users/nsteinbe/eGENIE_grid/e4v/1159/C12/1159_hN_01Q2/EmQ2_01-routine_validation_01-eScattering/e4v_1159_hN_SF.gst.root", sigma_SF, num_events_SF, sf_prot_frac); 


   TCanvas *c1 = new TCanvas("Initial Momentum", "Initial Momentum", 1200, 800);
   //sf_hists_2GeV[1]->SetTitle("SF 2 GeV hN");
   //sf_hists_2GeV[1]->Divide(sf_hists_2GeV[0]);
   //sf_hists_1GeV[1]->SetTitle("SF 1 GeV hN");
   //sf_hists_1GeV[1]->Divide(sf_hists_1GeV[0]);


   LFG_hA_2GeV[1]->SetTitle("GEM21_11a LFG hA");
   LFG_hN_2GeV[1]->SetTitle("GEM21_11b LFG hN");
   CFG_hA_2GeV[1]->SetTitle("GEM21_11a CFG hA");
   LFG_hA_2GeV[1]->Divide(LFG_hA_2GeV[0]);
   LFG_hN_2GeV[1]->Divide(LFG_hN_2GeV[0]);
   CFG_hA_2GeV[1]->Divide(CFG_hA_2GeV[0]);


   LFG_hA_2GeV[1]->GetXaxis()->SetTitle("Initial Proton Momentum (GeV)");
   LFG_hA_2GeV[1]->GetYaxis()->SetTitle("Transparency");
   LFG_hA_2GeV[1]->SetLineColor(kBlue);
   LFG_hN_2GeV[1]->SetLineColor(kRed);
   CFG_hA_2GeV[1]->SetLineColor(kGreen);

   LFG_hA_2GeV[1]->Draw("hist");
   LFG_hN_2GeV[1]->Draw("hist same");
   CFG_hA_2GeV[1]->Draw("hist same");
   LFG_hA_2GeV[1]->GetXaxis()->SetRangeUser(0,2.5);
   LFG_hA_2GeV[1]->GetYaxis()->SetRangeUser(0,1.0); 

   c1->BuildLegend();

   c1->SaveAs("test.png");

}

std::vector<TH1D*> Analysis::Loop(TString filename, double tot_xsec, double num_events, double &prot_fraction)
{
   std::vector<TH1D*> hists;

   TTree *tree;
   TFile *f = new TFile(filename);
   f->GetObject("gst",tree); 
   Init(tree);

   TH1D* h_prot_momi = new TH1D("init mom", "init mom", 60, 0, 2.5);
   TH1D* h_prot_momi_noFSI = new TH1D("init mom noFSI", "init mom noFSI", 60, 0, 2.5);

   TH1D* h_prot_momf = new TH1D("final mom", "final mom", 60, 0, 2);
   TH1D* h_prot_momf_noFSI = new TH1D("final mom noFSI", "final mom noFSI", 60, 0, 2);

   //Total number of entries
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nb = 0;

   //Loop over entries
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry); 

      if(jentry > 5e6) break;
      if(jentry%200000 == 0) std::cout << jentry/1000. << "k" << "\n";

      if(qel == false) continue;

      TVector3 evec;
      evec.SetXYZ(pxl,pyl,pzl);

      double theta_e_deg = evec.Theta()*TMath::RadToDeg();
      if(pass_elec_cut(pl, theta_e_deg) == false ) continue;

      //if(nf > 1) continue;
      //Loop over post-fsi nucleons

      if (pdgi[0] != 2212) continue;

      TVector3 pvecf;
      pvecf.SetXYZ(pxf[0], pyf[0],pzf[0]);
      double p_final = pvecf.Mag();

      TVector3 pveci;
      pveci.SetXYZ(pxi[0], pyi[0], pzi[0]);
      double p_initial = pveci.Mag();

      bool rescattered = false;
      if (resc[0] != 1) rescattered = true;

      double Tp = 0;
      double E2 = pow(p_initial,2.) + 0.938*0.938;
      double E = sqrt(E2);
      Tp = E - 0.938;

        //    double ProtonTheta_Deg = pvecf.Theta()*TMath::RadToDeg();
      //if(pass_prot_cut(pvecf.Mag(), ProtonTheta_Deg) == false) continue;

      h_prot_momi->Fill(p_initial);
      h_prot_momf->Fill(p_final);

      if (rescattered == false) {
	h_prot_momi_noFSI->Fill(p_initial);
	h_prot_momf_noFSI->Fill(p_final);
//	std::cout << "do we fill!??" << "\n"; 
     }

   }


   hists.push_back(h_prot_momi);
   hists.push_back(h_prot_momi_noFSI);
   hists.push_back(h_prot_momf);
   hists.push_back(h_prot_momf_noFSI);

   return hists;
}

bool pass_elec_cut(double pl, double theta_l){
   if(pl < 0.4) return false;
   if(theta_l < 15.0 || theta_l > 45.0) return false;
   if(theta_l < ( 17.0 + ( 7./pl ) ) ) return false;
   return true;

}
bool pass_prot_cut(double pp, double theta_p){
   if(theta_p < 12.0) return false;
   if(pp < .3) return false;
   return true;
}
