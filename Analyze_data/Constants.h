#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <TF1.h>
#include <TString.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>

	// ------------------------------------------------------------------------------------

	// All units are in GeV

	const double m_pimi = 0.139570, m_pipl = 0.139570, m_pion = 0.139570;
	const double m_prot = 0.9382720813, m_neut = 0.939565;
	const double H3_bind_en = 0.008481, He4_bind_en = 0.0283, C12_bind_en = 0.09215, B_bind_en = 0.0762;
	const double He3_bind_en = 0.0077, D2_bind_en = 0.00222, Fe_bind_en = 0.49226, Mn_bind_en = 0.4820764;
	const double e_mass = 0.000510998;

	const double fine_struc_const = 0.007297;
	const double ns_to_s = 1.0E-9;
	const Double_t c = 2.99792E+10;

	// smithja: Note these variables are only half of the Delta-phi cuts made in the 
	// genie_analysis code, e.g. PhiOpeningAngleEl = 6 --> Delta-phi for the electron is 12.
	const double PhiOpeningAngleEl = 6;
	const double PhiOpeningAngleProt = 22.5;
        const double PhiOpeningAngle = 6.;

	static const Float_t par_EcUVW[6][3] = {{60, 360, 400}, {55, 360, 400}, {50, 363, 400}, {52, 365, 396}, {60, 360, 398}, {50, 362, 398}};

	const double MinThetaProton = 12.;
	const double MinThetaPiPlus = 12.;
	const double MinThetaPiMinus = 0.;
	const double MinThetaGamma = 8.;

	const double CenterFirstSector = 30;
	const double CenterSecondSector = 90;
	const double CenterThirdSector = 150;
	const double CenterFourthSector = 210;
	const double CenterFifthSector = 270;
	const double CenterSixthSector = 330;

	const int RotCounterLimit = 100;

#endif
