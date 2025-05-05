
#include "myFunctions.h"

int A_He = 4;
int A_C = 12;
int A_Fe = 56;

double mom(double KE) {
        double mass = .938;
        double E = KE + mass;
        double p = sqrt(E*E - mass*mass);
        return p;
}

std::vector<TGraphErrors*> fillAdep(std::vector<TGraphErrors*> He, std::vector<TGraphErrors*> C, std::vector<TGraphErrors*> Fe) {

        std::vector<TGraphErrors*> adep_graphs;

        TGraphErrors *d[3];
        TGraphErrors *s[3];
        TGraphErrors *g[3];

        TLegend *legA[3];

        TF1 *fit_data[3];
        TF1 *fit_susa[3];
        TF1 *fit_g18[3];

        TFitResultPtr r_data[3];
        TFitResultPtr r_susa[3];
        TFitResultPtr r_g18[3];

        TGraphErrors *mom_dep[3];
        TCanvas *c[3];

        mom_dep[0] = new TGraphErrors();
        mom_dep[1] = new TGraphErrors();
        mom_dep[2] = new TGraphErrors();

        for(int range = 0; range < 3; range++) {
                std::cout << "Fitting for range " << range+1 << "\n";
                c[range] = new TCanvas(TString::Format("%i",range+1),TString::Format("%i",range+1), 1200, 1000);
                d[range] = new TGraphErrors();
                s[range] = new TGraphErrors();
                g[range] = new TGraphErrors();


                d[range]->SetPoint(0,A_He,He[0]->GetY()[range]);
                d[range]->SetPointError(0,0,He[0]->GetErrorY(range));
                d[range]->SetPoint(1,A_C,C[0]->GetY()[range]);
                d[range]->SetPointError(1,0,C[0]->GetErrorY(range));
                d[range]->SetPoint(2,A_Fe,Fe[0]->GetY()[range]);
                d[range]->SetPointError(2,0,Fe[0]->GetErrorY(range));

                s[range]->SetPoint(0,A_He,He[1]->GetY()[range]);
                s[range]->SetPointError(0,0,He[1]->GetErrorY(range));
                s[range]->SetPoint(1,A_C,C[1]->GetY()[range]);
                s[range]->SetPointError(1,0,C[1]->GetErrorY(range));
                s[range]->SetPoint(2,A_Fe,Fe[1]->GetY()[range]);
                s[range]->SetPointError(2,0,Fe[1]->GetErrorY(range));
                
                g[range]->SetPoint(0,A_He,He[2]->GetY()[range]);
                g[range]->SetPointError(0,0,He[2]->GetErrorY(range));
                g[range]->SetPoint(1,A_C,C[2]->GetY()[range]);
                g[range]->SetPointError(1,0,C[2]->GetErrorY(range));
                g[range]->SetPoint(2,A_Fe,Fe[2]->GetY()[range]);
                g[range]->SetPointError(2,0,Fe[2]->GetErrorY(range));

                double avg_mom_d = 0.; 
                double avg_mom_s = 0.; 
                double avg_mom_g = 0.; 
                avg_mom_d += (He[0]->GetX()[range] + C[0]->GetX()[range] + Fe[0]->GetX()[range])/3.;
                avg_mom_s += (He[1]->GetX()[range] + C[1]->GetX()[range] + Fe[1]->GetX()[range])/3.;
                avg_mom_g += (He[2]->GetX()[range] + C[2]->GetX()[range] + Fe[2]->GetX()[range])/3.;
                //std::cout << "Average momentum data = " << avg_mom_d << "\n";
                //std::cout << "Average momentum susa = " << avg_mom_s << "\n";
                //std::cout << "Average momentum g18 = " << avg_mom_g << "\n";

                double mom_err_d = 0.;
                double mom_err_s = 0.;
                double mom_err_g = 0.;
                mom_err_d += pow(avg_mom_d - He[0]->GetX()[range],2) + pow(avg_mom_d - C[0]->GetX()[range],2) + pow(avg_mom_d - Fe[0]->GetX()[range],2);
                mom_err_s += pow(avg_mom_s - He[1]->GetX()[range],2) + pow(avg_mom_s - C[1]->GetX()[range],2) + pow(avg_mom_s - Fe[1]->GetX()[range],2);
                mom_err_g += pow(avg_mom_g - He[2]->GetX()[range],2) + pow(avg_mom_g - C[2]->GetX()[range],2) + pow(avg_mom_g - Fe[2]->GetX()[range],2);
                mom_err_d = sqrt(mom_err_d);
                mom_err_s = sqrt(mom_err_s);
                mom_err_g = sqrt(mom_err_g);

                fit_data[range] = new TF1("F_data", "pow(x,-[0])");
                fit_susa[range] = new TF1("F_susa", "pow(x,-[0])");
                fit_g18[range] = new TF1("F_g18", "pow(x,-[0])");

                fit_data[range]->SetLineColor(kBlack);
                fit_susa[range]->SetLineColor(kBlue);
                fit_g18[range]->SetLineColor(kRed);

                r_data[range] = d[range]->Fit("F_data","SQ");
                r_susa[range] = s[range]->Fit("F_susa","SQ");
                r_g18[range] = g[range]->Fit("F_g18","SQ");

                double alpha_data = r_data[range]->Parameter(0);
                double alpha_data_err = r_data[range]->ParError(0);
                double alpha_susa = r_susa[range]->Parameter(0);
                double alpha_susa_err = r_susa[range]->ParError(0);
                double alpha_g18 = r_g18[range]->Parameter(0);
                double alpha_g18_err = r_g18[range]->ParError(0);
                
                mom_dep[0]->SetPoint(range, avg_mom_d, alpha_data);
                mom_dep[0]->SetPointError(range, mom_err_d, alpha_data_err);
                //std::cout << "Range: " << range << ", avg mom: " << avg_mom_d << ", alpha = " << alpha_data << "\n";

                mom_dep[1]->SetPoint(range, avg_mom_s, alpha_susa);
                mom_dep[1]->SetPointError(range, mom_err_s, alpha_susa_err);

                mom_dep[2]->SetPoint(range, avg_mom_g, alpha_g18);
                mom_dep[2]->SetPointError(range, mom_err_g, alpha_g18_err);

                PrettyGraph(d[range]);
                PrettyGraph(s[range]);
                PrettyGraph(g[range]);

                d[range]->SetMarkerStyle(kFullCircle);
                s[range]->SetMarkerStyle(kFullCircle);
                g[range]->SetMarkerStyle(kFullCircle);

                d[range]->SetMarkerSize(1.5);
                s[range]->SetMarkerSize(1.5);
                g[range]->SetMarkerSize(1.5);

                d[range]->SetMarkerColor(kBlack);
                s[range]->SetMarkerColor(kBlue);
                g[range]->SetMarkerColor(kRed);

                d[range]->Draw("AP");
                s[range]->Draw("P");
                g[range]->Draw("P");

                d[range]->GetYaxis()->SetTitle("Transparency");
                d[range]->GetXaxis()->SetTitle("A");
                d[range]->GetYaxis()->SetRangeUser(0,1.0);

                legA[range] = new TLegend(.82,.65,.99,.85);
                legA[range]->AddEntry(d[range], TString::Format("#splitline{Data: #alpha = %3.2f}{+/- %3.2e}", r_data[range]->Parameter(0),r_data[range]->ParError(0)));
                legA[range]->AddEntry(s[range], TString::Format("#splitline{SuSAv2: #alpha = %3.2f}{+/- %3.2e}", r_susa[range]->Parameter(0),r_susa[range]->ParError(0)));
                legA[range]->AddEntry(g[range], TString::Format("#splitline{G18: #alpha = %3.2f}{+/- %3.2e}", r_g18[range]->Parameter(0),r_g18[range]->ParError(0)));
                legA[range]->SetBorderSize(0);
                legA[range]->Draw();

                c[range]->SetLeftMargin(0.2);
                c[range]->SetBottomMargin(0.2);
                c[range]->SetRightMargin(0.2);
                c[range]->Update();

                c[range]->SaveAs(TString::Format("A_dep_range%i.pdf",range));
        }

        for(int i = 0; i < 3; i++) {
                mom_dep[i]->SetMarkerStyle(kFullCircle);
                mom_dep[i]->SetMarkerSize(1.5);
                adep_graphs.push_back(mom_dep[i]);
        }

        return adep_graphs;
}

void draw_data() {

gStyle->SetOptTitle(0);

TFile *Fe_file = TFile::Open("T_Fe56_sectors.root");
TFile *He_file = TFile::Open("T_He4_sectors.root");
TFile *C_file = TFile::Open("T_C12_sectors.root");


TGraphErrors * C_G = (TGraphErrors*)C_file->Get("data_C12");
TGraphErrors * He_G = (TGraphErrors*)He_file->Get("data_He4");
TGraphErrors * Fe_G = (TGraphErrors*)Fe_file->Get("data_Fe56");


TGraphErrors * SuSAC_G = (TGraphErrors*)C_file->Get("SuSA_C12");
TGraphErrors * SuSAHe_G = (TGraphErrors*)He_file->Get("SuSA_He4");
TGraphErrors * SuSAFe_G = (TGraphErrors*)Fe_file->Get("SuSA_Fe56");


TGraphErrors * G18C_G = (TGraphErrors*)C_file->Get("G_C12");
TGraphErrors * G18He_G = (TGraphErrors*)He_file->Get("G_He4");
TGraphErrors * G18Fe_G = (TGraphErrors*)Fe_file->Get("G_Fe56");


TCanvas *c1 = new TCanvas("c1","c1",1200,1000);
c1->SetLeftMargin(0.2);
c1->SetBottomMargin(0.2);
c1->SetRightMargin(0.2);

PrettyGraph(C_G);
PrettyGraph(He_G);
PrettyGraph(Fe_G);
C_G->GetYaxis()->SetRangeUser(0.0,1.0);
He_G->SetMarkerColor(kRed);
C_G->SetMarkerColor(kBlue);
Fe_G->SetMarkerColor(kBlack);
Fe_G->RemovePoint(3);
C_G->Draw("AP");
Fe_G->Draw("P");
He_G->Draw("P");
TLegend *leg = new TLegend(.82,.55,.99,.85);
leg->SetBorderSize(0);
leg->AddEntry(C_G, "C");
leg->AddEntry(He_G, "He");
leg->AddEntry(Fe_G, "Fe");
leg->Draw();
leg->SetBorderSize(0);
//c1->SaveAs("Data_total_T.pdf");

TCanvas *c2 = new TCanvas("c2","c2",1200,1000);
c2->SetLeftMargin(0.2);
c2->SetBottomMargin(0.2);
c2->SetRightMargin(0.2);
PrettyGraph(SuSAC_G);
PrettyGraph(SuSAHe_G);
PrettyGraph(SuSAFe_G);
TAxis *axis2 = SuSAHe_G->GetXaxis();
axis2->SetLimits(0.5,1.7);
SuSAC_G->GetYaxis()->SetRangeUser(0.0,1.);
SuSAC_G->GetXaxis()->SetRangeUser(0.3,1.6);
SuSAHe_G->SetMarkerColor(kRed);
SuSAC_G->SetMarkerColor(kBlue);
SuSAFe_G->SetMarkerColor(kBlack);
SuSAHe_G->Draw("AP");
SuSAC_G->Draw("P");
SuSAFe_G->Draw("P");
TLegend *leg2 = new TLegend(.82,.55,.99,.85);
leg2->AddEntry(SuSAC_G, "C");
leg2->AddEntry(SuSAHe_G, "He");
leg2->AddEntry(SuSAFe_G, "Fe");
leg2->SetBorderSize(0);
leg2->Draw();
//c2->SaveAs("SuSA_total_T.pdf");

TCanvas *c3 = new TCanvas("c3","c3",1200,1000);
c3->SetLeftMargin(0.2);
c3->SetBottomMargin(0.2);
c3->SetRightMargin(0.2);
PrettyGraph(G18C_G);
PrettyGraph(G18He_G);
PrettyGraph(G18Fe_G);
G18C_G->GetYaxis()->SetRangeUser(0,1.);
G18He_G->SetMarkerColor(kRed);
G18C_G->SetMarkerColor(kBlue);
G18Fe_G->SetMarkerColor(kBlack);
G18C_G->Draw("AP");
G18Fe_G->Draw("P");
G18He_G->Draw("P");
TLegend *leg3 = new TLegend(.82,.55,.99,.85);
leg3->AddEntry(G18C_G, "C");
leg3->AddEntry(G18He_G, "He");
leg3->AddEntry(G18Fe_G, "Fe");
leg3->SetBorderSize(0);
leg3->Draw();
//c3->SaveAs("G18_total_T.pdf");

std::vector<TGraphErrors*> He;
He.push_back(He_G); He.push_back(SuSAHe_G); He.push_back(G18He_G);
std::vector<TGraphErrors*> C;
C.push_back(C_G); C.push_back(SuSAC_G); C.push_back(G18C_G);
std::vector<TGraphErrors*> Fe;
Fe.push_back(Fe_G); Fe.push_back(SuSAFe_G); Fe.push_back(G18Fe_G);

std::vector<TGraphErrors*> Adep = fillAdep(He, C, Fe);


TCanvas *c4 = new TCanvas("c4","c4",1200,1000);
PrettyGraph(Adep[0]);
PrettyGraph(Adep[1]);
PrettyGraph(Adep[2]);

Adep[0]->SetMarkerColor(kBlack);
Adep[1]->SetMarkerColor(kBlue);
Adep[2]->SetMarkerColor(kRed);

Adep[0]->GetYaxis()->SetRangeUser(0,.3);
TAxis *axis = Adep[0]->GetXaxis();
axis->SetLimits(0.01,5.);

Adep[0]->Draw("AP");
Adep[1]->Draw("P");
Adep[2]->Draw("P");

Adep[0]->GetXaxis()->SetTitle("Proton Momentum (GeV)");
Adep[0]->GetYaxis()->SetTitle("#alpha");

TGraphErrors* G_Garino = new TGraphErrors();
G_Garino->SetPoint(0,mom(0.18),0.23);
G_Garino->SetPointError(0,mom(0.05),.03);
G_Garino->SetMarkerStyle(34);
G_Garino->SetMarkerSize(1.5);
G_Garino->SetMarkerColor(kBlack);
G_Garino->Draw("P");

TGraphErrors* G_Abbott = new TGraphErrors();
G_Abbott->SetPoint(0,.35,0.17);
G_Abbott->SetPointError(0,0,.04);
G_Abbott->SetPoint(1,.7,0.22);
G_Abbott->SetPointError(1,0,.05);
G_Abbott->SetPoint(2,.97,0.24);
G_Abbott->SetPointError(2,0,.04);
G_Abbott->SetPoint(3,1.8,0.25);
G_Abbott->SetPointError(3,0,.04);
G_Abbott->SetMarkerStyle(22);
G_Abbott->SetMarkerSize(1.5);
G_Abbott->SetMarkerColor(kBlack);
G_Abbott->Draw("P");

TGraphErrors* G_Oneill = new TGraphErrors();
G_Oneill->SetPoint(0,mom(.582),0.18);
G_Oneill->SetPointError(0,0,.02);
G_Oneill->SetPoint(1,mom(1.678),0.24);
G_Oneill->SetPointError(1,0,.02);
G_Oneill->SetPoint(2,mom(2.722),0.24);
G_Oneill->SetPointError(2,0,.02);
G_Oneill->SetPoint(3,mom(3.641),0.20);
G_Oneill->SetPointError(3,0,.02);
G_Oneill->SetMarkerStyle(21);
G_Oneill->SetMarkerSize(1.5);
G_Oneill->SetMarkerColor(kBlack);
G_Oneill->Draw("P");

TGraphErrors* G_Garrow = new TGraphErrors();
G_Garrow->SetPoint(0,mom(1.760),0.24);
G_Garrow->SetPointError(0,0,.02);
G_Garrow->SetPoint(1,mom(3.263),0.24);
G_Garrow->SetPointError(1,0,.03);
G_Garrow->SetPoint(2,mom(4.293),0.23);
G_Garrow->SetPointError(2,0,.02);
G_Garrow->SetMarkerStyle(29);
G_Garrow->SetMarkerSize(1.5);
G_Garrow->SetMarkerColor(kBlack);
G_Garrow->Draw("P");


TLegend *leg4 = new TLegend(.82,.65,.99,.85);
leg4->AddEntry(Adep[0], "This Work");
leg4->AddEntry(Adep[1], "SuSAv2");
leg4->AddEntry(Adep[2], "G18");
leg4->AddEntry(G_Garino, "MIT 1992", "p");
leg4->AddEntry(G_Oneill, "SLAC 1995", "p");
leg4->AddEntry(G_Abbott, "JLab 2005", "p");
leg4->AddEntry(G_Garrow, "JLab 2002", "p");
leg4->SetBorderSize(0);
leg4->SetNColumns(2);
leg4->Draw();

c4->SetLeftMargin(.2);
c4->SetBottomMargin(.2);
c4->SetRightMargin(.2);
c4->Update();

//c4->SaveAs("A_dep.pdf");



}
