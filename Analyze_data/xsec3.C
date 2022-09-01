#include "myFunctions.cpp"


void xsec3() {


	TFile *input[3];
	input[0] = TFile::Open("/genie/app/users/gchamber/e4nu_2022/e4nu/output/output2022/fixed_Q2_2/Exclusive/Exclusive_Range1_Genie_2_C12_2.261000.root");
	input[1] = TFile::Open("/genie/app/users/gchamber/e4nu_2022/e4nu/output/output2022/fixed_Q2_2/Exclusive/Exclusive_Range2_Genie_2_C12_2.261000.root");
	input[2] = TFile::Open("/genie/app/users/gchamber/e4nu_2022/e4nu/output/output2022/fixed_Q2_2/Exclusive/Exclusive_Range3_Genie_2_C12_2.261000.root");

	TH1D* h1_prot_momentum_sector[3][6][4];


	for (int file_i = 0; file_i < 3; file_i++){
                std::cout << "File " << file_i << "\n";
                for (int sector = 0; sector < 6; sector++) {
                        std::cout << "Sector " << sector << "\n";
        		for(int interact = 0; interact < 4; interact++) {
	                	std::cout << "Interaction " << interact << "\n";
				h1_prot_momentum_sector[file_i][sector][interact] = (TH1D*)input[file_i]->Get( TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", interact+1, sector) );
                        	
				if(interact != 0 ) {
					std::cout << "Adding file " << file_i << ", sector " << sector << ", interaction " << interact << "to first hist \n"; 
					h1_prot_momentum_sector[file_i][sector][0]->Add(h1_prot_momentum_sector[file_i][sector][interact]);
				}
			}
			if(sector !=0 ) {
                                std::cout << "Adding file " << file_i << ", sector " << sector << " to first hist \n";
                                h1_prot_momentum_sector[file_i][0][0]->Add(h1_prot_momentum_sector[file_i][sector][0]);
			}
                }
        }


	double integral[3];	
	double err[3];

	        TCanvas* c;
        c= new TCanvas(TString::Format("c"), TString::Format("c"), 800, 600);
        const int color_options[3] = {kBlue, kRed, kBlack};
        const char * draw_options[3] = {"HIST","HIST SAME","HIST SAME"};

        UniversalE4vFunction(h1_prot_momentum_sector[0][0][0],"G2018 QE Only","12C","2_261","h1_prot_mom");
        UniversalE4vFunction(h1_prot_momentum_sector[1][0][0],"G2018 QE Only","12C","2_261","h1_prot_mom");
        UniversalE4vFunction(h1_prot_momentum_sector[2][0][0],"G2018 QE Only","12C","2_261","h1_prot_mom");

        double tot_xsec = 0;
        for (int i=0;i<3;i++){
                h1_prot_momentum_sector[i][0][0]->SetStats(0);
                h1_prot_momentum_sector[i][0][0]->SetLineColor(color_options[i]);
                h1_prot_momentum_sector[i][0][0]->GetXaxis()->SetTitle("Proton Momentum [GeV/c]");
                h1_prot_momentum_sector[i][0][0]->Rebin(10);
                h1_prot_momentum_sector[i][0][0]->GetYaxis()->SetTitle("absolute double differential cross section [#mub]");
                h1_prot_momentum_sector[i][0][0]->GetXaxis()->SetRangeUser(0,2);
                h1_prot_momentum_sector[i][0][0]->SetTitle("C-12 @ 2.261 GeV e^{-} Beam (CLAS with exclusive cuts)");
                h1_prot_momentum_sector[i][0][0]->Draw(draw_options[i]);
                integral[i] = h1_prot_momentum_sector[i][0][0]->IntegralAndError(1,h1_prot_momentum_sector[i][0][0]->GetNbinsX(),err[i],"width");
                std::cout << "Range" << i+1 << "  cross section: " << integral[i] << " +/- " << err[i] << std::endl;
                tot_xsec += integral[i];
        }
        std::cout << tot_xsec << std::endl;
        c->SetLeftMargin(0.13);
        c->Update();

        TLegend *legend = new TLegend(0.75, 0.7, 0.9, 0.88);
        legend->AddEntry(h1_prot_momentum_sector[0][0][0],"Range 1","l");
        legend->AddEntry(h1_prot_momentum_sector[1][0][0],"Range 2","l");
        legend->AddEntry(h1_prot_momentum_sector[2][0][0],"Range 3","l");
        legend->SetBorderSize(0);
        legend->SetFillStyle(0);
        legend->Draw();

        c->SaveAs(TString::Format("prot_xsec_C12_2261_data_allranges.pdf"));
}
