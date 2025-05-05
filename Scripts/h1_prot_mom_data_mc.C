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

void h1_prot_mom_data_mc(std::string sim, std::string targ, std::string beamen, std::string range, std::string type){


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

    file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/"+sim+"/Excl_Range"+range+"_Genie_"+sim_num+"_"+targ+"_"+beamen+".root";
    file_name2 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ_nominal/"+flipped_target+"/Excl_Range"+range+"_Data__"+targ+"_"+beamen+".root";

    //ile_name2= "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/elec_momData__56Fe_4.461000.root";
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
    double beam_energy;
    if(info1.find("1.161")!= std::string::npos) {beam_en = "1_161";beam_energy=1.161;}
    else if(info1.find("2.261")!= std::string::npos) {beam_en = "2_261";beam_energy = 2.261;}
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
    TH1D* h1_protmom_mc_total;
    TH1D* h1_protmom_InteractionBreakDown_inSector_mc[4][6];
    TH1D* h1_protmom_mc_int[4];
    TH1D* h1_protmom_data[6];


	for (int i = 0; i < 4; i++) { // for all the interactions
	    for (int j = 0; j < 6; j++) { // for all the sectors
    	   // extract the histrograms
    	   h1_protmom_InteractionBreakDown_inSector_mc[i][j] = (TH1D*)input1->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", i+1, j));    
    	   h1_protmom_InteractionBreakDown_inSector_mc[i][j]->Rebin(40);
         //Add everything to the first sector
            if(i == 0 && j == 0) h1_protmom_mc_total = (TH1D*)h1_protmom_InteractionBreakDown_inSector_mc[i][j]->Clone();
            if(i != 0 ||  j != 0) h1_protmom_mc_total->Add(h1_protmom_InteractionBreakDown_inSector_mc[i][j]);
	        if(j == 0) h1_protmom_mc_int[i] = (TH1D*)h1_protmom_InteractionBreakDown_inSector_mc[i][j]->Clone();
		    if(j != 0) h1_protmom_mc_int[i]->Add(h1_protmom_InteractionBreakDown_inSector_mc[i][j]);
	   }
	}

    for (int i = 0; i < 6; i++) { // for all the sectors
		h1_protmom_data[i] = (TH1D*)input2->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", i));
      h1_protmom_data[i]->Rebin(40);
    }

    // compile all the sectors into one histogram
    for( int i = 1; i < 6; i++) { 
       h1_protmom_data[0]->Add( h1_protmom_data[i]); 
    }

    UniversalE4vFunction(h1_protmom_mc_total,  sim_label, target, beam_en, TString(info1)+TString(cuts1));
    PrettyDoubleXSecPlot(h1_protmom_mc_total, 2, beam_energy, 4, false);
    for(int i = 0; i < 4; i++) {
      UniversalE4vFunction(h1_protmom_mc_int[i], sim_label, target, beam_en, TString(info1)+TString(cuts1));
      PrettyDoubleXSecPlot(h1_protmom_mc_int[i], 2, beam_energy, 4, false);
    }
    UniversalE4vFunction(h1_protmom_data[0],  "Pinned Data", target, beam_en, TString(info2));
    

    // create a canvas on which to draw the histograms
    
    double max = 1.1*h1_protmom_mc_total->GetMaximum();

    const int color_options[4] = {kBlue, kAzure+10, kGreen-3, kViolet};

    TCanvas* c3;
    c3 = new TCanvas(TString::Format("c3"), TString::Format("c3"), 1000, 1000);
    // format the histograms
    h1_protmom_data[0]->Sumw2();
    h1_protmom_data[0]->SetStats( 0); // get rid of the stats box that usually appears at the top right of plots
/*    h1_protmom_data[0]->GetXaxis()->SetTitle("Proton Momentum (MeV)");
    h1_protmom_data[0]->GetYaxis()->SetTitle("Events");
    h1_protmom_data[0]->GetXaxis()->CenterTitle( true);
    h1_protmom_data[0]->GetYaxis()->CenterTitle( true);
    h1_protmom_data[0]->SetTitle(TString(info2)+TString(cuts2));*/
    h1_protmom_data[0]->SetMarkerStyle(kFullCircle);
    h1_protmom_data[0]->SetMarkerSize(1.5);
    h1_protmom_data[0]->SetMarkerColor(kBlack);
    h1_protmom_data[0]->GetYaxis()->SetRangeUser(0,max);

    h1_protmom_mc_total->SetLineColor(kBlack);
    h1_protmom_mc_total->GetYaxis()->SetRangeUser(0, max);
    h1_protmom_mc_total->GetXaxis()->SetRangeUser(.4,2.0);
    h1_protmom_mc_total->GetXaxis()->SetTitle("Proton Momentum (GeV)");

    h1_protmom_mc_total->Draw("HIST E"); 

    for(int i = 0; i < 4; i++) {
    	h1_protmom_mc_int[i]->SetLineColor(color_options[i]);
	   h1_protmom_mc_int[i]->GetYaxis()->SetRangeUser(0,max);
	   h1_protmom_mc_int[i]->Draw("HIST SAME");
    }

  
    h1_protmom_data[0]->Draw("E P SAME");
	

    // draw a legend for our plot
    TLegend *legend = new TLegend( .82,.65,.99,.85);
    legend->AddEntry( h1_protmom_mc_total, sim.c_str());
    legend->AddEntry( h1_protmom_data[0], "CLAS data");
    legend->AddEntry( h1_protmom_mc_int[0],"QE");
    legend->AddEntry( h1_protmom_mc_int[1],"MEC");
    legend->AddEntry( h1_protmom_mc_int[2],"RES");
    legend->AddEntry( h1_protmom_mc_int[3],"DIS");
    legend->SetBorderSize( 0);
    legend->SetFillStyle( 0);
    legend->Draw();


    // crop the margins of the canvas
   c3->SetLeftMargin( 0.2);
    c3->SetBottomMargin( 0.2);
    c3->SetRightMargin( 0.2);
    c3->Update();

//    c3->SaveAs(TString::Format("ProtMom_%s_%s_%s.pdf",targ.c_str(), beamen.c_str(), range.c_str()));

    
}
