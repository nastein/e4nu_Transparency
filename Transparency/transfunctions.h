#ifndef TRANSFUNCTIONS_H
#define TRANSFUNCTIONS_H

#include <TF1.h>
#include <TString.h>
#include <TH1F.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>

#include "myFunctions.h"

void findmaxhist(TH1D *h1, TH1D *h2, TH1D* h3) {
	double max = 0.;
        
	if (h1->GetMaximum() > max) max = h1->GetMaximum();
	if (h2->GetMaximum() > max) max = h2->GetMaximum();
	if (h3->GetMaximum() > max) max = h3->GetMaximum();

	max *= 1.2;

	h1->GetYaxis()->SetRangeUser(0.,max);
	h2->GetYaxis()->SetRangeUser(0.,max);
	h3->GetYaxis()->SetRangeUser(0.,max);
	
}

double weighted_average(TH1D* h1) {
        double num_sum = 0.0;
        double den_sum = 0.0;
        for (int i = 0; i < h1->GetNbinsX(); i++) {
                if (h1->GetBinContent(i) == 0) continue;
                num_sum += h1->GetBinCenter(i)*h1->GetBinContent(i);
                den_sum += h1->GetBinContent(i);
        }

        if(isnan(num_sum/den_sum)) return 0.;
        return num_sum/den_sum;
}

double get_Neutron_corr(TString file, bool incl) {

        TFile *F = TFile::Open( TString( file ) );
        TH1D* hit_nuc;
        
        if (incl == true) {
                hit_nuc = (TH1D*)F->Get(TString::Format("h1_hit_nuc"));
        }

        if (incl == false) {
                hit_nuc = (TH1D*)F->Get("h1_hit_nuc_pass");
        }

        double protons = hit_nuc->GetBinContent(1);
        double neutrons = hit_nuc->GetBinContent(2);

        if((neutrons + protons) == 0.0) {std::cout << "file name: " << file << ", protons = " << protons << ", neutrons = " << neutrons << "\n"; return 0;}
        else return protons/(neutrons + protons);

}

double get_MEC_corr(TString file, int sector, bool incl, double threshold = 0.0) {   
        TFile *input = TFile::Open( TString( file ) );

        TH1D* mom_Int[4];
        TH1D* total;

        if( incl == true ) {
                for(int i = 0; i < 4; i++) {
                        mom_Int[i] = (TH1D*)input->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", i+1, sector));
                }
                
        }

        if( incl == false ) {
                for(int i = 0; i < 4; i++) {
                        mom_Int[i] = (TH1D*)input->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", i+1, sector));
                        for(int ibin = 0; ibin < mom_Int[i]->GetNbinsX(); ibin++) {
                                if(ibin < int(threshold*1000)) { //bins are 1MeV in size so 0-1 MeV is bin 1
                                        mom_Int[i]->SetBinContent(ibin+1, 0.);
                                }
                                else break;
                        }
                }
        }

        total = (TH1D*) mom_Int[0]->Clone();
        total->Add(mom_Int[1]); total->Add(mom_Int[2]); total->Add(mom_Int[3]);

        double mec_int = mom_Int[1]->Integral("width");
        double total_int = total->Integral("width");
        if (total_int == 0.0) return 0;

        return mec_int/total_int;
}

void ApplyMECcorr(TH1D &h1, double mec_corr[]) {
        if (h1.GetEntries() == 0) return;
        int nbins = h1.GetNbinsX();

        for(int WhichBin = 0; WhichBin < nbins; WhichBin ++){
                double bincontent = h1.GetBinContent(WhichBin+1);
                double binerror = h1.GetBinError(WhichBin +1);

                double corr_factor = (1 - mec_corr[1]);
                double corr_factor_low = (1 - mec_corr[0]);
                double corr_factor_high = (1 - mec_corr[2]);
                double corr_factor_unc = std::abs(corr_factor_high - corr_factor);


                double newbincontent = bincontent*(corr_factor);
                double newbinerror = sqrt(pow(bincontent*corr_factor_unc,2) + pow(binerror*corr_factor,2));
                
                h1.SetBinContent(WhichBin + 1, newbincontent);
                h1.SetBinError(WhichBin + 1, newbinerror);

        }
}

double get_MEC_corr_overall(TString file,  bool incl, double threshold = 0.0) {   
        TFile *input = TFile::Open( TString( file ) );

        TH1D* mom_Int[4][6];
        TH1D* MEC;
        TH1D* total;

        if( incl == true ) {
                for(int i = 0; i < 4; i++) {
                        for(int j = 0; j < 6; j++) {
                                mom_Int[i][j] = (TH1D*)input->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", i+1, j));
                                if(i == 0 && j == 0) total = (TH1D*)(mom_Int[i][j]->Clone());
                                else total->Add(mom_Int[i][j]);
                        }
                }
                
        }

        if( incl == false ) {
                for(int i = 0; i < 4; i++) {
                        for(int j = 0; j < 6; j++) {
                                mom_Int[i][j] = (TH1D*)input->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", i+1, j));
                                for(int ibin = 0; ibin < mom_Int[i][j]->GetNbinsX(); ibin++) {
                                        if(ibin < int(threshold*1000)) { //bins are 1MeV in size so 0-1 MeV is bin 1
                                                mom_Int[i][j]->SetBinContent(ibin+1, 0.);
                                        }
                                        else break;
                                }     
                                if(i == 0 && j == 0) total = (TH1D*)(mom_Int[i][j]->Clone());
                                else total->Add(mom_Int[i][j]);
                        }
                }
        }

        for(int j = 0; j < 6; j++) {
                if(j == 0) MEC = (TH1D*)(mom_Int[1][j]->Clone());
                else MEC->Add(mom_Int[1][j]);
        }

        double mec_int = MEC->Integral("width");
        double total_int = total->Integral("width");
        if (total_int == 0.0) return 0;

        return mec_int/total_int;
}

TH1D* SumElecInts(TString file, int sector, bool isData) {
        //std::cout << "file = " << file << ", sector = " << sector << ", r = " << r << "\n";
        TFile *input = TFile::Open( TString( file ) );

        TH1D* el_mom;
        TH1D* el_mom_Int[6];
        TH1D* el_mom_d;

        if ( isData == false ) { 
                        for (int i = 0; i < 4; i++) { // for all the interactions

                                // extract the histrograms
                                el_mom_Int[i] = (TH1D*)input->Get( TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", i+1, sector));
                                if( i == 0 ) el_mom = (TH1D*)( el_mom_Int[i]->Clone() );
                                else el_mom->Add(el_mom_Int[i]);
                        }
        }

        if ( isData == true ) {
                el_mom_d = (TH1D*)input->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", sector));
                el_mom = (TH1D*) ( el_mom_d->Clone() );
        }

        el_mom->Rebin( 40 );
        return el_mom;
}

TH1D* SumProtInts(TString file, int sector, bool isData, double threshold = 0.0) {
        TFile *input = TFile::Open( TString( file ) );

        TH1D* h1_prot_momentum;
        TH1D* h1_prot_momentum_d;
        TH1D* h1_prot_mom_InteractionBreakDown_inSector[4];

        if ( isData == false ) {
                for (int i = 0; i < 4; i++) { // for all the interactions

                        // extract the histrograms
                        h1_prot_mom_InteractionBreakDown_inSector[i] = (TH1D*)input->Get( TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", i+1, sector) );
                        for(int ibin = 0; ibin < h1_prot_mom_InteractionBreakDown_inSector[i]->GetNbinsX(); ibin++) {
                                if(ibin < int(threshold*1000)) { //bins are 1MeV in size so 0-1 MeV is bin 1
                                        h1_prot_mom_InteractionBreakDown_inSector[i]->SetBinContent(ibin+1, 0.);
                                }
                                else break;
                        }
                        if(i == 0) h1_prot_momentum = (TH1D*)( h1_prot_mom_InteractionBreakDown_inSector[i]->Clone() );
                        else h1_prot_momentum->Add( h1_prot_mom_InteractionBreakDown_inSector[i] );
                }
        }

        if ( isData == true ) {
               
                h1_prot_momentum_d = (TH1D*)input->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", sector));
                for(int ibin = 0; ibin < h1_prot_momentum_d->GetNbinsX(); ibin++) {
                        if(ibin < int(threshold*1000)) { //bins are 1MeV in size so 0-1 MeV is bin 1
                                h1_prot_momentum_d->SetBinContent(ibin+1, 0.);
                        }
                        else break;
                }
                h1_prot_momentum = (TH1D*)( h1_prot_momentum_d->Clone() );
        }

        h1_prot_momentum->Rebin( 40 );
        return h1_prot_momentum;
}

TH1D* AcceptanceCorrect(TH1D* hist, TH1D* susa_true, TH1D* susa_truereco, TH1D* G_true, TH1D* G_truereco, TH1D* susa_truereco_rad, bool make_plots, std::string type, std::string nucleus, TH1D* sf_true = NULL, TH1D* sf_truereco = NULL) {

        gStyle->SetOptStat(0);
        gStyle->SetOptTitle(0);

        //Make sure we have a non empty histogram
        if(hist->GetEntries() == 0.0) return hist;
        
        TH1D::SetDefaultSumw2();

	TH1D* reco = (TH1D*)hist->Clone();
	TH1D* corrected_reco;

        TH1D* OverallClone = (TH1D*)hist->Clone();

        TH1D* susa_correction = (TH1D*)susa_true->Clone();
        TH1D* G_correction = (TH1D*)G_true->Clone();
        TH1D* sf_correction;

        if(type == "SF" && sf_true !=NULL) {
                sf_correction = (TH1D*)sf_true->Clone();
                sf_correction->Divide(sf_truereco);
        }

        susa_correction->Divide(susa_truereco);
        G_correction->Divide(G_truereco);

        TH1D* Average = (TH1D*)(susa_correction->Clone());
        Average->Add(G_correction);
        Average->Scale(0.5);

        int p;
        double E;
        int r;

        std::string energy;

        if(std::string(hist->GetTitle()).find("2.261") != std::string::npos) {E = 2.261; energy = "2_261";}
        else {E = 4.461; energy = "4_461";}

        TH1D* RadCorrection = (TH1D*)susa_truereco->Clone();
        RadCorrection->Divide(susa_truereco_rad);

        if(std::string(hist->GetTitle()).find("Excl") != std::string::npos) p = 0;
        else p = 1;

        if(std::string(hist->GetTitle()).find("Range 1") != std::string::npos) r = 0;
        if(std::string(hist->GetTitle()).find("Range 2") != std::string::npos) r = 1;
        if(std::string(hist->GetTitle()).find("Range 3") != std::string::npos) r = 2;
        if(std::string(hist->GetTitle()).find("Range 4") != std::string::npos) r = 3;

        std::string nuc_no_A;
        if(nucleus == "12C") nuc_no_A = "C";
        if(nucleus == "56Fe") nuc_no_A = "Fe";
        if(nucleus == "4He") nuc_no_A = "He";
        
        int NBins = OverallClone->GetXaxis()->GetNbins();
        double AccCorrTolerance = 5.0;
        //double RadCorrTolerance = 2.0;

	double sum_of_corr = 0.0;

        for (int WhichBin = 0; WhichBin < NBins; WhichBin++) {
                double AccCorr = 0.;
                double RadCorr = 0.;

                double NewBinContent = 0.;
                double NewBinError = 0.;

                if(type == "G") AccCorr = G_correction->GetBinContent(WhichBin + 1);
                else if(type == "SF" && sf_true != NULL) {
                        AccCorr = sf_correction->GetBinContent(WhichBin + 1);
                }
                else if(type == "SuSA") AccCorr = susa_correction->GetBinContent(WhichBin + 1);

                else AccCorr = Average->GetBinContent(WhichBin + 1);

                if (AccCorr < 0 || AccCorr > AccCorrTolerance) {
                        double CorrectionSuSav2Bin = susa_correction->GetBinContent(WhichBin + 1);
                        double CorrectionG2018Bin = G_correction->GetBinContent(WhichBin + 1);

                        if (CorrectionSuSav2Bin > 0 && CorrectionSuSav2Bin < AccCorrTolerance) { AccCorr = CorrectionSuSav2Bin; }
                        else if (CorrectionG2018Bin > 0 && CorrectionG2018Bin < AccCorrTolerance) { AccCorr = CorrectionG2018Bin; }
                        else { AccCorr = 0.; }

                }

                //If the GENIE correction is 0, then we don't want to use it as the acceptance correction
                if(type == "data" && G_correction->GetBinContent(WhichBin + 1) < (0.2)) AccCorr = susa_correction->GetBinContent(WhichBin + 1);
                
                
                RadCorr = RadCorrection->GetBinContent(WhichBin + 1);

		sum_of_corr+=RadCorr;

                if(RadCorr <= 0.) RadCorr = 1.;
                if(AccCorr <= 0.) AccCorr = 1.;
                if(type != "data") RadCorr = 1.;


		//std::cout << "Type = " << type << ", RadCorr = " << RadCorr << "\n";	

		//RadCorr = 1.;	

                NewBinContent = hist->GetBinContent(WhichBin + 1) * AccCorr * RadCorr;
                NewBinError = hist->GetBinError(WhichBin + 1) * AccCorr * RadCorr;

                OverallClone->SetBinContent(WhichBin + 1, NewBinContent);
                OverallClone->SetBinError(WhichBin + 1, NewBinError);
        }
	std::cout << "Type = " << type << "\n";
        std::cout << "Sum of radiative corrections = " << sum_of_corr << "\n";

	corrected_reco = (TH1D*)OverallClone->Clone(); 

        TH1D* Spread = (TH1D*)susa_correction->Clone();
        Spread->Add(G_correction, -1);
        Spread->Divide(Average);
        Spread->Scale(1./TMath::Sqrt(12.));

        int NBinsSpread = Spread->GetXaxis()->GetNbins();

        for (int WhichBin = 0; WhichBin < NBinsSpread; WhichBin++) {

                double BinContent = Spread->GetBinContent(WhichBin+1);
                if (BinContent < 0) { Spread->SetBinContent(WhichBin+1,-BinContent); }

        }
        
        if(type == "data") {
                for (int WhichBin = 0; WhichBin < NBinsSpread; WhichBin++) {

                        double SpreadBinContent = Spread->GetBinContent(WhichBin+1);

                        //If the GENIE correction is 0, then we don't want to use it as the acceptance correction
                        if(G_correction->GetBinContent(WhichBin + 1) < (0.2)) SpreadBinContent = 0.0;

                        double XSecBinError = OverallClone->GetBinError(WhichBin+1);
                        double XSecBinEntry = OverallClone->GetBinContent(WhichBin+1);
                        double AccCorrError = SpreadBinContent * XSecBinEntry;
                        //std::cout << "Previous error = " << XSecBinError << "\n";

                        //std::cout << "acc percent error = " << SpreadBinContent << "\n";
                        //std::cout << "Bin Content: " << XSecBinEntry << "\n";
                        //std::cout << "Acc % * Bin Content: " << XSecBinEntry * SpreadBinContent << "\n";
                        //std::cout << "New error should = " << sqrt(pow(XSecBinError,2) + pow(XSecBinEntry*SpreadBinContent,2)) << "\n";
                        double NewXSecBinError = TMath::Sqrt( TMath::Power(XSecBinError,2.) + TMath::Power(AccCorrError,2.) );
                        if(NewXSecBinError < XSecBinError) {
                                std::cout << "Something wrong, errors should increase!" << "\n";
                                std::cout << "Previous bin error: " << XSecBinError << "\n";
                                std::cout << "Updated bin error: " << NewXSecBinError << "\n";
                        }
                        //std::cout << "New error = " << NewXSecBinError << "\n";
                        OverallClone->SetBinError(WhichBin+1,NewXSecBinError);

                }
        }
        
	std::string mylabel;
	if(type == "G") mylabel = "hA2018_Final_NoRadCorr_LFGM";
	if(type == "SuSA") mylabel = "SuSav2_NoRadCorr_LFGM_Truth_WithFidAcc"; 

	if(make_plots) {UniversalE4vFunction(corrected_reco,FSIModelsToLabels[mylabel], nucleus, energy, TString::Format("corrected reco"));
	UniversalE4vFunction(reco,FSIModelsToLabels[mylabel], nucleus, energy, TString::Format("reco"));}

        if(make_plots) {
                TString tSCanvasName = TString::Format("true_vs_reco_%s",hist->GetTitle());
                TCanvas* tSPlotCanvas = new TCanvas(tSCanvasName,tSCanvasName,205,34,1024,768);
                PrettyDoubleXSecPlot(corrected_reco, p, E, r, true);
                PrettyDoubleXSecPlot(reco, p, E, r, true);
		PrettyDoubleXSecPlot(susa_true, p, E, r, true);
                //PrettyDoubleXSecPlot(susa_truereco, p, E, r, true);
		PrettyDoubleXSecPlot(G_true, p, E, r, true);
                PrettyDoubleXSecPlot(G_truereco, p, E, r, true);
                susa_true->SetTitle(TString::Format("True SuSav2 %s",hist->GetTitle()));
                susa_truereco->SetTitle(TString::Format("Reco SuSav2 %s",hist->GetTitle()));
        	G_true->SetTitle(TString::Format("True G18 %s",hist->GetTitle()));
                G_truereco->SetTitle(TString::Format("Reco G18 %s",hist->GetTitle()));        
		corrected_reco->SetTitle(TString::Format("Corrected Reco %s",hist->GetTitle()));
                reco->SetTitle(TString::Format("Reco %s",hist->GetTitle()));	

		corrected_reco->SetMarkerColor(kBlue); corrected_reco->SetMarkerStyle(kFullCircle); corrected_reco->SetMarkerSize(1.2);
		reco->SetMarkerColor(kBlack); reco->SetMarkerStyle(kFullCircle); reco->SetMarkerSize(1.2);

		susa_true->SetLineColor(kBlue);
		//susa_truereco->SetLineStyle(kDashed);
		susa_truereco->SetLineColor(kBlue);
        
		susa_true->GetYaxis()->SetRangeUser(0, G_true->GetMaximum() * 1.1);
	        susa_true->Draw("hist");
                susa_truereco->Draw("hist same");
		G_true->SetLineColor(kRed);
		G_truereco->SetLineColor(kRed);
		G_truereco->SetLineStyle(kDashed);
                G_true->Draw("hist same");
                G_truereco->Draw("hist same");

		corrected_reco->Draw("p same");
		reco->Draw("p same");

                TLegend *accSLegend = new TLegend(.82,.65,.99,.85);
                accSLegend->AddEntry(susa_true, "SuSAv2 True","l"); 
                accSLegend->AddEntry(susa_truereco, "SuSAv2 TrueReco","l");
		accSLegend->AddEntry(G_true, "G18 True","l");
                accSLegend->AddEntry(G_truereco, "G18 TrueReco","l");
		accSLegend->AddEntry(corrected_reco, "SuSAv2 Corrected Reco", "p");
		accSLegend->AddEntry(reco, "SuSAv2 Reco", "p"); 
                accSLegend->SetBorderSize(0);
                accSLegend->Draw();
                tSPlotCanvas->SetLeftMargin( 0.2);
                tSPlotCanvas->SetBottomMargin( 0.2);
                tSPlotCanvas->SetRightMargin(0.2);
                tSPlotCanvas->Update();
                tSPlotCanvas->SaveAs(TString::Format("%s/%s_%s.pdf",nucleus.c_str(),nucleus.c_str(), tSCanvasName.Data()));

                if(type == "SF" && sf_true !=NULL) {
                        TString tSFCanvasName = TString::Format("SF_true_vs_reco_%s",hist->GetTitle());
                        TCanvas* tSFPlotCanvas = new TCanvas(tSFCanvasName,tSFCanvasName,205,34,1024,768);
                        PrettyDoubleXSecPlot(sf_true, p, E, r, false);
                        PrettyDoubleXSecPlot(sf_truereco, p, E, r, false);
                        sf_true->GetYaxis()->SetTitle("Scaled number of events");
                        sf_true->SetTitle(TString::Format("True SF %s",hist->GetTitle()));
                        sf_truereco->SetTitle(TString::Format("Reco SF %s",hist->GetTitle()));
                        sf_true->SetLineColor(kRed);
                        sf_true->Draw("e hist");
                        sf_truereco->Draw("e hist same");
                        TLegend *accSFLegend = new TLegend(.82,.65,.99,.85);
                        accSFLegend->AddEntry(sf_true, "True"); 
                        accSFLegend->AddEntry(sf_truereco, "Reco"); 
                        accSFLegend->SetBorderSize(0);
                        accSFLegend->Draw();
                        tSFPlotCanvas->SetLeftMargin( 0.2);
                        tSFPlotCanvas->SetBottomMargin( 0.2);
                        tSFPlotCanvas->SetRightMargin(0.2);
                        tSFPlotCanvas->Update();
                        tSFPlotCanvas->SaveAs(TString::Format("%s/%s_%s.pdf",nucleus.c_str(),nucleus.c_str(), tSFCanvasName.Data()));
                }

                TString trCanvasName = TString::Format("truerecorad_vs_trueoreco_%s",hist->GetTitle());
                TCanvas* trPlotCanvas = new TCanvas(trCanvasName,trCanvasName,205,34,1024,768);
                PrettyDoubleXSecPlot(susa_truereco, p, E, r, false);
                PrettyDoubleXSecPlot(susa_truereco_rad, p, E, r, false);
                susa_truereco->Draw("e hist");
                susa_truereco->SetLineColor(kBlack);
                susa_truereco_rad->SetLineColor(kBlue);
                susa_truereco_rad->SetTitle(TString::Format("Reco Rad %s",hist->GetTitle()));
                susa_truereco_rad->Draw("e hist same");
                TLegend *radLegend = new TLegend(.82,.65,.99,.85);
                radLegend->AddEntry(susa_truereco, "Nominal");
                radLegend->AddEntry(susa_truereco_rad, "Radiative");
                radLegend->SetBorderSize(0);
                radLegend->Draw();
                trPlotCanvas->SetLeftMargin( 0.2);
                trPlotCanvas->SetBottomMargin( 0.2);
                trPlotCanvas->SetRightMargin(0.2);
                trPlotCanvas->Update();
                trPlotCanvas->SaveAs(TString::Format("%s/%s_%s.pdf",nucleus.c_str(),nucleus.c_str(), trCanvasName.Data()));

                TString CanvasName = TString::Format("Acceptance_Ratio_%s",hist->GetTitle());
                TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
                PrettyDoubleXSecPlot(Average, p, E, 4, false);
                PrettyDoubleXSecPlot(susa_correction, p, E, 4, false);
                PrettyDoubleXSecPlot(G_correction, p, E, 4, false);
                susa_correction->SetLineColor(kRed);
                G_correction->SetLineColor(kBlue);
                Average->SetLineColor(kBlack);
                Average->GetYaxis()->SetTitle("Detector Acceptance Correction");
                susa_correction->Draw("e hist");
                Average->Draw("e hist same");
                G_correction->Draw("e hist same");
                TLegend *corrLegend = new TLegend(.82,.65,.99,.85);
                corrLegend->AddEntry(Average, "Average");
                corrLegend->AddEntry(susa_correction, "SuSAv2");
                corrLegend->AddEntry(G_correction, "G18");
                corrLegend->SetBorderSize(0);
                if(sf_true != NULL) {
                        PrettyDoubleXSecPlot(sf_correction, p, E, 4, false);
                        sf_correction->SetLineColor(kGreen);
                        sf_correction->Draw("e hist same");
                        corrLegend->AddEntry(sf_correction, "SF");
                }
                corrLegend->Draw(); 
                Average->SetTitle(TString::Format("%s",hist->GetTitle()));
                PlotCanvas->SetLeftMargin( 0.2);
                PlotCanvas->SetBottomMargin( 0.2);
                PlotCanvas->SetRightMargin(0.2);
                PlotCanvas->Update();
                PlotCanvas->SaveAs(TString::Format("%s/%s_%s.pdf",nucleus.c_str(),nucleus.c_str(), CanvasName.Data()));

                TString RadCanvasName = TString::Format("Rad_Ratio_%s",hist->GetTitle());
                TCanvas* RadPlotCanvas = new TCanvas(RadCanvasName,RadCanvasName,205,34,1024,768);
                PrettyDoubleXSecPlot(RadCorrection, p, E, 4, false);
                RadCorrection->GetYaxis()->SetTitle("Radiative Correction");
                RadCorrection->SetTitle(TString::Format("%s", hist->GetTitle()));
                RadCorrection->Draw("e hist");
                RadPlotCanvas->SetLeftMargin( 0.2);
                RadPlotCanvas->SetBottomMargin( 0.2);
                RadPlotCanvas->Update();
                RadPlotCanvas->SaveAs(TString::Format("%s/%s_%s.pdf",nucleus.c_str(),nucleus.c_str(), RadCanvasName.Data()));
        }

        return OverallClone;
}

TH1D* AcceptanceCorrectSF(TH1D* hist, TH1D* SF_true, TH1D* SF_truereco, TH1D* susa_true, TH1D* susa_truereco, TH1D* G_true, TH1D* G_truereco, TH1D* susa_truereco_rad, bool make_plots, std::string type, std::string nucleus) {

        //Make sure we have a non empty histogram
        if(hist->GetEntries() == 0.0) return hist;
        
        TH1D::SetDefaultSumw2();

        TH1D* OverallClone = (TH1D*)hist->Clone();

        TH1D* susa_correction = (TH1D*)susa_true->Clone();
        TH1D* G_correction = (TH1D*)G_true->Clone();

        susa_correction->Divide(susa_truereco);
        G_correction->Divide(G_truereco);

        TH1D* AverageGS = (TH1D*)(susa_correction->Clone());
        AverageGS->Add(G_correction);
        AverageGS->Scale(0.5);

        TH1D* correction = (TH1D*)SF_true->Clone();
        correction->Divide(SF_truereco);

        TH1D* Average = (TH1D*)(correction->Clone());

        TH1D* RadCorrection = (TH1D*)susa_truereco->Clone();
        RadCorrection->Divide(susa_truereco_rad);

        int p;
        double E;
        int r;

        if(std::string(hist->GetTitle()).find("2.261") != std::string::npos) E = 2.261;
        else E = 4.461;

        if(std::string(hist->GetTitle()).find("Excl") != std::string::npos) p = 0;
        else p = 1;

        if(std::string(hist->GetTitle()).find("Range 1") != std::string::npos) r = 0;
        if(std::string(hist->GetTitle()).find("Range 2") != std::string::npos) r = 1;
        if(std::string(hist->GetTitle()).find("Range 3") != std::string::npos) r = 2;

        if(make_plots) {
                TString tCanvasName = TString::Format("true_vs_reco_%s",hist->GetTitle());
                TCanvas* tPlotCanvas = new TCanvas(tCanvasName,tCanvasName,205,34,1024,768);
                tPlotCanvas->SetLeftMargin(0.2);
                tPlotCanvas->SetBottomMargin(0.2);
                tPlotCanvas->SetRightMargin(0.2);
                PrettyDoubleXSecPlot(SF_true, p, E, r, false);
                PrettyDoubleXSecPlot(SF_truereco, p, E, r, false);
                SF_true->GetYaxis()->SetTitle("Scaled number of events");
                SF_true->GetXaxis()->SetTitle("Momentum (GeV)");
                SF_true->SetTitle(TString::Format("True %s",hist->GetTitle()));
                SF_truereco->SetTitle(TString::Format("Reco %s",hist->GetTitle()));
                SF_true->SetLineColor(kRed);
                SF_true->Draw("e hist");
                SF_truereco->Draw("e hist same");
                TLegend *accLegend = new TLegend(.82,.65,.99,.85);
                accLegend->AddEntry(SF_true, "True"); 
                accLegend->AddEntry(SF_truereco, "Reco"); 
                accLegend->SetBorderSize(0);
                accLegend->Draw();
                tPlotCanvas->SaveAs("C12_true_vs_truereco.pdf");


                TString trCanvasName = TString::Format("radrec_vs_noradreco_%s",hist->GetTitle());
                TCanvas* trPlotCanvas = new TCanvas(trCanvasName,trCanvasName,205,34,1024,768);

                trPlotCanvas->SetLeftMargin(0.2);
                trPlotCanvas->SetBottomMargin(0.2);
                trPlotCanvas->SetRightMargin(0.2);
                PrettyDoubleXSecPlot(susa_true, p, E, r, false);
                PrettyDoubleXSecPlot(susa_truereco, p, E, r, false);
                susa_truereco->GetYaxis()->SetTitle("Scaled number of events");
                susa_truereco->GetXaxis()->SetTitle("Momentum (GeV)");
                susa_truereco->Draw("e hist");
                susa_truereco->SetLineColor(kBlack);
                susa_truereco_rad->SetLineColor(kBlue);
                susa_truereco_rad->SetTitle(TString::Format("Reco Rad %s",hist->GetTitle()));
                susa_truereco_rad->Draw("e hist same");
                TLegend *radLegend = new TLegend(.82,.65,.99,.85);
                radLegend->AddEntry(susa_truereco, "Nominal");
                radLegend->AddEntry(susa_truereco_rad, "Radiative");
                radLegend->SetBorderSize(0);
                radLegend->Draw();
                trPlotCanvas->SaveAs("C12_truerecorad_vs_truereco.pdf");
        }
        
        int NBins = OverallClone->GetXaxis()->GetNbins();
        double AccCorrTolerance = 10.;

        for (int WhichBin = 0; WhichBin < NBins; WhichBin++) {
                double AccCorr = 0.;
                double RadCorr = 0.;

                double NewBinContent = 0.;
                double NewBinError = 0.;

                AccCorr = Average->GetBinContent(WhichBin + 1);
                RadCorr = RadCorrection->GetBinContent(WhichBin + 1);

                if(RadCorr <= 0.) RadCorr = 1.;
                if(AccCorr <= 0.) AccCorr = 1.;
                if(type != "data") RadCorr = 1.;
                //AccCorr = 1.;
                NewBinContent = hist->GetBinContent(WhichBin + 1) * AccCorr * RadCorr;
                NewBinError = hist->GetBinError(WhichBin + 1) * AccCorr * RadCorr;

                OverallClone->SetBinContent(WhichBin + 1, NewBinContent);
                OverallClone->SetBinError(WhichBin + 1, NewBinError);
        }

        if(make_plots) {
          TString CanvasName = TString::Format("AccCorrCanvas_%s",hist->GetTitle());
          TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
          PlotCanvas->SetLeftMargin(0.2);
          PlotCanvas->SetBottomMargin(0.2);
          PlotCanvas->SetRightMargin(0.2);
          Average->GetYaxis()->SetTitle("Detector Acceptance Correction");
          Average->GetXaxis()->SetTitle("Momentum (GeV)");
          PrettyDoubleXSecPlot(Average, p, E, 4, false);
          PrettyDoubleXSecPlot(AverageGS, p, E, 4, false);
          PrettyDoubleXSecPlot(susa_correction, p, E, 4, false);
          PrettyDoubleXSecPlot(G_correction, p, E, 4, false);
          Average->SetLineColor(kBlack);
          AverageGS->SetLineColor(kGreen);
          susa_correction->SetLineColor(kRed);
          G_correction->SetLineColor(kBlue);
          Average->Draw("e hist");
          susa_correction->Draw("e hist same");
          G_correction->Draw("e hist same");
          AverageGS->Draw("e hist same");
          Average->SetTitle(TString::Format("%s",hist->GetTitle()));
          TLegend *corrLegend = new TLegend(.82,.65,.99,.85);
          corrLegend->AddEntry(Average, "SF");
          corrLegend->AddEntry(AverageGS, "SuSA:G18 Average");
          corrLegend->AddEntry(susa_correction, "SuSAv2");
          corrLegend->AddEntry(G_correction, "G18");
          corrLegend->SetBorderSize(0);
          corrLegend->Draw();
          PlotCanvas->SaveAs("C12_Acceptance_Ratios.pdf");

          TString RadCanvasName = TString::Format("RadCorrCanvas_%s",hist->GetTitle());
          TCanvas* RadPlotCanvas = new TCanvas(RadCanvasName,RadCanvasName,205,34,1024,768);
                RadPlotCanvas->SetLeftMargin( 0.2);
                RadPlotCanvas->SetBottomMargin( 0.2);
                RadPlotCanvas->SetRightMargin(0.2);
                RadPlotCanvas->Update();
          RadCorrection->GetYaxis()->SetTitle("Radiative Correction");
          RadCorrection->GetXaxis()->SetTitle("Momentum (GeV)");
          RadCorrection->SetTitle(TString::Format("%s", hist->GetTitle()));
          RadCorrection->Draw("e hist");
          RadPlotCanvas->SaveAs("C12_Rad_Ratios.pdf");
        }

        return OverallClone;
}
/*
double get_ratio_error(double num, double denom, double num_err, double denom_err) {
        // Binomial errors for transparency ratio
        if (denom == 0. || isnan(num) || isnan(denom)) {
                std::cout << "Is this happening?" << "\n";
                return 0.;
        }

        double num_stat_err = sqrt(num);
        double denom_stat_err = sqrt(denom);

        std::cout << "Numerator err = " << num_err << "\n";
        std::cout << "Denominator err = " << denom_err << "\n";
        std::cout << "Numerator stat err = " << num_stat_err << "\n";
        std::cout << "Denominator stat err = " << denom_stat_err << "\n";

        double num_err_sys = sqrt(num_err*num_err - num_stat_err*num_stat_err);
        double denom_err_sys = sqrt(denom_err*denom_err - denom_stat_err*denom_stat_err);


        std::cout << "Numerator sys err = " << num_err_sys << "\n";
        std::cout << "Denominator sys err = " << denom_err_sys << "\n";

        double err = 0;
        std::map<int,std::vector<double>> combos;
        std::vector<double> low_low = {-num_err_sys, -denom_err_sys};
        std::vector<double> low_high = {-num_err_sys, denom_err_sys};
        std::vector<double> high_high = {num_err_sys, denom_err_sys};
        std::vector<double> high_low = {num_err_sys, -denom_err_sys};
        combos[0] = low_low; combos[1] = low_high; combos[2] = high_high; combos[3] = high_low;
        std::map <int, std::string> sys_string = {{0, "low low"}, {1, "low high"}, {2, "high high"}, {3, "high low"}};

        double pstat = num/denom;
        double qstat = (1 - pstat);
        double stat_err = sqrt(pstat*qstat/denom);

        for(int i = 0; i < 4; i++) {
                double p = (num + combos[i][0])/(denom + combos[i][1]);
                double q = 1. - p;
                double temp_err = sqrt(p*q/(denom+combos[i][1]));
                if (temp_err > err) err = temp_err;
                std::cout << "total error for " << sys_string[i] << " = " << temp_err << "\n";
        }
        std::cout << "Stat err = " << stat_err << ", Total err = " << err << "\n";
        return err;
}
*/

double get_ratio_error(double num, double denom, double num_err, double denom_err) {

        TH1D::SetDefaultSumw2();
        TH1D* h_num = new TH1D("num", "num", 1, 0, 1);
        TH1D* h_denom = new TH1D("denom", "denom", 1, 0, 1);

        h_num->SetBinContent(1, num); h_num->SetBinError(1, num_err);
        h_denom->SetBinContent(1, denom); h_denom->SetBinError(1, denom_err);

        //std::cout << "num = " << h_num->GetBinContent(1) << ", num err = " << h_num->GetBinError(1) << "\n";
        //std::cout << "denom = " << h_denom->GetBinContent(1) << ", denom err = " << h_denom->GetBinError(1) << "\n";

        //h_num->Divide(h_num,h_denom, 1, 1, "b");
        TGraphAsymmErrors *g = new TGraphAsymmErrors(h_num,h_denom,"cl=0.683 b(1,1) mode");
        double trans = num/denom;
        double trans_err_low = g->GetErrorYlow(0);
        double trans_err_high = g->GetErrorYhigh(0);
        //double trans = h_num->GetBinContent(1);
        //double trans_err = h_num->GetBinError(1);

        //std::cout << "Transparency = " << trans << " + " << trans_err_high << " - " << trans_err_low << "\n";
        delete h_num;
        delete h_denom;

        return g->GetErrorY(0);


}

double get_ratio_error_ind(double num, double num_err, double denom, double denom_err) {
        return (num/denom)*sqrt(pow(num_err/num,2) + pow(denom_err/denom,2));
}

void printit(std::string s, double x) {
        std::cout << s << " = " << x << "\n";
}

double diff_squared(double x, double y) {
        if (isnan(x) || isnan(y) || x == 0.0 || y == 0.0) return 0.;
        //std::cout << (x-y)*(x-y) << "\n";
        return (x - y)*(x - y); 
}

double weighted_var(double x[], double x_err[], std::vector<int> sects) {
        double weight_sum = 0.;
        double num_sum = 0.;
        double weighted_mean = 0;
        double var = 0.;
        for(int s: sects) {
                if(x[s] == 0 || isnan(x[s])) continue;
                num_sum += x[s]*pow(x_err[s],-2);
                weight_sum += pow(x_err[s],-2);
                //std::cout << "num_sum = " << num_sum << "\n";
                //std::cout << "weight_sum = " << weight_sum << "\n";
        }
        weighted_mean = num_sum/weight_sum;
        //std::cout << weighted_mean << "\n";

        double error_sum = 0;

        for(int s: sects) { 
                if(x[s] == 0) continue;
                var+= pow(x[s] - weighted_mean,2);
                error_sum+= pow(x_err[s],2);
        }

        //std::cout << "var = " << var << "\n";
        //std::cout << "error_sum = " << error_sum << "\n";
        if (var < error_sum) return 0.0;
        
        var = sqrt((var - error_sum)/sects.size());
        return var;
}

double myratio(double x, double y) {
        if(y == 0. || isnan(x) || isnan(y)) {std::cout << "dividing by 0 or bad input" << "\n";return 0.;};
        if (x > y) {
                std::cout << "Something is wrong!" << "\n";
                std::cout << "Ratio = " << x/y << "\n";
        }
        return x/y;
}



#endif
