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

void h1_holes(std::string beamen){

        // declare variables that will be used in the plotting/formatting of histograms and file names
    std::string info1 ("");
    std::string cuts1 ("");

    // import the ROOT data file from the output of doing ./genie_analysis in the e4nu directory
    std::string file_name1;
    std::string file_name2;
    std::string file_name3;
    std::string file_name4;
    std::string file_name5;
    std::string file_name6;
    std::string file_name7;
   
    file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/LookForHoles_Genie_1_C12_"+beamen+".root";
    
    //file_name2 = "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/Excl_Range1_Pt_FSItest_Genie_1_C12_2.261000.root";
    //file_name3 = "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/Excl_Range2_Pt_FSItest_Genie_1_C12_2.261000.root";
    //file_name4 = "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/Excl_Range3_Pt_FSItest_Genie_1_C12_2.261000.root";
    

    file_name2 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SuSAv2/Excl_Range1_Genie_1_C12_2.261000.root";
    file_name3 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SuSAv2/Excl_Range2_Genie_1_C12_2.261000.root";
    file_name4 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut/SuSAv2/Excl_Range3_Genie_1_C12_2.261000.root";

    file_name5 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/C12/Excl_Range1_Data__C12_2.261000.root";
    file_name6 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/C12/Excl_Range2_Data__C12_2.261000.root";
    file_name7 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/C12/Excl_Range3_Data__C12_2.261000.root";



    TFile *input1 = TFile::Open( TString(file_name1));
    TFile *input2 = TFile::Open( TString(file_name2));
    TFile *input3 = TFile::Open( TString(file_name3));
    TFile *input4 = TFile::Open( TString(file_name4));
    TFile *input5 = TFile::Open( TString(file_name5));
    TFile *input6 = TFile::Open( TString(file_name6));
    TFile *input7 = TFile::Open( TString(file_name7));

    // Grab the TList in the ROOT File for info on the run
    TList *Run_Info1 = (TList*)input1->Get("Run_Info");

    std::vector<std::string> parse1 = parse_file(Run_Info1);

    info1 = parse1[0];
    cuts1 = parse1[1];

    std::string beam_en;
    if(info1.find("1.161")!= std::string::npos) {beam_en = "1_161";}
    else if(info1.find("2.261")!= std::string::npos) {beam_en = "2_261";}
    else {beam_en = "4_461";}

    std::cout << "Analyzed beam en: " << beam_en << "\n";

    // histogram initialization
    TH1D* h1_theta_el[6];
    TH1D* h1_theta_prot[6];

    TH1D* range1_noFSI[6];
    TH1D* range1_FSI[6];
    TH1D* range2_noFSI[6];
    TH1D* range2_FSI[6];
    TH1D* range3_noFSI[6];
    TH1D* range3_FSI[6];

    TH1D* range1_data[6];
    TH1D* range2_data[6];
    TH1D* range3_data[6];

    for(int sect = 0; sect < 6; sect++) {

        h1_theta_el[sect] = (TH1D*)input1->Get(TString::Format("h1_Sect_%i_el_theta",sect));
        h1_theta_prot[sect] = (TH1D*)input1->Get(TString::Format("h1_Sect_%i_proton_theta",sect));

        /*
        h1_theta_el[sect]->Scale(1/(h1_theta_el[sect]->Integral(1,h1_theta_el[sect]->GetNbinsX())));
        h1_theta_prot[sect]->Scale(1/(h1_theta_prot[sect]->Integral(1,h1_theta_prot[sect]->GetNbinsX())));
        */
        range1_noFSI[sect] = (TH1D*)input2->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector%i_noFSI_prot_theta",sect));
        range1_noFSI[sect]->Rebin(2);
        range1_FSI[sect] = (TH1D*)input2->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector%i_FSI_prot_theta",sect));
        range2_noFSI[sect] = (TH1D*)input3->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector%i_noFSI_prot_theta",sect));
        range2_noFSI[sect]->Rebin(2);
        range2_FSI[sect] = (TH1D*)input3->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector%i_FSI_prot_theta",sect));
        range3_noFSI[sect] = (TH1D*)input4->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector%i_noFSI_prot_theta",sect));
        range3_noFSI[sect]->Rebin(2);
        range3_FSI[sect] = (TH1D*)input4->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector%i_FSI_prot_theta",sect));

        range1_data[sect] = (TH1D*)input5->Get(TString::Format("h1_InteractionEq0_NoQ4Weight_InSector%i_prot_theta",sect));
        range1_data[sect]->Rebin(2);
        range2_data[sect] = (TH1D*)input6->Get(TString::Format("h1_InteractionEq0_NoQ4Weight_InSector%i_prot_theta",sect));
        range2_data[sect]->Rebin(2);
        range3_data[sect] = (TH1D*)input7->Get(TString::Format("h1_InteractionEq0_NoQ4Weight_InSector%i_prot_theta",sect));
        range3_data[sect]->Rebin(2);

    }

    /*
    for( int i = 1; i < 6; i++) {
        range1_noFSI[0]->Add(range1_noFSI[i]);
        range1_FSI[0]->Add(range1_FSI[i]);
        range2_noFSI[0]->Add(range2_noFSI[i]);
        range2_FSI[0]->Add(range2_FSI[i]);
        range3_noFSI[0]->Add(range3_noFSI[i]);
        range3_FSI[0]->Add(range3_FSI[i]);

        range1_data[0]->Add(range1_data[i]);
        range2_data[0]->Add(range2_data[i]);
        range3_data[0]->Add(range3_data[i]);
    }
    */
    /*
    for(int i = 0; i < 6; i++) {
        range1_noFSI[i]->Scale(1/(range1_noFSI[i]->Integral(1,range1_noFSI[i]->GetNbinsX())));
        range2_noFSI[i]->Scale(1/(range2_noFSI[i]->Integral(1,range2_noFSI[i]->GetNbinsX())));
        range3_noFSI[i]->Scale(1/(range3_noFSI[i]->Integral(1,range3_noFSI[i]->GetNbinsX())));
        range1_data[i]->Scale(1/(range1_data[i]->Integral(1,range1_data[i]->GetNbinsX())));
        range2_data[i]->Scale(1/(range2_data[i]->Integral(1,range2_data[i]->GetNbinsX())));
        range3_data[i]->Scale(1/(range3_data[i]->Integral(1,range3_data[i]->GetNbinsX())));
    }
    */

    /*
    range1_FSI[0]->Scale(.01*1/(range1_FSI[0]->Integral(1,range1_FSI[0]->GetNbinsX())));
    range1_noFSI[0]->Scale(.01*1/(range1_noFSI[0]->Integral(1,range1_noFSI[0]->GetNbinsX())));
    range2_FSI[0]->Scale(.01*1/(range2_FSI[0]->Integral(1,range2_FSI[0]->GetNbinsX())));
    range2_noFSI[0]->Scale(.01*1/(range2_noFSI[0]->Integral(1,range2_noFSI[0]->GetNbinsX())));
    range3_FSI[0]->Scale(.01*1/(range3_FSI[0]->Integral(1,range3_FSI[0]->GetNbinsX())));
    range3_noFSI[0]->Scale(.01*1/(range3_noFSI[0]->Integral(1,range3_noFSI[0]->GetNbinsX())));


    range1_data[0]->Scale(.01*1/(range1_data[0]->Integral(1,range1_data[0]->GetNbinsX())));
    range2_data[0]->Scale(.01*1/(range2_data[0]->Integral(1,range2_data[0]->GetNbinsX())));
    range3_data[0]->Scale(.01*1/(range3_data[0]->Integral(1,range3_data[0]->GetNbinsX())));
        */

    const int color_options[6] = {kBlue, kAzure+10, kGreen-3, kViolet, kBlack, kRed};
    
    TCanvas* c;
    c = new TCanvas(TString::Format("c"), TString::Format("c"), 800, 600);
    // format the histograms
    h1_theta_el[0]->SetStats( 0); // get rid of the stats box that usually appears at the top right of plots
    h1_theta_el[0]->GetXaxis()->SetTitle("Electron Scattering Angle (Degrees)");
    h1_theta_el[0]->GetYaxis()->SetTitle("Number of Events");
    h1_theta_el[0]->GetXaxis()->CenterTitle( true);
    h1_theta_el[0]->GetYaxis()->CenterTitle( true);
    h1_theta_el[0]->SetTitle(TString(info1)+TString(cuts1));
    h1_theta_el[0]->GetXaxis()->SetRangeUser(18,61);

    for(int sect = 0; sect < 6; sect++) {
        h1_theta_el[sect]->SetLineColor(color_options[sect]);
        h1_theta_el[sect]->SetLineWidth(2);
        if(sect == 0) h1_theta_el[sect]->Draw("HIST");
        else h1_theta_el[sect]->Draw("HIST SAME");
    }
    
    // draw a legend for our plot
    TLegend *legend = new TLegend( 0.6, 0.725, 0.8, 0.925);
    for(int sect = 0; sect < 6; sect++) {
        legend->AddEntry( h1_theta_el[sect], TString::Format("Sector %i",sect+1));
        }
    legend->SetBorderSize( 0);
    legend->SetFillStyle( 0);
    legend->Draw();

    // crop the margins of the canvas
    c->SetLeftMargin( 0.14);
    c->SetBottomMargin( 0.14);
    c->Update();

    ////////////////////////////////////////////
    TCanvas* cp;
    cp = new TCanvas(TString::Format("cp"), TString::Format("cp"), 800, 600);
    // format the histograms
    h1_theta_prot[0]->Sumw2();
    h1_theta_prot[0]->SetStats( 0); // get rid of the stats box that usually appears at the top right of plots
    h1_theta_prot[0]->GetXaxis()->SetTitle("Proton Scattering Angle (Degrees)");
    h1_theta_prot[0]->GetYaxis()->SetTitle("Number of Events");
    h1_theta_prot[0]->GetXaxis()->SetRangeUser(10,140);
    h1_theta_prot[0]->GetXaxis()->CenterTitle( true);
    h1_theta_prot[0]->GetYaxis()->CenterTitle( true);
    h1_theta_prot[0]->SetTitle(TString(info1)+TString(cuts1));
    
    for(int sect = 0; sect < 6; sect++) {
        h1_theta_prot[sect]->SetLineColor(color_options[sect]);
        h1_theta_prot[sect]->SetLineWidth(2);
        if(sect == 0) h1_theta_prot[sect]->Draw("HIST");
        else h1_theta_prot[sect]->Draw("HIST SAME");
    }
    /*
        //range1_FSI[0]->SetLineColor(kRed);
        range1_noFSI[0]->SetLineColor(kBlack);
        //range2_FSI[0]->SetLineColor(kRed);
        range2_noFSI[0]->SetLineColor(kBlack);
        //range3_FSI[0]->SetLineColor(kRed);
        range3_noFSI[0]->SetLineColor(kBlack);


        //range1_FSI[0]->Draw("HIST SAME");
        range1_noFSI[0]->Draw("HIST SAME");
        //range2_FSI[0]->Draw("HIST SAME");
        range2_noFSI[0]->Draw("HIST SAME");
        //range3_FSI[0]->Draw("HIST SAME");
        range3_noFSI[0]->Draw("HIST SAME");
        

        range1_data[0]->SetLineStyle(kDashed);
        range2_data[0]->SetLineStyle(kDashed);
        range3_data[0]->SetLineStyle(kDashed);
        range1_data[0]->Draw("E SAME");
        range2_data[0]->Draw("E SAME");
        range3_data[0]->Draw("E SAME");
    */
    // draw a legend for our plot
    TLegend *legendp = new TLegend( 0.6, 0.725, 0.8, 0.925);
    for(int sect = 0; sect < 6; sect++) {
        legendp->AddEntry( h1_theta_prot[sect], TString::Format("Sector %i",sect));
        }
    legendp->SetBorderSize( 0);
    legendp->SetFillStyle( 0);
    legendp->Draw();

    // crop the margins of the canvas
    cp->SetLeftMargin( 0.14);
    cp->SetBottomMargin( 0.14);
    cp->Update();


/////////////////////////////////////////////////////////////
    TCanvas* c2;
    c2 = new TCanvas(TString::Format("c2"), TString::Format("c2"), 800, 600);
    
    for(int sect = 0; sect < 6; sect++) {
        range1_data[sect]->SetLineColor(color_options[sect]);
        range1_data[sect]->GetXaxis()->SetRangeUser(20,90);
        //range1_data[sect]->GetYaxis()->SetRangeUser(0,.35);
        range1_data[sect]->SetLineWidth(2);
        if(sect == 0) {range1_data[sect]->Draw("HIST");
        range1_data[sect]->GetXaxis()->SetTitle("Proton Theta");
        range1_data[sect]->SetTitle("Range 1");}
        else range1_data[sect]->Draw("HIST SAME");
    }
    
    // draw a legend for our plot
    TLegend *legend3 = new TLegend( 0.6, 0.725, 0.8, 0.925);
    for(int sect = 0; sect < 6; sect++) {
        legend3->AddEntry( range1_data[sect], TString::Format("Sector %i",sect+1));
        }
    legend3->SetBorderSize( 0);
    legend3->SetFillStyle( 0);
    legend3->Draw();

    // crop the margins of the canvas
    c2->SetLeftMargin( 0.14);
    c2->SetBottomMargin( 0.14);
    c2->Update();

        TCanvas* c3;
    c3 = new TCanvas(TString::Format("c3"), TString::Format("c3"), 800, 600);
    
    for(int sect = 0; sect < 6; sect++) {
        range2_data[sect]->SetLineColor(color_options[sect]);
        range2_data[sect]->GetXaxis()->SetRangeUser(20,90);
        //range2_data[sect]->GetYaxis()->SetRangeUser(0,.35);
        range2_data[sect]->SetLineWidth(2);
        if(sect == 0) {range2_data[sect]->Draw("HIST");
        range2_data[sect]->GetXaxis()->SetTitle("Proton Theta");
        range2_data[sect]->SetTitle("Range 2");}
        else range2_data[sect]->Draw("HIST SAME");
    }
    
    // draw a legend for our plot
    TLegend *legend4 = new TLegend( 0.6, 0.725, 0.8, 0.925);
    for(int sect = 0; sect < 6; sect++) {
        legend4->AddEntry( range2_data[sect], TString::Format("Sector %i",sect+1));
        }
    legend4->SetBorderSize( 0);
    legend4->SetFillStyle( 0);
    legend4->Draw();

    // crop the margins of the canvas
    c3->SetLeftMargin( 0.14);
    c3->SetBottomMargin( 0.14);
    c3->Update();

        TCanvas* c4;
    c4 = new TCanvas(TString::Format("c4"), TString::Format("c4"), 800, 600);
    
    for(int sect = 0; sect < 6; sect++) {
        range3_data[sect]->SetLineColor(color_options[sect]);
        range3_data[sect]->GetXaxis()->SetRangeUser(20,90);
        //range3_data[sect]->GetYaxis()->SetRangeUser(0,.35);
        range3_data[sect]->SetLineWidth(2);
        if(sect == 0) {range3_data[sect]->Draw("HIST");
        range3_data[sect]->GetXaxis()->SetTitle("Proton Theta");
        range3_data[sect]->SetTitle("Range 3");}
        else range3_data[sect]->Draw("HIST SAME");
    }
    
    // draw a legend for our plot
    TLegend *legend5 = new TLegend( 0.6, 0.725, 0.8, 0.925);
    for(int sect = 0; sect < 6; sect++) {
        legend5->AddEntry( range3_data[sect], TString::Format("Sector %i",sect+1));
        }
    legend5->SetBorderSize( 0);
    legend5->SetFillStyle( 0);
    legend5->Draw();

    // crop the margins of the canvas
    c4->SetLeftMargin( 0.14);
    c4->SetBottomMargin( 0.14);
    c4->Update();

     TCanvas* c5;
    c5 = new TCanvas(TString::Format("c5"), TString::Format("c5"), 800, 600);
    
    for(int sect = 0; sect < 6; sect++) {
        range1_noFSI[sect]->SetLineColor(color_options[sect]);
        range1_noFSI[sect]->GetXaxis()->SetRangeUser(20,90);
        //range1_noFSI[sect]->GetYaxis()->SetRangeUser(0,.35);
        range1_noFSI[sect]->SetLineWidth(2);
        if(sect == 0) {range1_noFSI[sect]->Draw("HIST");
        range1_noFSI[sect]->GetXaxis()->SetTitle("Proton Theta");
        range1_noFSI[sect]->SetTitle("Range 1");}
        else range1_noFSI[sect]->Draw("HIST SAME");
    }
    
    // draw a legend for our plot
    TLegend *legend8 = new TLegend( 0.6, 0.725, 0.8, 0.925);
    for(int sect = 0; sect < 6; sect++) {
        legend8->AddEntry( range1_noFSI[sect], TString::Format("Sector %i",sect+1));
        }
    legend8->SetBorderSize( 0);
    legend8->SetFillStyle( 0);
    legend8->Draw();

    // crop the margins of the canvas
    c5->SetLeftMargin( 0.14);
    c5->SetBottomMargin( 0.14);
    c5->Update();

        TCanvas* c6;
    c6 = new TCanvas(TString::Format("c6"), TString::Format("c6"), 800, 600);
    
    for(int sect = 0; sect < 6; sect++) {
        range2_noFSI[sect]->SetLineColor(color_options[sect]);
        range2_noFSI[sect]->GetXaxis()->SetRangeUser(20,90);
        //range2_noFSI[sect]->GetYaxis()->SetRangeUser(0,.35);
        range2_noFSI[sect]->SetLineWidth(2);
        if(sect == 0) {range2_noFSI[sect]->Draw("HIST");
        range2_noFSI[sect]->GetXaxis()->SetTitle("Proton Theta");
        range2_noFSI[sect]->SetTitle("Range 2");}
        else range2_noFSI[sect]->Draw("HIST SAME");
    }
    
    // draw a legend for our plot
    TLegend *legend6 = new TLegend( 0.6, 0.725, 0.8, 0.925);
    for(int sect = 0; sect < 6; sect++) {
        legend6->AddEntry( range2_noFSI[sect], TString::Format("Sector %i",sect+1));
        }
    legend6->SetBorderSize( 0);
    legend6->SetFillStyle( 0);
    legend6->Draw();

    // crop the margins of the canvas
    c6->SetLeftMargin( 0.14);
    c6->SetBottomMargin( 0.14);
    c6->Update();

        TCanvas* c7;
    c7= new TCanvas(TString::Format("c7"), TString::Format("c7"), 800, 600);
    
    for(int sect = 0; sect < 6; sect++) {
        range3_noFSI[sect]->SetLineColor(color_options[sect]);
        range3_noFSI[sect]->GetXaxis()->SetRangeUser(20,90);
        //range3_noFSI[sect]->GetYaxis()->SetRangeUser(0,.35);
        range3_noFSI[sect]->SetLineWidth(2);
        if(sect == 0) {range3_noFSI[sect]->Draw("HIST");
        range3_noFSI[sect]->GetXaxis()->SetTitle("Proton Theta");
        range3_noFSI[sect]->SetTitle("Range 3");}
        else range3_noFSI[sect]->Draw("HIST SAME");
    }
    
    // draw a legend for our plot
    TLegend *legend7 = new TLegend( 0.6, 0.725, 0.8, 0.925);
    for(int sect = 0; sect < 6; sect++) {
        legend7->AddEntry( range3_noFSI[sect], TString::Format("Sector %i",sect+1));
        }
    legend7->SetBorderSize( 0);
    legend7->SetFillStyle( 0);
    legend7->Draw();

    // crop the margins of the canvas
    c7->SetLeftMargin( 0.14);
    c7->SetBottomMargin( 0.14);
    c7->Update();

    
}
