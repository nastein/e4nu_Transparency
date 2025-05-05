// File to plot histograms of the elecon momentum for a simulation.
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
#include "parse_file.C"

class line {
    public:
        double m;
        double x1;
        double x2;
        double y1; 
        double y2;

        double getval(double x) {
            return (m*x + (y1 - m*x1));
        }

        void initline(double xstart, double xend, double ystart, double yend) {
            x1 = xstart;
            x2 = xend;
            y1 = ystart;
            y2 = yend;
            m = (y2 - y1)/(x2 - x1);
        }
};

void theta_e_correct(std::string targ){

    std::string susa_true[4];
    std::string susa_reco[4];


    std::string G_true[4];
    std::string G_reco[4];

    std::string data[4];

    TFile *fsusa_true[4];
    TFile *fsusa_reco[4];

    TFile *fG_true[4];
    TFile *fG_reco[4];
    TFile *fdata[4];

    std::string nuc;
    if(targ == "56Fe") nuc = "Fe56";
    if(targ == "4He") nuc = "He4";
    if(targ == "C12") nuc = "C12";

    for(int r = 0; r < 3; r++) {
        susa_true[r] = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut_QPshifted/Truth/SuSA/Big_Excl_Range%i_Genie_1_%s_2.261000.root",r+1,targ.c_str());
        susa_reco[r] = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut_QPshifted/Truth_Reco/SuSA/Big_Excl_Range%i_Genie_1_%s_2.261000.root",r+1,targ.c_str());


        G_true[r] = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut_QPshifted/Truth/G18/Big_Excl_Range%i_Genie_2_%s_2.261000.root",r+1,targ.c_str());
        G_reco[r] = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut_QPshifted/Truth_Reco/G18/Big_Excl_Range%i_Genie_2_%s_2.261000.root",r+1,targ.c_str());
        
    }

    susa_true[3] = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut_QPshifted/Truth/SuSA/Big_Excl_Range1_Genie_1_%s_4.461000.root",targ.c_str());
    G_true[3] = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut_QPshifted/Truth/G18/Big_Excl_Range1_Genie_2_%s_4.461000.root",targ.c_str());
    susa_reco[3] = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut_QPshifted/Truth_Reco/SuSA/Big_Excl_Range1_Genie_1_%s_4.461000.root",targ.c_str());
    G_reco[3] = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut_QPshifted/Truth_Reco/G18/Big_Excl_Range1_Genie_2_%s_4.461000.root",targ.c_str());

    for(int r = 0; r < 4; r++) {
        fsusa_true[r] = TFile::Open(TString(susa_true[r]));
        fsusa_reco[r] = TFile::Open(TString(susa_reco[r]));
        fG_true[r] = TFile::Open(TString(G_true[r]));
        fG_reco[r] = TFile::Open(TString(G_reco[r]));
    }
    
    data[0] = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Data_ThetaPQ_QPshifted/%s/Excl_Range1_Data__%s_2.261000.root",nuc.c_str(),targ.c_str());
    data[1] = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Data_ThetaPQ_QPshifted/%s/Excl_Range2_Data__%s_2.261000.root",nuc.c_str(),targ.c_str());
    data[2] = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Data_ThetaPQ_QPshifted/%s/Excl_Range3_Data__%s_2.261000.root",nuc.c_str(),targ.c_str());
    data[3] = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Data_ThetaPQ_QPshifted/%s/Excl_Range1_Data__%s_4.461000.root",nuc.c_str(),targ.c_str());

    TFile* fdata_1 = TFile::Open(TString(data[0]));
    TFile* fdata_2 = TFile::Open(TString(data[1]));
    TFile* fdata_3 = TFile::Open(TString(data[2]));
    TFile* fdata_4 = TFile::Open(TString(data[3]));

    // Grab the TList in the ROOT File for info on the run
    TList *Run_Info1 = (TList*)fdata_1->Get("Run_Info");

    std::vector<std::string> parse1 = parse_file(Run_Info1);

    std::string info1 = parse1[0];
    std::string cuts1 = parse1[1];

    // histogram initialization
    TH1D* h1_theta_elec_true[4][6];
    TH1D* h1_theta_elec_reco[4][6];
    TH1D* h1_theta_elec_trueG[4][6];
    TH1D* h1_theta_elec_recoG[4][6];
    TH1D* h1_theta_elec_corr[4][6];
    TH1D* h1_theta_elec_corrG[4][6];
    TH1D* h1_theta_elec_data_corr[4][6];
    TH1D* h1_theta_elec_data[4][6];

    TH1D* average_corr[4][6];
    std::map<int,std::string> sector_map;
    sector_map[0] = "FirstSector";
    sector_map[1] = "SecondSector";
    sector_map[2] = "ThirdSector";
    sector_map[3] = "FourthSector";
    sector_map[4] = "FifthSector";
    sector_map[5] = "SixthSector";

    for(int r = 0; r < 4; r++) {
        for(int sect = 0; sect < 6; sect++) {
             
            h1_theta_elec_true[r][sect] = (TH1D*)(((TH2D*)fsusa_true[r]->Get(TString::Format("h2_Electron_Theta_Momentum_%s",sector_map[sect].c_str())))->ProjectionY());

            h1_theta_elec_reco[r][sect] = (TH1D*)(((TH2D*)fsusa_reco[r]->Get(TString::Format("h2_Electron_Theta_Momentum_%s",sector_map[sect].c_str())))->ProjectionY());
            h1_theta_elec_trueG[r][sect] = (TH1D*)(((TH2D*)fG_true[r]->Get(TString::Format("h2_Electron_Theta_Momentum_%s",sector_map[sect].c_str())))->ProjectionY());
            h1_theta_elec_recoG[r][sect] = (TH1D*)(((TH2D*)fG_reco[r]->Get(TString::Format("h2_Electron_Theta_Momentum_%s",sector_map[sect].c_str())))->ProjectionY());
  
            
            if(r == 0) {
                h1_theta_elec_data[0][sect] = (TH1D*)(((TH2D*)fdata_1->Get(TString::Format("h2_Electron_Theta_Momentum_%s",sector_map[sect].c_str())))->ProjectionY());
                h1_theta_elec_data[1][sect] = (TH1D*)(((TH2D*)fdata_2->Get(TString::Format("h2_Electron_Theta_Momentum_%s",sector_map[sect].c_str())))->ProjectionY());
                h1_theta_elec_data[2][sect] = (TH1D*)(((TH2D*)fdata_3->Get(TString::Format("h2_Electron_Theta_Momentum_%s",sector_map[sect].c_str())))->ProjectionY());
                h1_theta_elec_data[3][sect] = (TH1D*)(((TH2D*)fdata_4->Get(TString::Format("h2_Electron_Theta_Momentum_%s",sector_map[sect].c_str())))->ProjectionY());
            }

            //h1_theta_elec_true[r][sect]->Rebin(2);
            //h1_theta_elec_reco[r][sect]->Rebin(2);
            //h1_theta_elec_trueG[r][sect]->Rebin(2);
            //h1_theta_elec_recoG[r][sect]->Rebin(2);
            //h1_theta_elec_data[r][sect]->Rebin(2);

            h1_theta_elec_corr[r][sect] = (TH1D*)(h1_theta_elec_true[r][sect]->Clone());
            h1_theta_elec_corr[r][sect]->Divide(h1_theta_elec_reco[r][sect]);

            h1_theta_elec_corrG[r][sect] = (TH1D*)(h1_theta_elec_trueG[r][sect]->Clone());
            h1_theta_elec_corrG[r][sect]->Divide(h1_theta_elec_recoG[r][sect]);

            average_corr[r][sect]=(TH1D*)(h1_theta_elec_corr[r][sect]->Clone());
            average_corr[r][sect]->Add(h1_theta_elec_corrG[r][sect]);
            average_corr[r][sect]->Scale(0.5);
            
            /*
            h1_theta_elec_data_corr[r][sect] = (TH1D*)(h1_theta_elec_data[r][sect]->Clone());
            h1_theta_elec_data_corr[r][sect]->Multiply(average_corr[r][sect]);
            */
            
            
            

        }

    }

    for(int r = 0; r < 4; r++) {
        for(int sect = 0; sect < 6; sect++) {
            for(int whichbin = 0; whichbin < h1_theta_elec_corrG[r][sect]->GetNbinsX(); whichbin++) {
                if(h1_theta_elec_corrG[r][sect]->GetBinContent(whichbin + 1) == 0.) {
                    average_corr[r][sect]->SetBinContent(whichbin + 1, h1_theta_elec_corr[r][sect]->GetBinContent(whichbin + 1));
                }
            }
        }
    }

    std::vector<int> starts;
    std::vector<int> ends;
    bool started;
    bool ended;
    int startbin;
    int endbin;

    for(int r = 0; r < 4; r++) {
	std::cout << "Range " << r << "\n";
        for(int sect = 0; sect < 6; sect++){
            std::cout << "Sector " << sect << "\n";
            //started = false;
            //ended = true;
            //starts.clear();
            //ends.clear();

            h1_theta_elec_data_corr[r][sect] = (TH1D*)(h1_theta_elec_data[r][sect]->Clone());

            for(int whichbin = 0; whichbin < average_corr[r][sect]->GetNbinsX(); whichbin++) {
                
                double AccCorr = average_corr[r][sect]->GetBinContent(whichbin+1);
		if(AccCorr != 0) std::cout << "Acceptance correction factor = " << AccCorr << "\n";
                if(AccCorr < 0.) AccCorr = 1.;
		if(h1_theta_elec_data[r][sect]->GetBinContent(whichbin+1) != 0) std::cout << "Old bin content = " << h1_theta_elec_data[r][sect]->GetBinContent(whichbin+1) << "\n"; 
                double newbincontent = AccCorr*h1_theta_elec_data[r][sect]->GetBinContent(whichbin+1);
                double newbinerror = AccCorr*h1_theta_elec_data[r][sect]->GetBinError(whichbin+1);
                
                h1_theta_elec_data_corr[r][sect]->SetBinContent(whichbin+1,newbincontent);
                h1_theta_elec_data_corr[r][sect]->SetBinError(whichbin+1,newbinerror);
                if(h1_theta_elec_data[r][sect]->GetBinContent(whichbin+1) != 0)std::cout << "Corrected bin ccontent = " << newbincontent << "\n";
                /*
                if ( (average_corr[r][sect]->GetBinContent(whichbin+1) > 2.0 )) {
                    std::cout << "Found a bad bin" << "\n";
                    if(started == false && ended == true) {
                        std::cout << "Starting in bin: " << whichbin +1 << "\n";
                        started = true;
                        ended = false;
                        startbin = whichbin+1;
                        starts.push_back(startbin);
                    }
                }

                else {
                    std::cout << "Good bin" << "\n";
                    if( (started == true) && (ended == false) ) {endbin = whichbin; ended = true; ends.push_back(endbin);}
                    h1_theta_elec_data_corr[r][sect]->SetBinContent(whichbin+1,h1_theta_elec_data_corr[r][sect]->GetBinContent(whichbin+1)*average_corr[r][sect]->GetBinContent(whichbin +1));
                    h1_theta_elec_data_corr[r][sect]->SetBinError(whichbin+1,h1_theta_elec_data_corr[r][sect]->GetBinError(whichbin+1)*average_corr[r][sect]->GetBinContent(whichbin+1));
                    started = false;
                }
                
            }
            
            if(starts.size() != 0) {
                for(int i = 0; i < starts.size(); i++) {
                    std::cout << "We found bad bins, starting from bin: " << starts[i] << ", ending in bin " << ends[i] << "\n";
                    std::cout << "Correcting them now" << "\n";
                    line bestfit;
                    bestfit.initline(starts[i]-1, ends[i]+1, h1_theta_elec_data_corr[r][sect]->GetBinContent(starts[i] - 1), h1_theta_elec_data_corr[r][sect]->GetBinContent(ends[i] + 1));
                    for(int whichbin = starts[i]; whichbin < ends[i]+1; whichbin++) {
                        double newval = bestfit.getval(whichbin);
                        double prebincontent = h1_theta_elec_data_corr[r][sect]->GetBinContent(whichbin);
                        double ratio = newval/prebincontent;
                        h1_theta_elec_data_corr[r][sect]->SetBinContent(whichbin,newval);
                        h1_theta_elec_data_corr[r][sect]->SetBinError(whichbin,h1_theta_elec_data_corr[r][sect]->GetBinError(whichbin)*ratio);
                    }
                }*/
            }
        }
    }
    
    Float_t rightmax[4][6];
    Float_t scale[4][6];

    const int color_options[6] = {kBlue, kAzure+10, kGreen-3, kViolet, kBlack, kRed};
    
    TCanvas* c[4][6];
    TLegend *legend[4][6];
    TCanvas *test = new TCanvas(TString::Format("test"), TString::Format("test"), 800, 600);
    test->SaveAs("acceptance_theta.pdf");


    for(int r = 0; r < 4; r++) {
        for(int sect = 0; sect < 6; sect++) {
            //if(r != 0 && sect != 0) {
                c[r][sect] = new TCanvas(TString::Format("c%i%i",r,sect), TString::Format("c%i%i",r,sect), 800, 600);
            //}
            c[r][sect]->cd();
            //c[r][sect]->SetLogy();

            h1_theta_elec_data_corr[r][sect]->SetStats(0);
            h1_theta_elec_data_corr[r][sect]->SetTitle(TString::Format("Range %i Sector %i",r+1,sect+1));
            h1_theta_elec_data_corr[r][sect]->GetXaxis()->SetTitle("Electron Theta (Degrees)");
            h1_theta_elec_data_corr[r][sect]->GetYaxis()->SetTitle("Number of Events");
            h1_theta_elec_data_corr[r][sect]->GetXaxis()->CenterTitle( true );
            h1_theta_elec_data_corr[r][sect]->GetYaxis()->CenterTitle( true );
            h1_theta_elec_data_corr[r][sect]->SetLineColor(kBlue);
            h1_theta_elec_data_corr[r][sect]->SetLineWidth(2);
            h1_theta_elec_data_corr[r][sect]->GetXaxis()->SetRangeUser(20,45);
            h1_theta_elec_data_corr[r][sect]->Draw("HIST E");
            h1_theta_elec_data[r][sect]->SetLineColor(kBlack);
            h1_theta_elec_data[r][sect]->SetLineWidth(2);
            h1_theta_elec_data[r][sect]->Draw("HIST E SAME");

            c[r][sect]->SetLeftMargin( 0.14);
            c[r][sect]->SetBottomMargin( 0.14);
            c[r][sect]->Update();

            //h1_theta_elec_corr[r][sect]->SetLogy(1);

            rightmax[r][sect] = 1.1*h1_theta_elec_corr[r][sect]->GetMaximum();
            scale[r][sect] = gPad->GetUymax()/rightmax[r][sect];
            h1_theta_elec_corr[r][sect]->SetLineColor(kRed);
            h1_theta_elec_corrG[r][sect]->SetLineColor(kRed);
            h1_theta_elec_corr[r][sect]->SetLineStyle(kDashed);
            h1_theta_elec_corrG[r][sect]->SetLineStyle(kDashDotted);
            average_corr[r][sect]->SetLineColor(kRed);

            h1_theta_elec_corrG[r][sect]->SetLineWidth(2);
            average_corr[r][sect]->SetLineWidth(2);
            h1_theta_elec_corr[r][sect]->Scale(scale[r][sect]);
            h1_theta_elec_corrG[r][sect]->Scale(scale[r][sect]);
            average_corr[r][sect]->Scale(scale[r][sect]);
            h1_theta_elec_corr[r][sect]->SetLineWidth(2);
            h1_theta_elec_corrG[r][sect]->Draw("HIST E SAME");
            h1_theta_elec_corr[r][sect]->Draw("HIST E SAME");
            average_corr[r][sect]->Draw("HIST E SAME");

            
            //draw an axis on the right side
            TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
            gPad->GetUxmax(), gPad->GetUymax(),0,rightmax[r][sect],510,"+L");
            axis->SetLineColor(kRed);
            axis->SetLabelColor(kRed);
            axis->Draw();
            


            legend[r][sect] = new TLegend( 0.6, 0.725, 0.8, 0.925);
            legend[r][sect]->AddEntry( h1_theta_elec_data[r][sect], TString::Format("Data"));
            legend[r][sect]->AddEntry( h1_theta_elec_data_corr[r][sect], TString::Format("Corrected Data"));
            legend[r][sect]->AddEntry( h1_theta_elec_corr[r][sect], "G18 Corr.");
            legend[r][sect]->AddEntry( h1_theta_elec_corrG[r][sect], "SuSa Corr.");
            legend[r][sect]->AddEntry( average_corr[r][sect], "Avg Corr.");
            legend[r][sect]->SetBorderSize( 0);
            legend[r][sect]->SetFillStyle( 0);
            legend[r][sect]->Draw();

            c[r][sect]->SaveAs("acceptance_theta.pdf(");

        }
    }


    test->SaveAs("acceptance_theta.pdf)");
    
}

