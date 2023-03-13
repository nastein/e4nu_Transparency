#include "myFunctions.h"

double mom(double KE) {
	double mass = .938;
	double E = KE + mass;
	double p = sqrt(E*E - mass*mass);
	return p;
}

void other_data() {
    gStyle->SetOptTitle(0);

	TFile *myC= TFile::Open("T_C12_sectors.root");
	TFile *myF= TFile::Open("T_Fe56_sectors.root");
	TFile *myH= TFile::Open("T_He4_sectors.root");

	//TFile *myC_SF = TFile::Open("T_C12_SF.root");

	//TGraphErrors *C_g_SF = (TGraphErrors*)myC_SF->Get("Data_C12_SF");
	TGraphErrors *C_g = (TGraphErrors*)myC->Get("data_C12");
	TGraphErrors *F_g = (TGraphErrors*)myF->Get("data_Fe56");
	TGraphErrors *H_g = (TGraphErrors*)myH->Get("data_He4");
	F_g->RemovePoint(3);

	double p5_err[5] = {0.,0.,0.,0.,0.};
	double p4_err[4] = {0.,0.,0.,0.};

	double Cdutta[4] = {.625, .60, .58, .58};
	double Cdutta_err[4] = {.02, .02, .01, .02};
	double Cdutta_p[4] = {mom(.35),mom(.70),mom(.97),mom(1.80)};
	TGraphErrors *C_dutta_g = new TGraphErrors(4, Cdutta_p, Cdutta, p4_err, Cdutta_err);

	double Coneill[4] = {.64, .63, .61, .67};
	double Coneill_err[4] = {.05, .06, .06, .07};
	double Coneill_p[4] = {mom(.582),mom(1.678),mom(2.722),mom(3.641)};
	TGraphErrors *C_oneill_g = new TGraphErrors(4, Coneill_p, Coneill, p4_err, Coneill_err);

	double Crohe[5] = {.641, .628, .605, .593, .591};
	double Crohe_err[5] = {.025, .025, .024, .023, .023};
	double Crohe_p[5] = {mom(.328),mom(.433),mom(.625),mom(.830), mom(1.0)};
	TGraphErrors *C_rohe_g = new TGraphErrors(5, Crohe_p, Crohe, p5_err, Crohe_err);

	double CGarrow[3] = {.548, .570, .573};
	double CGarrow_err[3] = {.014, .015, .016};
	double CGarrow_p[3] = {mom(1.760), mom(3.263), mom (4.293)};
	double p_err3[3] = {0.,0.,0.};
	TGraphErrors *C_Garrow_g = new TGraphErrors(3,CGarrow_p, CGarrow, p_err3, CGarrow_err);

	double CGarino[1] = {0.76};
	double CGarino_err[1] = {.045};
	double CGarino_p[1] = {mom(0.18)};
	double p_err1[1] = {mom(0.05)};
	TGraphErrors *C_Garino_g = new TGraphErrors(1,CGarino_p, CGarino,p_err1,CGarino_err);

	double Fdutta[4] = {.51, .44, .42, .42};
	double Fdutta_err[4] = {.02, .01, .02, .01};
	double Fdutta_p[4] = {mom(.35),mom(.70),mom(.97),mom(1.80)};
	TGraphErrors *F_dutta_g = new TGraphErrors(4, Fdutta_p, Fdutta, p4_err, Fdutta_err);

	double Foneill[4] = {.50, .38, .40, .43};
	double Foneill_err[4] = {.05, .04, .05, .05};
	double Foneill_p[4] = {mom(.582),mom(1.678),mom(2.722),mom(3.641)};
	TGraphErrors *F_oneill_g = new TGraphErrors(4, Foneill_p, Foneill, p4_err, Foneill_err);

	TCanvas *c1 = new TCanvas("1","1",1200,1000);
	c1->SetLeftMargin(0.2);
	c1->SetBottomMargin(0.2);
//	c1->SetRightMargin(0.2);


	C_g->SetMarkerColor(kBlack);
	C_g->SetMarkerSize(1.5);
	C_g->GetYaxis()->SetRangeUser(0,1.0);
	C_g->GetXaxis()->SetTitle("Proton Momentum (GeV)");
	C_g->GetYaxis()->SetTitle("Transparency");
	PrettyGraph(C_g);
	C_g->SetTitle("CLAS6-C12");
   	TAxis *axis = C_g->GetXaxis();
   	axis->SetLimits(0.01,5.);
   	C_g->SetMarkerStyle(20);
   	C_g->SetMarkerSize(1.5); 
   	C_g->SetMarkerColor(kBlue);
	C_g->Draw("AP");
	C_oneill_g->SetMarkerColor(kBlue);
	C_oneill_g->SetTitle("Oneil-C12");
	C_oneill_g->SetMarkerStyle(21);
	C_oneill_g->SetMarkerSize(1.5);
	C_oneill_g->Draw("P");
	C_dutta_g->SetMarkerColor(kBlue);
	C_dutta_g->SetTitle("Dutta-C12");
	C_dutta_g->SetMarkerStyle(22);
	C_dutta_g->SetMarkerSize(1.5);
	C_dutta_g->Draw("P");
	C_rohe_g->SetMarkerColor(kBlue);
	C_rohe_g->SetTitle("Rohe-C12");
	C_rohe_g->SetMarkerStyle(33);
	C_rohe_g->SetMarkerSize(1.5);
	C_rohe_g->Draw("P");
	C_Garrow_g->SetTitle("Garrow-C12");
	C_Garrow_g->SetMarkerStyle(29);
	C_Garrow_g->SetMarkerSize(1.5);
	C_Garrow_g->SetMarkerColor(kBlue);
	C_Garrow_g->Draw("P");
	C_Garino_g->SetTitle("Garino-C12");
	C_Garino_g->SetMarkerStyle(34);
	C_Garino_g->SetMarkerSize(1.5);
	C_Garino_g->SetMarkerColor(kBlue);
	C_Garino_g->Draw("P");
	
	F_g->SetMarkerColor(kBlack);
	F_g->SetMarkerSize(1.5);
	F_g->GetYaxis()->SetRangeUser(0,0.7);
	PrettyGraph(F_g);
	F_g->GetXaxis()->SetTitle("Proton Momentum (GeV)");
	F_g->GetYaxis()->SetTitle("Transparency");
	F_g->SetMarkerStyle(20);
	F_g->SetMarkerColor(kBlack);
	F_g->SetTitle("CLAS6-Fe56");
   	
	F_g->Draw("P");
	F_oneill_g->SetMarkerColor(kBlack);
	F_oneill_g->SetTitle("Oneil-Fe56");
	F_oneill_g->SetMarkerStyle(21);
	F_oneill_g->SetMarkerSize(1.5);
	F_oneill_g->Draw("P");
	F_dutta_g->SetMarkerColor(kBlack);
	F_dutta_g->SetTitle("Dutta-Fe56");
	F_dutta_g->SetMarkerStyle(22);
	F_dutta_g->SetMarkerSize(1.5);
	F_dutta_g->Draw("P");

	H_g->SetMarkerColor(kRed);
	H_g->SetMarkerSize(1.5);
	H_g->SetMarkerStyle(20);
	H_g->Draw("P");

	TLegend *leg = new TLegend(0.25,0.22,0.65,0.43);
	leg->SetBorderSize(0);
	leg->SetNColumns(3);
	leg->AddEntry(C_g, "C This Work", "p");
	leg->AddEntry(C_Garino_g, "C MIT 1992", "p");
	leg->AddEntry(C_oneill_g, "C SLAC 1995", "p");
	leg->AddEntry(C_dutta_g, "C JLab 2003", "p");
	leg->AddEntry(C_rohe_g, "C JLab 2005", "p");
	leg->AddEntry(C_Garrow_g, "C JLab 2002", "p");
	leg->AddEntry(F_g, "Fe This Work", "p");
	leg->AddEntry(F_oneill_g, "Fe SLAC 1995", "p");
	leg->AddEntry(F_dutta_g, "Fe JLab 2003", "p");
	leg->AddEntry(H_g, "He This Work", "p");
	leg->Draw();
	c1->SaveAs("World_Data.pdf");	

	TCanvas *c2 = new TCanvas("2","2",1200,1000);
	c2->SetLeftMargin(0.2);
	c2->SetBottomMargin(0.2);

	C_g->Draw("AP");
	C_oneill_g->Draw("P");
	C_dutta_g->Draw("P");
	C_rohe_g->Draw("P");
	C_Garrow_g->Draw("P");
	C_Garino_g->Draw("P");

	TLegend *legC = new TLegend(0.25,0.22,0.65,0.43);
	legC->SetBorderSize(0);
	legC->SetNColumns(3);
	legC->AddEntry(C_g, "This Work", "p");
	legC->AddEntry(C_Garino_g, "MIT 1992", "p");
	legC->AddEntry(C_oneill_g, "SLAC 1995", "p");
	legC->AddEntry(C_dutta_g, "JLab 2003", "p");
	legC->AddEntry(C_rohe_g, "JLab 2005", "p");
	legC->AddEntry(C_Garrow_g, "JLab 2002", "p");
	legC->Draw();
	c2->SaveAs("World_Data_C.pdf");	

	TCanvas *c3 = new TCanvas("3","3",1200,1000);
	c3->SetLeftMargin(0.2);
	c3->SetBottomMargin(0.2);

   	TAxis *axisF = F_g->GetXaxis();
   	axisF->SetLimits(0.01,5.);
	F_g->Draw("AP");
	F_oneill_g->Draw("P");
	F_dutta_g->Draw("P");

	TLegend *legF = new TLegend(0.25,0.22,0.65,0.43);
	legF->SetBorderSize(0);
	legF->SetNColumns(3);
	legF->AddEntry(F_g, "This Work", "p");
	legF->AddEntry(F_oneill_g, "SLAC 1995", "p");
	legF->AddEntry(F_dutta_g, "JLab 2003", "p");
	legF->Draw();
	c3->SaveAs("World_Data_Fe.pdf");


}

