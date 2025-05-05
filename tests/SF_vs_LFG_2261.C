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

   

   gStyle->SetOptStat(0);
   gStyle->SetErrorX(0);
   gStyle->SetOptTitle(0);

   std::vector<TH1D*> sf_hists;
   std::vector<TH1D*> susa_hists;

   double sf_prot_frac = 0;
   double susa_prot_frac = 0;

   //Creating all of gennie histograms
   sf_hists = Loop("/pnfs/genie/scratch/users/nsteinbe/eGENIE_grid/e4v/2261/C12_SF_hN/EmQ2_04-routine_validation_01-eScattering/e4v_2261_hN_SF.gst.root", sigma_SF, num_events_SF, sf_prot_frac); 
   susa_hists = Loop("/pnfs/genie/persistent/users/apapadop/e4v_SuSav2/Exclusive/electrons/C12_2261GeV/apapadop_SuSav2_C12_2261GeV_master.root", sigma_susa, num_events_susa, susa_prot_frac);

   std::cout << "SuSA proton fraction = " << susa_prot_frac << "\n";
   std::cout << "SF proton fraction = " << sf_prot_frac << "\n";

   //for(TH1D* h: susa_hists) h->Scale(sf_prot_frac/susa_prot_frac);

   TCanvas *c1 = new TCanvas("emiss", "emiss", 1200, 800);
   sf_hists[0]->SetTitle("SF");
   sf_hists[0]->GetXaxis()->SetTitle("Missing Energy (GeV)");
   sf_hists[0]->GetYaxis()->SetTitle("#frac{d#sigma}{dE_{m}} (#mu b/GeV)");
   sf_hists[0]->SetLineColor(kRed);
   susa_hists[0]->SetTitle("LFG SuSA");
   susa_hists[0]->SetLineColor(kBlue);
   sf_hists[0]->Draw("hist same");
   susa_hists[0]->Draw("hist same");
   c1->BuildLegend();

   TCanvas *c2 = new TCanvas("pmiss", "pmiss", 1200, 800);
   susa_hists[1]->SetTitle("SuSAv2");
   sf_hists[1]->SetTitle("SF");
   sf_hists[1]->GetXaxis()->SetTitle("Missing Momentum (GeV)");
   sf_hists[1]->GetYaxis()->SetTitle("#frac{d#sigma}{dP_{m}} (#mu b/GeV)");
   sf_hists[1]->SetLineColor(kRed); sf_hists[3]->SetLineColor(kRed);
   sf_hists[3]->SetLineStyle(kDashed);
   susa_hists[1]->SetLineColor(kBlue); susa_hists[3]->SetLineColor(kBlue);
   susa_hists[3]->SetLineStyle(kDashed);
   sf_hists[1]->Draw("HIST SAME");
   sf_hists[3]->Draw("HIST SAME");
   susa_hists[1]->Draw("HIST SAME");
   susa_hists[3]->Draw("HIST SAME");
   c2->BuildLegend();

   double kF = 0.240;

   int bin_kF = susa_hists[4]->FindBin(kF);
   double SuSA_MF = susa_hists[4]->Integral(1,bin_kF);
   double SF_MF = sf_hists[4]->Integral(1,bin_kF);

   double SuSA_total = susa_hists[4]->Integral(1,susa_hists[4]->GetNbinsX()+1);
   double SF_total = sf_hists[4]->Integral(1,susa_hists[4]->GetNbinsX()+1);

   std::cout << "SuSAv2 MF/Total ratio = " << SuSA_MF/SuSA_total << "\n";
   std::cout << "SF MF/Total ratio = " << SF_MF/SF_total << "\n";



   TCanvas *c3 = new TCanvas("nuc mom", "nuc mom", 1200, 800);
   sf_hists[4]->SetTitle("SF");
   sf_hists[4]->GetXaxis()->SetTitle("P_{n} (Struck nucleon momentum) (GeV)");
   sf_hists[4]->GetYaxis()->SetTitle("#frac{d#sigma}{dP_{n}} (#mu b/GeV)");
   sf_hists[4]->SetLineColor(kRed);
   susa_hists[4]->SetTitle("LFG SuSA");
   susa_hists[4]->SetLineColor(kBlue);
   sf_hists[4]->Draw("hist same");
   susa_hists[4]->Draw("hist same");
   c3->BuildLegend();

   TCanvas *c4 = new TCanvas("nuc mom final", "nuc mom final", 1200, 800);
   sf_hists[5]->SetTitle("SF");
   susa_hists[5]->SetTitle("SuSAv2 LFG");
   sf_hists[5]->GetXaxis()->SetTitle("P_{p} (Proton momentum) (GeV)");
   sf_hists[5]->GetYaxis()->SetTitle("#frac{d#sigma}{dP_{p}} (#mu b/GeV)");
   sf_hists[5]->SetLineColor(kRed); sf_hists[7]->SetLineColor(kRed);
   sf_hists[7]->SetLineStyle(kDashed);
   susa_hists[5]->SetLineColor(kBlue); susa_hists[7]->SetLineColor(kBlue);
   susa_hists[7]->SetLineStyle(kDashed);
   sf_hists[5]->Draw("HIST SAME");
   sf_hists[7]->Draw("HIST SAME");
   susa_hists[5]->Draw("HIST SAME");
   susa_hists[7]->Draw("HIST SAME");
   c4->BuildLegend();

   TCanvas *c5 = new TCanvas("omega", "omega", 1200, 800);
   sf_hists[9]->SetTitle("SF");
   susa_hists[9]->SetTitle("SuSAv2");
   sf_hists[9]->GetXaxis()->SetTitle("Energy transfer (GeV)");
   sf_hists[9]->GetYaxis()->SetTitle("#frac{d#sigma}{d#Omega dE} (#mu b /GeV sr)");
   sf_hists[9]->SetLineColor(kRed);
   double delta_cos = std::abs( std::cos( 25.5*TMath::DegToRad() ) - std::cos( 28.5*TMath::DegToRad() ) );
   sf_hists[9]->Scale(1./(2.0*TMath::Pi())/delta_cos);
   susa_hists[9]->Scale(1./(2.0*TMath::Pi())/delta_cos);
   sf_hists[9]->Draw("HIST SAME");
   susa_hists[9]->Draw("HIST SAME");

}

std::vector<TH1D*> Analysis::Loop(TString filename, double tot_xsec, double num_events, double &prot_fraction)
{
   std::vector<TH1D*> hists;

   TTree *tree;
   TFile *f = new TFile(filename);
   f->GetObject("gst",tree); 
   Init(tree);

   TH1D* h_omega = new TH1D("omega", "omega", 50, 0,1.0);

   TH1D* h_emiss = new TH1D("Emiss", "Emiss", 100, 0, .2);
   TH1D* h_pmiss = new TH1D("P_{m}", "P_{m}", 100, 0, 1.0);
   TH1D* h_pmiss_phicut = new TH1D("P_{m} (e-p opposite sector)", "P_{m} (e-p opposite sector)", 100, 0, 1.0);
   TH1D* h_pmiss_thetaPQcut = new TH1D("P_{m} (#theta_{PQ} < 20.^{#circ})", "P_{m} (#theta_{PQ} < 20.^{#circ})", 100, 0, 1.0);
   TH1D *h_nuc_mom = new TH1D("nuc_mom", "nuc_mom", 100, 0, 0.7);
   TH1D *h_nuc_final = new TH1D("final nuc mom", "final nuc mom", 50, 0.3, 1.6);
   TH1D* h_nuc_final_deltaphi = new TH1D("P_{p} (e-p opposite sector)", "P_{p} (e-p opposite sector)", 50, 0.3, 1.2);
   TH1D* h_nuc_final_thetaPQ = new TH1D("P_{p} (#theta_{PQ} < 20.^{#circ})", "P_{p} (#theta_{PQ} < 20.^{#circ})", 50, 0.3, 1.2);
   TH1D *h_nuc_final_pmcut = new TH1D("P_{p} (P_{m} < 0.4 GeV)", "P_{p} (P_{m} < 0.4 GeV)", 50, 0.3, 1.2);
   
   //Total number of entries
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nb = 0;

   int num_struck_prot = 0;
   int num_struck_neut = 0;

   //Loop over entries
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry); 

      if(jentry > 5e6) break;
      if(jentry%10000 == 0) std::cout << jentry/1000. << "k" << "\n";

      //if(qel == false) continue;

      TVector3 evec;
      evec.SetXYZ(pxl,pyl,pzl);

      double theta_e_deg = evec.Theta()*TMath::RadToDeg();
      if(pass_elec_cut(pl, theta_e_deg) == false ) continue;

      //if(theta_e_deg < 21.0 || theta_e_deg > 23.0) continue;

      if(theta_e_deg < 25.5 || theta_e_deg > 28.5) continue;

      TVector3 qvec;
      qvec.SetXYZ(-pxl, -pyl, 2.261 - pzl);

      double omega = 2.261 - El;

      double pmiss;
      double emiss;

      if(pdgi[0] == 2212) num_struck_prot++;
      if(pdgi[0] == 2112) num_struck_neut++;

      h_omega->Fill(omega);


      if(nf > 1) continue;
      //Loop over post-fsi nucleons

      if(pdgf[0] != 2212) continue;

      TVector3 pvec;
      pvec.SetXYZ(pxf[0], pyf[0],pzf[0]);
      double p_final = pvec.Mag();

      double ProtonTheta_Deg = pvec.Theta()*TMath::RadToDeg();
      if(pass_prot_cut(pvec.Mag(), ProtonTheta_Deg) == false) continue;

      TVector3 pm = qvec - pvec;
      pmiss = pm.Mag();
      emiss = omega - (Ef[0] - .938); 

      h_nuc_mom->Fill(sqrt(pxn*pxn + pyn*pyn + pzn*pzn));
      h_emiss->Fill(emiss);
      h_pmiss->Fill(pmiss);
      h_nuc_final->Fill(p_final);

      double phi_dff = std::abs(pvec.Phi() - evec.Phi())*TMath::RadToDeg();
      if ( std::abs(phi_dff - 180.0) > 30.0) continue;
      
      h_pmiss_phicut->Fill(pmiss);
      h_nuc_final_deltaphi->Fill(p_final);

      double thetaPQ = pvec.Angle(qvec)*TMath::RadToDeg();
      if (thetaPQ > 20.0) continue;

      h_nuc_final_thetaPQ->Fill(p_final);
      h_pmiss_thetaPQcut->Fill(pmiss);

      if(pmiss > 0.4) continue;

      h_nuc_final_pmcut->Fill(p_final);

   }

   prot_fraction = double(num_struck_prot)/double(num_struck_neut + num_struck_prot);

   hists.push_back(h_emiss);
   hists.push_back(h_pmiss);
   hists.push_back(h_pmiss_phicut);
   hists.push_back(h_pmiss_thetaPQcut);
   hists.push_back(h_nuc_mom);
   hists.push_back(h_nuc_final);
   hists.push_back(h_nuc_final_deltaphi);
   hists.push_back(h_nuc_final_thetaPQ);
   hists.push_back(h_nuc_final_pmcut);
   hists.push_back(h_omega);

   for(TH1D* h: hists) {
      h->Scale(1e30*tot_xsec/num_events, "width");
   }

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
