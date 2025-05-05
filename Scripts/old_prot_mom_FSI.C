// File to plot histograms of the proton momentum for a simulation. The histograms generated
// with this macro are separated into the different interaction components: quasi-elastic (QE),
// mesonic current (MEC), resonance (RES), and deep inelastic scattering (DIS). This functionality
// is indicated by "intSeparated" being in the macro's file name.
//
// Author: Jacob Smith (smithja)
// Creation Date: 09/23/2021
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

#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include "parse_file.C"
#include "../Transparency/myFunctions.h"

void old_prot_mom_FSI(std::string sim, std::string targ, std::string beamen){


    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);

    // declare variables that will be used in the plotting/formatting of histograms and file names
    std::string info1 ("");
    std::string cuts1 ("");    
    std::string info2 ("");
    std::string cuts2 ("");

// import the ROOT data file from the output of doing ./genie_analysis in the e4nu directory
    std::string file_name1;
    std::string file_name2;

    std::string sim_num;
    std::string sim_label;
    if(sim == "SuSAv2") {sim_label = FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"]; sim_num = "1";}
    if(sim == "SF") {sim_label = "SF"; sim_num = "2";}

    std::string flipped_target;
    if(targ == "56Fe") flipped_target = "Fe56";
    if(targ == "4He") flipped_target = "He4";
    if(targ == "C12") flipped_target = "C12";

    /*
    int r;
    if(range == "1") r = 0;
    else if(range == "2") r = 1;
    else r = 2;
    */

    /*
    if(sim == "SuSAv2") file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/"+sim+"/Excl_Range"+range+"_Genie_"+sim_num+"_"+targ+"_"+beamen+".root";
    file_name2 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/"+flipped_target+"/Excl_Range"+range+"_Data__"+targ+"_"+beamen+".root";
   */
    file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/SuSAv2/Excl_Range2_Genie_1_C12_2.261000.root";
   
    TFile *input1 = TFile::Open( TString(file_name1));
    //TFile *input2 = TFile::Open( TString(file_name2));

    // Grab the TList in the ROOT File for info on the run
    TList *Run_Info1 = (TList*)input1->Get("Run_Info");
    //TList *Run_Info2 = (TList*)input2->Get("Run_Info");

    std::vector<std::string> parse1 = parse_file(Run_Info1);
    //std::vector<std::string> parse2 = parse_file(Run_Info2);

    info1 = parse1[0];
    cuts1 = parse1[1];
    //info2 = parse2[0];
    //cuts2 = parse2[1];

    std::string beam_en;
    double beam_en_dbl;
    if(info1.find("1.161")!= std::string::npos) {beam_en = "1_161"; beam_en_dbl = 1.161;}
    else if(info1.find("2.261")!= std::string::npos) {beam_en = "2_261"; beam_en_dbl = 2.261;}
    else {beam_en = "4_461"; beam_en_dbl = 4.461;}

    std::string target;
    if(info1.find("C12")!= std::string::npos) {target = "12C";}
    else if(info1.find("4He")!= std::string::npos) {target = "4He";}
    else {target = "56Fe";}

    std::cout << "Simulation: " << sim << "\n";
    std::cout << "Sim label: " << sim_label << "\n";
    std::cout << "Analyzing target: " << target << "\n";
    std::cout << "Analyzed beam en: " << beam_en << "\n";

    TCanvas *c;
    TLegend *legend;

    const int color_options[8] = {kBlue, kAzure+10, kGreen-3, kViolet, kBlue+2, kBlack, kRed, kBlack+2};

    TH1D *h1_mom_mc_total;
    TH1D *h1_mom_mc_QE_FSI;
    TH1D *h1_mom_mc_QE_noFSI;
    TH1D *h1_mom_mc_non_QE;
    TH1D *h1_mom_data[6];

    TH1D *h1_mom_mc_individual[3][6];

      // create a canvas on which to draw the histograms
      c = new TCanvas(TString::Format("c"), TString::Format("c"), 1200, 1000);
      c->cd();
       for (int i = 0; i < 4; i++) { // for all the interactions
           for (int j = 0; j < 6; j++) { // for all the sectors
               if(i == 0) {
                   if(j == 0) {
                       h1_mom_mc_QE_noFSI = (TH1D*)(input1->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector%i_noFSI_prot_mom_QE",j))->Clone());
                       h1_mom_mc_QE_FSI = (TH1D*)(input1->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector%i_FSI_prot_mom_QE",j))->Clone());
                   }
                   else {
                       h1_mom_mc_QE_noFSI->Add((TH1D*)input1->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector%i_noFSI_prot_mom_QE",j)));
                       h1_mom_mc_QE_FSI->Add((TH1D*)input1->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector%i_FSI_prot_mom_QE",j)));
                   }
               }

               else {
                   h1_mom_mc_individual[i-1][j]= (TH1D*)input1->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", i+1, j)); 
                   if(i==1 && j==0) {
                       h1_mom_mc_non_QE= (TH1D*)h1_mom_mc_individual[i-1][j]->Clone();
                   }  
                   else h1_mom_mc_non_QE->Add(h1_mom_mc_individual[i-1][j]);
               }
           }
       }
       

       h1_mom_mc_QE_noFSI->Rebin(40);
       h1_mom_mc_QE_FSI->Rebin(40);
       h1_mom_mc_non_QE->Rebin(40);

       h1_mom_mc_total = (TH1D*)(h1_mom_mc_QE_noFSI->Clone());
       h1_mom_mc_total->Add(h1_mom_mc_QE_FSI);
       h1_mom_mc_total->Add(h1_mom_mc_non_QE);

       /*
       for (int i = 0; i < 6; i++) { // for all the sectors
           h1_mom_data[i] = (TH1D*)input2->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i_InSlice%i", i,th));
           h1_mom_data[i]->Rebin(40);
       }

       // compile all the sectors into one histogram
       for( int i = 1; i < 6; i++) { 
          h1_mom_data[0]->Add( h1_mom_data[i]); 
       }
       */

       UniversalE4vFunction(h1_mom_mc_total,  sim_label, target, beam_en, TString(info1)+TString(cuts1));
       PrettyDoubleXSecPlot(h1_mom_mc_total, 0, beam_en_dbl, 4, false);
           
       UniversalE4vFunction(h1_mom_mc_QE_noFSI, sim_label, target, beam_en, TString(info1)+TString(cuts1));
       PrettyDoubleXSecPlot(h1_mom_mc_QE_noFSI, 0, beam_en_dbl, 4, false);

       UniversalE4vFunction(h1_mom_mc_QE_FSI, sim_label, target, beam_en, TString(info1)+TString(cuts1));
       PrettyDoubleXSecPlot(h1_mom_mc_QE_FSI, 0, beam_en_dbl, 4, false);

       UniversalE4vFunction(h1_mom_mc_non_QE, sim_label, target, beam_en, TString(info1)+TString(cuts1));
       PrettyDoubleXSecPlot(h1_mom_mc_non_QE, 0, beam_en_dbl, 4, false);
       
       //UniversalE4vFunction(h1_mom_data[0],  "Pinned Data", target, beam_en, TString(info2));

       

       // initialize things such as color options that will be used in plotting the histograms below
       
       double hist_max = 0.;
       // format the histograms and then make them

       /*
       h1_mom_data[0]->SetMarkerStyle(kFullCircle);
       h1_mom_data[0]->SetMarkerSize(1.5);
       h1_mom_data[0]->SetMarkerColor(kBlack);
      */
   
       h1_mom_mc_total->SetLineColor(kBlack);
       h1_mom_mc_total->GetXaxis()->SetTitle("Proton Momentum (GeV)");

       hist_max = 1.1*h1_mom_mc_total->GetMaximum();
       h1_mom_mc_total->GetYaxis()->SetRangeUser(0,hist_max);
       h1_mom_mc_QE_FSI->GetYaxis()->SetRangeUser(0,hist_max);
       h1_mom_mc_non_QE->GetYaxis()->SetRangeUser(0,hist_max);
       h1_mom_mc_QE_noFSI->GetYaxis()->SetRangeUser(0,hist_max);

       h1_mom_mc_total->Draw("HIST E");
       h1_mom_mc_QE_FSI->SetLineColor(kBlue);
       h1_mom_mc_QE_noFSI->SetLineColor(kBlue);
       h1_mom_mc_QE_FSI->SetLineStyle(kDashed);
       h1_mom_mc_non_QE->SetLineColor(kViolet);

       h1_mom_mc_QE_FSI->Draw("HIST E SAME");
       h1_mom_mc_QE_noFSI->Draw("HIST E SAME");
       h1_mom_mc_non_QE->Draw("HIST E SAME");

       //h1_mom_data[0]->Draw("E P SAME");

      
           // draw a legend for our plot
       legend = new TLegend( .82,.65,.99,.85);
       legend->AddEntry( h1_mom_mc_total, sim.c_str());
       //legend->AddEntry( h1_mom_data[0], "CLAS data");
       legend->AddEntry( h1_mom_mc_QE_FSI,"QE FSI");
       legend->AddEntry( h1_mom_mc_QE_noFSI,"QE no FSI");
       legend->AddEntry( h1_mom_mc_non_QE,"non QE");
       legend->SetBorderSize( 0);
       legend->SetFillStyle( 0);
       legend->Draw();


       // crop the margins of the canvas
       c->SetLeftMargin( 0.2);
       c->SetBottomMargin( 0.2);
       c->SetRightMargin( 0.2);
       c->Update();
   
}

