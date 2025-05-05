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

void h1_el_mom_data_mc(std::string sim, std::string targ, std::string beamen, std::string range, std::string type){


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
    if(sim == "SuSAv2") {sim_label = FSIModelsToLabels["SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"]; sim_num = "1";}
    if(sim == "SF") {sim_label = "SF"; sim_num = "2";}

    std::string flipped_target;
    if(targ == "56Fe") flipped_target = "Fe56";
    if(targ == "4He") flipped_target = "He4";
    if(targ == "C12") flipped_target = "C12";

    double beam_energy;
    if(beamen == "2.261000") beam_energy = 2.261;
    if(beamen == "4.461000") beam_energy = 4.461;
    
    //Use these to demonstrate where we do electron momentum cuts
    file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/Electron_momentum/Electron_mom_Range"+range+"_Genie_"+sim_num+"_"+targ+"_"+beamen+".root";
    file_name2 = "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/Electron_momentum/Electron_mom_Range"+range+"_Data__"+targ+"_"+beamen+".root";

    //file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/SuSAv2/Excl_Range"+range+"_Genie_1_"+targ+"_"+beamen+".root";
    //file_name2 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Data_ThetaPQ/C12/Excl_Range"+range+"_Data__"+targ+"_"+beamen+".root";
    //file_name3 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/SF/Excl_Range"+range+"_Genie_1_"+targ+"_"+beamen+".root";

    //file_name2= "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/elec_momData__56Fe_4.461000.root";
    //file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/elec_momGenie_1_56Fe_4.461000.root";

    TFile *input1 = TFile::Open( TString(file_name1));
    TFile *input2 = TFile::Open( TString(file_name2));
    //TFile *input3 = TFile::Open( TString(file_name3));

    // Grab the TList in the ROOT File for info on the run
    TList *Run_Info1 = (TList*)input1->Get("Run_Info");
    TList *Run_Info2 = (TList*)input2->Get("Run_Info");

    std::vector<std::string> parse1 = parse_file(Run_Info1);
    std::vector<std::string> parse2 = parse_file(Run_Info2);

    info1 = parse1[0];
    cuts1 = parse1[1];
    info2 = parse2[0];
    cuts2 = parse2[1];

      std::vector<int> sectors = {};

    std::string beam_en;
    if(info1.find("1.161")!= std::string::npos) {beam_en = "1_161";}
    else if(info1.find("2.261")!= std::string::npos) {beam_en = "2_261";}
    else {beam_en = "4_461";}

    std::string target;
    if(info1.find("C12")!= std::string::npos) {target = "12C";
	if (beam_en == "2_261") {
	   if (range == "1") {
		sectors.push_back(0); sectors.push_back(1); sectors.push_back(5);
	   }
	   if (range == "2") {
                sectors.push_back(0); sectors.push_back(1); sectors.push_back(2); sectors.push_back(3); sectors.push_back(5);
           }
	   if (range == "3") {
                sectors.push_back(0); sectors.push_back(2); sectors.push_back(3);
           }

	}
	if (beam_en == "4_461") {sectors.push_back(0); sectors.push_back(1); sectors.push_back(4);}
	
    }
    else if(info1.find("4He")!= std::string::npos) {target = "4He";
	if (beam_en == "2_261") {
           if (range == "1") {
                sectors.push_back(0); sectors.push_back(3); sectors.push_back(5);
           }
           if (range == "2") {
                sectors.push_back(0); sectors.push_back(2); sectors.push_back(3); sectors.push_back(5);
           }
           if (range == "3") {
                sectors.push_back(0); sectors.push_back(5); sectors.push_back(3);
           }

        }
        if (beam_en == "4_461") {sectors.push_back(0); sectors.push_back(1); sectors.push_back(5);}


    }
    else {target = "56Fe";
	if (beam_en == "2_261") {
           if (range == "1") {
                sectors.push_back(0); sectors.push_back(3); sectors.push_back(5); sectors.push_back(2); sectors.push_back(4);
           }
           if (range == "2") {
                sectors.push_back(1); sectors.push_back(2); sectors.push_back(3); sectors.push_back(5);
           }
           if (range == "3") {
                sectors.push_back(1); sectors.push_back(5); sectors.push_back(3); sectors.push_back(2);
           }

        }
        if (beam_en == "4_461") {sectors.push_back(0); sectors.push_back(1); sectors.push_back(5);}

    }

    std::cout << "Simulation: " << sim << "\n";
    std::cout << "Sim label: " << sim_label << "\n";
    std::cout << "Analyzing target: " << target << "\n";
    std::cout << "Analyzed beam en: " << beam_en << "\n";
    std::cout << "Range: " << range << "\n";
    for(int s: sectors) {std::cout << "Sector " << s << "\n";}


    // histogram initialization
    TH1D* h1_elmom_mc_total;
    TH1D* h1_elmom_InteractionBreakDown_inSector_mc[4][6];
    TH1D* h1_elmom_SF_total;
    TH1D* h1_elmom_InteractionBreakDown_inSector_SF[4][6];
    TH1D* h1_elmom_mc_int[4];
    TH1D* h1_elmom_data[6];




	for (int i = 0; i < 4; i++) { // for all the interactions
	    for (int j: sectors) { // for all the sectors
    	   // extract the histrograms
    	   h1_elmom_InteractionBreakDown_inSector_mc[i][j] = (TH1D*)input1->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", i+1, j));    
    	   h1_elmom_InteractionBreakDown_inSector_mc[i][j]->Rebin(40);
	   //h1_elmom_InteractionBreakDown_inSector_SF[i][j] = (TH1D*)input3->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", i+1, j));
           //h1_elmom_InteractionBreakDown_inSector_SF[i][j]->Rebin(40);
         //Add everything to the first sector
            if(i == 0 && j == sectors[0]) h1_elmom_mc_total = (TH1D*)h1_elmom_InteractionBreakDown_inSector_mc[i][j]->Clone();
            if(i != 0 ||  j !=  sectors[0]) h1_elmom_mc_total->Add(h1_elmom_InteractionBreakDown_inSector_mc[i][j]);
	    //            if(i == 0 && j == sectors[0]) h1_elmom_SF_total = (TH1D*)h1_elmom_InteractionBreakDown_inSector_SF[i][j]->Clone();
            //if(i != 0 ||  j !=  sectors[0]) h1_elmom_SF_total->Add(h1_elmom_InteractionBreakDown_inSector_SF[i][j]);    
		if(j ==  sectors[0]) h1_elmom_mc_int[i] = (TH1D*)h1_elmom_InteractionBreakDown_inSector_mc[i][j]->Clone();
		    if(j !=  sectors[0]) h1_elmom_mc_int[i]->Add(h1_elmom_InteractionBreakDown_inSector_mc[i][j]);
	   }
	}

    for (int i: sectors) { // for all the sectors
		h1_elmom_data[i] = (TH1D*)input2->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", i));
      h1_elmom_data[i]->Rebin(40);
    }

    // compile all the sectors into one histogram
    for( int i: sectors) {
       if(i == sectors[0]) continue; 
       h1_elmom_data[sectors[0]]->Add( h1_elmom_data[i]); 
    }

    UniversalE4vFunction(h1_elmom_mc_total,  sim_label, target, beam_en, TString(info1)+TString(cuts1));
    PrettyDoubleXSecPlot(h1_elmom_mc_total, 2, beam_energy, 4, false);
    //UniversalE4vFunction(h1_elmom_SF_total,  FSIModelsToLabels["Fortran_SF_NoRadCorr_hN2018_Truth_WithoutFidAcc"], target, beam_en, TString(info1)+TString(cuts1));
    //PrettyDoubleXSecPlot(h1_elmom_SF_total, 2, beam_energy, 4, false);
    for(int i = 0; i < 4; i++) {
      UniversalE4vFunction(h1_elmom_mc_int[i], sim_label, target, beam_en, TString(info1)+TString(cuts1));
      PrettyDoubleXSecPlot(h1_elmom_mc_int[i], 2, beam_energy, 4, false);
    }
    UniversalE4vFunction(h1_elmom_data[sectors[0]],  "Pinned Data", target, beam_en, TString(info2));
    PrettyDoubleXSecPlot(h1_elmom_data[sectors[0]], 2, beam_energy, 4, false);
    

    // create a canvas on which to draw the histograms
    
    double max = 1.1*h1_elmom_mc_total->GetMaximum();

    const int color_options[4] = {kBlue, kAzure+10, kGreen-3, kViolet};

    TCanvas* c3;
    c3 = new TCanvas(TString::Format("c3"), TString::Format("c3"), 1200, 1000);
    // format the histograms
    h1_elmom_data[sectors[0]]->Sumw2();
    h1_elmom_data[sectors[0]]->SetStats( 0); // get rid of the stats box that usually appears at the top right of plots
    //h1_elmom_data[sectors[0]]->Scale(1.35);
    //h1_elmom_data[0]->GetXaxis()->SetTitle("Electron Momentum (GeV)");
    //h1_elmom_data[0]->GetYaxis()->SetTitle("Events");
    //h1_elmom_data[0]->GetXaxis()->CenterTitle( true);
    //h1_elmom_data[0]->GetYaxis()->CenterTitle( true);
    //h1_elmom_data[0]->SetTitle(TString(info2)+TString(cuts2));
    h1_elmom_data[sectors[0]]->SetMarkerStyle(kFullCircle);
    h1_elmom_data[sectors[0]]->SetMarkerSize(1.5);
    h1_elmom_data[sectors[0]]->SetMarkerColor(kBlack);
    h1_elmom_data[sectors[0]]->GetYaxis()->SetRangeUser(0,max);
    
    gStyle->SetOptStat(0);
    h1_elmom_mc_total->SetLineColor(kBlack);
    h1_elmom_mc_total->GetYaxis()->SetRangeUser(0, max);
    if(beam_energy == 4.461) h1_elmom_mc_total->GetXaxis()->SetRangeUser(2.0,4.);
    if(beam_energy == 2.261) h1_elmom_mc_total->GetXaxis()->SetRangeUser(0.5,2.1);
   
    //h1_elmom_SF_total->SetLineStyle(kDashed);

  // std::cout << "SF integral = " << h1_elmom_SF_total->Integral(1,h1_elmom_SF_total->GetNbinsX())*.725 << "\n";

    //h1_elmom_mc_total->Scale(.725*.909);

    h1_elmom_mc_total->GetXaxis()->SetTitle("Electron Momentum (GeV)");
    h1_elmom_mc_total->Draw("HIST E");
    //h1_elmom_SF_total->Draw("HIST SAME");
    double cutval;
    if(targ == "C12") {
      if(range=="1"){
         if(beamen =="2.261000") {
            cutval = 1.95;
            h1_elmom_mc_total->GetXaxis()->SetRangeUser(1.8,2.4);
         }
         else {
            cutval = 3.4;
            h1_elmom_mc_total->GetXaxis()->SetRangeUser(3.0,4.1);
         }
      }
      else if(range=="2") {
         cutval = 1.75;
         h1_elmom_mc_total->GetXaxis()->SetRangeUser(1.5,2.1);
      }
      else {
         cutval = 1.5;
         h1_elmom_mc_total->GetXaxis()->SetRangeUser(1.35,2.1);
      }
    }

   if(targ == "4He") {
      if(range=="1"){
         if(beamen == "2.261000") {
            cutval = 1.85;
            h1_elmom_mc_total->GetXaxis()->SetRangeUser(1.7,2.4);
         }
         else {
            cutval = 3.4;
            h1_elmom_mc_total->GetXaxis()->SetRangeUser(3.0,4.2);
         }
      }
      else if(range=="2") {
         cutval = 1.75;
         h1_elmom_mc_total->GetXaxis()->SetRangeUser(1.5,2.1);
      }
      else {
         cutval = 1.5;
         h1_elmom_mc_total->GetXaxis()->SetRangeUser(1.35,2.1);
      }
    }

   if(targ == "56Fe") {
      if(range=="1"){
         if(beamen == "2.261000") {
            cutval = 1.95;
            h1_elmom_mc_total->GetXaxis()->SetRangeUser(1.8,2.4);
         }
         else {
            cutval = 3.35;
            h1_elmom_mc_total->GetXaxis()->SetRangeUser(3.0,4.0);
         }
      }
      else if(range=="2") {
         cutval = 1.75;
         h1_elmom_mc_total->GetXaxis()->SetRangeUser(1.5,2.1);
      }
      else {
         cutval = 1.5;
         h1_elmom_mc_total->GetXaxis()->SetRangeUser(1.35,2.1);
	 h1_elmom_mc_total->GetYaxis()->SetRangeUser(0,1.45e-3);
      }
    }

    TLine *cut = new TLine(cutval, 0, cutval, max);
    cut->SetLineColor(kRed);
    cut->SetLineWidth(3);
    cut->Draw();

    //h1_elmom_data[0]->Scale(.725*.909);
    h1_elmom_data[sectors[0]]->Draw("E P SAME");
    for(int i = 0; i < 4; i++) {
//		h1_elmom_mc_int[i]->Scale(.725*.909);
    	h1_elmom_mc_int[i]->SetLineColor(color_options[i]);
	   h1_elmom_mc_int[i]->GetYaxis()->SetRangeUser(0,max);
	   h1_elmom_mc_int[i]->Draw("HIST SAME");
    }


    	

    // draw a legend for our plot
    TLegend *legend = new TLegend(.62,.60,.82,.90);
    legend->AddEntry( h1_elmom_mc_total, sim.c_str());
    legend->AddEntry( h1_elmom_data[sectors[0]], "CLAS data");
    legend->AddEntry( h1_elmom_mc_int[0],"QE");
    legend->AddEntry( h1_elmom_mc_int[1],"MEC");
    legend->AddEntry( h1_elmom_mc_int[2],"RES");
    legend->AddEntry( h1_elmom_mc_int[3],"DIS");
    legend->SetBorderSize( 0);
    legend->SetFillStyle( 0);
    legend->Draw();


    // crop the margins of the canvas
    c3->SetLeftMargin( 0.2);
    c3->SetBottomMargin( 0.2);
    c3->SetRightMargin( 0.2);
    c3->Update();

    c3->SaveAs(TString::Format("ElecMomcut/8_9_ElecMomcut_%s_%s_%s.pdf",targ.c_str(), beamen.c_str(), range.c_str()));


    
}
