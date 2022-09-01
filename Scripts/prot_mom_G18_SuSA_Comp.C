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

#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
//#include "myFunctions.cpp"
#include "parse_file.C"

void h1_prot_mom( int range){

        // declare variables that will be used in the plotting/formatting of histograms and file names
    std::string info1 ("");
    std::string cuts1 ("");
    std::string info2 ("");
    std::string cuts2 ("");

    // import the ROOT data file from the output of doing ./genie_analysis in the e4nu directory
    std::string G18_mc[3];
    std::string SuSA_mc[3];

    
    G18_mc[0] = "/genie/app/users/gchamber/e4nu_2022/e4nu/output";
    G18_mc[1] = "/genie/app/users/gchamber/e4nu_2022/e4nu/output";
    G18_mc[2] = "/genie/app/users/gchamber/e4nu_2022/e4nu/output";

    SuSA_mc[0] = "/genie/app/users/gchamber/e4nu_2022/e4nu/output";
    SuSA_mc[1] = "/genie/app/users/gchamber/e4nu_2022/e4nu/output";
    SuSA_mc[2] = "/genie/app/users/gchamber/e4nu_2022/e4nu/output";


    TFile *G18[3]; = TFile::Open( TString(file_name1));
    TFile *SuSA[3];

    for(int i = 0; i < 3; i++) {
	G18[i]  = TFile::Open( TString(G18_mc[i]));
        SuSA[i] = TFile::Open( TString(SuSA_mc[i]));
     }
    // Grab the TList in the ROOT File for info on the run
    TList *Run_Info1 = (TList*)input1->Get("Run_Info");
    TList *Run_Info2 = (TList*)input2->Get("Run_Info");

    std::vector<std::string> parse1 = parse_file(Run_Info1);
    std::vector<std::string> parse2 = parse_file(Run_Info2);

    info1 = parse1[0];
    cuts1 = parse1[1];
    info2 = parse2[0];
    cuts2 = parse2[1];

    std::string run_type1 = std::string(((TNamed*)Run_Info1->FindObject("Run type"))->GetTitle());
    std::string run_type2 = std::string(((TNamed*)Run_Info2->FindObject("Run type"))->GetTitle());

    // declare variables that will be used in the plotting/formatting of histograms and file names
    std::string target ("invalid");
    std::string target_plot ("invalid");
    std::string beam_energy ("invalid");
    std::string beam_energy_plot ("invalid");
    std::string elSectors ("invalid");
    std::string elSectors_plot ("invalid");
    std::string deltaPhiEl ("invalid");
    std::string thetaEl_lb ("invalid");
    std::string thetaEl_ub ("invalid");
    std::string elMom_lb ("invalid");
    std::string elMom_lb_plot ("invalid");
    std::string protSectors ("invalid");
    std::string protSectors_plot ("invalid");
    std::string deltaPhiProt ("invalid");
    std::string thetaProt_lb ("invalid");
    std::string thetaProt_ub ("invalid");
    std::string protMom_lb ("invalid");
    std::string protMom_lb_plot ("invalid");

    // histogram initialization
    TH1F* prot_mom_G[6][3];
    TH1F* prot_mom_InteractionBreakDown_inSector_G[3][6][4];

    TH1F* prot_mom_SuSA[6][3];
    TH1F* prot_mom_InteractionBreakDown_inSector_SuSA[3][6][4];


    //For G18
    for( int k = 0; k < 3; k++ ) {	
       for (int i = 0; i < 6; i++) { // for all the sectors
	    for (int j = 0; j < 4; j++) { // for all the interactions
		// extract the histrograms
		prot_mom_InteractionBreakDown_inSector_G[k][i][j] = (TH1F*)G18[k]->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", j, i));
	    
	        // compile the histograms by interaction, but not by sector; this is done later because it must be done for both GENIE MC and CLAS data
	        if (j == 0) { continue; } // do not add the first interaction to itself; we are adding everything to the first interaction histogram
	    	prot_mom_InteractionBreakDown_inSector_G[k][i][0]->Add( prot_mom_InteractionBreakDown_inSector_G[k][i][j]);
	    }
	    // alias the interaction compiled histogram as the h1_prot_momentum array.
	    prot_mom_G[i][k] = prot_mom_InteractionBreakDown_inSector_G[k][i][0];
	}
	
    }


    //For SuSA v2
    for( int k = 0; k < 3; k++ ) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			 prot_mom_InteractionBreakDown_inSector_SuSA[k][i][j] = (TH1F*)SuSA[k]->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", j, i));
			 if (j == 0) { continue; }
                         prot_mom_InteractionBreakDown_inSector_SuSA[k][i][0]->Add( prot_mom_InteractionBreakDown_inSector_SuSA[k][i][j]);
		}
		prot_mom_SuSA[i][k] = prot_mom_InteractionBreakDown_inSector_SuSA[k][i][0];
	}
    }

    // compile all the sectors into one histogram
    for(int k = 0; k < 3; k++ ) {
    	for( int i = 1; i < 6; i++) { 
		prot_mom_G[0][k]->Add(prot_mom_G[i][k]); 
		prot_mom_SuSA[0][k]->Add(prot_mom_SuSA[i][k]);
    	}
    }

    // create a canvas on which to draw the histograms
    TCanvas* c;
    c = new TCanvas(TString::Format("c"), TString::Format("c"), 800, 600);

    // format the histograms
    for(int k = 0; k < 3; k++) { 
    	prot_mom_G[0]->Sumw2();
    	prot_mom_G[0]->Rebin( 25);

    	prot_mom_G[0]->SetStats( 0); // get rid of the stats box that usually appears at the top right of plots
    	prot_mom_G[0]->GetXaxis()->SetTitle("Proton Momentum [GeV/c]");
   	prot_mom_G[0]->GetYaxis()->SetTitle("Events");
    	prot_mom_G[0]->GetXaxis()->SetRangeUser( 0, 3);
    	h1_prot_momentum_mc[0]->GetXaxis()->CenterTitle( true);
   	h1_prot_momentum_mc[0]->GetYaxis()->CenterTitle( true);
    	h1_prot_momentum_mc[0]->SetTitle(TString(info1)+TString(cuts1));

//    h1_prot_momentum[0]->GetXaxis()->SetTitleSize( 0.06);
//    h1_prot_momentum[0]->GetYaxis()->SetTitleSize( 0.06);
    
    	h1_prot_momentum_mc[0]->Draw("HIST E");
    	h1_prot_momentum_data[0]->Draw("E SAME");
    }
        const double leg_x1 = 0.75; // x-axis lower bound for the legend
        const double leg_x2 = 0.88; // x-axis upper bound for the legend
        const double leg_y1 = 0.74; // y-axis lower bound for the legend
        const double leg_y2 = 0.875; // y-axis upper bound for the legend


    TLegend *legend = new TLegend(leg_x1,leg_y1,leg_x2,leg_y2);
    //TLegend *legend = new TLegend( 0.2, 0.725, 0.35, 0.825);
    legend->AddEntry( h1_prot_momentum_mc[0], "GENIE");
    legend->AddEntry( h1_prot_momentum_data[0], "CLAS");
    legend->SetBorderSize( 0);
    legend->SetFillStyle( 0);
    legend->Draw();


    // crop the margins of the canvas
    c->SetLeftMargin( 0.14);
    c->SetBottomMargin( 0.14);
    c->Update();

    // save this histogram as a PDF file
    std::string save_file_path ("invalid");
    save_file_path = "../output2/Analysis17/h1_prot_mom/"+TString(info1)+TString(cuts1); 
    //TFile *f = new TFile(TString(save_file_path),"RECREATE");
    //cout << "File saved at: " << save_file_path << "\n";
    //h1_prot_momentum[0]->Write();
    //f->Close();
    c->SaveAs(TString(save_file_path)+".pdf");
    // smithja: this section of code integrates the distribution and prints it to the screen
    /*
    int num_events = h1_prot_momentum[0]->Integral();

    cout << "// --- PROGRAM OUTPUT ------------------------------------------------------" << endl;
    cout << "There are " << num_events << " many events in the h1_prot_mom histogram." << endl;
    cout << "// -------------------------------------------------------------------------" << endl << endl; // separate program output
    */
}
