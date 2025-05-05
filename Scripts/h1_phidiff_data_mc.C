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

void h1_phidiff_data_mc(std::string sim, std::string targ, std::string beamen, std::string range, std::string type){
	
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

    file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/"+sim+"/Excl_Range"+range+"_Genie_"+sim_num+"_"+targ+"_"+beamen+".root";
    file_name2 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Data_ThetaPQ/"+flipped_target+"/Excl_Range"+range+"_Data__"+targ+"_"+beamen+".root";

    //file_name2= "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/elec_momData__56Fe_4.461000.root";
    //file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/elec_momGenie_1_56Fe_4.461000.root";

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

    // histogram initialization
    TH1D* h1_elmom_mc_total;
    TH1D* h1_elmom_InteractionBreakDown_inSector_mc[4][6];
    TH1D* h1_elmom_mc_int[4];
    TH1D* h1_elmom_data[6];

    TH1D* h1_phidiff_mc;
    TH1D* h1_phidiff_data;



    h1_phidiff_mc = (TH1D*)input1->Get(TString::Format("h1_el_prot_phi_diff"));
	h1_phidiff_data = (TH1D*)input2->Get(TString::Format("h1_el_prot_phi_diff"));


    UniversalE4vFunction(h1_phidiff_mc,  sim_label, target, beam_en, TString(info1)+TString(cuts1));
    UniversalE4vFunction(h1_phidiff_data,  "Data", target, beam_en, TString(info2));
    

    // create a canvas on which to draw the histograms
    
    double max = 1.1*h1_phidiff_mc->GetMaximum();

    const int color_options[4] = {kBlue, kAzure+10, kGreen-3, kViolet};

    TCanvas* c3;
    c3 = new TCanvas(TString::Format("c3"), TString::Format("c3"), 1000, 1000);
    
    c3->SetLeftMargin( 0.2);
    c3->SetBottomMargin( 0.2);
    c3->SetRightMargin( 0.2);
    c3->Update();

     c3->SetLogy();
    // format the histograms
    h1_phidiff_data->Sumw2();
  
    PrettyDoubleXSecPlot(h1_phidiff_data, 2, 2.261000, 4, false);

     h1_phidiff_data->SetStats( 0); // get rid of the stats box that usually appears at the top right of plots
    h1_phidiff_data->GetXaxis()->SetTitle("#phi_{e} - #phi_{p} (degrees)");
    //h1_phidiff_data->GetYaxis()->SetTitle("Events");
    //h1_phidiff_data->GetXaxis()->CenterTitle( true);
    //h1_phidiff_data->GetYaxis()->CenterTitle( true);
    //h1_phidiff_data->SetTitle(TString(info2)+TString(cuts2));
    //h1_phidiff_data->SetMarkerStyle(2);
    //h1_phidiff_data->SetMarkerColor(kBlack);
    h1_phidiff_data->SetMarkerStyle(kFullCircle);
    h1_phidiff_data->SetMarkerSize(1.5);
    h1_phidiff_data->SetMarkerColor(kBlack);

    h1_phidiff_data->GetYaxis()->SetRangeUser(0.0000001,max);

    gStyle->SetOptStat(0);
    h1_phidiff_mc->SetLineColor(kBlack);
    h1_phidiff_mc->GetYaxis()->SetRangeUser(0.00000001, max);
    h1_phidiff_data->Draw(" E P");
    h1_phidiff_data->GetXaxis()->SetRangeUser(0,360.);

   

   h1_phidiff_mc->Draw("HIST SAME"); 

    // draw a legend for our plot
    TLegend *legend = new TLegend( 0.6, 0.625, 0.825, 0.875);
    legend->AddEntry( h1_phidiff_mc, sim.c_str());
    legend->AddEntry( h1_phidiff_data, "CLAS data");
    legend->SetBorderSize( 0);
    legend->SetFillStyle( 0);
    legend->Draw();


    // crop the margins of the canvas
    //c3->SetLeftMargin( 0.14);
    //c3->SetBottomMargin( 0.14);
    //c3->Update();
    c3->SaveAs("phi_difference_C12_2.261_Range2.pdf");
    
}
