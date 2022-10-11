#ifndef NOAHCONSTANTSC12_H
#define NOAHCONSTANTSC12_H

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


		// Get Data Files
		// Format is [Ranges][Excl/Incl]
        // Excl == 0, Incl == 1
        std::string data_1161[2][2];
        std::string data_2261[3][2];
        std::string data_4461[1][2];


        // SUSA MC
        std::string susa_1161[2][2];
        std::string susa_2261[3][2];
        std::string susa_4461[1][2];

        //G18 MC
        std::string g_1161[2][2];
        std::string g_2261[3][2];
        std::string g_4461[1][2];

        // SuSA TRUE RECO MC
        std::string susa_1161_truereco[2][2];
        std::string susa_2261_truereco[3][2];
        std::string susa_4461_truereco[1][2];


        // SuSA TRUE MC
        std::string susa_1161_true[2][2];
        std::string susa_2261_true[3][2];
        std::string susa_4461_true[1][2];

        

        // G18 TRUE RECO MC
        std::string g_1161_truereco[2][2];
        std::string g_2261_truereco[3][2];
        std::string g_4461_truereco[1][2];

        

        // G18 TRUE MC
        std::string g_1161_true[2][2];
        std::string g_2261_true[3][2];
        std::string g_4461_true[1][2];

        // MC rad corr files
        std::string susa_1161_truereco_rad[2][2];
        std::string susa_2261_truereco_rad[3][2];
        std::string susa_4461_truereco_rad[1][2];


        


#endif
