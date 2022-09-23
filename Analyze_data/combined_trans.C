#include <TGraphErrors.h>
#include <TFile.h>
#include <TCanvas.h>

void combined_trans() {
	TFile *C = TFile::Open("T_C12.root");
	TFile *He = TFile::Open("T_He4.root");
	TFile *Fe = TFile::Open("T_Fe56.root");

	TGraphErrors *C_data = (TGraphErrors*)C->Get("data");
	TGraphErrors *C_SuSA = (TGraphErrors*)C->Get("SuSA");
	TGraphErrors *He_data = (TGraphErrors*)He->Get("data");
	TGraphErrors *He_SuSA = (TGraphErrors*)He->Get("SuSA");
	TGraphErrors *Fe_data = (TGraphErrors*)Fe->Get("data");
	TGraphErrors *Fe_SuSA = (TGraphErrors*)Fe->Get("SuSA");

	C_data->SetMarkerStyle(3);
	C_data->SetLineColor(kBlue);
	C_data->SetMarkerColor(kBlue);
	C_SuSA->SetMarkerStyle(2);
	C_SuSA->SetMarkerColor(kBlue);
	C_SuSA->SetLineColor(kBlue);

	He_data->SetMarkerStyle(3);
	He_data->SetMarkerColor(kGreen);
	He_data->SetLineColor(kGreen);
	He_SuSA->SetMarkerStyle(2);
	He_SuSA->SetMarkerColor(kGreen);
	He_SuSA->SetLineColor(kGreen);

	Fe_data->SetMarkerStyle(3);
	Fe_data->SetMarkerColor(kBlack);
	Fe_data->SetLineColor(kBlack);
	Fe_SuSA->SetMarkerStyle(2);
	Fe_SuSA->SetMarkerColor(kBlack);
	Fe_SuSA->SetLineColor(kBlack);

	double dutta_C_P[4] = {.35,.7,.97,1.8};
	double dutta_C_T[4] = {.61,.60,.57,.58};
	double dutta_C_T_err[4] = {0.0,0.0,0.0,0.0};
	double dutta_C_P_err[4] = {0.0,0.0,0.0,0.0};
	for(int i = 0; i < 4; i++) {dutta_C_T_err[i] = dutta_C_T[i]*.05;}
	TGraphErrors* dutta_C = new TGraphErrors(4,dutta_C_P,dutta_C_T, dutta_C_P_err, dutta_C_T_err);
	dutta_C->SetMarkerColor(kBlue);
	dutta_C->SetLineColor(kBlue);
	dutta_C->SetMarkerSize(2);
	dutta_C->SetMarkerStyle(33);
        dutta_C->GetXaxis()->SetTitle("Proton Momentum (GeV)");
        dutta_C->GetYaxis()->SetTitle("Transparency");

	double dutta_Fe_P[4] = {.35,.7,.97,1.8};
	double dutta_Fe_T[4] = {.47,.44,.40,.42};
	double dutta_Fe_T_err[4] = {0.0,0.0,0.0,0.0};
	double dutta_Fe_P_err[4] = {0.0,0.0,0.0,0.0};
	for(int i = 0; i < 4; i++) {dutta_Fe_T_err[i] = dutta_Fe_T[i]*.05;}
	TGraphErrors* dutta_Fe = new TGraphErrors(4,dutta_Fe_P,dutta_Fe_T, dutta_Fe_P_err, dutta_Fe_T_err);
	dutta_Fe->SetMarkerColor(kBlack);
	dutta_Fe->SetLineColor(kBlack);
	dutta_Fe->SetMarkerSize(2);
	dutta_Fe->SetMarkerStyle(33);
	dutta_Fe->GetXaxis()->SetTitle("Proton Momentum (GeV)");
        dutta_Fe->GetYaxis()->SetTitle("Transparency");

	TLegend* leg = new TLegend();
	leg->AddEntry(C_data,"CLAS C12");
	leg->AddEntry(C_SuSA,"SuSAv2 C12");
	leg->AddEntry(dutta_C, "Dutta C12");
	leg->AddEntry(He_data,"CLAS He4");
	leg->AddEntry(He_SuSA,"SuSAv2 He4");
	leg->AddEntry(Fe_data,"CLAS Fe56");
	leg->AddEntry(Fe_SuSA,"SuSAv2 Fe56");
	leg->AddEntry(dutta_Fe, "Dutta Fe56");

	//Canvas *c = new TCanvas("","",800,800);
	dutta_C->Draw("AP");
	C_data->Draw("PL");
	//C_data->GetXaxis()->SetRangeUser(0.2,2.0);
	//c->Update();
	//C_data->Draw("APL");

	C_SuSA->Draw("PL");
	//dutta_C->Draw("P");
	He_data->Draw("PL");
	He_SuSA->Draw("PL");
	Fe_data->Draw("PL");
	Fe_SuSA->Draw("PL");
	dutta_Fe->Draw("P");
	leg->Draw();
}
