#include "TMath.h"
#include <TProfile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TGaxis.h>
#include <TLegend.h>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <utility>

#include "/genie/app/users/nsteinbe/grahams_e4nu/Analyze_data/AfroConstants.h"
#include "/genie/app/users/nsteinbe/grahams_e4nu/Analyze_data/myFunctions.cpp"
void Acceptance(TString cuts, TString Range, TString nucleus, TString E, double Eb);
TH1F* SumProtSectorsAndInts(TString file = "", bool isData = false);
TH1F* SumElecSectorsAndInts(TString file = "", bool isData = false);
void AcceptanceCheck(TString cuts, TString Range, TString nucleus, TString E, double Eb);

using namespace std;

void AcceptanceCorrect() {
	/*
	Acceptance("Excl", "1", "56Fe", "2_261", 2.261);
	Acceptance("Excl", "2", "56Fe", "2_261", 2.261);
	Acceptance("Excl", "3", "56Fe", "2_261", 2.261);
	Acceptance("Excl", "1", "56Fe", "4_461", 4.461);

	Acceptance("Incl", "1", "56Fe", "2_261", 2.261);
	Acceptance("Incl", "2", "56Fe", "2_261", 2.261);
	Acceptance("Incl", "3", "56Fe", "2_261", 2.261);
	Acceptance("Incl", "1", "56Fe", "4_461", 4.461);
	*/
	AcceptanceCheck("Excl", "1", "56Fe", "2_261", 2.261);
	AcceptanceCheck("Excl", "2", "56Fe", "2_261", 2.261);
	AcceptanceCheck("Excl", "3", "56Fe", "2_261", 2.261);
	AcceptanceCheck("Excl", "1", "56Fe", "4_461", 4.461);
	//Acceptance("Excl", "2", "C12", "1_161", 1.161);
	//Acceptance("Excl", "3", "C12", "1_161", 1.161);
	//Acceptance("Excl", "1", "C12", "4_461", 4.461);

	AcceptanceCheck("Incl", "1", "56Fe", "2_261", 2.261);
	AcceptanceCheck("Incl", "2", "56Fe", "2_261", 2.261);
	AcceptanceCheck("Incl", "3", "56Fe", "2_261", 2.261);
	AcceptanceCheck("Incl", "1", "56Fe", "4_461", 4.461);
	//Acceptance("Incl", "2", "C12", "1_161", 1.161);
	//Acceptance("Incl", "3", "C12", "1_161", 1.161);
	//Acceptance("Incl", "1", "C12", "4_461", 4.461);
}

void Acceptance(TString cuts, TString Range, TString nucleus, TString E, double Eb) {
	TString GlobalPath = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/";


	TH1D::SetDefaultSumw2();
	std::vector<TH1D*> Plots; Plots.clear();
	std::vector<TString> FSIModel; FSIModel.clear();
	std::vector<TString> FSILabel; FSILabel.clear();

	FSILabel.push_back("Truth_Reco");
	FSILabel.push_back("Truth");

	FSIModel.push_back("SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc");//SuSAv2 noRad plot for acceptance
	FSIModel.push_back("SuSav2_NoRadCorr_LFGM_Truth_WithoutFidAcc");//SuSAv2 noRad plot for acceptance and radiative corrections

	int NFSIModels = FSIModel.size();
	TString PathToFile;
	TString FileName;

	for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

		// --------------------------------------------------------------------------------------
		PathToFile = GlobalPath + FSILabel[WhichFSIModel] + "/" ;
		FileName = cuts + "_" + "Range"+ Range + "_" + FSILabel[WhichFSIModel] + "_" + "Genie_" +"1_"+ nucleus + "_" + std::to_string(Eb);

		if(cuts == "Incl") {
			Plots.push_back( (TH1D*)( SumElecSectorsAndInts(PathToFile + FileName + ".root", false) ) );
		}
		if(cuts == "Excl") {
			Plots.push_back( (TH1D*)( SumProtSectorsAndInts(PathToFile + FileName + ".root", false) ) );
		}
		
		AbsoluteXSecScaling(Plots[WhichFSIModel], FSIModelsToLabels[FSIModel[WhichFSIModel]], nucleus, E);
		ReweightPlots(Plots[WhichFSIModel]);
		
		// --------------------------------------------------------------------------------------
	}

	//TH1D* OverallClone = (TH1D*)h->Clone();	

	// --------------------------------------------------------------------------------------	

	// Acceptance Correction

	// Two simulation models: get their average & use it as a correction factor
	// 1: Reco 1p0pi SuSav2 NoRad plot for average
	// 2: Reco 1p0pi G2018 Offset NoRad plot for average
	// 3: True 1p0pi SuSav2 NoRad plot for average
	// 4: True 1p0pi G2018 Offset NoRad plot for average

	TH1D* CorrectionSuSav2 = (TH1D*)Plots[1]->Clone();	
	CorrectionSuSav2->Divide(Plots[0]);
	TH1D* Average = (TH1D*)(CorrectionSuSav2->Clone());

	// --------------------------------------------------------------------------------------	

	/*int NBins = OverallClone->GetXaxis()->GetNbins();

	double AccCorrTolerance = 30;

	for (int WhichBin = 0; WhichBin < NBins; WhichBin++) {

		double AccCorr = 0.;
		double RadCorr = 0.;

		double NewBinContent = 0.;
		double NewBinError = 0.;		

		//if (Plots[0]->GetBinContent(WhichBin + 1) > 0) { 

		AccCorr = Average->GetBinContent(WhichBin + 1);

		// Sanity checks for acceptance corrections 
		if (AccCorr < 0 || AccCorr > AccCorrTolerance) { 

			double CorrectionSuSav2Bin = CorrectionSuSav2->GetBinContent(WhichBin + 1); 
			//double CorrectionG2018Bin = CorrectionG2018->GetBinContent(WhichBin + 1); 
				
			if (CorrectionSuSav2Bin > 0 && CorrectionSuSav2Bin < AccCorrTolerance) { AccCorr = CorrectionSuSav2Bin; } 
			//else if (CorrectionG2018Bin > 0 && CorrectionG2018Bin < AccCorrTolerance) { AccCorr = CorrectionG2018Bin; }
			//else { AccCorr = 0.; } 

		}

		//RadCorr = RadCorrection->GetBinContent(WhichBin + 1);

		NewBinContent = h->GetBinContent(WhichBin + 1) * AccCorr ;
		NewBinError = h->GetBinError(WhichBin + 1) * AccCorr;

		cout << "AccCorr = " << AccCorr << endl;
		//cout << "RadCorr = " << RadCorr << endl;
		//cout << "h->GetBinContent(WhichBin + 1) = " << h->GetBinContent(WhichBin + 1) << "   NewBinContent = " << NewBinContent << endl;
		//cout << "h->GetBinError(WhichBin + 1) = " << h->GetBinError(WhichBin + 1) << "   NewBinError = " << NewBinError << endl << endl;

		//}

		OverallClone->SetBinContent(WhichBin + 1, NewBinContent);
		OverallClone->SetBinError(WhichBin + 1, NewBinError);

	}*/


	TString CanvasName = FileName+"AccCorrFactorCanvas";
	TCanvas* PlotCanvas_Acc = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
	//Average->GetXaxis()->SetRangeUser(0.1,1.5);
	Average->GetYaxis()->SetTitle("Detector Acceptance Correction");
	if(cuts == "Excl") Average->GetXaxis()->SetTitle("Proton momentum (GeV)");
	if(cuts == "Incl") Average->GetXaxis()->SetTitle("Electron momentum (GeV)");
	Average->Draw("e hist");
	PlotCanvas_Acc->SaveAs("Corrections/"+FileName+"Acceptance_Correction.png");

	/*
	CanvasName = "AccCorrCanvas";
	TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
	OverallClone->GetXaxis()->SetRangeUser(0.1,1.5);
	OverallClone->GetYaxis()->SetTitle("Detector Acceptance Correction");
	OverallClone->Draw("e hist");
	OverallClone->Draw("e hist same");
	PlotCanvas_Acc->SaveAs("Acceptance_CorrectedPlot.png");
	*/
}

TH1F* SumProtSectorsAndInts(TString file, bool isData) {
		TFile *input = TFile::Open( TString( file ) );

	    TH1F* h1_prot_momentum;
	    TH1F* h1_prot_momentum_d[6];
    	TH1F* h1_prot_mom_InteractionBreakDown_inSector[6][4];

    	if (isData == false) {
    		for (int i = 0; i < 6; i++) { // for all the sectors
            	for (int j = 0; j < 4; j++) { // for all the interactions
            
            		// extract the histrograms
                	h1_prot_mom_InteractionBreakDown_inSector[i][j] = (TH1F*)input->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", j+1, i));
                	if(i == 0 && j == 0) h1_prot_momentum = (TH1F*)(h1_prot_mom_InteractionBreakDown_inSector[i][j]->Clone());
                	else h1_prot_momentum->Add(h1_prot_mom_InteractionBreakDown_inSector[i][j]);
				}
            }
    	}

    	if (isData == true) {
    		for (int i = 0; i < 6; i++) { // for all the sectors
    			 h1_prot_momentum_d[i] = (TH1F*)input->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", i));
            	if(i == 0) h1_prot_momentum = (TH1F*)(h1_prot_momentum_d[i]->Clone());
            	else h1_prot_momentum->Add(h1_prot_momentum_d[i]);
            }
    	}

    	h1_prot_momentum->Rebin( 40 );
    	return h1_prot_momentum;
}

TH1F* SumElecSectorsAndInts(TString file, bool isData) {
		TFile *input = TFile::Open( TString( file ) );

	    TH1F* h1_elec_momentum;
	    TH1F* h1_elec_momentum_d[6];
    	TH1F* h1_elec_mom_InteractionBreakDown_inSector[6][4];

    	if (isData == false) {
    		for (int i = 0; i < 6; i++) { // for all the sectors
            	for (int j = 0; j < 4; j++) { // for all the interactions
            
            		// extract the histrograms
                	h1_elec_mom_InteractionBreakDown_inSector[i][j] = (TH1F*)input->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", j+1, i));
                	if(i == 0 && j == 0) h1_elec_momentum = (TH1F*)(h1_elec_mom_InteractionBreakDown_inSector[i][j]->Clone());
                	else h1_elec_momentum->Add(h1_elec_mom_InteractionBreakDown_inSector[i][j]);
				}
            }
    	}

    	if (isData == true) {
    		for (int i = 0; i < 6; i++) { // for all the sectors
    			 h1_elec_momentum_d[i] = (TH1F*)input->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", i));
            	if(i == 0) h1_elec_momentum = (TH1F*)(h1_elec_momentum_d[i]->Clone());
            	else h1_elec_momentum->Add(h1_elec_momentum_d[i]);
            }
    	}

    	h1_elec_momentum->Rebin( 40 );
    	return h1_elec_momentum;
}


void AcceptanceCheck(TString cuts, TString Range, TString nucleus, TString E, double Eb) {

	TString GlobalPath = "/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/";


	TH1D::SetDefaultSumw2();
	std::vector<TH1D*> Plots; Plots.clear();
	std::vector<TString> FSILabel; FSILabel.clear();

	
	FSILabel.push_back("Truth");
	FSILabel.push_back("Truth_Reco");
	FSILabel.push_back("Reco");

	int NFSIModels = FSILabel.size();
	TString PathToFile;
	TString FileName;

	std::cout << "Analyzing " << cuts << ", Range " << Range << ", " << nucleus << ", E = " << Eb << "\n";
	for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

		// --------------------------------------------------------------------------------------
		PathToFile = GlobalPath + FSILabel[WhichFSIModel] + "/" ;
		FileName = cuts + "_" + "Range"+ Range + "_" + FSILabel[WhichFSIModel] + "_" + "Genie_" +"1_"+ nucleus + "_" + std::to_string(Eb);
		if(cuts == "Excl") Plots.push_back( (TH1D*)( SumProtSectorsAndInts(PathToFile + FileName + ".root", false) ) );
		if(cuts == "Incl") Plots.push_back( (TH1D*)( SumElecSectorsAndInts(PathToFile + FileName + ".root", false) ) );
	}

	TString CanvasName = FileName+"AccCorrCheckCanvas";
	TCanvas* PlotCanvas_Check = new TCanvas(CanvasName,CanvasName,205,34,1024,768);

	Plots[0]->SetLineColor(kBlack);
	Plots[1]->SetLineColor(kRed);
	Plots[2]->SetLineColor(kBlue);

	for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

		Plots[WhichFSIModel]->GetYaxis()->SetTitle("Event Rate");
		
		if(cuts == "Excl") {
			Plots[WhichFSIModel]->GetXaxis()->SetTitle("Proton momentum (GeV");
			if(Eb == 1.161)Plots[WhichFSIModel]->GetXaxis()->SetRangeUser(0.4,1.1);
			if(Eb == 2.261)Plots[WhichFSIModel]->GetXaxis()->SetRangeUser(0.5,1.2);
			if(Eb == 4.461)Plots[WhichFSIModel]->GetXaxis()->SetRangeUser(0.8,2.0);
		}
		if(cuts == "Incl") {
			Plots[WhichFSIModel]->GetXaxis()->SetTitle("Electron momentum (GeV");
			if(Eb == 1.161)Plots[WhichFSIModel]->GetXaxis()->SetRangeUser(0.7,1.2);
			if(Eb == 2.261)Plots[WhichFSIModel]->GetXaxis()->SetRangeUser(1.5,2.4);
			if(Eb == 4.461)Plots[WhichFSIModel]->GetXaxis()->SetRangeUser(3.0,4.6);
		}

		if (WhichFSIModel == 0) Plots[WhichFSIModel]->Draw("e hist");
		else Plots[WhichFSIModel]->Draw("e hist Same");

	}
	
	TLegend *legend = new TLegend( 0.2, 0.725, 0.35, 0.825);
	legend->AddEntry(Plots[0], "Signal");
	legend->AddEntry(Plots[1], "Signal Reco");
	legend->AddEntry(Plots[2], "Reco");
	legend->SetBorderSize(0);
	legend->SetFillStyle(0);
	legend->Draw();

	PlotCanvas_Check->SaveAs("Test/"+FileName+"_Acceptance_Check.png");
}

















