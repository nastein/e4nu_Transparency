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
//#include "myFunctions.cpp"
#include "parse_file.C"

void h1_ThetaPQ_data_mc( int range){

        // declare variables that will be used in the plotting/formatting of histograms and file names
    std::string info1 ("");
    std::string cuts1 ("");
    std::string info2 ("");
    std::string cuts2 ("");

    // import the ROOT data file from the output of doing ./genie_analysis in the e4nu directory
    std::string file_name1;
    std::string file_name2;
 
    file_name2 = "../Analyze_data/test2Data__C12_2.261000.root";
    file_name1 = "../Analyze_data/test2Genie_1_C12_2.261000.root";

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


    // histogram initialization
    TH1F* h1_Emiss_mc_total;
    TH1F* h1_Emiss_InteractionBreakDown_inSector_mc[4][6];
    TH1F* h1_Emiss_data[6];


	for (int i = 0; i < 4; i++) { // for all the interactions
	    for (int j = 0; j < 6; j++) { // for all the sectors
    		// extract the histrograms
    		h1_Emiss_InteractionBreakDown_inSector_mc[i][j] = (TH1F*)input1->Get(TString::Format("h1_Int%i_Sect_%i_ThetaPQ", i+1, j));    
    	    //Add everything to the first sector
            if(i == 0 && j == 0) h1_Emiss_mc_total = (TH1F*)h1_Emiss_InteractionBreakDown_inSector_mc[i][j]->Clone();
            else h1_Emiss_mc_total->Add(h1_Emiss_InteractionBreakDown_inSector_mc[i][j]);
	    
	   }
	}

    for (int i = 0; i < 6; i++) { // for all the sectors
		h1_Emiss_data[i] = (TH1F*)input2->Get( TString::Format("h1_Int0_Sect_%i_ThetaPQ", i));
    }

    // compile all the sectors into one histogram
    for( int i = 1; i < 6; i++) { 
       h1_Emiss_data[0]->Add( h1_Emiss_data[i]); 
    }

    double norm = h1_Emiss_data[0]->Integral()/h1_Emiss_mc_total->Integral();
    std::cout << "normalizing factor = " << norm << "\n";
    h1_Emiss_mc_total->Scale(norm);


    // create a canvas on which to draw the histograms
    

    const int color_options[4] = {kBlue, kAzure+10, kGreen-3, kViolet};

    TCanvas* c;
    c = new TCanvas(TString::Format("c"), TString::Format("c"), 800, 600);
    // format the histograms
    h1_Emiss_data[0]->Sumw2();
    h1_Emiss_data[0]->SetStats( 0); // get rid of the stats box that usually appears at the top right of plots
    h1_Emiss_data[0]->GetXaxis()->SetTitle("ThetaPQ (Degrees)");
    h1_Emiss_data[0]->GetYaxis()->SetTitle("Events");
    h1_Emiss_data[0]->GetXaxis()->CenterTitle( true);
    h1_Emiss_data[0]->GetYaxis()->CenterTitle( true);
    h1_Emiss_data[0]->SetTitle(TString(info2)+TString(cuts2));
    h1_Emiss_data[0]->SetMarkerStyle(2);
    h1_Emiss_data[0]->SetMarkerColor(kBlack);
    
    h1_Emiss_mc_total->SetLineColor(kRed);
    h1_Emiss_data[0]->Draw("HIST E");
    h1_Emiss_mc_total->Draw("SAME");
    
    // draw a legend for our plot
    TLegend *legend = new TLegend( 0.2, 0.725, 0.35, 0.825);
    legend->AddEntry( h1_Emiss_mc_total, "SuSAv2");
    legend->AddEntry( h1_Emiss_data[0], "CLAS data");
    legend->SetBorderSize( 0);
    legend->SetFillStyle( 0);
    legend->Draw();

    // crop the margins of the canvas
    c->SetLeftMargin( 0.14);
    c->SetBottomMargin( 0.14);
    c->Update();


    
}
