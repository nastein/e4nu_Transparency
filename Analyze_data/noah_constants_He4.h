#ifndef NOAHCONSTANTSHe4_H
#define NOAHCONSTANTSHe4_H

#include <TF1.h>
#include <TString.h>
#include <TH1F.h>
#include <TFile.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>

	double get_Neutron_corr(TString file, bool incl);
        double get_MEC_corr(TString file, int sectors, bool electrons);
        TH1D* SumElecSectorsAndInts(TString file, int sectors, bool isData);
        TH1D* SumProtSectorsAndInts(TString file, int sectors, bool isData);
        TH1D* AcceptanceCorrect(TH1D* hist, TH1D* susa_true, TH1D* susa_truereco, TH1D* G_true, TH1D* G_truereco, TH1D* susa_truereco_rad, bool make_plots, std::string type);
        double get_ratio_error(double num, double denom);
        void printit(std::string s, double x);
        double diff_squared(double x, double y);
        double myratio(double x, double y);

        // Get Data Files
        // Format is [Ranges][Excl/Incl]
        // Excl == 0, Incl == 1
        std::string data_2261[3][2];
        std::string data_4461[1][2];


        // SUSA MC
        std::string susa_2261[3][2];
        std::string susa_4461[1][2];

        //G18 MC
        std::string g_2261[3][2];
        std::string g_4461[1][2];

        // SuSA TRUE RECO MC
        std::string susa_2261_truereco[3][2];
        std::string susa_4461_truereco[1][2];


        // SuSA TRUE MC
        std::string susa_2261_true[3][2];
        std::string susa_4461_true[1][2];

        

        // G18 TRUE RECO MC
        std::string g_2261_truereco[3][2];
        std::string g_4461_truereco[1][2];

        

        // G18 TRUE MC
        std::string g_2261_true[3][2];
        std::string g_4461_true[1][2];

        


        // MC rad corr files
        std::string susa_2261_truereco_rad[3][2];
        std::string susa_4461_truereco_rad[1][2];

        


#endif
