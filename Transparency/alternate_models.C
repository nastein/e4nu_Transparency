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
	//TGraphErrors *C_g = (TGraphErrors*)myC->Get("data_C12");
	//TGraphErrors *F_g = (TGraphErrors*)myF->Get("data_Fe56");
	TGraphErrors *H_g = (TGraphErrors*)myH->Get("data_He4");
	//F_g->RemovePoint(3);
	


	double Carbon_x[] = {.70588, .9864, 1.30317, 1.6425};
	double Carbon_xerr[] = {0,0,0,0};
	double Carbon_y[] = {.57923, .61639, .57377, .58251};
	double Carbon_yerr[] = {.58798 - .57293, .628415 - .61639, .58251 - .57377, .6306 - .58251};

	double Fe_x[] = {.7013, .9866, 1.302};
	double Fe_xerr[] = {0,0,0};
	double Fe_y[] = {.4119, .3926, .43807};
	double Fe_yerr[] = {.43125 - .4119, .42614 - .3926, .52045- .43807};

	TGraphErrors *C_g = new TGraphErrors(4, Carbon_x, Carbon_y, Carbon_xerr, Carbon_yerr);
	TGraphErrors *F_g = new TGraphErrors(3, Fe_x, Fe_y, Fe_xerr, Fe_yerr);

	double p5_err[5] = {0.,0.,0.,0.,0.};
	double p4_err[4] = {0.,0.,0.,0.};

	TCanvas *c1 = new TCanvas("1","1",1200,1000);
	c1->SetLeftMargin(0.2);
	c1->SetBottomMargin(0.2);
//	c1->SetRightMargin(0.2);


	C_g->SetMarkerColor(kBlack);
	C_g->SetMarkerSize(1.7);
	C_oneill_g->GetYaxis()->SetRangeUser(0,0.85);
	C_oneill_g->GetXaxis()->SetTitle("Proton Momentum (GeV)");
	C_oneill_g->GetYaxis()->SetTitle("Transparency");
	PrettyGraph(C_oneill_g);
	C_g->SetTitle("CLAS6-C12");
   	TAxis *axis = C_g->GetXaxis();
   	axis->SetLimits(0.01,5.);
   	C_g->SetMarkerStyle(20);
   	C_g->SetMarkerSize(2.0); 
   	C_g->SetMarkerColor(kBlack);
	C_oneill_g->SetMarkerColor(kBlue);
	C_oneill_g->SetTitle("Oneil-C12");
	C_oneill_g->SetMarkerStyle(21);
	C_oneill_g->SetMarkerSize(2.0);
	C_oneill_g->Draw("AP");
	C_dutta_g->SetMarkerColor(kBlue);
	C_dutta_g->SetTitle("Dutta-C12");
	C_dutta_g->SetMarkerStyle(22);
	C_dutta_g->SetMarkerSize(2.0);

	F_g->SetMarkerColor(kBlack);
	F_g->SetMarkerSize(2.0);
	F_g->GetYaxis()->SetRangeUser(0,0.6);
	PrettyGraph(F_g);
	F_g->GetXaxis()->SetTitle("Proton Momentum (GeV)");
	F_g->GetYaxis()->SetTitle("Transparency");
	F_g->SetMarkerStyle(20);
	F_g->SetMarkerColor(kBlack);
	F_g->SetTitle("CLAS6-Fe56");
   	
	F_g->Draw("P");
	F_oneill_g->SetMarkerColor(kBlue);
	F_oneill_g->SetTitle("Oneil-Fe56");
	F_oneill_g->SetMarkerStyle(21);
	F_oneill_g->SetMarkerSize(2.0);
	F_oneill_g->Draw("P");
	F_dutta_g->SetMarkerColor(kBlue);
	F_dutta_g->SetTitle("Dutta-Fe56");
	F_dutta_g->SetMarkerStyle(22);
	F_dutta_g->SetMarkerSize(2.0);
	F_dutta_g->Draw("P");
	F_Garrow_g->SetMarkerColor(kBlue);
	F_Garrow_g->SetTitle("Garrow-Fe56");
	F_Garrow_g->SetMarkerStyle(33);
	F_Garrow_g->SetMarkerSize(2.0);
	F_Garrow_g->Draw("P");

	TLegend *leg = new TLegend(0.25,0.26,0.65,0.46);
	leg->SetBorderSize(0);
	leg->SetNColumns(3);
        leg->SetTextSize(40);
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
	//c1->SaveAs("World_Data.pdf");	

	TCanvas *c2 = new TCanvas("2","2",1200,1000);
	c2->SetLeftMargin(0.2);
	c2->SetBottomMargin(0.2);
	
	TAxis *ggaxis = C_oneill_g->GetXaxis();
        ggaxis->SetLimits(0.01,5.);

	C_oneill_g->Draw("AP");
	C_dutta_g->Draw("P");
	C_rohe_g->Draw("P");
	C_Garrow_g->Draw("P");
	C_Garino_g->Draw("P");
	C_g->Draw("P");

	TLegend *legC = new TLegend(0.25,0.21,0.8,0.63);
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
   	axisF->SetLimits(0.01,5.5);
	F_g->Draw("AP");
	F_oneill_g->Draw("P");
	F_dutta_g->Draw("P");
	F_Garrow_g->Draw("P");

	TLegend *legF = new TLegend(0.25,0.21,0.8,0.58);
	legF->SetBorderSize(0);
	legF->SetNColumns(3);
	legF->AddEntry(F_g, "This Work", "p");
	legF->AddEntry(F_oneill_g, "SLAC 1995", "p");
	legF->AddEntry(F_dutta_g, "JLab 2003", "p");
	legF->AddEntry(F_Garrow_g, "JLab 2002", "p");
	legF->Draw();
	c3->SaveAs("World_Data_Fe.pdf");


}

