#ifndef TRANSFUNCTIONS_H
#define TRANSFUNCTIONS_H

#include <TF1.h>
#include <TString.h>
#include <TH1F.h>
#include <TFile.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>

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
                hit_nuc = (TH1D*)F->Get("h1_hit_nuc");
        }

        if (incl == false) {
                hit_nuc = (TH1D*)F->Get("h1_hit_nuc_pass");
        }

        double protons = hit_nuc->GetBinContent(1);
        double neutrons = hit_nuc->GetBinContent(2);

        if((neutrons + protons) == 0.0) return 0;
        else return protons/(neutrons + protons);

}

double get_MEC_corr(TString file, int sector, bool incl) {   
        TFile *input = TFile::Open( TString( file ) );

        TH1D* mom_Int[4];
        TH1D* total;

        if( incl == true ) {
                for(int i = 0; i < 4; i++) {
                        mom_Int[i] = (TH1D*)input->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", i+1, (sector) ));
                }
                
        }

        if( incl == false ) {
                for(int i = 0; i < 4; i++) {
                        mom_Int[i] = (TH1D*)input->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", i+1, sector));
                }
        }

        total = (TH1D*) mom_Int[0]->Clone();
        total->Add(mom_Int[1]); total->Add(mom_Int[2]); total->Add(mom_Int[3]);

        double mec_int = mom_Int[1]->Integral("width");
        double total_int = total->Integral("width");
        if (total_int == 0.0) return 0;

        return mec_int/total_int;
}

double get_MEC_corr_overall(TString file,  bool incl) {   
        TFile *input = TFile::Open( TString( file ) );

        TH1D* mom_Int[4][6];
        TH1D* MEC;
        TH1D* total;

        if( incl == true ) {
                for(int i = 0; i < 4; i++) {
                        for(int j = 0; j < 6; j++) {
                                mom_Int[i][j] = (TH1D*)input->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", i+1, j ));
                                if(i == 0 && j == 0) total = (TH1D*)(mom_Int[i][j]->Clone());
                                else total->Add(mom_Int[i][j]);
                        }
                }
                
        }

        if( incl == false ) {
                for(int i = 0; i < 4; i++) {
                        for(int j = 0; j < 6; j++) {
                                mom_Int[i][j] = (TH1D*)input->Get(TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", i+1, j));
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
        TFile *input = TFile::Open( TString( file ) );

        TH1D* el_mom;
        TH1D* el_mom_Int[6];
        TH1D* el_mom_d;

        if ( isData == false ) { 
                        for (int i = 0; i < 4; i++) { // for all the interactions

                                // extract the histrograms
                                el_mom_Int[i] = (TH1D*)input->Get( TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", i+1, (sector) ));
                                if( i == 0 ) el_mom = (TH1D*)( el_mom_Int[i]->Clone() );
                                else el_mom->Add(el_mom_Int[i]);
                        }
        }

        if ( isData == true ) {
                el_mom_d = (TH1D*)input->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", (sector) ));
                el_mom = (TH1D*) ( el_mom_d->Clone() );
        }

        el_mom->Rebin( 30 );
        return el_mom;
}

TH1D* SumProtInts(TString file, int sector, bool isData) {
        TFile *input = TFile::Open( TString( file ) );

        TH1D* h1_prot_momentum;
        TH1D* h1_prot_momentum_d;
        TH1D* h1_prot_mom_InteractionBreakDown_inSector[4];

        if ( isData == false ) {
                for (int i = 0; i < 4; i++) { // for all the interactions

                        // extract the histrograms
                        h1_prot_mom_InteractionBreakDown_inSector[i] = (TH1D*)input->Get( TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", i+1, sector) );
                        if(i == 0) h1_prot_momentum = (TH1D*)( h1_prot_mom_InteractionBreakDown_inSector[i]->Clone() );
                        else h1_prot_momentum->Add( h1_prot_mom_InteractionBreakDown_inSector[i] );
                }
        }

        if ( isData == true ) {
               
                h1_prot_momentum_d = (TH1D*)input->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", sector));
                h1_prot_momentum = (TH1D*)( h1_prot_momentum_d->Clone() );
        }

        h1_prot_momentum->Rebin( 30 );
        return h1_prot_momentum;
}

TH1D* AcceptanceCorrect(TH1D* hist, TH1D* susa_true, TH1D* susa_truereco, TH1D* G_true, TH1D* G_truereco, TH1D* susa_truereco_rad, bool make_plots, std::string type) {

        //Make sure we have a non empty histogram
        if(hist->GetEntries() == 0.0) return hist;
        
        TH1D::SetDefaultSumw2();

        TH1D* OverallClone = (TH1D*)hist->Clone();

        TH1D* susa_correction = (TH1D*)susa_true->Clone();
        TH1D* G_correction = (TH1D*)G_true->Clone();

        susa_correction->Divide(susa_truereco);
        G_correction->Divide(G_truereco);

        TH1D* Average = (TH1D*)(susa_correction->Clone());
        Average->Add(G_correction);
        Average->Scale(0.5);

        TH1D* RadCorrection = (TH1D*)susa_truereco->Clone();
        RadCorrection->Divide(susa_truereco_rad);

        if(make_plots) {
                TString tCanvasName = TString::Format("true_vs_reco_%s",hist->GetTitle());
                TCanvas* tPlotCanvas = new TCanvas(tCanvasName,tCanvasName,205,34,1024,768);
                if(type == "SuSA") {
                        susa_true->GetYaxis()->SetTitle("Scaled number of events");
                        susa_true->GetXaxis()->SetTitle("Momentum (GeV)");
                        susa_true->SetTitle(TString::Format("True %s",hist->GetTitle()));
                        susa_truereco->SetTitle(TString::Format("Reco %s",hist->GetTitle()));
                        susa_true->SetLineColor(kRed);
                        susa_true->Draw("e hist");
                        susa_truereco->Draw("e hist same");
                }
                if(type == "G") {
                        G_true->GetYaxis()->SetTitle("Scaled number of events");
                        G_true->GetXaxis()->SetTitle("Momentum (GeV)");
                        G_true->SetTitle(TString::Format("True %s",hist->GetTitle()));
                        G_truereco->SetTitle(TString::Format("Reco %s",hist->GetTitle()));
                        G_true->SetLineColor(kRed);
                        G_true->Draw("e hist");
                        G_truereco->Draw("e hist same"); 
                }
                tPlotCanvas->BuildLegend();
                tPlotCanvas->SaveAs("C12_true_vs_truereco.pdf");


                TString trCanvasName = TString::Format("radrec_vs_noradreco_%s",hist->GetTitle());
                TCanvas* trPlotCanvas = new TCanvas(trCanvasName,trCanvasName,205,34,1024,768);
                susa_truereco->GetYaxis()->SetTitle("Scaled number of events");
                susa_truereco->GetXaxis()->SetTitle("Momentum (GeV)");
                susa_truereco->Draw("e hist");
                susa_truereco->SetLineColor(kBlack);
                susa_truereco_rad->SetLineColor(kGreen);
                susa_truereco_rad->SetTitle(TString::Format("Reco Rad %s",hist->GetTitle()));
                susa_truereco_rad->Draw("e hist same");
                trPlotCanvas->BuildLegend();
                trPlotCanvas->SaveAs("C12_truerecorad_vs_truereco.pdf");
        }
        
        int NBins = OverallClone->GetXaxis()->GetNbins();
        double AccCorrTolerance = 1.5;

        for (int WhichBin = 0; WhichBin < NBins; WhichBin++) {
                double AccCorr = 0.;
                double RadCorr = 0.;

                double NewBinContent = 0.;
                double NewBinError = 0.;

                if(type == "G") AccCorr = G_correction->GetBinContent(WhichBin + 1);
                else if(type == "SuSA") AccCorr = susa_correction->GetBinContent(WhichBin + 1);
                else AccCorr = Average->GetBinContent(WhichBin + 1);

                if (AccCorr < 0 || AccCorr > AccCorrTolerance) {
                        double CorrectionSuSav2Bin = susa_correction->GetBinContent(WhichBin + 1);
                        double CorrectionG2018Bin = G_correction->GetBinContent(WhichBin + 1);

                        if (CorrectionSuSav2Bin > 0 && CorrectionSuSav2Bin < AccCorrTolerance) { AccCorr = CorrectionSuSav2Bin; }
                        else if (CorrectionG2018Bin > 0 && CorrectionG2018Bin < AccCorrTolerance) { AccCorr = CorrectionG2018Bin; }
                        else { AccCorr = 0.; }

                }
                
                
                RadCorr = RadCorrection->GetBinContent(WhichBin + 1);
                if(RadCorr <= 0.) RadCorr = 1.;
                if(AccCorr <= 0.) AccCorr = 1.;
                if(type != "data") RadCorr = 1.;

                NewBinContent = hist->GetBinContent(WhichBin + 1) * AccCorr * RadCorr;
                NewBinError = hist->GetBinError(WhichBin + 1) * AccCorr * RadCorr;

                OverallClone->SetBinContent(WhichBin + 1, NewBinContent);
                OverallClone->SetBinError(WhichBin + 1, NewBinError);
        }

        if(make_plots) {
          TString CanvasName = TString::Format("AccCorrCanvas_%s",hist->GetTitle());
          TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
          Average->GetYaxis()->SetTitle("Detector Acceptance Correction");
          Average->GetXaxis()->SetTitle("Momentum (GeV)");
          Average->Draw("e hist");
          Average->SetTitle(TString::Format("%s",hist->GetTitle()));
          PlotCanvas->SaveAs("C12_Acceptance_Ratios.pdf");

          TString RadCanvasName = TString::Format("RadCorrCanvas_%s",hist->GetTitle());
          TCanvas* RadPlotCanvas = new TCanvas(RadCanvasName,RadCanvasName,205,34,1024,768);
          RadCorrection->GetYaxis()->SetTitle("Radiative Correction");
          RadCorrection->GetXaxis()->SetTitle("Momentum (GeV)");
          RadCorrection->SetTitle(TString::Format("%s", hist->GetTitle()));
          RadCorrection->Draw("e hist");
          RadPlotCanvas->SaveAs("C12_Rad_Ratios.pdf");
        }

        TH1D* Spread = (TH1D*)susa_correction->Clone();
        Spread->Add(G_correction, -1);
        Spread->Divide(Average);
        //Spread->Scale(1./TMath::Sqrt(12.));

        int NBinsSpread = Spread->GetXaxis()->GetNbins();

        for (int WhichBin = 0; WhichBin < NBinsSpread; WhichBin++) {

                double BinContent = Spread->GetBinContent(WhichBin+1);
                if (BinContent < 0) { Spread->SetBinContent(WhichBin+1,-BinContent); }

        }

        if(type == "data") {
                for (int WhichBin = 0; WhichBin < NBinsSpread; WhichBin++) {

                        double SpreadBinContent = Spread->GetBinContent(WhichBin+1);
                        double XSecBinError = OverallClone->GetBinError(WhichBin+1);
                        double XSecBinEntry = OverallClone->GetBinContent(WhichBin+1);
                        double AccCorrError = SpreadBinContent * XSecBinEntry;
                        double NewXSecBinError = TMath::Sqrt( TMath::Power(XSecBinError,2.) + TMath::Power(AccCorrError,2.) );
                        if(NewXSecBinError < XSecBinError) {
                                std::cout << "Something wrong, errors should increase!" << "\n";
                                std::cout << "Previous bin error: " << XSecBinError << "\n";
                                std::cout << "Updated bin error: " << NewXSecBinError << "\n";
                        }
                        OverallClone->SetBinError(WhichBin+1,NewXSecBinError);

                }
        }
        

        return OverallClone;
}

double get_ratio_error(double num, double denom) {
        // Binomial errors for transparency ratio
        if (denom == 0. || isnan(num) || isnan(denom)) {
                std::cout << "Is this happening?" << "\n";
                return 0.;
        }
        double p = num/denom;
        double q = 1. - p;
        //std::cout << sqrt(denom * p * q) << "\n";
        return sqrt(denom * p * q);
}

void printit(std::string s, double x) {
        std::cout << s << " = " << x << "\n";
}

double diff_squared(double x, double y) {
        if (isnan(x) || isnan(y) || x == 0.0 || y == 0.0) return 0.;
        //std::cout << (x-y)*(x-y) << "\n";
        return (x - y)*(x - y); 
}

double myratio(double x, double y) {
        if(y == 0. || isnan(x) || isnan(y)) return 0.;
        if (x > y) {
                std::cout << "Something is wrong!" << "\n";
                std::cout << "Ratio = " << x/y << "\n";
        }
        return x/y;
}



#endif