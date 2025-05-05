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

   Loop("/pnfs/genie/persistent/users/jtenavid/e4nu_files/GENIE_Files/2024Generation/GEM21_11a_Dipole_CFG_Q2_04_2GeV_eCarbon.gst.root", 1);

}

void Analysis::Loop(TString filename, int range)
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

   int correlated = 0;
   int MF = 0;

   double etheta_min, etheta_max;
   double pmin;
   if(range == 1) {
        etheta_min = 21.0;
        etheta_max = 23.0;
  	pmin = 1.95;    
  }

      else if(range == 2){
        etheta_min = 28.0;
        etheta_max = 31.0;
	pmin = 1.75;   
   }

      else if(range == 3){
        etheta_min = 37.0;
        etheta_max = 40.0;
	pmin = 1.5;    
  }
   //Loop over entries
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry); 

      if(jentry > 1e6) break;
      if(jentry%200000 == 0) std::cout << jentry/1000. << "k" << "\n";

      if(qel == false) continue;

      TVector3 evec;
      evec.SetXYZ(pxl,pyl,pzl);
      
      double pl = evec.Mag();

      double theta_e_deg = evec.Theta()*TMath::RadToDeg();
      if(pass_elec_cut(pl, theta_e_deg) == false ) continue;

     
      if(theta_e_deg < etheta_min || theta_e_deg > etheta_max || pl < pmin) continue;

      if (pdgi[0] != 2212) continue;

      TVector3 pveci;
      pveci.SetXYZ(pxn, pyn, pzn);
      double p_initial = pveci.Mag();

      if (p_initial > .225) correlated++;
      else MF++;

     

   }


   double total = MF + correlated;
   std::cout << "MF fraction = " << double(MF)/double(total) << "\n";
   std::cout << "correlated fraction = " << double(correlated)/double(total) << "\n";

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
