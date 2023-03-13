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
#include "parse_file.C"

void theta_correct(std::string beamen){

    std::string susa_true[3];
    std::string susa_reco[3];


    std::string G_true[3];
    std::string G_reco[3];

    std::string data[3];

    TFile *fsusa_true[3];
    TFile *fsusa_reco[3];

    TFile *fG_true[3];
    TFile *fG_reco[3];
    TFile *fdata[3];

    for(int r = 0; r < 3; r++) {
        susa_true[r] = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/SuSA/Big_Excl_Range%i_Genie_1_C12_%s.root",r+1,beamen.c_str());
        susa_reco[r] = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/SuSA/Big_Excl_Range%i_Genie_1_C12_%s.root",r+1,beamen.c_str());


        G_true[r] = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth/G18/Big_Excl_Range%i_Genie_2_C12_%s.root",r+1,beamen.c_str());
        G_reco[r] = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/CLAS/GENIE/Acceptance/ThetaPQCut/Truth_Reco/G18/Big_Excl_Range%i_Genie_2_C12_%s.root",r+1,beamen.c_str());
    
        std::cout << susa_true[r] << "\n";
        std::cout << susa_reco[r] << "\n";

        fsusa_true[r] = TFile::Open(TString(susa_true[r]));
        fsusa_reco[r] = TFile::Open(TString(susa_reco[r]));
        fG_true[r] = TFile::Open(TString(G_true[r]));
        fG_reco[r] = TFile::Open(TString(G_reco[r]));
        
    }
    
    data[0] = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/C12/Excl_Range1_Data__C12_%s.root",beamen.c_str());
    //fdata[0] = TFile::Open(TString(data[0]));
    data[1] = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/C12/Excl_Range2_Data__C12_%s.root",beamen.c_str());
    //fdata[1] = TFile::Open(TString(data[1]));
    data[2] = TString::Format("/genie/app/users/nsteinbe/grahams_e4nu/CLAS/DATA/Full_Data_SampleThetaPQ/C12/Excl_Range3_Data__C12_%s.root",beamen.c_str());
    //fdata[2] = TFile::Open(TString(data[2]));
    
 
    //TFile fdata_test = TFile::Open(TString(data[2]));

    TFile* fdata_1 = TFile::Open(TString(data[0]));
    TFile* fdata_2 = TFile::Open(TString(data[1]));
     TFile* fdata_3 = TFile::Open(TString(data[2]));

    // Grab the TList in the ROOT File for info on the run
    TList *Run_Info1 = (TList*)fdata_1->Get("Run_Info");

    std::vector<std::string> parse1 = parse_file(Run_Info1);

    std::string info1 = parse1[0];
    std::string cuts1 = parse1[1];

    int rmax;
    std::string beam_en;
    if(info1.find("1.161")!= std::string::npos) {beam_en = "1_161"; rmax = 2;}
    else if(info1.find("2.261")!= std::string::npos) {beam_en = "2_261"; rmax = 3;}
    else {beam_en = "4_461"; rmax = 1;}

    rmax = 3;
    std::cout << "Analyzed beam en: " << beam_en << "\n";

    // histogram initialization
    TH1D* h1_theta_prot_true_int[3][4][6];
    TH1D* h1_theta_prot_reco_int[3][4][6];
    TH1D* h1_theta_prot_true[3][6];
    TH1D* h1_theta_prot_reco[3][6];
    TH1D* h1_theta_prot_true_intG[3][4][6];
    TH1D* h1_theta_prot_reco_intG[3][4][6];
    TH1D* h1_theta_prot_trueG[3][6];
    TH1D* h1_theta_prot_recoG[3][6];
    TH1D* h1_theta_prot_data[3][6];
    TH1D* h1_theta_prot_corr[3][6];
    TH1D* h1_theta_prot_corrG[3][6];
    TH1D* h1_theta_prot_data_corr[3][6];

    TH1D* average_corr[3][6];

    for(int r = 0; r < rmax; r++) {
        for(int sect = 0; sect < 6; sect++) {
            for(int il = 0; il < 4; il++) {
                h1_theta_prot_true_int[r][il][sect] = (TH1D*)fsusa_true[r]->Get(TString::Format("h1_InteractionEq%i_NoQ4Weight_InSector%i_prot_theta",il+1,sect));
                h1_theta_prot_reco_int[r][il][sect] = (TH1D*)fsusa_reco[r]->Get(TString::Format("h1_InteractionEq%i_NoQ4Weight_InSector%i_prot_theta",il+1,sect));
                h1_theta_prot_true_intG[r][il][sect] = (TH1D*)fG_true[r]->Get(TString::Format("h1_InteractionEq%i_NoQ4Weight_InSector%i_prot_theta",il+1,sect));
                h1_theta_prot_reco_intG[r][il][sect] = (TH1D*)fG_reco[r]->Get(TString::Format("h1_InteractionEq%i_NoQ4Weight_InSector%i_prot_theta",il+1,sect));
                if(il == 0) {
                    h1_theta_prot_true[r][sect] = (TH1D*)(h1_theta_prot_true_int[r][0][sect]->Clone());
                    h1_theta_prot_reco[r][sect] = (TH1D*)(h1_theta_prot_reco_int[r][0][sect]->Clone());
                    h1_theta_prot_trueG[r][sect] = (TH1D*)(h1_theta_prot_true_intG[r][0][sect]->Clone());
                    h1_theta_prot_recoG[r][sect] = (TH1D*)(h1_theta_prot_reco_intG[r][0][sect]->Clone());
                }
                else{
                    h1_theta_prot_true[r][sect]->Add(h1_theta_prot_true_int[r][il][sect]);
                    h1_theta_prot_reco[r][sect]->Add(h1_theta_prot_reco_int[r][il][sect]);
                    h1_theta_prot_trueG[r][sect]->Add(h1_theta_prot_true_intG[r][il][sect]);
                    h1_theta_prot_recoG[r][sect]->Add(h1_theta_prot_reco_intG[r][il][sect]);
                }
            }
            std::cout << "r = " << r << " sector = " << sect << "\n";
            if(r == 0) {


                h1_theta_prot_data[0][sect] = (TH1D*)fdata_1->Get(TString::Format("h1_InteractionEq0_NoQ4Weight_InSector%i_prot_theta",sect));

                h1_theta_prot_data[1][sect] = (TH1D*)fdata_2->Get(TString::Format("h1_InteractionEq0_NoQ4Weight_InSector%i_prot_theta",sect));

                h1_theta_prot_data[2][sect] = (TH1D*)fdata_3->Get(TString::Format("h1_InteractionEq0_NoQ4Weight_InSector%i_prot_theta",sect));
            }


            

            h1_theta_prot_true[r][sect]->Rebin(2);
            h1_theta_prot_reco[r][sect]->Rebin(2);
            if(r != 2) h1_theta_prot_data[r][sect]->Rebin(2);

            
            

            h1_theta_prot_corr[r][sect] = (TH1D*)(h1_theta_prot_true[r][sect]->Clone());
            h1_theta_prot_corr[r][sect]->Divide(h1_theta_prot_reco[r][sect]);


            h1_theta_prot_corrG[r][sect] = (TH1D*)(h1_theta_prot_trueG[r][sect]->Clone());
            h1_theta_prot_corrG[r][sect]->Divide(h1_theta_prot_recoG[r][sect]);

            average_corr[r][sect]=(TH1D*)(h1_theta_prot_corr[r][sect]->Clone());
            average_corr[r][sect]->Add(h1_theta_prot_corrG[r][sect]);
            average_corr[r][sect]->Scale(0.5);

            /*
            h1_theta_prot_data_corr[r][sect] = (TH1D*)(h1_theta_prot_data[r][sect]->Clone());
            h1_theta_prot_data_corr[r][sect]->Multiply(h1_theta_prot_corr[r][sect]);
            */
            
            

        }

    }
    
            int startbin[3][6] = 0;
            int endbin[3][6] = 0;
            int num[3][6] = 0;

    for(int r = 0; r < rmax; r++) {
        for(int sect = 0; sect < 6; sect++){

            h1_theta_prot_data_corr[r][sect] = (TH1D*)(h1_theta_prot_data[r][sect]->Clone());

            for(int whichbin = 0; whichbin < average_corr[r][sect]->GetNbinsX(); whichbin++) {
                if ( (average_corr[r][sect]->GetBinContent(whichbin+1) > 2) && (average_corr[r][sect]->GetBinError(whichbin+1) > 1) ) {
                    if(startbin != 0) {
                        startbin[r][sect] = whichbin+1;
                        num++;
                    }
                    
                }
                if(startbin[r][sect] != 0) endbin[r][sect] = whichbin+1;
                else {
                    h1_theta_prot_data_corr[r][sect]->SetBinContent(whichbin+1,h1_theta_prot_data_corr[r][sect]->GetBinContent(whichbin+1)*average_corr[r][sect]->GetBinContent(whichbin +1));
                    h1_theta_prot_data_corr[r][sect]->SetBinError(whichbin+1,h1_theta_prot_data_corr[r][sect]->GetBinError(whichbin+1)*average_corr[r][sect]->GetBinContent(whichbin+1));
                }
            }
        }
    }

    for(int r = 0; r < rmax; r++) {
        for(int sect = 0; sect < 6; sect++){
            for(int whichbin = startbin[sect]; whichbin < endbin[r][sect]+1; whichbin++) {
                double average = (h1_theta_prot_data_corr[r][sect]->GetBinContent(startbin[r][sect]-1) + h1_theta_prot_data_corr[r][sect]->GetBinContent(startbin[r][sect]+1))/2.;
                h1_theta_prot_data_corr[r][sect]->SetBinContent(whichbin,average);
            }
        }
    }
    

    
    Float_t rightmax[3][6];
    Float_t scale[3][6];

    const int color_options[6] = {kBlue, kAzure+10, kGreen-3, kViolet, kBlack, kRed};
    
    TCanvas* c[3][6];
    TLegend *legend[3][6];
    TCanvas *test = new TCanvas(TString::Format("test"), TString::Format("test"), 800, 600);
    test->SaveAs("acceptance_theta.pdf");


    for(int r = 0; r < rmax; r++) {
        for(int sect = 0; sect < 6; sect++) {
            //if(r != 0 && sect != 0) {
                c[r][sect] = new TCanvas(TString::Format("c%i%i",r,sect), TString::Format("c%i%i",r,sect), 800, 600);
            //}
            c[r][sect]->cd();
            c[r][sect]->SetLogy();

            h1_theta_prot_data_corr[r][sect]->SetStats(0);
            h1_theta_prot_data_corr[r][sect]->SetTitle(TString::Format("Range %i Sector %i",r+1,sect+1));
            h1_theta_prot_data_corr[r][sect]->GetXaxis()->SetTitle("Proton Theta (Degrees)");
            h1_theta_prot_data_corr[r][sect]->GetYaxis()->SetTitle("Number of Events");
            h1_theta_prot_data_corr[r][sect]->GetXaxis()->CenterTitle( true );
            h1_theta_prot_data_corr[r][sect]->GetYaxis()->CenterTitle( true );
            h1_theta_prot_data_corr[r][sect]->SetLineColor(kBlue);
            h1_theta_prot_data_corr[r][sect]->SetLineWidth(2);
            h1_theta_prot_data_corr[r][sect]->GetXaxis()->SetRangeUser(20,90);
            h1_theta_prot_data_corr[r][sect]->Draw("HIST E");
            h1_theta_prot_data[r][sect]->SetLineColor(kBlack);
            h1_theta_prot_data[r][sect]->SetLineWidth(2);
            h1_theta_prot_data[r][sect]->Draw("HIST E SAME");

            c[r][sect]->SetLeftMargin( 0.14);
            c[r][sect]->SetBottomMargin( 0.14);
            c[r][sect]->Update();

            //h1_theta_prot_corr[r][sect]->SetLogy(1);

            rightmax[r][sect] = 1.1*h1_theta_prot_corr[r][sect]->GetMaximum();
            scale[r][sect] = gPad->GetUymax()/rightmax[r][sect];
            h1_theta_prot_corr[r][sect]->SetLineColor(kRed);
            //h1_theta_prot_corr[r][sect]->Scale(scale[r][sect]);
            h1_theta_prot_corr[r][sect]->SetLineWidth(2);
            h1_theta_prot_corr[r][sect]->Draw("HIST E SAME");

            /*
            //draw an axis on the right side
            TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
            gPad->GetUxmax(), gPad->GetUymax(),0,rightmax[r][sect],510,"+L");
            axis->SetLineColor(kRed);
            axis->SetLabelColor(kRed);
            axis->Draw();
            */


            legend[r][sect] = new TLegend( 0.6, 0.725, 0.8, 0.925);
            legend[r][sect]->AddEntry( h1_theta_prot_data[r][sect], TString::Format("Data"));
            legend[r][sect]->AddEntry( h1_theta_prot_data_corr[r][sect], TString::Format("Corrected Data"));
            legend[r][sect]->AddEntry( h1_theta_prot_corr[r][sect], "Acceptance Correction");
            legend[r][sect]->SetBorderSize( 0);
            legend[r][sect]->SetFillStyle( 0);
            legend[r][sect]->Draw();

            c[r][sect]->SaveAs("acceptance_theta.pdf(");

        }
    }


    c[0][0]->SaveAs("acceptance_theta.pdf)");
    
}
