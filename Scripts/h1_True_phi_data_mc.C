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

    std::string data = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Data_ThetaPQ/"+flipped_target+"/"+type+"_Range"+range+"_Data__"+targ+"_"+beamen+".root";
    //std::string truth = "/genie/app/users/nsteinbe/grahams_e4nu/Analyze_data/True_Range1_NoProtCuts_Genie_1_C12_2.261000.root";;
    //std::string truthreco = "/genie/app/users/nsteinbe/grahams_e4nu/Analyze_data/TrueReco_Range1_NoProtCuts_Genie_1_C12_2.261000.root";
    //std::string truthreco_rad = "/genie/app/users/nsteinbe/grahams_e4nu/Analyze_data/TrueReco_Rad_Range1_NoProtCuts_Genie_3_C12_2.261000.root";

    std::string truth = "/genie/app/users/nsteinbe/grahams_e4nu/Analyze_data/SuSAv2_range1_noprotcuts_true_Genie_1_C12_2.261000.root";
    std::string truthreco = "/genie/app/users/nsteinbe/grahams_e4nu/Analyze_data/SuSAv2_range1_noprotcuts_truereco_Genie_1_C12_2.261000.root";
    std::string truthreco_rad = "/genie/app/users/nsteinbe/grahams_e4nu/Analyze_data/SuSAv2_range1_noprotcuts_truereco_rad_Genie_3_C12_2.261000.root";

    TFile *data_file = TFile::Open(TString(data));
    TFile *truth_file = TFile::Open(TString(truth));
    TFile *truthreco_file = TFile::Open(TString(truthreco));
    TFile *truthreco_rad_file = TFile::Open(TString(truthreco_rad));    

    // Grab the TList in the ROOT File for info on the run
    TList *Run_Info1 = (TList*)truth_file->Get("Run_Info");
    TList *Run_Info2 = (TList*)data_file->Get("Run_Info");

    std::vector<std::string> parse1 = parse_file(Run_Info1);
    std::vector<std::string> parse2 = parse_file(Run_Info2);

    info1 = parse1[0];
    cuts1 = parse1[1];
    info2 = parse2[0];
    cuts2 = parse2[1];

    std::string beam_en;
    if(info1.find("1.161")!= std::string::npos) {beam_en = "1_161";}
    if(info1.find("2.261")!= std::string::npos) {beam_en = "2_261";}
    if(info1.find("4.461")!= std::string::npos) {beam_en = "4_461";}

    std::string target;
    if(info1.find("C12")!= std::string::npos) {target = "12C";}
    else if(info1.find("4He")!= std::string::npos) {target = "4He";}
    else {target = "56Fe";}

    std::cout << "Simulation: " << sim << "\n";
    std::cout << "Sim label: " << sim_label << "\n";
    std::cout << "Analyzing target: " << target << "\n";
    std::cout << "Analyzed beam en: " << beam_en << "\n";

    // histogram initialization

    TH1D* h1_phi_truth;
    TH1D* h1_phi_truthreco;
    TH1D* h1_phi_truthreco_rad;
    TH1D* h1_phi_data;

    TH2D* h2_proton_thetaphi_truth;
    TH2D* h2_proton_thetaphi_truthreco;
    TH2D* h2_proton_thetaphi_truthreco_rad;
    TH2D* h2_proton_thetaphi_data;
    
    h2_proton_thetaphi_truth = (TH2D*)truth_file->Get(TString::Format("h2_Proton_Theta_Phi"));
    h2_proton_thetaphi_truthreco = (TH2D*)truthreco_file->Get(TString::Format("h2_Proton_Theta_Phi"));
    h2_proton_thetaphi_truthreco_rad = (TH2D*)truthreco_rad_file->Get(TString::Format("h2_Proton_Theta_Phi"));
    h2_proton_thetaphi_data = (TH2D*)data_file->Get(TString::Format("h2_Proton_Theta_Phi"));

    TCanvas *c1 = new TCanvas("MC","MC");
    h2_proton_thetaphi_truthreco->GetXaxis()->SetTitle("Proton phi (Deg)");
    h2_proton_thetaphi_truthreco->GetYaxis()->SetTitle("Proton theta (Deg)");
    h2_proton_thetaphi_truthreco->Draw("COLZ");

    TCanvas *c2 = new TCanvas("Data", "Data");
    h2_proton_thetaphi_data->Draw("COLZ");

    

    h1_phi_truth = (TH1D*)h2_proton_thetaphi_truth->ProjectionX("mc_phi");
    h1_phi_truthreco = (TH1D*)h2_proton_thetaphi_truthreco->ProjectionX("mc_reco_phi");
    h1_phi_truthreco_rad = (TH1D*)h2_proton_thetaphi_truthreco_rad->ProjectionX("mc_reco_rad_phi");
    h1_phi_data = (TH1D*)h2_proton_thetaphi_data->ProjectionX("data_phi");


    UniversalE4vFunction(h1_phi_truth,  sim_label, target, beam_en, TString(info1)+TString(cuts1));
    UniversalE4vFunction(h1_phi_truthreco,  sim_label, target, beam_en, TString(info1)+TString(cuts1));
    UniversalE4vFunction(h1_phi_truthreco_rad,  sim_label, target, beam_en, TString(info1)+TString(cuts1));
    PrettyDoubleXSecPlot(h1_phi_truth, 2, 2.261, 4, false);
    UniversalE4vFunction(h1_phi_data,  "Pinned Data", target, beam_en, TString(info2));

    
    TH1D* radCorr = (TH1D*)h1_phi_truthreco->Clone();
    radCorr->Divide(h1_phi_truthreco_rad);

    TH1D* accCorr = (TH1D*)h1_phi_truth->Clone();
    accCorr->Divide(h1_phi_truthreco);

    for(int whichbin = 0; whichbin < h1_phi_data->GetNbinsX(); whichbin++) {

    	double oldbincontent_git= h1_phi_data->GetBinContent(whichbin+1);
    	double oldbinerror_git = h1_phi_data->GetBinError(whichbin+1);

    	double acceptance = accCorr->GetBinContent(whichbin+1);
    	double radiation = radCorr->GetBinContent(whichbin+1);

    	if(acceptance < 0) acceptance = 1.0;
    	if(radiation < 0) radiation = 1.0;
	//radiation = 1;
    	double newbincontent_git = oldbincontent_git * acceptance * radiation;
    	double newbinerror_git = oldbinerror_git * acceptance * radiation;

    	h1_phi_data->SetBinContent(whichbin+1, newbincontent_git);
    	h1_phi_data->SetBinError(whichbin+1, newbinerror_git);

    }
   

    // create a canvas on which to draw the histograms
    
    double max = 1.1*h1_phi_truth->GetMaximum();

    const int color_options[4] = {kBlue, kAzure+10, kGreen-3, kViolet};

    TCanvas* c3;
    c3 = new TCanvas(TString::Format("c3"), TString::Format("c3"), 1000, 1000);
    //c3->SetLogy();
    // format the histograms
    h1_phi_data->Sumw2();
    h1_phi_data->SetStats( 0); // get rid of the stats box that usually appears at the top right of plots
    h1_phi_truth->GetXaxis()->SetTitle("#phi_{p} (degrees)");
    h1_phi_truth->GetYaxis()->SetTitle("Scaled Events");
    h1_phi_truth->SetTitle(TString(info2)+TString(cuts2));
    h1_phi_data->SetMarkerStyle(kFullCircle);
    h1_phi_data->SetMarkerColor(kBlack);
    h1_phi_truth->GetYaxis()->SetRangeUser(0.0,max);
    h1_phi_truth->GetXaxis()->SetRangeUser(0.0,360.0);
    //h1_phi_truth->Scale(.72/0.5);
    gStyle->SetOptStat(0);
    h1_phi_truth->SetLineColor(kBlue);
    
    //h1_phi_mc2->SetLineColor(kRed);

    //h1_phi_truth->Draw("HIST "); 
    //h1_phi_truthreco->Draw("HIST SAME");
    h1_phi_data->Draw("E P SAME");

    // draw a legend for our plot
    TLegend *legend = new TLegend(.82,.65,.99,.85);
    legend->AddEntry( h1_phi_truth, "SuSAv2");
    //legend->AddEntry(h1_phi_mc2, "SuSA Reco");
    legend->AddEntry( h1_phi_data, "CLAS data");
    legend->SetBorderSize( 0);
    legend->SetFillStyle( 0);
    legend->Draw();


    // crop the margins of the canvas
    c3->SetLeftMargin( 0.2);
    c3->SetBottomMargin( 0.2);
    c3->SetRightMargin( 0.2);
    c3->Update();

//    c3->SaveAs("Proton_Phi_Gaps.pdf");

    
}
