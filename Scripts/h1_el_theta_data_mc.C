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
#include "../Transparency/myFunctions.h"
#include "parse_file.C"

void h1_el_theta_data_mc( std::string sim, std::string targ, std::string beamen, std::string range, std::string type ){

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

    std::string flipped_target;
    if(targ == "56Fe") flipped_target = "Fe56";
    if(targ == "4He") flipped_target = "He4";
    if(targ == "C12") flipped_target = "C12";
 
    //file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/Third_Try/"+sim+"/"+type+"_Range"+range+"_Genie_"+sim_num+"_"+targ+"_"+beamen+".root";
    //file_name2 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_Sample3/"+flipped_target+"/"+type+"_Range"+range+"_Data__"+targ+"_"+beamen+".root";
    
    file_name1 = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/All_Angles_Genie_1_%s_%s.root",targ.c_str(),beamen.c_str());
    file_name2 = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/All_Angles/test_all_anglesData__%s_%s.root", targ.c_str(), beamen.c_str());

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

    std::string beam_en; double beam_energy;
    if(info1.find("1.161")!= std::string::npos) {beam_en = "1_161";beam_energy = 1.161;}
    else if(info1.find("2.261")!= std::string::npos) {beam_en = "2_261"; beam_energy = 2.261;}
    else {beam_en = "4_461"; beam_energy = 4.461;}

    std::string target;
    if(info1.find("C12")!= std::string::npos) {target = "12C";}
    else if(info1.find("4He")!= std::string::npos) {target = "4He";}
    else {target = "56Fe";}

    std::cout << "Simulation: " << sim << "\n";
    std::cout << "Sim label: " << sim_label << "\n";
    std::cout << "Analyzing target: " << target << "\n";
    std::cout << "Analyzed beam en: " << beam_en << "\n";

    // histogram initialization
    TH1D* h1_theta_el_mc;
    TH1D* h1_theta_el_data;


    h1_theta_el_mc = (TH1D*)input1->Get(TString::Format("h1_el_theta"));
    h1_theta_el_data = (TH1D*)input2->Get(TString::Format("h1_el_theta"));


   UniversalE4vFunction(h1_theta_el_mc,  sim_label, target, beam_en, TString(info1)+TString(cuts1));
   
    PrettyDoubleXSecPlot(h1_theta_el_mc, 2, beam_energy, 4, false);
   UniversalE4vFunction(h1_theta_el_data,  "Pinned Data", target, beam_en, TString(info2));


    // create a canvas on which to draw the histograms
    

    const int color_options[4] = {kBlue, kAzure+10, kGreen-3, kViolet};

    TCanvas* c;
    c = new TCanvas(TString::Format("c"), TString::Format("c"), 1200, 1000);

    //PrettyDoubleXSecPlot(h1_theta_el_mc, 2, beam_energy, 4, false);
    PrettyDoubleXSecPlot(h1_theta_el_data, 2, beam_energy, 4, false);
    // format the histograms
    h1_theta_el_data->Sumw2();
    h1_theta_el_data->SetStats( 0); // get rid of the stats box that usually appears at the top right of plots
    //h1_theta_el_data->GetXaxis()->SetTitle("Electron Scattering Angle (Degrees)");
    //h1_theta_el_data->GetYaxis()->SetTitle("Events");
    h1_theta_el_data->GetXaxis()->CenterTitle( true);
    h1_theta_el_data->GetYaxis()->CenterTitle( true);
    h1_theta_el_data->SetTitle(TString(info2)+TString(cuts2));
    h1_theta_el_data->SetMarkerStyle(kFullCircle);
    h1_theta_el_data->SetMarkerSize(1.5);
    h1_theta_el_data->SetMarkerColor(kBlack);
    
    h1_theta_el_data->SetLineColor(kBlack);
    h1_theta_el_data->GetXaxis()->SetRangeUser(10.,60.);
    h1_theta_el_data->GetXaxis()->SetTitle("Electron Scattering Angle (Degrees)");
    //h1_theta_el_data->GetYaxis()->SetTitle("Scaled Number of Events");
    double max = 1.1*h1_theta_el_data->GetMaximum();
    h1_theta_el_data->GetYaxis()->SetRangeUser(0., max);
    //h1_theta_el_mc->Draw("HIST E");
    h1_theta_el_data->Draw("E P SAME");


    TLine *r1l = new TLine(21,0,21,max);
    TLine *r1r = new TLine(23,0,23,max);
    r1l->SetLineColor(kRed);
    r1r->SetLineColor(kRed);
    r1l->Draw();
    r1r->Draw();
    TLine *r2l = new TLine(28,0,28,max);
    TLine *r2r = new TLine(31,0,31,max);
    r2l->SetLineColor(kBlue);
    r2r->SetLineColor(kBlue);
    if(beam_energy == 2.261){
        r2l->Draw();
        r2r->Draw();
        }
    TLine *r3l = new TLine(37,0,37,max);
    TLine *r3r = new TLine(40,0,40,max);
    r3l->SetLineColor(6);
    r3r->SetLineColor(6);
    if(beam_energy == 2.261){
    r3l->Draw();
    r3r->Draw();
        }
    
    // draw a legend for our plot
    TLegend *legend = new TLegend( .60,.55,.79,.9);
    //legend->AddEntry( h1_theta_el_mc, "SuSAv2");
    legend->AddEntry( h1_theta_el_data, "CLAS data");
    legend->SetBorderSize( 0);
    legend->SetFillStyle( 0);
    legend->Draw();

    // crop the margins of the canvas
    c->SetLeftMargin( 0.2);
    c->SetBottomMargin( 0.2);
    c->SetRightMargin( 0.2);
    c->Update();


    c->SaveAs(TString::Format("ElecTheta_%s_%s_%s.pdf",targ.c_str(), beamen.c_str(), range.c_str()));

    
}
