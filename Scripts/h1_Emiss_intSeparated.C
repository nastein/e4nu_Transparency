// File to plot histograms of the proton momentum for a simulation. The histograms generated
// with this macro are separated into the different interaction components: quasi-elastic (QE),
// mesonic current (MEC), resonance (RES), and deep inelastic scattering (DIS). This functionality
// is indicated by "intSeparated" being in the macro's file name.
//
// Author: Jacob Smith (smithja)
// Creation Date: 09/23/2021
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
#include "parse_file.C"
//#include "myFunctions.cpp"

void h1_Emiss_intSeparated( std::string file_name){

    // declare variables that will be used in the plotting/formatting of histograms and file names
    std::string info ("");
    std::string cuts ("");

    // import the ROOT data file from the output of doing ./genie_analysis in the e4nu directory
    TFile *input1 = TFile::Open( TString( file_name));

    // Grab the TList in the ROOT File for info on the run
    TList *Run_Info = (TList*)input1->Get("Run_Info");

    std::vector<std::string> parse = parse_file(Run_Info);

    info = parse[0];
    cuts = parse[1];

    // histogram initialization
    TH1F* h1_Emiss[24];

    h1_Emiss[0] = (TH1F*)input1->Get(TString::Format("h1_Int_1_Sect_5_Em"));
    h1_Emiss[1] = (TH1F*)input1->Get(TString::Format("h1_Int_2_Sect_5_Em"));
    h1_Emiss[2] = (TH1F*)input1->Get(TString::Format("h1_Int_3_Sect_5_Em"));
    h1_Emiss[3] = (TH1F*)input1->Get(TString::Format("h1_Int_4_Sect_5_Em"));

    h1_Emiss[4] = (TH1F*)input1->Get(TString::Format("h1_Int_1_Sect_4_Em"));
    h1_Emiss[5] = (TH1F*)input1->Get(TString::Format("h1_Int_2_Sect_4_Em"));
    h1_Emiss[6] = (TH1F*)input1->Get(TString::Format("h1_Int_3_Sect_4_Em"));
    h1_Emiss[7] = (TH1F*)input1->Get(TString::Format("h1_Int_4_Sect_4_Em"));

    h1_Emiss[8] = (TH1F*)input1->Get(TString::Format("h1_Int_1_Sect_3_Em"));
    h1_Emiss[9] = (TH1F*)input1->Get(TString::Format("h1_Int_2_Sect_3_Em"));
    h1_Emiss[10] = (TH1F*)input1->Get(TString::Format("h1_Int_3_Sect_3_Em"));
    h1_Emiss[11] = (TH1F*)input1->Get(TString::Format("h1_Int_4_Sect_3_Em"));

    h1_Emiss[12] = (TH1F*)input1->Get(TString::Format("h1_Int_1_Sect_2_Em"));
    h1_Emiss[13] = (TH1F*)input1->Get(TString::Format("h1_Int_2_Sect_2_Em"));
    h1_Emiss[14] = (TH1F*)input1->Get(TString::Format("h1_Int_3_Sect_2_Em"));
    h1_Emiss[15] = (TH1F*)input1->Get(TString::Format("h1_Int_4_Sect_2_Em"));

    h1_Emiss[16] = (TH1F*)input1->Get(TString::Format("h1_Int_1_Sect_1_Em"));
    h1_Emiss[17] = (TH1F*)input1->Get(TString::Format("h1_Int_2_Sect_1_Em"));
    h1_Emiss[18] = (TH1F*)input1->Get(TString::Format("h1_Int_3_Sect_1_Em"));
    h1_Emiss[19] = (TH1F*)input1->Get(TString::Format("h1_Int_4_Sect_1_Em"));

    h1_Emiss[20] = (TH1F*)input1->Get(TString::Format("h1_Int_1_Sect_0_Em"));
    h1_Emiss[21] = (TH1F*)input1->Get(TString::Format("h1_Int_2_Sect_0_Em"));
    h1_Emiss[22] = (TH1F*)input1->Get(TString::Format("h1_Int_3_Sect_0_Em"));
    h1_Emiss[23] = (TH1F*)input1->Get(TString::Format("h1_Int_4_Sect_0_Em"));

    // compile all the histograms into the four interaction types (QE, MEC, RES, and DIS for quasi-elastic,
    // mesonic current, resonance, and deep inelastic scattering, respectively.
    for( int i = 1; i < 6; i++) {
        h1_Emiss[20]->Add(h1_Emiss[20-(4*i)]);
	h1_Emiss[21]->Add(h1_Emiss[21-(4*i)]); 
	h1_Emiss[22]->Add(h1_Emiss[22-(4*i)]); 
	h1_Emiss[23]->Add(h1_Emiss[23-(4*i)]); 
    }

    // create a canvas on which to draw the histograms
    TCanvas* c;
    c = new TCanvas(TString::Format("c"), TString::Format("c"), 800, 600);

    // initialize things such as color options that will be used in plotting the histograms below
    const int color_options[5] = {kBlue, kAzure+10, kGreen-3, kViolet, kBlue+2};
    const char * draw_options[5] = {"HIST","HIST SAME","HIST SAME", "HIST SAME","HIST SAME"};
    const char * draw_options2[5] = {"E SAME", "E SAME","E SAME", "E SAME","E SAME"};

    double hist_max = 0.;
    // format the histograms and then make them
    for( int i = 20; i < 24; i++){
	// formatting statements
        h1_Emiss[i]->Sumw2();
        //h1_Emiss[i]->Rebin( 25);
//        h1_prot_momentum[i]->Scale( 1./h1_prot_momentum[i]->Integral(),"width"); // normalize the histogram to 1
        h1_Emiss[i]->SetStats( 0); // get rid of the stats box that usually appears at the top right of plots
        h1_Emiss[i]->SetLineColor( color_options[i-20]);
        h1_Emiss[i]->GetXaxis()->SetTitle("Missing Energy [GeV]");
        h1_Emiss[i]->GetYaxis()->SetTitle("Events");
        //h1_Emiss[i]->GetXaxis()->SetRangeUser( 0, 200);
        h1_Emiss[i]->GetXaxis()->CenterTitle( true);
        h1_Emiss[i]->GetYaxis()->CenterTitle( true);
//        h1_Emiss[i]->GetXaxis()->SetTitleSize( 0.06);
//        h1_Emiss[i]->GetYaxis()->SetTitleSize( 0.06);

        h1_Emiss[i]->SetTitle(TString(info)+TString(cuts));

        // take the maximum of the four interactions to use later in plotting
        if (h1_Emiss[i]->GetMaximum() > hist_max) { hist_max = h1_Emiss[i]->GetMaximum(); }
    }

    // draw the histograms
    for( int i = 20; i < 24; i++){
	h1_Emiss[i]->GetYaxis()->SetRangeUser( 0, hist_max*1.1); // smithja: hist_max mult. by 1.1 to give the graph some head room
        h1_Emiss[i]->Draw( draw_options[i-20]);
        h1_Emiss[i]->Draw( draw_options2[i-20]);
    }

    // crop the margins of the canvas
    c->SetLeftMargin( 0.14);
    c->SetBottomMargin( 0.14);
    //if ( cut_case.compare("noCuts") != 0) { c->SetTopMargin( 0.16); }
    c->Update();

    // create and draw a legend for our histograms
    TLegend *legend = new TLegend( 0.7, 0.655, 1.2, 0.8);
    legend->AddEntry( h1_Emiss[20],"QE","l");
    legend->AddEntry( h1_Emiss[21],"MEC","l");
    legend->AddEntry( h1_Emiss[22],"RES","l");
    legend->AddEntry( h1_Emiss[23],"DIS","l");
    legend->SetBorderSize( 0);
    legend->SetFillStyle( 0);
    legend->Draw();

    TH1F* h1_Pmiss[24];

    h1_Pmiss[0] = (TH1F*)input1->Get(TString::Format("h1_Int_1_Sect_5_Pm"));
    h1_Pmiss[1] = (TH1F*)input1->Get(TString::Format("h1_Int_2_Sect_5_Pm"));
    h1_Pmiss[2] = (TH1F*)input1->Get(TString::Format("h1_Int_3_Sect_5_Pm"));
    h1_Pmiss[3] = (TH1F*)input1->Get(TString::Format("h1_Int_4_Sect_5_Pm"));

    h1_Pmiss[4] = (TH1F*)input1->Get(TString::Format("h1_Int_1_Sect_4_Pm"));
    h1_Pmiss[5] = (TH1F*)input1->Get(TString::Format("h1_Int_2_Sect_4_Pm"));
    h1_Pmiss[6] = (TH1F*)input1->Get(TString::Format("h1_Int_3_Sect_4_Pm"));
    h1_Pmiss[7] = (TH1F*)input1->Get(TString::Format("h1_Int_4_Sect_4_Pm"));

    h1_Pmiss[8] = (TH1F*)input1->Get(TString::Format("h1_Int_1_Sect_3_Pm"));
    h1_Pmiss[9] = (TH1F*)input1->Get(TString::Format("h1_Int_2_Sect_3_Pm"));
    h1_Pmiss[10] = (TH1F*)input1->Get(TString::Format("h1_Int_3_Sect_3_Pm"));
    h1_Pmiss[11] = (TH1F*)input1->Get(TString::Format("h1_Int_4_Sect_3_Pm"));

    h1_Pmiss[12] = (TH1F*)input1->Get(TString::Format("h1_Int_1_Sect_2_Pm"));
    h1_Pmiss[13] = (TH1F*)input1->Get(TString::Format("h1_Int_2_Sect_2_Pm"));
    h1_Pmiss[14] = (TH1F*)input1->Get(TString::Format("h1_Int_3_Sect_2_Pm"));
    h1_Pmiss[15] = (TH1F*)input1->Get(TString::Format("h1_Int_4_Sect_2_Pm"));

    h1_Pmiss[16] = (TH1F*)input1->Get(TString::Format("h1_Int_1_Sect_1_Pm"));
    h1_Pmiss[17] = (TH1F*)input1->Get(TString::Format("h1_Int_2_Sect_1_Pm"));
    h1_Pmiss[18] = (TH1F*)input1->Get(TString::Format("h1_Int_3_Sect_1_Pm"));
    h1_Pmiss[19] = (TH1F*)input1->Get(TString::Format("h1_Int_4_Sect_1_Pm"));

    h1_Pmiss[20] = (TH1F*)input1->Get(TString::Format("h1_Int_1_Sect_0_Pm"));
    h1_Pmiss[21] = (TH1F*)input1->Get(TString::Format("h1_Int_2_Sect_0_Pm"));
    h1_Pmiss[22] = (TH1F*)input1->Get(TString::Format("h1_Int_3_Sect_0_Pm"));
    h1_Pmiss[23] = (TH1F*)input1->Get(TString::Format("h1_Int_4_Sect_0_Pm"));

    // compile all the histograms into the four interaction types (QE, MEC, RES, and DIS for quasi-elastic,
    // mesonic current, resonance, and deep inelastic scattering, respectively.
    for( int i = 1; i < 6; i++) {
        h1_Pmiss[20]->Add(h1_Pmiss[20-(4*i)]);
    h1_Pmiss[21]->Add(h1_Pmiss[21-(4*i)]); 
    h1_Pmiss[22]->Add(h1_Pmiss[22-(4*i)]); 
    h1_Pmiss[23]->Add(h1_Pmiss[23-(4*i)]); 
    }

    // create a canvas on which to draw the histograms
    TCanvas* c2;
    c2 = new TCanvas(TString::Format("c2"), TString::Format("c2"), 800, 600);


    //double hist_max = 0.;
    // format the histograms and then make them
    for( int i = 20; i < 24; i++){
    // formatting statements
        h1_Pmiss[i]->Sumw2();
        //h1_Pmiss[i]->Rebin( 25);
//        h1_prot_momentum[i]->Scale( 1./h1_prot_momentum[i]->Integral(),"width"); // normalize the histogram to 1
        h1_Pmiss[i]->SetStats( 0); // get rid of the stats box that usually appears at the top right of plots
        h1_Pmiss[i]->SetLineColor( color_options[i-20]);
        h1_Pmiss[i]->GetXaxis()->SetTitle("Missing Momentum [GeV]");
        h1_Pmiss[i]->GetYaxis()->SetTitle("Events");
        //h1_Pmiss[i]->GetXaxis()->SetRangeUser( 0, 200);
        h1_Pmiss[i]->GetXaxis()->CenterTitle( true);
        h1_Pmiss[i]->GetYaxis()->CenterTitle( true);
//        h1_Pmiss[i]->GetXaxis()->SetTitleSize( 0.06);
//        h1_Pmiss[i]->GetYaxis()->SetTitleSize( 0.06);

        h1_Pmiss[i]->SetTitle(TString(info)+TString(cuts));

        // take the maximum of the four interactions to use later in plotting
        if (h1_Pmiss[i]->GetMaximum() > hist_max) { hist_max = h1_Pmiss[i]->GetMaximum(); }
    }

    // draw the histograms
    for( int i = 20; i < 24; i++){
    h1_Pmiss[i]->GetYaxis()->SetRangeUser( 0, hist_max*1.1); // smithja: hist_max mult. by 1.1 to give the graph some head room
        h1_Pmiss[i]->Draw( draw_options[i-20]);
        h1_Pmiss[i]->Draw( draw_options2[i-20]);
    }

    // crop the margins of the canvas
    c2->SetLeftMargin( 0.14);
    c2->SetBottomMargin( 0.14);
    //if ( cut_case.compare("noCuts") != 0) { c->SetTopMargin( 0.16); }
    c2->Update();

    // create and draw a legend for our histograms
    TLegend *legend2 = new TLegend( 0.7, 0.655, 1.2, 0.8);
    legend2->AddEntry( h1_Pmiss[20],"QE","l");
    legend2->AddEntry( h1_Pmiss[21],"MEC","l");
    legend2->AddEntry( h1_Pmiss[22],"RES","l");
    legend2->AddEntry( h1_Pmiss[23],"DIS","l");
    legend2->SetBorderSize( 0);
    legend2->SetFillStyle( 0);
    legend2->Draw();

    TH2F* h1_EmissPmiss[24];

    h1_EmissPmiss[0] = (TH2F*)input1->Get(TString::Format("h2_Int_1_Sect_5_EmPm"));
    h1_EmissPmiss[1] = (TH2F*)input1->Get(TString::Format("h2_Int_2_Sect_5_EmPm"));
    h1_EmissPmiss[2] = (TH2F*)input1->Get(TString::Format("h2_Int_3_Sect_5_EmPm"));
    h1_EmissPmiss[3] = (TH2F*)input1->Get(TString::Format("h2_Int_4_Sect_5_EmPm"));

    h1_EmissPmiss[4] = (TH2F*)input1->Get(TString::Format("h2_Int_1_Sect_4_EmPm"));
    h1_EmissPmiss[5] = (TH2F*)input1->Get(TString::Format("h2_Int_2_Sect_4_EmPm"));
    h1_EmissPmiss[6] = (TH2F*)input1->Get(TString::Format("h2_Int_3_Sect_4_EmPm"));
    h1_EmissPmiss[7] = (TH2F*)input1->Get(TString::Format("h2_Int_4_Sect_4_EmPm"));

    h1_EmissPmiss[8] = (TH2F*)input1->Get(TString::Format("h2_Int_1_Sect_3_EmPm"));
    h1_EmissPmiss[9] = (TH2F*)input1->Get(TString::Format("h2_Int_2_Sect_3_EmPm"));
    h1_EmissPmiss[10] = (TH2F*)input1->Get(TString::Format("h2_Int_3_Sect_3_EmPm"));
    h1_EmissPmiss[11] = (TH2F*)input1->Get(TString::Format("h2_Int_4_Sect_3_EmPm"));

    h1_EmissPmiss[12] = (TH2F*)input1->Get(TString::Format("h2_Int_1_Sect_2_EmPm"));
    h1_EmissPmiss[13] = (TH2F*)input1->Get(TString::Format("h2_Int_2_Sect_2_EmPm"));
    h1_EmissPmiss[14] = (TH2F*)input1->Get(TString::Format("h2_Int_3_Sect_2_EmPm"));
    h1_EmissPmiss[15] = (TH2F*)input1->Get(TString::Format("h2_Int_4_Sect_2_EmPm"));

    h1_EmissPmiss[16] = (TH2F*)input1->Get(TString::Format("h2_Int_1_Sect_1_EmPm"));
    h1_EmissPmiss[17] = (TH2F*)input1->Get(TString::Format("h2_Int_2_Sect_1_EmPm"));
    h1_EmissPmiss[18] = (TH2F*)input1->Get(TString::Format("h2_Int_3_Sect_1_EmPm"));
    h1_EmissPmiss[19] = (TH2F*)input1->Get(TString::Format("h2_Int_4_Sect_1_EmPm"));

    h1_EmissPmiss[20] = (TH2F*)input1->Get(TString::Format("h2_Int_1_Sect_0_EmPm"));
    h1_EmissPmiss[21] = (TH2F*)input1->Get(TString::Format("h2_Int_2_Sect_0_EmPm"));
    h1_EmissPmiss[22] = (TH2F*)input1->Get(TString::Format("h2_Int_3_Sect_0_EmPm"));
    h1_EmissPmiss[23] = (TH2F*)input1->Get(TString::Format("h2_Int_4_Sect_0_EmPm"));

    // compile all the histograms into the four interaction types (QE, MEC, RES, and DIS for quasi-elastic,
    // mesonic current, resonance, and deep inelastic scattering, respectively.
    for( int i = 1; i < 6; i++) {
        h1_EmissPmiss[20]->Add(h1_EmissPmiss[20-(4*i)]);
        h1_EmissPmiss[21]->Add(h1_EmissPmiss[21-(4*i)]); 
        h1_EmissPmiss[22]->Add(h1_EmissPmiss[22-(4*i)]); 
        h1_EmissPmiss[23]->Add(h1_EmissPmiss[23-(4*i)]); 
    }

    // create a canvas on which to draw the histograms
    TCanvas* c3;
    c3 = new TCanvas(TString::Format("c3"), TString::Format("c3"), 800, 600);

    c3->Divide(2,2,0,0);


    //double hist_max = 0.;
    // format the histograms and then make them
    for( int i = 20; i < 24; i++){
    // formatting statements
        h1_EmissPmiss[i]->Sumw2();
        //h1_EmissPmiss[i]->Rebin( 25);
//        h1_prot_momentum[i]->Scale( 1./h1_prot_momentum[i]->Integral(),"width"); // normalize the histogram to 1
        h1_EmissPmiss[i]->SetStats( 0); // get rid of the stats box that usually appears at the top right of plots
        h1_EmissPmiss[i]->SetMarkerColor( color_options[i-20]);
        h1_EmissPmiss[i]->GetXaxis()->SetTitle("Missing Energy [GeV]");
        h1_EmissPmiss[i]->GetYaxis()->SetTitle("Missing Momentum [GeV]");
        //h1_EmissPmiss[i]->GetXaxis()->SetRangeUser( 0, 200);
        h1_EmissPmiss[i]->GetXaxis()->CenterTitle( true);
        h1_EmissPmiss[i]->GetYaxis()->CenterTitle( true);
//        h1_EmissPmiss[i]->GetXaxis()->SetTitleSize( 0.06);
//        h1_EmissPmiss[i]->GetYaxis()->SetTitleSize( 0.06);

        h1_EmissPmiss[i]->SetTitle(TString(info)+TString(cuts));

        // take the maximum of the four interactions to use later in plotting
        //if (h1_EmissPmiss[i]->GetMaximum() > hist_max) { hist_max = h1_EmissPmiss[i]->GetMaximum(); }
    }

    // draw the histograms
    //for( int i = 20; i < 24; i++){
    //h1_EmissPmiss[i]->GetYaxis()->SetRangeUser( 0, hist_max*1.1); // smithja: hist_max mult. by 1.1 to give the graph some head room
        //h1_EmissPmiss[i]->Draw( draw_options[i-20]);
        //h1_EmissPmiss[i]->Draw( draw_options2[i-20]);
    //}
    c3->cd(1);
    h1_EmissPmiss[20]->Draw("COLZ");
    c3->cd(2);
    h1_EmissPmiss[21]->Draw("COLZ");
    c3->cd(3);
    h1_EmissPmiss[22]->Draw("COLZ");
    c3->cd(4);
    h1_EmissPmiss[23]->Draw("COLZ");
    // crop the margins of the canvas
    c3->SetLeftMargin( 0.14);
    c3->SetBottomMargin( 0.14);
    //if ( cut_case.compare("noCuts") != 0) { c->SetTopMargin( 0.16); }
    c3->Update();

    // create and draw a legend for our histograms
    /*TLegend *legend3 = new TLegend( 0.7, 0.655, 1.2, 0.8);
    legend3->AddEntry( h1_EmissPmiss[20],"QE","l");
    legend3->AddEntry( h1_EmissPmiss[21],"MEC","l");
    legend3->AddEntry( h1_EmissPmiss[22],"RES","l");
    legend3->AddEntry( h1_EmissPmiss[23],"DIS","l");
    legend3->SetBorderSize( 0);
    legend3->SetFillStyle( 0);
    legend3->Draw();*/

    //std::string save_file_path;
    //save_file_path = "../output/h1_prot_mom_intSeparated/"+TString(info)+TString(cuts)+"MottXSecEq1.pdf"; 
    //c->SaveAs( TString::Format("%s", save_file_path.c_str()));

    // smithja: this section of code integrates the distributions and prints
    //          it to the screen
    int num_QE_events = h1_Pmiss[20]->Integral();
    int num_MEC_events = h1_Pmiss[21]->Integral();
    int num_RES_events = h1_Pmiss[22]->Integral();
    int num_DIS_events = h1_Pmiss[23]->Integral();
    int num_events = num_QE_events + num_MEC_events + num_RES_events + num_DIS_events;

    cout << "// --- PROGRAM OUTPUT ------------------------------------------------------" << endl;
    cout << "There are " << num_QE_events << " many QE events in this histogram." << endl;
    cout << "There are " << num_MEC_events << " many MEC events in this histogram." << endl;
    cout << "There are " << num_RES_events << " many RES events in this histogram." << endl;
    cout << "There are " << num_DIS_events << " many DIS events in this histogram." << endl;
    cout << "There are " << num_events << " many total events in the h1_prot_mom_insSeparated histogram." << endl;
    cout << "// -------------------------------------------------------------------------" << endl << endl; // separate program output
}
