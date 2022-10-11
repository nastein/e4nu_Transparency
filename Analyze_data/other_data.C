double mom(double KE) {
	double mass = .938;
	double E = KE + mass;
	double p = sqrt(E*E - mass*mass);
	return p;
}

void other_data() {

	TFile *myC= TFile::Open("T_C12_sectors.root");
	TFile *myF= TFile::Open("T_Fe56_sectors.root");

	TGraphErrors *C_g = (TGraphErrors*)myC->Get("data_C12");
	TGraphErrors *F_g = (TGraphErrors*)myF->Get("data_Fe56");

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

	double Crohe[5] = {.628, .641, .605, .593, .591};
	double Crohe_err[5] = {.025, .025, .024, .023, .023};
	double Crohe_p[5] = {mom(.328),mom(433),mom(625),mom(.380), mom(1.0)};
	TGraphErrors *C_rohe_g = new TGraphErrors(5, Crohe_p, Crohe, p5_err, Crohe_err);

	double Fdutta[4] = {.51, .44, .42, .42};
	double Fdutta_err[4] = {.02, .01, .02, .01};
	double Fdutta_p[4] = {mom(.35),mom(.70),mom(.97),mom(1.80)};
	TGraphErrors *F_dutta_g = new TGraphErrors(4, Fdutta_p, Fdutta, p4_err, Fdutta_err);

	double Foneill[4] = {.50, .38, .40, .43};
	double Foneill_err[4] = {.05, .04, .05, .05};
	double Foneill_p[4] = {mom(.582),mom(1.678),mom(2.722),mom(3.641)};
	TGraphErrors *F_oneill_g = new TGraphErrors(4, Foneill_p, Foneill, p4_err, Foneill_err);

	TCanvas *c1 = new TCanvas("1","1",800,800);
	C_g->SetMarkerColor(kBlack);
	C_g->GetXaxis()->SetTitle("Proton Momentum (GeV)");
	C_g->GetYaxis()->SetTitle("Transparency");
	C_g->SetTitle("CLAS6-C12");
   	TAxis *axis = C_g->GetXaxis();
   	axis->SetLimits(0.3,5.); 
	C_g->Draw("AP");  
	C_oneill_g->SetMarkerColor(kRed);
	C_oneill_g->SetTitle("Oneil-C12");
	C_oneill_g->SetMarkerStyle(20);
	C_oneill_g->Draw("P");
	C_dutta_g->SetMarkerColor(kBlue);
	C_dutta_g->SetTitle("Dutta-C12");
	C_dutta_g->SetMarkerStyle(20);
	C_dutta_g->Draw("P");
	C_rohe_g->SetMarkerColor(6);
	C_rohe_g->SetTitle("Rohe-C12");
	C_rohe_g->SetMarkerStyle(20);
	C_rohe_g->Draw("P");


	c1->BuildLegend();

	TCanvas *c2 = new TCanvas("2","2",800,800);
	F_g->SetMarkerColor(kBlack);
	F_g->GetXaxis()->SetTitle("Proton Momentum (GeV)");
	F_g->GetYaxis()->SetTitle("Transparency");
	F_g->SetTitle("CLAS6-Fe56");
   	TAxis *axis2 = F_g->GetXaxis();
   	axis2->SetLimits(0.3,5.);
	F_g->Draw("AP");
	F_oneill_g->SetMarkerColor(kRed);
	F_oneill_g->SetTitle("Oneil-Fe56");
	F_oneill_g->SetMarkerStyle(20);
	F_oneill_g->Draw("P");
	F_dutta_g->SetMarkerColor(kBlue);
	F_dutta_g->SetTitle("Dutta-Fe56");
	F_dutta_g->SetMarkerStyle(20);
	F_dutta_g->Draw("P");

	c2->BuildLegend();

}

