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

void h1_EmPm_CFG_LFG(std::string sim, std::string targ, std::string beamen, std::string range, std::string type){
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

    file_name1 = "/genie/app/users/nsteinbe/grahams_e4nu/Cut_BreakDown/ProtMom_Cut/Excl_Range_"+range+"_Genie_1_"+targ+"_2.261000.root";
    file_name2 = "/genie/app/users/nsteinbe/grahams_e4nu/Analyze_data/SuSAv2_CFG_range1_truereco_Genie_1_C12_2.261000.root";
   

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

    TH1D* Emiss_LFG_sector[6];
    TH1D* Emiss_CFG_sector[6];
    TH1D* Emiss_LFG;
    TH1D* Emiss_CFG;

    TH1D* Pmiss_LFG_sector[6];
    TH1D* Pmiss_CFG_sector[6];
    TH1D* Pmiss_LFG;
    TH1D* Pmiss_CFG;    


    for (int j: sectors) { // for all the sectors
		// extract the histrograms
		Emiss_LFG_sector[j] = (TH1D*)input1->Get(TString::Format("h1_Int_1_Sect_%i_Em", j));
    	Emiss_LFG_sector[j]->Scale(scale_factor);

        Emiss_CFG_sector[j] = (TH1D*)input2->Get(TString::Format("h1_Int_1_Sect_%i_Em", j));
        Emiss_CFG_sector[j]->Scale(scale_factor);

        if (j == sectors[0]) {
            Emiss_LFG = (TH1D*)Emiss_LFG_sector[j]->Clone();
            Emiss_CFG = (TH1D*)Emiss_CFG_sector[j]->Clone();
        }

        else {
            Emiss_LFG->Add(Emiss_LFG_sector[j]);
            Emiss_CFG->Add(Emiss_CFG_sector[j]);
        }
         
   }
	

    UniversalE4vFunction(Emiss_LFG,  sim_label, target, beam_en, TString(info1)+TString(cuts1));
    PrettyDoubleXSecPlot(Emiss_LFG, 2, beam_en_dbl, 4, false);
    UniversalE4vFunction(Emiss_CFG,  FSIModelsToLabels["SuSav2_NoRadCorr_CFG"], target, beam_en, TString(info1)+TString(cuts1)+"SF");
    PrettyDoubleXSecPlot(Emiss_CFG, 2, beam_en_dbl, 4, false);
    
    for (int j: sectors) { // for all the sectors
        // extract the histrograms
        Pmiss_LFG_sector[j] = (TH1D*)input1->Get(TString::Format("h1_Int_1_Sect_%i_Pm", j));
        Pmiss_LFG_sector[j]->Scale(scale_factor);

        Pmiss_CFG_sector[j] = (TH1D*)input2->Get(TString::Format("h1_Int_1_Sect_%i_Pm", j));
        Pmiss_CFG_sector[j]->Scale(scale_factor);

        if (j == sectors[0]) {
            Pmiss_LFG = (TH1D*)Pmiss_LFG_sector[j]->Clone();
            Pmiss_CFG = (TH1D*)Pmiss_CFG_sector[j]->Clone();
        }

        else {
            Pmiss_LFG->Add(Pmiss_LFG_sector[j]);
            Pmiss_CFG->Add(Pmiss_CFG_sector[j]);
        }
         
   }
    

    UniversalE4vFunction(Pmiss_LFG,  sim_label, target, beam_en, TString(info1)+TString(cuts1));
    PrettyDoubleXSecPlot(Pmiss_LFG, 2, beam_en_dbl, 4, false);
    UniversalE4vFunction(Pmiss_CFG,  FSIModelsToLabels["SuSav2_NoRadCorr_CFG"], target, beam_en, TString(info1)+TString(cuts1)+"SF");
    PrettyDoubleXSecPlot(Pmiss_CFG, 2, beam_en_dbl, 4, false);
       


    const int color_options[4] = {kBlue, kAzure+10, kGreen-3, kViolet};

    TCanvas* c3;
    c3 = new TCanvas(TString::Format("c3"), TString::Format("c3"), 1200, 1000);
    //c3->Divide(1,2);

    c3->SetLeftMargin( 0.2);
    c3->SetBottomMargin( 0.2);
    c3->SetRightMargin( 0.2);
    c3->Update();

    Emiss_LFG->Sumw2();
    Emiss_LFG->SetStats( 0); 
    Emiss_LFG->GetXaxis()->SetTitle("Missing Energy (GeV)");
    Emiss_LFG->GetYaxis()->SetTitle("Scaled Events");
    Emiss_LFG->SetTitle(TString(info2)+TString(cuts2));
    Emiss_LFG->SetLineColor(kBlack);

    double max = 1.1*Emiss_LFG->GetMaximum();
    Emiss_LFG->GetYaxis()->SetRangeUser(0, max);
    Emiss_LFG->Draw("HIST"); 
    //h1_Emiss_SF_total->Draw("HIST SAME");

    Emiss_CFG->SetLineColor(kBlue);
    Emiss_CFG->Draw("HIST SAME");

    
    // draw a legend for our plot
    TLegend *legend = new TLegend( 0.6, 0.625, 0.825, 0.875);
    legend->AddEntry( Emiss_LFG, "SuSAv2 QE LFG");
    legend->AddEntry( Emiss_CFG, "SuSAv2 QE CFG");
    legend->SetBorderSize( 0);
    legend->SetFillStyle( 0);
    legend->Draw();
    

    TCanvas* c4;
    c4 = new TCanvas(TString::Format("c4"), TString::Format("c4"), 1200, 1000);

    c4->SetLeftMargin( 0.2);
    c4->SetBottomMargin( 0.2);
    c4->SetRightMargin( 0.2);
    c4->Update();

    Pmiss_LFG->Sumw2();
    Pmiss_LFG->SetStats( 0); 
    Pmiss_LFG->GetXaxis()->SetTitle("Missing Momentum (GeV)");
    Pmiss_LFG->GetYaxis()->SetTitle("Scaled Events");
    Pmiss_LFG->SetTitle(TString(info2)+TString(cuts2));
    Pmiss_LFG->SetLineColor(kBlack);

    max = 1.1*Pmiss_LFG->GetMaximum();
    Pmiss_LFG->GetYaxis()->SetRangeUser(0, max);
    Pmiss_LFG->Draw("HIST"); 
    //h1_Emiss_SF_total->Draw("HIST SAME");

    Pmiss_CFG->SetLineColor(kBlue);
    Pmiss_CFG->Draw("HIST SAME");

    
    // draw a legend for our plot
    TLegend *legend2 = new TLegend( 0.6, 0.625, 0.825, 0.875);
    legend2->AddEntry( Pmiss_LFG, "SuSAv2 QE LFG");
    legend2->AddEntry( Pmiss_CFG, "SuSAv2 QE CFG");
    legend2->SetBorderSize( 0);
    legend2->SetFillStyle( 0);
    legend2->Draw();
    

//    c3->SaveAs(TString::Format("Em_%s_%s_%s.pdf",targ.c_str(), beamen.c_str(), range.c_str()));
//    c4->SaveAs(TString::Format("Pm_%s_%s_%s.pdf",targ.c_str(), beamen.c_str(), range.c_str()));
    
}
