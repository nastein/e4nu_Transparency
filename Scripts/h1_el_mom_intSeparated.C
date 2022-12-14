// File to plot histograms of the electron momentum for a simulation. The histograms generated 
// with this macro are separated into the different interaction components: quasi-elastic (QE),
// mesonic current (MEC), resonance (RES), and deep inelastic scattering (DIS). This functionality
// is indicated by "separated" being in the macro's file name. 
//
// Author: Jacob Smith (smithja)
// Creation Date: 09/09/2021
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

void h1_el_mom_intSeparated( std::string file_name){

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
    TH1F* h1_el_momentum[24];

    h1_el_momentum[0] = (TH1F*)input1->Get(TString::Format("h1_1_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__5"));
    h1_el_momentum[1] = (TH1F*)input1->Get(TString::Format("h1_2_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__5"));
    h1_el_momentum[2] = (TH1F*)input1->Get(TString::Format("h1_3_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__5"));
    h1_el_momentum[3] = (TH1F*)input1->Get(TString::Format("h1_4_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__5"));

    h1_el_momentum[4] = (TH1F*)input1->Get(TString::Format("h1_1_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__4"));
    h1_el_momentum[5] = (TH1F*)input1->Get(TString::Format("h1_2_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__4"));
    h1_el_momentum[6] = (TH1F*)input1->Get(TString::Format("h1_3_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__4"));
    h1_el_momentum[7] = (TH1F*)input1->Get(TString::Format("h1_4_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__4"));

    h1_el_momentum[8] = (TH1F*)input1->Get(TString::Format("h1_1_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__3"));
    h1_el_momentum[9] = (TH1F*)input1->Get(TString::Format("h1_2_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__3"));
    h1_el_momentum[10] = (TH1F*)input1->Get(TString::Format("h1_3_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__3"));
    h1_el_momentum[11] = (TH1F*)input1->Get(TString::Format("h1_4_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__3"));

    h1_el_momentum[12] = (TH1F*)input1->Get(TString::Format("h1_1_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__2"));
    h1_el_momentum[13] = (TH1F*)input1->Get(TString::Format("h1_2_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__2"));
    h1_el_momentum[14] = (TH1F*)input1->Get(TString::Format("h1_3_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__2"));
    h1_el_momentum[15] = (TH1F*)input1->Get(TString::Format("h1_4_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__2"));

    h1_el_momentum[16] = (TH1F*)input1->Get(TString::Format("h1_1_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__1"));
    h1_el_momentum[17] = (TH1F*)input1->Get(TString::Format("h1_2_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__1"));
    h1_el_momentum[18] = (TH1F*)input1->Get(TString::Format("h1_3_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__1"));
    h1_el_momentum[19] = (TH1F*)input1->Get(TString::Format("h1_4_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__1"));

    h1_el_momentum[20] = (TH1F*)input1->Get(TString::Format("h1_1_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__0"));
    h1_el_momentum[21] = (TH1F*)input1->Get(TString::Format("h1_2_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__0"));
    h1_el_momentum[22] = (TH1F*)input1->Get(TString::Format("h1_3_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__0"));
    h1_el_momentum[23] = (TH1F*)input1->Get(TString::Format("h1_4_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__0"));

    // compile all the histograms into the four interaction types (QE, MEC, RES, and DIS for quasi-elastic,
    // mesonic current, resonance, and deep inelastic scattering, respectively.
    for( int i = 1; i < 6; i++) {
        h1_el_momentum[20]->Add(h1_el_momentum[20-(4*i)]);
	h1_el_momentum[21]->Add(h1_el_momentum[21-(4*i)]); 
	h1_el_momentum[22]->Add(h1_el_momentum[22-(4*i)]); 
	h1_el_momentum[23]->Add(h1_el_momentum[23-(4*i)]); 
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
    for( int i = 20; i < 24; i++){
	// formatting statements
        h1_el_momentum[i]->Sumw2();
    //    h1_el_momentum[i]->Rebin( 25);
//        h1_el_momentum[i]->Scale( 1./h1_el_momentum[i]->Integral(),"width"); // normalize the histogram to 1
        h1_el_momentum[i]->SetStats( 0); // get rid of the stats box that usually appears at the top right of plots
        h1_el_momentum[i]->SetLineColor( color_options[i-20]);
        h1_el_momentum[i]->GetXaxis()->SetTitle("Electron Momentum [GeV/c]");
        h1_el_momentum[i]->GetYaxis()->SetTitle("Events");
      //  h1_el_momentum[i]->GetXaxis()->SetRangeUser( 0, 4);
        h1_el_momentum[i]->GetXaxis()->CenterTitle( true);
        h1_el_momentum[i]->GetYaxis()->CenterTitle( true);
//        h1_el_momentum[i]->GetXaxis()->SetTitleSize( 0.06);
//        h1_el_momentum[i]->GetYaxis()->SetTitleSize( 0.06);


        h1_el_momentum[i]->SetTitle(TString(info)+TString(cuts)); 
    
        // take the maximum of the four interactions to use later in plotting
        if (h1_el_momentum[i]->GetMaximum() > hist_max) { hist_max = h1_el_momentum[i]->GetMaximum(); }
    }

    // draw the histograms
    for( int i = 20; i < 24; i++){
	h1_el_momentum[i]->GetYaxis()->SetRangeUser( 0, hist_max*1.1); // smithja: hist_max mult. by 1.1 to give the graph some head room
        h1_el_momentum[i]->Draw( draw_options[i-20]);
        h1_el_momentum[i]->Draw( draw_options2[i-20]);
    }

    // crop the margins of the canvas
    c->SetLeftMargin( 0.14);
    c->SetBottomMargin( 0.14);
    c->Update();

    // create and draw a legend for our histograms
    TLegend *legend = new TLegend( 0.7, 0.655, 1.2, 0.8);
    legend->AddEntry( h1_el_momentum[20],"QE","l");
    legend->AddEntry( h1_el_momentum[21],"MEC","l");
    legend->AddEntry( h1_el_momentum[22],"RES","l");
    legend->AddEntry( h1_el_momentum[23],"DIS","l");
    legend->SetBorderSize( 0);
    legend->SetFillStyle( 0);
    legend->Draw();

    // save this histogram as a PDF file
    std::string save_file_path ("invalid");
    save_file_path = "../output2/h1_el_mom_intSeparated/"+TString(info)+TString(cuts)+"MottXSecEq1.pdf"; 
    
    //c->SaveAs( TString::Format("%s", save_file_path.c_str()));

    // smithja: this section of code integrates the distributions and prints
    //          it to the screen
    int num_QE_events = h1_el_momentum[20]->Integral();
    int num_MEC_events = h1_el_momentum[21]->Integral();
    int num_RES_events = h1_el_momentum[22]->Integral();
    int num_DIS_events = h1_el_momentum[23]->Integral();
    int num_events = num_QE_events + num_MEC_events + num_RES_events + num_DIS_events;

    cout << "// --- PROGRAM OUTPUT ------------------------------------------------------" << endl;
    cout << "There are " << num_QE_events << " many QE events in this histogram." << endl;
    cout << "There are " << num_MEC_events << " many MEC events in this histogram." << endl;
    cout << "There are " << num_RES_events << " many RES events in this histogram." << endl;
    cout << "There are " << num_DIS_events << " many DIS events in this histogram." << endl;
    cout << "There are " << num_events << " many total events in the h1_el_mom_insSeparated histogram." << endl;
    cout << "// -------------------------------------------------------------------------" << endl << endl; // separate program output
}
