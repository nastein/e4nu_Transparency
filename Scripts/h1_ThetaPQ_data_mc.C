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

#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include "../Transparency/myFunctions.h"
#include "parse_file.C"

void h1_ThetaPQ_data_mc( std::string sim, std::string targ, std::string beamen, std::string range, std::string type ){

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

    int r;
    if(range == "1") r = 0;
    else if(range == "2") r = 1;
    else r = 2;
 
    //file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/ThetaPQ/ThetaPQ_Range"+range+"_Genie_"+sim_num+"_"+targ+"_"+beamen+".root";
    //file_name2 = "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/ThetaPQ/ThetaPQ_Range"+range+"_Data__"+targ+"_"+beamen+".root";
    
    if(sim == "SuSAv2") file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/"+sim+"/"+type+"_Range"+range+"_Genie_"+sim_num+"_"+targ+"_"+beamen+".root";
    file_name2 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/"+flipped_target+"/"+type+"_Range"+range+"_Data__"+targ+"_"+beamen+".root";

    
    TFile *input1 = TFile::Open( TString(file_name1));
    TFile *input2 = TFile::Open( TString(file_name2));

    // Grab the TList in the ROOT File for info on the run
    TList *Run_Info1 = (TList*)input1->Get("Run_Info");
    TList *Run_Info2 = (TList*)input2->Get("Run_Info");

    std::vector<std::string> parse1 = parse_file(Run_Info1);
    std::vector<std::string> parse2 = parse_file(Run_Info2);

    info1 = parse1[0];
    cuts1 = parse1[1];
    info2 = parse2[0];
    cuts2 = parse2[1];

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

    // histogram initialization
    TH1D* h1_ThetaPQ_mc_total;
    TH1D* h1_ThetaPQ_InteractionBreakDown_inSector_mc[4][6];
    TH1D* h1_ThetaPQ_mc_int[4];
    TH1D* h1_ThetaPQ_data[6];


	for (int i = 0; i < 4; i++) { // for all the interactions
	    for (int j = 0; j < 6; j++) { // for all the sectors
    		// extract the histrograms
    		h1_ThetaPQ_InteractionBreakDown_inSector_mc[i][j] = (TH1D*)input1->Get(TString::Format("h1_Int%i_Sect_%i_ThetaPQ", i+1, j));    
            if(j == 0) h1_ThetaPQ_mc_int[i] = (TH1D*)h1_ThetaPQ_InteractionBreakDown_inSector_mc[i][j]->Clone();
            else h1_ThetaPQ_mc_int[i]->Add(h1_ThetaPQ_InteractionBreakDown_inSector_mc[i][j]);
	    
	   }
	}

    h1_ThetaPQ_mc_total = (TH1D*)(h1_ThetaPQ_mc_int[0]->Clone());
    h1_ThetaPQ_mc_total->Add(h1_ThetaPQ_mc_int[1]);
    h1_ThetaPQ_mc_total->Add(h1_ThetaPQ_mc_int[2]);
    h1_ThetaPQ_mc_total->Add(h1_ThetaPQ_mc_int[3]);
    
   for (int i = 0; i < 6; i++) { // for all the sectors
      h1_ThetaPQ_data[i] = (TH1D*)input2->Get( TString::Format("h1_Int0_Sect_%i_ThetaPQ", i));
   }

   // compile all the sectors into one histogram
   for( int i = 1; i < 6; i++) { 
       h1_ThetaPQ_data[0]->Add( h1_ThetaPQ_data[i]); 
   }


   UniversalE4vFunction(h1_ThetaPQ_mc_total,  sim_label, target, beam_en, TString(info1)+TString(cuts1));
   PrettyDoubleXSecPlot(h1_ThetaPQ_mc_total, 2, beam_en_dbl, 4, false);
    for(int i = 0; i < 4; i++) {
        UniversalE4vFunction(h1_ThetaPQ_mc_int[i], sim_label, target, beam_en, TString(info1)+TString(cuts1));
        PrettyDoubleXSecPlot(h1_ThetaPQ_mc_int[i], 2, beam_en_dbl, 4, false);
    }
   UniversalE4vFunction(h1_ThetaPQ_data[0],  "Pinned Data", target, beam_en, TString(info2));
   //PrettyDoubleXSecPlot(h1_ThetaPQ_data[0], 0, beam_en_dbl, r, false);


    // create a canvas on which to draw the histograms
    

    const int color_options[4] = {kBlue, kAzure+10, kGreen-3, kViolet};
    std::string interactions[4] = {"QE", "MEC", "RES", "DIS"};

    TCanvas* c;
    c = new TCanvas(TString::Format("c"), TString::Format("c"), 1200, 1000);
    // format the histograms
    h1_ThetaPQ_data[0]->Sumw2();
    h1_ThetaPQ_data[0]->SetStats( 0); // get rid of the stats box that usually appears at the top right of plots
    h1_ThetaPQ_mc_total->GetXaxis()->SetTitle("ThetaPQ (Degrees)");
    h1_ThetaPQ_mc_total->GetYaxis()->SetTitle("Scaled Events");
    h1_ThetaPQ_mc_total->SetTitle(TString(info2)+TString(cuts2));

    h1_ThetaPQ_data[0]->SetMarkerStyle(kFullCircle);
    h1_ThetaPQ_data[0]->SetMarkerSize(1.5);
    h1_ThetaPQ_data[0]->SetMarkerColor(kBlack);

    h1_ThetaPQ_data[0]->GetXaxis()->SetRangeUser(0,90);


    double max = 1.1*h1_ThetaPQ_mc_total->GetMaximum();
    
    h1_ThetaPQ_mc_total->SetLineColor(kBlack);
    h1_ThetaPQ_mc_total->GetYaxis()->SetRangeUser(0, max);
    h1_ThetaPQ_mc_total->GetXaxis()->SetRangeUser(0,90);
    h1_ThetaPQ_mc_total->Draw("HIST");
    for(int i = 0; i < 4; i++) {
      h1_ThetaPQ_mc_int[i]->SetLineColor(color_options[i]);
        h1_ThetaPQ_mc_int[i]->GetXaxis()->SetRangeUser(0,90);
      h1_ThetaPQ_mc_int[i]->Draw("HIST SAME");
    }


    h1_ThetaPQ_data[0]->Draw("P E SAME");
    
    TLine *cut = new TLine(20., 0, 20., max);
    cut->SetLineColor(kRed);
    cut->SetLineWidth(3);
    cut->Draw();

    // draw a legend for our plot
    TLegend *legend = new TLegend(.82,.65,.99,.85);
    legend->AddEntry( h1_ThetaPQ_mc_total, "SuSAv2");
    for(int i = 0; i < 4; i++) {
        legend->AddEntry(h1_ThetaPQ_mc_int[i], TString::Format("%s", interactions[i].c_str()));
    }
    legend->AddEntry( h1_ThetaPQ_data[0], "CLAS data");
    legend->SetBorderSize( 0);
    legend->SetFillStyle( 0);
    legend->Draw();

    // crop the margins of the canvas
    c->SetLeftMargin( 0.2);
    c->SetBottomMargin( 0.2);
    c->SetRightMargin( 0.2);
    c->Update();

    c->SaveAs(TString::Format("ThetaPQcut/ThetaPQcut_%s_%s_%s.pdf",targ.c_str(), beamen.c_str(), range.c_str()));


    
}
