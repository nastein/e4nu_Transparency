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
#include "parse_file.C"
#include "../Transparency/myFunctions.h"

void h1_True_phi_data_mc(std::string sim, std::string targ, std::string beamen, std::string range, std::string type){

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
    std::string file_name3;
 
    std::string sim_num;
    std::string sim_label;
    if(sim == "SuSA") {sim_label = FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithoutFidAcc"]; sim_num = "1";}
    if(sim == "G18") {sim_label = FSIModelsToLabels["hA2018_Final_NoRadCorr_LFGM_Truth_WithoutFidAcc"]; sim_num = "2";}

    std::string flipped_target;
    if(targ == "56Fe") flipped_target = "Fe56";
    if(targ == "4He") flipped_target = "He4";
    if(targ == "C12") flipped_target = "C12";

    file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/"+sim+"/Big_"+type+"_Range"+range+"_Genie_"+sim_num+"_"+targ+"_"+beamen+".root";
    file_name3 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SuSAv2/"+type+"_Range"+range+"_Genie_"+sim_num+"_"+targ+"_"+beamen+".root";
    file_name2 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/"+flipped_target+"/"+type+"_Range"+range+"_Data__"+targ+"_"+beamen+".root";

    //file_name2= "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/elec_momData__56Fe_4.461000.root";
    //file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/elec_momGenie_1_56Fe_4.461000.root";

    TFile *input1 = TFile::Open( TString(file_name1));
    TFile *input2 = TFile::Open( TString(file_name2));
    TFile *input3 = TFile::Open( TString(file_name3));

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

    TH1D* h1_phi_mc;
    TH1D* h1_phi_mc2;
    TH1D* h1_phi_data;

    TH2D* h2_proton_thetaphi_mc;
    TH2D* h2_proton_thetaphi_mc2;
    TH2D* h2_proton_thetaphi_data;


    h2_proton_thetaphi_mc = (TH2D*)input1->Get(TString::Format("h2_Proton_Theta_Phi"));
    h2_proton_thetaphi_mc2 = (TH2D*)input3->Get(TString::Format("h2_Proton_Theta_Phi"));
    h2_proton_thetaphi_data = (TH2D*)input2->Get(TString::Format("h2_Proton_Theta_Phi"));

    TCanvas *c1 = new TCanvas("MC","MC");
    h2_proton_thetaphi_mc->GetXaxis()->SetTitle("Proton phi (Deg)");
    h2_proton_thetaphi_mc->GetYaxis()->SetTitle("Proton theta (Deg)");
    h2_proton_thetaphi_mc->Draw("COLZ");


    TCanvas *c2 = new TCanvas("Data", "Data");
    h2_proton_thetaphi_data->Draw("COLZ");


    h1_phi_mc = (TH1D*)h2_proton_thetaphi_mc->ProjectionX("mc_phi");
    h1_phi_mc2 = (TH1D*)h2_proton_thetaphi_mc2->ProjectionX("mc_phi2");
    h1_phi_data = (TH1D*)h2_proton_thetaphi_data->ProjectionX("data_phi");


    UniversalE4vFunction(h1_phi_mc,  sim_label, target, beam_en, TString(info1)+TString(cuts1));

    UniversalE4vFunction(h1_phi_mc2,  sim_label, target, beam_en, TString(info1)+TString(cuts1));
    PrettyDoubleXSecPlot(h1_phi_mc, 2, 2.261, 4, false);
    PrettyDoubleXSecPlot(h1_phi_mc2, 2, 2.261, 4, false);
    UniversalE4vFunction(h1_phi_data,  "Pinned Data", target, beam_en, TString(info2));

    h1_phi_mc->Scale(0.5);
    h1_phi_mc2->Scale(0.5);
    

    // create a canvas on which to draw the histograms
    
    double max = 1.1*h1_phi_mc->GetMaximum();

    const int color_options[4] = {kBlue, kAzure+10, kGreen-3, kViolet};

    TCanvas* c3;
    c3 = new TCanvas(TString::Format("c3"), TString::Format("c3"), 1000, 1000);
    //c3->SetLogy();
    // format the histograms
    h1_phi_data->Sumw2();
    h1_phi_data->SetStats( 0); // get rid of the stats box that usually appears at the top right of plots
    h1_phi_mc->GetXaxis()->SetTitle("#phi_{p} (degrees)");
    h1_phi_mc->GetYaxis()->SetTitle("Scaled Events");
    h1_phi_mc->SetTitle(TString(info2)+TString(cuts2));
    h1_phi_data->SetMarkerStyle(kFullCircle);
    h1_phi_data->SetMarkerColor(kBlack);
    h1_phi_mc->GetYaxis()->SetRangeUser(0.0,max);

    gStyle->SetOptStat(0);
    h1_phi_mc->SetLineColor(kBlue);
    
    h1_phi_mc2->SetLineColor(kRed);

    h1_phi_mc->Draw("HIST "); 
    h1_phi_mc2->Draw("HIST SAME");
    h1_phi_data->Draw("E P SAME");

    // draw a legend for our plot
    TLegend *legend = new TLegend(.82,.65,.99,.85);
    legend->AddEntry( h1_phi_mc, "SuSA True");
    legend->AddEntry(h1_phi_mc2, "SuSA Reco");
    legend->AddEntry( h1_phi_data, "CLAS data");
    legend->SetBorderSize( 0);
    legend->SetFillStyle( 0);
    legend->Draw();


    // crop the margins of the canvas
    c3->SetLeftMargin( 0.2);
    c3->SetBottomMargin( 0.2);
    c3->SetRightMargin( 0.2);
    c3->Update();

    c3->SaveAs("Proton_Phi_Gaps.pdf");

    
}
