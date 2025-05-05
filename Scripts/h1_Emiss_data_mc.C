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
#include "../Transparency/myFunctions.h"

void h1_Emiss_data_mc(std::string sim, std::string targ, std::string beamen, std::string range, std::string type){
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);

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

    //if(sim == "SuSAv2") file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/"+sim+"/"+type+"_Range"+range+"_Genie_"+sim_num+"_"+targ+"_"+beamen+".root";
    //file_name2 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Data_ThetaPQ/"+flipped_target+"/"+type+"_Range"+range+"_Data__"+targ+"_"+beamen+".root";

    std::string susa_true_reco_rad_file = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut_nominal/Rad_Truth_Reco/Big_Excl_Range1_Genie_3_C12_2.261000.root";
    std::string susa_true_reco_file = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut_nominal/Truth_Reco/SuSA/Big_Excl_Range1_Genie_1_C12_2.261000.root";

    file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/ProtMom_Cut/Excl_Range_"+range+"_Genie_1_"+targ+"_2.261000.root";
    file_name2 = "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/ProtMom_Cut/Excl_Range"+range+"_Data__"+targ+"_2.261000.root";
    //file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/ProtMom_Cut/Excl_Range_2_Genie_1_"+targ+"_2.261000.root";
    //file_name2 = "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/ProtMom_Cut/Excl_Range2_Data__"+targ+"_2.261000.root";
    //file_name3 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/SF/Excl_Range"+range+"_Genie_1_C12_2.261000.root";

    file_name3 = "/genie/app/users/nsteinbe/grahams_e4nu/Analyze_data/SF_files/SF_range1_truth_Genie_1_C12_2.261000.root";

    //file_name4 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/G18/2_Range"+range+"_Genie_"+sim_num+"_"+targ+"_"+beamen+".root";
    //file_name4 = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Reconstructed/ThetaPQCut_nominal/G18/Excl_Range1_Genie_2_C12_2.261000.root";


    TFile *input1 = TFile::Open( TString(file_name1));
    TFile *input2 = TFile::Open( TString(file_name2));
    TFile *input3 = TFile::Open( TString(file_name3));

    TFile *input_truereco = TFile::Open( TString(susa_true_reco_file));
    TFile *input_truereco_rad = TFile::Open( TString(susa_true_reco_rad_file));

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
    double beam_en_dbl;
    if(info1.find("1.161")!= std::string::npos) {beam_en = "1_161"; beam_en_dbl = 1.161;}
    else if(info1.find("2.261")!= std::string::npos) {beam_en = "2_261"; beam_en_dbl = 2.261;}
    else {beam_en = "4_461"; beam_en_dbl = 4.461;}

    std::vector<int> sectors = {};
 double scale_factor=0;
    std::string target;
            if(info1.find("C12")!= std::string::npos) {target = "12C";
        if (beam_en == "2_261") {
           if (range == "1") {
                sectors.push_back(2); sectors.push_back(3); sectors.push_back(4);
  		scale_factor = 0.759/0.5;
           }
           if (range == "2") {
                sectors.push_back(0); sectors.push_back(2); sectors.push_back(3); sectors.push_back(4); sectors.push_back(5);
		scale_factor = .720/0.5;
           }
           if (range == "3") {
                sectors.push_back(0); sectors.push_back(3); sectors.push_back(5);
		scale_factor = .685/0.5;
           }

        }
        if (beam_en == "4_461") {sectors.push_back(1); sectors.push_back(3); sectors.push_back(4); scale_factor = 0.697/0.5;}

    }
    else if(info1.find("4He")!= std::string::npos) {target = "4He";
        if (beam_en == "2_261") {
           if (range == "1") {
                sectors.push_back(0); sectors.push_back(2); sectors.push_back(3);
		scale_factor = 0.755/0.5;
           }
           if (range == "2") {
                sectors.push_back(0); sectors.push_back(2); sectors.push_back(3); sectors.push_back(5);
		scale_factor = 0.708/0.5;
           }
           if (range == "3") {
                sectors.push_back(0); sectors.push_back(2); sectors.push_back(3);
		scale_factor = 0.690/0.5; 
           }

        }
        if (beam_en == "4_461") {sectors.push_back(2); sectors.push_back(3); sectors.push_back(4); scale_factor = 0.688/0.5;}


    }
    else {target = "56Fe";
        if (beam_en == "2_261") {
           if (range == "1") {
                sectors.push_back(0); sectors.push_back(1); sectors.push_back(2); sectors.push_back(3); sectors.push_back(5);
		scale_factor = 0.725/0.5;
           }
           if (range == "2") {
                sectors.push_back(0); sectors.push_back(2); sectors.push_back(4); sectors.push_back(5);
		scale_factor = 0.672/0.5;
           }
           if (range == "3") {
                sectors.push_back(0); sectors.push_back(2); sectors.push_back(4); sectors.push_back(5);
		scale_factor = 0.665/0.5;
           }

        }
        if (beam_en == "4_461") {sectors.push_back(2); sectors.push_back(3); sectors.push_back(4); scale_factor = 0.629/0.5;}

    }
//sectors.clear();
//sectors.push_back(0);sectors.push_back(1);sectors.push_back(2);sectors.push_back(3);sectors.push_back(4);sectors.push_back(5);
    std::cout << "Simulation: " << sim << "\n";
    std::cout << "Sim label: " << sim_label << "\n";
    std::cout << "Analyzing target: " << target << "\n";
    std::cout << "Analyzed beam en: " << beam_en << "\n";

    // histogram initialization
    TH1D* h1_Emiss_mc_total = new TH1D("","",10,0,0.4);
    TH1D* h1_Emiss_InteractionBreakDown_inSector_mc[4][6];
    TH1D* h1_Emiss_mc_int[4];
    TH1D* h1_Emiss_SF_total = new TH1D("SF","SF",10,0,0.4);
    TH1D* h1_Emiss_InteractionBreakDown_inSector_SF[4][6];
    TH1D* h1_Emiss_data[6];

    TH1D* h1_Pmiss_mc_total = new TH1D("","",100, 0, 1.0);
    TH1D* h1_Pmiss_InteractionBreakDown_inSector_mc[4][6];
    TH1D* h1_Pmiss_mc_int[4];
    TH1D* h1_Pmiss_SF_total = new TH1D("SFp","SFp",100, 0, 1.0);
    TH1D* h1_Pmiss_InteractionBreakDown_inSector_SF[4][6];
    TH1D* h1_Pmiss_data[6];


    TH1D* h1_Emiss_truereco[4][6];
    TH1D* h1_Emiss_truereco_Rad[4][6];
    TH1D* h1_Pmiss_truereco[4][6];
    TH1D* h1_Pmiss_truereco_Rad[4][6];

    TH2F* h1_EmissPmiss_mc_total;
    TH2F* h1_EmissPmiss_InteractionBreakDown_inSector_mc[4][6];
    TH2F* h1_EmissPmiss_data[6];

	for (int i = 0; i < 4; i++) { // for all the interactions
	    for (int j: sectors) { // for all the sectors
    		// extract the histrograms
    		h1_Emiss_InteractionBreakDown_inSector_mc[i][j] = (TH1D*)input1->Get(TString::Format("h1_Int_%i_Sect_%i_Em", i+1, j));
		h1_Emiss_InteractionBreakDown_inSector_mc[i][j]->Scale(scale_factor);
		h1_Emiss_InteractionBreakDown_inSector_SF[i][j] = (TH1D*)input3->Get(TString::Format("h1_Int_%i_Sect_%i_Em", i+1, j));

		h1_Emiss_truereco[i][j] = (TH1D*)input_truereco->Get( TString::Format("h1_Int_%i_Sect_%i_Em", i+1, j) );
                h1_Emiss_truereco_Rad[i][j] = (TH1D*)input_truereco_rad->Get( TString::Format("h1_Int_%i_Sect_%i_Em", i+1, j) ); 

                h1_Emiss_mc_total->Add(h1_Emiss_InteractionBreakDown_inSector_mc[i][j]);
	        h1_Emiss_SF_total->Add(h1_Emiss_InteractionBreakDown_inSector_SF[i][j]);
            if(j == sectors[0]) h1_Emiss_mc_int[i] = (TH1D*)h1_Emiss_InteractionBreakDown_inSector_mc[i][j]->Clone();
            else h1_Emiss_mc_int[i]->Add(h1_Emiss_InteractionBreakDown_inSector_mc[i][j]);

	    if(i != 0) {

		h1_Emiss_truereco[0][j]->Add(h1_Emiss_truereco[i][j]);
		h1_Emiss_truereco_Rad[0][j]->Add(h1_Emiss_truereco_Rad[i][j]);

	    }	

             
	   }
	}



    for (int i: sectors) { // for all the sectors
                h1_Emiss_data[i] = (TH1D*)input2->Get( TString::Format("h1_Int_0_Sect_%i_Em", i));
    }

    TH1D* h1_rad_corr[6];

    //Radiatively correct the data
    for(int j: sectors) {
	
	UniversalE4vFunction(h1_Emiss_truereco[0][j], sim_label, target, beam_en, "no rad");
	UniversalE4vFunction(h1_Emiss_truereco_Rad[0][j], FSIModelsToLabels["SuSav2_RadCorr_LFGM_Truth_WithFidAcc_UpdatedSchwinger"], target, beam_en, "rad");

        h1_rad_corr[j] = (TH1D*) (h1_Emiss_truereco[0][j]->Clone());
	h1_rad_corr[j]->Divide(h1_Emiss_truereco_Rad[0][j]);

	for(int b = 0; b < h1_Emiss_data[j]->GetNbinsX(); b++) {

		double radcorr = h1_rad_corr[j]->GetBinContent(b+1);
		double oldbincontent = h1_Emiss_data[j]->GetBinContent(b+1);
		double oldbinerror = h1_Emiss_data[j]->GetBinError(b+1);

		if(radcorr <= 0) continue;

		double newbincontent = radcorr*oldbincontent;
		double newbinerror = radcorr*oldbinerror;

		h1_Emiss_data[j]->SetBinContent(b+1, newbincontent);
		h1_Emiss_data[j]->SetBinError(b+1, newbinerror);
	
	}


    }

    // compile all the sectors into one histogram
    for( int i: sectors) { 
       if(i != sectors[0]) h1_Emiss_data[sectors[0]]->Add( h1_Emiss_data[i]); 
    }

    UniversalE4vFunction(h1_Emiss_mc_total,  sim_label, target, beam_en, TString(info1)+TString(cuts1));
    PrettyDoubleXSecPlot(h1_Emiss_mc_total, 2, beam_en_dbl, 4, false);
    UniversalE4vFunction(h1_Emiss_SF_total,  FSIModelsToLabels["Fortran_SF_NoRadCorr_hN2018_Truth_WithoutFidAcc"], target, beam_en, TString(info1)+TString(cuts1)+"SF");
    PrettyDoubleXSecPlot(h1_Emiss_SF_total, 2, beam_en_dbl, 4, false);
    
    for(int i = 0; i < 4; i++) {
	   UniversalE4vFunction(h1_Emiss_mc_int[i], sim_label, target, beam_en, TString(info1)+TString(cuts1));
        PrettyDoubleXSecPlot(h1_Emiss_mc_int[i], 2, beam_en_dbl, 4, false);
    }
    
    UniversalE4vFunction(h1_Emiss_data[sectors[0]],  "Pinned Data", target, beam_en, TString(info2));

    
            h1_Pmiss_mc_total->Rebin(2);
            h1_Pmiss_SF_total->Rebin(2);

    for (int i = 0; i < 4; i++) { // for all the interactions
        for (int j: sectors) { // for all the sectors
            // extract the histrograms
            h1_Pmiss_InteractionBreakDown_inSector_mc[i][j] = (TH1D*)input1->Get(TString::Format("h1_Int_%i_Sect_%i_Pm", i+1, j));
	    h1_Pmiss_InteractionBreakDown_inSector_SF[i][j] = (TH1D*)input3->Get(TString::Format("h1_Int_%i_Sect_%i_Pm", i+1, j));
	    h1_Pmiss_InteractionBreakDown_inSector_mc[i][j]->Scale(scale_factor); 

	    
            h1_Pmiss_InteractionBreakDown_inSector_mc[i][j]->Rebin(2);
            h1_Pmiss_InteractionBreakDown_inSector_SF[i][j]->Rebin(2);

            h1_Pmiss_mc_total->Add( h1_Pmiss_InteractionBreakDown_inSector_mc[i][j]);
	    h1_Pmiss_SF_total->Add( h1_Pmiss_InteractionBreakDown_inSector_SF[i][j]);
      
	    h1_Pmiss_truereco[i][j] = (TH1D*)input_truereco->Get( TString::Format("h1_Int_%i_Sect_%i_Pm", i+1, j) );
            h1_Pmiss_truereco_Rad[i][j] = (TH1D*)input_truereco_rad->Get( TString::Format("h1_Int_%i_Sect_%i_Pm", i+1, j) );

	    h1_Pmiss_truereco[i][j]->Rebin(2);
    	    h1_Pmiss_truereco_Rad[i][j]->Rebin(2);

            if(j == sectors[0]) h1_Pmiss_mc_int[i] = (TH1D*)h1_Pmiss_InteractionBreakDown_inSector_mc[i][j]->Clone();
            else h1_Pmiss_mc_int[i]->Add(h1_Pmiss_InteractionBreakDown_inSector_mc[i][j]);   
            
            if(i != 0) {
		h1_Pmiss_truereco[0][j]->Add(h1_Pmiss_truereco[i][j]);
		h1_Pmiss_truereco_Rad[0][j]->Add(h1_Pmiss_truereco_Rad[i][j]);
	    }

       }
    }

    for (int i: sectors) { // for all the sectors
        h1_Pmiss_data[i] = (TH1D*)input2->Get( TString::Format("h1_Int_0_Sect_%i_Pm", i));
        h1_Pmiss_data[i]->Rebin(2);
    }


    for(int j: sectors) {
        
        UniversalE4vFunction(h1_Pmiss_truereco[0][j], sim_label, target, beam_en, "no rad");
        UniversalE4vFunction(h1_Pmiss_truereco_Rad[0][j], FSIModelsToLabels["SuSav2_RadCorr_LFGM_Truth_WithFidAcc_UpdatedSchwinger"], target, beam_en, "rad");
        
        h1_rad_corr[j] = (TH1D*) (h1_Pmiss_truereco[0][j]->Clone());
        h1_rad_corr[j]->Divide(h1_Pmiss_truereco_Rad[0][j]);
        
        for(int b = 0; b < h1_Pmiss_data[j]->GetNbinsX(); b++) {
                
                double radcorr = h1_rad_corr[j]->GetBinContent(b+1);
                double oldbincontent = h1_Pmiss_data[j]->GetBinContent(b+1);
                double oldbinerror = h1_Pmiss_data[j]->GetBinError(b+1);
                
                if(radcorr <= 0) continue;
                
                double newbincontent = radcorr*oldbincontent;
                double newbinerror = radcorr*oldbinerror;
                
                h1_Pmiss_data[j]->SetBinContent(b+1, newbincontent);
                h1_Pmiss_data[j]->SetBinError(b+1, newbinerror);
        
        }

    
    }



    // compile all the sectors into one histogram
    for( int i: sectors) { 
       if(i!= sectors[0]) h1_Pmiss_data[sectors[0]]->Add( h1_Pmiss_data[i]); 
    }

    UniversalE4vFunction(h1_Pmiss_mc_total,  sim_label, target, beam_en, TString(info1)+TString(cuts1));
    PrettyDoubleXSecPlot(h1_Pmiss_mc_total, 2, beam_en_dbl, 4, false);
    UniversalE4vFunction(h1_Pmiss_SF_total,  FSIModelsToLabels["Fortran_SF_NoRadCorr_hN2018_Truth_WithoutFidAcc"], target, beam_en, TString(info1)+TString(cuts1)+"SFp");
    PrettyDoubleXSecPlot(h1_Pmiss_SF_total, 2, beam_en_dbl, 4, false);    

    for(int i = 0; i < 4; i++) {
        UniversalE4vFunction(h1_Pmiss_mc_int[i], sim_label, target, beam_en, TString(info1)+TString(cuts1));
        PrettyDoubleXSecPlot(h1_Pmiss_mc_int[i], 2, beam_en_dbl, 4, false);
    }
    UniversalE4vFunction(h1_Pmiss_data[sectors[0]],  "Pinned Data", target, beam_en, TString(info2));
    

    for (int i = 0; i < 4; i++) { // for all the interactions
        for (int j = 0; j < 6; j++) { // for all the sectors
            // extract the histrograms
            h1_EmissPmiss_InteractionBreakDown_inSector_mc[i][j] = (TH2F*)input1->Get(TString::Format("h2_Int_%i_Sect_%i_EmPm", i+1, j));    
            //Add everything to the first sector
            if(i == 0 && j == 0) h1_EmissPmiss_mc_total = (TH2F*)h1_EmissPmiss_InteractionBreakDown_inSector_mc[i][j]->Clone();
            else h1_EmissPmiss_mc_total->Add(h1_EmissPmiss_InteractionBreakDown_inSector_mc[i][j]);
        
       }
    }

    for (int i = 0; i < 6; i++) { // for all the sectors
        h1_EmissPmiss_data[i] = (TH2F*)input2->Get( TString::Format("h2_Int_0_Sect_%i_EmPm", i));
    }

    // compile all the sectors into one histogram
    for( int i = 1; i < 6; i++) { 
       h1_EmissPmiss_data[0]->Add( h1_EmissPmiss_data[i]); 
    }

    //std::cout << "integral of SF = " << h1_Pmiss_SF_total->Integral(1,h1_Pmiss_SF_total->GetNbinsX()) << "\n";



    //norm = h1_EmissPmiss_data[0]->Integral()/h1_EmissPmiss_mc_total->Integral();
    //std::cout << "normalizing factor = " << norm << "\n";
    //h1_EmissPmiss_mc_total->Scale(norm);
                        

    // create a canvas on which to draw the histograms
    

    const int color_options[4] = {kBlue, kAzure+10, kGreen-3, kViolet};

    TCanvas* c3;
    c3 = new TCanvas(TString::Format("c3"), TString::Format("c3"), 1200, 1000);
    //c3->Divide(1,2);

    c3->SetLeftMargin( 0.2);
    c3->SetBottomMargin( 0.2);
    c3->SetRightMargin( 0.2);
    c3->Update();

    //c3->cd(1);
    // format the histograms
    //h1_Emiss_data[sectors[0]]->Scale(1.35);
    h1_Emiss_data[sectors[0]]->Sumw2();
    h1_Emiss_data[sectors[0]]->SetStats( 0); 
    h1_Emiss_mc_total->GetXaxis()->SetTitle("Missing Energy (GeV)");
    h1_Emiss_mc_total->GetYaxis()->SetTitle("Scaled Events");
    h1_Emiss_mc_total->SetTitle(TString(info2)+TString(cuts2));
    h1_Emiss_data[sectors[0]]->SetMarkerStyle(kFullCircle);
    h1_Emiss_data[sectors[0]]->SetMarkerSize(1.5);
    h1_Emiss_data[sectors[0]]->SetMarkerColor(kBlack);
    h1_Emiss_SF_total->SetLineStyle(kDashed);

    h1_Emiss_mc_total->SetLineColor(kBlack);

    double max = 1.1*h1_Emiss_mc_total->GetMaximum();
    h1_Emiss_mc_total->GetYaxis()->SetRangeUser(0, max);
    h1_Emiss_mc_total->Draw("HIST"); 
    h1_Emiss_SF_total->Draw("HIST SAME");
    
    for(int i = 0; i < 4; i++) {
        h1_Emiss_mc_int[i]->SetLineColor(color_options[i]);
        h1_Emiss_mc_int[i]->Draw("HIST SAME");
    }
    
    
    h1_Emiss_data[sectors[0]]->Draw("P E SAME");
	
    
    // draw a legend for our plot
    TLegend *legend = new TLegend( 0.6, 0.625, 0.825, 0.875);
    legend->AddEntry( h1_Emiss_mc_total, sim.c_str());
    legend->AddEntry( h1_Emiss_data[sectors[0]], "CLAS data");
    legend->AddEntry( h1_Emiss_mc_int[0],"QE");
    legend->AddEntry( h1_Emiss_mc_int[1],"MEC");
    legend->AddEntry( h1_Emiss_mc_int[2],"RES");
    legend->AddEntry( h1_Emiss_mc_int[3],"DIS");
    legend->AddEntry( h1_Emiss_SF_total, "SF QE");
    legend->SetBorderSize( 0);
    legend->SetFillStyle( 0);
    legend->Draw();
    

    TCanvas* c4;
    c4 = new TCanvas(TString::Format("c4"), TString::Format("c4"), 1200, 1000);

    c4->SetLeftMargin( 0.2);
    c4->SetBottomMargin( 0.2);
    c4->SetRightMargin( 0.2);
    c4->Update();

    // format the histograms
    h1_Pmiss_data[sectors[0]]->Scale(1.35);
    h1_Pmiss_data[sectors[0]]->Sumw2();
    h1_Pmiss_data[sectors[0]]->SetStats( 0); // get rid of the stats box that usually appears at the top right of plots
    h1_Pmiss_mc_total->GetXaxis()->SetTitle("Missing Momentum (GeV)");
    h1_Pmiss_mc_total->GetYaxis()->SetTitle("Scaled Events");
    h1_Pmiss_mc_total->SetTitle(TString(info2)+TString(cuts2));
    h1_Pmiss_SF_total->SetLineStyle(kDashed);

    h1_Pmiss_data[sectors[0]]->SetMarkerStyle(kFullCircle);
    h1_Pmiss_data[sectors[0]]->SetMarkerSize(1.5);
    h1_Pmiss_data[sectors[0]]->SetMarkerColor(kBlack);
    
    h1_Pmiss_mc_total->SetLineColor(kBlack);
    //double maxP = 1.1*h1_Pmiss_mc_total->GetMaximum();
	    //h1_Pmiss_mc_total->GetYaxis()->SetRangeUser(0,maxP);

    h1_Pmiss_mc_total->Draw("HIST"); 
    h1_Pmiss_SF_total->Draw("HIST SAME");
    for(int i = 0; i < 4; i++) {
        h1_Pmiss_mc_int[i]->SetLineColor(color_options[i]);
       h1_Pmiss_mc_int[i]->Draw("HIST SAME");
     }
    h1_Pmiss_data[sectors[0]]->Draw("P E SAME");   
 
    // draw a legend for our plot
    TLegend *legend2 = new TLegend(.82,.65,.99,.85);
    legend2->AddEntry( h1_Pmiss_mc_total, sim.c_str());
    legend2->AddEntry( h1_Pmiss_data[sectors[0]], "CLAS data");
    
    legend2->AddEntry( h1_Pmiss_mc_int[0],"QE");
    legend2->AddEntry( h1_Pmiss_mc_int[1],"MEC");
    legend2->AddEntry( h1_Pmiss_mc_int[2],"RES");
    legend2->AddEntry( h1_Pmiss_mc_int[3],"DIS");
    //legend2->AddEntry( h1_Pmiss_SF_total, "SF QE");
    legend2->SetBorderSize( 0);
    legend2->SetFillStyle( 0);
    legend2->Draw();

    std::cout << "Emiss integral: " << h1_Emiss_mc_total->Integral(0,h1_Emiss_mc_total->GetNbinsX()) << "\n";
    std::cout << "Pmiss integral: " << h1_Pmiss_mc_total->Integral(0,h1_Pmiss_mc_total->GetNbinsX()) << "\n";
    std::cout << "Data Emiss integral: " << h1_Emiss_data[sectors[0]]->Integral(0,h1_Emiss_data[sectors[0]]->GetNbinsX()) << "\n";
    std::cout << "Data Pmiss integral: " << h1_Pmiss_data[sectors[0]]->Integral(0,h1_Pmiss_data[sectors[0]]->GetNbinsX()) << "\n";

    //c3->SaveAs(TString::Format("Em_%s_%s_%s.pdf",targ.c_str(), beamen.c_str(), range.c_str()));
    //c4->SaveAs(TString::Format("Pm_%s_%s_%s.pdf",targ.c_str(), beamen.c_str(), range.c_str()));
    
}
