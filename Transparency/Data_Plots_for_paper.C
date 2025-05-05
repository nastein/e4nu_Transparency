#include "myFunctions.h"

double mom(double KE) {
        double mass = .938;
        double E = KE + mass;
        double p = sqrt(E*E - mass*mass);
        return p;
}

void src_corrected_data() {
	gStyle->SetOptTitle(0);


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

	 std::cout << "Carbon" << "\n";
    for(int i = 0; i < 4; i++) {
    	std::cout << Carbon_y[i] << " +/- " << Carbon_yerr[i] << "\n";
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

  std::cout << "Iron" << "\n";
    for(int i = 0; i < 3; i++) {
    	std::cout << Fe_y[i] << " +/- " << Fe_yerr[i] << "\n";
    }


    double He_x[] = {.81, 1.0, 1.3, 1.65};
    double He_xerr[] = {0,0,0,0};
    double He_y[] = {.72, .69, .67, .69};
    double He_yerr[] = {.006, .02, .02,.05};
    double He_src_corr[] = {.045,.0225,.0225,.0225};
    
    for(int i = 0; i < 4; i++) {
    	He_src_corr[i] = He_src_corr[i]*He_y[i];
    	He_yerr[i] = sqrt(pow(He_yerr[i],2) + pow(src_corr_err*He_y[i],2));
    	He_y[i] = He_y[i] + He_src_corr[i];
    }

    std::cout << "Helium" << "\n";
    for(int i = 0; i < 4; i++) {
    	std::cout << He_y[i] << " +/- " << He_yerr[i] << "\n";
    }

    TGraphErrors *C_g = new TGraphErrors(4, Carbon_x, Carbon_y, Carbon_xerr, Carbon_yerr);
    TGraphErrors *F_g = new TGraphErrors(3, Fe_x, Fe_y, Fe_xerr, Fe_yerr);
    TGraphErrors *H_g = new TGraphErrors(4, He_x, He_y, He_xerr, He_yerr);

    C_g->SetMarkerColor(kBlue);
    C_g->SetMarkerSize(2.0);        
    C_g->GetXaxis()->SetTitle("Proton Momentum (GeV)");
    C_g->GetYaxis()->SetTitle("Transparency");

    F_g->SetMarkerColor(kBlack);
    F_g->SetMarkerSize(2.0);

    H_g->SetMarkerColor(kRed);
    H_g->SetMarkerSize(2.9);

    PrettyGraph(C_g);
    PrettyGraph(F_g);
    PrettyGraph(H_g);


    TAxis *axis = C_g->GetXaxis();
    axis->SetLimits(0.6,1.8);
    C_g->GetYaxis()->SetRangeUser(0,1.);

    TCanvas *c2 = new TCanvas("2","2",1200,1000);
    c2->SetLeftMargin(0.2);
    c2->SetBottomMargin(0.2);

    C_g->Draw("AP");
    F_g->Draw("P");
    H_g->Draw("P");

    TLegend *legC = new TLegend(0.65,0.21,0.8,0.43);
    legC->SetBorderSize(0);
    legC->AddEntry(C_g, "C", "p");
    legC->AddEntry(H_g, "He", "p");
    legC->AddEntry(F_g, "Fe", "p");
    legC->Draw();
    c2->SaveAs("src_correct_data_transparencies.pdf");

   	/*
    //TFile *myC= TFile::Open("T_C12_sectors.root");
    TFile *myF= TFile::Open("T_Fe56_sectors.root");
    TFile *myH= TFile::Open("T_He4_sectors.root");

    TGraphErrors *F_susa_g = (TGraphErrors*)myF->Get("SuSA_Fe56");
    TGraphErrors *H_susa_g = (TGraphErrors*)myH->Get("SuSA_He4");
    F_susa_g->SetMarkerColor(kBlue);
    H_susa_g->SetMarkerColor(kBlue);
    F_g->SetMarkerColor(kBlack);
    H_g->SetMarkerColor(kBlack);

    TGraphErrors *F_G_g = (TGraphErrors*)myF->Get("G_Fe56");
    TGraphErrors *H_G_g = (TGraphErrors*)myH->Get("G_He4");
    F_G_g->SetMarkerColor(kRed);
    H_G_g->SetMarkerColor(kRed);

    TCanvas *c3 = new TCanvas("3","3",1200,1000);
    c3->SetLeftMargin(0.2);
    c3->SetBottomMargin(0.2);
    F_g->GetYaxis()->SetRangeUser(0,1.0);
    F_g->Draw("AP");
    F_susa_g->Draw("P");
    F_G_g->Draw("P");

    TLegend *legF = new TLegend(0.65,0.21,0.8,0.43);
    legF->SetBorderSize(0);
    legF->AddEntry(F_g, "CLAS Data", "p");
    legF->AddEntry(F_susa_g, "SuSA v2", "p");
    legF->AddEntry(F_G_g, "G18", "p");
    legF->Draw();

    TCanvas *c4 = new TCanvas("4","4",1200,1000);
    c4->SetLeftMargin(0.2);
    c4->SetBottomMargin(0.2);
    H_g->GetYaxis()->SetRangeUser(0,1.0);
    H_g->Draw("AP");
    H_susa_g->Draw("P");
    H_G_g->Draw("P");

    TLegend *legH = new TLegend(0.65,0.21,0.8,0.43);
    legH->SetBorderSize(0);
    legH->AddEntry(H_g, "CLAS Data", "p");
    legH->AddEntry(H_susa_g, "SuSA v2", "p");
    legH->AddEntry(H_G_g, "G18", "p");
    legH->Draw();
 
*/
}
