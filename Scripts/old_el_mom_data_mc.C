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
#include "parse_file.C"
#include "../Transparency/myFunctions.h"

void old_el_mom_data_mc(std::string sim, std::string targ, std::string beamen){


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

    double beam_energy;
    if(beamen == "2.261000") beam_energy = 2.261;
    if(beamen == "4.461000") beam_energy = 4.461;
    //file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/Electron_momentum/Electron_mom_Genie_"+sim_num+"_"+targ+"_"+beamen+".root";
    //file_name2 = "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/Electron_momentum/Electron_mom_Data__"+targ+"_"+beamen+".root";

    file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/SuSAv2/Excl_Range1_Genie_1_C12_2.261000.root";
   
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
    if(info1.find("1.161")!= std::string::npos) {beam_en = "1_161";}
    else if(info1.find("2.261")!= std::string::npos) {beam_en = "2_261";}
    else {beam_en = "4_461";}

    std::string target;
    if(info1.find("C12")!= std::string::npos) {target = "12C";}
    else if(info1.find("4He")!= std::string::npos) {target = "4He";}
    else {target = "56Fe";}

    std::cout << "Simulation: " << sim << "\n";
    std::cout << "Sim label: " << sim_label << "\n";
    std::cout << "Analyzing target: " << target << "\n";
    std::cout << "Analyzed beam en: " << beam_en << "\n";

    int el_angle_bins = 8;
    double e_theta_bins[] = {19.,21.,23.,25.,28.,31.,34.,37.,40.};
    TCanvas *c;
    TLegend *legend;

    const int color_options[4] = {kBlue, kAzure+10, kGreen-3, kViolet};

    // histogram initialization
    TH1D* h1_elmom_mc_total;
    TH1D* h1_elmom_InteractionBreakDown_inSector_mc[4][6];
    TH1D* h1_elmom_mc_int[4];
    TH1D* h1_elmom_data[6];

   	for (int i = 0; i < 4; i++) { // for all the interactions
   	    for (int j = 0; j < 6; j++) { // for all the sectors
       	   // extract the histrograms
       	   h1_elmom_InteractionBreakDown_inSector_mc[i][j] = (TH1D*)input1->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", i+1, j));    
       	   h1_elmom_InteractionBreakDown_inSector_mc[i][j]->Rebin(40);
            //Add everything to the first sector
               if(i == 0 && j == 0) h1_elmom_mc_total = (TH1D*)h1_elmom_InteractionBreakDown_inSector_mc[i][j]->Clone();
               if(i != 0 ||  j != 0) h1_elmom_mc_total->Add(h1_elmom_InteractionBreakDown_inSector_mc[i][j]);
   	        if(j == 0) h1_elmom_mc_int[i] = (TH1D*)h1_elmom_InteractionBreakDown_inSector_mc[i][j]->Clone();
   		    if(j != 0) h1_elmom_mc_int[i]->Add(h1_elmom_InteractionBreakDown_inSector_mc[i][j]);
   	   }
   	}

      /*
      for (int i = 0; i < 6; i++) { // for all the sectors
         h1_elmom_data[i] = (TH1D*)input2->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", i));
         h1_elmom_data[i]->Rebin(40);
      }

      // compile all the sectors into one histogram
      for( int i = 1; i < 6; i++) { 
         h1_elmom_data[0]->Add( h1_elmom_data[i]); 
      }
      */

      UniversalE4vFunction(h1_elmom_mc_total,  sim_label, target, beam_en, TString(info1)+TString(cuts1));
      PrettyDoubleXSecPlot(h1_elmom_mc_total, 2, beam_energy, 4, false);
      for(int i = 0; i < 4; i++) {
         UniversalE4vFunction(h1_elmom_mc_int[i], sim_label, target, beam_en, TString(info1)+TString(cuts1));
         PrettyDoubleXSecPlot(h1_elmom_mc_int[i], 2, beam_energy, 4, false);
      }
      h1_elmom_mc_total->GetXaxis()->SetNdivisions(10, kTRUE);
      //UniversalE4vFunction(h1_elmom_data[0],  "Pinned Data", target, beam_en, TString(info2));

      c = new TCanvas(TString::Format("c"), TString::Format("c"), 1200, 1000);
      

      double max = 1.1*h1_elmom_mc_total->GetMaximum();

      /*
      h1_elmom_data[0]->Sumw2();
      h1_elmom_data[0]->SetStats( 0); 
      h1_elmom_data[0]->SetMarkerStyle(kFullCircle);
      h1_elmom_data[0]->SetMarkerSize(1.5);
      h1_elmom_data[0]->SetMarkerColor(kBlack);
      h1_elmom_data[0]->GetYaxis()->SetRangeUser(0,max);
      */

      h1_elmom_mc_total->SetLineColor(kBlack);
      h1_elmom_mc_total->GetYaxis()->SetRangeUser(0, max);
      if(beam_energy == 4.461) h1_elmom_mc_total->GetXaxis()->SetRangeUser(2.0,4.);
      if(beam_energy == 2.261) h1_elmom_mc_total->GetXaxis()->SetRangeUser(0.5,2.1);
      h1_elmom_mc_total->GetXaxis()->SetTitle("Electron Momentum (GeV)");
      h1_elmom_mc_total->Draw("HIST E");

      /*
       double cutval;
       if(targ == "C12") {
         if(range=="1"){
            if(beamen =="2.261000") {
               cutval = 1.95;
               h1_elmom_mc_total->GetXaxis()->SetRangeUser(1.4,2.4);
            }
            else {
               cutval = 3.4;
               h1_elmom_mc_total->GetXaxis()->SetRangeUser(1.9,4.1);
            }
         }
         else if(range=="2") {
            cutval = 1.75;
            h1_elmom_mc_total->GetXaxis()->SetRangeUser(0.5,2.1);
         }
         else {
            cutval = 1.5;
            h1_elmom_mc_total->GetXaxis()->SetRangeUser(0.5,2.1);
         }
       }

      if(targ == "4He") {
         if(range=="1"){
            if(beamen == "2.261000") {
               cutval = 1.85;
               h1_elmom_mc_total->GetXaxis()->SetRangeUser(1.4,2.4);
            }
            else {
               cutval = 3.4;
               h1_elmom_mc_total->GetXaxis()->SetRangeUser(1.9,4.2);
            }
         }
         else if(range=="2") {
            cutval = 1.75;
            h1_elmom_mc_total->GetXaxis()->SetRangeUser(0.5,2.1);
         }
         else {
            cutval = 1.5;
            h1_elmom_mc_total->GetXaxis()->SetRangeUser(0.5,2.1);
         }
       }

      if(targ == "56Fe") {
         if(range=="1"){
            if(beamen == "2.261000") {
               cutval = 1.95;
               h1_elmom_mc_total->GetXaxis()->SetRangeUser(1.4,2.4);
            }
            else {
               cutval = 3.35;
               h1_elmom_mc_total->GetXaxis()->SetRangeUser(2.0,4.0);
            }
         }
         else if(range=="2") {
            cutval = 1.75;
            h1_elmom_mc_total->GetXaxis()->SetRangeUser(0.5,2.1);
         }
         else {
            cutval = 1.5;
            h1_elmom_mc_total->GetXaxis()->SetRangeUser(0.5,2.1);
         }
       }

       TLine *cut = new TLine(cutval, 0, cutval, max);
       cut->SetLineColor(kRed);
       cut->SetLineWidth(3);
       cut->Draw();
       */

      //h1_elmom_data[0]->Draw("E P SAME");
      for(int i = 0; i < 4; i++) {
         h1_elmom_mc_int[i]->SetLineColor(color_options[i]);
         h1_elmom_mc_int[i]->GetYaxis()->SetRangeUser(0,max);
         h1_elmom_mc_int[i]->Draw("HIST SAME");
      }


      

      // draw a legend for our plot
         legend = new TLegend(.82,.65,.99,.85);
         legend->AddEntry( h1_elmom_mc_total, sim.c_str());
         //legend->AddEntry( h1_elmom_data[0], "CLAS data");
         legend->AddEntry( h1_elmom_mc_int[0],"QE");
         legend->AddEntry( h1_elmom_mc_int[1],"MEC");
         legend->AddEntry( h1_elmom_mc_int[2],"RES");
         legend->AddEntry( h1_elmom_mc_int[3],"DIS");
         legend->SetBorderSize( 0);
         legend->SetFillStyle( 0);
         legend->Draw();


      // crop the margins of the canvas
      c->SetLeftMargin( 0.2);
      c->SetBottomMargin( 0.2);
      c->SetRightMargin( 0.2);
      c->Update();  
   
}
