#include "myFunctions.h"


void Data_MC_Plots() {
	
	//Carbon
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

    TGraphErrors *C_g = new TGraphErrors(4, Carbon_x, Carbon_y, Carbon_xerr, Carbon_yerr);

    //Iron
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

    TGraphErrors *F_g = new TGraphErrors(3, Fe_x, Fe_y, Fe_xerr, Fe_yerr);

    //Helium
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

    TGraphErrors *H_g = new TGraphErrors(4, He_x, He_y, He_xerr, He_yerr);

    //MC transparencies
    TFile *MC_Fe = TFile::Open("T_Fe56_sectors.root");
    TFile *MC_He = TFile::Open("T_He4_sectors.root");
    TFile *MC_C = TFile::Open("T_C12_sectors.root");
    TFile *Alt_MC_C = TFile::Open("T_C12_Alternate_models.root");

    TGraphErrors *SuSA_Fe = (TGraphErrors*)MC_Fe->Get("SuSA_Fe56");
    TGraphErrors *SuSA_He = (TGraphErrors*)MC_He->Get("SuSA_He4");
    SuSA_Fe->SetMarkerSize(2.3);
    SuSA_He->SetMarkerSize(2.3);

    TGraphErrors *G18_Fe = (TGraphErrors*)MC_Fe->Get("G_Fe56");
    TGraphErrors *G18_He = (TGraphErrors*)MC_He->Get("G_He4");
    G18_Fe->SetMarkerSize(2.3);
    G18_He->SetMarkerSize(2.3);

    TGraphErrors *G18_C = (TGraphErrors*)MC_C->Get("G_C12");
    TGraphErrors *LFG_HA = (TGraphErrors*)Alt_MC_C->Get("SuSAv2 LFG HA");
    TGraphErrors *CFG_HA = (TGraphErrors*)Alt_MC_C->Get("SuSAv2 CFG HA");
    TGraphErrors *LFG_HN = (TGraphErrors*)Alt_MC_C->Get("SuSAv2 LFG HN");
    G18_C->SetMarkerSize(2.3);
    LFG_HA->SetMarkerSize(2.3);
    CFG_HA->SetMarkerSize(2.3);
    LFG_HN->SetMarkerSize(2.3);


    TCanvas *cdt = new TCanvas("Data", "Data", 1200, 1200);
    cdt->SetLeftMargin(0.2);
    cdt->SetBottomMargin(0.2);
    PrettyGraph(C_g);
    PrettyGraph(H_g);
    PrettyGraph(F_g);
    C_g->SetMarkerSize(2.3);
    F_g->SetMarkerSize(2.3);
    H_g->SetMarkerSize(2.3);
    C_g->SetTitle("");
    C_g->GetXaxis()->SetTitle("Proton Momentum (GeV)");
    C_g->GetYaxis()->SetTitle("Transparency");
    C_g->GetYaxis()->SetRangeUser(0,1.0);
    C_g->GetXaxis()->SetLimits(0.5,1.8);
    C_g->SetMarkerColor(kBlue);
/* 
    TLatex *latexF = new TLatex(F_g->GetX()[2]+.01, F_g->GetY()[2]-.1,"Fe");
    F_g->GetListOfFunctions()->Add(latexF);
    latexF->SetTextSize(0.06); latexF->SetTextColor(kBlack);

    TLatex *latexC = new TLatex(C_g->GetX()[3]+.01, C_g->GetY()[3]-.1,"C");
    C_g->GetListOfFunctions()->Add(latexC);
    latexC->SetTextSize(0.06); latexC->SetTextColor(kBlue);

    TLatex *latexH = new TLatex(H_g->GetX()[3]-.03, H_g->GetY()[3]+.1,"He");
    H_g->GetListOfFunctions()->Add(latexH);
    latexH->SetTextSize(0.06); latexH->SetTextColor(kRed);

    C_g->Draw("AP");
    F_g->SetMarkerColor(kBlack);
    F_g->Draw("P");
    H_g->SetMarkerColor(kRed);
    H_g->Draw("P");
    cdt->SaveAs("Data_Trans_newlabels.png");

    TLegend *legD = new TLegend(.75,.29,.92,.59);
    legD->SetBorderSize(0);
    legD->SetTextSize(.03);
    legD->AddEntry(H_g, "He", "p");
    legD->AddEntry(C_g, "C", "p");
    legD->AddEntry(F_g, "Fe", "p");
//    legD->Draw();
*/
    TCanvas *c3 = new TCanvas("Iron", "Iron", 1200, 1000);
    c3->SetLeftMargin(0.2);
    c3->SetBottomMargin(0.2);
  //  PrettyGraph(F_g);
    F_g->SetTitle("");
    F_g->GetXaxis()->SetTitle("Proton Momentum (GeV)");
    F_g->GetYaxis()->SetTitle("Transparency");
    F_g->GetYaxis()->SetRangeUser(0,1.0);
    F_g->GetXaxis()->SetLimits(0.5,1.8);
    
     F_g->SetMarkerColor(kBlack);
/*
    
    TLatex *latexD = new TLatex(F_g->GetX()[1]-.1, F_g->GetY()[1]-.1,"CLAS");
    F_g->GetListOfFunctions()->Add(latexD);
    latexD->SetTextSize(0.06); latexD->SetTextColor(kBlack);

    TLatex *latexS = new TLatex(SuSA_Fe->GetX()[2]-.15, SuSA_Fe->GetY()[2]+.05,"SuSAv2");
    SuSA_Fe->GetListOfFunctions()->Add(latexS);
    latexS->SetTextSize(0.06); latexS->SetTextColor(kBlue);

    TLatex *latexG = new TLatex(G18_Fe->GetX()[0]-.03, G18_Fe->GetY()[0]+.1,"G18");
    G18_Fe->GetListOfFunctions()->Add(latexG);
    latexG->SetTextSize(0.06); latexG->SetTextColor(kRed);

    F_g->Draw("AP");
    SuSA_Fe->Draw("P");
    G18_Fe->Draw("P");

    TLegend *leg = new TLegend(.62,.59,.79,.89);
    leg->SetBorderSize(0);
    leg->SetTextSize(.03);
    leg->AddEntry(F_g, "CLAS Data", "p");
    leg->AddEntry(SuSA_Fe, "SuSAv2", "p");
    leg->AddEntry(G18_Fe, "G18", "p");
    //leg->Draw();

    //c3->SaveAs("T_56Fe_total.png");
*/
/*
    TCanvas *c4 = new TCanvas("Helium", "Helium", 1200, 1000);
    c4->cd();
    c4->SetLeftMargin(0.2);
    c4->SetBottomMargin(0.2);
    //PrettyGraph(H_g);
    H_g->SetTitle("");
    H_g->GetXaxis()->SetTitle("Proton Momentum (GeV)");
    H_g->GetYaxis()->SetTitle("Transparency");
    H_g->GetYaxis()->SetRangeUser(0,1.0);
    H_g->GetXaxis()->SetLimits(0.5,1.8);
    H_g->SetMarkerColor(kBlack);

        TLatex *latexDH = new TLatex(H_g->GetX()[1]-.1, H_g->GetY()[1]-.1,"CLAS");
    H_g->GetListOfFunctions()->Add(latexDH);
    latexDH->SetTextSize(0.06); latexDH->SetTextColor(kBlack);

    TLatex *latexSH = new TLatex(SuSA_He->GetX()[2]-.15, SuSA_He->GetY()[2]+.05,"SuSAv2");
    SuSA_He->GetListOfFunctions()->Add(latexSH);
    latexSH->SetTextSize(0.06); latexSH->SetTextColor(kBlue);

    TLatex *latexGH = new TLatex(G18_He->GetX()[0]-.03, G18_He->GetY()[0]+.1,"G18");
    G18_He->GetListOfFunctions()->Add(latexGH);
    latexGH->SetTextSize(0.06); latexGH->SetTextColor(kRed);    

    H_g->Draw("AP");
    SuSA_He->Draw("P");
    G18_He->Draw("P");

    TLegend *leg2 = new TLegend(.62,.25,.79,.55);
    leg2->SetBorderSize(0);
    leg2->SetTextSize(.03);
    leg2->AddEntry(H_g, "CLAS Data", "p");
    leg2->AddEntry(SuSA_He, "SuSAv2", "p");
    leg2->AddEntry(G18_He, "G18", "p");
  //  leg2->Draw();


//    c4->SaveAs("T_4He_total.png");

*/

    TCanvas *c5 = new TCanvas("Carbon", "Carbon", 1200, 1000);
    c5->cd();
    c5->SetLeftMargin(0.2);
    c5->SetBottomMargin(0.2);
    //PrettyGraph(C_g);
    C_g->SetTitle("");
    C_g->GetXaxis()->SetTitle("Proton Momentum (GeV)");
    C_g->GetYaxis()->SetTitle("Transparency");
    C_g->GetYaxis()->SetRangeUser(0,1.0);
    LFG_HN->SetMarkerColor(kBlue);
    LFG_HN->SetMarkerStyle(20);
    LFG_HA->SetMarkerColor(kBlue);
    LFG_HA->SetMarkerStyle(26);
    CFG_HA->SetMarkerColor(kBlue);
    CFG_HA->SetMarkerStyle(25);
    C_g->SetMarkerColor(kBlack);
    C_g->Draw("AP");
    LFG_HN->Draw("P");
    CFG_HA->Draw("P");
    LFG_HA->Draw("P");
    G18_C->Draw("P");

    TLegend *leg3 = new TLegend(.62,.25,.79,.55);
    leg3->SetBorderSize(0);
    leg3->SetTextSize(.03);
    leg3->AddEntry(C_g, "CLAS Data", "p");
    leg3->AddEntry(LFG_HA, "SuSAv2 LFG HA", "p");
    leg3->AddEntry(CFG_HA, "SuSAv2 CFG HA", "p");
    leg3->AddEntry(LFG_HN, "SuSAv2 LFG HN", "p");
    leg3->AddEntry(G18_C, "G18 LFG HA", "p");
    leg3->Draw();


    c5->SaveAs("Carbon_MC_Data_newlabels.png");







}
