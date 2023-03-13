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
//#include "myFunctions.cpp"

void h1_ThetaPQ_FSI( std::string file_name){

    // declare variables that will be used in the plotting/formatting of histograms and file names
    std::string info ("");
    std::string cuts ("");

    // import the ROOT data file from the output of doing ./genie_analysis in the e4nu directory
    TFile *input1 = TFile::Open( TString( file_name));

    // Grab the TList in the ROOT File for info on the run
    TList *Run_Info = (TList*)input1->Get("Run_Info");

    std::vector<std::string> parse = parse_file(Run_Info);

    info = parse[0];
    cuts = parse[1];

    // histogram initialization
    TH1F* noFSI[6];
    TH1F* FSI[6];

    TH1F* t_noFSI[6];
    TH1F* t_FSI[6];

    
    noFSI[0] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_0_noFSI_ThetaPQ"));
    noFSI[1] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_1_noFSI_ThetaPQ"));
    noFSI[2] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_2_noFSI_ThetaPQ"));
    noFSI[3] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_3_noFSI_ThetaPQ"));
    noFSI[4] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_4_noFSI_ThetaPQ"));
    noFSI[5] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_5_noFSI_ThetaPQ"));

    FSI[0] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_0_FSI_ThetaPQ"));
    FSI[1] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_1_FSI_ThetaPQ"));
    FSI[2] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_2_FSI_ThetaPQ"));
    FSI[3] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_3_FSI_ThetaPQ"));
    FSI[4] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_4_FSI_ThetaPQ"));
    FSI[5] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_5_FSI_ThetaPQ"));

    t_noFSI[0] = (TH1F*)input1->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector0_noFSI_prot_theta"));
    t_noFSI[1] = (TH1F*)input1->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector1_noFSI_prot_theta"));
    t_noFSI[2] = (TH1F*)input1->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector2_noFSI_prot_theta"));
    t_noFSI[3] = (TH1F*)input1->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector3_noFSI_prot_theta"));
    t_noFSI[4] = (TH1F*)input1->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector4_noFSI_prot_theta"));
    t_noFSI[5] = (TH1F*)input1->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector5_noFSI_prot_theta"));

    t_FSI[0] = (TH1F*)input1->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector0_FSI_prot_theta"));
    t_FSI[1] = (TH1F*)input1->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector1_FSI_prot_theta"));
    t_FSI[2] = (TH1F*)input1->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector2_FSI_prot_theta"));
    t_FSI[3] = (TH1F*)input1->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector3_FSI_prot_theta"));
    t_FSI[4] = (TH1F*)input1->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector4_FSI_prot_theta"));
    t_FSI[5] = (TH1F*)input1->Get(TString::Format("h1_InteractionEq1_NoQ4Weight_InSector5_FSI_prot_theta"));

    

    // compile all the histograms into the four interaction types (QE, MEC, RES, and DIS for quasi-elastic,
    // mesonic current, resonance, and deep inelastic scattering, respectively.
    for( int i = 1; i < 6; i++) {
        noFSI[0]->Add(noFSI[i]);
        FSI[0]->Add(FSI[i]);


        t_noFSI[0]->Add(t_noFSI[i]);
        t_FSI[0]->Add(t_FSI[i]);
    }

    // create a canvas on which to draw the histograms
    TCanvas* c;
    c = new TCanvas(TString::Format("c"), TString::Format("c"), 800, 600);

    // initialize things such as color options that will be used in plotting the histograms below
    const int color_options[5] = {kBlue, kAzure+10, kGreen-3, kViolet, kBlue+2};
    const char * draw_options[5] = {"HIST","HIST SAME","HIST SAME", "HIST SAME","HIST SAME"};
    const char * draw_options2[5] = {"E SAME", "E SAME","E SAME", "E SAME","E SAME"};

    double hist_max = 0.;
    // format the histograms and then make them

    FSI[0]->Sumw2();
    noFSI[0]->Sumw2();
    FSI[0]->SetStats(0);
    noFSI[0]->SetStats(0);

    noFSI[0]->SetLineColor(kRed);
    FSI[0]->SetLineColor(kBlack);

    noFSI[0]->GetXaxis()->SetTitle("ThetaPQ (Degrees)");
    noFSI[0]->GetYaxis()->SetTitle("Events");
    noFSI[0]->GetXaxis()->CenterTitle( true);
    noFSI[0]->GetYaxis()->CenterTitle( true);

    noFSI[0]->SetTitle(TString(info)+TString(cuts));

    t_FSI[0]->Sumw2();
    t_noFSI[0]->Sumw2();
    t_FSI[0]->SetStats(0);
    t_noFSI[0]->SetStats(0);

    t_noFSI[0]->SetLineColor(kBlack);
    t_FSI[0]->SetLineColor(kRed);

    t_noFSI[0]->GetXaxis()->SetTitle("Proton Theta (Degrees)");
    t_noFSI[0]->GetYaxis()->SetTitle("Events");
    t_noFSI[0]->GetXaxis()->CenterTitle( true);
    t_noFSI[0]->GetYaxis()->CenterTitle( true);

    t_noFSI[0]->SetTitle(TString(info)+TString(cuts));

    // take the maximum of the four interactions to use later in plotting
    if (noFSI[0]->GetMaximum() > hist_max)  hist_max = noFSI[0]->GetMaximum(); 
    if (FSI[0]->GetMaximum() > hist_max) hist_max = FSI[0]->GetMaximum();


    if (t_noFSI[0]->GetMaximum() > hist_max)  hist_max = t_noFSI[0]->GetMaximum(); 
    if (t_FSI[0]->GetMaximum() > hist_max) hist_max = t_FSI[0]->GetMaximum();
    
    noFSI[0]->GetYaxis()->SetRangeUser(0, hist_max*1.1);
    t_noFSI[0]->GetYaxis()->SetRangeUser(0, hist_max*1.1);

    noFSI[0]->Draw("E hist");
    FSI[0]->Draw("E hist same");

    // crop the margins of the canvas
    c->SetLeftMargin( 0.14);
    c->SetBottomMargin( 0.14);
    c->Update();

    // create and draw a legend for our histograms
    TLegend *legend = new TLegend( 0.7, 0.655, 1.2, 0.8);
    legend->AddEntry( noFSI[0],"QE FSI","l");
    legend->AddEntry( FSI[0],"QE no FSI","l");
    legend->SetBorderSize( 0);
    legend->SetFillStyle( 0);
    legend->Draw();
    
    TCanvas* c2;
    c2 = new TCanvas(TString::Format("c2"), TString::Format("c2"), 800, 600);
    //t_noFSI[0]->Rebin(2);
    //t_FSI[0]->Rebin(2);
    t_noFSI[0]->Draw("E hist");
    t_FSI[0]->Draw("E hist same");

    // crop the margins of the canvas
    c2->SetLeftMargin( 0.14);
    c2->SetBottomMargin( 0.14);
    c2->Update();

    // create and draw a legend for our histograms
    TLegend *legend2 = new TLegend( 0.7, 0.655, 1.2, 0.8);
    legend2->AddEntry( t_noFSI[0],"QE no FSI","l");
    legend2->AddEntry( t_FSI[0],"QE FSI","l");
    legend2->SetBorderSize( 0);
    legend2->SetFillStyle( 0);
    legend2->Draw();


    double num_noFSI_events = FSI[0]->Integral(1,10);
    double num_FSI_events = noFSI[0]->Integral(1,10);

    double num_t_noFSI_events = t_noFSI[0]->Integral(30,55);
    double num_t_FSI_events = t_FSI[0]->Integral(30,55);

    cout << "// --- PROGRAM OUTPUT ------------------------------------------------------" << endl;
    cout << "There are " << num_noFSI_events << " QE no FSI events in this histogram." << endl;
    cout << "There are " << num_FSI_events << " QE FSI events in this histogram." << endl;
    cout << "Contamination = " << double(num_FSI_events/(num_noFSI_events + num_FSI_events)) << "\n";
 

    cout << "There are " << num_t_noFSI_events << " QE no FSI events in this histogram." << endl;
    cout << "There are " << num_t_FSI_events << " QE FSI events in this histogram." << endl;
    cout << "Contamination = " << double(num_t_FSI_events/(num_t_noFSI_events + num_t_FSI_events)) << "\n";
    cout << "// -------------------------------------------------------------------------" << endl << endl; // separate program output
}
