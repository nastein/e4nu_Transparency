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

void h1_Ptmiss_FSI( std::string file_name){

    // declare variables that will be used in the plotting/formatting of histograms and file names
    std::string info ("");
    std::string cuts ("");



    // import the ROOT data file from the output of doing ./genie_analysis in the e4nu directory
    TFile *input1 = TFile::Open( "../Cut_BreakDown/PT_FSI/Excl_Range1_Pt_FSItest_Genie_1_C12_2.261000.root");
    TFile *input2 = TFile::Open( "../Cut_BreakDown/PT_FSI/Excl_Range2_Pt_FSItest_Genie_1_C12_2.261000.root");
    TFile *input3 = TFile::Open("../Cut_BreakDown/PT_FSI/Excl_Range3_Pt_FSItest_Genie_1_C12_2.261000.root");



    // Grab the TList in the ROOT File for info on the run
    TList *Run_Info = (TList*)input1->Get("Run_Info");

    std::vector<std::string> parse = parse_file(Run_Info);

    info = parse[0];
    cuts = parse[1];

    // histogram initialization
    TH1F* noFSI[6];
    TH1F* FSI[6];

    TH1F* hnoFSI[6];
    TH1F* hFSI[6];

    TH1F* fnoFSI[6];
    TH1F* fFSI[6];

    
    noFSI[0] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_0_noFSI_Ptmiss"));
    noFSI[1] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_1_noFSI_Ptmiss"));
    noFSI[2] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_2_noFSI_Ptmiss"));
    noFSI[3] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_3_noFSI_Ptmiss"));
    noFSI[4] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_4_noFSI_Ptmiss"));
    noFSI[5] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_5_noFSI_Ptmiss"));

    FSI[0] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_0_FSI_Ptmiss"));
    FSI[1] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_1_FSI_Ptmiss"));
    FSI[2] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_2_FSI_Ptmiss"));
    FSI[3] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_3_FSI_Ptmiss"));
    FSI[4] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_4_FSI_Ptmiss"));
    FSI[5] = (TH1F*)input1->Get(TString::Format("h1_Int1_Sect_5_FSI_Ptmiss"));


    hnoFSI[0] = (TH1F*)input2->Get(TString::Format("h1_Int1_Sect_0_noFSI_Ptmiss"));
    hnoFSI[1] = (TH1F*)input2->Get(TString::Format("h1_Int1_Sect_1_noFSI_Ptmiss"));
    hnoFSI[2] = (TH1F*)input2->Get(TString::Format("h1_Int1_Sect_2_noFSI_Ptmiss"));
    hnoFSI[3] = (TH1F*)input2->Get(TString::Format("h1_Int1_Sect_3_noFSI_Ptmiss"));
    hnoFSI[4] = (TH1F*)input2->Get(TString::Format("h1_Int1_Sect_4_noFSI_Ptmiss"));
    hnoFSI[5] = (TH1F*)input2->Get(TString::Format("h1_Int1_Sect_5_noFSI_Ptmiss"));

    hFSI[0] = (TH1F*)input2->Get(TString::Format("h1_Int1_Sect_0_FSI_Ptmiss"));
    hFSI[1] = (TH1F*)input2->Get(TString::Format("h1_Int1_Sect_1_FSI_Ptmiss"));
    hFSI[2] = (TH1F*)input2->Get(TString::Format("h1_Int1_Sect_2_FSI_Ptmiss"));
    hFSI[3] = (TH1F*)input2->Get(TString::Format("h1_Int1_Sect_3_FSI_Ptmiss"));
    hFSI[4] = (TH1F*)input2->Get(TString::Format("h1_Int1_Sect_4_FSI_Ptmiss"));
    hFSI[5] = (TH1F*)input2->Get(TString::Format("h1_Int1_Sect_5_FSI_Ptmiss"));


    fnoFSI[0] = (TH1F*)input3->Get(TString::Format("h1_Int1_Sect_0_noFSI_Ptmiss"));
    fnoFSI[1] = (TH1F*)input3->Get(TString::Format("h1_Int1_Sect_1_noFSI_Ptmiss"));
    fnoFSI[2] = (TH1F*)input3->Get(TString::Format("h1_Int1_Sect_2_noFSI_Ptmiss"));
    fnoFSI[3] = (TH1F*)input3->Get(TString::Format("h1_Int1_Sect_3_noFSI_Ptmiss"));
    fnoFSI[4] = (TH1F*)input3->Get(TString::Format("h1_Int1_Sect_4_noFSI_Ptmiss"));
    fnoFSI[5] = (TH1F*)input3->Get(TString::Format("h1_Int1_Sect_5_noFSI_Ptmiss"));

    fFSI[0] = (TH1F*)input3->Get(TString::Format("h1_Int1_Sect_0_FSI_Ptmiss"));
    fFSI[1] = (TH1F*)input3->Get(TString::Format("h1_Int1_Sect_1_FSI_Ptmiss"));
    fFSI[2] = (TH1F*)input3->Get(TString::Format("h1_Int1_Sect_2_FSI_Ptmiss"));
    fFSI[3] = (TH1F*)input3->Get(TString::Format("h1_Int1_Sect_3_FSI_Ptmiss"));
    fFSI[4] = (TH1F*)input3->Get(TString::Format("h1_Int1_Sect_4_FSI_Ptmiss"));
    fFSI[5] = (TH1F*)input3->Get(TString::Format("h1_Int1_Sect_5_FSI_Ptmiss"));



    // compile all the histograms into the four interaction types (QE, MEC, RES, and DIS for quasi-elastic,
    // mesonic current, resonance, and deep inelastic scattering, respectively.
    for( int i = 1; i < 6; i++) {
        noFSI[0]->Add(noFSI[i]);
        FSI[0]->Add(FSI[i]);

        hnoFSI[0]->Add(hnoFSI[i]);
        hFSI[0]->Add(hFSI[i]);

        fnoFSI[0]->Add(fnoFSI[i]);
        fFSI[0]->Add(fFSI[i]);

    }
    noFSI[0]->Rebin(2);
    FSI[0]->Rebin(2);
    hnoFSI[0]->Rebin(2);
    hFSI[0]->Rebin(2);
    fnoFSI[0]->Rebin(2);
    fFSI[0]->Rebin(2);

    double range1_int = noFSI[0]->Integral(1,noFSI[0]->GetNbinsX()) + FSI[0]->Integral(1,FSI[0]->GetNbinsX());
    double range2_int = hnoFSI[0]->Integral(1,hnoFSI[0]->GetNbinsX()) + hFSI[0]->Integral(1,hFSI[0]->GetNbinsX());
    double range3_int = fnoFSI[0]->Integral(1,fnoFSI[0]->GetNbinsX()) + fFSI[0]->Integral(1,fFSI[0]->GetNbinsX());

    noFSI[0]->Scale(1./range1_int);
    FSI[0]->Scale(1./range1_int);
    hnoFSI[0]->Scale(1./range2_int);
    hFSI[0]->Scale(1./range2_int);
    fFSI[0]->Scale(1./range3_int);
    fnoFSI[0]->Scale(1./range3_int);

    // create a canvas on which to draw the histograms
    TCanvas* c;
    c = new TCanvas(TString::Format("c"), TString::Format("c"), 800, 600);

    // initialize things such as color options that will be used in plotting the histograms below
    const int color_options[5] = {kBlue, kAzure+10, kGreen-3, kViolet, kBlue+2};
    const char * draw_options[5] = {"HIST","HIST SAME","HIST SAME", "HIST SAME","HIST SAME"};
    const char * draw_options2[5] = {"E SAME", "E SAME","E SAME", "E SAME","E SAME"};

    double hist_max = 0.;
    // format the histograms and then make them

    FSI[0]->Sumw2();
    noFSI[0]->Sumw2();
    FSI[0]->SetStats(0);
    noFSI[0]->SetStats(0);

    hFSI[0]->Sumw2();
    hnoFSI[0]->Sumw2();
    hFSI[0]->SetStats(0);
    hnoFSI[0]->SetStats(0);

    fFSI[0]->Sumw2();
    fnoFSI[0]->Sumw2();
    fFSI[0]->SetStats(0);
    fnoFSI[0]->SetStats(0);

    noFSI[0]->SetLineColor(kRed);
    FSI[0]->SetLineColor(kBlack);

    hnoFSI[0]->SetLineColor(kRed);
    hFSI[0]->SetLineColor(kBlack);

    fnoFSI[0]->SetLineColor(kRed);
    fFSI[0]->SetLineColor(kBlack);

    hnoFSI[0]->SetLineStyle(kDashDotted);
    hFSI[0]->SetLineStyle(kDashDotted);

    fnoFSI[0]->SetLineStyle(kDashed);
    fFSI[0]->SetLineStyle(kDashed);

    noFSI[0]->GetXaxis()->SetTitle("PT_{miss} (GeV)");
    noFSI[0]->GetYaxis()->SetTitle("Events");
    noFSI[0]->GetXaxis()->CenterTitle( true);
    noFSI[0]->GetYaxis()->CenterTitle( true);

    noFSI[0]->SetTitle(TString(info)+TString(cuts));

    // take the maximum of the four interactions to use later in plotting
    if (noFSI[0]->GetMaximum() > hist_max)  hist_max = noFSI[0]->GetMaximum(); 
    if (FSI[0]->GetMaximum() > hist_max) hist_max = FSI[0]->GetMaximum();
    
    noFSI[0]->GetYaxis()->SetRangeUser(0, hist_max*1.1);

    noFSI[0]->Draw("E hist");
    FSI[0]->Draw("E hist same");
    hnoFSI[0]->Draw("E hist same");
    hFSI[0]->Draw("E hist same");
    fnoFSI[0]->Draw("E hist same");
    fFSI[0]->Draw("E hist same");


    // crop the margins of the canvas
    c->SetLeftMargin( 0.14);
    c->SetBottomMargin( 0.14);
    c->Update();

    // create and draw a legend for our histograms
    TLegend *legend = new TLegend( 0.7, 0.655, 1.2, 0.8);
    legend->AddEntry( noFSI[0],"C12 range 1 QE FSI","l");
    legend->AddEntry( FSI[0],"C12 range 1 QE no FSI","l");
    legend->AddEntry( hnoFSI[0],"C12 range 2 QE FSI","l");
    legend->AddEntry( hFSI[0],"C12 range 2 QE no FSI","l");
    legend->AddEntry( fnoFSI[0],"C12 range 3 QE FSI","l");
    legend->AddEntry( fFSI[0],"C12 range 3 QE no FSI","l");
    legend->SetBorderSize( 0);
    legend->SetFillStyle( 0);
    legend->Draw();

    TAxis *xaxis = FSI[0]->GetXaxis();
    Int_t binx = xaxis->FindBin(.25);

    double r1_noFSI_undercut = FSI[0]->Integral(1,binx);
    double r1_noFSI_overcut = FSI[0]->Integral(binx+1, FSI[0]->GetNbinsX());
    double r1_noFSI = FSI[0]->Integral(1,FSI[0]->GetNbinsX());
    double r1_FSI_undercut = noFSI[0]->Integral(1,binx);

    double r2_noFSI_undercut = hFSI[0]->Integral(1,binx);
    double r2_noFSI_overcut = hFSI[0]->Integral(binx+1, hFSI[0]->GetNbinsX());
    double r2_noFSI = hFSI[0]->Integral(1,hFSI[0]->GetNbinsX());
    double r2_FSI_undercut = hnoFSI[0]->Integral(1,binx);

    double r3_noFSI_undercut = fFSI[0]->Integral(1,binx);
    double r3_noFSI_overcut = fFSI[0]->Integral(binx+1, fFSI[0]->GetNbinsX());
    double r3_noFSI = fFSI[0]->Integral(1,fFSI[0]->GetNbinsX());
    double r3_FSI_undercut = fnoFSI[0]->Integral(1,binx);

    std::cout << "bin cut number = " << binx << "\n";

    std::cout << "Range 1 contamination = " << (r1_FSI_undercut/(r1_FSI_undercut + r1_noFSI_undercut)) << "\n";
    std::cout << "Range 1 efficiency = " << (r1_noFSI_undercut/r1_noFSI) << "\n";
    std::cout << "Range 1 noFSI loss = " << (r1_noFSI_overcut/r1_noFSI) << "\n";

    std::cout << "Range 2 contamination = " << (r2_FSI_undercut/(r2_FSI_undercut + r2_noFSI_undercut)) << "\n";
    std::cout << "Range 2 efficiency = " << (r2_noFSI_undercut/r2_noFSI) << "\n";
    std::cout << "Range 2 noFSI loss = " << (r2_noFSI_overcut/r2_noFSI) << "\n";

    std::cout << "Range 3 contamination = " << (r3_FSI_undercut/(r3_FSI_undercut + r3_noFSI_undercut)) << "\n";
    std::cout << "Range 3 efficiency = " << (r3_noFSI_undercut/r3_noFSI) << "\n";
    std::cout << "Range 3 noFSI loss = " << (r3_noFSI_overcut/r3_noFSI) << "\n";
    

    
   

}
