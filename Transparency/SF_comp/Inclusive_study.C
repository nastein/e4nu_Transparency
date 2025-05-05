// File to plot histograms of the proton momentum for a simulation.
//
// Author: Jacob Smith (smithja)
// Creation Date: 11/02/2021
//
// Notes:
// - This file was adapted from Graham Chambers' (gchamber) file called el_mom_plot.C located at
//   /genie/app/users/gchamber/e4nu/tutorial_code/. To better indicate which quantities are being
//   plotted and if the quantities are separated into the interaction components, I have modified
//   this file and created several others to plot similar distributions.

// These include statements were here when I received Graham's code. Delete/Modify them at
// your own peril.
#include <TFile.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TString.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TMath.h>
#include <TLine.h>
#include <TPad.h>
#include <TGaxis.h>
#include <THStack.h>
#include <TLine.h>

#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
//#include "myFunctions.cpp"
#include "../myFunctions.h"
#include "../Constants.h"

void Inclusive_study(){


   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);


   // import the ROOT data file from the output of doing ./genie_analysis in the e4nu directory
   std::string file_name5;

   std::string sim_num;
   std::string sim_label;sim_label = FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"]; sim_num = "1";
   std::string radsim_label;
   radsim_label = FSIModelsToLabels["SuSav2_RadCorr_LFGM_Truth_WithFidAcc_UpdatedSchwinger"];


   double beam_energy;
   beam_energy = 2.261;
    

    file_name5 = "SF_range2_truth_Genie_1_C12_2.261000.root";

    TFile *input5 = TFile::Open( TString(file_name5));
    TFile *xsec_file = TFile::Open("C12_xsecs.root");

    // Grab the TList in the ROOT File for info on the run

    std::string beam_en;
    beam_en = "2_261";
    std::string target;
    target = "12C";

    //std::cout << "Sim label: " << sim_label << "\n";
    std::cout << "Analyzing target: " << target << "\n";
    std::cout << "Analyzed beam en: " << beam_en << "\n";

   double delta_cos = std::abs( std::cos( 28.*TMath::DegToRad() ) - std::cos( 31.0*TMath::DegToRad() ) );
   double delta_phi = 12.*6.*TMath::DegToRad();
   double solid_angle = delta_phi*delta_cos;

    const int color_options[4] = {kBlue, kAzure+10, kGreen-3, kViolet};

    // histogram initialization
    TH1D* h_SF_el_mom[6];
    TH1D* h_SF_prot_mom[6];
    TH1D* h_SF_prot;
    TH1D* h_SF_omega;
    TH1D* h_hit_nuc;

    h_hit_nuc = (TH1D*)input5->Get("h1_hit_nuc");
    double num_prot = h_hit_nuc->GetBinContent(1);
    double num_neut = h_hit_nuc->GetBinContent(2);
    double neut_corr = num_prot/(num_neut + num_prot);

    for (int i = 0; i < 6; i++ ) {
      h_SF_el_mom[i] = (TH1D*)input5->Get(TString::Format("h1_1_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", i));
      h_SF_prot_mom[i] = (TH1D*)input5->Get(TString::Format("h1_1_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", i));
      if(i == 0) {
        h_SF_omega = (TH1D*)h_SF_el_mom[i]->Clone();
        h_SF_prot = (TH1D*)h_SF_prot_mom[i]->Clone();
      }
      else {
        h_SF_omega->Add(h_SF_el_mom[i]);
        h_SF_prot->Add(h_SF_prot_mom[i]);
      }
    }

    for(int ibin = 0; ibin < h_SF_prot->GetNbinsX(); ibin++) {
      if(ibin+1 < int(750)) {
        h_SF_prot->SetBinContent(ibin+1, 0.0);
      }
    }


    UniversalE4vFunction(h_SF_omega, FSIModelsToLabels["Fortran_SF_NoRadCorr_hN2018_Truth_WithoutFidAcc"], target, beam_en, "");
        UniversalE4vFunction(h_SF_prot, FSIModelsToLabels["Fortran_SF_NoRadCorr_hN2018_Truth_WithoutFidAcc"], target, beam_en, "");

   h_SF_omega->Rebin(40);
   h_SF_omega->Scale(1./solid_angle, "width");

   h_SF_prot->Rebin(40);
   h_SF_prot->Scale(1./solid_angle, "width");

   h_SF_omega->Scale(neut_corr);

   h_SF_omega->SetLineColor(kBlack);


   h_SF_prot->SetLineColor(kBlack);

   double sf_e_int = h_SF_omega->Integral(1,h_SF_omega->GetNbinsX());
   double sf_p_int = h_SF_prot->Integral(1,h_SF_prot->GetNbinsX());

   std::cout << "SF T: " << sf_p_int/sf_e_int << "\n";

    TCanvas* c1 = (TCanvas*)xsec_file->Get("total reco can_1_1");
    c1->Draw();
    h_SF_omega->SetTitle("SF C");
    h_SF_omega->SetLineWidth(2);
   h_SF_omega->Draw("e hist same");

    TLegend *l1 = c1->BuildLegend();
    l1->SetBorderSize(0);
    l1->SetTextSize(.03);

       TCanvas* c2 = (TCanvas*)xsec_file->Get("total reco can_1_0");
    c2->Draw();
    h_SF_prot->SetTitle("SF C");
    h_SF_prot->SetLineWidth(2);
   h_SF_prot->Draw("e hist same");

    TLegend *l2 = c2->BuildLegend();
    l2->SetBorderSize(0);
    l2->SetTextSize(.03);


}
