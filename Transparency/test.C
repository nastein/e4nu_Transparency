#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

#include <TGraph.h>
#include <TGraphErrors.h>

#include "myFunctions.h"

using namespace std;

double mom(double T) {
	double mp = .938;
	double E = mp + T;
	return sqrt(E*E - mp*mp);

}

void test() {

	TFile *C_file = TFile::Open("T_C12_sectors.root");

	TGraphErrors * C_G = (TGraphErrors*)C_file->Get("data_C12");
	TGraphErrors * SuSAC_G = (TGraphErrors*)C_file->Get("SuSA_C12");
	TGraphErrors * G18C_G = (TGraphErrors*)C_file->Get("G_C12");

	TCanvas *c1 = new TCanvas("c1","c1",1200,1000);
	c1->SetLeftMargin(0.2);
	c1->SetBottomMargin(0.2);
	c1->SetRightMargin(0.2);

	PrettyGraph(C_G);
	PrettyGraph(SuSAC_G);
	PrettyGraph(G18C_G);

	C_G->GetYaxis()->SetRangeUser(0.0,1.0);
	G18C_G->SetMarkerColor(kRed);
	SuSAC_G->SetMarkerColor(kBlue);
	C_G->SetMarkerColor(kBlack);
	C_G->Draw("AP");
	SuSAC_G->Draw("P");
	G18C_G->Draw("P");
	
 	string line;                    /* string to hold each line */

	vector<double> hA_x; vector<double> hA_y;
	vector<double> hN_x; vector<double> hN_y;
	vector<double> INCL_x; vector<double> INCL_y;


    ifstream hA ("GENIE_hA2018.csv");
    ifstream hN ("GENIE_hN2018.csv");
    ifstream INCL ("GENIE_INCL.csv");

    while (getline (hA, line)) {
    	string val;
    	stringstream s (line);
    	int i = 0;
    	while (getline (s, val, ',')) {
    		if (i == 0) hA_x.push_back(mom(stod(val)));
    		else hA_y.push_back(stod(val));
    		i++;
    	}
    }
    hA.close();

    while (getline (hN, line)) {
    	string val;
    	stringstream s (line);
    	int i = 0;
    	while (getline (s, val, ',')) {
    		if (i == 0) hN_x.push_back(mom(stod(val)));
    		else hN_y.push_back(stod(val));
    		i++;
    	}
    }
    hN.close();

    while (getline (INCL, line)) {
    	string val;
    	stringstream s (line);
    	int i = 0;
    	while (getline (s, val, ',')) {
    		if (i == 0) INCL_x.push_back(mom(stod(val)));
    		else INCL_y.push_back(stod(val));
    		i++;
    	}
    }
    INCL.close();

    TGraph *INCL_G = new TGraph(INCL_x.size(),&(INCL_x[0]), &(INCL_y[0]));
    TGraph *hA_G = new TGraph(hA_x.size(),&(hA_x[0]), &(hA_y[0]));
    TGraph *hN_G = new TGraph(hN_x.size(),&(hN_x[0]), &(hN_y[0]));

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

    INCL_G->SetLineColor(6);
    INCL_G->SetLineWidth(3);
    INCL_G->Draw("L");
    hA_G->SetLineColor(kBlack);
    hA_G->SetLineWidth(3);
    hA_G->Draw("L");
    hN_G->SetLineColor(kRed);
    hN_G->SetLineWidth(3);
    hN_G->Draw("L");


	C_oneill_g->SetMarkerColor(kBlack);
	C_oneill_g->SetTitle("Oneil-C12");
	C_oneill_g->SetMarkerStyle(21);
	C_oneill_g->SetMarkerSize(1.5);
	C_oneill_g->Draw("P");
	C_dutta_g->SetMarkerColor(kBlack);
	C_dutta_g->SetTitle("Dutta-C12");
	C_dutta_g->SetMarkerStyle(22);
	C_dutta_g->SetMarkerSize(1.5);
	C_dutta_g->Draw("P");
	C_rohe_g->SetMarkerColor(kBlack);
	C_rohe_g->SetTitle("Rohe-C12");
	C_rohe_g->SetMarkerStyle(33);
	C_rohe_g->SetMarkerSize(1.5);
	C_rohe_g->Draw("P");
	C_Garrow_g->SetTitle("Garrow-C12");
	C_Garrow_g->SetMarkerStyle(29);
	C_Garrow_g->SetMarkerSize(1.5);
	C_Garrow_g->SetMarkerColor(kBlack);
	C_Garrow_g->Draw("P");
	C_Garino_g->SetTitle("Garino-C12");
	C_Garino_g->SetMarkerStyle(34);
	C_Garino_g->SetMarkerSize(1.5);
	C_Garino_g->SetMarkerColor(kBlack);
	C_Garino_g->Draw("P");


	TLegend *leg = new TLegend(.82,.55,.99,.85);
	leg->SetBorderSize(0);
	leg->SetNColumns(3);
	leg->AddEntry(C_G, "This Work");
	leg->AddEntry(SuSAC_G, "SuSAv2");
	leg->AddEntry(G18C_G, "G18");
	leg->AddEntry(INCL_G, "INCL++");
	leg->AddEntry(hA_G, "hA2018");
	leg->AddEntry(hN_G, "hN2018");
	leg->AddEntry(C_Garino_g, "MIT 1992", "p");
	leg->AddEntry(C_oneill_g, "SLAC 1995", "p");
	leg->AddEntry(C_dutta_g, "JLab 2003", "p");
	leg->AddEntry(C_rohe_g, "JLab 2005", "p");
	leg->AddEntry(C_Garrow_g, "JLab 2002", "p");
	leg->Draw();

}