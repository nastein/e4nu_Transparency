void draw_data() {

TFile *Fe_file = TFile::Open("T_Fe56_sectors.root");
TFile *He_file = TFile::Open("T_He4_sectors.root");
TFile *C_file = TFile::Open("T_C12_sectors.root");

TCanvas *c1 = new TCanvas("1","1",800,800);
TGraphErrors * C_G = (TGraphErrors*)C_file->Get("data_C12");
TGraphErrors * He_G = (TGraphErrors*)He_file->Get("data_He4");
TGraphErrors * Fe_G = (TGraphErrors*)Fe_file->Get("data_Fe56");
C_G->GetYaxis()->SetRangeUser(0.0,1.2);
He_G->SetMarkerColor(kRed);
C_G->SetMarkerColor(kBlue);
Fe_G->SetMarkerColor(kBlack);
C_G->Draw("AP");
Fe_G->Draw("P");
He_G->Draw("P");
TLegend *leg = new TLegend();
leg->AddEntry(C_G, "12C");
leg->AddEntry(He_G, "4He");
leg->AddEntry(Fe_G, "56Fe");
leg->Draw();


TCanvas *c2 = new TCanvas("2","2",800,800);
TGraphErrors * SuSAC_G = (TGraphErrors*)C_file->Get("SuSA_C12");
TGraphErrors * SuSAHe_G = (TGraphErrors*)He_file->Get("SuSA_He4");
TGraphErrors * SuSAFe_G = (TGraphErrors*)Fe_file->Get("SuSA_Fe56");
SuSAC_G->GetYaxis()->SetRangeUser(0.0,1.2);
SuSAHe_G->SetMarkerColor(kRed);
SuSAC_G->SetMarkerColor(kBlue);
SuSAFe_G->SetMarkerColor(kBlack);
SuSAC_G->Draw("AP");
SuSAFe_G->Draw("P");
SuSAHe_G->Draw("P");
TLegend *leg2 = new TLegend();
leg2->AddEntry(SuSAC_G, "12C");
leg2->AddEntry(SuSAHe_G, "4He");
leg2->AddEntry(SuSAFe_G, "56Fe");
leg2->Draw();


TCanvas *c3 = new TCanvas("3","3",800,800);
TGraphErrors * G18C_G = (TGraphErrors*)C_file->Get("G_C12");
TGraphErrors * G18He_G = (TGraphErrors*)He_file->Get("G_He4");
TGraphErrors * G18Fe_G = (TGraphErrors*)Fe_file->Get("G_Fe56");
G18C_G->GetYaxis()->SetRangeUser(0.0,1.2);
G18He_G->SetMarkerColor(kRed);
G18C_G->SetMarkerColor(kBlue);
G18Fe_G->SetMarkerColor(kBlack);
G18C_G->Draw("AP");
G18Fe_G->Draw("P");
G18He_G->Draw("P");
TLegend *leg3 = new TLegend();
leg3->AddEntry(G18C_G, "12C");
leg3->AddEntry(G18He_G, "4He");
leg3->AddEntry(G18Fe_G, "56Fe");
leg3->Draw();


}
