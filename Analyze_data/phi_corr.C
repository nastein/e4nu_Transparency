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
#include "../Transparency/myFunctions.h"

void phi_corr(std::string file_name) {

	TFile *input1 = TFile::Open(TString(file_name));

	TH2F* h= (TH2F*)input1->Get(TString::Format("h2_el_prot_phi_incl"));

    TCanvas *c = new TCanvas("c","c",1600,1000);
       c->SetLeftMargin( 0.2);
    c->SetBottomMargin( 0.2);
    c->SetRightMargin( 0.2);
    c->Update();

    h->SetStats(0);
	h->GetZaxis()->SetRangeUser( 0, h->GetMaximum()); // do not assign a color to bins with <=0 events in them
    h->GetXaxis()->SetRangeUser( 0, 360);
    h->GetYaxis()->SetRangeUser( 0, 360);
    h->GetXaxis()->SetTitle("#phi_{electron}");
    h->GetYaxis()->SetTitle("#phi_{proton}");
    h->GetXaxis()->CenterTitle( true);
    h->GetYaxis()->CenterTitle( true);

          h->GetXaxis()->CenterTitle();
        h->GetXaxis()->SetLabelFont(FontStyle);
        h->GetXaxis()->SetTitleFont(FontStyle);
        h->GetXaxis()->SetLabelSize(TextSize);
        h->GetXaxis()->SetTitleSize(TextSize);
        //h->GetXaxis()->SetTitleOffset(1.05);
        h->GetXaxis()->SetNdivisions(Ndivisions);
        // ----------------------------------------------------------------------------------------------------------------

        // Y-axis

        h->GetYaxis()->CenterTitle();
        h->GetYaxis()->SetTitleSize(TextSize);
        //h->GetYaxis()->SetTickSize(0.02);
        h->GetYaxis()->SetLabelSize(TextSize);
        //h->GetYaxis()->SetTitle(DoubleXSecTitle);
        h->GetYaxis()->SetTitleFont(FontStyle);
        h->GetYaxis()->SetLabelFont(FontStyle);
        //h->GetYaxis()->SetTitleOffset(1.05);
        h->GetYaxis()->SetNdivisions(Ndivisions);

    h->Draw("COLZ");

    c->SaveAs("phi_corr_bkgd.pdf");


}