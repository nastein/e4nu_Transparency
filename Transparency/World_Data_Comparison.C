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
	


	double src_corr_err = .02;

	double Carbon_x[] = {.70588, .9864, 1.30317, 1.6425};
   	 double Carbon_xerr[] = {0,0,0,0};
    	double Carbon_y[] = {.57923, .61639, .57377, .58251};
   	 double Carbon_yerr[] = {.58798 - .57293, .628415 - .61639, .58251 - .57377, .6306 - .58251};
    	double Carbon_src_corr[] = {.06,.03,.03,.03};

   	 for(int i = 0; i < 4; i++) {
    		Carbon_src_corr[i] = Carbon_src_corr[i]*Carbon_y[i];
    		Carbon_yerr[i] = sqrt(pow(Carbon_yerr[i],2) + pow(src_corr_err*Carbon_y[i],2));
    		Carbon_y[i] = Carbon_y[i] + Carbon_src_corr[i];
    	}

	double Fe_x[] = {.7013, .9866, 1.302};
    double Fe_xerr[] = {0,0,0};
    double Fe_y[] = {.4119, .3926, .43807};
    double Fe_yerr[] = {.43125 - .4119, .42614 - .3926, .52045- .43807};
    double Fe_src_corr[] = {.066,.033,.033};
    
    for(int i = 0; i < 3; i++) {
    	Fe_src_corr[i] = Fe_src_corr[i]*Fe_y[i];
    	Fe_yerr[i] = sqrt(pow(Fe_yerr[i],2) + pow(src_corr_err*Fe_y[i],2));
    	Fe_y[i] = Fe_y[i] + Fe_src_corr[i];
    }
	TGraphErrors *C_g = new TGraphErrors(4, Carbon_x, Carbon_y, Carbon_xerr, Carbon_yerr);
	TGraphErrors *F_g = new TGraphErrors(3, Fe_x, Fe_y, Fe_xerr, Fe_yerr);

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


	double FGarrow[3] = {.394, .454, .391};
        double FGarrow_err[3] = {.012, .023, .015};
 	double FGarrow_p[3] = {mom(1.76), mom(3.263), mom(4.293)};
	TGraphErrors *F_Garrow_g = new TGraphErrors(3, FGarrow_p, FGarrow, p_err3, FGarrow_err);


	C_g->SetMarkerColor(kBlack);
	C_g->SetMarkerSize(2.5);
	PrettyGraph(C_g);
	C_g->GetYaxis()->SetRangeUser(0,1.0);
	C_g->GetXaxis()->SetTitle("Proton Momentum (GeV)");
	C_g->GetYaxis()->SetTitle("Transparency");
	C_g->SetTitle("CLAS6-C12");
   	TAxis *axis = C_g->GetXaxis();
   	axis->SetLimits(0.25,3.);
   	C_g->SetMarkerStyle(20);
   	C_g->SetMarkerSize(2.8); 
   	C_g->SetMarkerColor(kBlack);
	C_oneill_g->SetMarkerColor(kBlue);
	C_oneill_g->SetTitle("Oneil-C12");
	C_oneill_g->SetMarkerStyle(25);
	C_oneill_g->SetMarkerSize(2.0);
	C_dutta_g->SetMarkerColor(kBlue);
	C_dutta_g->SetTitle("Dutta-C12");
	C_dutta_g->SetMarkerStyle(26);
	C_dutta_g->SetMarkerSize(2.0);
	C_rohe_g->SetMarkerColor(kBlue);
	C_rohe_g->SetTitle("Rohe-C12");
	C_rohe_g->SetMarkerStyle(38);
	C_rohe_g->SetMarkerSize(2.0);
	C_Garrow_g->SetTitle("Garrow-C12");
	C_Garrow_g->SetMarkerStyle(32);
	C_Garrow_g->SetMarkerSize(2.0);
	C_Garrow_g->SetMarkerColor(kBlue);
	C_Garino_g->SetTitle("Garino-C12");
	C_Garino_g->SetMarkerStyle(46);
	C_Garino_g->SetMarkerSize(2.0);
	C_Garino_g->SetMarkerColor(kBlue);

	F_g->SetMarkerColor(kBlack);
	F_g->SetMarkerSize(2.7);
	F_g->GetYaxis()->SetRangeUser(0,1.0);
	PrettyGraph(F_g);
	F_g->GetXaxis()->SetTitle("Proton Momentum (GeV)");
	F_g->GetYaxis()->SetTitle("Transparency");
	F_g->SetMarkerStyle(20);
	F_g->SetMarkerColor(kBlack);
	F_g->SetTitle("CLAS6-Fe56");
   	F_g->SetMarkerSize(2.7);
	F_oneill_g->SetMarkerColor(kBlue);
	F_oneill_g->SetTitle("Oneil-Fe56");
	F_oneill_g->SetMarkerStyle(25);
	F_oneill_g->SetMarkerSize(2.0);
	F_dutta_g->SetMarkerColor(kBlue);
	F_dutta_g->SetTitle("Dutta-Fe56");
	F_dutta_g->SetMarkerStyle(26);
	F_dutta_g->SetMarkerSize(2.0);
	F_Garrow_g->SetMarkerColor(kBlue);
	F_Garrow_g->SetTitle("Garrow-Fe56");
	F_Garrow_g->SetMarkerStyle(32);
	F_Garrow_g->SetMarkerSize(2.0);

	TCanvas *c2 = new TCanvas("2","2",1200,1000);
	c2->SetLeftMargin(0.2);
	c2->SetBottomMargin(0.2);
	
	TAxis *ggaxis = C_oneill_g->GetXaxis();
        ggaxis->SetLimits(0.5,3.);

	C_g->Draw("AP");
	C_dutta_g->Draw("P");
	C_Garrow_g->Draw("P");
	C_Garino_g->Draw("P");
	C_oneill_g->Draw("P");
	C_rohe_g->Draw("P");

	TLegend *legC = new TLegend(0.25,0.21,0.8,0.5);
	legC->SetBorderSize(0);
	//legC->SetNColumns(3);
	legC->AddEntry(C_g, "This Work", "p");
	legC->AddEntry(C_Garino_g, "MIT 1992", "p");
	legC->AddEntry(C_oneill_g, "SLAC 1995", "p");
	legC->AddEntry(C_dutta_g, "JLab 2003", "p");
	legC->AddEntry(C_Garrow_g, "JLab 2002", "p");
	legC->AddEntry(C_rohe_g, "JLab 2005", "p");
	legC->Draw();
//	c2->SaveAs("World_Data_C.pdf");	

	TCanvas *c3 = new TCanvas("3","3",1200,1000);
	c3->SetLeftMargin(0.2);
	c3->SetBottomMargin(0.2);

   	TAxis *axisF = F_g->GetXaxis();
   	axisF->SetLimits(0.01,5.5);
	F_g->Draw("AP");
	F_oneill_g->Draw("P");
	F_dutta_g->Draw("P");
	F_Garrow_g->Draw("P");

	TLegend *legF = new TLegend(0.45,0.2,0.8,0.45);
	legF->SetBorderSize(0);
	//legF->SetNColumns(3);
	legF->AddEntry(F_g, "This Work", "p");
	legF->AddEntry(F_oneill_g, "SLAC 1995", "p");
	legF->AddEntry(F_dutta_g, "JLab 2003", "p");
	legF->AddEntry(F_Garrow_g, "JLab 2002", "p");
	legF->Draw();
//	c3->SaveAs("World_Data_Fe.pdf");


}

